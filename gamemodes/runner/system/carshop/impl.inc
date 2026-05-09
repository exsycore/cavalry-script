#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
    mysql_tquery(get_handle(), "SELECT * FROM `"DEALERSHIP_TABLE"`", "LoadDealerships", "");
    return 1;
}

public LoadDealerships() {
    new rows;
    cache_get_row_count(rows);

    for (new i = 0; i < rows && i < MAX_DEALERSHIPS; i++) {
        DealershipData[i][ds_exists] = true;
        cache_get_value_name_int  (i, "id",       DealershipData[i][ds_id]);
        cache_get_value_name      (i, "name",     DealershipData[i][ds_name]);
        cache_get_value_name_float(i, "posx",     DealershipData[i][ds_posx]);
        cache_get_value_name_float(i, "posy",     DealershipData[i][ds_posy]);
        cache_get_value_name_float(i, "posz",     DealershipData[i][ds_posz]);
        cache_get_value_name_float(i, "posa",     DealershipData[i][ds_posa]);
        cache_get_value_name_int  (i, "interior", DealershipData[i][ds_interior]);
        cache_get_value_name_int  (i, "world",    DealershipData[i][ds_world]);

        DealershipCreateObjects(i);
    }

    printf("[SYSTEM][DB] %d Dealership(s) loaded.", rows);
    mysql_tquery(get_handle(), "SELECT * FROM `"DEALERSHIP_STOCK_TABLE"`", "LoadDealershipStock", "");
    return 1;
}

public LoadDealershipStock() {
    new rows;
    cache_get_row_count(rows);

    for (new i = 0; i < rows; i++) {
        new shopid, slot = -1;
        cache_get_value_name_int(i, "shopid", shopid);

        new dsIdx = DealershipGetIndex(shopid);
        if (dsIdx == -1) continue;

        for (new s = 0; s < MAX_DEALERSHIP_STOCK; s++) {
            if (!DealershipStock[dsIdx][s][dss_exists]) { slot = s; break; }
        }
        if (slot == -1) continue;

        DealershipStock[dsIdx][slot][dss_exists] = true;
        cache_get_value_name_int(i, "id",      DealershipStock[dsIdx][slot][dss_id]);
        cache_get_value_name_int(i, "shopid",  DealershipStock[dsIdx][slot][dss_shopid]);
        cache_get_value_name_int(i, "modelid", DealershipStock[dsIdx][slot][dss_modelid]);
        cache_get_value_name_int(i, "color1",  DealershipStock[dsIdx][slot][dss_color1]);
        cache_get_value_name_int(i, "color2",  DealershipStock[dsIdx][slot][dss_color2]);
        cache_get_value_name_int(i, "price",   DealershipStock[dsIdx][slot][dss_price]);
        cache_get_value_name_int(i, "stock",   DealershipStock[dsIdx][slot][dss_stock]);
        cache_get_value_name    (i, "name",    DealershipStock[dsIdx][slot][dss_name]);

        DealershipData[dsIdx][ds_stockCount]++;
    }

    printf("[SYSTEM][DB] %d Dealership stock loaded.", rows);
    return 1;
}

stock DealershipNearest(playerid) {
    for (new i = 0; i < MAX_DEALERSHIPS; i++) {
        if (DealershipData[i][ds_exists] && IsPlayerInRangeOfPoint(playerid, 1.0, DealershipData[i][ds_posx], DealershipData[i][ds_posy], DealershipData[i][ds_posz])) {
            return i;
        }
    }
    return -1;
}

stock DealershipCreateObjects(idx) {
    if (!DealershipData[idx][ds_exists]) return 0;

    if (IsValidDynamicPickup(DealershipData[idx][ds_pickup]))
        DestroyDynamicPickup(DealershipData[idx][ds_pickup]);
    if (IsValidDynamic3DTextLabel(DealershipData[idx][ds_label]))
        DestroyDynamic3DTextLabel(DealershipData[idx][ds_label]);

    new Float:x = DealershipData[idx][ds_posx];
    new Float:y = DealershipData[idx][ds_posy];
    new Float:z = DealershipData[idx][ds_posz];
    new inter   = DealershipData[idx][ds_interior];
    new world   = DealershipData[idx][ds_world];

    DealershipData[idx][ds_pickup] = CreateDynamicPickup(
        1239, 23, x, y, z, world, inter
    );

    new labelStr[128];
    format(labelStr, sizeof labelStr,
        "{FFD700}%s\n{FFFFFF}กด {FFFF00}N {FFFFFF}เพื่อเข้าชมรถ",
        DealershipData[idx][ds_name]
    );
    DealershipData[idx][ds_label] = CreateDynamic3DTextLabel(
        labelStr, 0xFFD700FF, x, y, z, 8.0,
        .interiorid = inter, .worldid = world
    );
    return 1;
}

stock DealershipDestroyObjects(idx) {
    if (IsValidDynamicPickup(DealershipData[idx][ds_pickup]))
        DestroyDynamicPickup(DealershipData[idx][ds_pickup]);
    if (IsValidDynamic3DTextLabel(DealershipData[idx][ds_label]))
        DestroyDynamic3DTextLabel(DealershipData[idx][ds_label]);
    // DealershipData[idx][ds_pickup] = INVALID_PICKUP_ID;
    DealershipData[idx][ds_label]  = INVALID_3DTEXT_ID;
    return 1;
}

hook OnPlayerConnect(playerid) {
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if (!GetPlayerLoggedIn(playerid)) return 1;

    if (newkeys & PRESS_N) {
        new id = DealershipNearest(playerid);
        if (id == -1) return 1;
        OpenDealershipMenu(playerid, id);
    }
    return 1;
}

