#if defined _inc_impl
    #undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
    mysql_tquery(get_handle(), "SELECT * FROM "PUMP_TABLE"", "PumpLoad", "");
    return true;
}

public PumpLoad() {
    new rows;
    cache_get_row_count(rows);

    for (new i = 0; i < rows && i < MAX_PUMP; i++) {
        Player.Pump[i][@exists] = true;
        cache_get_value_name_int(i,   "pumpid",      Player.Pump[i][@id]);
        cache_get_value_name_int(i,   "interior",    Player.Pump[i][@interior]);
        cache_get_value_name_int(i,   "world",       Player.Pump[i][@world]);
        cache_get_value_name_float(i, "x",           Player.Pump[i][@x]);
        cache_get_value_name_float(i, "y",           Player.Pump[i][@y]);
        cache_get_value_name_float(i, "z",           Player.Pump[i][@z]);
        PumpRefresh(i);
    }
    printf("[SYSTEM][DB] %d Pump loaded.", rows);
    return true;
}

public OnPumpCreated(pumpid) {
    if (pumpid == -1 || !Player.Pump[pumpid][@exists]) return false;
    Player.Pump[pumpid][@id] = cache_insert_id();
    PumpSave(pumpid);
    return true;
}

stock SetFuelPrice(Float:price) {
    g_FuelPrice = price;
}

stock Float:GetFuelPrice() {
    return g_FuelPrice;
}

stock GetFuelCost(Float:fuelAmount) {
    return floatround(fuelAmount * g_FuelPrice);
}

stock Float:GetFuelByMoney(money) {
    if (g_FuelPrice <= 0.0) return 0.0;
    return floatdiv(float(money), g_FuelPrice);
}

stock PumpNearest(playerid) {
    for (new i = 0; i < MAX_PUMP; i++) {
        if (Player.Pump[i][@exists] && IsPlayerInRangeOfPoint(playerid, 1.0, Player.Pump[i][@x], Player.Pump[i][@y], Player.Pump[i][@z])) {
            return i;
        }
    }
    return -1;
}

stock PumpFindByDBID(dbid) {
    for (new i = 0; i < MAX_PUMP; i++) {
        if (Player.Pump[i][@exists] && Player.Pump[i][@id] == dbid)
            return i;
    }
    return -1;
}

stock PumpRefresh(pumpid) {
    if (pumpid == -1 || !Player.Pump[pumpid][@exists]) return false;

    if (IsValidDynamicPickup(Player.Pump[pumpid][@obj]))
        DestroyDynamicPickup(Player.Pump[pumpid][@obj]);
    
    if (IsValidDynamic3DTextLabel(Player.Pump[pumpid][@text]))
        DestroyDynamic3DTextLabel(Player.Pump[pumpid][@text]);

    Player.Pump[pumpid][@obj] = CreateDynamicPickup(
        MODEL_PUMP, 23,
        Player.Pump[pumpid][@x],
        Player.Pump[pumpid][@y],
        Player.Pump[pumpid][@z],
        Player.Pump[pumpid][@world],
        Player.Pump[pumpid][@interior]
    );

    Player.Pump[pumpid][@text] = CreateDynamic3DTextLabel(
        PUMP_TEXT,
        0xFFFFFFFF,
        Player.Pump[pumpid][@x],
        Player.Pump[pumpid][@y],
        Player.Pump[pumpid][@z],
        8.0,
        .interiorid = Player.Pump[pumpid][@interior],
        .worldid = Player.Pump[pumpid][@world]
    );
    return true;
}

stock PumpSave(pumpid) {
    new query[512];
    mysql_format(get_handle(), query, sizeof query,
        "UPDATE "PUMP_TABLE" SET \
        `interior` = '%d', `world` = '%d', `x` = '%.4f', `y` = '%.4f', `z` = '%.4f' WHERE `pumpid` = '%d'",
        Player.Pump[pumpid][@interior],
        Player.Pump[pumpid][@world],
        Player.Pump[pumpid][@x],
        Player.Pump[pumpid][@y],
        Player.Pump[pumpid][@z],
        Player.Pump[pumpid][@id]
    );
    return mysql_tquery(get_handle(), query);
}

stock PumpCreate(interior, virtualworld, Float:x, Float:y, Float:z) {
    for (new i = 0; i < MAX_PUMP; i++) {
        if (!Player.Pump[i][@exists]) {
            Player.Pump[i][@exists]   = true;
            Player.Pump[i][@interior] = interior;
            Player.Pump[i][@world]    = virtualworld;
            Player.Pump[i][@x] = x;
            Player.Pump[i][@y] = y;
            Player.Pump[i][@z] = z;

            mysql_tquery(get_handle(),
                "INSERT INTO "PUMP_TABLE" (`pumpid`) VALUES(0)",
                "OnPumpCreated", "d", i);
            PumpRefresh(i);
            return i;
        }
    }
    return -1;
}

