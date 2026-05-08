#if defined _inc_atm_impl
    #undef _inc_atm_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
    mysql_tquery(get_handle(), "SELECT * FROM "ATM_TABLE"", "ATMLoad", "");
    return true;
}

public ATMLoad() {
    new rows;
    cache_get_row_count(rows);

    for (new i = 0; i < rows && i < MAX_ATM; i++) {
        ATMData[i][E_ATM_exists] = true;
        cache_get_value_name_int(i,   "atmid",    ATMData[i][E_ATM_id]);
        cache_get_value_name_int(i,   "interior", ATMData[i][E_ATM_interior]);
        cache_get_value_name_int(i,   "world",    ATMData[i][E_ATM_world]);
        cache_get_value_name_float(i, "x",        ATMData[i][E_ATM_x]);
        cache_get_value_name_float(i, "y",        ATMData[i][E_ATM_y]);
        cache_get_value_name_float(i, "z",        ATMData[i][E_ATM_z]);
        cache_get_value_name_float(i, "rx",       ATMData[i][E_ATM_rx]);
        cache_get_value_name_float(i, "ry",       ATMData[i][E_ATM_ry]);
        cache_get_value_name_float(i, "rz",       ATMData[i][E_ATM_rz]);
        ATMRefresh(i);
    }
    printf("[SYSTEM][DB] %d ATM loaded.", rows);
    return true;
}

public OnATMCreated(atmid) {
    if (atmid == -1 || !ATMData[atmid][E_ATM_exists]) return false;
    ATMData[atmid][E_ATM_id] = cache_insert_id();
    ATMSave(atmid);
    return true;
}

stock ATMSave(atmid) {
    new query[512];
    mysql_format(get_handle(), query, sizeof query,
        "UPDATE "ATM_TABLE" SET \
        `interior`='%d', `world`='%d', \
        `x`='%.4f', `y`='%.4f', `z`='%.4f', \
        `rx`='%.4f', `ry`='%.4f', `rz`='%.4f' \
        WHERE `atmid`='%d'",
        ATMData[atmid][E_ATM_interior],
        ATMData[atmid][E_ATM_world],
        ATMData[atmid][E_ATM_x],  ATMData[atmid][E_ATM_y],  ATMData[atmid][E_ATM_z],
        ATMData[atmid][E_ATM_rx], ATMData[atmid][E_ATM_ry], ATMData[atmid][E_ATM_rz],
        ATMData[atmid][E_ATM_id]);
    return mysql_tquery(get_handle(), query);
}

stock ATMCreate(interior, virtualworld, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
    for (new i = 0; i < MAX_ATM; i++) {
        if (!ATMData[i][E_ATM_exists]) {
            ATMData[i][E_ATM_exists]   = true;
            ATMData[i][E_ATM_interior] = interior;
            ATMData[i][E_ATM_world]    = virtualworld;
            ATMData[i][E_ATM_x]  = x;   ATMData[i][E_ATM_y]  = y;   ATMData[i][E_ATM_z]  = z;
            ATMData[i][E_ATM_rx] = rx;  ATMData[i][E_ATM_ry] = ry;  ATMData[i][E_ATM_rz] = rz;

            mysql_tquery(get_handle(),
                "INSERT INTO "ATM_TABLE" (`atmid`) VALUES(0)",
                "OnATMCreated", "d", i);
            ATMRefresh(i);
            return i;
        }
    }
    return -1;
}

stock ATMDelete(atmid) {
    if (atmid == -1 || !ATMData[atmid][E_ATM_exists]) return false;

    if (IsValidDynamicObject(ATMData[atmid][E_ATM_obj]))
        DestroyDynamicObject(ATMData[atmid][E_ATM_obj]);

    if (IsValidDynamic3DTextLabel(ATMData[atmid][E_ATM_label]))
        DestroyDynamic3DTextLabel(ATMData[atmid][E_ATM_label]);

    new query[64];
    mysql_format(get_handle(), query, sizeof query,
        "DELETE FROM "ATM_TABLE" WHERE `atmid`='%d'", ATMData[atmid][E_ATM_id]);
    mysql_tquery(get_handle(), query);

    ATMData[atmid][E_ATM_exists] = false;
    ATMData[atmid][E_ATM_id]     = 0;
    return true;
}