stock OpenDealershipMenu(playerid, idx) {
    if (!DealershipData[idx][ds_exists]) return 0;

    PlayerDealershipID[playerid]   = idx;
    PlayerDealershipPage[playerid] = 0;

    DealershipShowPage(playerid, idx, 0);
    return 1;
}

stock DealershipShowPage(playerid, idx, page) {
    #pragma unused page
    new body[1024] = "{FFFFFF}รุ่นรถ\t{FFFFFF}จำนวนที่มีในร้าน\t{FFFFFF}ราคา\n";
    new line[128];
    new count = 0;

    for (new s = 0; s < MAX_DEALERSHIP_STOCK; s++) {
        if (!DealershipStock[idx][s][dss_exists]) continue;

        new price = DealershipStock[idx][s][dss_price];
        new vstock = DealershipStock[idx][s][dss_stock];
        new modelName[64];
        strmid(modelName, DealershipStock[idx][s][dss_name], 0, sizeof modelName);

        format(line, sizeof line,
            "{FFFFFF}%s\t{FFFFFF}%d\t{AAFFAA}$%d\n",
            modelName, vstock, price
        );
        strcat(body, line, sizeof body);
        count++;
    }

    if (!count) {
        strcat(body, "{AAAAAA}ยังไม่มีรถในร้านนี้\t-\t-\n", sizeof body);
    }

    new title[128];
    format(title, sizeof title, "{FFD700}%s {FFFFFF}— เลือกรถ", DealershipData[idx][ds_name]);

    inline BuyMenu(res, list, string:input[]) {
        #pragma unused input
        if (!res) {
            PlayerDealershipID[playerid] = -1;
            @return 1;
        }

        new slot = DealershipGetSlotByList(idx, list);
        if (slot == -1) @return 1;

        DealershipConfirmBuy(playerid, idx, slot);
    }
    Dialog_ShowCallback(playerid, using inline BuyMenu,
        DIALOG_STYLE_TABLIST_HEADERS, title, body,
        "{FFFFFF}ซื้อ", "{FFFFFF}ปิด");
    return 1;
}

stock DealershipConfirmBuy(playerid, idx, slot) {
    new price   = DealershipStock[idx][slot][dss_price];
    new model   = DealershipStock[idx][slot][dss_modelid];
    new vstock  = DealershipStock[idx][slot][dss_stock];
    new c1      = DealershipStock[idx][slot][dss_color1];
    new c2      = DealershipStock[idx][slot][dss_color2];

    new str[512];
    format(str, sizeof str,
        "{FFFFFF}รุ่น : {FFD700}%s\n\
        {FFFFFF}Model : {AAAAAA}%d\n\
        {FFFFFF}สี : {AAAAAA}%d / %d\n\
        {FFFFFF}จำนวนรถในร้าน : {AAAAAA}%d\n\
        {FFFFFF}ราคา : {AAFFAA}$%d\n\n\
        {FFFFFF}เงินคุณ : {AAFFAA}$%d\n\n\
        {DD0000}คุณยืนยันจะซื้อรถคันนี้หรือไม่?",
        DealershipStock[idx][slot][dss_name],
        model, c1, c2, vstock, price,
        GetPlayerMoneyEx(playerid)
    );

    inline ConfirmBuy(res, list, string:input[]) {
        #pragma unused list, input
        if (!res) {
            DealershipShowPage(playerid, idx, 0);
            @return 1;
        }

        if (DealershipStock[idx][slot][dss_stock] <= 0) {
            SendErrorMessage(playerid, "{FFFFFF}รถคันนี้หมดสต๊อกแล้ว");
            @return DealershipShowPage(playerid, idx, 0);
        }

        if (GetPlayerMoney(playerid) < price) {
            SendErrorMessage(playerid, "{FFFFFF}เงินไม่พอ ต้องการ {AAFFAA}$%d", price);
            @return DealershipShowPage(playerid, idx, 0);
        }

        GivePlayerMoneyEx(playerid, -price);
        CreatePlayerVehicle(playerid, model, c1, c2);

        DealershipStockUpdate(idx, slot);

        va_SendClientMessage(playerid, COLOR_GREEN, "แจ้งเตือน: {FFFFFF}คุณซื้อ {FFD700}%s {FFFFFF}ในราคา {AAFFAA}$%d {FFFFFF}เรียบร้อยแล้ว!",
            DealershipStock[idx][slot][dss_name], price
        );

        PlayerDealershipID[playerid] = -1;
    }
    Dialog_ShowCallback(playerid, using inline ConfirmBuy,
        DIALOG_STYLE_MSGBOX, "{FFD700}ยืนยันการซื้อรถ", str,
        "{FFFFFF}ยืนยัน", "{FFFFFF}กลับ");
}

stock DealershipStockUpdate(idx, slot) {
    if (DealershipStock[idx][slot][dss_stock] > 1) {
        DealershipStock[idx][slot][dss_stock]--;
        new query[128];
        format(query, sizeof query,
            "UPDATE `"DEALERSHIP_STOCK_TABLE"` SET `stock` = '%d' WHERE `id` = '%d'"
            , DealershipStock[idx][slot][dss_stock]
            , DealershipStock[idx][slot][dss_id]);
        mysql_tquery(get_handle(), query);
    } else {
        new query[128];
        format(query, sizeof query,
            "DELETE FROM `"DEALERSHIP_STOCK_TABLE"` WHERE `id` = '%d'",
            DealershipStock[idx][slot][dss_id]);
        mysql_tquery(get_handle(), query);

        DealershipStock[idx][slot][dss_exists] = false;
        DealershipStock[idx][slot][dss_stock] = 0;
        DealershipData[idx][ds_stockCount]--;
    }
    return 1;
}

