#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>

new
	fishTake[MAX_PLAYERS],
	auto_farm[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    fishTake[playerid] = 0;
	auto_farm[playerid] = 0;
	FishingRod[playerid] = 0;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    if (fishTake[playerid] != 0) {
		StopProgress(playerid);
		auto_farm[playerid] = 0;
    }
    return 1;
}

hook OnGameModeInit() {
    for (new i = 0; i < sizeof(fishData); i ++) {
        fishData[i][fishPickup] = CreateDynamicPickup(1604, 23, fishData[i][fishPosX], fishData[i][fishPosY], fishData[i][fishPosZ]);
		fishData[i][fish3D] = CreateDynamic3DTextLabel("{B7FF56}ตกปลา\n{FFFFFF}กดปุ่ม {FF6600}'N'{FFFFFF} ตกปลา\n{FFFFFF}กดปุ่ม {FF6600}'H'{FFFFFF} ยกเลิกตกปลา", COLOR_GREEN, fishData[i][fishPosX], fishData[i][fishPosY], fishData[i][fishPosZ], 5.0);
	}

	CreateActor(33, DEFAULT_POS_FISHING_X, DEFAULT_POS_FISHING_Y, DEFAULT_POS_FISHING_Z, DEFAULT_POS_FISHING_A);
	CreateDynamic3DTextLabel("{708090}ชาวประมง\n{FFFFFF}กด {00ffff}N{FFFFFF} เพื่อเข้าสู่ร้าน", -1, DEFAULT_POS_FISHING_X, DEFAULT_POS_FISHING_Y, DEFAULT_POS_FISHING_Z + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1);

	new fishingmap;
	fishingmap = CreateDynamicObject(19482, 2154.557128, -94.198486, 2.148847, 0.000000, 0.000000, 149.500000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(fishingmap, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
	SetDynamicObjectMaterialText(fishingmap, 0, "{FFFFFF}ชาวประมง", 120, "Ariel", 60, 1, 0x00000000, 0x00000000, 0);
	fishingmap = CreateDynamicObject(3334, 2130.382080, -75.339553, 4.820294, 0.000000, -178.799865, -151.099990, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(fishingmap, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
	fishingmap = CreateDynamicObject(19482, 2130.043212, -74.361389, 3.781853, 0.000000, 0.000000, 27.600015, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(fishingmap, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
	SetDynamicObjectMaterialText(fishingmap, 0, "{000000}ตกปลา", 90, "Ariel", 70, 1, 0x00000000, 0x00000000, 0);
	fishingmap = CreateDynamicObject(19482, 2129.955566, -74.022941, 2.781852, 0.000000, 0.000000, 27.600015, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(fishingmap, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
	SetDynamicObjectMaterialText(fishingmap, 0, "{ffff00}Cavalry", 120, "Ariel", 70, 1, 0x00000000, 0x00000000, 0);
	fishingmap = CreateDynamicObject(19462, 2131.517578, -101.923477, 0.183862, -0.399999, -90.199989, 38.200019, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(fishingmap, 0, 1560, "7_11_door", "cj_sheetmetal2", 0x00000000);
	fishingmap = CreateDynamicObject(19462, 2128.846191, -104.026100, 0.181994, -0.399999, -90.199989, 38.200019, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(fishingmap, 0, 1560, "7_11_door", "cj_sheetmetal2", 0x00000000);
	fishingmap = CreateDynamicObject(19462, 2126.222656, -106.091613, 0.180336, -0.399999, -90.199989, 38.200019, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(fishingmap, 0, 1560, "7_11_door", "cj_sheetmetal2", 0x00000000);
	fishingmap = CreateDynamicObject(19462, 2123.494140, -108.237449, 0.178224, -0.399999, -90.199989, 38.200019, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(fishingmap, 0, 1560, "7_11_door", "cj_sheetmetal2", 0x00000000);
	fishingmap = CreateDynamicObject(19462, 2120.788818, -110.364791, 0.166217, -0.399999, -90.199989, 38.200019, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(fishingmap, 0, 1560, "7_11_door", "cj_sheetmetal2", 0x00000000);
	fishingmap = CreateDynamicObject(738, 2142.845947, -104.759140, 1.256946, 0.000000, 0.000000, -56.999996, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(fishingmap, 0, -1, "none", "none", 0xFFFFF00F);
	fishingmap = CreateDynamicObject(738, 2132.505859, -88.927131, 1.676946, 0.000000, 0.000000, -56.999996, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(fishingmap, 0, -1, "none", "none", 0xFFFFF00F);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fishingmap = CreateDynamicObject(1568, 2145.703125, -69.266120, 2.351313, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	fishingmap = CreateDynamicObject(1568, 2151.313720, -69.266120, 2.351313, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	fishingmap = CreateDynamicObject(642, 2154.997558, -95.692733, 2.977672, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	fishingmap = CreateDynamicObject(19632, 2153.409423, -96.352905, 1.732707, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	fishingmap = CreateDynamicObject(19076, 2154.496582, -103.192474, 1.088351, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	fishingmap = CreateDynamicObject(970, 2128.492919, -98.502571, 0.744239, 0.000000, 0.000000, 37.500007, -1, -1, -1, 300.00, 300.00); 
	fishingmap = CreateDynamicObject(970, 2125.198242, -101.035079, 0.754239, 0.000000, 0.000000, 37.500007, -1, -1, -1, 300.00, 300.00); 
	fishingmap = CreateDynamicObject(970, 2121.948974, -103.531036, 0.754239, 0.000000, 0.000000, 37.500007, -1, -1, -1, 300.00, 300.00); 
	fishingmap = CreateDynamicObject(970, 2118.685058, -106.039237, 0.754239, 0.000000, 0.000000, 37.500007, -1, -1, -1, 300.00, 300.00); 
	fishingmap = CreateDynamicObject(970, 2124.012695, -113.879280, 0.754239, 0.000000, 0.000000, 37.500007, -1, -1, -1, 300.00, 300.00); 
	fishingmap = CreateDynamicObject(970, 2127.296630, -111.358993, 0.754239, 0.000000, 0.000000, 37.500007, -1, -1, -1, 300.00, 300.00); 
	fishingmap = CreateDynamicObject(970, 2130.578613, -108.838668, 0.754239, 0.000000, 0.000000, 37.500007, -1, -1, -1, 300.00, 300.00); 
	fishingmap = CreateDynamicObject(970, 2133.851806, -106.324493, 0.754239, 0.000000, 0.000000, 37.500007, -1, -1, -1, 300.00, 300.00); 
	fishingmap = CreateDynamicObject(970, 2121.103515, -113.473564, 0.754239, 0.000000, 0.000000, -53.199951, -1, -1, -1, 300.00, 300.00); 
	fishingmap = CreateDynamicObject(970, 2118.616455, -110.150489, 0.754239, 0.000000, 0.000000, -53.199951, -1, -1, -1, 300.00, 300.00); 
	fishingmap = CreateDynamicObject(970, 2117.877197, -109.165512, 0.754239, 0.000000, 0.000000, -53.199951, -1, -1, -1, 300.00, 300.00); 
	fishingmap = CreateDynamicObject(1568, 2134.884033, -104.050422, 0.332982, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	fishingmap = CreateDynamicObject(1568, 2130.212158, -98.040412, 0.332982, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if (newkeys & KEY_NO && !IsPlayerInAnyVehicle(playerid)) {
		if (IsPlayerInRangeOfPoint(playerid, 3.0, DEFAULT_POS_FISHING_X, DEFAULT_POS_FISHING_Y, DEFAULT_POS_FISHING_Z)) {
			inline Dialog_Show_Fishing(res, list, string:in[]) {
				#pragma unused in
				if (!res) @return 1;

				switch (list) {
					case 0: {
						inline Buy_Fishing(res1, list1, string:input1[]) {
							#pragma unused list1, input1
							if (res1) {
								if (GetPlayerMoneyEx(playerid) < DEFAULT_FISH_ROD)
									return SendErrorFishingMessage(playerid, "คุณมีเงินไม่เพียงพอในการซื้อ {00ffff}เบ็ดตกปลา{FFFFFF} (%s/%s)", FormatMoney(GetPlayerMoneyEx(playerid)), FormatMoney(DEFAULT_FISH_ROD));

								if (GetItemAmountByName(playerid, "เบ็ดตกปลา") >= 3)
									return SendErrorFishingMessage(playerid, "คุณซื้อเบ็ดตกปลาครบ 3 อันแล้ว !");

								AddItemByName(playerid, "เบ็ดตกปลา", 1);
								GivePlayerMoneyEx(playerid, -DEFAULT_FISH_ROD);

								SendPlayerAction(playerid, "คุณได้ซื้อ {00ffff}เบ็ดตกปลา{FFFFFF} สำเร็จ ในราคา {00ffff}%s", FormatMoney(DEFAULT_FISH_ROD));
							} else {
								Dialog_ShowCallback(playerid, using inline Dialog_Show_Fishing, DIALOG_STYLE_LIST,
									"ชาวประมง", 
									"{FFFFFF}คันเบ็ดตกปลา\t\t{00FF00}$5,000\n{FFFFFF}เหยื่อ\t\t\t{00FF00}$30", 
									"เลือก", "ปิด");
							}
						}
						Dialog_ShowCallback(playerid, using inline Buy_Fishing, DIALOG_STYLE_MSGBOX, 
							"ชาวประมง", 
							"{FF6600}คุณต้องการซื้อเบ็ดตกปลาใช่มั้ย?\n{FFFFFF}กด {ffff00}'ตกลง'{FFFFFF} เพื่อซื้อเบ็ดตกปลา", 
							"ตกลง", "ปิด");
					}
					case 1: {
						inline Buy_Victim(res2, list2, string:in2[]) {
                            #pragma unused list2

							if (res2) {
								new amount = strval(in2);
								new price = amount*30;

								if (amount <= 0) {
									SendErrorFishingMessage(playerid, "กรุณาใส่จำนวนมากกว่า 0");

									new string[256];
									format(string, sizeof(string), "{FFFFFF}คุณต้องการซื้อ {00FFFF}เหยื่อ {FFFFFF}กี่ตัว ?\n{FFFFFF}ราคาปัจจุบัน: 1 ตัว/{00ff00}$30");
									Dialog_ShowCallback(playerid, using inline Buy_Victim, DIALOG_STYLE_INPUT, 
										"ชาวประมง", 
										string, 
										"ตกลง", "ยกเลิก");
								}

								if (GetPlayerMoneyEx(playerid) < price) {
									SendErrorFishingMessage(playerid, "คุณมีเงินสดไม่เพียงพอ !");
				
									new string[256];
									format(string, sizeof(string), "{FFFFFF}คุณต้องการซื้อ {00FFFF}เหยื่อ {FFFFFF}กี่ตัว ?\n{FFFFFF}ราคาปัจจุบัน: 1 ตัว/{00ff00}$30");
									Dialog_ShowCallback(playerid, using inline Buy_Victim, DIALOG_STYLE_INPUT, 
										"ชาวประมง", 
										string, 
										"ตกลง", "ยกเลิก");
								}

								if (GetItemAmountByName(playerid, "เหยื่อตกปลา") >= 50)
									return SendErrorMessage(playerid, "คุณมีเหยื่อในตัว 50 ชิ้นแล้ว !");

								AddItemByName(playerid, "เหยื่อตกปลา", amount);
								GivePlayerMoneyEx(playerid, -price);
								va_SendClientMessage(playerid, COLOR_YELLOW, "[เหยื่อ]: {FFFFFF}คุณได้ซื้อเหยื่อ จำนวน %d", amount);
							} else {
								Dialog_ShowCallback(playerid, using inline Dialog_Show_Fishing, DIALOG_STYLE_LIST,
									"ชาวประมง", 
									"{FFFFFF}คันเบ็ดตกปลา\t\t{00FF00}$5,000\n{FFFFFF}เหยื่อ\t\t\t{00FF00}$30", 
									"เลือก", "ปิด");
							}
                        }

						new str[256];
						format(str, sizeof(str), "{FFFFFF}คุณต้องการซื้อ {00FFFF}เหยื่อ {FFFFFF}กี่ตัว ?\n{FFFFFF}ราคาปัจจุบัน: 1 ตัว/{00ff00}$30");
						Dialog_ShowCallback(playerid, using inline Buy_Victim, DIALOG_STYLE_INPUT, 
							"ชาวประมง", 
							str, 
							"ตกลง", "ยกเลิก");
					}
				}
			}
			Dialog_ShowCallback(playerid, using inline Dialog_Show_Fishing, DIALOG_STYLE_LIST,
				"ชาวประมง", 
				"{FFFFFF}คันเบ็ดตกปลา\t\t{00FF00}$5,000\n{FFFFFF}เหยื่อ\t\t\t{00FF00}$30", 
				"เลือก", "ปิด");
        }

		for (new i = 0; i < sizeof(fishData); i ++) {
		    if (IsPlayerInRangeOfPoint(playerid, 2.5, fishData[i][fishPosX], fishData[i][fishPosY], fishData[i][fishPosZ])) {
                if (!GetItemAmountByName(playerid, "เบ็ดตกปลา"))
                    return SendErrorFishingMessage(playerid, "คุณไม่มีเหยื่ออยู่ในตัวเลย");

				if (FishingRod[playerid] == 0)
                    return SendErrorFishingMessage(playerid, "คุณยังไม่สามารถตกปลาได้เนื่องจากคุณยังไม่ได้หยิบเบ็ดตกปลา !");

                if (fishTake[playerid] == 1)
                    return SendErrorFishingMessage(playerid, "คุณกำลังตกปลาอยู่ !");

	        	fishTake[playerid] = 1;
				auto_farm[playerid] = 1;

				SetPlayerPos(playerid, fishData[i][fishPosX], fishData[i][fishPosY], fishData[i][fishPosZ]);
				SetPlayerFacingAngle(playerid, fishData[i][fishPosA]);

				ApplyAnimation(playerid, "SWORD", "sword_block", 50.0, 0, 1, 0, 1, 1);
				
				new rand = randomEx(100, 200);
                StartProgress(playerid, rand, 0, INVALID_OBJECT_ID);
				
	        	for (new s = 0; s < MAX_ITEMS; s++) {
					if (!strcmp(ItemsInfo[s][ItemName2], "เหยื่อตกปลา", true)) {
						CallLocalFunction("DeleteItem", "ddd", playerid, s, 1);
					}
				}

				TogglePlayerControllable(playerid, false);
	        	break;
	    	}
		}
	}
	if (newkeys & KEY_CTRL_BACK && !IsPlayerInAnyVehicle(playerid)) {
		for (new i = 0; i < sizeof(fishData); i ++) {
			if (IsPlayerInRangeOfPoint(playerid, 2.5, fishData[i][fishPosX], fishData[i][fishPosY], fishData[i][fishPosZ])) {
				if (auto_farm[playerid] == 1) {
					auto_farm[playerid] = 0;
					SendPlayerAction(playerid, "คุณได้ยกเลิกการตกปลาแล้ว !");
				}
			}
		}
	}
	return 1;
}

public PlayerFishingUnfreeze(playerid) {
	fishTake[playerid] = 0;
	TogglePlayerControllable(playerid, true);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	ClearAnimations(playerid);

	new rand = randomEx(1, 200);
	switch (rand) {
	    case 1..15: {
			SendErrorFishingMessage(playerid, "เสียใจด้วย คุณตกไม่ได้ปลาอะไรเลย !"); 
		}
	    case 16..40: {
			AddItemByName(playerid, "ปลานิล", 1);

			GivePlayerExp(playerid, 20);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			ClearAnimations(playerid);
			SendPlayerAction(playerid, "คุณได้รับ {00FF00}ปลานิล +1{FFFFFF} ตัว");
	    }
	    case 41..60: {
			AddItemByName(playerid, "ปลาดุก", 1);

			GivePlayerExp(playerid, 20);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			ClearAnimations(playerid);
			SendPlayerAction(playerid, "คุณได้รับ {00FF00}ปลาดุก +1{FFFFFF} ตัว");
	    }
	    case 76..85: {
			AddItemByName(playerid, "ปลานิล", 1);

			GivePlayerExp(playerid, 20);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			ClearAnimations(playerid);
			SendPlayerAction(playerid, "คุณได้รับ {00FF00}ปลานิล +1{FFFFFF} ตัว");
	    }
	    case 86..99: {
			AddItemByName(playerid, "ปลากระพง", 1);

			GivePlayerExp(playerid, 20);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			ClearAnimations(playerid);
			SendPlayerAction(playerid, "คุณได้รับ {00FF00}ปลากระพง +1{FFFFFF} ตัว");
	    }
	    case 101..130: {
			AddItemByName(playerid, "ปลาแซลม่อน", 1);

			GivePlayerExp(playerid, 20);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			ClearAnimations(playerid);
			SendPlayerAction(playerid, "คุณได้รับ {00FF00}ปลาแซลม่อน +1{FFFFFF} ตัว");
	    }
	    case 141..160: {
			SendErrorFishingMessage(playerid, "เสียใจด้วย คุณตกไม่ได้ปลาอะไรเลย !");
		}
	}

	if (auto_farm[playerid] == 1) {
		for (new i = 0; i < sizeof(fishData); i ++) {
			if (IsPlayerInRangeOfPoint(playerid, 3.0, fishData[i][fishPosX], fishData[i][fishPosY], fishData[i][fishPosZ])) {
                if (!GetItemAmountByName(playerid, "เบ็ดตกปลา"))
                    return SendErrorFishingMessage(playerid, "คุณไม่มีเหยื่ออยู่ในตัวเลย");

				if (FishingRod[playerid] == 0)
                    return SendErrorFishingMessage(playerid, "คุณยังไม่สามารถตกปลาได้เนื่องจากคุณยังไม่ได้หยิบเบ็ดตกปลา !");

				fishTake[playerid] = 1;
				auto_farm[playerid] = 1;
				
				new randx = randomEx(100, 200);
				StartProgress(playerid, randx, 0, i); 
								
				for (new s = 0; s < MAX_ITEMS; s++) {
					if (!strcmp(ItemsInfo[s][ItemName2], "เหยื่อตกปลา", true)) {
						CallLocalFunction("DeleteItem", "ddd", playerid, s, 1);
					}
				}

				SetPlayerPos(playerid, fishData[i][fishPosX], fishData[i][fishPosY], fishData[i][fishPosZ]);
				SetPlayerFacingAngle(playerid, fishData[i][fishPosA]);

				ApplyAnimation(playerid, "SWORD", "sword_block", 50.0, 0, 0, 0, 1, 1);
				
				SendClientMessage(playerid, COLOR_YELLOW, "[AUTO FARM] {FFFFFF}เหวี่ยงเบ็ดตกปลา...");
				//break;	
			}
		}	
	}
	return 1;
}

hook OnProgressFinish(playerid, objectid) {
	if (fishTake[playerid] == 1)
		PlayerFishingUnfreeze(playerid);

	return Y_HOOKS_CONTINUE_RETURN_0;
}

hook OnProgressUpdate(playerid, progress, objectid) {
	if (fishTake[playerid] == 1) {
		ApplyAnimation(playerid, "SWORD", "sword_block", 50.0, 0, 1, 0, 1, 1);
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_0;
}