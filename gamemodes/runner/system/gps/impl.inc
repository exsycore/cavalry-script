#if defined _inc_gps_impl
    #undef _inc_gps_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
    mysql_tquery(get_handle(), "SELECT * FROM "GPS_TABLE"", "GPSLoad", "");
    return true;
}

public GPSLoad() {
    new rows;
    cache_get_row_count(rows);

    for (new i = 0; i < rows && i < MAX_GPS; i++) {
        GPSData[i][E_GPS_exists] = true;
        cache_get_value_name_int(i,   "gpsid",    GPSData[i][E_GPS_id]);
        cache_get_value_name(i,       "name",      GPSData[i][E_GPS_name]);
        cache_get_value_name_int(i,   "category",  GPSData[i][E_GPS_category]);
        cache_get_value_name_float(i, "x",         GPSData[i][E_GPS_x]);
        cache_get_value_name_float(i, "y",         GPSData[i][E_GPS_y]);
        cache_get_value_name_float(i, "z",         GPSData[i][E_GPS_z]);
    }
    printf("[SYSTEM][DB] %d GPS Location loaded.", rows);
    return true;
}

public OnGPSCreated(gpsid) {
    if (gpsid == -1 || !GPSData[gpsid][E_GPS_exists]) return false;
    GPSData[gpsid][E_GPS_id] = cache_insert_id();
    GPSSave(gpsid);
    return true;
}

stock GPSSave(gpsid) {
    new query[256];
    mysql_format(get_handle(), query, sizeof query,
        "UPDATE "GPS_TABLE" SET `name`='%e', `category`='%d', `x`='%.4f', `y`='%.4f', `z`='%.4f' WHERE `gpsid`='%d'",
        GPSData[gpsid][E_GPS_name],
        GPSData[gpsid][E_GPS_category],
        GPSData[gpsid][E_GPS_x],
        GPSData[gpsid][E_GPS_y],
        GPSData[gpsid][E_GPS_z],
        GPSData[gpsid][E_GPS_id]);
    return mysql_tquery(get_handle(), query);
}

stock GPSCreate(const name[], category, Float:x, Float:y, Float:z) {
    for (new i = 0; i < MAX_GPS; i++) {
        if (!GPSData[i][E_GPS_exists]) {
            GPSData[i][E_GPS_exists]   = true;
            GPSData[i][E_GPS_category] = category;
            GPSData[i][E_GPS_x] = x;
            GPSData[i][E_GPS_y] = y;
            GPSData[i][E_GPS_z] = z;
            GPSData[i][E_GPS_name][0] = '\0';
            strcat(GPSData[i][E_GPS_name], name);

            mysql_tquery(get_handle(),
                "INSERT INTO "GPS_TABLE" (`gpsid`) VALUES(0)",
                "OnGPSCreated", "d", i);
            return i;
        }
    }
    return -1;
}

stock GPSDelete(gpsid) {
    if (gpsid == -1 || !GPSData[gpsid][E_GPS_exists]) return false;

    foreach (new i : Player)
        if (GPS_ActiveID[i] == gpsid) GPSStop(i);

    new query[64];
    mysql_format(get_handle(), query, sizeof query, "DELETE FROM "GPS_TABLE" WHERE `gpsid`='%d'", GPSData[gpsid][E_GPS_id]);
    mysql_tquery(get_handle(), query);

    GPSData[gpsid][E_GPS_exists]    = false;
    GPSData[gpsid][E_GPS_id]        = 0;
    GPSData[gpsid][E_GPS_name][0]   = '\0';
    return true;
}

stock GPSStart(playerid, gpsid) {
    if (gpsid == -1 || !GPSData[gpsid][E_GPS_exists]) return false;

    GPSStop(playerid);

    GPS_ActiveID[playerid] = gpsid;
    GPS_CP[playerid] = CreateDynamicCP(
        GPSData[gpsid][E_GPS_x],
        GPSData[gpsid][E_GPS_y],
        GPSData[gpsid][E_GPS_z],
        GPS_CP_SIZE,
        .playerid       = playerid,
        .streamdistance = GPS_CP_SD);

    SetPlayerCheckpoint(playerid,
        GPSData[gpsid][E_GPS_x],
        GPSData[gpsid][E_GPS_y],
        GPSData[gpsid][E_GPS_z],
        GPS_CP_SIZE);

    GameTextForPlayer(playerid, "~y~GPS: ON", 2000, 7);
    SendCongratMessage(playerid, "{FFFFFF}GPS นำทางไป: %s", GPSData[gpsid][E_GPS_name]);
    return true;
}