stock ATMRefresh(atmid) {
    if (atmid == -1 || !ATMData[atmid][E_ATM_exists]) return false;

    if (IsValidDynamicObject(ATMData[atmid][E_ATM_obj]))
        DestroyDynamicObject(ATMData[atmid][E_ATM_obj]);

    if (IsValidDynamic3DTextLabel(ATMData[atmid][E_ATM_label]))
        DestroyDynamic3DTextLabel(ATMData[atmid][E_ATM_label]);

    ATMData[atmid][E_ATM_obj] = CreateDynamicObject(
        MODEL_ATM,
        ATMData[atmid][E_ATM_x],  ATMData[atmid][E_ATM_y],  ATMData[atmid][E_ATM_z],
        ATMData[atmid][E_ATM_rx], ATMData[atmid][E_ATM_ry], ATMData[atmid][E_ATM_rz],
        ATMData[atmid][E_ATM_world],
        ATMData[atmid][E_ATM_interior]
    );

    ATMData[atmid][E_ATM_label] = CreateDynamic3DTextLabel(
        ATM_TEXT,
        ATM_LABEL_COLOR,
        ATMData[atmid][E_ATM_x],
        ATMData[atmid][E_ATM_y],
        ATMData[atmid][E_ATM_z] + 1.2,
        ATM_USE_RANGE * 3.0,
        .worldid  = ATMData[atmid][E_ATM_world],
        .interiorid = ATMData[atmid][E_ATM_interior]
    );
    return true;
}

stock ATMNearest(playerid) {
    for (new i = 0; i < MAX_ATM; i++) {
        if (ATMData[i][E_ATM_exists] && 
            GetPlayerInterior(playerid) == ATMData[i][E_ATM_interior] &&
            GetPlayerVirtualWorld(playerid) == ATMData[i][E_ATM_world] &&
            IsPlayerInRangeOfPoint(playerid, ATM_USE_RANGE,
            ATMData[i][E_ATM_x], ATMData[i][E_ATM_y], ATMData[i][E_ATM_z]))
        {
            return i;
        }
    }
    return -1;
}

hook OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys) {
    if (newkeys & KEY_NO) {
        new atmid = ATMNearest(playerid);
        if (atmid == -1) return true;
        ATMDialogUse(playerid);
    }
    return true;
}

stock ATMDialogUse(playerid) {
    new str[512];

    inline const Menu(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return true;

        switch (listitem) {
            case 0: ATMDialogUse(playerid); // refresh
            case 1: ATMDialogDeposit(playerid);
            case 2: ATMDialogWithdraw(playerid);
            case 3: ATMDialogTransfer(playerid);
        }
    }

    format(str, sizeof str, "{AAAAAA}ยอดเงินธนาคาร: {00DD00}$%d\n{FFFFFF}ฝากเงิน\n{FF4444}ถอนเงิน\n{FFFFFF}โอนเงิน", playerData[playerid][pBank]);
    Dialog_ShowCallback(playerid, using inline Menu, DIALOG_STYLE_LIST, "{FFFFFF}ตู้ ATM", str, "เลือก", "ยกเลิก");
    return true;
}

stock ATMDialogDeposit(playerid) {
    inline const Input(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return ATMDialogUse(playerid);

        new amount = 0;
        if (sscanf(inputtext, "d", amount) || amount <= 0) {
            SendErrorMessage(playerid, "{FFFFFF}กรุณาป้อนจำนวนเงินที่ถูกต้อง");
            @return ATMDialogDeposit(playerid);
        }

        if (playerData[playerid][pMoney] < amount) {
            SendErrorMessage(playerid, "{FFFFFF}เงินสดไม่เพียงพอ");
            @return ATMDialogDeposit(playerid);
        }

        GivePlayerMoneyEx(playerid, -amount);
        playerData[playerid][pBank] += amount;

        // บันทึกลง DB
        SavePlayerBank(playerid);
        ApplyAnimation(playerid, "DEALER", "shop_pay", 4.1, 0, 1, 1, 0, 0, 1);
        SendCongratMessage(playerid, "{FFFFFF}คุณฝากเงิน {00DD00}$%d{FFFFFF} | ยอดธนาคาร: {00DD00}$%d{FFFFFF} | เงินสด: {00DD00}$%d", amount, playerData[playerid][pBank], playerData[playerid][pMoney]);
        @return ATMDialogUse(playerid);
    }

    new str[128];
    format(str, sizeof str, "{FFFFFF}เงินสดในมือ: {FFFF00}$%d\n\n{FFFFFF}ป้อนจำนวนเงินที่ต้องการฝาก", playerData[playerid][pMoney]);
    Dialog_ShowCallback(playerid, using inline Input, DIALOG_STYLE_INPUT, "{FFFFFF}ฝากเงิน", str, "ฝาก", "ย้อนกลับ");
    return true;
}

