#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
    Iter_Init(PrivateVehicles);
    mysql_tquery(get_handle(), "SELECT * FROM "VEHICLE_TABLE" WHERE `vehOwner` = '-'", "LoadDealerVehicles", "");
    return 1;
}

hook OnGameModeExit() {
    foreach (new i : ServerVehicles) {
        if (!strcmp(vInfo[i][vehOwner], "-") || strcmp(vInfo[i][vehOwner], "-")) {
            SaveVehicle(i);
            DestroyVehicle(vInfo[i][vehSessionID]);
            DestroyDynamic3DTextLabel(vInfo[i][vehLabel]);
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if (newkeys & PRESS_N) {
        foreach (new i : ServerVehicles) {
            if (strcmp(vInfo[i][vehOwner], "-")) continue; // ข้ามรถที่มีเจ้าของ
            if (IsPlayerInAnyVehicle(playerid)) continue;
            if (IsPlayerInRangeOfPoint(playerid, 2.0, vInfo[i][vehX], vInfo[i][vehY], vInfo[i][vehZ])) {
                new str[32];
                format(str, sizeof str, "/buyvehicle %d", i);
                Command_ReProcess(playerid, str, 0);
            }
        }

        foreach (new i : ServerVehicles) {
            if (!strcmp(vInfo[i][vehOwner], "-")) continue; // ข้ามรถ dealer

            if (IsPlayerInVehicle(playerid, vInfo[i][vehSessionID])) {
                new engine, lights, alarm, doors, bonnet, boot, objective;
                GetVehicleParamsEx(vInfo[i][vehSessionID], engine, lights, alarm, doors, bonnet, boot, objective);

                if (engine == VEHICLE_PARAMS_ON) {
                    SetVehicleParamsEx(vInfo[i][vehSessionID], VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);
                    GameTextForPlayer(playerid, "~r~ENGINE OFF", 2000, 3);
                } else {
                    SetVehicleParamsEx(vInfo[i][vehSessionID], VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective);
                    GameTextForPlayer(playerid, "~g~ENGINE ON", 2000, 3);
                }
            }
        }
    }
    return 1;
}

hook OnPlayerConnect(playerid) {

	new query[65];
    mysql_format(get_handle(), query, sizeof(query), "SELECT * FROM "VEHICLE_TABLE" WHERE `vehOwner` = '%e'", ReturnPlayerName(playerid));
    mysql_tquery(get_handle(), query, "LoadPlayerVehicles", "i", playerid);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
	foreach (new i : PrivateVehicles[playerid]) {
        if (!strcmp(vInfo[i][vehOwner], ReturnPlayerName(playerid))) {
            SaveVehicle(i);
            DestroyVehicle(vInfo[i][vehSessionID]);
            Iter_Remove(ServerVehicles, i);
        }
    }
	return 1;
}

hook OnVehicleMod(playerid, vehicleid, componentid) {
	foreach (new i : PrivateVehicles[playerid]) {
        if (IsPlayerInVehicle(playerid, vInfo[i][vehSessionID])) {
            if (!strcmp(vInfo[i][vehOwner], ReturnPlayerName(playerid))) {
                for (new x; x < 14; x++) {
                    if (GetVehicleComponentType(componentid) == x) {
                        vInfo[i][vehMod][x] = componentid;
                    }
                }
                SaveVehicle(i);
            }
        }
    }
	return 1;
}

hook OnVehicleSpawn(vehicleid) {
    foreach (new playerid : Player) {
        foreach (new i : PrivateVehicles[playerid]) {
            for (new x = 0; x < 14; x++) {
                if (!strcmp(vInfo[i][vehOwner], ReturnPlayerName(playerid))) {
                    if(vInfo[i][vehMod][x] > 0) AddVehicleComponent(vInfo[i][vehSessionID], vInfo[i][vehMod][x]);
                }
            }
        }
    }
    return 1;
}

hook OnVehicleRespray(playerid, vehicleid, color1, color2) {
    foreach (new i : PrivateVehicles[playerid]) {
        if (IsPlayerInVehicle(playerid, vInfo[i][vehSessionID])) {
            if (!strcmp(vInfo[i][vehOwner], ReturnPlayerName(playerid))) {
                vInfo[i][vehColorOne] = color1;
                vInfo[i][vehColorTwo] = color2;
                ChangeVehicleColor(vInfo[i][vehSessionID], vInfo[i][vehColorOne], vInfo[i][vehColorTwo]);
                SaveVehicle(i);
            }
        }
    }
    return 0;
}

public LoadDealerVehicles() {
    new rows = cache_num_rows();
    if(rows) {
        new string[75];
        for (new i; i < rows; i++) {
            new id = Iter_Free(ServerVehicles);
            
            cache_get_value_name(i, "vehOwner", vInfo[id][vehOwner], .max_len = MAX_PLAYER_NAME);
            cache_get_value_name_int(i, "vehModel", vInfo[id][vehModel]);
            cache_get_value_name(i, "vehName", vInfo[id][vehName]);
            cache_get_value_name(i, "vehPlate", vInfo[id][vehPlate]);
            cache_get_value_name_int(i, "vehPrice", vInfo[id][vehPrice]);
            cache_get_value_name_int(i, "vehColorOne", vInfo[id][vehColorOne]);
            cache_get_value_name_int(i, "vehColorTwo", vInfo[id][vehColorTwo]);
            cache_get_value_name_float(i, "vehX", vInfo[id][vehX]);
            cache_get_value_name_float(i, "vehY", vInfo[id][vehY]);
            cache_get_value_name_float(i, "vehZ", vInfo[id][vehZ]);
            cache_get_value_name_float(i, "vehA", vInfo[id][vehA]);

            vInfo[id][vehSessionID] = CreateVehicle(vInfo[id][vehModel], vInfo[id][vehX], vInfo[id][vehY], vInfo[id][vehZ], vInfo[id][vehA], vInfo[id][vehColorOne], vInfo[id][vehColorTwo], -1);

            cache_get_value_name_int(i, "vehID", vInfo[id][vehID]);

            SetVehicleToRespawn(vInfo[id][vehSessionID]);
            SetVehicleParamsEx(vInfo[id][vehSessionID], 0, 0, 0, 1, 0, 0, 0);
            SetVehicleNumberPlate(vInfo[id][vehSessionID], "CC");

            format(string, sizeof(string), VEHICLE_BUY_TEXT, vInfo[id][vehName], cNumber(vInfo[id][vehPrice]));

            vInfo[id][vehLabel] = CreateDynamic3DTextLabel(string, 0xFFFF00FF, vInfo[id][vehX], vInfo[id][vehY], vInfo[id][vehZ], 10.0, INVALID_PLAYER_ID, vInfo[id][vehSessionID]);
            Iter_Add(ServerVehicles, id);
        }
        printf("[SYSTEM][DB] Loaded %d vehicles for dealership", rows);
    }
    return 1;
}

public LoadPlayerVehicles(playerid) {
    new rows = cache_num_rows();
    if (rows) {
        for (new i; i < rows; i++) {
            new id = Iter_Free(ServerVehicles);
            cache_get_value_name(i, "vehOwner", vInfo[id][vehOwner], .max_len = MAX_PLAYER_NAME);
            cache_get_value_name_int(i, "vehModel", vInfo[id][vehModel]);
            cache_get_value_name(i, "vehName", vInfo[id][vehName]);
            cache_get_value_name(i, "vehPlate", vInfo[id][vehPlate]);
            cache_get_value_name_int(i, "vehPrice", vInfo[id][vehPrice]);
            cache_get_value_name_int(i, "vehLock", vInfo[id][vehLock]);
            cache_get_value_name_int(i, "vehColorOne", vInfo[id][vehColorOne]);
            cache_get_value_name_int(i, "vehColorTwo", vInfo[id][vehColorTwo]);
            cache_get_value_name_int(i, "vehMod_1", vInfo[id][vehMod][0]);
            cache_get_value_name_int(i, "vehMod_2", vInfo[id][vehMod][1]);
            cache_get_value_name_int(i, "vehMod_3", vInfo[id][vehMod][2]);
            cache_get_value_name_int(i, "vehMod_4", vInfo[id][vehMod][3]);
            cache_get_value_name_int(i, "vehMod_5", vInfo[id][vehMod][4]);
            cache_get_value_name_int(i, "vehMod_6", vInfo[id][vehMod][5]);
            cache_get_value_name_int(i, "vehMod_7", vInfo[id][vehMod][6]);
            cache_get_value_name_int(i, "vehMod_8", vInfo[id][vehMod][7]);
            cache_get_value_name_int(i, "vehMod_9", vInfo[id][vehMod][8]);
            cache_get_value_name_int(i, "vehMod_10", vInfo[id][vehMod][9]);
            cache_get_value_name_int(i, "vehMod_11", vInfo[id][vehMod][10]);
            cache_get_value_name_int(i, "vehMod_12", vInfo[id][vehMod][11]);
            cache_get_value_name_int(i, "vehMod_13", vInfo[id][vehMod][12]);
            cache_get_value_name_int(i, "vehMod_14", vInfo[id][vehMod][13]);
            cache_get_value_name_float(i, "vehX", vInfo[id][vehX]);
            cache_get_value_name_float(i, "vehY", vInfo[id][vehY]);
            cache_get_value_name_float(i, "vehZ", vInfo[id][vehZ]);
            cache_get_value_name_float(i, "vehA", vInfo[id][vehA]);

            vInfo[id][vehSessionID] = CreateVehicle(vInfo[id][vehModel], vInfo[id][vehX], vInfo[id][vehY], vInfo[id][vehZ], vInfo[id][vehA], vInfo[id][vehColorOne], vInfo[id][vehColorTwo], -1);

            cache_get_value_name_int(i, "vehID", vInfo[id][vehID]);

            format(vInfo[id][vehName], MAX_PLAYER_NAME, GetVehicleName(vInfo[id][vehModel]));
            format(vInfo[id][vehPlate], 16, vInfo[id][vehPlate]);
            format(vInfo[id][vehOwner], MAX_PLAYER_NAME, ReturnPlayerName(playerid));

            SetVehicleToRespawn(vInfo[id][vehSessionID]);
            SetVehicleParamsEx(vInfo[id][vehSessionID], 0, 0, 0, vInfo[id][vehLock], 0, 0, 0);
            SetVehicleNumberPlate(vInfo[id][vehSessionID], vInfo[id][vehPlate]);
            for (new x = 0; x < 14; x++) if(vInfo[id][vehMod][x] > 0) AddVehicleComponent(vInfo[id][vehSessionID], vInfo[id][vehMod][x]);

            Iter_Add(PrivateVehicles[playerid], id);
            Iter_Add(ServerVehicles, id);
        }
        printf("Loaded %d vehicles for %s", rows, ReturnPlayerName(playerid));
    }
    return 1;
}

public OnDealerVehicleCreated(vehicleid) {
    vInfo[vehicleid][vehID] = cache_insert_id(); 
    Iter_Add(ServerVehicles, vehicleid);
    return 1;
}

stock SaveVehicle(vehicleid) {
    if (!Iter_Contains(ServerVehicles, vehicleid)) return 0;

    format(vInfo[vehicleid][vehName], 16, GetVehicleName(vInfo[vehicleid][vehModel]));
    GetVehiclePos(vInfo[vehicleid][vehSessionID], vInfo[vehicleid][vehX], vInfo[vehicleid][vehY], vInfo[vehicleid][vehZ]);
    GetVehicleZAngle(vInfo[vehicleid][vehSessionID], vInfo[vehicleid][vehA]);

    new query[500];
    mysql_format(get_handle(), query, sizeof(query), "UPDATE "VEHICLE_TABLE" SET `vehName` = '%e', `vehOwner` = '%e', `vehLock` = %i, `vehModel` = %i,\
    `vehPlate` = '%e', `vehMod_1` = %i, `vehMod_2` = %i, `vehMod_3` = %i, `vehMod_4` = %i, `vehMod_5` = %i, `vehMod_6` = %i, `vehMod_7` = %i,\
    `vehMod_8` = %i, `vehMod_9` = %i, `vehMod_10` = %i, `vehMod_11` = %i, `vehMod_12` = %i, `vehMod_13` = %i, `vehMod_14` = %i, `vehColorOne` = %i,\
    `vehColorTwo` = %i, `vehX` = %f, `vehY` = %f, `vehZ` = %f, `vehA` = %f WHERE `vehID` = %d", vInfo[vehicleid][vehName], vInfo[vehicleid][vehOwner],
    vInfo[vehicleid][vehLock], vInfo[vehicleid][vehModel], vInfo[vehicleid][vehPlate], vInfo[vehicleid][vehMod][0], vInfo[vehicleid][vehMod][1], vInfo[vehicleid][vehMod][2], 
    vInfo[vehicleid][vehMod][3], vInfo[vehicleid][vehMod][4], vInfo[vehicleid][vehMod][5], vInfo[vehicleid][vehMod][6], vInfo[vehicleid][vehMod][7], vInfo[vehicleid][vehMod][8], 
    vInfo[vehicleid][vehMod][9], vInfo[vehicleid][vehMod][10], vInfo[vehicleid][vehMod][11], vInfo[vehicleid][vehMod][12], vInfo[vehicleid][vehMod][13], vInfo[vehicleid][vehColorOne],
    vInfo[vehicleid][vehColorTwo], vInfo[vehicleid][vehX], vInfo[vehicleid][vehY], vInfo[vehicleid][vehZ], vInfo[vehicleid][vehA], vInfo[vehicleid][vehID]);
    mysql_tquery(get_handle(), query);
    return 1;
}

stock ResetVehicle(vehicleid) {
    if (!Iter_Contains(ServerVehicles, vehicleid)) return 0;

    foreach (new i : Player) {
        if (!strcmp(vInfo[vehicleid][vehOwner], ReturnPlayerName(i))) {
            Iter_Remove(PrivateVehicles[i], vehicleid);
        }
    }

    format(vInfo[vehicleid][vehOwner], MAX_PLAYER_NAME, "-");
    format(vInfo[vehicleid][vehPlate], 16, "NULL");
    vInfo[vehicleid][vehModel] = -1; 
    vInfo[vehicleid][vehLock] = MODE_NOLOCK;
    vInfo[vehicleid][vehPrice] = 0;
    vInfo[vehicleid][vehColorOne] = -1;
    vInfo[vehicleid][vehColorTwo] = -1;

    for (new i = 0; i < 14; i++) {
        if (vInfo[vehicleid][vehMod][i] > 0) {
            RemoveVehicleComponent(vInfo[vehicleid][vehSessionID], vInfo[vehicleid][vehMod][i]);
            vInfo[vehicleid][vehMod][i] = 0;
        }
    }

    if(IsValidDynamic3DTextLabel(vInfo[vehicleid][vehLabel])) DestroyDynamic3DTextLabel(vInfo[vehicleid][vehLabel]);
    DestroyVehicle(vInfo[vehicleid][vehSessionID]);
    return 1;
}

stock createVehicle(vehicleid, Float:itsX, Float:itsY, Float:itsZ, Float:itsA, bool:removeold = false) {
    if (removeold == true) {
        DestroyVehicle(vInfo[vehicleid][vehSessionID]);
    }

    vInfo[vehicleid][vehSessionID] = CreateVehicle(vInfo[vehicleid][vehModel], itsX, itsY, itsZ, itsA, vInfo[vehicleid][vehColorOne], vInfo[vehicleid][vehColorTwo], -1);
    format(vInfo[vehicleid][vehName], MAX_PLAYER_NAME, GetVehicleName(vInfo[vehicleid][vehModel]));
    SetVehicleParamsEx(vInfo[vehicleid][vehSessionID], 0, 0, 0, 1, 0, 0, 0);
    SetVehicleNumberPlate(vInfo[vehicleid][vehSessionID], vInfo[vehicleid][vehPlate]);
    for(new x = 0; x < 14; x++) if(vInfo[vehicleid][vehMod][x] > 0) AddVehicleComponent(vInfo[vehicleid][vehSessionID], vInfo[vehicleid][vehMod][x]);
    ChangeVehicleColor(vInfo[vehicleid][vehSessionID], vInfo[vehicleid][vehColorOne], vInfo[vehicleid][vehColorTwo]);
    SetVehicleToRespawn(vInfo[vehicleid][vehSessionID]);
    return 1;
}

stock GetVehicleName(modelid) {
    new string[20];
    format(string,sizeof(string),"%s",VehicleNames[modelid - 400]);
    return string;
}

stock cNumber(integer, const separator[] = ",") { 
    new string[16]; 
    format(string, sizeof(string), "%i", integer);
    if (integer >= 1000) { 
        for (new i = (strlen(string) - 3); i > 0; i -= 3) { 

            strins(string, separator, i); 
        } 
    } 
    return string; 
}

stock ReturnVehicleModelID(const Name[]) {
    for (new i; i != 211; i++) if (strfind(VehicleNames[i], Name, true) != -1) return i + 400;
    return INVALID_VEHICLE_ID;
}

YCMD:buyvehicle(playerid, string:params[], help) {
    new id, string[100];
    if (sscanf(params, "i", id)) return SendSyntaxMessage(playerid, "/buyvehicle <VehicleID>");
    if (!Iter_Contains(ServerVehicles, id)) return SendErrorMessage(playerid, "{FFFFFF}รหัสรถไม่ถูกต้อง");
    if (!IsPlayerInRangeOfPoint(playerid, 2.0, vInfo[id][vehX], vInfo[id][vehY], vInfo[id][vehZ])) return 1;

    if (!strcmp(vInfo[id][vehOwner], "-")) {
        SetPVarInt(playerid, "buyVehicle", id);
        
        inline BuyVehicle(res, list, string:in[]) {
            #pragma unused list, in
            if (!res) @return 1;

            new i = GetPVarInt(playerid, "buyVehicle");
            if (GetPlayerMoneyEx(playerid) < vInfo[i][vehPrice]) return SendErrorMessage(playerid, "{FFFFFF}คุณมีเงินไม่พอ");
            if (strcmp(vInfo[i][vehOwner], "-")) return SendErrorMessage(playerid, "{FFFFFF}รถคันนี้เป็นของผู้เล่นอยู่แล้ว");

            DestroyDynamic3DTextLabel(vInfo[i][vehLabel]);
            SetVehicleToRespawn(vInfo[i][vehSessionID]);

            GivePlayerMoneyEx(playerid, -vInfo[i][vehPrice]);
            GetPlayerName(playerid, vInfo[i][vehOwner], MAX_PLAYER_NAME);

            SetVehicleParamsForPlayer(vInfo[i][vehSessionID], playerid, 0, 0);
            vInfo[i][vehLock] = MODE_NOLOCK;

            format(vInfo[i][vehOwner], MAX_PLAYER_NAME, ReturnPlayerName(playerid));

            Iter_Add(PrivateVehicles[playerid], i);
            SaveVehicle(i);
        }
        format(string, sizeof(string), "{FFFFFF}รถรุ่น: {00FF00}%s \n{FFFFFF}ราคา: {00FF00}$%s \n{FFFFFF}คุณต้องการซื้อหรือไม่", vInfo[id][vehName], cNumber(vInfo[id][vehPrice]));
        Dialog_ShowCallback(playerid, using inline BuyVehicle, DIALOG_STYLE_MSGBOX, "{FFFFFF}ซื้อรถส่วนตัว", string, "ซื้อ", "ไม่");
        return 1;
    }
    else return SendErrorMessage(playerid, "{FFFFFF}รถคันนี้เป็นของผู้เล่นอยู่แล้ว");
}

YCMD:vehicles(playerid, string:params[], help) {
    if (!IsPlayerAdminEx(playerid)) return 1;

    new bool:found = false, list_text[512];
    list_text = "ID\tVehicle\tNumber Plate\n";
    foreach (new i : PrivateVehicles[playerid]) {
        if (!strcmp(vInfo[i][vehOwner], ReturnPlayerName(playerid))) {
            found = true;
            format(list_text, sizeof(list_text), "%s%d\t%s\t%s\n", list_text, i, vInfo[i][vehName], vInfo[i][vehPlate]);
        }
    }

    inline Vehicle(res, list, string:in[]) {
        #pragma unused in
        if (!res) @return 1;

        new count = 0;
        foreach (new i : PrivateVehicles[playerid]) {
            if (!strcmp(vInfo[i][vehOwner], ReturnPlayerName(playerid))) {
                if (count == list) {
                    SetPVarInt(playerid, "playerVehID", i);

                    inline Vehicle2(res2, list2, string:in2[]) {
                        #pragma unused in2
                        if (!res2) @return 1;

                        switch (list2) {
                            case 0: {
                                GetPlayerPos(playerid, vInfo[i][vehX], vInfo[i][vehY], vInfo[i][vehZ]);
                                GetPlayerFacingAngle(playerid, vInfo[i][vehA]);

                                createVehicle(i, vInfo[i][vehX]+3, vInfo[i][vehY], vInfo[i][vehZ], vInfo[i][vehA], true);
                                SaveVehicle(i);
                            }
                            case 1: {
                                inline Vehicle3(res3, list3, string:in3[]) {
                                    #pragma unused list3
                                    if (!res3) @return 1;

                                    SetVehicleNumberPlate(vInfo[i][vehSessionID], in3);
                                    format(vInfo[i][vehPlate], 16, in3);

                                    SetVehicleToRespawn(vInfo[i][vehSessionID]);

                                    if (IsPlayerInVehicle(playerid, vInfo[i][vehSessionID])) {

                                        new Float:playerX, Float:playerY, Float:playerZ;
                                        GetPlayerPos(playerid, playerX, playerY, playerZ);

                                        SetVehiclePos(vInfo[i][vehSessionID], playerX, playerY, playerZ);
                                        PutPlayerInVehicle(playerid, vInfo[i][vehSessionID], 0);
                                    }

                                    SaveVehicle(i);
                                }
                                Dialog_ShowCallback(playerid, using inline Vehicle3, DIALOG_STYLE_INPUT, "{FFFFFF}ป้ายทะเบียนรถ", "{FFFFFF}กรอกหมายเลขทะเบียนรถใหม่ด้านล่าง", "ถัดไป", "ปิด");
                            }
                            case 2: {
                                foreach (new x : Player) if(x != playerid) SetVehicleParamsForPlayer(vInfo[i][vehSessionID], x, 0, 1);

                                vInfo[i][vehLock] = MODE_LOCK;
                                SaveVehicle(i);
                                SendCongratMessage(playerid, "{FFFFFF}คุณได้ล็อกรถของคุณแล้ว");
                            }
                            case 3: {
                                foreach (new x : Player) if(x != playerid) SetVehicleParamsForPlayer(vInfo[i][vehSessionID], x, 0, 0);
                                vInfo[i][vehLock] = MODE_NOLOCK;
                                SaveVehicle(i);
                                SendCongratMessage(playerid, "{FFFFFF}คุณได้ปลดล็อกรถของคุณแล้ว");
                            }
                            case 4: {
                                foreach (new x : Player) {
                                    if (IsPlayerInVehicle(x, vInfo[i][vehSessionID])) {
                                        RemovePlayerFromVehicle(x);
                                    }
                                }
                                SendCongratMessage(playerid, "{FFFFFF}คุณได้ไล่ผู้เล่นทั้งหมดออกจากรถของคุณแล้ว");
                            }
                        }
                    }
                    Dialog_ShowCallback(playerid, using inline Vehicle2, DIALOG_STYLE_LIST, "{FFFFFF}ยานพาหนะ", "เรียกรถ\nเปลี่ยนป้ายทะเบียน\nล็อค\nปลดล็อค\nไล่ผู้เล่นทั้งหมดออกจากรถ", "เลือก", "ปิด");
                    break;
                }
                else count++;
            }
        }
    }
    inline Empty(res, list, string:in[]) {
        #pragma unused list, in
        if (!res) @return 1;
        if (res) @return 1;
    }
    if(found == true) return Dialog_ShowCallback(playerid, using inline Vehicle, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}ยานพาหนะ", list_text, "เลือก", "ปิด");
    else return Dialog_ShowCallback(playerid, using inline Empty, DIALOG_STYLE_MSGBOX, "{FFFFFF}ยานพาหนะ", "{FF0000}ไม่พบยานพาหนะ", "ปิด", "");
}

YCMD:changeplate(playerid, string:params[], help) {
    new txt[16];
    if (sscanf(params, "s[16]", txt)) return SendSyntaxMessage(playerid, "/changeplate <Text>");
    if (strlen(txt) > 16) return SendErrorMessage(playerid, "{FFFFFF}ข้อความที่ป้อนยาวเกินไป");
    if (!IsPlayerInAnyVehicle(playerid)) return SendErrorMessage(playerid, "{FFFFFF}คุณไม่ได้อยู่ภายในยานพาหนะใดๆ");
    if (GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) return SendErrorMessage(playerid, "{FFFFFF}คุณต้องเป็นผู้ขับขี่จึงจะสามารถใช้คำสั่งนี้ได้");

    foreach(new i : PrivateVehicles[playerid]) {
        if(IsPlayerInVehicle(playerid, vInfo[i][vehSessionID])) {
            if(!strcmp(vInfo[i][vehOwner], ReturnPlayerName(playerid))) { 
                SetVehicleNumberPlate(vInfo[i][vehSessionID], txt);
                vInfo[i][vehPlate] = txt;

                new Float:playerX, Float:playerY, Float:playerZ;
                GetPlayerPos(playerid, playerX, playerY, playerZ);

                SetVehicleToRespawn(vInfo[i][vehSessionID]);
                SetVehiclePos(vInfo[i][vehSessionID], playerX, playerY, playerZ);
                PutPlayerInVehicle(playerid, vInfo[i][vehSessionID], 0);

                SaveVehicle(i);
            }
            else return SendErrorMessage(playerid, "{FFFFFF}คุณไม่ใช่เจ้าของรถคันนี้");
        }
    }

    SendCongratMessage(playerid, "{FFFFFF}คุณได้เปลี่ยนป้ายทะเบียนรถของคุณแล้ว");
    return 1;
}

YCMD:lock(playerid, string:params[], help) {
    if (isnull(params)) {
        foreach (new i : ServerVehicles) {
            if (IsPlayerInVehicle(playerid, vInfo[i][vehSessionID])) {
                if (!strcmp(vInfo[i][vehOwner], ReturnPlayerName(playerid))) {
                    foreach (new x : Player) if(x != playerid) SetVehicleParamsForPlayer(vInfo[i][vehSessionID], x, 0, 1);

                    GameTextForPlayer(playerid, "~w~LOCKED", 2000, 3);
                    vInfo[i][vehLock] = MODE_LOCK;
                    SaveVehicle(i);
                }
                else return SendErrorMessage(playerid, "{FFFFFF}คุณไม่ใช่เจ้าของรถคันนี้");
            }
        }
        return 1;
    }

    new id;
    if (sscanf(params, "i", id)) return SendSyntaxMessage(playerid, "/unlock <VehicleID>");
    if (!Iter_Contains(ServerVehicles, id)) return SendErrorMessage(playerid, "{FFFFFF}รหัสรถไม่ถูกต้อง");
    if (strcmp(vInfo[id][vehOwner], ReturnPlayerName(playerid))) return SendErrorMessage(playerid, "{FFFFFF}คุณไม่ใช่เจ้าของรถคันนี้");

    if (vInfo[id][vehLock] == MODE_NOLOCK) {

        foreach(new x : Player) if(x != playerid) SetVehicleParamsForPlayer(vInfo[id][vehSessionID], x, 0, 1);

        GameTextForPlayer(playerid, "~w~LOCKED", 2000, 3);
        vInfo[id][vehLock] = MODE_LOCK;
        SaveVehicle(id);
        return 1;
    }
    else return SendWarningMessage(playerid, "{FFFFFF}รถถูกล็อกไว้เรียบร้อยแล้ว");
}

YCMD:unlock(playerid, string:params[], help) {
    if (isnull(params)){
        foreach (new i : ServerVehicles) {
            if (IsPlayerInVehicle(playerid, vInfo[i][vehSessionID])) {
                if(!strcmp(vInfo[i][vehOwner], ReturnPlayerName(playerid))) {
                    foreach (new x : Player) if(x != playerid) SetVehicleParamsForPlayer(vInfo[i][vehSessionID], x, 0, 0);

                    GameTextForPlayer(playerid, "~w~UNLOCKED", 2000, 3);
                    vInfo[i][vehLock] = MODE_NOLOCK;
                    SaveVehicle(i);
                }
                else return SendErrorMessage(playerid, "{FFFFFF}คุณไม่ใช่เจ้าของรถคันนี้");
            }
        }
        return 1;
    }

    new id;
    if (sscanf(params, "i", id)) return SendSyntaxMessage(playerid, "/unlock <VehicleID>");
    if (!Iter_Contains(ServerVehicles, id)) return SendErrorMessage(playerid, "{FFFFFF}รหัสรถไม่ถูกต้อง");
    if (strcmp(vInfo[id][vehOwner], ReturnPlayerName(playerid))) return SendErrorMessage(playerid, "{FFFFFF}คุณไม่ใช่เจ้าของรถคันนี้");

    if(vInfo[id][vehLock] == MODE_LOCK) {

        foreach(new x : Player) if(x != playerid) SetVehicleParamsForPlayer(vInfo[id][vehSessionID], x, 0, 0);

        GameTextForPlayer(playerid, "~w~UNLOCKED", 2000, 3);
        vInfo[id][vehLock] = MODE_NOLOCK;
        SaveVehicle(id);
        return 1;
    }
    else return SendWarningMessage(playerid, "{FFFFFF}ยานพาหนะได้รับการปลดล็อกแล้ว");
}

YCMD:createvehicle(playerid, string:params[], help) {
    if (!IsPlayerAdminEx(playerid)) return 1;

    new modelid[30], vehid, color1, color2, price;
    if (sscanf(params, "s[30]iid", modelid, color1, color2, price)) return SendSyntaxMessage(playerid, "/createvehicle <ModelID/Vehicle Name> <Color1> <Color2> <Price>");

    if (IsNumeric(modelid)) vehid = strval(modelid);
    else vehid = ReturnVehicleModelID(modelid);

    if (vehid < 400 || vehid > 611) return SendErrorMessage(playerid, "{FFFFFF}รุ่นรถไม่ถูกต้อง!");

    new index = Iter_Free(ServerVehicles);
    if (index == -1) return SendErrorMessage(playerid, "{FFFFFF}คุณไม่สามารถสร้างยานพาหนะเพิ่มได้!");

    if (IsPlayerInAnyVehicle(playerid)) DestroyVehicle(GetPlayerVehicleID(playerid));

    GetPlayerPos(playerid, vInfo[index][vehX], vInfo[index][vehY], vInfo[index][vehZ]);
    GetPlayerFacingAngle(playerid, vInfo[index][vehA]);

    SetPlayerPos(playerid, vInfo[index][vehX] + 3, vInfo[index][vehY], vInfo[index][vehZ]);

    vInfo[index][vehSessionID] = CreateVehicle(vehid, vInfo[index][vehX], vInfo[index][vehY], vInfo[index][vehZ], vInfo[index][vehA], color1, color2, 10);
    SetVehicleParamsEx(vInfo[index][vehSessionID], 0, 0, 0, 1, 0, 0, 0);
    SetVehicleNumberPlate(vInfo[index][vehSessionID], "CC");

    format(vInfo[index][vehName], MAX_PLAYER_NAME, GetVehicleName(vehid));
    format(vInfo[index][vehOwner], MAX_PLAYER_NAME, "-");
    format(vInfo[index][vehPlate], 16, "CC");

    vInfo[index][vehModel] = vehid;
    vInfo[index][vehPrice] = price;
    vInfo[index][vehLock] = MODE_LOCK;
    vInfo[index][vehColorOne] = color1;
    vInfo[index][vehColorTwo] = color2;

    new query[220];
    format(query, sizeof(query), VEHICLE_BUY_TEXT, vInfo[index][vehName], cNumber(vInfo[index][vehPrice]));

    vInfo[index][vehLabel] = CreateDynamic3DTextLabel(query, 0xFFFF00FF, vInfo[index][vehX], vInfo[index][vehY], vInfo[index][vehZ], 10.0, INVALID_PLAYER_ID, vInfo[index][vehSessionID]);

    
    mysql_format(get_handle(), query, sizeof(query),
    "INSERT INTO "VEHICLE_TABLE" (vehModel, vehPrice, vehName, vehPlate, vehColorOne, vehColorTwo, vehX, vehY, vehZ, vehA) VALUES (%d, %d, '%e', '%e', %d, %d, %f, %f, %f, %f)",
    vInfo[index][vehModel], vInfo[index][vehPrice], vInfo[index][vehName], vInfo[index][vehPlate], vInfo[index][vehColorOne], vInfo[index][vehColorTwo], vInfo[index][vehX], 
    vInfo[index][vehY], vInfo[index][vehZ], vInfo[index][vehA]);
    mysql_tquery(get_handle(), query, "OnDealerVehicleCreated", "i", index);

    SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ได้สร้างยานพาหนะ - ModelID: %d, VehicleID: %d, ราคา: %d", ReturnPlayerName(playerid), vInfo[index][vehModel], index, vInfo[index][vehPrice]);
    return 1;
}

CMD:gotovehicle(playerid, params[]) {
    if (!IsPlayerAdminEx(playerid)) return 1;

    new id;
    if (sscanf(params, "i", id)) return SendSyntaxMessage(playerid, "/gotovehicle <VehicleID>");
    if (!Iter_Contains(ServerVehicles, id)) return SendErrorMessage(playerid, "{FFFFFF}รหัสรถไม่ถูกต้อง");

    GetVehiclePos(vInfo[id][vehSessionID], vInfo[id][vehX], vInfo[id][vehY], vInfo[id][vehZ]);

    SetPlayerPos(playerid, vInfo[id][vehX], vInfo[id][vehY], vInfo[id][vehZ]+3);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
    return 1;
}

CMD:setvehicleprice(playerid, params[]) {
    if (!IsPlayerAdminEx(playerid)) return 1;
    
    new id, price;
    if (sscanf(params, "ii", id, price)) return SendSyntaxMessage(playerid, "/setvehicleprice <VehicleID> <Price>");
    if (!Iter_Contains(ServerVehicles, id)) return SendErrorMessage(playerid, "{FFFFFF}รหัสรถไม่ถูกต้อง");

    new query[64];
    mysql_format(get_handle(), query, sizeof(query), "UPDATE "VEHICLE_TABLE" SET `vehPrice` = %i WHERE `vehID` = %d", price, vInfo[id][vehID]);
    mysql_tquery(get_handle(), query);

    SendAdminMessage(COLOR_ADMIN, "AdmLog: %s Price updated VID: %d, Price: %d", vInfo[id][vehID], price);
    return 1;
}

CMD:deletevehicle(playerid, params[]) {
    if (!IsPlayerAdminEx(playerid)) return 1;

    new id;
    if (sscanf(params, "i", id)) return SendSyntaxMessage(playerid, "/deletevehicle <VehicleID>");
    if (!Iter_Contains(ServerVehicles, id)) return SendErrorMessage(playerid, "{FFFFFF}รหัสรถไม่ถูกต้อง");

    ResetVehicle(id);

    Iter_Remove(ServerVehicles, id);

    SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ลบยานพาหนะแล้ว VID: %d", vInfo[id][vehID]);
    
    new query[45];
    mysql_format(get_handle(), query, sizeof(query), "DELETE FROM "VEHICLE_TABLE" WHERE `vehID` = %d", vInfo[id][vehID]);
    mysql_tquery(get_handle(), query);
    return 1;
}