stock PumpDelete(pumpid) {
    if (pumpid == -1 || !Player.Pump[pumpid][@exists]) return false;

    new string[64];
    if (IsValidDynamicPickup(Player.Pump[pumpid][@obj]))
        DestroyDynamicPickup(Player.Pump[pumpid][@obj]);
    
    if (IsValidDynamic3DTextLabel(Player.Pump[pumpid][@text]))
        DestroyDynamic3DTextLabel(Player.Pump[pumpid][@text]);

    mysql_format(get_handle(), string, sizeof string,
        "DELETE FROM "PUMP_TABLE" WHERE `pumpid` = '%d'",
        Player.Pump[pumpid][@id]);
    mysql_tquery(get_handle(), string);

    Player.Pump[pumpid][@exists] = false;
    Player.Pump[pumpid][@id]     = 0;
    return true;
}

stock PumpWarp(playerid, pumpid) {
    if (pumpid == -1 || !Player.Pump[pumpid][@exists]) return false;

    if (IsPlayerInRangeOfPoint(playerid, 4.0, Player.Pump[pumpid][@x], Player.Pump[pumpid][@y], Player.Pump[pumpid][@z])) {
        SetPlayerPos(playerid, Player.Pump[pumpid][@tox], Player.Pump[pumpid][@toy], Player.Pump[pumpid][@toz]);
        SetPlayerFacingAngle(playerid, Player.Pump[pumpid][@toa]);
        SetPlayerInterior(playerid,    Player.Pump[pumpid][@tointerior]);
        SetPlayerVirtualWorld(playerid,Player.Pump[pumpid][@toworld]);
        TogglePlayerLoadObject(playerid);
    } else {
        SetPlayerPos(playerid, Player.Pump[pumpid][@x], Player.Pump[pumpid][@y], Player.Pump[pumpid][@z]);
        SetPlayerFacingAngle(playerid, Player.Pump[pumpid][@a]);
        SetPlayerInterior(playerid,    Player.Pump[pumpid][@interior]);
        SetPlayerVirtualWorld(playerid,Player.Pump[pumpid][@world]);
        TogglePlayerLoadObject(playerid);
    }
    return true;
}

YCMD:apump(playerid, string:params[], help) {
    if (!GetPlayerLoggedIn(playerid)) return 1;
    if (!IsPlayerAdminEx(playerid)) return 1;

    PanelCreatePump(playerid);
    return 1;
}

stock PanelCreatePump(playerid) {
    if (!IsPlayerAdminEx(playerid)) return true;

    inline const MainMenu(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return true;

        switch (listitem) {
            case 0: PumpDialogCreate(playerid);
            case 1: PumpDialogDelete(playerid);
            case 2: PumpDialogMove(playerid);
            case 3: PumpDialogList(playerid);
            case 4: PumpDialogWarpTo(playerid);
        }
    }
    Dialog_ShowCallback(playerid, using inline MainMenu, DIALOG_STYLE_LIST,
        "{FFFFFF}AdminPanel (Pump)",
        "สร้าง Pump\n\
        ลบ Pump\n\
        ย้ายตำแหน่ง\n\
        รายการ Pump ทั้งหมด\n\
        วาร์ปไปหา Pump",
        "เลือก", "ยกเลิก");
    return true;
}

stock PumpDialogCreate(playerid) {
    if (GetPlayerInterior(playerid) != 0) {
        SendErrorMessage(playerid, "{FFFFFF}ต้องอยู่ใน Interior 0 เพื่อสร้างปั้ม");
        return PanelCreatePump(playerid);
    }

    inline const Confirm(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, inputtext, pid
        if (!response) @return PanelCreatePump(playerid);

        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);

        new id = PumpCreate(
            GetPlayerInterior(playerid),
            GetPlayerVirtualWorld(playerid),
            x, y, z);

        if (id == -1) {
            SendErrorMessage(playerid, "{FFFFFF}ความจุ Pump เต็มแล้ว (MAX_PUMP)");
            @return true;
        }
        SendAdminMessage(COLOR_ADMIN,
            "AdmLog: %s สร้าง Pump ID:%d ที่ (%.1f, %.1f, %.1f)",
            ReturnPlayerName(playerid), id, x, y, z);
    }
    Dialog_ShowCallback(playerid, using inline Confirm, DIALOG_STYLE_MSGBOX,
        "{FFFFFF}สร้าง Pump",
        "สร้าง Pump ณ ตำแหน่งของคุณในขณะนี้?\n\n\
        {AAAAAA}ตำแหน่งทางเข้าจะถูกบันทึกตามตำแหน่งของคุณในขณะนี้",
        "ยืนยัน", "ยกเลิก");
    return true;
}