stock ATMDialogWithdraw(playerid) {
    inline const Input(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return ATMDialogUse(playerid);

        new amount = 0;
        if (sscanf(inputtext, "d", amount) || amount <= 0) {
            SendErrorMessage(playerid, "{FFFFFF}กรุณาป้อนจำนวนเงินที่ถูกต้อง");
            @return ATMDialogWithdraw(playerid);
        }

        if (playerData[playerid][pBank] < amount) {
            SendErrorMessage(playerid, "{FFFFFF}ยอดเงินในธนาคารไม่เพียงพอ");
            @return ATMDialogWithdraw(playerid);
        }

        playerData[playerid][pBank] -= amount;
        GivePlayerMoneyEx(playerid, amount);

        SavePlayerBank(playerid);
        ApplyAnimation(playerid, "DEALER", "shop_pay", 4.1, 0, 1, 1, 0, 0, 1);
        SendCongratMessage(playerid, "{FFFFFF}คุณฝากเงิน {FF4444}$%d{FFFFFF} | ยอดธนาคาร: {FF4444}$%d{FFFFFF} | เงินสด: {FF4444}$%d", amount, playerData[playerid][pBank], playerData[playerid][pMoney]);
        @return ATMDialogUse(playerid);
    }

    new str[128];
    format(str, sizeof str, "{FFFFFF}ยอดเงินธนาคาร: {00DD00}$%d\n\n{FFFFFF}ป้อนจำนวนเงินที่ต้องการถอน", playerData[playerid][pBank]);
    Dialog_ShowCallback(playerid, using inline Input, DIALOG_STYLE_INPUT, "{FFFFFF}ถอนเงิน", str, "ถอน", "ย้อนกลับ");
    return true;
}

stock ATMDialogTransfer(playerid) {
    inline const ChooseMethod(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return ATMDialogUse(playerid);

        switch (listitem) {
            case 0: ATMDialogTransferList(playerid);
            case 1: ATMDialogTransferByID(playerid);
        }
    }
    Dialog_ShowCallback(playerid, using inline ChooseMethod, DIALOG_STYLE_LIST,
        "{FFFFFF}โอนเงิน — เลือกวิธี",
        "{FFFFFF}เลือกจากรายการผู้เล่น Online\n{FFFFFF}พิมพ์ Player ID",
        "เลือก", "ย้อนกลับ");
    return true;
}

stock ATMDialogTransferList(playerid) {
    new str[2048] = "";
    new count = 0;
    new mapping[MAX_PLAYERS];

    foreach (new i : Player) {
        if (i == playerid) continue;
        if (!GetPlayerLoggedIn(i)) continue;

        new row[64];
        format(row, sizeof row, "[%d] %s\n", i, ReturnPlayerName(i));
        strcat(str, row);
        mapping[count] = i;
        count++;
    }

    if (!count) {
        SendErrorMessage(playerid, "ไม่มีผู้เล่นออนไลน์คนอื่น");
        return ATMDialogTransfer(playerid);
    }

    static s_map[MAX_PLAYERS], s_count;
    s_count = count;
    for (new i = 0; i < count; i++) s_map[i] = mapping[i];

    inline const PickPlayer(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return ATMDialogTransfer(playerid);
        if (listitem >= s_count) @return true;

        new targetid = s_map[listitem];
        if (!IsPlayerConnected(targetid) || !GetPlayerLoggedIn(targetid)) {
            SendErrorMessage(playerid, "{FFFFFF}ผู้เล่นคนนั้นออฟไลน์แล้ว");
            @return ATMDialogTransferList(playerid);
        }
        ATMDialogTransferAmount(playerid, targetid);
    }
    Dialog_ShowCallback(playerid, using inline PickPlayer, DIALOG_STYLE_LIST, "{FFFFFF}เลือกผู้รับโอน", str, "เลือก", "ย้อนกลับ");
    return true;
}

