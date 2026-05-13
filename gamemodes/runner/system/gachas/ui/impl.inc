#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnPlayerClickTextDraw(playerid, Text:clickedid) {
	if (GetPlayerLoggedIn(playerid)) {
		if (clickedid == Text:INVALID_TEXT_DRAW) {
			if (PlayerOpeningGachaMenu[playerid]) {
				if (playerCoutingGacha[playerid] > 0) {
					return SelectTextDraw(playerid, 0x8F00C4FF);
				} else if (playerCoutingGacha[playerid] == 0) {
					OnPlayerDestroyGachaUI(playerid);
					return 1;
				}
			} else {
			}
		}
	}
	return 1;
}

hook OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid) {
	if (GetPlayerLoggedIn(playerid)) {
		if (PlayerOpeningGachaMenu[playerid]) {
			if (playertextid == PlayerGachaUI[playerid][18]) { // Cancel
				if (playerTimeCountingGacha[playerid] == 0 && !playerOpenGachaAuto[playerid]) {
					OnPlayerDestroyGachaUI(playerid);
					return 1;
				}
			}

			if (playertextid == PlayerGachaUI[playerid][15]) { // Open
				if (playerTimeCountingGacha[playerid] == 0) {
					return OnPlayerStartGacha(playerid);
				}
			}

			if (playertextid == PlayerGachaUI[playerid][23]) { // Open Auto
				if (!playerOpenGachaAuto[playerid]) {
					playerOpenGachaAuto[playerid] = true;
					PlayerTextDrawSetString(playerid, PlayerGachaUI[playerid][23], "OPEN AUTO (TRUE)");
					PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][23], 12849919);
					PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][24], 12849919);
					PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][25], 12849919);
					PlayerTextDrawShow(playerid, PlayerGachaUI[playerid][23]);
					PlayerTextDrawShow(playerid, PlayerGachaUI[playerid][24]);
					PlayerTextDrawShow(playerid, PlayerGachaUI[playerid][25]);
				} else {
					playerOpenGachaAuto[playerid] = false;
					PlayerTextDrawSetString(playerid, PlayerGachaUI[playerid][23], "OPEN AUTO (FALSE)");
					PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][23], -1962934017);
					PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][24], -1962934017);
					PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][25], -1962934017);
					PlayerTextDrawShow(playerid, PlayerGachaUI[playerid][23]);
					PlayerTextDrawShow(playerid, PlayerGachaUI[playerid][24]);
					PlayerTextDrawShow(playerid, PlayerGachaUI[playerid][25]);
				}
			}
		}
	}
	return 1;
}

stock OnPlayerDestroyGachaUI(playerid) {
	if (PlayerOpeningGachaMenu[playerid] && playerMaxCoutingGacha[playerid] == 0) {
		for (new i = 0; i < MAX_GACHAS_UI; i ++) {
			if (IsPlayerTextDrawVisible(playerid, PlayerGachaUI[playerid][i])) {
				PlayerTextDrawHide(playerid, PlayerGachaUI[playerid][i]);
			}
			PlayerTextDrawDestroy(playerid, PlayerGachaUI[playerid][i]);
		}

		PlayerOpeningGachaMenu[playerid] = false;

		ShowPlayerUI(playerid);

		CancelSelectTextDraw(playerid);
	}
}