stock PumpDialogDelete(playerid) {
    inline const InputID(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return PanelCreatePump(playerid);

        new id = -1;
        if (sscanf(inputtext, "d", id) || id < 0 || id >= MAX_PUMP || !Player.Pump[id][@exists]) {
            SendErrorMessage(playerid, "{FFFFFF}ID ไม่ถูกต้องหรือไม่มีอยู่ในระบบ");
            @return PanelCreatePump(playerid);
        }

        new dbid = Player.Pump[id][@id];
        PumpDelete(id);
        SendAdminMessage(COLOR_ADMIN,
            "AdmLog: %s ลบ Pump LocalID:%d (DB:%d)",
            ReturnPlayerName(playerid), id, dbid);
    }
    Dialog_ShowCallback(playerid, using inline InputID, DIALOG_STYLE_INPUT,
        "{FFFFFF}ลบ Pump",
        "ป้อน Local ID ของ Pump ที่ต้องการลบ\n\
        {AAAAAA}(ดู ID ได้จากเมนู รายการ Pump)",
        "ลบ", "ยกเลิก");
    return true;
}

stock PumpDialogMove(playerid) {
    new body[256];
    format(body, sizeof body,
        "ป้อน Local ID ของ Pump ที่ต้องการย้าย\n\
        {AAAAAA}ตำแหน่งปัจจุบัน Interior และ VirtualWorld\n\
        ของคุณจะถูกบันทึกเป็นตำแหน่งปั้มใหม่");

    inline const InputID(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return PanelCreatePump(playerid);

        new id = -1;
        if (sscanf(inputtext, "d", id) || id < 0 || id >= MAX_PUMP || !Player.Pump[id][@exists]) {
            SendErrorMessage(playerid, "{FFFFFF}ID ไม่ถูกต้องหรือไม่มีอยู่ในระบบ");
            @return PanelCreatePump(playerid);
        }

        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        new interior = GetPlayerInterior(playerid);
        new vworld   = GetPlayerVirtualWorld(playerid);

        Player.Pump[id][@x]       = x;
        Player.Pump[id][@y]       = y;
        Player.Pump[id][@z]       = z;
        Player.Pump[id][@interior]= interior;
        Player.Pump[id][@world]   = vworld;
        PumpSave(id);
        PumpRefresh(id);   // รีเฟรช pickup ด้วย
        SendAdminMessage(COLOR_ADMIN,
            "AdmLog: %s ย้ายตำแหน่งปั้ม ID:%d -> (%.1f,%.1f,%.1f) INT:%d VW:%d",
            ReturnPlayerName(playerid), id, x, y, z, interior, vworld);
    }
    Dialog_ShowCallback(playerid, using inline InputID, DIALOG_STYLE_INPUT,
        "{FFFFFF}ย้ายตำแหน่งปั้ม", body, "บันทึก", "ยกเลิก");
    return true;
}

stock PumpDialogWarpTo(playerid) {
    new string[2048] = "";
    new count = 0;
    new mapping[MAX_PUMP];   // mapping[listitem] = local id

    for (new i = 0; i < MAX_PUMP; i++) {
        if (!Player.Pump[i][@exists]) continue;
        new row[128];
        format(row, sizeof row,
            "{FFFFFF}%d {AAAAAA}DB:%d (%.1f, %.1f, %.1f) INT:%d VW:%d\n",
            i,
            Player.Pump[i][@id],
            Player.Pump[i][@x], Player.Pump[i][@y], Player.Pump[i][@z],
            Player.Pump[i][@interior],
            Player.Pump[i][@world]);
        strcat(string, row);
        mapping[count] = i;
        count++;
    }

    if (!count) {
        SendErrorMessage(playerid, "{FFFFFF}ยังไม่มี Pump ในระบบ");
        return PanelCreatePump(playerid);
    }

    static s_mapping[MAX_PUMP], s_count;
    s_count = count;
    for (new i = 0; i < count; i++) s_mapping[i] = mapping[i];

    inline const WarpMenu(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return PanelCreatePump(playerid);
        if (listitem >= s_count) @return true;

        new eid = s_mapping[listitem];
        SetPlayerPos(playerid,
            Player.Pump[eid][@x],
            Player.Pump[eid][@y],
            Player.Pump[eid][@z]);
        SetPlayerInterior(playerid,    Player.Pump[eid][@interior]);
        SetPlayerVirtualWorld(playerid,Player.Pump[eid][@world]);

        SendCongratMessage(playerid, "{FFFFFF}วาร์ปไปยัง Pump ID: %d (DB:%d)", eid, Player.Pump[eid][@id]);
    }
    Dialog_ShowCallback(playerid, using inline WarpMenu, DIALOG_STYLE_LIST, "วาร์ปไปหา Pump", string, "วาร์ป", "ยกเลิก");
    return true;
}