stock DealershipGetIndex(dbid) {
    for (new i = 0; i < MAX_DEALERSHIPS; i++) {
        if (DealershipData[i][ds_exists] && DealershipData[i][ds_id] == dbid)
            return i;
    }
    return -1;
}

stock DealershipGetSlotByList(idx, listitem) {
    new count = 0;
    for (new s = 0; s < MAX_DEALERSHIP_STOCK; s++) {
        if (!DealershipStock[idx][s][dss_exists]) continue;
        if (count == listitem) return s;
        count++;
    }
    return -1;
}

stock DealershipGetFreeIndex() {
    for (new i = 0; i < MAX_DEALERSHIPS; i++) {
        if (!DealershipData[i][ds_exists]) return i;
    }
    return -1;
}

stock DealershipGetFreeStock(idx) {
    for (new s = 0; s < MAX_DEALERSHIP_STOCK; s++) {
        if (!DealershipStock[idx][s][dss_exists]) return s;
    }
    return -1;
}

YCMD:adealership(playerid, string:params[], help) {
    if (!IsPlayerAdminEx(playerid)) return 1;
    if (!GetPlayerLoggedIn(playerid)) return 1;

    inline ADS_Main(res, list, string:in[]) {
        #pragma unused in
        if (!res) @return 1;
        switch (list) {
            case 0: Command_ReProcess(playerid, "/createdealer",        0);
            case 1: Command_ReProcess(playerid, "/deletedealer",        0);
            case 2: Command_ReProcess(playerid, "/addcardealer",        0);
            case 3: Command_ReProcess(playerid, "/removecardealer",     0);
            case 4: Command_ReProcess(playerid, "/setpricedeal",        0);
            case 5: Command_ReProcess(playerid, "/movedealer",          0);
            case 6: Command_ReProcess(playerid, "/tpdealer",            0);
            case 7: Command_ReProcess(playerid, "/listdealers",         0);
            case 8: Command_ReProcess(playerid, "/editstockcardealer",  0);
        }
    }
    Dialog_ShowCallback(playerid, using inline ADS_Main, DIALOG_STYLE_LIST,
        "{FFFFFF}Admin Menu — Dealership",
        "{FFFFFF}สร้างร้านใหม่\n\
        {FF4444}ลบร้าน\n\
        {FFFFFF}เพิ่มรถในร้าน\n\
        {FF4444}ลบรถออกจากร้าน\n\
        {FFFFFF}ตั้งราคารถ\n\
        {FFFFFF}ย้ายตำแหน่งร้าน\n\
        {FFFFFF}วาปไปร้าน\n\
        {FFFFFF}รายการร้านทั้งหมด\n\
        {FFFFFF}ปรับจำนวนรถที่อยู่ในสต๊อก",
        "{FFFFFF}เลือก", "{FFFFFF}ปิด");
    return 1;
}

YCMD:createdealer(playerid, string:params[], help) {
    if (!IsPlayerAdminEx(playerid)) return 1;

    inline InputName(res, list, string:input[]) {
        #pragma unused list
        if (!res) @return 1;
        if (isnull(input)) {
            SendErrorMessage(playerid, "{FFFFFF}กรุณากรอกชื่อร้าน");
            @return 1;
        }

        new idx = DealershipGetFreeIndex();
        if (idx == -1) {
            SendErrorMessage(playerid, "{FFFFFF}ร้านเต็มแล้ว (MAX: %d)", MAX_DEALERSHIPS);
            @return 1;
        }

        new Float:x, Float:y, Float:z, Float:a;
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, a);

        new query[256];
        mysql_format(get_handle(), query, sizeof query,
            "INSERT INTO `"DEALERSHIP_TABLE"` (`name`,`posx`,`posy`,`posz`,`posa`,`interior`,`world`) \
            VALUES('%e','%.4f','%.4f','%.4f','%.4f','%d','%d')",
            input, x, y, z, a,
            GetPlayerInterior(playerid),
            GetPlayerVirtualWorld(playerid)
        );

        inline OnCreated() {
            DealershipData[idx][ds_exists]   = true;
            DealershipData[idx][ds_id]       = cache_insert_id();
            DealershipData[idx][ds_posx]     = x;
            DealershipData[idx][ds_posy]     = y;
            DealershipData[idx][ds_posz]     = z;
            DealershipData[idx][ds_posa]     = a;
            DealershipData[idx][ds_interior] = GetPlayerInterior(playerid);
            DealershipData[idx][ds_world]    = GetPlayerVirtualWorld(playerid);
            DealershipData[idx][ds_stockCount] = 0;
            strmid(DealershipData[idx][ds_name], input, 0, 64);

            DealershipCreateObjects(idx);

            SendAdminMessage(COLOR_ADMIN, "AdmLog: %s สร้างร้านขายรถ '%s'", ReturnPlayerName(playerid), input);
        }
        MySQL_TQueryInline(get_handle(), using inline OnCreated, query);
    }
    Dialog_ShowCallback(playerid, using inline InputName, DIALOG_STYLE_INPUT,
        "{FFFFFF}สร้างร้านขายรถ",
        "{FFFFFF}กรอกชื่อร้าน\n{AAAAAA}ตำแหน่งจะถูกตั้งที่ที่คุณยืนอยู่",
        "{FFFFFF}สร้าง", "{FFFFFF}ยกเลิก");
    return 1;
}

