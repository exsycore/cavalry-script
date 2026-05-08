#if defined _inc_impl
    #undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
    mysql_tquery(get_handle(), "SELECT * FROM "ENTRANCE_TABLE"", "EntranceLoad", "");
    return true;
}

public EntranceLoad() {
    new rows;
    cache_get_row_count(rows);

    for (new i = 0; i < rows && i < MAX_ENTRANCE; i++) {
        Player.Entrance[i][@exists] = true;
        cache_get_value_name_int(i,   "entranceid",  Player.Entrance[i][@id]);
        cache_get_value_name_int(i,   "interior",    Player.Entrance[i][@interior]);
        cache_get_value_name_int(i,   "world",       Player.Entrance[i][@world]);
        cache_get_value_name_int(i,   "tointerior",  Player.Entrance[i][@tointerior]);
        cache_get_value_name_int(i,   "toworld",     Player.Entrance[i][@toworld]);

        cache_get_value_name_float(i, "x",           Player.Entrance[i][@x]);
        cache_get_value_name_float(i, "y",           Player.Entrance[i][@y]);
        cache_get_value_name_float(i, "z",           Player.Entrance[i][@z]);
        cache_get_value_name_float(i, "a",           Player.Entrance[i][@a]);

        cache_get_value_name_float(i, "tox",         Player.Entrance[i][@tox]);
        cache_get_value_name_float(i, "toy",         Player.Entrance[i][@toy]);
        cache_get_value_name_float(i, "toz",         Player.Entrance[i][@toz]);
        cache_get_value_name_float(i, "toa",         Player.Entrance[i][@toa]);

        EntranceRefresh(i);
    }
    printf("[SYSTEM][DB] %d Entrance loaded.", rows);
    return true;
}

public OnEntranceCreated(entranceid) {
    if (entranceid == -1 || !Player.Entrance[entranceid][@exists]) return false;
    Player.Entrance[entranceid][@id] = cache_insert_id();
    EntranceSave(entranceid);
    return true;
}

stock EntranceNearest(playerid) {
    for (new i = 0; i < MAX_ENTRANCE; i++) {
        if (Player.Entrance[i][@exists] && IsPlayerInRangeOfPoint(playerid, 1.0, Player.Entrance[i][@x], Player.Entrance[i][@y], Player.Entrance[i][@z])) {
            return i;
        }
    }
    return -1;
}

stock EntranceFindByDBID(dbid) {
    for (new i = 0; i < MAX_ENTRANCE; i++) {
        if (Player.Entrance[i][@exists] && Player.Entrance[i][@id] == dbid)
            return i;
    }
    return -1;
}

stock EntranceRefresh(entranceid) {
    if (entranceid == -1 || !Player.Entrance[entranceid][@exists]) return false;

    if (IsValidDynamicPickup(Player.Entrance[entranceid][@obj]))
        DestroyDynamicPickup(Player.Entrance[entranceid][@obj]);

    Player.Entrance[entranceid][@obj] = CreateDynamicPickup(
        MODEL_ENTRANCE, 23,
        Player.Entrance[entranceid][@x],
        Player.Entrance[entranceid][@y],
        Player.Entrance[entranceid][@z],
        Player.Entrance[entranceid][@world],
        Player.Entrance[entranceid][@interior]
    );
    return true;
}

stock EntranceSave(entranceid) {
    new query[512];
    mysql_format(get_handle(), query, sizeof query,
        "UPDATE "ENTRANCE_TABLE" SET \
        `interior`   = '%d', `world`      = '%d', \
        `tointerior` = '%d', `toworld`    = '%d', \
        `x`  = '%.4f', `y`  = '%.4f', `z`  = '%.4f', `a`  = '%.4f', \
        `tox`= '%.4f', `toy`= '%.4f', `toz`= '%.4f', `toa`= '%.4f' \
        WHERE `entranceid` = '%d'",
        Player.Entrance[entranceid][@interior],
        Player.Entrance[entranceid][@world],
        Player.Entrance[entranceid][@tointerior],
        Player.Entrance[entranceid][@toworld],
        Player.Entrance[entranceid][@x],  Player.Entrance[entranceid][@y],
        Player.Entrance[entranceid][@z],  Player.Entrance[entranceid][@a],
        Player.Entrance[entranceid][@tox], Player.Entrance[entranceid][@toy],
        Player.Entrance[entranceid][@toz], Player.Entrance[entranceid][@toa],
        Player.Entrance[entranceid][@id]
    );
    return mysql_tquery(get_handle(), query);
}

