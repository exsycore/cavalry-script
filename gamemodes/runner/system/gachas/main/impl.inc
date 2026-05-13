#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

stock ResetPlayerGacha(playerid) {
	KillTimer(playerTimerGacha[playerid]);
	playerCoutingGacha[playerid] = 0;
	playerMaxCoutingGacha[playerid] = 0;
	playerTimeCountingGacha[playerid] = 0;
	playerGetLastItemGacha[playerid] = MODEL_NULL;
	playerGetLastItemColorGacha[playerid] = 174;
	playerStampGoldItemGacha[playerid] = 0;
	playerStampBlueItemGacha[playerid] = 0;
	playerStampGreenItemGacha[playerid] = 0;
	playerGetGachaBoxID[playerid] = -1;
	playerGetGachaItemInvIndex[playerid] = -1;
	format(playerGetLastItemNameGacha[playerid], 64, "NULL");
	playerOpenGachaAuto[playerid] = false;
	PlayerOpeningGachaMenu[playerid] = false;
}

hook OnGameModeInit() {
	for (new i = 0; i < MAX_GACHA; i ++) {
		for (new j = 0; j < 15; j ++) {
			format(GaChaItemName[i][j], 64, "NULL");
			GaChaItemModel[i][j] = MODEL_NULL;
			GaChaItemAmount[i][j] = 0;
		}
	}

	//--> โหลด กาชา
	mysql_tquery(g_SQL, "SELECT * FROM `gachas`", "GachaBoxLoad", "");

	// GaChaItemModel[0][0] = 1240;
	// GaChaItemModel[0][1] = 1239; // 2 ของเขียว
	// GaChaItemModel[0][2] = 1550;
	// GaChaItemModel[0][3] = 1579; // 4 ของฟ้า
	// GaChaItemModel[0][4] = 1275;
	// GaChaItemModel[0][5] = 1254;
	// GaChaItemModel[0][6] = 1314;
	// GaChaItemModel[0][7] = 1277; // 8 ของทอง
	// GaChaItemModel[0][8] = 1212;
	// GaChaItemModel[0][9] = 954; // 10 ของเขียว
	// GaChaItemModel[0][10] = 1582;
	// GaChaItemModel[0][11] = 1650;
	// GaChaItemModel[0][12] = 1654; // 13 ของเขียว
	// GaChaItemModel[0][13] = 1279;
	// GaChaItemModel[0][14] = 1276;
	return 1;
}

forward GachaBoxLoad();
public GachaBoxLoad() {
	new rows, str[128], count = 0;
    cache_get_row_count(rows);
    for (new i = 0; i < rows && i < MAX_GACHA; i ++) {
		cache_get_value_name_int(i, "gachaID", GachaData[i][gachaID]);
        cache_get_value_name(i, "gachaName", GachaData[i][gachaName], 64);
		
		for (new k = 0; k < 15; k ++) {
			format(str, sizeof str, "gachaItemName%d", k+1);
			cache_get_value_name(i, str, GaChaItemName[i][k], 64);

			format(str, sizeof str, "gachaItemModel%d", k+1);
			cache_get_value_name_int(i, str, GaChaItemModel[i][k]);

			format(str, sizeof str, "gachaItemAmount%d", k+1);
			cache_get_value_name_int(i, str, GaChaItemAmount[i][k]);
		}	
		printf("LoadedGachaBox: [%d] [%s]", i, GachaData[i][gachaName]);
		count++;
	}
	return 1;
}