stock GPSStop(playerid) {
    if (GPS_ActiveID[playerid] == -1) return false;

    if (IsValidDynamicCP(GPS_CP[playerid]))
        DestroyDynamicCP(GPS_CP[playerid]);

    DisablePlayerCheckpoint(playerid);
    GPS_ActiveID[playerid] = -1;
    return true;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid) {
    if (GPS_ActiveID[playerid] == -1) return true;
    if (GPS_CP[playerid] != checkpointid) return true;

    new name[64];
    format(name, sizeof name, "%s", GPSData[GPS_ActiveID[playerid]][E_GPS_name]);
    GPSStop(playerid);

    GameTextForPlayer(playerid, "~y~GPS: OFF", 2000, 7);
    SendCongratMessage(playerid, "{FFFFFF}คุณถึงจุดหมาย: %s แล้ว", name);
    return true;
}

hook OnPlayerDisconnect(playerid, reason) {
    GPSStop(playerid);
    return true;
}

stock GPSDialogCategory(playerid) {
    new count[GPS_CAT_MAX];
    for (new i = 0; i < MAX_GPS; i++) {
        if (!GPSData[i][E_GPS_exists]) continue;
        new cat = GPSData[i][E_GPS_category];
        if (cat >= 0 && cat < GPS_CAT_MAX) count[cat]++;
    }

    new str[512] = "";
    new hasAny = false;
    for (new c = 0; c < GPS_CAT_MAX; c++) {
        new row[64];
        format(row, sizeof row, "%s%s {AAAAAA}(%d จุด)\n",
            GPS_CAT_COLOR[c], GPS_CAT_NAME[c], count[c]);
        strcat(str, row);
        if (count[c]) hasAny = true;
    }

    if (!hasAny) {
        SendErrorMessage(playerid, "{FFFFFF}ยังไม่มีจุดหมาย GPS ในระบบ");
        return true;
    }

    inline const PickCat(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return true;
        if (listitem < 0 || listitem >= GPS_CAT_MAX) @return true;

        GPSDialogSelect(playerid, listitem);
    }
    Dialog_ShowCallback(playerid, using inline PickCat, DIALOG_STYLE_LIST, "{FFFFFF}GPS — เลือกประเภท", str, "เลือก", "ยกเลิก");
    return true;
}

stock GPSDialogSelect(playerid, category) {
    new str[4096] = "";
    new count = 0;
    new mapping[MAX_GPS];

    for (new i = 0; i < MAX_GPS; i++) {
        if (!GPSData[i][E_GPS_exists]) continue;
        if (GPSData[i][E_GPS_category] != category) continue;

        new row[128];
        format(row, sizeof row, "%s%s\n", GPS_CAT_COLOR[category], GPSData[i][E_GPS_name]);
        strcat(str, row);
        mapping[count] = i;
        count++;
    }

    if (!count) {
        SendErrorMessage(playerid, "{FFFFFF}ไม่มีจุดหมายในหมวดนี้");
        return GPSDialogCategory(playerid);
    }

    static s_map[MAX_GPS], s_count;
    s_count = count;
    for (new i = 0; i < count; i++) s_map[i] = mapping[i];

    new title[64];
    format(title, sizeof title, "{FFFFFF}GPS — %s", GPS_CAT_NAME[category]);

    inline const Pick(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return GPSDialogCategory(playerid);
        if (listitem >= s_count) @return true;

        GPSStart(playerid, s_map[listitem]);
    }
    Dialog_ShowCallback(playerid, using inline Pick, DIALOG_STYLE_LIST,
        title, str, "นำทาง", "ย้อนกลับ");
    return true;
}