stock EntranceCreate(interior, virtualworld, Float:x, Float:y, Float:z, Float:a) {
    for (new i = 0; i < MAX_ENTRANCE; i++) {
        if (!Player.Entrance[i][@exists]) {
            Player.Entrance[i][@exists]   = true;
            Player.Entrance[i][@interior] = interior;
            Player.Entrance[i][@world]    = virtualworld;
            Player.Entrance[i][@x] = x;   Player.Entrance[i][@y] = y;
            Player.Entrance[i][@z] = z;   Player.Entrance[i][@a] = a;
            // ค่าทางออกยังว่าง รอ SetEntranceExit
            Player.Entrance[i][@tox] = 0.0; Player.Entrance[i][@toy] = 0.0;
            Player.Entrance[i][@toz] = 0.0; Player.Entrance[i][@toa] = 0.0;
            Player.Entrance[i][@tointerior] = 0;
            Player.Entrance[i][@toworld]    = 0;

            mysql_tquery(get_handle(),
                "INSERT INTO "ENTRANCE_TABLE" (`entranceid`) VALUES(0)",
                "OnEntranceCreated", "d", i);
            EntranceRefresh(i);
            return i;
        }
    }
    return -1;
}

stock EntranceDelete(entranceid) {
    if (entranceid == -1 || !Player.Entrance[entranceid][@exists]) return false;

    new string[64];
    if (IsValidDynamicPickup(Player.Entrance[entranceid][@obj]))
        DestroyDynamicPickup(Player.Entrance[entranceid][@obj]);

    mysql_format(get_handle(), string, sizeof string,
        "DELETE FROM "ENTRANCE_TABLE" WHERE `entranceid` = '%d'",
        Player.Entrance[entranceid][@id]);
    mysql_tquery(get_handle(), string);

    Player.Entrance[entranceid][@exists] = false;
    Player.Entrance[entranceid][@id]     = 0;
    return true;
}

stock EntranceWarp(playerid, entranceid) {
    if (entranceid == -1 || !Player.Entrance[entranceid][@exists]) return false;

    if (IsPlayerInRangeOfPoint(playerid, 4.0, Player.Entrance[entranceid][@x], Player.Entrance[entranceid][@y], Player.Entrance[entranceid][@z])) {
        SetPlayerPos(playerid, Player.Entrance[entranceid][@tox], Player.Entrance[entranceid][@toy], Player.Entrance[entranceid][@toz]);
        SetPlayerFacingAngle(playerid, Player.Entrance[entranceid][@toa]);
        SetPlayerInterior(playerid,    Player.Entrance[entranceid][@tointerior]);
        SetPlayerVirtualWorld(playerid,Player.Entrance[entranceid][@toworld]);
        TogglePlayerLoadObject(playerid);
    } else {
        SetPlayerPos(playerid, Player.Entrance[entranceid][@x], Player.Entrance[entranceid][@y], Player.Entrance[entranceid][@z]);
        SetPlayerFacingAngle(playerid, Player.Entrance[entranceid][@a]);
        SetPlayerInterior(playerid,    Player.Entrance[entranceid][@interior]);
        SetPlayerVirtualWorld(playerid,Player.Entrance[entranceid][@world]);
        TogglePlayerLoadObject(playerid);
    }
    return true;
}

YCMD:aentrance(playerid, string:params[], help) {
    if (!GetPlayerLoggedIn(playerid)) return 1;
    if (!IsPlayerAdminEx(playerid)) return SendErrorMessage(playerid, "คุณไม่สามารถใช้คำสั่งนี้ได้ โปรดอย่าใช้มันแอดมินกำลังดูคุณอยู่");

    PanelCreateEntrance(playerid);
    return 1;
}

