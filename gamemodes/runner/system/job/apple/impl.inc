#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
	for (new i = 0; i < sizeof(AppleData); i++) {
		AppleData[i][appleID] = CreateDynamicObject(AppleData[i][appleObject], AppleData[i][applePosX], AppleData[i][applePosY], AppleData[i][applePosZ], 0.0, 0.0, 0.0);
		AppleData[i][appleText3D] = CreateDynamic3DTextLabel(AppleData[i][Apple3DText], COLOR_GREEN, AppleData[i][applePosX], AppleData[i][applePosY], AppleData[i][applePosZ] + 1.5, 5.0);
	}
	CreateDynamicPickup(1239, 23, 1227.9988,-2362.9695,10.7937);
	CreateDynamic3DTextLabel("[ Apple ]\n{FFFFFF}กดปุ่ม N เพื่อสมัครงาน", COLOR_GREEN, 1227.9988,-2362.9695,10.7937, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1);

	CreateDynamicPickup(1239, 23, 1124.1536,-1438.8242,15.7969);
	CreateDynamic3DTextLabel("[ Market ]\n{FFFFFF}กดปุ่ม N เพื่อขายน้ำแอปเปิ้ล", COLOR_GREEN, 1124.1536,-1438.8242,15.7969, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1);

	CreateDynamicPickup(1239, 23, 1214.5134,-2368.9109,10.7937);
	CreateDynamic3DTextLabel("[ Procress ]\n{FFFFFF}กดปุ่ม N เพื่อแปรรูปแอปเปิ้ล", COLOR_GREEN, 1214.5134,-2368.9109,10.7937, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1);
    AppleMapping();

    CreateDynamic3DTextLabel("กด {00ffff}N{ffffff} เพื่อขายแอปเปิ้ล", 0xFFFFFFFF, 1596.1569,1789.4802,10.8047, 8.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1);
    CreateDynamicPickup(1274, 23, 1596.1569,1789.4802,10.8047);
    return true;
}