stock PanelGPS(playerid) {
    if (!IsPlayerAdminEx(playerid)) return true;

    inline const MainMenu(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return true;

        switch (listitem) {
            case 0: GPSAdminDialogCreate(playerid);
            case 1: GPSAdminDialogDelete(playerid);
            case 2: GPSAdminDialogRename(playerid);
            case 3: GPSAdminDialogChangeCategory(playerid);
            case 4: GPSAdminDialogMove(playerid);
            case 5: GPSAdminDialogList(playerid);
            case 6: GPSAdminDialogWarpTo(playerid);
        }
    }
    Dialog_ShowCallback(playerid, using inline MainMenu, DIALOG_STYLE_LIST,
        "{FFFFFF}AdminPanel (GPS)",
        "สร้างจุด GPS\nลบจุด GPS\nเปลี่ยนชื่อ\nเปลี่ยนหมวดหมู่\nย้ายตำแหน่ง\nรายการจุด GPS\nวาร์ปไปหาจุด GPS",
        "เลือก", "ยกเลิก");
    return true;
}

YCMD:agps(playerid, string:params[], help) {
    if (!GetPlayerLoggedIn(playerid)) return 1;
    if (!IsPlayerAdminEx(playerid)) return 1;

    PanelGPS(playerid);
    return 1;
}

stock GPSAdminPickCategory(playerid, &out_cat) {
    #pragma unused out_cat
    return true;
}

stock GPSAdminDialogCreate(playerid) {
    inline const InputName(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return PanelGPS(playerid);

        if (!strlen(inputtext) || strlen(inputtext) > 63) {
            SendErrorMessage(playerid, "{FFFFFF}ชื่อต้องมีความยาว 1-63 ตัวอักษร");
            @return GPSAdminDialogCreate(playerid);
        }

        new savedName[64];
        format(savedName, sizeof savedName, "%s", inputtext);

        new catStr[256] = "";
        for (new c = 0; c < GPS_CAT_MAX; c++) {
            new row[64];
            format(row, sizeof row, "%s%s\n", GPS_CAT_COLOR[c], GPS_CAT_NAME[c]);
            strcat(catStr, row);
        }

        inline const PickCat(pid2, dialogid2, response2, listitem2, string:inputtext2[]) {
            #pragma unused dialogid2, inputtext2, pid2
            if (!response2) @return PanelGPS(playerid);
            if (listitem2 < 0 || listitem2 >= GPS_CAT_MAX) @return true;

            new Float:x, Float:y, Float:z;
            GetPlayerPos(playerid, x, y, z);

            new id = GPSCreate(savedName, listitem2, x, y, z);
            if (id == -1) {
                SendErrorMessage(playerid, "{FFFFFF}ความจุจุด GPS เต็มแล้ว (MAX_GPS)");
                @return true;
            }
            SendAdminMessage(COLOR_ADMIN,
                "AdmLog: %s สร้างจุด GPS ID:%d [%s] '%s' ที่ (%.1f,%.1f,%.1f)",
                ReturnPlayerName(playerid), id,
                GPS_CAT_NAME[listitem2], savedName, x, y, z);
        }
        Dialog_ShowCallback(playerid, using inline PickCat, DIALOG_STYLE_LIST,
            "{FFFFFF}เลือกหมวดหมู่", catStr, "เลือก", "ย้อนกลับ");
    }
    Dialog_ShowCallback(playerid, using inline InputName, DIALOG_STYLE_INPUT,
        "{FFFFFF}สร้างจุด GPS",
        "ป้อนชื่อจุดหมาย\n{AAAAAA}ตำแหน่งปัจจุบันของคุณจะถูกบันทึก",
        "ถัดไป", "ย้อนกลับ");
    return true;
}

stock GPSAdminDialogDelete(playerid) {
    inline const InputID(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return PanelGPS(playerid);

        new id = -1;
        if (sscanf(inputtext, "d", id) || id < 0 || id >= MAX_GPS || !GPSData[id][E_GPS_exists]) {
            SendErrorMessage(playerid, "{FFFFFF}ID ไม่ถูกต้องหรือไม่มีอยู่ในระบบ");
            @return GPSAdminDialogDelete(playerid);
        }
        new name[64];
        format(name, sizeof name, "%s", GPSData[id][E_GPS_name]);
        GPSDelete(id);
        SendAdminMessage(COLOR_ADMIN,
            "AdmLog: %s ลบจุด GPS LocalID:%d '%s'",
            ReturnPlayerName(playerid), id, name);
    }
    Dialog_ShowCallback(playerid, using inline InputID, DIALOG_STYLE_INPUT,
        "{FFFFFF}ลบจุด GPS",
        "ป้อน Local ID ของจุด GPS\n{AAAAAA}(ดู ID ได้จากเมนู รายการจุด GPS)",
        "ลบ", "ย้อนกลับ");
    return true;
}