YCMD:deletedealer(playerid, string:params[], help) {
    if (!IsPlayerAdminEx(playerid)) return 1;

    new body[1024] = "{FFFFFF}ID\t{FFFFFF}Index\t{FFFFFF}ชื่อร้าน\n";
    new line[128];
    new count = 0;

    for (new i = 0; i < MAX_DEALERSHIPS; i++) {
        if (!DealershipData[i][ds_exists]) continue;
        format(line, sizeof line, "{FFFFFF}%d\t{FFFFFF}%d\t{FFFFFF}%s\n",
            DealershipData[i][ds_id], i, DealershipData[i][ds_name]);
        strcat(body, line, sizeof body);
        count++;
    }

    if (!count) return SendErrorMessage(playerid, "{FFFFFF}ยังไม่มีร้านขายรถ");

    inline SelectShop(res, list, string:input[]) {
        #pragma unused input
        if (!res) @return 1;

        new idx = DealershipGetIndexByList(list);
        if (idx == -1) @return 1;

        inline ConfirmDelete(res2, list2, string:in2[]) {
            #pragma unused list2, in2
            if (!res2) @return 1;

            new query[128];
            format(query, sizeof query,
                "DELETE FROM `"DEALERSHIP_TABLE"` WHERE `id` = '%d'",
                DealershipData[idx][ds_id]);
            mysql_tquery(get_handle(), query);

            format(query, sizeof query,
                "DELETE FROM `"DEALERSHIP_STOCK_TABLE"` WHERE `shopid` = '%d'",
                DealershipData[idx][ds_id]);
            mysql_tquery(get_handle(), query);

            DealershipDestroyObjects(idx);
            SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ลบร้านขายรถ '%s'",
                ReturnPlayerName(playerid), DealershipData[idx][ds_name]);

            DealershipData[idx][ds_exists] = false;
            DealershipData[idx][ds_id]     = 0;
            strcopy(DealershipData[idx][ds_name], "None");
            // DealershipData[idx][ds_name]   = "None";
            for (new s = 0; s < MAX_DEALERSHIP_STOCK; s++)
                DealershipStock[idx][s][dss_exists] = false;
        }
        new str[128];
        format(str, sizeof str, "{FFFFFF}ยืนยันลบร้าน {FF4444}%s{FFFFFF}?",
            DealershipData[idx][ds_name]);
        Dialog_ShowCallback(playerid, using inline ConfirmDelete,
            DIALOG_STYLE_MSGBOX, "{FF4444}ลบร้านขายรถ", str,
            "{FF4444}ลบ", "{FFFFFF}ยกเลิก");
    }
    Dialog_ShowCallback(playerid, using inline SelectShop,
        DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}เลือกร้านที่จะลบ", body,
        "{FF4444}ลบ", "{FFFFFF}ยกเลิก");
    return 1;
}