stock PanelCreateEntrance(playerid) {
    if (!IsPlayerAdminEx(playerid)) return true;

    inline const MainMenu(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return true;

        switch (listitem) {
            case 0: EntranceDialogCreate(playerid);
            case 1: EntranceDialogDelete(playerid);
            case 2: EntranceDialogSetExit(playerid);
            case 3: EntranceDialogMove(playerid, false);   // ย้ายทางเข้า
            case 4: EntranceDialogMove(playerid, true);    // ย้ายทางออก
            case 5: EntranceDialogList(playerid);
            case 6: EntranceDialogWarpTo(playerid);
        }
    }
    Dialog_ShowCallback(playerid, using inline MainMenu, DIALOG_STYLE_LIST,
        "{FFFFFF}AdminPanel (Entrance)",
        "สร้าง Entrance\n\
        ลบ Entrance\n\
        ตั้งค่าทางออก (Exit)\n\
        ย้ายตำแหน่งทางเข้า\n\
        ย้ายตำแหน่งทางออก\n\
        รายการ Entrance ทั้งหมด\n\
        วาร์ปไปหา Entrance",
        "เลือก", "ยกเลิก");
    return true;
}

stock EntranceDialogCreate(playerid) {
    if (GetPlayerInterior(playerid) != 0) {
        SendErrorMessage(playerid, "{FFFFFF}ต้องอยู่ใน Interior 0 เพื่อสร้างทางเข้า");
        return PanelCreateEntrance(playerid);
    }

    inline const Confirm(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, inputtext, pid
        if (!response) @return PanelCreateEntrance(playerid);

        new Float:x, Float:y, Float:z, Float:a;
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, a);

        new id = EntranceCreate(
            GetPlayerInterior(playerid),
            GetPlayerVirtualWorld(playerid),
            x, y, z, a);

        if (id == -1) {
            SendErrorMessage(playerid, "{FFFFFF}ความจุ Entrance เต็มแล้ว (MAX_ENTRANCE)");
            @return true;
        }
        SendAdminMessage(COLOR_ADMIN,
            "AdmLog: %s สร้าง Entrance ID:%d ที่ (%.1f, %.1f, %.1f) A:%.1f",
            ReturnPlayerName(playerid), id, x, y, z, a);
    }
    Dialog_ShowCallback(playerid, using inline Confirm, DIALOG_STYLE_MSGBOX,
        "{FFFFFF}สร้าง Entrance",
        "สร้าง Entrance ณ ตำแหน่งของคุณในขณะนี้?\n\n\
        {AAAAAA}ตำแหน่งทางเข้าจะถูกบันทึกตาม facing angle ที่คุณหันอยู่\n\
        คุณสามารถตั้งทางออกได้ภายหลังผ่านเมนู [ตั้งค่าทางออก]",
        "ยืนยัน", "ยกเลิก");
    return true;
}

stock EntranceDialogDelete(playerid) {
    inline const InputID(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return PanelCreateEntrance(playerid);

        new id = -1;
        if (sscanf(inputtext, "d", id) || id < 0 || id >= MAX_ENTRANCE || !Player.Entrance[id][@exists]) {
            SendErrorMessage(playerid, "{FFFFFF}ID ไม่ถูกต้องหรือไม่มีอยู่ในระบบ");
            @return PanelCreateEntrance(playerid);
        }

        new dbid = Player.Entrance[id][@id];
        EntranceDelete(id);
        SendAdminMessage(COLOR_ADMIN,
            "AdmLog: %s ลบ Entrance LocalID:%d (DB:%d)",
            ReturnPlayerName(playerid), id, dbid);
    }
    Dialog_ShowCallback(playerid, using inline InputID, DIALOG_STYLE_INPUT,
        "{FFFFFF}ลบ Entrance",
        "ป้อน Local ID ของ Entrance ที่ต้องการลบ\n\
        {AAAAAA}(ดู ID ได้จากเมนู รายการ Entrance)",
        "ลบ", "ยกเลิก");
    return true;
}