stock GPSAdminDialogRename(playerid) {
    inline const InputID(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return PanelGPS(playerid);

        new id = -1;
        if (sscanf(inputtext, "d", id) || id < 0 || id >= MAX_GPS || !GPSData[id][E_GPS_exists]) {
            SendErrorMessage(playerid, "{FFFFFF}ID ไม่ถูกต้องหรือไม่มีอยู่ในระบบ");
            @return GPSAdminDialogRename(playerid);
        }

        inline const InputName(pid2, dialogid2, response2, listitem2, string:inputtext2[]) {
            #pragma unused dialogid2, listitem2, pid2
            if (!response2) @return PanelGPS(playerid);

            if (!strlen(inputtext2) || strlen(inputtext2) > 63) {
                SendErrorMessage(playerid, "{FFFFFF}ชื่อต้องมีความยาว 1-63 ตัวอักษร");
                @return GPSAdminDialogRename(playerid);
            }
            new old[64];
            format(old, sizeof old, "%s", GPSData[id][E_GPS_name]);
            GPSData[id][E_GPS_name][0] = '\0';
            strcat(GPSData[id][E_GPS_name], inputtext2);
            GPSSave(id);
            SendAdminMessage(COLOR_ADMIN,
                "AdmLog: %s เปลี่ยนชื่อ GPS ID:%d '%s' -> '%s'",
                ReturnPlayerName(playerid), id, old, inputtext2);
        }

        new str[128];
        format(str, sizeof str, "ชื่อปัจจุบัน: {FFFF00}%s\n\n{FFFFFF}ป้อนชื่อใหม่",
            GPSData[id][E_GPS_name]);
        Dialog_ShowCallback(playerid, using inline InputName, DIALOG_STYLE_INPUT,
            "{FFFFFF}เปลี่ยนชื่อ", str, "บันทึก", "ย้อนกลับ");
    }
    Dialog_ShowCallback(playerid, using inline InputID, DIALOG_STYLE_INPUT,
        "{FFFFFF}เปลี่ยนชื่อจุด GPS", "ป้อน Local ID", "ถัดไป", "ย้อนกลับ");
    return true;
}

stock GPSAdminDialogChangeCategory(playerid) {
    inline const InputID(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return PanelGPS(playerid);

        new id = -1;
        if (sscanf(inputtext, "d", id) || id < 0 || id >= MAX_GPS || !GPSData[id][E_GPS_exists]) {
            SendErrorMessage(playerid, "{FFFFFF}ID ไม่ถูกต้องหรือไม่มีอยู่ในระบบ");
            @return GPSAdminDialogChangeCategory(playerid);
        }

        new catStr[256] = "";
        for (new c = 0; c < GPS_CAT_MAX; c++) {
            new row[64];
            format(row, sizeof row, "%s%s\n", GPS_CAT_COLOR[c], GPS_CAT_NAME[c]);
            strcat(catStr, row);
        }

        inline const PickCat(pid2, dialogid2, response2, listitem2, string:inputtext2[]) {
            #pragma unused dialogid2, inputtext2, pid2
            if (!response2) @return PanelGPS(playerid);
            if (listitem2 < 0 || listitem2 >= GPS_CAT_MAX) @return true;

            new oldCat = GPSData[id][E_GPS_category];
            GPSData[id][E_GPS_category] = listitem2;
            GPSSave(id);
            SendAdminMessage(COLOR_ADMIN,
                "AdmLog: %s เปลี่ยนหมวด GPS ID:%d '%s' [%s] ? [%s]",
                ReturnPlayerName(playerid), id, GPSData[id][E_GPS_name],
                GPS_CAT_NAME[oldCat], GPS_CAT_NAME[listitem2]);
        }
        Dialog_ShowCallback(playerid, using inline PickCat, DIALOG_STYLE_LIST,
            "{FFFFFF}เลือกหมวดหมู่ใหม่", catStr, "เลือก", "ย้อนกลับ");
    }
    Dialog_ShowCallback(playerid, using inline InputID, DIALOG_STYLE_INPUT,
        "{FFFFFF}เปลี่ยนหมวดหมู่", "ป้อน Local ID", "ถัดไป", "ย้อนกลับ");
    return true;
}