hook OnPlayerConnect(playerid) {
    //AppleStart[playerid] = 0;
    return true;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if (newkeys & KEY_NO && !IsPlayerInAnyVehicle(playerid)) {
        if (IsPlayerInRangeOfPoint(playerid, 2.5, 1596.1569,1789.4802,10.8047)) {
			new wood = Player.Auth[playerid][@itemapplefruit];

			new string[256];

			format(string, sizeof(string), "คุณมีน้ำแอปเปิ้ลจำนวน: [%d]\nราคาปัจจุบัน: 1 ชิ้น/%s\n- กรอกจำนวนที่จะขายด้านล่าง:", wood, FormatMoney(MarketPrice[0]));
			Dialog_Show(playerid, DIALOG_SELL_APPLE, DIALOG_STYLE_INPUT, "ขายน้ำแอปเปิ้ล", string, "ตกลง", "ยกเลิก");

            /*new string[256];

			format(string, sizeof(string), "ราคาปัจจุบัน: 1 ชิ้น/50\n- กรอกจำนวนที่จะขายด้านล่าง:");
			Dialog_Show(playerid, DIALOG_SELL_LUMBERJACK, DIALOG_STYLE_INPUT, "ขายไม้แปรรูป", string, "ตกลง", "ยกเลิก");*/
        }

		if (IsPlayerInRangeOfPoint(playerid, 3.5, 1214.5134,-2368.9109,10.7937)) {
            if (AppleStart[playerid] == 0)
                return SendErrorMessage(playerid, "คุณต้องเริ่มงานก่อน");

            if (AppleProcress[playerid] == 0) {
                new amount = Player.Auth[playerid][@itemapple];
                if (amount <= 2) return SendClientMessageEx(playerid, COLOR_RED, "[ERROR] คุณต้องมี 'ผลแอปเปิ้ล' 2 ชิ้นขึ้นไปสำหรับการแปรรูป!");

                AppleProcress[playerid] = 1;
                TogglePlayerControllable(playerid, false);
                ApplyAnimation(playerid, "BD_FIRE", "WASH_UP", 4.0, 1, 0, 0, 0, 0, 1);
                
                StartProgress(playerid, 150, 0, 0);
                SendClientMessage(playerid, COLOR_RED, "[INFO] {FFFFFF}หากต้องการยกเลิก กด 'N' อีกครั้ง");
                return true;
            } else {
                AppleProcress[playerid] = 0;
                TogglePlayerControllable(playerid, true);

                SendClientMessage(playerid, COLOR_RED, "[INFO] {FFFFFF}คุณได้ยกเลิกการแปรรูปแล้ว");
                StopProgress(playerid);
            }
        }
	}
    if (newkeys & KEY_NO) {
        if (IsPlayerInRangeOfPoint(playerid, 2.5, 1124.1536,-1438.8242,15.7969)) {
            Dialog_Show(playerid, DIALOG_SELLRAREAPPLE, DIALOG_STYLE_TABLIST_HEADERS, "[รายการรับซื้อ]", "ชื่อรายการ\tราคา\nน้ำแอปเปิ้ล\t{00FF00}32", "ขาย", "ออก");
        }
        if (IsPlayerInRangeOfPoint(playerid, 3.0, 1227.9988,-2362.9695,10.0103)) {
            ShowJobInApple(playerid);
        }
        for (new i = 0; i < sizeof AppleData; i ++) {
            if (IsPlayerInRangeOfPoint(playerid, 4.0, AppleData[i][applePosX], AppleData[i][applePosY], AppleData[i][applePosZ])) {
                if (AppleStart[playerid] == 0)
                    return SendErrorMessage(playerid, "คุณต้องเริ่มงานก่อน");

                OP_PlayerStartCircleProgressbar(playerid, 250, 0x00FFFFFF, "AppleJobFinish");
                //StartProgress(playerid, 150, 0, 0);
                ApplePick[playerid] = 1;
                ApplyAnimation(playerid,"OTB","wtchrace_win",4.1,1,0,1,1,0,1);
                TogglePlayerControllable(playerid, 0);
            }
        }
        return true;
	}
    return true;
}

Dialog:AppleJobIn(playerid, response, listitem, inputtext[]) {
    if (response) {
        switch (listitem) {
            case 0: {
                if (AppleStart[playerid] == 1)
                    return ErrorMsg(playerid, "คุณอยู่ในงานนี้อยู่แล้ว ไม่จำเป็นต้องสมัคร");

                AppleStart[playerid] = 1;
                SaveOldSkin(playerid);
                SetPlayerSkin(playerid, 133);
                JobMsg(playerid, "คุณได้ทำการเข้ารับงานตัดไม้แล้ว!");

                SetPlayerAttachedObject(playerid, 1, 1235,1,0.085000,-0.326999,0.005999,135.699935,89.900070,-31.199995,0.741000,0.748000,0.879999);
            }
            case 1: {
                if (AppleStart[playerid] == 0)
                    return ErrorMsg(playerid, "คุณไม่ได้อยู่ในงานอยู่แล้ว ไม่จำเป็นต้องออกจากงาน");

                AppleStart[playerid] = 0;

                if (Player.Auth[playerid][@Oldskin] == 0) {
                    return SetPlayerSkin(playerid, Player.Auth[playerid][@skin]);
                }

                RemovePlayerAttachedObject(playerid, 1);
                /*RemovePlayerAttachedObject(playerid, 2);
                RemovePlayerAttachedObject(playerid, 3);
                RemovePlayerAttachedObject(playerid, 4);*/

                SetPlayerSkin(playerid, Player.Auth[playerid][@Oldskin]);
                JobMsg(playerid, "คุณได้ทำการออกจากรับงานแอปเปิ้ลแล้ว!");
            }
        }
    }

    return true;
}