stock PumpDialogList(playerid) {
    new string[4096] = "";
    new count = 0;

    for (new i = 0; i < MAX_PUMP; i++) {
        if (!Player.Pump[i][@exists]) continue;
        new row[256];

        format(row, sizeof row,
            "{FFFFFF}%d {AAAAAA}DB:%d %.1f,%.1f,%.1f\n",
            i,
            Player.Pump[i][@id],
            Player.Pump[i][@x], Player.Pump[i][@y], Player.Pump[i][@z]);
        strcat(string, row);
        count++;
    }

    if (!count) return SendErrorMessage(playerid, "{FFFFFF}ยังไม่มี Pump ในระบบ");

    inline const Close(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, inputtext, listitem, response
        @return true;
    }
    Dialog_ShowCallback(playerid, using inline Close, DIALOG_STYLE_LIST, "รายการ Pump", string, "ปิด", "");
    return true;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if (newkeys & KEY_CROUCH) {
        new id = PumpNearest(playerid);
        if (id == -1) return 1;
        if (!IsPlayerInAnyVehicle(playerid)) return 1;

        new vehicleid = GetPlayerVehicleID(playerid);
        if (!IsVehicleOwner(playerid, vehicleid))
            return SendErrorMessage(playerid, "{FFFFFF}คุณไม่ใช่เจ้าของรถ ไม่สามารถเติมน้ำมันแทนได้");

        new Float:currentFuel = GetVehicleFuelF(vehicleid);
        new Float:missingFuel = 100.0 - currentFuel;

        if (missingFuel <= 0.0)
            return SendErrorMessage(playerid, "{FFFFFF}น้ำมันเต็มแล้ว");

        new totalCost = GetFuelCost(missingFuel);
        new playerMoney = GetPlayerMoneyEx(playerid);

        new Float:canFillFuel;
        new actualCost;

        if (playerMoney < totalCost) {
            canFillFuel = GetFuelByMoney(playerMoney);
            actualCost  = playerMoney;
        } else {
            canFillFuel = missingFuel;
            actualCost  = totalCost;
        }

        if (actualCost <= 0 || canFillFuel <= 0.0)
            return SendErrorMessage(playerid, "{FFFFFF}เงินของคุณไม่เพียงพอสำหรับเติมน้ำมัน");

        new dialogMsg[256];
        format(dialogMsg, sizeof dialogMsg,
            "{FFFFFF}น้ำมันปัจจุบัน: {FFFF00}%.1f%%\n\
            {FFFFFF}เติมน้ำมัน: {00FF00}%.1f ลิตร\n\
            {FFFFFF}ราคาต่อลิตร: {FFFF00}$%.0f\n\
            {FFFFFF}ราคารวม: {FF0000}$%d",
            currentFuel, canFillFuel, g_FuelPrice, actualCost);

        inline PumpAsk(res, list, string:in[]) {
            #pragma unused list, in
            if (!res) @return 1;

            if (!IsPlayerInAnyVehicle(playerid)) return 1;

            new vid = GetPlayerVehicleID(playerid);
            if (!IsVehicleOwner(playerid, vid))
                return SendErrorMessage(playerid, "{FFFFFF}คุณไม่ใช่เจ้าของรถ");

            if (GetPlayerMoneyEx(playerid) < actualCost)
                return SendErrorMessage(playerid, "{FFFFFF}เงินของคุณไม่เพียงพอ");

            AddVehicleFuel(vid, canFillFuel);
            GivePlayerMoneyEx(playerid, -actualCost);

            va_SendClientMessage(playerid, -1,
                "{FFFFFF}เติมน้ำมัน {00FF00}%.1f ลิตร {FFFFFF}ราคา {FF0000}$%d",
                canFillFuel, actualCost);
        }
        Dialog_ShowCallback(playerid, using inline PumpAsk, DIALOG_STYLE_MSGBOX,
            "{FFFFFF}เติมน้ำมัน", dialogMsg, "ยืนยัน", "ยกเลิก");
    }
    return true;
}