stock ATMDialogTransferByID(playerid) {
    inline const InputID(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return ATMDialogTransfer(playerid);

        new targetid = -1;
        if (sscanf(inputtext, "d", targetid)) {
            SendErrorMessage(playerid, "กรุณาป้อนเป็นตัวเลข ID เท่านั้น");
            @return ATMDialogTransferByID(playerid);
        }

        if (targetid == playerid) {
            SendErrorMessage(playerid, "ไม่สามารถโอนเงินให้ตัวเองได้");
            @return ATMDialogTransferByID(playerid);
        }

        if (!IsPlayerConnected(targetid) || !GetPlayerLoggedIn(targetid)) {
            SendErrorMessage(playerid, "ไม่พบผู้เล่น ID นี้ หรือยังไม่ได้ล็อกอิน");
            @return ATMDialogTransferByID(playerid);
        }

        ATMDialogTransferAmount(playerid, targetid);
    }
    Dialog_ShowCallback(playerid, using inline InputID, DIALOG_STYLE_INPUT,
        "{FFFFFF}โอนเงิน — พิมพ์ Player ID",
        "ป้อน Player ID ของผู้ที่ต้องการโอนเงินให้",
        "ยืนยัน", "ย้อนกลับ");
    return true;
}

stock ATMDialogTransferAmount(playerid, targetid) {
    inline const InputAmount(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return ATMDialogTransfer(playerid);

        new amount = 0;
        if (sscanf(inputtext, "d", amount) || amount <= 0) {
            SendErrorMessage(playerid, "กรุณาป้อนจำนวนเงินที่ถูกต้อง");
            @return ATMDialogTransferAmount(playerid, targetid);
        }

        if (playerData[playerid][pBank] < amount) {
            SendErrorMessage(playerid, "ยอดเงินในธนาคารไม่เพียงพอ");
            @return ATMDialogTransferAmount(playerid, targetid);
        }

        if (!IsPlayerConnected(targetid) || !GetPlayerLoggedIn(targetid)) {
            SendErrorMessage(playerid, "ผู้เล่นคนนั้นออฟไลน์แล้ว");
            @return ATMDialogTransfer(playerid);
        }

        playerData[playerid][pBank] -= amount;
        playerData[targetid][pBank] += amount;

        SavePlayerBank(playerid);
        SavePlayerBank(targetid);

        ApplyAnimation(playerid, "DEALER", "shop_pay", 4.1, 0, 1, 1, 0, 0, 1);
        SendCongratMessage(playerid, "{FFFFFF}โอนเงิน {00DD00}$%d{FFFFFF} ให้ %s (ID:%d) | ยอดคงเหลือ: {00DD00}$%d", amount, ReturnPlayerRPName(targetid), targetid, playerData[playerid][pBank]);
        SendCongratMessage(targetid, "{FFFFFF}ได้รับโอนเงิน {00DD00}$%d{FFFFFF} จาก %s (ID:%d) | ยอดคงเหลือ: {00DD00}$%d", amount, ReturnPlayerRPName(playerid), playerid, playerData[targetid][pBank]);
        @return ATMDialogUse(playerid);
    }

    new str[128];
    format(str, sizeof str, "{FFFFFF}โอนให้: {FFFF00}%s {AAAAAA}(ID:%d)\n{AAAAAA}ยอดธนาคารของคุณ: {00DD00}$%d\n\n{FFFFFF}ป้อนจำนวนเงินที่ต้องการโอน", ReturnPlayerRPName(targetid), targetid, playerData[playerid][pBank]);
    Dialog_ShowCallback(playerid, using inline InputAmount, DIALOG_STYLE_INPUT, "{FFFFFF}โอนเงิน", str, "โอน", "ย้อนกลับ");
    return true;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT:objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
    new atmid = ATM_EditingID[playerid];
    if (atmid == -1) return true;

    if (response == EDIT_RESPONSE_CANCEL) {
        ATMRefresh(atmid);
        ATM_EditingID[playerid] = -1;
        SendWarningMessage(playerid, "{FFFFFF}ยกเลิกการย้ายตำแหน่ง");
        return true;
    }

    if (response == EDIT_RESPONSE_FINAL) {
        ATMData[atmid][E_ATM_x]  = x;   ATMData[atmid][E_ATM_y]  = y;   ATMData[atmid][E_ATM_z]  = z;
        ATMData[atmid][E_ATM_rx] = rx;  ATMData[atmid][E_ATM_ry] = ry;  ATMData[atmid][E_ATM_rz] = rz;
        ATMSave(atmid);
        ATMRefresh(atmid); // รีเฟรช label ให้ตามตำแหน่งใหม่
        ATM_EditingID[playerid] = -1;

        SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ย้าย ATM ID:%d -> (%.1f,%.1f,%.1f) RX:%.1f RY:%.1f RZ:%.1f", ReturnPlayerName(playerid), atmid, x, y, z, rx, ry, rz);
    }
    return true;
}