Dialog:DIALOG_SELL_APPLE(playerid, response, listitem, inputtext[]) {
    if (response) {
        new amount = strval(inputtext);
        new price = amount*MarketPrice[0];

        if (amount <= 0 ||amount > Player.Auth[playerid][@itemapplefruit])
            return ErrorMsg(playerid, "คุณมีน้ำแอปเปิ้ลไม่เพียงพอ");

        Player.Auth[playerid][@itemapplefruit] -= amount;
        GivePlayerMoneyEx(playerid, price);
        SendClientMessageEx(playerid, COLOR_YELLOW, "[ขายน้ำแอปเปิ้ล]: คุณได้ขายน้ำแอปเปิ้ล จำนวน %d และได้รับเงิน %s", amount, FormatNumber(price));
	}
    return true;
}

hook OnProgressUpdate(playerid, progress, objectid) {
	if (ApplePick[playerid] == 1) {
	    ApplyAnimation(playerid,"OTB","wtchrace_win",4.1,1,0,1,1,0,1);
		return Y_HOOKS_BREAK_RETURN_1;
	}
    if (AppleProcress[playerid] == 1) {
        ApplyAnimation(playerid, "BD_FIRE", "WASH_UP", 4.0, 1, 0, 0, 0, 0, 1);
    }
	return Y_HOOKS_CONTINUE_RETURN_0;
}