stock OnPlayerCreateGachaUI(playerid, gachaindex) {
	if (!PlayerOpeningGachaMenu[playerid] && playerMaxCoutingGacha[playerid] == 0) {
		new string[128];
		PlayerGachaUI[playerid][0] = CreatePlayerTextDraw(playerid, 319.000000, -8.000000, "_");
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][0], 1);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][0], 0.600000, 55.300003);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][0], 298.500000, 680.000000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][0], 1);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][0], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][0], 2);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][0], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][0], 255);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][0], 135);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][0], 1);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][0], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][0], 0);

		PlayerGachaUI[playerid][1] = CreatePlayerTextDraw(playerid, 5.000000, 200.000000, "Preview_Model");
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][1], 5);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][1], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][1], 90.000000, 92.000000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][1], 0);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][1], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][1], 1);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][1], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][1], -1094795651);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][1], 255);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][1], 0);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][1], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][1], 0);
		PlayerTextDrawSetPreviewModel(playerid, PlayerGachaUI[playerid][1], GaChaItemModel[gachaindex][0]);
		PlayerTextDrawSetPreviewRot(playerid, PlayerGachaUI[playerid][1], -10.000000, 0.000000, -20.000000, 1.000000);
		PlayerTextDrawSetPreviewVehCol(playerid, PlayerGachaUI[playerid][1], 1, 1);

		PlayerGachaUI[playerid][2] = CreatePlayerTextDraw(playerid, 50.000000, 276.500000, GaChaItemName[gachaindex][0]);
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][2], 1);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][2], 0.316666, 1.500000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][2], 400.000000, 86.500000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][2], 0);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][2], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][2], 2);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][2], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][2], 255);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][2], 174);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][2], 1);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][2], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][2], 0);

		PlayerGachaUI[playerid][3] = CreatePlayerTextDraw(playerid, 95.000000, 200.000000, "Preview_Model");
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][3], 5);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][3], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][3], 90.000000, 92.000000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][3], 0);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][3], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][3], 1);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][3], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][3], -1094795651);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][3], 255);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][3], 0);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][3], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][3], 0);
		PlayerTextDrawSetPreviewModel(playerid, PlayerGachaUI[playerid][3], GaChaItemModel[gachaindex][1]);
		PlayerTextDrawSetPreviewRot(playerid, PlayerGachaUI[playerid][3], -10.000000, 0.000000, -20.000000, 1.000000);
		PlayerTextDrawSetPreviewVehCol(playerid, PlayerGachaUI[playerid][3], 1, 1);

		PlayerGachaUI[playerid][4] = CreatePlayerTextDraw(playerid, 140.000000, 276.500000, GaChaItemName[gachaindex][1]);
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][4], 1);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][4], 0.316666, 1.500000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][4], 400.000000, 86.500000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][4], 0);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][4], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][4], 2);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][4], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][4], 255);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][4], 174);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][4], 1);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][4], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][4], 0);

		PlayerGachaUI[playerid][5] = CreatePlayerTextDraw(playerid, 185.000000, 200.000000, "Preview_Model");
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][5], 5);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][5], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][5], 90.000000, 92.000000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][5], 0);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][5], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][5], 1);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][5], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][5], -1094795651);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][5], 255);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][5], 0);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][5], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][5], 0);
		PlayerTextDrawSetPreviewModel(playerid, PlayerGachaUI[playerid][5], GaChaItemModel[gachaindex][2]);
		PlayerTextDrawSetPreviewRot(playerid, PlayerGachaUI[playerid][5], -10.000000, 0.000000, -20.000000, 1.000000);
		PlayerTextDrawSetPreviewVehCol(playerid, PlayerGachaUI[playerid][5], 1, 1);

		PlayerGachaUI[playerid][6] = CreatePlayerTextDraw(playerid, 230.000000, 276.500000, GaChaItemName[gachaindex][2]);
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][6], 1);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][6], 0.316666, 1.500000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][6], 400.000000, 86.500000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][6], 0);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][6], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][6], 2);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][6], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][6], 255);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][6], 174);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][6], 1);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][6], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][6], 0);

		PlayerGachaUI[playerid][7] = CreatePlayerTextDraw(playerid, 275.000000, 200.000000, "Preview_Model");
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][7], 5);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][7], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][7], 90.000000, 92.000000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][7], 0);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][7], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][7], 1);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][7], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][7], -1094795651);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][7], 255);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][7], 0);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][7], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][7], 0);
		PlayerTextDrawSetPreviewModel(playerid, PlayerGachaUI[playerid][7], GaChaItemModel[gachaindex][3]);
		PlayerTextDrawSetPreviewRot(playerid, PlayerGachaUI[playerid][7], -10.000000, 0.000000, -20.000000, 1.000000);
		PlayerTextDrawSetPreviewVehCol(playerid, PlayerGachaUI[playerid][7], 1, 1);

		PlayerGachaUI[playerid][8] = CreatePlayerTextDraw(playerid, 320.000000, 276.500000, GaChaItemName[gachaindex][3]);
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][8], 1);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][8], 0.316666, 1.500000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][8], 400.000000, 86.500000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][8], 0);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][8], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][8], 2);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][8], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][8], 255);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][8], 174);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][8], 1);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][8], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][8], 0);

		PlayerGachaUI[playerid][9] = CreatePlayerTextDraw(playerid, 365.000000, 200.000000, "Preview_Model");
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][9], 5);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][9], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][9], 90.000000, 92.000000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][9], 0);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][9], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][9], 1);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][9], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][9], -1094795651);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][9], 255);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][9], 0);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][9], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][9], 0);
		PlayerTextDrawSetPreviewModel(playerid, PlayerGachaUI[playerid][9], GaChaItemModel[gachaindex][4]);
		PlayerTextDrawSetPreviewRot(playerid, PlayerGachaUI[playerid][9], -10.000000, 0.000000, -20.000000, 1.000000);
		PlayerTextDrawSetPreviewVehCol(playerid, PlayerGachaUI[playerid][9], 1, 1);

		PlayerGachaUI[playerid][10] = CreatePlayerTextDraw(playerid, 410.000000, 276.500000, GaChaItemName[gachaindex][4]);
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][10], 1);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][10], 0.316666, 1.500000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][10], 400.000000, 86.500000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][10], 0);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][10], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][10], 2);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][10], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][10], 255);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][10], 174);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][10], 1);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][10], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][10], 0);

		PlayerGachaUI[playerid][11] = CreatePlayerTextDraw(playerid, 455.000000, 200.000000, "Preview_Model");
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][11], 5);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][11], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][11], 90.000000, 92.000000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][11], 0);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][11], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][11], 1);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][11], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][11], -1094795651);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][11], 255);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][11], 0);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][11], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][11], 0);
		PlayerTextDrawSetPreviewModel(playerid, PlayerGachaUI[playerid][11], GaChaItemModel[gachaindex][5]);
		PlayerTextDrawSetPreviewRot(playerid, PlayerGachaUI[playerid][11], -10.000000, 0.000000, -20.000000, 1.000000);
		PlayerTextDrawSetPreviewVehCol(playerid, PlayerGachaUI[playerid][11], 1, 1);

		PlayerGachaUI[playerid][12] = CreatePlayerTextDraw(playerid, 500.000000, 276.500000, GaChaItemName[gachaindex][5]);
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][12], 1);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][12], 0.316666, 1.500000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][12], 400.000000, 86.500000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][12], 0);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][12], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][12], 2);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][12], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][12], 255);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][12], 174);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][12], 1);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][12], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][12], 0);

		PlayerGachaUI[playerid][13] = CreatePlayerTextDraw(playerid, 545.000000, 200.000000, "Preview_Model");
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][13], 5);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][13], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][13], 90.000000, 92.000000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][13], 0);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][13], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][13], 1);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][13], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][13], -1094795651);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][13], 255);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][13], 0);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][13], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][13], 0);
		PlayerTextDrawSetPreviewModel(playerid, PlayerGachaUI[playerid][13], GaChaItemModel[gachaindex][6]);
		PlayerTextDrawSetPreviewRot(playerid, PlayerGachaUI[playerid][13], -10.000000, 0.000000, -20.000000, 1.000000);
		PlayerTextDrawSetPreviewVehCol(playerid, PlayerGachaUI[playerid][13], 1, 1);

		PlayerGachaUI[playerid][14] = CreatePlayerTextDraw(playerid, 590.000000, 276.500000, GaChaItemName[gachaindex][6]);
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][14], 1);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][14], 0.316666, 1.500000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][14], 400.000000, 86.500000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][14], 0);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][14], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][14], 2);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][14], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][14], 255);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][14], 174);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][14], 1);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][14], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][14], 0);

		//format(string, sizeof string, "OPEN %d", Player.Auth[playerid][@itemboxnewbie]);
		PlayerGachaUI[playerid][15] = CreatePlayerTextDraw(playerid, 244.000000, 373.000000, string);
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][15], 1);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][15], 0.258332, 1.750000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][15], 16.500000, 90.500000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][15], 0);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][15], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][15], 2);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][15], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][15], 255);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][15], 12849919);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][15], 1);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][15], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][15], 1);

		PlayerGachaUI[playerid][16] = CreatePlayerTextDraw(playerid, 183.000000, 366.220001, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][16], 4);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][16], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][16], 28.000000, 29.500000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][16], 1);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][16], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][16], 1);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][16], 12849919);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][16], 255);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][16], 50);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][16], 1);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][16], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][16], 0);

		PlayerGachaUI[playerid][17] = CreatePlayerTextDraw(playerid, 278.000000, 366.220001, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][17], 4);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][17], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][17], 28.000000, 29.500000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][17], 1);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][17], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][17], 1);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][17], 12849919);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][17], 255);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][17], 50);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][17], 1);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][17], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][17], 0);

		PlayerGachaUI[playerid][18] = CreatePlayerTextDraw(playerid, 389.000000, 373.000000, "CANCEL");
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][18], 1);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][18], 0.258332, 1.750000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][18], 16.500000, 90.500000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][18], 0);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][18], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][18], 2);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][18], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][18], 255);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][18], -1962934017);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][18], 1);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][18], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][18], 1);

		PlayerGachaUI[playerid][19] = CreatePlayerTextDraw(playerid, 328.000000, 366.220001, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][19], 4);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][19], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][19], 28.000000, 29.500000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][19], 1);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][19], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][19], 1);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][19], -1962934017);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][19], 255);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][19], 50);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][19], 1);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][19], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][19], 0);

		PlayerGachaUI[playerid][20] = CreatePlayerTextDraw(playerid, 423.000000, 366.220001, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][20], 4);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][20], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][20], 28.000000, 29.500000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][20], 1);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][20], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][20], 1);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][20], -1962934017);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][20], 255);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][20], 50);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][20], 1);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][20], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][20], 0);

		PlayerGachaUI[playerid][21] = CreatePlayerTextDraw(playerid, 313.000000, 203.000000, "HUD:radar_centre");
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][21], 4);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][21], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][21], 11.500000, -12.000000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][21], 1);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][21], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][21], 1);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][21], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][21], 255);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][21], 50);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][21], 1);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][21], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][21], 0);

		PlayerGachaUI[playerid][22] = CreatePlayerTextDraw(playerid, 313.000000, 288.000000, "HUD:radar_centre");
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][22], 4);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][22], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][22], 11.500000, 12.000000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][22], 1);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][22], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][22], 1);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][22], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][22], 255);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][22], 50);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][22], 1);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][22], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][22], 0);

		PlayerGachaUI[playerid][23] = CreatePlayerTextDraw(playerid, 244.000000, 402.000000, "OPEN AUTO (FALSE)");
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][23], 1);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][23], 0.258332, 1.750000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][23], 16.500000, 90.500000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][23], 0);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][23], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][23], 2);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][23], -1);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][23], 255);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][23], -1962934017);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][23], 1);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][23], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][23], 1);

		PlayerGachaUI[playerid][24] = CreatePlayerTextDraw(playerid, 183.000000, 395.220001, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][24], 4);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][24], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][24], 28.000000, 29.500000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][24], 1);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][24], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][24], 1);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][24], -1962934017);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][24], 255);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][24], 50);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][24], 1);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][24], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][24], 0);

		PlayerGachaUI[playerid][25] = CreatePlayerTextDraw(playerid, 278.000000, 395.220001, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerGachaUI[playerid][25], 4);
		PlayerTextDrawLetterSize(playerid, PlayerGachaUI[playerid][25], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerGachaUI[playerid][25], 28.000000, 29.500000);
		PlayerTextDrawSetOutline(playerid, PlayerGachaUI[playerid][25], 1);
		PlayerTextDrawSetShadow(playerid, PlayerGachaUI[playerid][25], 0);
		PlayerTextDrawAlignment(playerid, PlayerGachaUI[playerid][25], 1);
		PlayerTextDrawColor(playerid, PlayerGachaUI[playerid][25], -1962934017);
		PlayerTextDrawBackgroundColor(playerid, PlayerGachaUI[playerid][25], 255);
		PlayerTextDrawBoxColor(playerid, PlayerGachaUI[playerid][25], 50);
		PlayerTextDrawUseBox(playerid, PlayerGachaUI[playerid][25], 1);
		PlayerTextDrawSetProportional(playerid, PlayerGachaUI[playerid][25], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerGachaUI[playerid][25], 0);

		PlayerOpeningGachaMenu[playerid] = true;

		for (new i = 0; i < MAX_GACHAS_UI; i ++) {
			PlayerTextDrawShow(playerid, PlayerGachaUI[playerid][i]);
		}
		SelectTextDraw(playerid, 0x8F00C4FF);

		DestroyPlayerUI(playerid);
	}
}