stock PanelATM(playerid) {
    if (!IsPlayerAdminEx(playerid)) return true;

    inline const MainMenu(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return true;

        switch (listitem) {
            case 0: ATMDialogCreate(playerid);
            case 1: ATMDialogDelete(playerid);
            case 2: ATMDialogEdit(playerid);
            case 3: ATMDialogList(playerid);
            case 4: ATMDialogWarpTo(playerid);
        }
    }
    Dialog_ShowCallback(playerid, using inline MainMenu, DIALOG_STYLE_LIST,
        "{FFFFFF}AdminPanel (ATM)",
        "สร้าง ATM\n\
        ลบ ATM\n\
        ย้าย/หมุน ATM (Edit Mode)\n\
        รายการ ATM ทั้งหมด\n\
        วาร์ปไปหา ATM",
        "เลือก", "ยกเลิก");
    return true;
}

YCMD:aatm(playerid, string:params[], help) {
    if (!GetPlayerLoggedIn(playerid)) return 1;
    if (!IsPlayerAdminEx(playerid)) return SendErrorMessage(playerid, "คุณไม่สามารถใช้คำสั่งนี้ได้ โปรดอย่าใช้มันแอดมินกำลังดูคุณอยู่");

    PanelATM(playerid);
    return 1;
}

stock ATMDialogCreate(playerid) {
    inline const Confirm(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, inputtext, pid
        if (!response) @return PanelATM(playerid);

        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);

        new id = ATMCreate(
            GetPlayerInterior(playerid),
            GetPlayerVirtualWorld(playerid),
            x, y, z, 0.0, 0.0, 0.0);

        if (id == -1) {
            SendErrorMessage(playerid, "{FFFFFF}ความจุ ATM เต็มแล้ว (MAX_ATM)");
            @return true;
        }
        SendAdminMessage(COLOR_ADMIN, "AdmLog: %s สร้าง ATM ID:%d ที่ (%.1f,%.1f,%.1f)", ReturnPlayerName(playerid), id, x, y, z);
        SendCongratMessage(playerid, "{FFFFFF}ATM สร้างแล้ว ID:%d — ใช้เมนู [ย้าย/หมุน] เพื่อจัดตำแหน่ง", id);
    }
    Dialog_ShowCallback(playerid, using inline Confirm, DIALOG_STYLE_MSGBOX,
        "{FFFFFF}สร้าง ATM",
        "สร้าง ATM ณ ตำแหน่งของคุณ?\n\n\
        {AAAAAA}Object จะถูกวางที่พิกัดปัจจุบัน\n\
        จากนั้นใช้ [ย้าย/หมุน ATM] เพื่อปรับตำแหน่งด้วย Edit Mode",
        "ยืนยัน", "ยกเลิก");
    return true;
}

stock ATMDialogDelete(playerid) {
    inline const InputID(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return PanelATM(playerid);

        new id = -1;
        if (sscanf(inputtext, "d", id) || id < 0 || id >= MAX_ATM || !ATMData[id][E_ATM_exists]) {
            SendErrorMessage(playerid, "{FFFFFF}ID ไม่ถูกต้องหรือไม่มีอยู่ในระบบ");
            @return PanelATM(playerid);
        }
        new dbid = ATMData[id][E_ATM_id];
        ATMDelete(id);
        SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ลบ ATM LocalID:%d (DB:%d)", ReturnPlayerName(playerid), id, dbid);
    }
    Dialog_ShowCallback(playerid, using inline InputID, DIALOG_STYLE_INPUT,
        "{FFFFFF}ลบ ATM",
        "ป้อน Local ID ของ ATM ที่ต้องการลบ\n{AAAAAA}(ดู ID ได้จากเมนู รายการ ATM)",
        "ลบ", "ยกเลิก");
    return true;
}