hook OnProgressFinish(playerid, objectid) {
	if (ApplePick[playerid] == 1) {
        AppleCount[playerid] +=1;

        new string[256];
        format(string, sizeof(string), "เก็บแอปเปิ้ลสำเสร็จ [%d/10]", AppleCount[playerid]);

        Player.Auth[playerid][@itemapple] += 1;
        SendClientMessage(playerid, COLOR_RED, "[ เก็บผลแอปเปิ้ล ] {FFFFFF}คุณได้รับผลแอปเปิ้ล +1");

        for (new i = 0; i < sizeof(AppleData); i ++) {       
            AppleData[i][AppleAmount] -= 1;
            UpdateDynamic3DTextLabelText(AppleData[i][appleText3D], COLOR_GREEN, sprintf("[Apple Growers]\n{FFFFFF}กด N เพื่อเก็บน้ำแอปเปิ้ล\n{FFE200}จำนวน %d ลูก", AppleData[i][AppleAmount]));
            if (AppleData[i][AppleAmount] <= 0) {
                DestroyDynamicObject(AppleData[i][appleID]);
                DestroyDynamic3DTextLabel(AppleData[i][appleText3D]);
                defer AppleTimerReset(i);
            }
        }
        if (AppleCount[playerid] == 1) {
            SetPlayerAttachedObject(playerid, 2, 19575,1,-0.261000,-0.357999,-0.061999,0.000000,92.200012,0.000000,1.647000,1.453999,1.437000);
        } else if (AppleCount[playerid] == 2) {
            SetPlayerAttachedObject(playerid, 3,19575,1,-0.179999,-0.333000,0.068999,0.000000,94.000007,0.000000,1.892999,1.894998,1.431000);
        } else if (AppleCount[playerid] == 3) {
            SetPlayerAttachedObject(playerid, 4,19575,1,-0.065000,-0.351999,0.070000,0.000000,98.000000,0.000000,1.532000,1.443000,1.163999);
        } else if (AppleCount[playerid] == 4) {
            SetPlayerAttachedObject(playerid, 5,19575,1,-0.138999,-0.270000,-0.062999,0.000000,82.000030,0.000000,1.723999,1.628000,1.461000);
        } else if (AppleCount[playerid] == 5) {
            SetPlayerAttachedObject(playerid, 6,19575,1,-0.055999,-0.212999,0.040000,0.000000,85.999969,0.000000,1.797000,1.670000,1.583000);
        } else if (AppleCount[playerid] == 6) {
            SetPlayerAttachedObject(playerid, 7,19575,1,-0.144999,-0.427000,-0.035999,0.000000,98.600006,0.000000,1.354000,1.186000,1.146000);
        } else if (AppleCount[playerid] == 7) {
            SetPlayerAttachedObject(playerid, 8,19575,1,-0.056999,-0.381999,-0.081000,0.000000,87.700004,0.000000,1.458000,1.447999,1.156999);
        }
        ApplePick[playerid] = 0;
    }
    if (AppleProcress[playerid] == 1) {
        new amount = Player.Auth[playerid][@itemapple];
        if (amount < 2) {
            SendClientMessageEx(playerid, COLOR_RED, "[ERROR] {FFFFFF}คุณมี 'ผลแอปเปิ้ล' ไม่พอสำหรับการคัดแยก");
            TogglePlayerControllable(playerid, true);
            AppleProcress[playerid] = 0;
            return true;
        } else {
            //Inventory_Remove(playerid, "ผลแอปเปิ้ล", 2);
            //Inventory_Add(playerid, "น้ำแอปเปิ้ล", 1);
            Player.Auth[playerid][@itemapple] -= 2;
            Player.Auth[playerid][@itemapplefruit] += 1;
			SendClientMessage(playerid, 0xAFAFAFF, "|==========================================|");
			SendClientMessage(playerid, -1, "{0469C8}[!] {FFFFFF}คุณได้เสีย (ผลแอปเปิ้ล) - 2");
			SendClientMessage(playerid, -1, "{0469C8}[!] {FFFFFF}คุณได้รับ (น้ำแอปเปิ้ล) + 1");
			SendClientMessage(playerid, -1, "{0469C8}[!] {FFFFFF}คุณได้รับ (Exp) + 3");
			SendClientMessage(playerid, 0xAFAFAFF, "|==========================================|");
            StartProgress(playerid, 150, 0, 0);
            AppleCount[playerid] -= 1;

            if (AppleCount[playerid] == 1) {
                RemovePlayerAttachedObject(playerid, 2);
            } else if (AppleCount[playerid] == 2) {
                RemovePlayerAttachedObject(playerid, 3);
            } else if (AppleCount[playerid] == 3) {
                RemovePlayerAttachedObject(playerid, 4);
            } else if (AppleCount[playerid] == 4) {
                RemovePlayerAttachedObject(playerid, 5);
            } else if (AppleCount[playerid] == 5) {
                RemovePlayerAttachedObject(playerid, 6);
            } else if (AppleCount[playerid] == 6) {
                RemovePlayerAttachedObject(playerid, 7);
            } else if (AppleCount[playerid] == 7) {
                RemovePlayerAttachedObject(playerid, 8);
            }
        }
    }
	return Y_HOOKS_CONTINUE_RETURN_0;
}