stock EntranceDialogSetExit(playerid) {
    inline const InputID(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return PanelCreateEntrance(playerid);

        new id = -1;
        if (sscanf(inputtext, "d", id) || id < 0 || id >= MAX_ENTRANCE || !Player.Entrance[id][@exists]) {
            SendErrorMessage(playerid, "{FFFFFF}ID ไม่ถูกต้องหรือไม่มีอยู่ในระบบ");
            @return PanelCreateEntrance(playerid);
        }

        new Float:x, Float:y, Float:z, Float:a;
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, a);

        Player.Entrance[id][@tox] = x;
        Player.Entrance[id][@toy] = y;
        Player.Entrance[id][@toz] = z;
        Player.Entrance[id][@toa] = a;
        Player.Entrance[id][@tointerior] = GetPlayerInterior(playerid);
        Player.Entrance[id][@toworld]    = GetPlayerVirtualWorld(playerid);

        EntranceSave(id);
        SendAdminMessage(COLOR_ADMIN,
            "AdmLog: %s ตั้งทางออก Entrance ID:%d > (%.1f, %.1f, %.1f) A:%.1f INT:%d VW:%d",
            ReturnPlayerName(playerid), id, x, y, z, a,
            Player.Entrance[id][@tointerior], Player.Entrance[id][@toworld]);
    }
    Dialog_ShowCallback(playerid, using inline InputID, DIALOG_STYLE_INPUT,
        "{FFFFFF}ตั้งค่าทางออก (Exit)",
        "ป้อน Local ID ของ Entrance\n\
        {AAAAAA}ตำแหน่งปัจจุบันของคุณจะถูกบันทึกเป็นจุดออก (tox/toy/toz/toa)\n\
        รวมถึง Interior และ VirtualWorld ที่คุณอยู่ในขณะนี้",
        "บันทึก", "ยกเลิก");
    return true;
}

stock EntranceDialogMove(playerid, bool:isExit) {
    new title[64];
    format(title, sizeof title, "{FFFFFF}ย้ายตำแหน่ง%s", isExit ? "ทางออก (Exit)" : "ทางเข้า (Entrance)");

    new body[256];
    format(body, sizeof body,
        "ป้อน Local ID ของ Entrance ที่ต้องการย้าย\n\
        {AAAAAA}ตำแหน่งปัจจุบัน, facing angle, Interior และ VirtualWorld\n\
        ของคุณจะถูกบันทึกเป็นตำแหน่ง%s ใหม่",
        isExit ? "ทางออก" : "ทางเข้า");

    inline const InputID(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return PanelCreateEntrance(playerid);

        new id = -1;
        if (sscanf(inputtext, "d", id) || id < 0 || id >= MAX_ENTRANCE || !Player.Entrance[id][@exists]) {
            SendErrorMessage(playerid, "{FFFFFF}ID ไม่ถูกต้องหรือไม่มีอยู่ในระบบ");
            @return PanelCreateEntrance(playerid);
        }

        new Float:x, Float:y, Float:z, Float:a;
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, a);
        new interior = GetPlayerInterior(playerid);
        new vworld   = GetPlayerVirtualWorld(playerid);

        if (!isExit) {
            Player.Entrance[id][@x]       = x;
            Player.Entrance[id][@y]       = y;
            Player.Entrance[id][@z]       = z;
            Player.Entrance[id][@a]       = a;
            Player.Entrance[id][@interior]= interior;
            Player.Entrance[id][@world]   = vworld;
            EntranceSave(id);
            EntranceRefresh(id);   // รีเฟรช pickup ด้วย
            SendAdminMessage(COLOR_ADMIN,
                "AdmLog: %s ย้ายทางเข้า ID:%d ? (%.1f,%.1f,%.1f) A:%.1f INT:%d VW:%d",
                ReturnPlayerName(playerid), id, x, y, z, a, interior, vworld);
        } else {
            Player.Entrance[id][@tox]       = x;
            Player.Entrance[id][@toy]       = y;
            Player.Entrance[id][@toz]       = z;
            Player.Entrance[id][@toa]       = a;
            Player.Entrance[id][@tointerior]= interior;
            Player.Entrance[id][@toworld]   = vworld;
            EntranceSave(id);
            SendAdminMessage(COLOR_ADMIN,
                "AdmLog: %s ย้ายทางออก ID:%d ? (%.1f,%.1f,%.1f) A:%.1f INT:%d VW:%d",
                ReturnPlayerName(playerid), id, x, y, z, a, interior, vworld);
        }
    }
    Dialog_ShowCallback(playerid, using inline InputID, DIALOG_STYLE_INPUT,
        title, body, "บันทึก", "ยกเลิก");
    return true;
}