YCMD:addcardealer(playerid, string:params[], help) {
    if (!IsPlayerAdminEx(playerid)) return 1;

    new body[1024] = "{FFFFFF}ID\t{FFFFFF}Index\t{FFFFFF}ชื่อร้าน\n";
    new line[128];
    new count = 0;

    for (new i = 0; i < MAX_DEALERSHIPS; i++) {
        if (!DealershipData[i][ds_exists]) continue;
        format(line, sizeof line, "{FFFFFF}%d\t{FFFFFF}%d\t{FFFFFF}%s\n",
            DealershipData[i][ds_id], i, DealershipData[i][ds_name]);
        strcat(body, line, sizeof body);
        count++;
    }

    if (!count) return SendErrorMessage(playerid, "{FFFFFF}ยังไม่มีร้านขายรถ");

    inline SelectShop(res, list, string:input[]) {
        #pragma unused input
        if (!res) @return 1;

        new idx = DealershipGetIndexByList(list);
        if (idx == -1) @return 1;

        new slot = DealershipGetFreeStock(idx);
        if (slot == -1) {
            SendErrorMessage(playerid, "{FFFFFF}รถในร้านเต็มแล้ว (MAX: %d)", MAX_DEALERSHIP_STOCK);
            @return 1;
        }

        inline InputModel(res2, list2, string:in2[]) {
            #pragma unused list2
            if (!res2) @return 1;

            new modelid = GetVehicleModelByName(in2);

            if (!modelid || modelid < 400 || modelid > 611) {
                SendErrorMessage(playerid, "{FFFFFF}ไม่พบรุ่นรถนั้น กรอก ID (400-611) หรือชื่อรถ");
                @return 1;
            }

            inline InputPrice(res3, list3, string:in3[]) {
                #pragma unused list3
                if (!res3) @return 1;

                new price = strval(in3);
                if (price <= 0) {
                    SendErrorMessage(playerid, "{FFFFFF}ราคาต้องมากกว่า 0");
                    @return 1;
                }

                inline InputColors(res4, list4, string:in4[]) {
                    #pragma unused list4
                    if (!res4) @return 1;

                    new c1, c2;
                    if (sscanf(in4, "dd", c1, c2)) {
                        c1 = 1; c2 = 1;
                    }

                    inline InputStock(res5, list5, string:in5[]) {
                        #pragma unused list5
                        if (!res5) @return 1;

                        new vStock;
                        new vName[64];
                        if (sscanf(in5, "d", vStock)) {
                            vStock = 1;
                        }

                        strcopy(vName, ReturnVehicleModelName(modelid));

                        new query[256];
                        mysql_format(get_handle(), query, sizeof query,
                            "INSERT INTO `"DEALERSHIP_STOCK_TABLE"` (`shopid`,`modelid`,`color1`,`color2`,`price`,`name`,`stock`) \
                            VALUES('%d','%d','%d','%d','%d','%e','%d')",
                            DealershipData[idx][ds_id], modelid, c1, c2, price, vName, vStock
                        );

                        inline OnStockAdded() {
                            DealershipStock[idx][slot][dss_exists]  = true;
                            DealershipStock[idx][slot][dss_id]      = cache_insert_id();
                            DealershipStock[idx][slot][dss_shopid]  = DealershipData[idx][ds_id];
                            DealershipStock[idx][slot][dss_modelid] = modelid;
                            DealershipStock[idx][slot][dss_color1]  = c1;
                            DealershipStock[idx][slot][dss_color2]  = c2;
                            DealershipStock[idx][slot][dss_price]   = price;
                            DealershipStock[idx][slot][dss_stock]   = vStock;
                            strcopy(DealershipStock[idx][slot][dss_name], vName);
                            DealershipData[idx][ds_stockCount]++;
                            
                            SendAdminMessage(COLOR_ADMIN, "AdmLog: %s เพิ่มรถ %s ราคา $%d ลงร้าน %s จำนวน %d คัน",
                                ReturnPlayerName(playerid), vName, price, DealershipData[idx][ds_name], vStock);
                        }
                        MySQL_TQueryInline(get_handle(), using inline OnStockAdded, query);
                    }
                    Dialog_ShowCallback(playerid, using inline InputStock, DIALOG_STYLE_INPUT,
                        "{FFFFFF}ตั้งจำนวนที่อยู่ใน Stock",
                        "{FFFFFF}กรอก: {FFFF00}[จำนวนคัน]\n{AAAAAA}ตัวอย่าง: 10",
                        "{FFFFFF}ถัดไป", "{FFFFFF}ยกเลิก");                 
                }
                Dialog_ShowCallback(playerid, using inline InputColors, DIALOG_STYLE_INPUT,
                    "{FFFFFF}ตั้งสีรถ",
                    "{FFFFFF}กรอก: {FFFF00}[สี1] [สี2]\n{AAAAAA}ตัวอย่าง: 1 1",
                    "{FFFFFF}ถัดไป", "{FFFFFF}ยกเลิก");
            }
            new priceInfo[128];
            new vehicleName[64];
            strcopy(vehicleName, ReturnVehicleModelName(modelid));
            format(priceInfo, sizeof priceInfo, "{FFFFFF}รุ่น: {FFD700}%s\n{FFFFFF}กรอกราคา:", vehicleName);
            Dialog_ShowCallback(playerid, using inline InputPrice, DIALOG_STYLE_INPUT,
                "{FFFFFF}ตั้งราคา", priceInfo,
                "{FFFFFF}ถัดไป", "{FFFFFF}ยกเลิก");
        }
        Dialog_ShowCallback(playerid, using inline InputModel, DIALOG_STYLE_INPUT,
            "{FFFFFF}เพิ่มรถ",
            "{FFFFFF}กรอก {FFFF00}Model ID (400-611) {FFFFFF}หรือ {FFFF00}ชื่อรถ\n{AAAAAA}เช่น: 411 หรือ Infernus",
            "{FFFFFF}ถัดไป", "{FFFFFF}ยกเลิก");
    }
    Dialog_ShowCallback(playerid, using inline SelectShop,
        DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}เลือกร้านที่จะเพิ่มรถ", body,
        "{FFFFFF}เลือก", "{FFFFFF}ยกเลิก");
    return 1;
}

YCMD:removecardealer(playerid, string:params[], help) {
    if (!IsPlayerAdminEx(playerid)) return 1;

    new body[1024] = "{FFFFFF}ID\t{FFFFFF}Index\t{FFFFFF}ชื่อร้าน\n";
    new line[128], count = 0;
    for (new i = 0; i < MAX_DEALERSHIPS; i++) {
        if (!DealershipData[i][ds_exists]) continue;
        format(line, sizeof line, "{FFFFFF}%d\t{FFFFFF}%d\t{FFFFFF}%s\n",
            DealershipData[i][ds_id], i, DealershipData[i][ds_name]);
        strcat(body, line, sizeof body);
        count++;
    }
    if (!count) return SendErrorMessage(playerid, "{FFFFFF}ยังไม่มีร้านขายรถ");

    inline SelectShop(res, list, string:input[]) {
        #pragma unused input
        if (!res) @return 1;
        new idx = DealershipGetIndexByList(list);
        if (idx == -1) @return 1;

        new stockBody[1024] = "{FFFFFF}รุ่น\t{000000}-\t{FFFFFF}ราคา\n";
        new stockLine[128], stockCount = 0;
        for (new s = 0; s < MAX_DEALERSHIP_STOCK; s++) {
            if (!DealershipStock[idx][s][dss_exists]) continue;
            format(stockLine, sizeof stockLine, "{FFFFFF}%s\t{000000}-\t{AAFFAA}$%d\n",
                DealershipStock[idx][s][dss_name],
                DealershipStock[idx][s][dss_price]);
            strcat(stockBody, stockLine, sizeof stockBody);
            stockCount++;
        }

        if (!stockCount) {
            SendErrorMessage(playerid, "{FFFFFF}ร้านนี้ยังไม่มีรถ");
            @return 1;
        }

        new title[128];
        format(title, sizeof title, "{FFFFFF}เลือกรถที่จะลบจาก {FFD700}%s", DealershipData[idx][ds_name]);

        inline SelectCar(res2, list2, string:in2[]) {
            #pragma unused in2
            if (!res2) @return 1;

            new slot = DealershipGetSlotByList(idx, list2);
            if (slot == -1) @return 1;

            new query[128];
            format(query, sizeof query,
                "DELETE FROM `"DEALERSHIP_STOCK_TABLE"` WHERE `id` = '%d'",
                DealershipStock[idx][slot][dss_id]);
            mysql_tquery(get_handle(), query);

            SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ลบรถ %s ออกจากร้าน %s",
                ReturnPlayerName(playerid),
                DealershipStock[idx][slot][dss_name],
                DealershipData[idx][ds_name]);

            DealershipStock[idx][slot][dss_exists] = false;
            DealershipData[idx][ds_stockCount]--;
        }
        Dialog_ShowCallback(playerid, using inline SelectCar,
            DIALOG_STYLE_TABLIST_HEADERS, title, stockBody,
            "{FF4444}ลบ", "{FFFFFF}กลับ");
    }
    Dialog_ShowCallback(playerid, using inline SelectShop,
        DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}เลือกร้าน", body,
        "{FFFFFF}เลือก", "{FFFFFF}ยกเลิก");
    return 1;
}