forward AppleJobFinish(playerid);
public AppleJobFinish(playerid) {
    AppleCount[playerid] +=1;
    TogglePlayerControllable(playerid, 1);

    new string[256];
    
    format(string, sizeof(string), "เก็บแอปเปิ้ลสำเสร็จ [%d/10]", AppleCount[playerid]);
    SendClientMessage(playerid, 0xFFFFFFFF, string);

    Player.Auth[playerid][@itemapple] += 1;
    SendClientMessage(playerid, COLOR_RED, "[ เก็บผลแอปเปิ้ล ] {FFFFFF}คุณได้รับผลแอปเปิ้ล +1");

    for (new i = 0; i < sizeof(AppleData); i ++) {       
        AppleData[i][AppleAmount] -= 1;
        UpdateDynamic3DTextLabelText(AppleData[i][appleText3D], COLOR_GREEN, sprintf("[Apple Growers]\n{FFFFFF}กด N เพื่อเก็บน้ำแอปเปิ้ล\n{FFE200}จำนวน %d ลูก", AppleData[i][AppleAmount]));
        if (AppleData[i][AppleAmount] <= 0) {
            DestroyDynamicObject(AppleData[i][appleID]);
            DestroyDynamic3DTextLabel(AppleData[i][appleText3D]);
            defer AppleTimerReset(i);
        }
    }
    if (AppleCount[playerid] == 1) {
        SetPlayerAttachedObject(playerid, 2, 19575,1,-0.261000,-0.357999,-0.061999,0.000000,92.200012,0.000000,1.647000,1.453999,1.437000);
    } else if (AppleCount[playerid] == 2) {
        SetPlayerAttachedObject(playerid, 3,19575,1,-0.179999,-0.333000,0.068999,0.000000,94.000007,0.000000,1.892999,1.894998,1.431000);
    } else if (AppleCount[playerid] == 3) {
        SetPlayerAttachedObject(playerid, 4,19575,1,-0.065000,-0.351999,0.070000,0.000000,98.000000,0.000000,1.532000,1.443000,1.163999);
    } else if (AppleCount[playerid] == 4) {
        SetPlayerAttachedObject(playerid, 5,19575,1,-0.138999,-0.270000,-0.062999,0.000000,82.000030,0.000000,1.723999,1.628000,1.461000);
    } else if (AppleCount[playerid] == 5) {
        SetPlayerAttachedObject(playerid, 6,19575,1,-0.055999,-0.212999,0.040000,0.000000,85.999969,0.000000,1.797000,1.670000,1.583000);
    } else if (AppleCount[playerid] == 6) {
        SetPlayerAttachedObject(playerid, 7,19575,1,-0.144999,-0.427000,-0.035999,0.000000,98.600006,0.000000,1.354000,1.186000,1.146000);
    } else if (AppleCount[playerid] == 7) {
        SetPlayerAttachedObject(playerid, 8,19575,1,-0.056999,-0.381999,-0.081000,0.000000,87.700004,0.000000,1.458000,1.447999,1.156999);
    }
    ApplePick[playerid] = 0;
    return true;
}