stock OnPlayerStartGacha(playerid) {
	if (playerTimeCountingGacha[playerid] == 0 && playerCoutingGacha[playerid] == 0 && playerGetGachaBoxID[playerid] != -1) {
		/*if (Player_Inventory_Weight[playerid] >= LunaData[playerid][luna_MaxWeight]) {
			playerMaxCoutingGacha[playerid] = 0;
			OnPlayerDestroyGachaUI(playerid);
			ResetPlayerGacha(playerid);
			return SendErrorMessage(playerid, "กระเป๋าของคุณเต็มไม่สามารถเปิดกาชาได้");
		}*/

		playerCoutingGacha[playerid] = 0;
		playerTimeCountingGacha[playerid] = 100;
		playerMaxCoutingGacha[playerid] = randomEx(50, 55);
		va_SendClientMessage(playerid, COLOR_YELLOW, "[!] คุณกำลังเปิดกาชา %s", GachaData[playerGetGachaBoxID[playerid]][gachaName]);
		playerTimerGacha[playerid] = SetTimerEx("playerUpdateGacha", playerTimeCountingGacha[playerid], false, "i", playerid);
	}
	return 1;
}

stock timer PlaySoundGachaComplete[300](playerid) {
	PlayerPlaySound(playerid, 40405, 0.0, 0.0, 0.0);
}

stock timer OpenGachaAuto[500](playerid) {
	OnPlayerStartGacha(playerid);
}