YCMD:editstockcardealer(playerid, string:params[], help) {
    if (!IsPlayerAdminEx(playerid)) return 1;

    new body[1024] = "{FFFFFF}ID\t{FFFFFF}Index\t{FFFFFF}ชื่อร้าน\n";
    new line[128], count = 0;
    for (new i = 0; i < MAX_DEALERSHIPS; i++) {
        if (!DealershipData[i][ds_exists]) continue;
        format(line, sizeof line, "{FFFFFF}%d\t{FFFFFF}%d\t{FFFFFF}%s\n",
            DealershipData[i][ds_id], i, DealershipData[i][ds_name]);
        strcat(body, line, sizeof body);
        count++;
    }
    if (!count) return SendErrorMessage(playerid, "{FFFFFF}ยังไม่มีร้านขายรถ");

    inline SelectShop(res, list, string:input[]) {
        #pragma unused input
        if (!res) @return 1;
        new idx = DealershipGetIndexByList(list);
        if (idx == -1) @return 1;

        new stockBody[1024] = "{FFFFFF}รุ่น\t{FFFFFF}จำนวน\t{FFFFFF}ราคา\n";
        new stockLine[128], stockCount = 0;
        for (new s = 0; s < MAX_DEALERSHIP_STOCK; s++) {
            if (!DealershipStock[idx][s][dss_exists]) continue;
            format(stockLine, sizeof stockLine, "{FFFFFF}%s\t{FFFFFF}%d\t{AAFFAA}$%d\n",
                DealershipStock[idx][s][dss_name],
                DealershipStock[idx][s][dss_stock],
                DealershipStock[idx][s][dss_price]);
            strcat(stockBody, stockLine, sizeof stockBody);
            stockCount++;
        }

        if (!stockCount) {
            SendErrorMessage(playerid, "{FFFFFF}ร้านนี้ยังไม่มีรถ");
            @return 1;
        }

        new title[128];
        format(title, sizeof title, "{FFFFFF}ตั้งค่าจำนวนรถจาก {FFD700}%s", DealershipData[idx][ds_name]);

        inline SelectCar(res2, list2, string:in2[]) {
            #pragma unused in2
            if (!res2) @return 1;

            new slot = DealershipGetSlotByList(idx, list2);
            if (slot == -1) @return 1;

            inline EditStock(res3, list3, string:in3[]) {
                #pragma unused list3
                if (!res3) @return 1;

                new vStock = strval(in3);
                if (vStock <= 0) {
                    new query[128];
                    format(query, sizeof query,
                        "DELETE FROM `"DEALERSHIP_STOCK_TABLE"` WHERE `id` = '%d'"
                        , DealershipStock[idx][slot][dss_id]);
                    mysql_tquery(get_handle(), query);

                    DealershipStock[idx][slot][dss_exists] = false;
                    DealershipData[idx][ds_stockCount]--;

                    SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ลบรถ %s ออกจากร้าน %s",
                        ReturnPlayerName(playerid),
                        DealershipStock[idx][slot][dss_name],
                        DealershipData[idx][ds_name]);
                    @return 1;
                }

                DealershipStock[idx][slot][dss_stock] = vStock;
                
                new query[128];
                format(query, sizeof query,
                    "UPDATE `"DEALERSHIP_STOCK_TABLE"` SET `stock` = '%d' WHERE `id` = '%d'"
                    , DealershipStock[idx][slot][dss_stock]
                    , DealershipStock[idx][slot][dss_id]);
                mysql_tquery(get_handle(), query);

                SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ปรับจำนวนรถรุ่น %s ร้าน %s เป็นจำนวน %d คัน",
                    ReturnPlayerName(playerid),
                    DealershipStock[idx][slot][dss_name],
                    DealershipData[idx][ds_name],
                    DealershipStock[idx][slot][dss_stock]);
            }
            new str[128];
            format(str, sizeof str, "{FFFFFF}รถรุ่น: {FFFF00}%s\n{FFFFFF}จำนวนที่มีในสต๊อก: {FFFF00}%d\n{FFFFFF}กรอกจำนวนที่มีในสต๊อกที่นี่"
                , DealershipStock[idx][slot][dss_name]
                , DealershipStock[idx][slot][dss_stock]);
            Dialog_ShowCallback(playerid, using inline EditStock,
                DIALOG_STYLE_INPUT, "{FFFFFF}ปรับจำนวนรถ", str,
                "{FF4444}เลือก", "{FFFFFF}กลับ");
        }
        Dialog_ShowCallback(playerid, using inline SelectCar,
            DIALOG_STYLE_TABLIST_HEADERS, title, stockBody,
            "{FF4444}เลือก", "{FFFFFF}กลับ");
    }
    Dialog_ShowCallback(playerid, using inline SelectShop,
        DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}เลือกร้าน", body,
        "{FFFFFF}เลือก", "{FFFFFF}ยกเลิก");
    return 1;
}