stock AppleMapping() {
    CreateDynamicObject(18981, 1245.19897, -2358.84155, 9.29366,   0.00000, 90.00000, 3.30000);
    CreateDynamicObject(18981, 1223.89172, -2361.92041, 9.29366,   0.00000, 90.00000, 15.78000);
    CreateDynamicObject(18981, 1212.92627, -2373.77515, 9.29366,   0.00000, 90.00000, 68.82001);
    CreateDynamicObject(18981, 1212.46619, -2391.65991, 9.29366,   0.00000, 90.00000, 89.94000);
    CreateDynamicObject(18981, 1227.33386, -2401.55493, 9.29366,   0.00000, 90.00000, 65.88000);
    CreateDynamicObject(18981, 1244.70093, -2403.56274, 9.29366,   0.00000, 90.00000, 11.28000);
    CreateDynamicObject(18981, 1260.31567, -2395.57471, 9.29366,   0.00000, 90.00000, 37.38000);
    CreateDynamicObject(18981, 1271.48267, -2384.39795, 9.29366,   0.00000, 90.00000, 4.56001);
    CreateDynamicObject(18981, 1250.11072, -2377.61987, 9.29366,   0.00000, 90.00000, 4.56001);
    CreateDynamicObject(18981, 1234.47473, -2381.53027, 9.29366,   0.00000, 90.00000, 4.56001);
    CreateDynamicObject(18981, 1263.43433, -2365.22559, 9.29366,   0.00000, 90.00000, 31.32001);
    CreateDynamicObject(12921, 1245.94971, -2415.16357, 13.31951,   0.00000, 0.00000, 7.98000);
    CreateDynamicObject(18766, 1225.32495, -2404.34619, 9.35930,   90.00000, 180.00000, -56.80000);
    CreateDynamicObject(18766, 1220.24353, -2396.58154, 9.35930,   90.00000, 180.00000, -56.80000);
    CreateDynamicObject(18766, 1214.97021, -2388.52368, 9.35930,   90.00000, 180.00000, -56.80000);
    CreateDynamicObject(18766, 1222.97986, -2405.81543, 9.35930,   90.00000, 180.00000, -44.30001);
    CreateDynamicObject(18766, 1216.41699, -2399.41089, 9.35930,   90.00000, 180.00000, -44.30001);
    CreateDynamicObject(18766, 1214.47754, -2397.51855, 9.35930,   90.00000, 180.00000, -44.30001);
    CreateDynamicObject(18766, 1213.58997, -2393.95264, 9.35930,   90.00000, 180.00000, -56.80001);
    CreateDynamicObject(18766, 1211.14954, -2390.36621, 9.35930,   90.00000, 180.00000, -89.20000);
    CreateDynamicObject(18766, 1211.13452, -2389.29517, 9.35930,   90.00000, 180.00000, -89.20000);
    CreateDynamicObject(17060, 1264.35535, -2361.29639, 9.55392,   0.00000, 0.00000, -58.07999);
    CreateDynamicObject(17060, 1260.66003, -2361.75000, 9.55392,   0.00000, 0.00000, -58.07999);
    CreateDynamicObject(17060, 1255.53479, -2362.82861, 9.55392,   0.00000, 0.00000, -58.07999);
    CreateDynamicObject(17060, 1271.01306, -2377.04272, 9.55392,   0.00000, 0.00000, -69.89999);
    CreateDynamicObject(17060, 1267.26343, -2377.42920, 9.55392,   0.00000, 0.00000, -69.89999);
    CreateDynamicObject(17060, 1263.00049, -2377.50342, 9.55392,   0.00000, 0.00000, -69.89999);
    CreateDynamicObject(17060, 1270.29480, -2392.20435, 9.55392,   0.00000, 0.00000, -110.99998);
    CreateDynamicObject(17060, 1264.01550, -2390.37964, 9.55392,   0.00000, 0.00000, -110.99998);
    CreateDynamicObject(776, 1285.18176, -2391.62402, 11.54077,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(776, 1278.72729, -2403.20117, 11.54077,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(776, 1271.47546, -2410.41040, 11.54077,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(776, 1261.45471, -2414.47119, 11.54077,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(776, 1230.70032, -2417.82813, 9.26077,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(776, 1220.87134, -2412.61060, 9.05077,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(776, 1210.91162, -2406.45142, 9.53077,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(776, 1202.24194, -2398.87183, 9.97077,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(776, 1196.23804, -2389.53784, 10.32077,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(776, 1195.13940, -2379.13062, 10.69077,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(776, 1196.67615, -2368.50806, 11.54077,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(776, 1203.98792, -2355.24902, 11.03067,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(776, 1216.51611, -2348.92505, 11.03067,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(776, 1227.67786, -2345.59985, 11.03067,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(776, 1239.23218, -2345.22339, 11.03067,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(3359, 1213.68701, -2370.18604, 9.36759,   0.00000, 0.00000, 63.17999);
    CreateDynamicObject(3374, 1210.41785, -2372.06812, 11.00440,   0.00000, 0.00000, -20.10001);
    CreateDynamicObject(3374, 1214.25793, -2374.01172, 11.00440,   0.00000, 0.00000, -25.38001);
    CreateDynamicObject(10829, 1225.26965, -2358.26221, 9.61813,   0.00000, 0.00000, 17.94000);
    CreateDynamicObject(1457, 1233.96387, -2359.29785, 11.27471,   0.00000, 0.00000, 4.98000);
    CreateDynamicObject(2007, 1234.57898, -2358.05396, 9.79089,   0.00000, 0.00000, 0.48000);
    CreateDynamicObject(2007, 1233.48047, -2358.11816, 9.79089,   0.00000, 0.00000, 8.16000);
    CreateDynamicObject(2007, 1233.11023, -2359.03076, 9.79089,   0.00000, 0.00000, 96.84000);
    CreateDynamicObject(2007, 1234.77979, -2359.00513, 9.79089,   0.00000, 0.00000, -74.93999);
    CreateDynamicObject(2007, 1233.27026, -2360.15942, 9.79089,   0.00000, 0.00000, 96.84000);
    CreateDynamicObject(2007, 1234.93970, -2360.29541, 9.79089,   0.00000, 0.00000, -81.06004);
    CreateDynamicObject(19865, 1237.22400, -2349.32959, 9.57027,   0.00000, 0.00000, 3.24000);
    CreateDynamicObject(19865, 1237.50500, -2354.01123, 9.57027,   0.00000, 0.00000, 3.24000);
    CreateDynamicObject(19865, 1237.77380, -2358.63159, 9.57027,   0.00000, 0.00000, 3.24000);
    CreateDynamicObject(19865, 1237.93201, -2361.86499, 9.57027,   0.00000, 0.00000, 3.24000);
    CreateDynamicObject(19865, 1235.66833, -2364.56372, 9.57027,   0.00000, 0.00000, -83.22000);
    CreateDynamicObject(19865, 1227.13367, -2367.06396, 9.57027,   0.00000, 0.00000, -68.28001);
    CreateDynamicObject(19865, 1223.66724, -2365.83569, 9.57027,   0.00000, 0.00000, -151.37996);
    CreateDynamicObject(19865, 1221.39453, -2361.59375, 9.57027,   0.00000, 0.00000, -151.37996);
    CreateDynamicObject(19865, 1219.14624, -2357.46704, 9.57027,   0.00000, 0.00000, -151.37996);
    CreateDynamicObject(19865, 1217.47986, -2354.42554, 9.57027,   0.00000, 0.00000, -151.37996);
    CreateDynamicObject(19865, 1216.75073, -2353.03589, 9.57027,   0.00000, 0.00000, -151.37996);
    CreateDynamicObject(1408, 1210.70886, -2384.73315, 9.98078,   0.00000, 0.00000, -162.00005);
    CreateDynamicObject(1408, 1208.49072, -2388.04272, 9.98078,   0.00000, 0.00000, -84.90005);
    CreateDynamicObject(1408, 1209.46558, -2393.15430, 9.98078,   0.00000, 0.00000, -72.90005);
    CreateDynamicObject(1408, 1212.01843, -2397.60254, 9.98078,   0.00000, 0.00000, -45.60006);
    CreateDynamicObject(1408, 1215.70264, -2401.37476, 9.98078,   0.00000, 0.00000, -45.60006);
    CreateDynamicObject(1408, 1219.34302, -2405.15039, 9.98078,   0.00000, 0.00000, -45.60006);
    CreateDynamicObject(1408, 1223.35229, -2408.46533, 9.98078,   0.00000, 0.00000, -34.38006);
    CreateDynamicObject(1408, 1227.65564, -2408.56372, 9.98078,   0.00000, 0.00000, 32.75994);
    CreateDynamicObject(5836, 1237.69702, -2389.36963, 13.22274,   0.00000, 0.00000, -52.80000);
    return true;
}

timer AppleTimerReset[APPLE_TIME*1000](number) {
    if (AppleData[number][AppleAmount] <= 0) {
        AppleData[number][appleID] = CreateDynamicObject(AppleData[number][appleObject], AppleData[number][applePosX], AppleData[number][applePosY], AppleData[number][applePosZ], 0.0, 0.0, 0.0);
        AppleData[number][appleText3D] = CreateDynamic3DTextLabel(AppleData[number][Apple3DText], COLOR_GREEN, AppleData[number][applePosX], AppleData[number][applePosY], AppleData[number][applePosZ] + 0.0, 10.0);
        AppleData[number][AppleAmount] = APPLE_AMOUNT;
    }
    return false;
}