forward playerUpdateGacha(playerid);
public playerUpdateGacha(playerid) {
	new string[128];
	if (playerCoutingGacha[playerid] >= playerMaxCoutingGacha[playerid] && playerGetGachaBoxID[playerid] != -1) {
		if (playerGetGachaItemInvIndex[playerid] != -1) {
			new getitemModel = MODEL_NULL, getitemName[64], getitemAmount = 0, bool:announce = false;
			getitemModel = PlayerTextDrawGetPreviewModel(playerid, PlayerGachaUI[playerid][7]);
			PlayerTextDrawGetString(playerid, PlayerGachaUI[playerid][8], getitemName, 64);
			for (new i = 0; i < 15; i ++) {
				if (!strcmp(GaChaItemName[playerGetGachaBoxID[playerid]][i], getitemName, true) && GaChaItemModel[playerGetGachaBoxID[playerid]][i] == getitemModel) {
					if (i == 7) announce = true;
					getitemAmount = GaChaItemAmount[playerGetGachaBoxID[playerid]][i];
				}
			}

			if (getitemAmount != 0 && getitemModel != MODEL_NULL) {
				new additemid = -1;
				if (!strcmp(getitemName, "Cash", true) && getitemModel == 1212) {
					additemid = true;
					GivePlayerMoneyEx(playerid, getitemAmount);
				} else if (!strcmp(getitemName, "Cheetah", true) && getitemModel == 415) {
					additemid = true;

					/*new query[256];

					mysql_format(g_SQL, query, sizeof(query), "INSERT INTO venturas_vehicles (carOwnerID, carOwner, carModel, carPrice, carFuel) VALUES(%d, '%s', %d, %d, %.1f)", Player.Auth[playerid][@sqlid], ReturnName(playerid), 415, 0, 100.0);
					mysql_tquery(g_SQL, query);

					Inventory_Remove(playerid, "Cheetah", 1);*/
					//GiveMoney(playerid, getitemAmount, "Open Gacha");
					//GivePlayerMoneyEx(playerid, getitemAmount);
				} else if (!strcmp(getitemName, "Bobcat", true) && getitemModel == 422) {
					additemid = true;

					/*new query[256];

					mysql_format(g_SQL, query, sizeof(query), "INSERT INTO venturas_vehicles (carOwnerID, carOwner, carModel, carPrice, carFuel) VALUES(%d, '%s', %d, %d, %.1f)", Player.Auth[playerid][@sqlid], ReturnName(playerid), 422, 0, 100.0);
					mysql_tquery(g_SQL, query);
					Inventory_Remove(playerid, "Bobcat", 1);*/
					//GiveMoney(playerid, getitemAmount, "Open Gacha");
					//GivePlayerMoneyEx(playerid, getitemAmount);
				} else if (!strcmp(getitemName, "Faggio", true) && getitemModel == 462) {
					additemid = true;

					/*new query[256];

					mysql_format(g_SQL, query, sizeof(query), "INSERT INTO venturas_vehicles (carOwnerID, carOwner, carModel, carPrice, carFuel) VALUES(%d, '%s', %d, %d, %.1f)", Player.Auth[playerid][@sqlid], ReturnName(playerid), 462, 0, 100.0);
					mysql_tquery(g_SQL, query);
					Inventory_Remove(playerid, "Faggio", 1);*/
					//GiveMoney(playerid, getitemAmount, "Open Gacha");
					//GivePlayerMoneyEx(playerid, getitemAmount);
				} 
				/*else if(!strcmp(getitemName, "BMX", true) && getitemModel == 415) {
					additemid = true;

					new query[256];

					mysql_format(g_SQL, query, sizeof(query), "INSERT INTO venturas_vehicles (carOwnerID, carOwner, carModel, carPrice, carFuel) VALUES(%d, '%s', %d, %d, %.1f)", Player.Auth[playerid][@sqlid], ReturnName(playerid), 481, 0, 100.0);
					mysql_tquery(g_SQL, query);
					//GiveMoney(playerid, getitemAmount, "Open Gacha");
					//GivePlayerMoneyEx(playerid, getitemAmount);
				}*/
				/*else additemid = Inventory_Add(playerid, getitemName, getitemAmount);AddItemToPlayerID(playerid, getitemName, getitemModel, getitemAmount, 0, 100, -1);
				Player.Auth[playerid][@itemboxnewbie] -= 1;*/

				if (additemid == -1) {
					SendErrorMessage(playerid, "เกิดข้อผิดพลาด, กระเป๋าของคุณอาจจะเต็มทำให้คุณไม่สามารถเก็บไอเท็มเพิ่มได้");
					playerMaxCoutingGacha[playerid] = 0;
					OnPlayerDestroyGachaUI(playerid);
					ResetPlayerGacha(playerid);
					return 1;
				} else {
					if (!strcmp(getitemName, "Cash", true) && getitemModel == 1212) {
						va_SendClientMessage(playerid, COLOR_YELLOW, "[Gacha]: คุณได้รับเงินจำนวน '%s' จากการเปิดกาชา", FormatNumber(getitemAmount));
						if (announce) SendClientMessageToAllEx(0xF5C100FF, "[กล่องกาชา]: ผู้เล่น '%s' เปิดได้เงิน '%s' จำนวน '%s' จากกล่องกาชา '%s'", GetPlayerNameEx(playerid), getitemName, FormatNumber(getitemAmount), GachaData[playerGetGachaBoxID[playerid]][gachaName]);
					} else if (!strcmp(getitemName, "Cheetah", true) && getitemModel == 415) {
						SendClientMessage(playerid, COLOR_YELLOW, "[Gacha]: คุณได้รับรถ 'Cheetah' 1 คัน จากการเปิดกาชา");
						if (announce) SendClientMessageToAllEx(0xF5C100FF, "[กล่องกาชา]: ผู้เล่น '%s' เปิดได้รถ '%s' จำนวน '%s' จากกล่องกาชา '%s'", GetPlayerNameEx(playerid), getitemName, FormatNumber(getitemAmount), GachaData[playerGetGachaBoxID[playerid]][gachaName]);
					} else if (!strcmp(getitemName, "Bobcat", true) && getitemModel == 422) {
						SendClientMessage(playerid, COLOR_YELLOW, "[Gacha]: คุณได้รับรถ 'Bobcat' 1 คัน จากการเปิดกาชา");
						if (announce) SendClientMessageToAllEx(0xF5C100FF, "[กล่องกาชา]: ผู้เล่น '%s' เปิดได้รถ '%s' จำนวน '%s' จากกล่องกาชา '%s'", GetPlayerNameEx(playerid), getitemName, FormatNumber(getitemAmount), GachaData[playerGetGachaBoxID[playerid]][gachaName]);
					} else if (!strcmp(getitemName, "Faggio", true) && getitemModel == 462) {
						SendClientMessage(playerid, COLOR_YELLOW, "[Gacha]: คุณได้รับรถ 'Faggio' 1 คัน จากการเปิดกาชา");
						if (announce) SendClientMessageToAllEx(0xF5C100FF, "[กล่องกาชา]: ผู้เล่น '%s' เปิดได้รถ '%s' จำนวน '%s' จากกล่องกาชา '%s'", GetPlayerNameEx(playerid), getitemName, FormatNumber(getitemAmount), GachaData[playerGetGachaBoxID[playerid]][gachaName]);
					} else {
						va_SendClientMessage(playerid, COLOR_YELLOW, "[Gacha]: คุณได้รับไอเท็ม '%s' จำนวน '%d' ชิ้นจากการเปิดกาชา", getitemName, getitemAmount);
						if (announce) SendClientMessageToAllEx(0xF5C100FF, "[กล่องกาชา]: ผู้เล่น '%s' เปิดได้ไอเท็ม '%s' จำนวน '%d' จากกล่องกาชา '%s'", GetPlayerNameEx(playerid), getitemName, getitemAmount, GachaData[playerGetGachaBoxID[playerid]][gachaName]);
					}
					defer PlaySoundGachaComplete(playerid);

					//Player.Auth[playerid][@itemboxnewbie] -= 1;

					/*format(string, sizeof string, "OPEN (%d)", Player.Auth[playerid][@itemboxnewbie]);
					PlayerTextDrawSetString(playerid, PlayerGachaUI[playerid][15], string);*/
				}
			}

			/*if (Player.Auth[playerid][@itemboxnewbie] <= 0) {
				playerMaxCoutingGacha[playerid] = 0;
				OnPlayerDestroyGachaUI(playerid);
				ResetPlayerGacha(playerid);
			} else {
				KillTimer(playerTimerGacha[playerid]);
				playerCoutingGacha[playerid] = 0;
				playerMaxCoutingGacha[playerid] = 0;
				playerTimeCountingGacha[playerid] = 0;
				playerStampGoldItemGacha[playerid] = 0;
				playerStampBlueItemGacha[playerid] = 0;
				playerStampGreenItemGacha[playerid] = 0;

				SelectTextDraw(playerid, 0x8F00C4FF);

				if (playerOpenGachaAuto[playerid]) defer OpenGachaAuto(playerid);
			}*/
		}
		return 1;
	}

	// printf("playerGetGachaBoxID: %d of PlayerID: %d", playerGetGachaBoxID[playerid], playerid);
	if (playerCoutingGacha[playerid] < playerMaxCoutingGacha[playerid] && playerGetGachaBoxID[playerid] != -1) {
		PlayerPlaySound(playerid, 1135, 0.0, 0.0, 0.0);
		playerCoutingGacha[playerid]++;

		if (playerCoutingGacha[playerid] >= (playerMaxCoutingGacha[playerid] / 2)) playerTimeCountingGacha[playerid] += 50;
		else playerTimeCountingGacha[playerid] ++;
		
		new modelindex[7], boxtextcolor[7], itemnameindex[7][64];
		modelindex[0] = PlayerTextDrawGetPreviewModel(playerid, PlayerGachaUI[playerid][1]);
		modelindex[1] = PlayerTextDrawGetPreviewModel(playerid, PlayerGachaUI[playerid][3]);
		modelindex[2] = PlayerTextDrawGetPreviewModel(playerid, PlayerGachaUI[playerid][5]);
		modelindex[3] = PlayerTextDrawGetPreviewModel(playerid, PlayerGachaUI[playerid][7]);
		modelindex[4] = PlayerTextDrawGetPreviewModel(playerid, PlayerGachaUI[playerid][9]);
		modelindex[5] = PlayerTextDrawGetPreviewModel(playerid, PlayerGachaUI[playerid][11]);
		modelindex[6] = PlayerTextDrawGetPreviewModel(playerid, PlayerGachaUI[playerid][13]);

		boxtextcolor[0] = PlayerTextDrawGetBoxColor(playerid, PlayerGachaUI[playerid][2]);
		boxtextcolor[1] = PlayerTextDrawGetBoxColor(playerid, PlayerGachaUI[playerid][4]);
		boxtextcolor[2] = PlayerTextDrawGetBoxColor(playerid, PlayerGachaUI[playerid][6]);
		boxtextcolor[3] = PlayerTextDrawGetBoxColor(playerid, PlayerGachaUI[playerid][8]);
		boxtextcolor[4] = PlayerTextDrawGetBoxColor(playerid, PlayerGachaUI[playerid][10]);
		boxtextcolor[5] = PlayerTextDrawGetBoxColor(playerid, PlayerGachaUI[playerid][12]);
		boxtextcolor[6] = PlayerTextDrawGetBoxColor(playerid, PlayerGachaUI[playerid][14]);

		PlayerTextDrawGetString(playerid, PlayerGachaUI[playerid][2], itemnameindex[0], 64);
		PlayerTextDrawGetString(playerid, PlayerGachaUI[playerid][4], itemnameindex[1], 64);
		PlayerTextDrawGetString(playerid, PlayerGachaUI[playerid][6], itemnameindex[2], 64);
		PlayerTextDrawGetString(playerid, PlayerGachaUI[playerid][8], itemnameindex[3], 64);
		PlayerTextDrawGetString(playerid, PlayerGachaUI[playerid][10], itemnameindex[4], 64);
		PlayerTextDrawGetString(playerid, PlayerGachaUI[playerid][12], itemnameindex[5], 64);
		PlayerTextDrawGetString(playerid, PlayerGachaUI[playerid][14], itemnameindex[6], 64);

		PlayerTextDrawSetPreviewModel(playerid, PlayerGachaUI[playerid][1], modelindex[1]);
		PlayerTextDrawSetPreviewModel(playerid, PlayerGachaUI[playerid][3], modelindex[2]);
		PlayerTextDrawSetPreviewModel(playerid, PlayerGachaUI[playerid][5], modelindex[3]);
		PlayerTextDrawSetPreviewModel(playerid, PlayerGachaUI[playerid][7], modelindex[4]);
		PlayerTextDrawSetPreviewModel(playerid, PlayerGachaUI[playerid][9], modelindex[5]);
		PlayerTextDrawSetPreviewModel(playerid, PlayerGachaUI[playerid][11], modelindex[6]);

		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][2], boxtextcolor[1]);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][4], boxtextcolor[2]);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][6], boxtextcolor[3]);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][8], boxtextcolor[4]);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][10], boxtextcolor[5]);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][12], boxtextcolor[6]);

		format(string, sizeof string, "%s", itemnameindex[1]);
		PlayerTextDrawSetString(playerid, PlayerGachaUI[playerid][2], string);

		format(string, sizeof string, "%s", itemnameindex[2]);
		PlayerTextDrawSetString(playerid, PlayerGachaUI[playerid][4], string);

		format(string, sizeof string, "%s", itemnameindex[3]);
		PlayerTextDrawSetString(playerid, PlayerGachaUI[playerid][6], string);

		format(string, sizeof string, "%s", itemnameindex[4]);
		PlayerTextDrawSetString(playerid, PlayerGachaUI[playerid][8], string);

		format(string, sizeof string, "%s", itemnameindex[5]);
		PlayerTextDrawSetString(playerid, PlayerGachaUI[playerid][10], string);

		format(string, sizeof string, "%s", itemnameindex[6]);
		PlayerTextDrawSetString(playerid, PlayerGachaUI[playerid][12], string);

		new randomitem = randomEx(0, 14);
		if (randomitem == 1 || randomitem == 9 || randomitem == 12) {
			playerStampGreenItemGacha[playerid]++;
			if (playerStampGreenItemGacha[playerid] >= 2) {
				format(playerGetLastItemNameGacha[playerid], 64, GaChaItemName[playerGetGachaBoxID[playerid]][randomitem]);
				playerGetLastItemGacha[playerid] = GaChaItemModel[playerGetGachaBoxID[playerid]][randomitem];
				playerGetLastItemColorGacha[playerid] = 0x05B200FF;
				playerStampGreenItemGacha[playerid] = 0;
			} else {
				randomitem = 6;
				format(playerGetLastItemNameGacha[playerid], 64, GaChaItemName[playerGetGachaBoxID[playerid]][randomitem]);
				playerGetLastItemGacha[playerid] = GaChaItemModel[playerGetGachaBoxID[playerid]][randomitem];
				playerGetLastItemColorGacha[playerid] = 174;
			}
		} else if (randomitem == 3) {
			playerStampBlueItemGacha[playerid]++;
			if (playerStampBlueItemGacha[playerid] >= 3) {
				format(playerGetLastItemNameGacha[playerid], 64, GaChaItemName[playerGetGachaBoxID[playerid]][randomitem]);
				playerGetLastItemGacha[playerid] = GaChaItemModel[playerGetGachaBoxID[playerid]][randomitem];
				playerGetLastItemColorGacha[playerid] = 0x0077F5FF;
				playerStampBlueItemGacha[playerid] = 0;
			} else {
				randomitem = 11;
				format(playerGetLastItemNameGacha[playerid], 64, GaChaItemName[playerGetGachaBoxID[playerid]][randomitem]);
				playerGetLastItemGacha[playerid] = GaChaItemModel[playerGetGachaBoxID[playerid]][randomitem];
				playerGetLastItemColorGacha[playerid] = 174;
			}
		} else if (randomitem == 7) {
			playerStampGoldItemGacha[playerid]++;
			if (playerStampGoldItemGacha[playerid] >= 4) {
				format(playerGetLastItemNameGacha[playerid], 64, GaChaItemName[playerGetGachaBoxID[playerid]][randomitem]);
				playerGetLastItemGacha[playerid] = GaChaItemModel[playerGetGachaBoxID[playerid]][randomitem];
				playerGetLastItemColorGacha[playerid] = 0xF5C500FF;
				playerStampGoldItemGacha[playerid] = 0;
			} else {
				randomitem = 4;
				format(playerGetLastItemNameGacha[playerid], 64, GaChaItemName[playerGetGachaBoxID[playerid]][randomitem]);
				playerGetLastItemGacha[playerid] = GaChaItemModel[playerGetGachaBoxID[playerid]][randomitem];
				playerGetLastItemColorGacha[playerid] = 174;
			}
		} else {
			format(playerGetLastItemNameGacha[playerid], 64, GaChaItemName[playerGetGachaBoxID[playerid]][randomitem]);
			playerGetLastItemGacha[playerid] = GaChaItemModel[playerGetGachaBoxID[playerid]][randomitem];
			playerGetLastItemColorGacha[playerid] = 174;
		}

		PlayerTextDrawSetPreviewModel(playerid, PlayerGachaUI[playerid][13], playerGetLastItemGacha[playerid]);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][14], playerGetLastItemColorGacha[playerid]);

		for (new i = 1; i < 15; i ++) PlayerTextDrawShow(playerid, PlayerGachaUI[playerid][i]);

		format(string, sizeof string, "%s", playerGetLastItemNameGacha[playerid]);
		PlayerTextDrawSetString(playerid, PlayerGachaUI[playerid][14], string);

		playerTimerGacha[playerid] = SetTimerEx("playerUpdateGacha", playerTimeCountingGacha[playerid], false, "i", playerid);
	} 
	return 1;
}

timer OpeningGachaUI[300](playerid){
	if (!PlayerOpeningGachaMenu[playerid]) OnPlayerCreateGachaUI(playerid, playerGetGachaBoxID[playerid]);
	else OnPlayerDestroyGachaUI(playerid);
}

YCMD:gachatest(playerid, const params[], help) {
	if (GetPlayerLoggedIn(playerid)) {
		playerGetGachaBoxID[playerid] = 0;
		playerGetGachaItemInvIndex[playerid] = 0;
		defer OpeningGachaUI(playerid);
	}
	return 1;
}