YCMD:setpricedeal(playerid, string:params[], help) {
    if (!IsPlayerAdminEx(playerid)) return 1;

    new body[1024] = "{FFFFFF}ID\t{FFFFFF}Index\t{FFFFFF}ชื่อร้าน\n";
    new line[128], count = 0;
    for (new i = 0; i < MAX_DEALERSHIPS; i++) {
        if (!DealershipData[i][ds_exists]) continue;
        format(line, sizeof line, "{FFFFFF}%d\t{FFFFFF}%d\t{FFFFFF}%s\n",
            DealershipData[i][ds_id], i, DealershipData[i][ds_name]);
        strcat(body, line, sizeof body);
        count++;
    }
    if (!count) return SendErrorMessage(playerid, "{FFFFFF}ยังไม่มีร้านขายรถ");

    inline SelectShop(res, list, string:input[]) {
        #pragma unused input
        if (!res) @return 1;
        new idx = DealershipGetIndexByList(list);
        if (idx == -1) @return 1;

        new stockBody[1024] = "{FFFFFF}รุ่น\t{000000}-\t{FFFFFF}ราคาปัจจุบัน\n";
        new stockLine[128], stockCount = 0;
        for (new s = 0; s < MAX_DEALERSHIP_STOCK; s++) {
            if (!DealershipStock[idx][s][dss_exists]) continue;
            format(stockLine, sizeof stockLine, "{FFFFFF}%s\t{000000}-\t{AAFFAA}$%d\n",
                DealershipStock[idx][s][dss_name],
                DealershipStock[idx][s][dss_price]);
            strcat(stockBody, stockLine, sizeof stockBody);
            stockCount++;
        }
        if (!stockCount) {
            SendErrorMessage(playerid, "{FFFFFF}ร้านนี้ยังไม่มีรถ");
            @return 1;
        }

        inline SelectCar(res2, list2, string:in2[]) {
            #pragma unused in2
            if (!res2) @return 1;
            new slot = DealershipGetSlotByList(idx, list2);
            if (slot == -1) @return 1;

            inline InputNewPrice(res3, list3, string:in3[]) {
                #pragma unused list3
                if (!res3) @return 1;
                new newPrice = strval(in3);
                if (newPrice <= 0) {
                    SendErrorMessage(playerid, "{FFFFFF}ราคาต้องมากกว่า 0");
                    @return 1;
                }

                new query[128];
                format(query, sizeof query,
                    "UPDATE `"DEALERSHIP_STOCK_TABLE"` SET `price` = '%d' WHERE `id` = '%d'",
                    newPrice, DealershipStock[idx][slot][dss_id]);
                mysql_tquery(get_handle(), query);

                DealershipStock[idx][slot][dss_price] = newPrice;

                va_SendClientMessage(playerid, COLOR_GREEN, "แจ้งเตือน: {FFFFFF}ตั้งราคา {FFD700}%s {FFFFFF}เป็น {AAFFAA}$%d {FFFFFF}เรียบร้อยแล้ว",
                    DealershipStock[idx][slot][dss_name], newPrice);
                SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ตั้งราคา %s เป็น $%d",
                    ReturnPlayerName(playerid), DealershipStock[idx][slot][dss_name], newPrice);
            }
            new info[128];
            format(info, sizeof info, "{FFFFFF}รุ่น: {FFD700}%s\n{FFFFFF}ราคาเดิม: {AAFFAA}$%d\n\n{FFFFFF}กรอกราคาใหม่:",
                DealershipStock[idx][slot][dss_name],
                DealershipStock[idx][slot][dss_price]);
            Dialog_ShowCallback(playerid, using inline InputNewPrice, DIALOG_STYLE_INPUT,
                "{FFFFFF}ตั้งราคาใหม่", info,
                "{FFFFFF}บันทึก", "{FFFFFF}ยกเลิก");
        }
        new title[128];
        format(title, sizeof title, "{FFFFFF}เลือกรถ — {FFD700}%s", DealershipData[idx][ds_name]);
        Dialog_ShowCallback(playerid, using inline SelectCar,
            DIALOG_STYLE_TABLIST_HEADERS, title, stockBody,
            "{FFFFFF}เลือก", "{FFFFFF}กลับ");
    }
    Dialog_ShowCallback(playerid, using inline SelectShop,
        DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}เลือกร้าน", body,
        "{FFFFFF}เลือก", "{FFFFFF}ยกเลิก");
    return 1;
}