stock EntranceDialogWarpTo(playerid) {
    new string[2048] = "";
    new count = 0;
    new mapping[MAX_ENTRANCE];   // mapping[listitem] = local id

    for (new i = 0; i < MAX_ENTRANCE; i++) {
        if (!Player.Entrance[i][@exists]) continue;
        new row[128];
        format(row, sizeof row,
            "{FFFFFF}%d {AAAAAA}DB:%d (%.1f, %.1f, %.1f) A:%.0f INT:%d VW:%d\n",
            i,
            Player.Entrance[i][@id],
            Player.Entrance[i][@x], Player.Entrance[i][@y], Player.Entrance[i][@z],
            Player.Entrance[i][@a],
            Player.Entrance[i][@interior],
            Player.Entrance[i][@world]);
        strcat(string, row);
        mapping[count] = i;
        count++;
    }

    if (!count) {
        SendErrorMessage(playerid, "{FFFFFF}ยังไม่มี Entrance ในระบบ");
        return PanelCreateEntrance(playerid);
    }

    static s_mapping[MAX_ENTRANCE], s_count;
    s_count = count;
    for (new i = 0; i < count; i++) s_mapping[i] = mapping[i];

    inline const WarpMenu(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return PanelCreateEntrance(playerid);
        if (listitem >= s_count) @return true;

        new eid = s_mapping[listitem];
        SetPlayerPos(playerid,
            Player.Entrance[eid][@x],
            Player.Entrance[eid][@y],
            Player.Entrance[eid][@z] + 0.5);
        SetPlayerFacingAngle(playerid, Player.Entrance[eid][@a]);
        SetPlayerInterior(playerid,    Player.Entrance[eid][@interior]);
        SetPlayerVirtualWorld(playerid,Player.Entrance[eid][@world]);

        SendCongratMessage(playerid, "{FFFFFF}วาร์ปไปยัง Entrance ID: %d (DB:%d)", eid, Player.Entrance[eid][@id]);
        EntranceCooldown[playerid] = GetTickCount();
    }
    Dialog_ShowCallback(playerid, using inline WarpMenu, DIALOG_STYLE_LIST, "วาร์ปไปหา Entrance", string, "วาร์ป", "ยกเลิก");
    return true;
}

stock EntranceDialogList(playerid) {
    new string[4096] = "";
    new count = 0;

    for (new i = 0; i < MAX_ENTRANCE; i++) {
        if (!Player.Entrance[i][@exists]) continue;
        new row[256];
        new bool:hasExit = (Player.Entrance[i][@tox] != 0.0 ||
                            Player.Entrance[i][@toy] != 0.0 ||
                            Player.Entrance[i][@toz] != 0.0);
        format(row, sizeof row,
            "{FFFFFF}%d {AAAAAA}DB:%d %.1f,%.1f,%.1f %.1f,%.1f,%.1f %s\n",
            i,
            Player.Entrance[i][@id],
            Player.Entrance[i][@x], Player.Entrance[i][@y], Player.Entrance[i][@z],
            Player.Entrance[i][@tox], Player.Entrance[i][@toy], Player.Entrance[i][@toz],
            hasExit ? "{00FF00}มีทางออก" : "{FF4444}ยังไม่ตั้ง");
        strcat(string, row);
        count++;
    }

    if (!count) return SendErrorMessage(playerid, "{FFFFFF}ยังไม่มี Entrance ในระบบ");

    inline const Close(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, inputtext, listitem, response
        @return true;
    }
    Dialog_ShowCallback(playerid, using inline Close, DIALOG_STYLE_LIST, "รายการ Entrance", string, "ปิด", "");
    return true;
}

hook OnPlayerPickUpDynPickup(playerid, pickupid) {
    for (new i = 0; i < MAX_ENTRANCE; i++) {
        if (!Player.Entrance[i][@exists] || Player.Entrance[i][@obj] != pickupid) continue;

        if (GetTickCount() - EntranceCooldown[playerid] < ENTRANCE_COOLDOWN) return true;
        EntranceCooldown[playerid] = GetTickCount();

        if (Player.Entrance[i][@tox] == 0.0 && Player.Entrance[i][@toy] == 0.0 && Player.Entrance[i][@toz] == 0.0) {
            return true;
        }
        EntranceWarp(playerid, i);
        return true;
    }
    return true;
}