stock GPSAdminDialogMove(playerid) {
    inline const InputID(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return PanelGPS(playerid);

        new id = -1;
        if (sscanf(inputtext, "d", id) || id < 0 || id >= MAX_GPS || !GPSData[id][E_GPS_exists]) {
            SendErrorMessage(playerid, "{FFFFFF}ID ไม่ถูกต้องหรือไม่มีอยู่ในระบบ");
            @return GPSAdminDialogMove(playerid);
        }

        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        GPSData[id][E_GPS_x] = x;
        GPSData[id][E_GPS_y] = y;
        GPSData[id][E_GPS_z] = z;
        GPSSave(id);

        foreach (new i : Player)
            if (GPS_ActiveID[i] == id) GPSStart(i, id);

        SendAdminMessage(COLOR_ADMIN,
            "AdmLog: %s ย้ายจุด GPS ID:%d '%s' -> (%.1f,%.1f,%.1f)",
            ReturnPlayerName(playerid), id, GPSData[id][E_GPS_name], x, y, z);
    }
    Dialog_ShowCallback(playerid, using inline InputID, DIALOG_STYLE_INPUT,
        "{FFFFFF}ย้ายตำแหน่งจุด GPS",
        "ป้อน Local ID\n{AAAAAA}ตำแหน่งปัจจุบันของคุณจะถูกบันทึกเป็นตำแหน่งใหม่",
        "บันทึก", "ย้อนกลับ");
    return true;
}

stock GPSAdminDialogList(playerid) {
    new str[6144] = "";
    new count = 0;

    for (new c = 0; c < GPS_CAT_MAX; c++) {
        for (new i = 0; i < MAX_GPS; i++) {
            if (!GPSData[i][E_GPS_exists]) continue;
            if (GPSData[i][E_GPS_category] != c) continue;

            new row[128];
            format(row, sizeof row,
                "{FFFFFF}%d {AAAAAA}DB:%d %s%s {FFFFFF}%.1f, %.1f, %.1f\n",
                i, GPSData[i][E_GPS_id],
                GPS_CAT_COLOR[c], GPSData[i][E_GPS_name],
                GPSData[i][E_GPS_x], GPSData[i][E_GPS_y], GPSData[i][E_GPS_z]);
            strcat(str, row);
            count++;
        }
    }

    if (!count) return SendErrorMessage(playerid, "{FFFFFF}ยังไม่มีจุด GPS ในระบบ");

    inline const Close(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, inputtext, listitem, response
        @return true;
    }
    Dialog_ShowCallback(playerid, using inline Close, DIALOG_STYLE_LIST,
        "รายการจุด GPS", str, "ปิด", "");
    return true;
}

stock GPSAdminDialogWarpTo(playerid) {
    new str[6144] = "";
    new count = 0;
    new mapping[MAX_GPS];

    for (new i = 0; i < MAX_GPS; i++) {
        if (!GPSData[i][E_GPS_exists]) continue;
        new c = GPSData[i][E_GPS_category];
        new row[128];
        format(row, sizeof row,
            "{FFFFFF}%d %s%s {FFFFFF}%.1f, %.1f, %.1f\n",
            i, GPS_CAT_COLOR[c], GPSData[i][E_GPS_name],
            GPSData[i][E_GPS_x], GPSData[i][E_GPS_y], GPSData[i][E_GPS_z]);
        strcat(str, row);
        mapping[count] = i;
        count++;
    }

    if (!count) {
        SendErrorMessage(playerid, "{FFFFFF}ยังไม่มีจุด GPS ในระบบ");
        return PanelGPS(playerid);
    }

    static s_map[MAX_GPS], s_count;
    s_count = count;
    for (new i = 0; i < count; i++) s_map[i] = mapping[i];

    inline const WarpMenu(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return PanelGPS(playerid);
        if (listitem >= s_count) @return true;

        new gpsid = s_map[listitem];
        SetPlayerPos(playerid,
            GPSData[gpsid][E_GPS_x],
            GPSData[gpsid][E_GPS_y],
            GPSData[gpsid][E_GPS_z]);
        SendCongratMessage(playerid, "{FFFFFF}วาร์ปไปยัง GPS '%s'", GPSData[gpsid][E_GPS_name]);
    }
    Dialog_ShowCallback(playerid, using inline WarpMenu, DIALOG_STYLE_LIST,
        "วาร์ปไปหาจุด GPS", str, "วาร์ป", "ย้อนกลับ");
    return true;
}