YCMD:movedealer(playerid, string:params[], help) {
    if (!IsPlayerAdminEx(playerid)) return 1;

    new body[1024] = "{FFFFFF}ID\t{FFFFFF}Index\t{FFFFFF}ชื่อร้าน\n";
    new line[128], count = 0;
    for (new i = 0; i < MAX_DEALERSHIPS; i++) {
        if (!DealershipData[i][ds_exists]) continue;
        format(line, sizeof line, "{FFFFFF}%d\t{FFFFFF}%d\t{FFFFFF}%s\n",
            DealershipData[i][ds_id], i, DealershipData[i][ds_name]);
        strcat(body, line, sizeof body);
        count++;
    }
    if (!count) return SendErrorMessage(playerid, "{FFFFFF}ยังไม่มีร้านขายรถ");

    inline SelectShop(res, list, string:input[]) {
        #pragma unused input
        if (!res) @return 1;
        new idx = DealershipGetIndexByList(list);
        if (idx == -1) @return 1;

        inline ConfirmMove(res2, list2, string:in2[]) {
            #pragma unused list2, in2
            if (!res2) @return 1;

            new Float:x, Float:y, Float:z, Float:a;
            GetPlayerPos(playerid, x, y, z);
            GetPlayerFacingAngle(playerid, a);

            DealershipData[idx][ds_posx]     = x;
            DealershipData[idx][ds_posy]     = y;
            DealershipData[idx][ds_posz]     = z;
            DealershipData[idx][ds_posa]     = a;
            DealershipData[idx][ds_interior] = GetPlayerInterior(playerid);
            DealershipData[idx][ds_world]    = GetPlayerVirtualWorld(playerid);

            new query[256];
            format(query, sizeof query,
                "UPDATE `"DEALERSHIP_TABLE"` SET `posx`='%.4f',`posy`='%.4f',`posz`='%.4f',`posa`='%.4f',`interior`='%d',`world`='%d' WHERE `id`='%d'",
                x, y, z, a,
                GetPlayerInterior(playerid),
                GetPlayerVirtualWorld(playerid),
                DealershipData[idx][ds_id]);
            mysql_tquery(get_handle(), query);

            DealershipCreateObjects(idx);

            SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ย้ายร้านขายรถ '%s'",
                ReturnPlayerName(playerid), DealershipData[idx][ds_name]);
        }
        new str[128];
        format(str, sizeof str, "{FFFFFF}ย้ายร้าน {FFD700}%s {FFFFFF}มาที่ตำแหน่งที่คุณยืนอยู่?",
            DealershipData[idx][ds_name]);
        Dialog_ShowCallback(playerid, using inline ConfirmMove,
            DIALOG_STYLE_MSGBOX, "{FFFFFF}ยืนยันการย้ายร้าน", str,
            "{FFFFFF}ย้าย", "{FFFFFF}ยกเลิก");
    }
    Dialog_ShowCallback(playerid, using inline SelectShop,
        DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}เลือกร้านที่จะย้าย", body,
        "{FFFFFF}เลือก", "{FFFFFF}ยกเลิก");
    return 1;
}

YCMD:tpdealer(playerid, string:params[], help) {
    if (!IsPlayerAdminEx(playerid)) return 1;

    new body[1024] = "{FFFFFF}ID\t{FFFFFF}Index\t{FFFFFF}ชื่อร้าน\n";
    new line[128], count = 0;
    for (new i = 0; i < MAX_DEALERSHIPS; i++) {
        if (!DealershipData[i][ds_exists]) continue;
        format(line, sizeof line, "{FFFFFF}%d\t{FFFFFF}%d\t{FFFFFF}%s\n",
            DealershipData[i][ds_id], i, DealershipData[i][ds_name]);
        strcat(body, line, sizeof body);
        count++;
    }
    if (!count) return SendErrorMessage(playerid, "{FFFFFF}ยังไม่มีร้านขายรถ");

    inline SelectShop(res, list, string:input[]) {
        #pragma unused input
        if (!res) @return 1;
        new idx = DealershipGetIndexByList(list);
        if (idx == -1) @return 1;

        SetPlayerPos(playerid,
            DealershipData[idx][ds_posx],
            DealershipData[idx][ds_posy],
            DealershipData[idx][ds_posz]);
        SetPlayerFacingAngle(playerid, DealershipData[idx][ds_posa]);
        SetPlayerInterior(playerid, DealershipData[idx][ds_interior]);
        SetPlayerVirtualWorld(playerid, DealershipData[idx][ds_world]);

        SendCongratMessage(playerid, "{FFFFFF}วาปไปร้าน {FFD700}%s {FFFFFF}แล้ว", DealershipData[idx][ds_name]);
    }
    Dialog_ShowCallback(playerid, using inline SelectShop,
        DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}วาปไปร้าน", body,
        "{FFFFFF}ไป", "{FFFFFF}ยกเลิก");
    return 1;
}

YCMD:listdealers(playerid, string:params[], help) {
    if (!IsPlayerAdminEx(playerid)) return 1;

    new body[2048] = "{FFFFFF}ID\t{FFFFFF}ชื่อร้าน\t{FFFFFF}รถในร้าน\n";
    new line[128], count = 0;
    for (new i = 0; i < MAX_DEALERSHIPS; i++) {
        if (!DealershipData[i][ds_exists]) continue;
        format(line, sizeof line, "{FFFFFF}%d\t{FFFFFF}%s\t{AAFFAA}%d คัน\n",
            DealershipData[i][ds_id],
            DealershipData[i][ds_name],
            DealershipData[i][ds_stockCount]);
        strcat(body, line, sizeof body);
        count++;
    }

    if (!count) return SendErrorMessage(playerid, "{FFFFFF}ยังไม่มีร้านขายรถ");

    new title[64];
    format(title, sizeof title, "{FFFFFF}ร้านขายรถทั้งหมด (%d ร้าน)", count);

    inline Close(res, list, string:input[]) {
        #pragma unused res, list, input
    }
    Dialog_ShowCallback(playerid, using inline Close,
        DIALOG_STYLE_TABLIST_HEADERS, title, body,
        "{FFFFFF}ปิด", "");
    return 1;
}

stock DealershipGetIndexByList(listitem) {
    new count = 0;
    for (new i = 0; i < MAX_DEALERSHIPS; i++) {
        if (!DealershipData[i][ds_exists]) continue;
        if (count == listitem) return i;
        count++;
    }
    return -1;
}