stock ATMDialogEdit(playerid) {
    new string[4096] = "";
    new count = 0;
    new mapping[MAX_ATM];

    for (new i = 0; i < MAX_ATM; i++) {
        if (!ATMData[i][E_ATM_exists]) continue;
        new row[128];
        format(row, sizeof row,
            "{FFFFFF}%d {AAAAAA}DB:%d (%.1f, %.1f, %.1f)\n",
            i, ATMData[i][E_ATM_id],
            ATMData[i][E_ATM_x], ATMData[i][E_ATM_y], ATMData[i][E_ATM_z]);
        strcat(string, row);
        mapping[count] = i;
        count++;
    }

    if (!count) {
        SendErrorMessage(playerid, "{FFFFFF}ยังไม่มี ATM ในระบบ");
        return PanelATM(playerid);
    }

    static s_map[MAX_ATM], s_count;
    s_count = count;
    for (new i = 0; i < count; i++) s_map[i] = mapping[i];

    inline const Pick(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return PanelATM(playerid);
        if (listitem >= s_count) @return true;

        new atmid = s_map[listitem];
        ATM_EditingID[playerid] = atmid;

        SetPlayerPos(playerid,
            ATMData[atmid][E_ATM_x],
            ATMData[atmid][E_ATM_y],
            ATMData[atmid][E_ATM_z]);
        SetPlayerInterior(playerid,     ATMData[atmid][E_ATM_interior]);
        SetPlayerVirtualWorld(playerid, ATMData[atmid][E_ATM_world]);

        EditDynamicObject(playerid, ATMData[atmid][E_ATM_obj]);
        SendWarningMessage(playerid, "{FFFFFF}Edit Mode — ลาก/หมุน object แล้วกด Enter เพื่อบันทึก, ESC เพื่อยกเลิก");
    }
    Dialog_ShowCallback(playerid, using inline Pick, DIALOG_STYLE_LIST, "เลือก ATM ที่ต้องการย้าย/หมุน", string, "Edit", "ยกเลิก");
    return true;
}

stock ATMDialogList(playerid) {
    new string[4096] = "";
    new count = 0;

    for (new i = 0; i < MAX_ATM; i++) {
        if (!ATMData[i][E_ATM_exists]) continue;
        new row[256];
        format(row, sizeof row,
            "{FFFFFF}%d {AAAAAA}DB:%d %.1f,%.1f,%.1f RX:%.0f RY:%.0f RZ:%.0f INT:%d VW:%d\n",
            i, ATMData[i][E_ATM_id],
            ATMData[i][E_ATM_x], ATMData[i][E_ATM_y], ATMData[i][E_ATM_z],
            ATMData[i][E_ATM_rx], ATMData[i][E_ATM_ry], ATMData[i][E_ATM_rz],
            ATMData[i][E_ATM_interior], ATMData[i][E_ATM_world]);
        strcat(string, row);
        count++;
    }

    if (!count) return SendErrorMessage(playerid, "{FFFFFF}ยังไม่มี ATM ในระบบ");

    inline const Close(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, inputtext, listitem, response
        @return true;
    }
    Dialog_ShowCallback(playerid, using inline Close, DIALOG_STYLE_LIST,
        "รายการ ATM", string, "ปิด", "");
    return true;
}

stock ATMDialogWarpTo(playerid) {
    new string[4096] = "";
    new count = 0;
    new mapping[MAX_ATM];

    for (new i = 0; i < MAX_ATM; i++) {
        if (!ATMData[i][E_ATM_exists]) continue;
        new row[128];
        format(row, sizeof row,
            "{FFFFFF}%d {AAAAAA}DB:%d (%.1f, %.1f, %.1f) INT:%d VW:%d\n",
            i, ATMData[i][E_ATM_id],
            ATMData[i][E_ATM_x], ATMData[i][E_ATM_y], ATMData[i][E_ATM_z],
            ATMData[i][E_ATM_interior], ATMData[i][E_ATM_world]);
        strcat(string, row);
        mapping[count] = i;
        count++;
    }

    if (!count) {
        SendErrorMessage(playerid, "{FFFFFF}ยังไม่มี ATM ในระบบ");
        return PanelATM(playerid);
    }

    static s_map[MAX_ATM], s_count;
    s_count = count;
    for (new i = 0; i < count; i++) s_map[i] = mapping[i];

    inline const WarpMenu(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return PanelATM(playerid);
        if (listitem >= s_count) @return true;

        new atmid = s_map[listitem];
        SetPlayerPos(playerid,
            ATMData[atmid][E_ATM_x],
            ATMData[atmid][E_ATM_y],
            ATMData[atmid][E_ATM_z]);
        SetPlayerInterior(playerid,     ATMData[atmid][E_ATM_interior]);
        SetPlayerVirtualWorld(playerid, ATMData[atmid][E_ATM_world]);
        SendCongratMessage(playerid, "{FFFFFF}วาร์ปไปยัง ATM ID:%d (DB:%d)", atmid, ATMData[atmid][E_ATM_id]);
    }
    Dialog_ShowCallback(playerid, using inline WarpMenu, DIALOG_STYLE_LIST,
        "วาร์ปไปหา ATM", string, "วาร์ป", "ยกเลิก");
    return true;
}
