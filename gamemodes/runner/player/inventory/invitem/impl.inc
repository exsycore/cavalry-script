#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

/* ################################################################## */
/* #  ?????????  ???????????    ???????      ?????????  ?????   ????# */
/* # ???????????????????????  ???????????   ????????????????   ???? # */
/* #????    ??? ?   ????  ?  ???     ????? ???     ???  ????  ???   # */
/* #???????????     ????    ????      ????????          ????????    # */
/* # ???????????    ????    ????      ????????          ?????????   # */
/* # ???    ????    ????    ?????     ??? ?????     ??? ???? ?????  # */
/* #???????????     ?????    ???????????   ???????????  ????? ??????# */
/* # ?????????     ?????       ???????      ?????????  ?????   ???? # */
/* ################################################################## */

stock GetItemsIDByName(const name[]) {
	for (new i = 0; i < MAX_ITEMS; i++) {
		if ((strcmp(name, ItemsInfo[i][ItemName]) == 0))
			return i;
	}
	return -1;
}

stock bool:AddItemOn(playerid, itemid, amount) {
    if (playerData[playerid][pInventory][0] != 0 && playerData[playerid][pInventory][1] != 0 && playerData[playerid][pInventory][2] != 0 && playerData[playerid][pInventory][3] != 0 && playerData[playerid][pInventory][4] != 0 && playerData[playerid][pInventory][5] != 0 && playerData[playerid][pInventory][6] != 0 && playerData[playerid][pInventory][7] != 0 && playerData[playerid][pInventory][8] != 0 && playerData[playerid][pInventory][9] != 0 && playerData[playerid][pInventory][10] != 0 && playerData[playerid][pInventory][11] != 0 && playerData[playerid][pInventory][12] != 0 && playerData[playerid][pInventory][13] != 0 && playerData[playerid][pInventory][14] != 0 && playerData[playerid][pInventory][15] != 0 && playerData[playerid][pInventory][16] != 0 && playerData[playerid][pInventory][17] != 0 && playerData[playerid][pInventory][18] != 0 && playerData[playerid][pInventory][19] != 0 && playerData[playerid][pInventory][20] != 0 && playerData[playerid][pInventory][21] != 0 && playerData[playerid][pInventory][22] != 0 && playerData[playerid][pInventory][23] != 0 && playerData[playerid][pInventory][24] != 0 && playerData[playerid][pInventory][25] != 0 && playerData[playerid][pInventory][26] != 0 && playerData[playerid][pInventory][27] != 0 && playerData[playerid][pInventory][28] != 0 && playerData[playerid][pInventory][29] != 0 && playerData[playerid][pInventory][30] != 0 && playerData[playerid][pInventory][31] != 0 && playerData[playerid][pInventory][32] != 0 && playerData[playerid][pInventory][33] != 0 && playerData[playerid][pInventory][34] != 0 && playerData[playerid][pInventory][35] != 0 && playerData[playerid][pInventory][36] != 0 && playerData[playerid][pInventory][37] != 0 && playerData[playerid][pInventory][38] != 0 && playerData[playerid][pInventory][39] != 0 && playerData[playerid][pInventory][40] != 0 && playerData[playerid][pInventory][41] != 0 && playerData[playerid][pInventory][42] != 0 && playerData[playerid][pInventory][43] != 0 && playerData[playerid][pInventory][44] != 0 && playerData[playerid][pInventory][45] != 0 && playerData[playerid][pInventory][46] != 0 && playerData[playerid][pInventory][47] != 0 && playerData[playerid][pInventory][48] != 0 && playerData[playerid][pInventory][49] != 0 && playerData[playerid][pInventory][50] != 0 && playerData[playerid][pInventory][51] != 0 && playerData[playerid][pInventory][52] != 0 && playerData[playerid][pInventory][53] != 0 && playerData[playerid][pInventory][54] != 0 && playerData[playerid][pInventory][55] != 0 && playerData[playerid][pInventory][56] != 0 && playerData[playerid][pInventory][57] != 0 && playerData[playerid][pInventory][58] != 0 && playerData[playerid][pInventory][59] != 0 && playerData[playerid][pInventory][60] != 0 && playerData[playerid][pInventory][61] != 0 && playerData[playerid][pInventory][62] != 0 && playerData[playerid][pInventory][63] != 0 && playerData[playerid][pInventory][64] != 0 && playerData[playerid][pInventory][65] != 0 && playerData[playerid][pInventory][66] != 0 && playerData[playerid][pInventory][67] != 0 && playerData[playerid][pInventory][68] != 0 && playerData[playerid][pInventory][69] != 0 && playerData[playerid][pInventory][70] != 0 && playerData[playerid][pInventory][71] != 0) return va_SendClientMessage(playerid, COLOR_RED, "[������] {FFFFFF}� ��� �� ������� ����� � ���������");
    for (new i = 0; i < 72; i++) {
        if (playerData[playerid][pInventory][i] != itemid) continue;
        playerData[playerid][pInventoryKolvo][i] = amount;
        return true;
    }
    for (new i = 0; i < 72; i++) {
        if (playerData[playerid][pInventory][i] != 0) continue;
        playerData[playerid][pInventory][i] = itemid;
        playerData[playerid][pInventoryKolvo][i] = amount;
        return true;
    }
	SaveInventory(playerid);
    return true;
}

stock SaveInventory(playerid) {
    new query[900];
    new saveinv[900];
    for (new i = 0; i < 72; i++) {
        format(saveinv, 550, "%s%d,", saveinv, playerData[playerid][pInventory][i]);
    }
    format(query,sizeof(query),"UPDATE `players` SET `Item` = '%s' WHERE `playerID` = '%d'", saveinv, playerData[playerid][pID]);
    mysql_tquery(get_handle(), query);
    SaveInventoryKolvo(playerid);
    return true;
}

stock void:SaveInventoryKolvo(playerid) {
    new query[550];
    new saveinv[550];
    for (new i = 0; i < 72; i++) {
        format(saveinv, 550, "%s%d,", saveinv, playerData[playerid][pInventoryKolvo][i]);
    }
    format(query,sizeof(query),"UPDATE `players` SET `ItemKolvo` = '%s' WHERE `playerID` = '%d'", saveinv, playerData[playerid][pID]);
    mysql_tquery(get_handle(), query);
}

stock bool:LoadInventory(playerid) {
    new maximum[400];
    cache_get_value_name(0, "Item", maximum), sscanf(maximum, "p<,>a<i>[72]", playerData[playerid][pInventory]);
    return true;
}

stock bool:LoadInventoryKolvo(playerid) {
	new maximum[400];
	cache_get_value_name(0, "ItemKolvo", maximum), sscanf(maximum, "p<,>a<i>[72]", playerData[playerid][pInventoryKolvo]);
	return true;
}

stock bool:LoadAks(playerid) {
    new maximum[200];
    cache_get_value_name(0, "Aks", maximum), sscanf(maximum, "p<,>a<i>[8]", AksSlot[playerid]);
    return true;
}

stock bool:SaveAks(playerid) {
    new query5[550];
    new saveaks4[1000];
    for (new i = 0; i < 8; i++) {
        format(saveaks4, 1000, "%s%d,", saveaks4, AksSlot[playerid][i]);
    }
    format(query5,sizeof(query5),"UPDATE `players` SET `Aks` = '%s' WHERE `playerID` = '%d'", saveaks4, playerData[playerid][pID]);
    mysql_query(get_handle(), query5, false);
    return true;
}

/*
 * @brief Check if a player owns a specific item.
 * @param playerid Player ID in server.
 * @param itemid Item ID to check.
 * @retval true Player has the item.
 * @retval false Player does not have the item.
 */
stock bool:HasItem(playerid, itemid) {
    for (new i = 0; i < MAX_INVENTORY_SLOTS; i++) {
        if (playerData[playerid][pInventory][i] == itemid) {
            return true;
        }
    }
    return false;
}

/*
 * @brief Get the total amount of a specific item a player has.
 * @param playerid Player ID in server.
 * @param itemid Item ID to check.
 * @return Total quantity of the item across all slots, or 0 if not found.
 */
stock GetItemAmount(playerid, itemid) {
    new amount = 0;
    for (new i = 0; i < MAX_INVENTORY_SLOTS; i++) {
        if (playerData[playerid][pInventory][i] == itemid) {
            amount += playerData[playerid][pInventoryKolvo][i];
        }
    }
    return amount;
}

stock bool:OnPlayerClickSlot(playerid, slot) {
    if (playerData[playerid][pInventoryKolvo][slot] >= 2) {
	    for (new i = 0; i < 7; i++) {
			DestroyPlayerTD(playerid, fstd_p[playerid][i]);
		}
		for (new i = 0; i < 8; i++) {
			DestroyPlayerTD(playerid, dropmenu[playerid][i]);
		}
        for (new i = 0; i < 6; i++) {
		    DestroyPlayerTD(playerid, InfoItems[playerid][i]);
		}
	} else {
	    for (new i = 0; i < 6; i++) {
			DestroyPlayerTD(playerid, InfoItems[playerid][i]);
		}
	    for (new i = 0; i < 7; i++) {
		    DestroyPlayerTD(playerid, fstd_p[playerid][i]);
		}
	}
	new IDS = playerData[playerid][pInventory][slot];
	new string[24];
	format(string, sizeof(string), "%s", ItemsInfo[IDS][ItemUse]);

	new Float:Y = playerData[playerid][pInvPos_Y], Float:X = playerData[playerid][pInvPos_X];
	new row = slot / 6;
	new col = slot % 6;

	if (slot >= 36) {
		row = (slot - 36) / 6;
		col = (slot - 36) % 6;
	}

	new Float:debil = 30.5 * row;
	new Float:idiot = 26.5 * col;

    if (playerData[playerid][pInventoryKolvo][slot] >= 2) {
        if (ItemsInfo[playerData[playerid][pInventory][PickInvent[playerid]]][itemused] == true) {
		    if (playerData[playerid][pInventory][slot] != 313) {
				dropmenu[playerid][7] = CreatePlayerTextDraw(playerid, 451.309204+X+idiot, 134.350006+Y+debil, "particle:shad_bike");
				PlayerTextDrawLetterSize(playerid, dropmenu[playerid][7], 0.480000, 1.120000);
				PlayerTextDrawTextSize(playerid, dropmenu[playerid][7], 10.625000, 65.000000);
				PlayerTextDrawAlignment(playerid, dropmenu[playerid][7], 0);
				PlayerTextDrawColor(playerid, dropmenu[playerid][7], 0x00000070);
				PlayerTextDrawUseBox(playerid, dropmenu[playerid][7], 0);
				PlayerTextDrawBoxColor(playerid, dropmenu[playerid][7], 0x80808080);
				PlayerTextDrawSetShadow(playerid, dropmenu[playerid][7], 2);
				PlayerTextDrawSetOutline(playerid, dropmenu[playerid][7], 0);
				PlayerTextDrawBackgroundColor(playerid, dropmenu[playerid][7], 0x000000FF);
				PlayerTextDrawFont(playerid, dropmenu[playerid][7], 4);
				PlayerTextDrawSetProportional(playerid, dropmenu[playerid][7], 1);
				PlayerTextDrawSetSelectable(playerid, dropmenu[playerid][7], 0);

				dropmenu[playerid][6] = CreatePlayerTextDraw(playerid, 493.809204+X+idiot, 134.350006+Y+debil, "particle:shad_bike");
				PlayerTextDrawLetterSize(playerid, dropmenu[playerid][6], 0.480000, 1.120000);
				PlayerTextDrawTextSize(playerid, dropmenu[playerid][6], 10.625000, 65.000000);
				PlayerTextDrawAlignment(playerid, dropmenu[playerid][6], 0);
				PlayerTextDrawColor(playerid, dropmenu[playerid][6], 0x00000070);
				PlayerTextDrawUseBox(playerid, dropmenu[playerid][6], 0);
				PlayerTextDrawBoxColor(playerid, dropmenu[playerid][6], 0x80808080);
				PlayerTextDrawSetShadow(playerid, dropmenu[playerid][6], 2);
				PlayerTextDrawSetOutline(playerid, dropmenu[playerid][6], 0);
				PlayerTextDrawBackgroundColor(playerid, dropmenu[playerid][6], 0x000000FF);
				PlayerTextDrawFont(playerid, dropmenu[playerid][6], 4);
				PlayerTextDrawSetProportional(playerid, dropmenu[playerid][6], 1);
				PlayerTextDrawSetSelectable(playerid, dropmenu[playerid][6], 0);

				dropmenu[playerid][5] = CreatePlayerTextDraw(playerid, 500.371704+X+idiot, 135.850006+Y+debil, "usebox");
				PlayerTextDrawLetterSize(playerid, dropmenu[playerid][5], 0.000000, 6.880250);
				PlayerTextDrawTextSize(playerid, dropmenu[playerid][5], 455.121704+X+idiot, 0.000000);
				PlayerTextDrawAlignment(playerid, dropmenu[playerid][5], 1);
				PlayerTextDrawColor(playerid, dropmenu[playerid][5], 0xE1E1E1FF);
				PlayerTextDrawUseBox(playerid, dropmenu[playerid][5], 1);
				PlayerTextDrawBoxColor(playerid, dropmenu[playerid][5], 0x000000AA);
				PlayerTextDrawSetShadow(playerid, dropmenu[playerid][5], 2);
				PlayerTextDrawSetOutline(playerid, dropmenu[playerid][5], 0);
				PlayerTextDrawBackgroundColor(playerid, dropmenu[playerid][5], 0x000000FF);
				PlayerTextDrawFont(playerid, dropmenu[playerid][5], 0);
				PlayerTextDrawSetProportional(playerid, dropmenu[playerid][5], 1);
				PlayerTextDrawSetSelectable(playerid, dropmenu[playerid][5], 0);

				dropmenu[playerid][4] = CreatePlayerTextDraw(playerid, 477.871704+X+idiot, 136.516678+Y+debil, string);
				PlayerTextDrawLetterSize(playerid, dropmenu[playerid][4], 0.159033, 0.818733);
				PlayerTextDrawTextSize(playerid, dropmenu[playerid][4], 7.368598, 40.375000);
				PlayerTextDrawAlignment(playerid, dropmenu[playerid][4], 2);
				PlayerTextDrawColor(playerid, dropmenu[playerid][4], 0xFFFFFFFF);
				PlayerTextDrawUseBox(playerid, dropmenu[playerid][4], 0);
				PlayerTextDrawBoxColor(playerid, dropmenu[playerid][4], 0x80808080);
				PlayerTextDrawSetShadow(playerid, dropmenu[playerid][4], 0);
				PlayerTextDrawSetOutline(playerid, dropmenu[playerid][4], 1);
				PlayerTextDrawBackgroundColor(playerid, dropmenu[playerid][4], 0x00000000);
				PlayerTextDrawFont(playerid, dropmenu[playerid][4], 1);
				PlayerTextDrawSetProportional(playerid, dropmenu[playerid][4], 1);
				PlayerTextDrawSetSelectable(playerid, dropmenu[playerid][4], 1);

				dropmenu[playerid][3] = CreatePlayerTextDraw(playerid, 477.871704+X+idiot, 149.516678+Y+debil, "DROP");
				PlayerTextDrawLetterSize(playerid, dropmenu[playerid][3], 0.154033, 0.818733);
				PlayerTextDrawTextSize(playerid, dropmenu[playerid][3], 7.368598, 40.375000);
				PlayerTextDrawAlignment(playerid, dropmenu[playerid][3], 2);
				PlayerTextDrawColor(playerid, dropmenu[playerid][3], 0xFFFFFFFF);
				PlayerTextDrawUseBox(playerid, dropmenu[playerid][3], 0);
				PlayerTextDrawBoxColor(playerid, dropmenu[playerid][3], 0x80808080);
				PlayerTextDrawSetShadow(playerid, dropmenu[playerid][3], 0);
				PlayerTextDrawSetOutline(playerid, dropmenu[playerid][3], 1);
				PlayerTextDrawBackgroundColor(playerid, dropmenu[playerid][3], 0x00000000);
				PlayerTextDrawFont(playerid, dropmenu[playerid][3], 1);
				PlayerTextDrawSetProportional(playerid, dropmenu[playerid][3], 1);
				PlayerTextDrawSetSelectable(playerid, dropmenu[playerid][3], 1);

				dropmenu[playerid][2] = CreatePlayerTextDraw(playerid, 477.871704+X+idiot, 162.516678+Y+debil, "SPLIT");
				PlayerTextDrawLetterSize(playerid, dropmenu[playerid][2], 0.149033, 0.818733);
				PlayerTextDrawTextSize(playerid, dropmenu[playerid][2], 7.368598, 40.375000);
				PlayerTextDrawAlignment(playerid, dropmenu[playerid][2], 2);
				PlayerTextDrawColor(playerid, dropmenu[playerid][2], 0xFFFFFFFF);
				PlayerTextDrawUseBox(playerid, dropmenu[playerid][2], 0);
				PlayerTextDrawBoxColor(playerid, dropmenu[playerid][2], 0x80808080);
				PlayerTextDrawSetShadow(playerid, dropmenu[playerid][2], 0);
				PlayerTextDrawSetOutline(playerid, dropmenu[playerid][2], 1);
				PlayerTextDrawBackgroundColor(playerid, dropmenu[playerid][2], 0x00000000);
				PlayerTextDrawFont(playerid, dropmenu[playerid][2], 1);
				PlayerTextDrawSetProportional(playerid, dropmenu[playerid][2], 1);
				PlayerTextDrawSetSelectable(playerid, dropmenu[playerid][2], 1);

				dropmenu[playerid][1] = CreatePlayerTextDraw(playerid, 477.871704+X+idiot, 175.516678+Y+debil, "INFO");
				PlayerTextDrawLetterSize(playerid, dropmenu[playerid][1], 0.154033, 0.818733);
				PlayerTextDrawTextSize(playerid, dropmenu[playerid][1], 7.368598, 40.375000);
				PlayerTextDrawAlignment(playerid, dropmenu[playerid][1], 2);
				PlayerTextDrawColor(playerid, dropmenu[playerid][1], 0xFFFFFFFF);
				PlayerTextDrawUseBox(playerid, dropmenu[playerid][1], 0);
				PlayerTextDrawBoxColor(playerid, dropmenu[playerid][1], 0x80808080);
				PlayerTextDrawSetShadow(playerid, dropmenu[playerid][1], 0);
				PlayerTextDrawSetOutline(playerid, dropmenu[playerid][1], 1);
				PlayerTextDrawBackgroundColor(playerid, dropmenu[playerid][1], 0x00000000);
				PlayerTextDrawFont(playerid, dropmenu[playerid][1], 1);
				PlayerTextDrawSetProportional(playerid, dropmenu[playerid][1], 1);
				PlayerTextDrawSetSelectable(playerid, dropmenu[playerid][1], 1);

				dropmenu[playerid][0] = CreatePlayerTextDraw(playerid, 477.871704+X+idiot, 188.516678+Y+debil, "CLOSE");
				PlayerTextDrawLetterSize(playerid, dropmenu[playerid][0], 0.149033, 0.818733);
				PlayerTextDrawTextSize(playerid, dropmenu[playerid][0], 7.368598, 40.375000);
				PlayerTextDrawAlignment(playerid, dropmenu[playerid][0], 2);
				PlayerTextDrawColor(playerid, dropmenu[playerid][0], 0xBE5555FF);
				PlayerTextDrawUseBox(playerid, dropmenu[playerid][0], 0);
				PlayerTextDrawBoxColor(playerid, dropmenu[playerid][0], 0x80808080);
				PlayerTextDrawSetShadow(playerid, dropmenu[playerid][0], 0);
				PlayerTextDrawSetOutline(playerid, dropmenu[playerid][0], 1);
				PlayerTextDrawBackgroundColor(playerid, dropmenu[playerid][0], 0x00000000);
				PlayerTextDrawFont(playerid, dropmenu[playerid][0], 1);
				PlayerTextDrawSetProportional(playerid, dropmenu[playerid][0], 1);
				PlayerTextDrawSetSelectable(playerid, dropmenu[playerid][0], 1);
				PlayerTextDrawShow(playerid, dropmenu[playerid][0]),PlayerTextDrawShow(playerid, dropmenu[playerid][1]), PlayerTextDrawShow(playerid, dropmenu[playerid][2]), PlayerTextDrawShow(playerid, dropmenu[playerid][3]); PlayerTextDrawShow(playerid, dropmenu[playerid][4]); PlayerTextDrawShow(playerid, dropmenu[playerid][5]); PlayerTextDrawShow(playerid, dropmenu[playerid][6]); PlayerTextDrawShow(playerid, dropmenu[playerid][7]); // ????????????? ????.
			}
		} else {
		    fstd_p[playerid][6] = CreatePlayerTextDraw(playerid, 451.289215+X+idiot, 140.350006+Y+debil, "particle:shad_bike");
			PlayerTextDrawLetterSize(playerid, fstd_p[playerid][6], 0.480000, 1.120000);
			PlayerTextDrawTextSize(playerid, fstd_p[playerid][6], 10.625000, 52.000000);
			PlayerTextDrawAlignment(playerid, fstd_p[playerid][6], 0);
			PlayerTextDrawColor(playerid, fstd_p[playerid][6], 0x00000070);
			PlayerTextDrawUseBox(playerid, fstd_p[playerid][6], 0);
			PlayerTextDrawBoxColor(playerid, fstd_p[playerid][6], 0x80808080);
			PlayerTextDrawSetShadow(playerid, fstd_p[playerid][6], 2);
			PlayerTextDrawSetOutline(playerid, fstd_p[playerid][6], 0);
			PlayerTextDrawBackgroundColor(playerid, fstd_p[playerid][6], 0x000000FF);
			PlayerTextDrawFont(playerid, fstd_p[playerid][6], 4);
			PlayerTextDrawSetProportional(playerid, fstd_p[playerid][6], 1);
			PlayerTextDrawSetSelectable(playerid, fstd_p[playerid][6], 0);

			fstd_p[playerid][5] = CreatePlayerTextDraw(playerid, 493.789215+X+idiot, 140.350006+Y+debil, "particle:shad_bike");
			PlayerTextDrawLetterSize(playerid, fstd_p[playerid][5], 0.480000, 1.120000);
			PlayerTextDrawTextSize(playerid, fstd_p[playerid][5], 10.625000, 52.000000);
			PlayerTextDrawAlignment(playerid, fstd_p[playerid][5], 0);
			PlayerTextDrawColor(playerid, fstd_p[playerid][5], 0x00000070);
			PlayerTextDrawUseBox(playerid, fstd_p[playerid][5], 0);
			PlayerTextDrawBoxColor(playerid, fstd_p[playerid][5], 0x80808080);
			PlayerTextDrawSetShadow(playerid, fstd_p[playerid][5], 2);
			PlayerTextDrawSetOutline(playerid, fstd_p[playerid][5], 0);
			PlayerTextDrawBackgroundColor(playerid, fstd_p[playerid][5], 0x000000FF);
			PlayerTextDrawFont(playerid, fstd_p[playerid][5], 4);
			PlayerTextDrawSetProportional(playerid, fstd_p[playerid][5], 1);
			PlayerTextDrawSetSelectable(playerid, fstd_p[playerid][5], 0);

			fstd_p[playerid][4] = CreatePlayerTextDraw(playerid, 500.351715+X+idiot, 141.850006+Y+debil, "usebox");
			PlayerTextDrawLetterSize(playerid, fstd_p[playerid][4], 0.000000, 5.439200);
			PlayerTextDrawTextSize(playerid, fstd_p[playerid][4], 455.101715+X+idiot, 0.000000);
			PlayerTextDrawAlignment(playerid, fstd_p[playerid][4], 1);
			PlayerTextDrawColor(playerid, fstd_p[playerid][4], 0xE1E1E1FF);
			PlayerTextDrawUseBox(playerid, fstd_p[playerid][4], 1);
			PlayerTextDrawBoxColor(playerid, fstd_p[playerid][4], 0x000000AA);
			PlayerTextDrawSetShadow(playerid, fstd_p[playerid][4], 2);
			PlayerTextDrawSetOutline(playerid, fstd_p[playerid][4], 0);
			PlayerTextDrawBackgroundColor(playerid, fstd_p[playerid][4], 0x000000FF);
			PlayerTextDrawFont(playerid, fstd_p[playerid][4], 0);
			PlayerTextDrawSetProportional(playerid, fstd_p[playerid][4], 1);
			PlayerTextDrawSetSelectable(playerid, fstd_p[playerid][4], 0);

			fstd_p[playerid][3] = CreatePlayerTextDraw(playerid, 477.851715+X+idiot, 142.516678+Y+debil, string);
			PlayerTextDrawLetterSize(playerid, fstd_p[playerid][3], 0.159033, 0.818733);
			PlayerTextDrawTextSize(playerid, fstd_p[playerid][3], 7.368598, 40.375000);
			PlayerTextDrawAlignment(playerid, fstd_p[playerid][3], 2);
			PlayerTextDrawColor(playerid, fstd_p[playerid][3], 0xFFFFFFFF);
			PlayerTextDrawUseBox(playerid, fstd_p[playerid][3], 0);
			PlayerTextDrawBoxColor(playerid, fstd_p[playerid][3], 0x80808080);
			PlayerTextDrawSetShadow(playerid, fstd_p[playerid][3], 0);
			PlayerTextDrawSetOutline(playerid, fstd_p[playerid][3], 1);
			PlayerTextDrawBackgroundColor(playerid, fstd_p[playerid][3], 0x00000000);
			PlayerTextDrawFont(playerid, fstd_p[playerid][3], 1);
			PlayerTextDrawSetProportional(playerid, fstd_p[playerid][3], 1);
			PlayerTextDrawSetSelectable(playerid, fstd_p[playerid][3], 1);

			fstd_p[playerid][2] = CreatePlayerTextDraw(playerid, 477.851715+X+idiot, 155.516678+Y+debil, "DROP");
			PlayerTextDrawLetterSize(playerid, fstd_p[playerid][2], 0.154033, 0.818733);
			PlayerTextDrawTextSize(playerid, fstd_p[playerid][2], 7.368598, 40.375000);
			PlayerTextDrawAlignment(playerid, fstd_p[playerid][2], 2);
			PlayerTextDrawColor(playerid, fstd_p[playerid][2], 0xFFFFFFFF);
			PlayerTextDrawUseBox(playerid, fstd_p[playerid][2], 0);
			PlayerTextDrawBoxColor(playerid, fstd_p[playerid][2], 0x80808080);
			PlayerTextDrawSetShadow(playerid, fstd_p[playerid][2], 0);
			PlayerTextDrawSetOutline(playerid, fstd_p[playerid][2], 1);
			PlayerTextDrawBackgroundColor(playerid, fstd_p[playerid][2], 0x00000000);
			PlayerTextDrawFont(playerid, fstd_p[playerid][2], 1);
			PlayerTextDrawSetProportional(playerid, fstd_p[playerid][2], 1);
			PlayerTextDrawSetSelectable(playerid, fstd_p[playerid][2], 1);

			fstd_p[playerid][1] = CreatePlayerTextDraw(playerid, 477.851715+X+idiot, 168.516678+Y+debil, "INFO");
			PlayerTextDrawLetterSize(playerid, fstd_p[playerid][1], 0.154033, 0.818733);
			PlayerTextDrawTextSize(playerid, fstd_p[playerid][1], 7.368598, 40.375000);
			PlayerTextDrawAlignment(playerid, fstd_p[playerid][1], 2);
			PlayerTextDrawColor(playerid, fstd_p[playerid][1], 0xFFFFFFFF);
			PlayerTextDrawUseBox(playerid, fstd_p[playerid][1], 0);
			PlayerTextDrawBoxColor(playerid, fstd_p[playerid][1], 0x80808080);
			PlayerTextDrawSetShadow(playerid, fstd_p[playerid][1], 0);
			PlayerTextDrawSetOutline(playerid, fstd_p[playerid][1], 1);
			PlayerTextDrawBackgroundColor(playerid, fstd_p[playerid][1], 0x00000000);
			PlayerTextDrawFont(playerid, fstd_p[playerid][1], 1);
			PlayerTextDrawSetProportional(playerid, fstd_p[playerid][1], 1);
			PlayerTextDrawSetSelectable(playerid, fstd_p[playerid][1], 1);

			fstd_p[playerid][0] = CreatePlayerTextDraw(playerid, 477.851715+X+idiot, 181.516678+Y+debil, "CLOSE");
			PlayerTextDrawLetterSize(playerid, fstd_p[playerid][0], 0.149033, 0.818733);
			PlayerTextDrawTextSize(playerid, fstd_p[playerid][0], 7.368598, 40.375000);
			PlayerTextDrawAlignment(playerid, fstd_p[playerid][0], 2);
			PlayerTextDrawColor(playerid, fstd_p[playerid][0], 0xBE5555FF);
			PlayerTextDrawUseBox(playerid, fstd_p[playerid][0], 0);
			PlayerTextDrawBoxColor(playerid, fstd_p[playerid][0], 0x80808080);
			PlayerTextDrawSetShadow(playerid, fstd_p[playerid][0], 0);
			PlayerTextDrawSetOutline(playerid, fstd_p[playerid][0], 1);
			PlayerTextDrawBackgroundColor(playerid, fstd_p[playerid][0], 0x00000000);
			PlayerTextDrawFont(playerid, fstd_p[playerid][0], 1);
			PlayerTextDrawSetProportional(playerid, fstd_p[playerid][0], 1);
			PlayerTextDrawSetSelectable(playerid, fstd_p[playerid][0], 1);
		}
	} else if (playerData[playerid][pInventory][slot] != 313) {
	    if (ItemsInfo[playerData[playerid][pInventory][PickInvent[playerid]]][itemused] == true) {
	   	    fstd_p[playerid][6] = CreatePlayerTextDraw(playerid, 451.289215+X+idiot, 140.350006+Y+debil, "particle:shad_bike");
			PlayerTextDrawLetterSize(playerid, fstd_p[playerid][6], 0.480000, 1.120000);
			PlayerTextDrawTextSize(playerid, fstd_p[playerid][6], 10.625000, 52.000000);
			PlayerTextDrawAlignment(playerid, fstd_p[playerid][6], 0);
			PlayerTextDrawColor(playerid, fstd_p[playerid][6], 0x00000070);
			PlayerTextDrawUseBox(playerid, fstd_p[playerid][6], 0);
			PlayerTextDrawBoxColor(playerid, fstd_p[playerid][6], 0x80808080);
			PlayerTextDrawSetShadow(playerid, fstd_p[playerid][6], 2);
			PlayerTextDrawSetOutline(playerid, fstd_p[playerid][6], 0);
			PlayerTextDrawBackgroundColor(playerid, fstd_p[playerid][6], 0x000000FF);
			PlayerTextDrawFont(playerid, fstd_p[playerid][6], 4);
			PlayerTextDrawSetProportional(playerid, fstd_p[playerid][6], 1);
			PlayerTextDrawSetSelectable(playerid, fstd_p[playerid][6], 0);

			fstd_p[playerid][5] = CreatePlayerTextDraw(playerid, 493.789215+X+idiot, 140.350006+Y+debil, "particle:shad_bike");
			PlayerTextDrawLetterSize(playerid, fstd_p[playerid][5], 0.480000, 1.120000);
			PlayerTextDrawTextSize(playerid, fstd_p[playerid][5], 10.625000, 52.000000);
			PlayerTextDrawAlignment(playerid, fstd_p[playerid][5], 0);
			PlayerTextDrawColor(playerid, fstd_p[playerid][5], 0x00000070);
			PlayerTextDrawUseBox(playerid, fstd_p[playerid][5], 0);
			PlayerTextDrawBoxColor(playerid, fstd_p[playerid][5], 0x80808080);
			PlayerTextDrawSetShadow(playerid, fstd_p[playerid][5], 2);
			PlayerTextDrawSetOutline(playerid, fstd_p[playerid][5], 0);
			PlayerTextDrawBackgroundColor(playerid, fstd_p[playerid][5], 0x000000FF);
			PlayerTextDrawFont(playerid, fstd_p[playerid][5], 4);
			PlayerTextDrawSetProportional(playerid, fstd_p[playerid][5], 1);
			PlayerTextDrawSetSelectable(playerid, fstd_p[playerid][5], 0);

			fstd_p[playerid][4] = CreatePlayerTextDraw(playerid, 500.351715+X+idiot, 141.850006+Y+debil, "usebox");
			PlayerTextDrawLetterSize(playerid, fstd_p[playerid][4], 0.000000, 5.439200);
			PlayerTextDrawTextSize(playerid, fstd_p[playerid][4], 455.101715+X+idiot, 0.000000);
			PlayerTextDrawAlignment(playerid, fstd_p[playerid][4], 1);
			PlayerTextDrawColor(playerid, fstd_p[playerid][4], 0xE1E1E1FF);
			PlayerTextDrawUseBox(playerid, fstd_p[playerid][4], 1);
			PlayerTextDrawBoxColor(playerid, fstd_p[playerid][4], 0x000000AA);
			PlayerTextDrawSetShadow(playerid, fstd_p[playerid][4], 2);
			PlayerTextDrawSetOutline(playerid, fstd_p[playerid][4], 0);
			PlayerTextDrawBackgroundColor(playerid, fstd_p[playerid][4], 0x000000FF);
			PlayerTextDrawFont(playerid, fstd_p[playerid][4], 0);
			PlayerTextDrawSetProportional(playerid, fstd_p[playerid][4], 1);
			PlayerTextDrawSetSelectable(playerid, fstd_p[playerid][4], 0);

			fstd_p[playerid][3] = CreatePlayerTextDraw(playerid, 477.851715+X+idiot, 142.516678+Y+debil, string);
			PlayerTextDrawLetterSize(playerid, fstd_p[playerid][3], 0.159033, 0.818733);
			PlayerTextDrawTextSize(playerid, fstd_p[playerid][3], 7.368598, 40.375000);
			PlayerTextDrawAlignment(playerid, fstd_p[playerid][3], 2);
			PlayerTextDrawColor(playerid, fstd_p[playerid][3], 0xFFFFFFFF);
			PlayerTextDrawUseBox(playerid, fstd_p[playerid][3], 0);
			PlayerTextDrawBoxColor(playerid, fstd_p[playerid][3], 0x80808080);
			PlayerTextDrawSetShadow(playerid, fstd_p[playerid][3], 0);
			PlayerTextDrawSetOutline(playerid, fstd_p[playerid][3], 1);
			PlayerTextDrawBackgroundColor(playerid, fstd_p[playerid][3], 0x00000000);
			PlayerTextDrawFont(playerid, fstd_p[playerid][3], 1);
			PlayerTextDrawSetProportional(playerid, fstd_p[playerid][3], 1);
			PlayerTextDrawSetSelectable(playerid, fstd_p[playerid][3], 1);

			fstd_p[playerid][2] = CreatePlayerTextDraw(playerid, 477.851715+X+idiot, 155.516678+Y+debil, "DROP");
			PlayerTextDrawLetterSize(playerid, fstd_p[playerid][2], 0.154033, 0.818733);
			PlayerTextDrawTextSize(playerid, fstd_p[playerid][2], 7.368598, 40.375000);
			PlayerTextDrawAlignment(playerid, fstd_p[playerid][2], 2);
			PlayerTextDrawColor(playerid, fstd_p[playerid][2], 0xFFFFFFFF);
			PlayerTextDrawUseBox(playerid, fstd_p[playerid][2], 0);
			PlayerTextDrawBoxColor(playerid, fstd_p[playerid][2], 0x80808080);
			PlayerTextDrawSetShadow(playerid, fstd_p[playerid][2], 0);
			PlayerTextDrawSetOutline(playerid, fstd_p[playerid][2], 1);
			PlayerTextDrawBackgroundColor(playerid, fstd_p[playerid][2], 0x00000000);
			PlayerTextDrawFont(playerid, fstd_p[playerid][2], 1);
			PlayerTextDrawSetProportional(playerid, fstd_p[playerid][2], 1);
			PlayerTextDrawSetSelectable(playerid, fstd_p[playerid][2], 1);

			fstd_p[playerid][1] = CreatePlayerTextDraw(playerid, 477.851715+X+idiot, 168.516678+Y+debil, "INFO");
			PlayerTextDrawLetterSize(playerid, fstd_p[playerid][1], 0.154033, 0.818733);
			PlayerTextDrawTextSize(playerid, fstd_p[playerid][1], 7.368598, 40.375000);
			PlayerTextDrawAlignment(playerid, fstd_p[playerid][1], 2);
			PlayerTextDrawColor(playerid, fstd_p[playerid][1], 0xFFFFFFFF);
			PlayerTextDrawUseBox(playerid, fstd_p[playerid][1], 0);
			PlayerTextDrawBoxColor(playerid, fstd_p[playerid][1], 0x80808080);
			PlayerTextDrawSetShadow(playerid, fstd_p[playerid][1], 0);
			PlayerTextDrawSetOutline(playerid, fstd_p[playerid][1], 1);
			PlayerTextDrawBackgroundColor(playerid, fstd_p[playerid][1], 0x00000000);
			PlayerTextDrawFont(playerid, fstd_p[playerid][1], 1);
			PlayerTextDrawSetProportional(playerid, fstd_p[playerid][1], 1);
			PlayerTextDrawSetSelectable(playerid, fstd_p[playerid][1], 1);

			fstd_p[playerid][0] = CreatePlayerTextDraw(playerid, 477.851715+X+idiot, 181.516678+Y+debil, "CLOSE");
			PlayerTextDrawLetterSize(playerid, fstd_p[playerid][0], 0.149033, 0.818733);
			PlayerTextDrawTextSize(playerid, fstd_p[playerid][0], 7.368598, 40.375000);
			PlayerTextDrawAlignment(playerid, fstd_p[playerid][0], 2);
			PlayerTextDrawColor(playerid, fstd_p[playerid][0], 0xBE5555FF);
			PlayerTextDrawUseBox(playerid, fstd_p[playerid][0], 0);
			PlayerTextDrawBoxColor(playerid, fstd_p[playerid][0], 0x80808080);
			PlayerTextDrawSetShadow(playerid, fstd_p[playerid][0], 0);
			PlayerTextDrawSetOutline(playerid, fstd_p[playerid][0], 1);
			PlayerTextDrawBackgroundColor(playerid, fstd_p[playerid][0], 0x00000000);
			PlayerTextDrawFont(playerid, fstd_p[playerid][0], 1);
			PlayerTextDrawSetProportional(playerid, fstd_p[playerid][0], 1);
			PlayerTextDrawSetSelectable(playerid, fstd_p[playerid][0], 1);
			PlayerTextDrawShow(playerid, fstd_p[playerid][0]),PlayerTextDrawShow(playerid, fstd_p[playerid][1]), PlayerTextDrawShow(playerid, fstd_p[playerid][2]); PlayerTextDrawShow(playerid, fstd_p[playerid][3]); PlayerTextDrawShow(playerid, fstd_p[playerid][4]); PlayerTextDrawShow(playerid, fstd_p[playerid][5]); PlayerTextDrawShow(playerid, fstd_p[playerid][6]); // ????????????? ????.
		} else {
		    InfoItems[playerid][5] = CreatePlayerTextDraw(playerid, 451.289215+X+idiot, 140.350006+Y+debil, "particle:shad_bike");
			PlayerTextDrawLetterSize(playerid, InfoItems[playerid][5], 0.480000, 1.120000);
			PlayerTextDrawTextSize(playerid, InfoItems[playerid][5], 10.625000, 39.000000);
			PlayerTextDrawAlignment(playerid, InfoItems[playerid][5], 0);
			PlayerTextDrawColor(playerid, InfoItems[playerid][5], 0x00000070);
			PlayerTextDrawUseBox(playerid, InfoItems[playerid][5], 0);
			PlayerTextDrawBoxColor(playerid, InfoItems[playerid][5], 0x80808080);
			PlayerTextDrawSetShadow(playerid, InfoItems[playerid][5], 2);
			PlayerTextDrawSetOutline(playerid, InfoItems[playerid][5], 0);
			PlayerTextDrawBackgroundColor(playerid, InfoItems[playerid][5], 0x000000FF);
			PlayerTextDrawFont(playerid, InfoItems[playerid][5], 4);
			PlayerTextDrawSetProportional(playerid, InfoItems[playerid][5], 1);
			PlayerTextDrawSetSelectable(playerid, InfoItems[playerid][5], 0);

			InfoItems[playerid][4] = CreatePlayerTextDraw(playerid, 493.789215+X+idiot, 140.350006+Y+debil, "particle:shad_bike");
			PlayerTextDrawLetterSize(playerid, InfoItems[playerid][4], 0.480000, 1.120000);
			PlayerTextDrawTextSize(playerid, InfoItems[playerid][4], 10.625000, 39.000000);
			PlayerTextDrawAlignment(playerid, InfoItems[playerid][4], 0);
			PlayerTextDrawColor(playerid, InfoItems[playerid][4], 0x00000070);
			PlayerTextDrawUseBox(playerid, InfoItems[playerid][4], 0);
			PlayerTextDrawBoxColor(playerid, InfoItems[playerid][4], 0x80808080);
			PlayerTextDrawSetShadow(playerid, InfoItems[playerid][4], 2);
			PlayerTextDrawSetOutline(playerid, InfoItems[playerid][4], 0);
			PlayerTextDrawBackgroundColor(playerid, InfoItems[playerid][4], 0x000000FF);
			PlayerTextDrawFont(playerid, InfoItems[playerid][4], 4);
			PlayerTextDrawSetProportional(playerid, InfoItems[playerid][4], 1);
			PlayerTextDrawSetSelectable(playerid, InfoItems[playerid][4], 0);

			InfoItems[playerid][3] = CreatePlayerTextDraw(playerid, 500.351715+X+idiot, 141.850006+Y+debil, "usebox");
			PlayerTextDrawLetterSize(playerid, InfoItems[playerid][3], 0.000000, 3.998150);
			PlayerTextDrawTextSize(playerid, InfoItems[playerid][3], 455.101715+X+idiot, 0.000000);
			PlayerTextDrawAlignment(playerid, InfoItems[playerid][3], 1);
			PlayerTextDrawColor(playerid, InfoItems[playerid][3], 0xE1E1E1FF);
			PlayerTextDrawUseBox(playerid, InfoItems[playerid][3], 1);
			PlayerTextDrawBoxColor(playerid, InfoItems[playerid][3], 0x000000AA);
			PlayerTextDrawSetShadow(playerid, InfoItems[playerid][3], 2);
			PlayerTextDrawSetOutline(playerid, InfoItems[playerid][3], 0);
			PlayerTextDrawBackgroundColor(playerid, InfoItems[playerid][3], 0x000000FF);
			PlayerTextDrawFont(playerid, InfoItems[playerid][3], 0);
			PlayerTextDrawSetProportional(playerid, InfoItems[playerid][3], 1);
			PlayerTextDrawSetSelectable(playerid, InfoItems[playerid][3], 0);

			InfoItems[playerid][2] = CreatePlayerTextDraw(playerid, 477.851715+X+idiot, 142.516678+Y+debil, string);
			PlayerTextDrawLetterSize(playerid, InfoItems[playerid][2], 0.159033, 0.818733);
			PlayerTextDrawTextSize(playerid, InfoItems[playerid][2], 7.368598, 40.375000);
			PlayerTextDrawAlignment(playerid, InfoItems[playerid][2], 2);
			PlayerTextDrawColor(playerid, InfoItems[playerid][2], 0xFFFFFFFF);
			PlayerTextDrawUseBox(playerid, InfoItems[playerid][2], 0);
			PlayerTextDrawBoxColor(playerid, InfoItems[playerid][2], 0x80808080);
			PlayerTextDrawSetShadow(playerid, InfoItems[playerid][2], 0);
			PlayerTextDrawSetOutline(playerid, InfoItems[playerid][2], 1);
			PlayerTextDrawBackgroundColor(playerid, InfoItems[playerid][2], 0x00000000);
			PlayerTextDrawFont(playerid, InfoItems[playerid][2], 1);
			PlayerTextDrawSetProportional(playerid, InfoItems[playerid][2], 1);
			PlayerTextDrawSetSelectable(playerid, InfoItems[playerid][2], 1);

			InfoItems[playerid][1] = CreatePlayerTextDraw(playerid, 477.851715+X+idiot, 155.516678+Y+debil, "INFO");
			PlayerTextDrawLetterSize(playerid, InfoItems[playerid][1], 0.154033, 0.818733);
			PlayerTextDrawTextSize(playerid, InfoItems[playerid][1], 7.368598, 40.375000);
			PlayerTextDrawAlignment(playerid, InfoItems[playerid][1], 2);
			PlayerTextDrawColor(playerid, InfoItems[playerid][1], 0xFFFFFFFF);
			PlayerTextDrawUseBox(playerid, InfoItems[playerid][1], 0);
			PlayerTextDrawBoxColor(playerid, InfoItems[playerid][1], 0x80808080);
			PlayerTextDrawSetShadow(playerid, InfoItems[playerid][1], 0);
			PlayerTextDrawSetOutline(playerid, InfoItems[playerid][1], 1);
			PlayerTextDrawBackgroundColor(playerid, InfoItems[playerid][1], 0x00000000);
			PlayerTextDrawFont(playerid, InfoItems[playerid][1], 1);
			PlayerTextDrawSetProportional(playerid, InfoItems[playerid][1], 1);
			PlayerTextDrawSetSelectable(playerid, InfoItems[playerid][1], 1);

			InfoItems[playerid][0] = CreatePlayerTextDraw(playerid, 477.851715+X+idiot, 168.516678+Y+debil, "CLOSE");
			PlayerTextDrawLetterSize(playerid, InfoItems[playerid][0], 0.149033, 0.818733);
			PlayerTextDrawTextSize(playerid, InfoItems[playerid][0], 7.368598, 40.375000);
			PlayerTextDrawAlignment(playerid, InfoItems[playerid][0], 2);
			PlayerTextDrawColor(playerid, InfoItems[playerid][0], 0xBE5555FF);
			PlayerTextDrawUseBox(playerid, InfoItems[playerid][0], 0);
			PlayerTextDrawBoxColor(playerid, InfoItems[playerid][0], 0x80808080);
			PlayerTextDrawSetShadow(playerid, InfoItems[playerid][0], 0);
			PlayerTextDrawSetOutline(playerid, InfoItems[playerid][0], 1);
			PlayerTextDrawBackgroundColor(playerid, InfoItems[playerid][0], 0x00000000);
			PlayerTextDrawFont(playerid, InfoItems[playerid][0], 1);
			PlayerTextDrawSetProportional(playerid, InfoItems[playerid][0], 1);
			PlayerTextDrawSetSelectable(playerid, InfoItems[playerid][0], 1);
		}
	} else {
        InfoItems[playerid][5] = CreatePlayerTextDraw(playerid, 451.289215+X+idiot, 140.350006+Y+debil, "particle:shad_bike");
        PlayerTextDrawLetterSize(playerid, InfoItems[playerid][5], 0.480000, 1.120000);
        PlayerTextDrawTextSize(playerid, InfoItems[playerid][5], 10.625000, 39.000000);
        PlayerTextDrawAlignment(playerid, InfoItems[playerid][5], 0);
        PlayerTextDrawColor(playerid, InfoItems[playerid][5], 0x00000070);
        PlayerTextDrawUseBox(playerid, InfoItems[playerid][5], 0);
        PlayerTextDrawBoxColor(playerid, InfoItems[playerid][5], 0x80808080);
        PlayerTextDrawSetShadow(playerid, InfoItems[playerid][5], 2);
        PlayerTextDrawSetOutline(playerid, InfoItems[playerid][5], 0);
        PlayerTextDrawBackgroundColor(playerid, InfoItems[playerid][5], 0x000000FF);
        PlayerTextDrawFont(playerid, InfoItems[playerid][5], 4);
        PlayerTextDrawSetProportional(playerid, InfoItems[playerid][5], 1);
        PlayerTextDrawSetSelectable(playerid, InfoItems[playerid][5], 0);

        InfoItems[playerid][4] = CreatePlayerTextDraw(playerid, 493.789215+X+idiot, 140.350006+Y+debil, "particle:shad_bike");
        PlayerTextDrawLetterSize(playerid, InfoItems[playerid][4], 0.480000, 1.120000);
        PlayerTextDrawTextSize(playerid, InfoItems[playerid][4], 10.625000, 39.000000);
        PlayerTextDrawAlignment(playerid, InfoItems[playerid][4], 0);
        PlayerTextDrawColor(playerid, InfoItems[playerid][4], 0x00000070);
        PlayerTextDrawUseBox(playerid, InfoItems[playerid][4], 0);
        PlayerTextDrawBoxColor(playerid, InfoItems[playerid][4], 0x80808080);
        PlayerTextDrawSetShadow(playerid, InfoItems[playerid][4], 2);
        PlayerTextDrawSetOutline(playerid, InfoItems[playerid][4], 0);
        PlayerTextDrawBackgroundColor(playerid, InfoItems[playerid][4], 0x000000FF);
        PlayerTextDrawFont(playerid, InfoItems[playerid][4], 4);
        PlayerTextDrawSetProportional(playerid, InfoItems[playerid][4], 1);
        PlayerTextDrawSetSelectable(playerid, InfoItems[playerid][4], 0);

        InfoItems[playerid][3] = CreatePlayerTextDraw(playerid, 500.351715+X+idiot, 141.850006+Y+debil, "usebox");
        PlayerTextDrawLetterSize(playerid, InfoItems[playerid][3], 0.000000, 3.998150);
        PlayerTextDrawTextSize(playerid, InfoItems[playerid][3], 455.101715+X+idiot, 0.000000);
        PlayerTextDrawAlignment(playerid, InfoItems[playerid][3], 1);
        PlayerTextDrawColor(playerid, InfoItems[playerid][3], 0xE1E1E1FF);
        PlayerTextDrawUseBox(playerid, InfoItems[playerid][3], 1);
        PlayerTextDrawBoxColor(playerid, InfoItems[playerid][3], 0x000000AA);
        PlayerTextDrawSetShadow(playerid, InfoItems[playerid][3], 2);
        PlayerTextDrawSetOutline(playerid, InfoItems[playerid][3], 0);
        PlayerTextDrawBackgroundColor(playerid, InfoItems[playerid][3], 0x000000FF);
        PlayerTextDrawFont(playerid, InfoItems[playerid][3], 0);
        PlayerTextDrawSetProportional(playerid, InfoItems[playerid][3], 1);
        PlayerTextDrawSetSelectable(playerid, InfoItems[playerid][3], 0);

        InfoItems[playerid][2] = CreatePlayerTextDraw(playerid, 477.851715+X+idiot, 142.516678+Y+debil, string);
        PlayerTextDrawLetterSize(playerid, InfoItems[playerid][2], 0.159033, 0.818733);
        PlayerTextDrawTextSize(playerid, InfoItems[playerid][2], 7.368598, 40.375000);
        PlayerTextDrawAlignment(playerid, InfoItems[playerid][2], 2);
        PlayerTextDrawColor(playerid, InfoItems[playerid][2], 0xFFFFFFFF);
        PlayerTextDrawUseBox(playerid, InfoItems[playerid][2], 0);
        PlayerTextDrawBoxColor(playerid, InfoItems[playerid][2], 0x80808080);
        PlayerTextDrawSetShadow(playerid, InfoItems[playerid][2], 0);
        PlayerTextDrawSetOutline(playerid, InfoItems[playerid][2], 1);
        PlayerTextDrawBackgroundColor(playerid, InfoItems[playerid][2], 0x00000000);
        PlayerTextDrawFont(playerid, InfoItems[playerid][2], 1);
        PlayerTextDrawSetProportional(playerid, InfoItems[playerid][2], 1);
        PlayerTextDrawSetSelectable(playerid, InfoItems[playerid][2], 1);

        InfoItems[playerid][1] = CreatePlayerTextDraw(playerid, 477.851715+X+idiot, 155.516678+Y+debil, "INFO");
        PlayerTextDrawLetterSize(playerid, InfoItems[playerid][1], 0.154033, 0.818733);
        PlayerTextDrawTextSize(playerid, InfoItems[playerid][1], 7.368598, 40.375000);
        PlayerTextDrawAlignment(playerid, InfoItems[playerid][1], 2);
        PlayerTextDrawColor(playerid, InfoItems[playerid][1], 0xFFFFFFFF);
        PlayerTextDrawUseBox(playerid, InfoItems[playerid][1], 0);
        PlayerTextDrawBoxColor(playerid, InfoItems[playerid][1], 0x80808080);
        PlayerTextDrawSetShadow(playerid, InfoItems[playerid][1], 0);
        PlayerTextDrawSetOutline(playerid, InfoItems[playerid][1], 1);
        PlayerTextDrawBackgroundColor(playerid, InfoItems[playerid][1], 0x00000000);
        PlayerTextDrawFont(playerid, InfoItems[playerid][1], 1);
        PlayerTextDrawSetProportional(playerid, InfoItems[playerid][1], 1);
        PlayerTextDrawSetSelectable(playerid, InfoItems[playerid][1], 1);

        InfoItems[playerid][0] = CreatePlayerTextDraw(playerid, 477.851715+X+idiot, 168.516678+Y+debil, "CLOSE");
        PlayerTextDrawLetterSize(playerid, InfoItems[playerid][0], 0.149033, 0.818733);
        PlayerTextDrawTextSize(playerid, InfoItems[playerid][0], 7.368598, 40.375000);
        PlayerTextDrawAlignment(playerid, InfoItems[playerid][0], 2);
        PlayerTextDrawColor(playerid, InfoItems[playerid][0], 0xBE5555FF);
        PlayerTextDrawUseBox(playerid, InfoItems[playerid][0], 0);
        PlayerTextDrawBoxColor(playerid, InfoItems[playerid][0], 0x80808080);
        PlayerTextDrawSetShadow(playerid, InfoItems[playerid][0], 0);
        PlayerTextDrawSetOutline(playerid, InfoItems[playerid][0], 1);
        PlayerTextDrawBackgroundColor(playerid, InfoItems[playerid][0], 0x00000000);
        PlayerTextDrawFont(playerid, InfoItems[playerid][0], 1);
        PlayerTextDrawSetProportional(playerid, InfoItems[playerid][0], 1);
        PlayerTextDrawSetSelectable(playerid, InfoItems[playerid][0], 1);
	}
	CheckOn(playerid);
    return true;
}

stock CheckOn(playerid) {
	if (PickInvent[playerid] < 0 || PickInvent[playerid] >= MAX_INVENTORY_SLOTS) return true;

    PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
    for (new i = 1; i < MAX_ITEMS; i++) {
        if (playerData[playerid][pInventory][PickInvent[playerid]] == i) {
            PlayerTextDrawSetString(playerid, InfoItems[playerid][1], "INFO");
            PlayerTextDrawSetString(playerid, InfoItems[playerid][0], "CLOSE");
            PlayerTextDrawSetString(playerid, fstd_p[playerid][2], "DROP");
            PlayerTextDrawSetString(playerid, fstd_p[playerid][1], "INFO");
            PlayerTextDrawSetString(playerid, fstd_p[playerid][0], "CLOSE");
            
            PlayerTextDrawShow(playerid, InfoItems[playerid][1]);
            PlayerTextDrawShow(playerid, InfoItems[playerid][0]);
            PlayerTextDrawShow(playerid, fstd_p[playerid][2]);
            PlayerTextDrawShow(playerid, fstd_p[playerid][1]);
            PlayerTextDrawShow(playerid, fstd_p[playerid][0]);
            PlayerTextDrawShow(playerid, dropmenu[playerid][3]);
            PlayerTextDrawShow(playerid, dropmenu[playerid][2]);
            PlayerTextDrawShow(playerid, dropmenu[playerid][1]);
            PlayerTextDrawShow(playerid, dropmenu[playerid][0]);
        }
    }

    for (new i = 1; i < 312; i++) {
        if (playerData[playerid][pInventory][PickInvent[playerid]] == i) {
            PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][46], 0xd67373FF);
            PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], 1);
            PlayerTextDrawHide(playerid, InvTextDraws[playerid][46]);
            PlayerTextDrawShow(playerid, InvTextDraws[playerid][46]);
            timeskin[playerid] = 1;
			clickOnSkin[playerid] = 1;
        }
    }
    deletevy(playerid);
    new IDS2 = playerData[playerid][pInventory][PickInvent[playerid]];
    switch (ItemsInfo[IDS2][ItemModel]) {
        case 2102,2690,2045,19590,19631,2226,19332,19333,19334,19335,19336,19337,19338,333,337,338,339,326,19591,1276,19317,19319,1609,19318,19054,19055,19056,19057,19058,19847,2803,19878,2406,3026,371,19559,19636,2511,8492,355,3056,1212,341,19142,19515,322: {
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][34], 0xd67373FF);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][34]);
			timeaks[playerid] = 1;
		}
		case 18963,19036,19037,19038,19472,19350,19085,11704,6865,18911..18920,368: {
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][42], 0xd67373FF);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][42]);
			timeaks[playerid] = 2;

		}
		case 19090..19091,19092,18636,19487,19352,19064,19065,19200,19141,2908,19314,19094,19136,18952,19346,19137,19067..19069,19554,18953,18954,18968,18967,18969,18955,18956,18957,18959,18926,18927,18928,18929,18930,18931,18932,18933,19104..19109,18921..18925,19274,18906..18910,18970..18973,18947,18948,18949,18950,18951,19521,19100,19099,19066,19528,19514: {
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][44], 0xd67373FF);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][44]);
			timeaks[playerid] = 3;
		}
		case 19469,19421..19424,19079,11712,19347,1254,16776,3105: {
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][38], 0xd67373FF);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][38]);
			timeaks[playerid] = 4;
		}
		case 19921,11745,19624: {
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][30], 0xd67373FF);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][30]);
			timeaks[playerid] = 5;
		}
		case 19904,18637: {
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][40], 0xd67373FF);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][40]);
			timeaks[playerid] = 6;
		}
		case 19039..19053: {
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][32], 0xd67373FF);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][32]);
			timeaks[playerid] = 7;
		}
		case 19011..19019,19024,19027,19028,19029,19022,19035,19031,19032,19033: {
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][36], 0xd67373FF);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][36]);
			timeaks[playerid] = 8;
		}
    }
    new IDS = playerData[playerid][pInventory][PickInvent[playerid]];
    if (playerData[playerid][pInventoryKolvo][PickInvent[playerid]] >= 2) {
        if (ItemsInfo[IDS][itemused] == false) {
            PlayerTextDrawSetString(playerid, fstd_p[playerid][2], "SPLIT");
            PlayerTextDrawShow(playerid, fstd_p[playerid][2]);
        }
    }
    if (playerData[playerid][pInventoryKolvo][PickInvent[playerid]] >= 2) {
        PlayerTextDrawShow(playerid, fstd_p[playerid][0]),
        PlayerTextDrawShow(playerid, fstd_p[playerid][2]),
        PlayerTextDrawShow(playerid, fstd_p[playerid][3]),
        PlayerTextDrawShow(playerid, fstd_p[playerid][4]),
        PlayerTextDrawShow(playerid, fstd_p[playerid][5]),
        PlayerTextDrawShow(playerid, fstd_p[playerid][6]);
    } else {
        PlayerTextDrawShow(playerid, InfoItems[playerid][0]),
        PlayerTextDrawShow(playerid, InfoItems[playerid][1]),
        PlayerTextDrawShow(playerid, InfoItems[playerid][2]),
        PlayerTextDrawShow(playerid, InfoItems[playerid][3]);
        PlayerTextDrawShow(playerid, InfoItems[playerid][4]),
        PlayerTextDrawShow(playerid, InfoItems[playerid][5]); // ������������� ����.
    }
    return true;
}

stock bool:CheckSuka(playerid) {
    new string[56];
	if (playerData[playerid][pSkin] != GetPlayerSkin(playerid)) {

		if (GetPVarInt(playerid, "usedGangSkin") == 1) {
			SetPlayerSkinEx(playerid, playerData[playerid][pSkin]);

			new str2[24];
			format(str2, sizeof(str2), "ID:%d", GetPlayerSkin(playerid)),
			PlayerTextDrawSetString(playerid, InvTextDraws[playerid][45], str2);
			PlayerTextDrawHide(playerid, InvTextDraws[playerid][45]);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][45]);
			PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][47], GetPlayerSkin(playerid));
			PlayerTextDrawHide(playerid, InvTextDraws[playerid][47]);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][47]);

			PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
			RefreshInv2(playerid, PickInvent[playerid]);
			SetPVarInt(playerid, "usedGangSkin", 0);
			return true;
		}

		RefreshInv2(playerid, PickInvent[playerid]);
		va_SendClientMessage(playerid, COLOR_RED, "[��ͼԴ��Ҵ] {FFFFFF}�����ʹ����ͼ������ҹ���͡");
		return true;
	}

	if (playerData[playerid][pSkin] == DEFAULT_PLAYER_SKIN_MALE || playerData[playerid][pSkin] == DEFAULT_PLAYER_SKIN_FEMALE) {
		new roulette2 = PickInvent[playerid];
		playerData[playerid][pSkin] = playerData[playerid][pInventory][PickInvent[playerid]];
		SetPlayerSkinEx(playerid, playerData[playerid][pInventory][PickInvent[playerid]]);
		format(string, sizeof(string), "ID:%d", GetPlayerSkin(playerid)),
		PlayerTextDrawSetString(playerid, InvTextDraws[playerid][45], string);
		PlayerTextDrawHide(playerid, InvTextDraws[playerid][45]);
		PlayerTextDrawShow(playerid, InvTextDraws[playerid][45]);
		PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][47], GetPlayerSkin(playerid));
		PlayerTextDrawHide(playerid, InvTextDraws[playerid][47]);
		PlayerTextDrawShow(playerid, InvTextDraws[playerid][47]);
		RefreshInv(playerid, PickInvent[playerid]);
		playerData[playerid][pInventory][roulette2] = 0;
		playerData[playerid][pInventoryKolvo][roulette2] = 0;
		SaveInventory(playerid);
		timeskin[playerid] = 0;
		clickOnSkin[playerid] = 0;
		UpdatePlayerDataEx(playerid, "Skin", playerData[playerid][pSkin]);
		return true;
	} else {
		new roulette = GetPlayerSkin(playerid);
		new roulette2 = PickInvent[playerid];
		playerData[playerid][pSkin] = playerData[playerid][pInventory][PickInvent[playerid]];
		SetPlayerSkinEx(playerid, playerData[playerid][pInventory][PickInvent[playerid]]);
		format(string, sizeof(string), "ID:%d", GetPlayerSkin(playerid)),
		PlayerTextDrawSetString(playerid, InvTextDraws[playerid][45], string);
		PlayerTextDrawHide(playerid, InvTextDraws[playerid][45]);
		PlayerTextDrawShow(playerid, InvTextDraws[playerid][45]);
		PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][47], GetPlayerSkin(playerid));
		PlayerTextDrawHide(playerid, InvTextDraws[playerid][47]);
		PlayerTextDrawShow(playerid, InvTextDraws[playerid][47]);
		RefreshInv(playerid, PickInvent[playerid]);
		playerData[playerid][pInventory][roulette2] = roulette;
		playerData[playerid][pInventoryKolvo][roulette2] = 1;
		PlayerTextDrawSetPreviewModel(playerid, Govnishe[playerid][roulette2], roulette);
		PlayerTextDrawSetPreviewRot(playerid, Govnishe[playerid][roulette2], 0.000000, 0.000000, 0.000000, 1.000000);
		format(string, sizeof(string), "ID:%d", roulette),
		PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][roulette2], string);
		PlayerTextDrawColor(playerid, GovnisheKletki[playerid][roulette2], 0xFFFFFFFF);
		PlayerTextDrawHide(playerid, Govnishe[playerid][roulette2]);
		PlayerTextDrawShow(playerid, Govnishe[playerid][roulette2]);
		PlayerTextDrawHide(playerid, GovnisheKletki[playerid][roulette2]);
		PlayerTextDrawShow(playerid, GovnisheKletki[playerid][roulette2]);
		timeskin[playerid] = 0;
		clickOnSkin[playerid] = 0;
		UpdatePlayerDataEx(playerid, "Skin", playerData[playerid][pSkin]);
		return true;
	}
}

stock RefreshInv(playerid, slot) {
	if (playerData[playerid][pInventoryKolvo][slot] != 1) {
		playerData[playerid][pInventoryKolvo][slot] -= 1;
	} else {
		playerData[playerid][pInventory][slot] = 0;
		playerData[playerid][pInventoryKolvo][slot] = 0;
	}
	for (new i = 0; i < 6; i++) {
		DestroyPlayerTD(playerid, InfoItems[playerid][i]);
	}
	for (new i = 0; i < 7; i++) {
		DestroyPlayerTD(playerid, fstd_p[playerid][i]);
	}
	for (new i = 0; i < 8; i++) {
		DestroyPlayerTD(playerid, dropmenu[playerid][i]);
	}
	if (playerData[playerid][pInventoryKolvo][slot] < 1) {
		playerData[playerid][pInventoryKolvo][slot] = 0;
		playerData[playerid][pInventory][slot] = 0;
	}
	if (PickInvent[playerid] >= 0 && PickInvent[playerid] < MAX_INVENTORY_SLOTS) {
		for (new i = 1; i < 312; i++) {
			if (playerData[playerid][pInventory][PickInvent[playerid]] == i) {
				PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][46], 0x333333FF);
				timeskin[playerid] = 0;
				clickOnSkin[playerid] = 0;
				if (playerData[playerid][pSkin] == DEFAULT_PLAYER_SKIN_MALE || playerData[playerid][pSkin] == DEFAULT_PLAYER_SKIN_FEMALE) {
					PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], 0);
				}
				PlayerTextDrawHide(playerid, InvTextDraws[playerid][46]);
				PlayerTextDrawShow(playerid, InvTextDraws[playerid][46]);
			}
		}
	}
	InvSlotUpdate(playerid, slot, playerData[playerid][pInventory][slot]);
	PickInvent[playerid] = INVALID_SLOT;
	return true;
}

stock Pizda(playerid) {
	new string[10];
	new skin = GetPlayerSkin(playerid);
    format(string,sizeof(string),"ID:%d",skin),
    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][45], string);
    if (GetPlayerSkin(playerid) == DEFAULT_PLAYER_SKIN_MALE || GetPlayerSkin(playerid) == DEFAULT_PLAYER_SKIN_FEMALE) {
		PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], 0);
		PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][46], 1649);
		PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][46], 0.000000, 0.000000, 90.000000, 2.000000);
		PlayerTextDrawSetString(playerid, InvTextDraws[playerid][45], "");
		PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][47], (playerData[playerid][pGender] == 1) ? DEFAULT_PLAYER_SKIN_MALE : DEFAULT_PLAYER_SKIN_FEMALE);
		PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][47], 0.000000, 0.000000, 0.000000, 1.000000);
		PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][46], 0x333333FF);
	} else {
		PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], 1);
		PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][46], 2386);
		PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][46], 346.000000, 0.000000, 129.000000, 0.900000);
		PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][47], GetPlayerSkin(playerid));
		PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][47], 0.000000, 0.000000, 0.000000, 1.000000);
		PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][46], 0x333333FF);
	}

    PlayerTextDrawShow(playerid,InvTextDraws[playerid][45]);
    PlayerTextDrawShow(playerid,InvTextDraws[playerid][46]);
    PlayerTextDrawShow(playerid,InvTextDraws[playerid][47]);
    return true;
}

stock CheckItem(playerid) {
	if (IsPlayerAttachedObjectSlotUsed(playerid, 2)) RemovePlayerAttachedObject(playerid, 2);
	if (IsPlayerAttachedObjectSlotUsed(playerid, 4)) RemovePlayerAttachedObject(playerid, 4);
	if (IsPlayerAttachedObjectSlotUsed(playerid, 3)) RemovePlayerAttachedObject(playerid, 3);
	if (IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
	if (IsPlayerAttachedObjectSlotUsed(playerid, 0)) RemovePlayerAttachedObject(playerid, 0);
	if (IsPlayerAttachedObjectSlotUsed(playerid, 5)) RemovePlayerAttachedObject(playerid, 5);
	return 1;
}

stock GiveItem(playerid,item) {
	new skin = GetPlayerSkin(playerid);
	switch (item) {
		case 19039..19053: SetAttachToSkin(playerid, 15, skin, item);
		case 19421..19424://��������
			{
				SetAttachToSkin(playerid, 14, skin, item);
			}
		case 18911..18920: //�������
			{
				SetAttachToSkin(playerid, 13, skin, item);
			}
		case 19011..19019,19024,19027,19028,19029,19022,19035,19031,19032,19033://����
			{
				SetAttachToSkin(playerid, 12, skin, item);
			}
		case 19069,19068,19067://�����
			{
				SetAttachToSkin(playerid, 1, skin, item);
			}
		case 19554: //����� ������
			{
				SetAttachToSkin(playerid, 3, skin, item);
			}
		case 18953,18954: //Ҹ���� �����
			{
				SetAttachToSkin(playerid, 2, skin, item);
			}
		case 18968,18967,18969://�������
			{
				SetAttachToSkin(playerid, 4, skin, item);
			}
		case 18955,18956,18957,18959://����� �� ���
			{
				SetAttachToSkin(playerid, 5, skin, item);
			}
		case 18926,18927,18928,18929,18930,18931,18932,18933: //����� ������
			{
				SetAttachToSkin(playerid, 6, skin, item);
			}
		case 19104,19105,19106,19107,19108,19109://�����
			{
				SetAttachToSkin(playerid, 9, skin, item);
			}
		case 19519://������ 1
			{
				SetAttachToSkin(playerid, 10, skin, item);
			}
		case 19274://������ 2
			{
				SetAttachToSkin(playerid, 11, skin, item);
			}
		case 18925,18922,18923,18924,18921: //������
			{
				SetAttachToSkin(playerid, 8, skin, item);
			}
		case 18947,18948,18949,18950,18951: //�����
			{
				SetAttachToSkin(playerid, 7, skin, item);
			}
			//�������
		case 3026:
			{
				SetAttachToSkin(playerid, 16, skin, item);
			}
		case 371:
			{
				SetAttachToSkin(playerid, 17, skin, item);
			}
		case 19559:
			{
				SetAttachToSkin(playerid, 18, skin, item);
			}
			//���
			//����� 1
		case 18970, 18973, 18972, 18971:
			{
				SetAttachToSkin(playerid, 19, skin, item);
			}
			//����� 2
		case 19487, 19352:
			{
				SetAttachToSkin(playerid, 20, skin, item);
			}
			//������� �� ������
		case 18910, 18909, 18908, 18907, 18906:
			{
				SetAttachToSkin(playerid, 21, skin, item);
			}
			//���
		case 19351:
			{
				SetAttachToSkin(playerid, 22, skin, item);
			}
			//���
		case 19350:
			{
				SetAttachToSkin(playerid, 24, skin, item);
			}
			//������
		case 19319, 19318, 19317:
			{
				SetAttachToSkin(playerid, 23, skin, item);
			}
			//�����
		case 19878:
			{
				SetAttachToSkin(playerid, 32, skin, item);
			}
		case 19064..19066://����� ����������
			{
				SetAttachToSkin(playerid, 25, skin, item);
			}
		case 19085://�������
			{
				SetAttachToSkin(playerid, 26, skin, item);
			}
		case 19054..19058://���������� ������
			{
				SetAttachToSkin(playerid, 27, skin, item);
			}
		case 881://����
			{
				SetAttachToSkin(playerid, 28, skin, item);
			}
		case 19624: //�������
			{
				SetAttachToSkin(playerid, 29, skin, item);
			}
			//���� �� ������
		case 2102: //�������
			{
				SetAttachToSkin(playerid, 33, skin, item);
			}
		case 2690://������������
			{
				SetAttachToSkin(playerid, 34, skin, item);
			}
		case 2045://���� � ��������
			{
				SetAttachToSkin(playerid, 35, skin, item);
			}
		case 19590://���
			{
				SetAttachToSkin(playerid, 36, skin, item);
			}
		case 19631://�����
			{
				SetAttachToSkin(playerid, 37, skin, item);
			}
		case 18963://����� CJ
			{
				SetAttachToSkin(playerid, 38, skin, item);
			}
		case 19921://������� �������
			{
				SetAttachToSkin(playerid, 39, skin, item);
			}
		case 18645://�������� ����
			{
				SetAttachToSkin(playerid, 40, skin, item);
			}
		case 19036://����� �����
			{
				SetAttachToSkin(playerid, 41, skin, item);
			}
		case 19037://������� �����
			{
				SetAttachToSkin(playerid, 42, skin, item);
			}
		case 19038://������� �����
			{
				SetAttachToSkin(playerid, 43, skin, item);
			}
		case 18938://����� �����
			{
				SetAttachToSkin(playerid, 44, skin, item);
			}
		case 18937://������� �����
			{
				SetAttachToSkin(playerid, 45, skin, item);
			}
		case 19118://������� �����
			{
				SetAttachToSkin(playerid, 46, skin, item);
			}
		case 19904://�����
			{
				SetAttachToSkin(playerid, 47, skin, item);
			}
		case 19469://������� �� ���
			{
				SetAttachToSkin(playerid, 48, skin, item);
			}
		case 333://������
			{
				SetAttachToSkin(playerid, 49, skin, item);
			}
		case 336://����
			{
				SetAttachToSkin(playerid, 50, skin, item);
			}
		case 19626://������
			{
				SetAttachToSkin(playerid, 51, skin, item);
			}
		case 338://���
			{
				SetAttachToSkin(playerid, 52, skin, item);
			}
		case 339://������
			{
				SetAttachToSkin(playerid, 53, skin, item);
			}
		case 326://������
			{
				SetAttachToSkin(playerid, 54, skin, item);
			}
		case 18637://���
			{
				SetAttachToSkin(playerid, 55, skin, item);
			}
		case 18636://����� POLICE
			{
				SetAttachToSkin(playerid, 56, skin, item);
			}
		case 19472://����������
			{
				SetAttachToSkin(playerid, 57, skin, item);
			}
		case 2226://�������
			{
				SetAttachToSkin(playerid, 58, skin, item);
			}
		case 1276://������� �����
			{
				SetAttachToSkin(playerid, 59, skin, item);
			}
		case 19591:
			{
				SetAttachToSkin(playerid, 60, skin, item);
			}
			case 11704://����� ( ������ )
			{
				SetAttachToSkin(playerid, 61, skin, item);
			}
		case 19137://����� ( ������ )
			{
				SetAttachToSkin(playerid, 62, skin, item);
			}
		case 19346://������
			{
				SetAttachToSkin(playerid, 63, skin, item);
			}
		case 6865://����� ( �������� )
			{
				SetAttachToSkin(playerid, 64, skin, item);
			}
		case 18952://���� �������
			{
				SetAttachToSkin(playerid, 65, skin, item);
			}
		case 19847://��� ����19136
			{
				SetAttachToSkin(playerid, 66, skin, item);
			}
		case 19136://��� ����
			{
				SetAttachToSkin(playerid, 67, skin, item);
			}
		case 11745://����� ��� ����� by despaze in venni
			{
				SetAttachToSkin(playerid, 68, skin, item);
			}
		case 19094://������ �� ������ by despaze in venni
			{
				SetAttachToSkin(playerid, 69, skin, item);
			}
		case 19141:
			{
				SetAttachToSkin(playerid, 70, skin, item); // ���� ����
			}
		case 19314:
			{
				SetAttachToSkin(playerid, 71, skin, item); // ���� �� ������
			}
		case 2908:
			{
				SetAttachToSkin(playerid, 72, skin, item); // ����� �����
			}
		case 2803:
			{
				SetAttachToSkin(playerid, 73, skin, item); // ����� �����
			}
		case 2406:
			{
				SetAttachToSkin(playerid, 74, skin, item); // ����� �����
			}
		case 368:
			{
				SetAttachToSkin(playerid, 75, skin, item); // ����� �����
			}
		case 19636:
			{
				SetAttachToSkin(playerid, 76, skin, item); // ����� �����
			}
		case 19079:
			{
				SetAttachToSkin(playerid, 77, skin, item); // ����� �����
			}
		case 8492:
			{
				SetAttachToSkin(playerid, 78, skin, item); // ����� �����
			}
		case 2511:
			{
				SetAttachToSkin(playerid, 79, skin, item); // ����� �����
			}
		case 19521:
			{
				SetAttachToSkin(playerid, 80, skin, item); // ����� �����
			}
		case 11712:
			{
				SetAttachToSkin(playerid, 81, skin, item); // ����� �����
			}
		case 356:
			{
				SetAttachToSkin(playerid, 82, skin, item); // ����� �����
			}
		case 19332: // ���
			{
				SetAttachToSkin(playerid, 84, skin, item);
			}
		case 3105:
			{
				SetAttachToSkin(playerid, 85, skin, item);
			}
		case 19333: // ���
			{
				SetAttachToSkin(playerid, 86, skin, item);
			}
		case 19334: // ���
			{
				SetAttachToSkin(playerid, 87, skin, item);
			}
		case 19335: // ���
			{
				SetAttachToSkin(playerid, 88, skin, item);
			}
		case 19336: // ���
			{
				SetAttachToSkin(playerid, 89, skin, item);
			}
		case 19337: // ���
			{
				SetAttachToSkin(playerid, 90, skin, item);
			}
		case 19338: // ���
			{
				SetAttachToSkin(playerid, 91, skin, item);
			}
		case 1609:
			{
				SetAttachToSkin(playerid, 92, skin, item);
			}
		case 16776:
			{
				SetAttachToSkin(playerid, 93, skin, item); // 83
			}
		case 1212:
			{
				SetAttachToSkin(playerid, 94, skin, item); // 92
			}
		case 1254:
			{
				SetAttachToSkin(playerid, 95, skin, item); // 97
			}
		case 341:
			{
				SetAttachToSkin(playerid, 96, skin, item); // 94
			}
		case 3056:
			{
				SetAttachToSkin(playerid, 97, skin, item); // 89
			}
	}
	return true;
}

stock bool:SwitchInventoryPage(playerid, page) {
	switch (page) {
		case 0: {
			new string[50];
			new str[28];
			if (playerData[playerid][pSecondpage] == 0) return true;
			for (new j = 0; j < 36; j++) {
				new ID = playerData[playerid][pInventory][j];
				PlayerTextDrawSetPreviewModel(playerid, Govnishe[playerid][j], ItemsInfo[ID][ItemModel]);
				PlayerTextDrawSetPreviewRot(playerid, Govnishe[playerid][j], ItemsInfo[ID][POSTDx], ItemsInfo[ID][POSTDy], ItemsInfo[ID][POSTDz], ItemsInfo[ID][POSTDc]);
				PlayerTextDrawBackgroundColor(playerid, Govnishe[playerid][j], ItemsInfo[ID][ItemColor]);
				format(string,sizeof(string), "%d",playerData[playerid][pInventoryKolvo][j]),
				PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
			}
			for (new j = 0; j < 36; j++) {
				if (playerData[playerid][pInventoryKolvo][j] == 0) {
					/// fixed
					format(string,sizeof(string), ""),
					PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
				}
				if (playerData[playerid][pInventoryKolvo][j] == 1) {
					/// fixed
					format(string,sizeof(string), ""),
					PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
				}
				if (playerData[playerid][pInventory][j] == 313) {
					if (playerData[playerid][pChestTime] < 60) {
						format(string,sizeof(string),"%d SEC", playerData[playerid][pChestTime]);
						PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
					}
					if (playerData[playerid][pChestTime] == 0) {
						format(string,sizeof(string),""),
						PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
						playerData[playerid][pChestTime] = 0;
					}
					if (playerData[playerid][pChestTime] > 60) {
						format(string,sizeof(string),"%d MIN", playerData[playerid][pChestTime]/60);
						PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
					}
				}
				if (playerData[playerid][pInventory][j] == 590) {
					format(string,sizeof(string),"%d DAY", playerData[playerid][pCarLic]);
					PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
				}
				if (playerData[playerid][pInventory][j] == 591) {
					format(string,sizeof(string),"%d DAY", playerData[playerid][pBikeLic]);
					PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
				}
				if (playerData[playerid][pInventory][j] == 592) {
					format(string,sizeof(string),"%d DAY", playerData[playerid][pBoatLic]);
					PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
				}
				if (playerData[playerid][pInventory][j] == 593) {
					format(string,sizeof(string),"%d DAY", playerData[playerid][pFlyLic]);
					PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
				}
				if (playerData[playerid][pInventory][j] == 594) {
					format(string,sizeof(string),"%d DAY", playerData[playerid][pGunLic]);
					PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
				}
				for (new i = 1; i < 312; i++) {
				if (playerData[playerid][pInventory][j] == i) {
						format(str, sizeof(str), "ID:%d", i),
						PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], str);
						PlayerTextDrawColor(playerid, GovnisheKletki[playerid][j], 0xFFFFFFFF);
					}
				}
			}
			for (new i = 0; i < 36; i++) {
				PlayerTextDrawShow(playerid, Govnishe[playerid][i]);
			}
			for (new j = 0; j < 36; j++) {
				PlayerTextDrawShow(playerid, GovnisheKletki[playerid][j]);
			}
			for (new j = 36; j < 72; j++) {
				PlayerTextDrawHide(playerid, Govnishe[playerid][j]);
			}
			for (new j = 36; j < 72; j++) {
				PlayerTextDrawHide(playerid, GovnisheKletki[playerid][j]);
			}
			for (new j = 0; j < 6; j++) {
				PlayerTextDrawHide(playerid, InfoItems[playerid][j]);
			}
			for (new i = 0; i < 7; i++) {
				PlayerTextDrawHide(playerid, fstd_p[playerid][i]);
			}
			for (new i = 0; i < 8; i++) {
				PlayerTextDrawHide(playerid, dropmenu[playerid][i]);
			}
			for (new i = 0; i < 8; i++) {
				PlayerTextDrawHide(playerid, dropmenu[playerid][i]);
			}
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][8], 0x333333FF);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][9], playerData[playerid][pColorInv]);
			PlayerTextDrawHide(playerid, InvTextDraws[playerid][9]);
			PlayerTextDrawHide(playerid, InvTextDraws[playerid][8]);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][9]);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][8]);
			playerData[playerid][pSecondpage] = 0;
			PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
			return true;
		}
		case 1: {
			new str[28];
			new string[50];
			if (playerData[playerid][pSecondpage] == 1) return true;
			for (new j = 36; j < 72; j++) {
				new ID = playerData[playerid][pInventory][j];
				PlayerTextDrawSetPreviewModel(playerid, Govnishe[playerid][j], ItemsInfo[ID][ItemModel]);
				PlayerTextDrawSetPreviewRot(playerid, Govnishe[playerid][j], ItemsInfo[ID][POSTDx], ItemsInfo[ID][POSTDy], ItemsInfo[ID][POSTDz], ItemsInfo[ID][POSTDc]);
				PlayerTextDrawBackgroundColor(playerid, Govnishe[playerid][j], ItemsInfo[ID][ItemColor]);
				format(string,sizeof(string), "%d",playerData[playerid][pInventoryKolvo][j]),
				PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
			}
			for (new j = 36; j < 72; j++) {
				if (playerData[playerid][pInventoryKolvo][j] == 0) {
					/// fixed
					format(string,sizeof(string), ""),
					PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
				}
				if (playerData[playerid][pInventoryKolvo][j] == 1) {
					/// fixed
					format(string,sizeof(string), ""),
					PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
				}
				if (playerData[playerid][pInventory][j] == 313) {
					if (playerData[playerid][pChestTime] < 60) {
						format(string,sizeof(string),"%d SEC", playerData[playerid][pChestTime]);
						PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
					}
					if (playerData[playerid][pChestTime] == 0) {
						format(string,sizeof(string),""),
						PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
						playerData[playerid][pChestTime] = 0;
					}
					if (playerData[playerid][pChestTime] > 60) {
						format(string,sizeof(string),"%d MIN", playerData[playerid][pChestTime]/60);
						PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
					}
				}
				if (playerData[playerid][pInventory][j] == 590) {
					format(string,sizeof(string),"%d DAY", playerData[playerid][pCarLic]);
					PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
				}
				if (playerData[playerid][pInventory][j] == 591) {
					format(string,sizeof(string),"%d DAY", playerData[playerid][pBikeLic]);
					PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
				}
				if (playerData[playerid][pInventory][j] == 592) {
					format(string,sizeof(string),"%d DAY", playerData[playerid][pBoatLic]);
					PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
				}
				if (playerData[playerid][pInventory][j] == 593) {
					format(string,sizeof(string),"%d DAY", playerData[playerid][pFlyLic]);
					PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
				}
				if (playerData[playerid][pInventory][j] == 594) {
					format(string,sizeof(string),"%d DAY", playerData[playerid][pGunLic]);
					PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
				}
				for (new i = 1; i < 312; i++) {
				if (playerData[playerid][pInventory][j] == i) {
						format(str, sizeof(str), "ID:%d", i),
						PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], str);
						PlayerTextDrawColor(playerid, GovnisheKletki[playerid][j], 0xFFFFFFFF);
				}
				}
			}
			for (new i = 0; i < 36; i++) {
				PlayerTextDrawHide(playerid, Govnishe[playerid][i]);
			}
			for (new i = 0; i < 36; i++) {
				PlayerTextDrawHide(playerid, GovnisheKletki[playerid][i]);
			}
			for (new j = 36; j < 72; j++) {
				PlayerTextDrawShow(playerid, Govnishe[playerid][j]);
			}
			for (new j = 36; j < 72; j++) {
				PlayerTextDrawShow(playerid, GovnisheKletki[playerid][j]);
			}
			for (new j = 0; j < 6; j++) {
				PlayerTextDrawHide(playerid, InfoItems[playerid][j]);
			}
			for (new i = 0; i < 7; i++) {
				PlayerTextDrawHide(playerid, fstd_p[playerid][i]);
			}
			for (new i = 0; i < 8; i++) {
				PlayerTextDrawHide(playerid, dropmenu[playerid][i]);
			}
			PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
			playerData[playerid][pSecondpage] = 1;
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][8], playerData[playerid][pColorInv]);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][9], 0x333333FF);
			PlayerTextDrawHide(playerid, InvTextDraws[playerid][9]);
			PlayerTextDrawHide(playerid, InvTextDraws[playerid][8]);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][9]);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][8]);
			return true;
		}
	}
	return false;
}

stock InvSlotUpdate(playerid, td, jdk) {
    new string[28];
    new str[7];

    PlayerTextDrawSetPreviewModel(playerid, Govnishe[playerid][td], ItemsInfo[jdk][ItemModel]);
    PlayerTextDrawSetPreviewRot(playerid, Govnishe[playerid][td], ItemsInfo[jdk][POSTDx], ItemsInfo[jdk][POSTDy], ItemsInfo[jdk][POSTDz], ItemsInfo[jdk][POSTDc]);
    PlayerTextDrawBackgroundColor(playerid, Govnishe[playerid][td], ItemsInfo[jdk][ItemColor]);
    PlayerTextDrawSetSelectable(playerid, Govnishe[playerid][td], 1);
    format(string,sizeof(string), "%d", playerData[playerid][pInventoryKolvo][td]),
    PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
    PlayerTextDrawColor(playerid, GovnisheKletki[playerid][td], 0xAAAAAAFF);

    if (playerData[playerid][pInventoryKolvo][td] == 0 || playerData[playerid][pInventoryKolvo][td] == 1) {
		/// fixed
        format(string,sizeof(string), ""),
        PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
    }
    if (playerData[playerid][pInventory][td] == 313) {
        if (playerData[playerid][pChestTime] < 60) {
            format(string,sizeof(string),"%d SEC", playerData[playerid][pChestTime]);
            PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
        }
        if (playerData[playerid][pChestTime] == 0) {
            format(string,sizeof(string),""),
            PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
            playerData[playerid][pChestTime] = 0;
        }
        if (playerData[playerid][pChestTime] > 60) {
            format(string,sizeof(string),"%d MIN", playerData[playerid][pChestTime]/60);
            PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
        }
    }
    if (playerData[playerid][pInventory][td] == 590) {
        format(string,sizeof(string),"%d DAY", playerData[playerid][pCarLic]);
        PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
    }
    if (playerData[playerid][pInventory][td] == 591) {
        format(string,sizeof(string),"%d DAY", playerData[playerid][pBikeLic]);
        PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
    }
    if (playerData[playerid][pInventory][td] == 592) {
        format(string,sizeof(string),"%d DAY", playerData[playerid][pBoatLic]);
        PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
    }
    if (playerData[playerid][pInventory][td] == 593) {
        format(string,sizeof(string),"%d DAY", playerData[playerid][pFlyLic]);
        PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
    }
    if (playerData[playerid][pInventory][td] == 594) {
        format(string,sizeof(string),"%d DAY", playerData[playerid][pGunLic]);
        PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
    }
    for (new j = 1; j < 312; j++) {
        if (playerData[playerid][pInventory][td] == j) {
            format(str, sizeof(str), "ID:%d", j),
            PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], str);
            PlayerTextDrawColor(playerid, GovnisheKletki[playerid][td], 0xFFFFFFFF);
            PlayerTextDrawShow(playerid, GovnisheKletki[playerid][td]);
        }
    }
    PlayerTextDrawHide(playerid,Govnishe[playerid][td]);
    PlayerTextDrawShow(playerid,Govnishe[playerid][td]);
    PlayerTextDrawShow(playerid,GovnisheKletki[playerid][td]);
    if (playerData[playerid][pSecondpage] == 1) {
        for (new i = 0; i < 36; i++) {
            PlayerTextDrawHide(playerid, GovnisheKletki[playerid][i]);
        }
        for (new i = 0; i < 36; i++) {
            PlayerTextDrawHide(playerid, Govnishe[playerid][i]);
        }
    }
    if (playerData[playerid][pSecondpage] == 0) {
        for (new i = 36; i < 72; i++) {
            PlayerTextDrawHide(playerid, GovnisheKletki[playerid][i]);
        }
        for (new i = 36; i < 72; i++) {
            PlayerTextDrawHide(playerid, Govnishe[playerid][i]);
        }
    }
    if (playerData[playerid][pSecondpage] == 0) {
        for (new i = 36; i < 72; i++) {
            PlayerTextDrawHide(playerid, GovnisheKletki[playerid][i]);
        }
    }
    if (playerData[playerid][pSecondpage] == 1) {
        for (new i = 0; i < 36; i++) {
            PlayerTextDrawHide(playerid, GovnisheKletki[playerid][i]);
        }
    }
    for (new i = 1; i < 312; i++) {
        if (playerData[playerid][pInventory][td] == i) {
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][46], 0x333333FF);
			timeskin[playerid] = 0;
			clickOnSkin[playerid] = 0;
			if (GetPlayerSkin(playerid) == DEFAULT_PLAYER_SKIN_MALE || GetPlayerSkin(playerid) == DEFAULT_PLAYER_SKIN_FEMALE) {
				PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], 0);
			} else PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], 1);
			PlayerTextDrawHide(playerid, InvTextDraws[playerid][46]);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][46]);
        }
    }
    return true;
}

stock deletevy(playerid) {
    if (timeaks[playerid] == 1) {
	    new IDS2 = AksSlot[playerid][5];
	    PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][34], ItemsInfo[IDS2][ItemAksColor]);
		PlayerTextDrawShow(playerid, InvTextDraws[playerid][34]);
		CheckInvs(playerid, 5);
	}
	if (timeaks[playerid] == 2) {
	    new IDS2 = AksSlot[playerid][1];
	    PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][42], ItemsInfo[IDS2][ItemAksColor]);
		PlayerTextDrawShow(playerid, InvTextDraws[playerid][42]);
		CheckInvs(playerid, 1);
	}
	if (timeaks[playerid] == 3) {
	    new IDS2 = AksSlot[playerid][2];
	    PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][44], ItemsInfo[IDS2][ItemAksColor]);
		PlayerTextDrawShow(playerid, InvTextDraws[playerid][44]);
		CheckInvs(playerid, 2);
	}
	if (timeaks[playerid] == 4) {
	    new IDS2 = AksSlot[playerid][0];
	    PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][38], ItemsInfo[IDS2][ItemAksColor]);
		PlayerTextDrawShow(playerid, InvTextDraws[playerid][38]);
		CheckInvs(playerid, 0);
	}
	if (timeaks[playerid] == 5) {
	    new IDS2 = AksSlot[playerid][4];
	    PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][30], ItemsInfo[IDS2][ItemAksColor]);
		PlayerTextDrawShow(playerid, InvTextDraws[playerid][30]);
		CheckInvs(playerid, 4);
	}
	if (timeaks[playerid] == 6) {
	    new IDS2 = AksSlot[playerid][3];
	    PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][40], ItemsInfo[IDS2][ItemAksColor]);
		PlayerTextDrawShow(playerid, InvTextDraws[playerid][40]);
		CheckInvs(playerid, 3);
	}
	if (timeaks[playerid] == 7) {
	    new IDS2 = AksSlot[playerid][6];
	    PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][32], ItemsInfo[IDS2][ItemAksColor]);
		PlayerTextDrawShow(playerid, InvTextDraws[playerid][32]);
		CheckInvs(playerid, 6);
	}
	if (timeaks[playerid] == 8) {
	    new IDS2 = AksSlot[playerid][7];
	    PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][36], ItemsInfo[IDS2][ItemAksColor]);
		PlayerTextDrawShow(playerid, InvTextDraws[playerid][36]);
		CheckInvs(playerid, 7);
	}
	timeaks[playerid] = 0;
	return true;
}

stock bool:updateslot6(playerid) {
    for (new i = 0; i < 30; i++) {
        if (PickInvent[playerid] == i) {
            PlayerTextDrawSetSelectable(playerid, Govnishe[playerid][i+6], 1);
            PlayerTextDrawHide(playerid, Govnishe[playerid][i+6]);
            PlayerTextDrawShow(playerid, Govnishe[playerid][i+6]);
		}
	}
	for (new i = 36; i < 66; i++) {
        if (PickInvent[playerid] == i) {
            PlayerTextDrawSetSelectable(playerid, Govnishe[playerid][i+6], 1);
            PlayerTextDrawHide(playerid, Govnishe[playerid][i+6]);
            PlayerTextDrawShow(playerid, Govnishe[playerid][i+6]);
		}
	}
	return true;
}

stock RefreshInv2(playerid, slot) {
    for (new i = 0; i < 6; i++) {
	    DestroyPlayerTD(playerid, InfoItems[playerid][i]);
	}
	for (new i = 0; i < 7; i++) {
        DestroyPlayerTD(playerid, fstd_p[playerid][i]);
	}
	for (new i = 0; i < 8; i++) {
	    DestroyPlayerTD(playerid, dropmenu[playerid][i]);
	}

    if (slot >= 0 && slot < MAX_INVENTORY_SLOTS)
        InvSlotUpdate(playerid, slot, playerData[playerid][pInventory][slot]);
		
    PickInvent[playerid] = INVALID_SLOT;
    return true;
}

stock closeuse(playerid) {
	for (new i = 0; i < 2; i++) {
	    DestroyPlayerTD(playerid, kletka[playerid][i]);
	}
    for (new i = 0; i < 63; i++) {
        DestroyPlayerTD(playerid,InvTextDraws[playerid][i]);
    }
    for (new i = 0; i < 72; i++) {
        DestroyPlayerTD(playerid,Govnishe[playerid][i]);
    }
    for (new i = 0; i < 72; i++) {
        DestroyPlayerTD(playerid,GovnisheKletki[playerid][i]);
    }
    for (new i = 0; i < 6; i++) {
	    DestroyPlayerTD(playerid, InfoItems[playerid][i]);
	}
	for (new i = 0; i < 7; i++) {
	    DestroyPlayerTD(playerid, TDinv[playerid][i]);
	}
	for (new i = 0; i < 8; i++) {
	    DestroyPlayerTD(playerid, dropmenu[playerid][i]);
	}
	for (new i = 0; i < 4; i++) {
	    PlayerTextDrawHide(playerid, TDinvTrash[playerid][i]);
	}
	CancelSelectTextDraw(playerid);
	playerData[playerid][pSecondpage] = 0;
	return true;
}

stock _GiveWeaponFromItem(playerid, itemIndex, slot) {
	if (weaponOn[playerid]) {
		ResetPlayerWeapons(playerid);
		ResetPlayerCustomWeapon(playerid);
		weaponOn[playerid] = false;
		SendCongratMessage(playerid, "{FFFFFF}�س�������ظ���º��������");
	} else {
		new variant[25];
		strmid(variant, ItemsInfo[itemIndex][ItemPhoneColor], 0, sizeof(variant));

		new itemName[128];
		strmid(itemName, ItemsInfo[itemIndex][ItemName2], 0, sizeof(itemName));

		new weaponID = -1;
		new ammo     = 0;

		if      (!strcmp(itemName, "Colt 45",        true)) { weaponID = WEAPON_COLT45;   }
		else if (!strcmp(itemName, "Colt 45 Gold",   true)) { weaponID = WEAPON_COLT45;   }
		else if (!strcmp(itemName, "Silenced",       true)) { weaponID = WEAPON_SILENCED; }
		else if (!strcmp(itemName, "Desert Eagle",   true)) { weaponID = WEAPON_DEAGLE;   }
		else if (!strcmp(itemName, "Desert Eagle+",  true)) { weaponID = WEAPON_DEAGLE;   }
		else if (!strcmp(itemName, "Micro Uzi",      true)) { weaponID = WEAPON_UZI;      }
		else if (!strcmp(itemName, "MP5",            true)) { weaponID = WEAPON_MP5;      }
		else if (!strcmp(itemName, "Tec-9",          true)) { weaponID = WEAPON_TEC9;     }
		else if (!strcmp(itemName, "AK-47",          true)) { weaponID = WEAPON_AK47;     }
		else if (!strcmp(itemName, "AK-47 Elite",    true)) { weaponID = WEAPON_AK47;     }
		else if (!strcmp(itemName, "M4",             true)) { weaponID = WEAPON_M4;       }
		else if (!strcmp(itemName, "M4 Silenced",    true)) { weaponID = WEAPON_M4;       }
		else if (!strcmp(itemName, "Shotgun",        true)) { weaponID = WEAPON_SHOTGUN;  }
		else if (!strcmp(itemName, "Shotgun Slug",   true)) { weaponID = WEAPON_SHOTGUN;  }
		else if (!strcmp(itemName, "Sawnoff Shotgun",true)) { weaponID = WEAPON_SAWEDOFF; }
		else if (!strcmp(itemName, "Combat Shotgun", true)) { weaponID = WEAPON_SHOTGSPA; }
		else if (!strcmp(itemName, "Sniper Rifle",   true)) { weaponID = WEAPON_SNIPER;   }
		else if (!strcmp(itemName, "Sniper Mk.II",   true)) { weaponID = WEAPON_SNIPER;   }
		else if (!strcmp(itemName, "Rifle",          true)) { weaponID = WEAPON_RIFLE;    }
		else if (!strcmp(itemName, "Knife",          true)) { weaponID = WEAPON_KNIFE;     ammo = 1;  }
		else if (!strcmp(itemName, "Knife+",         true)) { weaponID = WEAPON_KNIFE;     ammo = 1;  }
		else if (!strcmp(itemName, "Baseball Bat",   true)) { weaponID = WEAPON_BAT;       ammo = 1;  }

		if (weaponID == -1) return 1; // ��辺 mapping

		new bool:isMelee = (weaponID == WEAPON_KNIFE || weaponID == WEAPON_BAT ||
							weaponID == WEAPON_BRASSKNUCKLE || weaponID == WEAPON_KATANA ||
							weaponID == WEAPON_CHAINSAW);
		
		if (!isMelee) {
			for (new i = 0; i < MAX_INVENTORY_SLOTS; i++) {
				new idx = playerData[playerid][pInventory][i];
				if (idx <= 0) continue;

				if (!strcmp(ItemsInfo[idx][ItemName2], "����ع", true)) {
					new qty = playerData[playerid][pInventoryKolvo][i];
					ammo += qty;
				}
			}

			if (ammo <= 0) return SendErrorMessage(playerid, "{FFFFFF}�س����ա��ͧ����ع �س����ö��ҿ���ͧ����ع��");
		}

		ResetPlayerWeapons(playerid);
		ResetPlayerCustomWeapon(playerid);

		playerData[playerid][pEquippedWeaponSlot] = slot;

		new cwIndex = FindCustomWeaponByName(itemName);
		if (cwIndex != -1) SetPlayerCustomWeapon(playerid, cwIndex);

		GivePlayerWeapon(playerid, weaponID, ammo);
		
		g_PlayerLastAmmo[playerid] = ammo;
		weaponOn[playerid] = true;

		SendCongratMessage(playerid, "{FFFFFF}�س��ҹ���ظ {FDCF28}%s {FFFFFF}(%d �Ѵ)", itemName, ammo);
	}
	return 1;
}

stock AddItemByName(playerid, const name[], val) {
	if (!playerData[playerid][IsLoggedIn]) return 1;
	for (new s = 0; s < MAX_ITEMS; s++) {
		if (!strcmp(ItemsInfo[s][ItemName2], name, true)) {
			AddItem(playerid, s, val);
			continue;
		}
	}
	return 1;
}

hook OnPlayerUpdate(playerid) {
    if (!playerData[playerid][IsLoggedIn]) return 1;

    new weaponID = GetPlayerWeapon(playerid);
    new ammo     = GetPlayerAmmo(playerid);
    new wstate    = GetPlayerWeaponState(playerid);

    if (wstate == -1) return 1;

    new bool:isMelee = (weaponID == WEAPON_KNIFE || weaponID == WEAPON_BAT ||
                        weaponID == WEAPON_BRASSKNUCKLE || weaponID == WEAPON_KATANA ||
                        weaponID == WEAPON_CHAINSAW || weaponID == 0);

    if (isMelee) {
        g_PlayerLastAmmo[playerid] = -1;
        return 1;
    }

    if (g_PlayerLastAmmo[playerid] == -1) {
        g_PlayerLastAmmo[playerid] = ammo;
        return 1;
    }

    new shotsFired = g_PlayerLastAmmo[playerid] - ammo;

    if (shotsFired > 0) {
        new remaining = shotsFired;

        for (new i = 0; i < MAX_INVENTORY_SLOTS && remaining > 0; i++) {
            new idx = playerData[playerid][pInventory][i];
            if (idx <= 0) continue;

            if (!strcmp(ItemsInfo[idx][ItemName2], "����ع", true)) {
                new qty = playerData[playerid][pInventoryKolvo][i];

                if (qty <= remaining) {
                    remaining -= qty;
                    CallLocalFunction("DeleteItem", "ddd", playerid, idx, qty);
                } else {
                    CallLocalFunction("DeleteItem", "ddd", playerid, idx, remaining);
                    remaining = 0;
                }
            }
        }
        SaveInventoryKolvo(playerid);
    }

    g_PlayerLastAmmo[playerid] = ammo;
    return 1;
}

stock UseItem(playerid, td, itemIndex, itemModel) {
    new IDS = PickInvent[playerid];
    if (IDS < 0 || IDS >= MAX_INVENTORY_SLOTS) return 0;

    updateslot6(playerid);
    playerData[playerid][pDopKletki] = 0;
    for (new i = 0; i < 7; i++) DestroyPlayerTD(playerid, fstd_p[playerid][i]);
    for (new i = 0; i < 8; i++) DestroyPlayerTD(playerid, dropmenu[playerid][i]);
    for (new i = 0; i < 6; i++) DestroyPlayerTD(playerid, InfoItems[playerid][i]);
    for (new i = 0; i < 2; i++) PlayerTextDrawHide(playerid, TDinvTrash[playerid][i]);

    if (ItemsInfo[itemIndex][itemused] == false) {
        if (musorka[playerid] >= 1) {
            RefreshInv2(playerid, td);
            va_SendClientMessage(playerid, COLOR_RED, "[��ͼԴ��Ҵ] {FFFFFF}�س����ö�����觢ͧ��੾�Т�ҧ�ѧ�����ҹ��");
        }
        if (musorka[playerid] == 0) {
            SetPVarInt(playerid, "dItemID", itemIndex);
			SetPVarInt(playerid, "dItemSlot", IDS);
            DropitemsAskDialog(playerid);
            HideInventory(playerid);
        }
        return true;
    }

    switch (itemModel) { // �� itemModel ����Ѻ�� case
		// �� USE ���ظ
		case 321 .. 372: {
			_GiveWeaponFromItem(playerid, itemIndex, IDS);
			RefreshInv2(playerid, td);
			closeuse(playerid);
		}
		// �� USE ���ͧ����ع
		case 2041: {
			for (new s = 0; s < MAX_ITEMS; s++) {
				if (!strcmp(ItemsInfo[s][ItemName2], "����ع", true)) {
					AddItem(playerid, s, 30);
				}
			}
			CallLocalFunction("DeleteItem", "ddd", playerid, itemIndex, 1);
			// RefreshInv2(playerid, td);
			// closeuse(playerid);
		}
        // �� USE �ͧ�Թ
		case 2768: {
			if (playerData[playerid][pHungry] >= 100) return SendErrorMessage(playerid, "{FFFFFF}�͹���س�ѧ�����������");

			GivePlayerHungry(playerid, 10);
			ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
			CallLocalFunction("DeleteItem", "ddd", playerid, itemIndex, 1);
			SendCongratMessage(playerid, "{FFFFFF}�س���Ѻ��зҹ����� (�������� +10)");
			// RefreshInv2(playerid, td);
			// closeuse(playerid);
		}
		// �� USE �ͧ�Թ
		case 2647: {
			if (playerData[playerid][pThirsty] >= 100) return SendErrorMessage(playerid, "{FFFFFF}�͹���س�ѧ�����ǹ��");

			GivePlayerThirsty(playerid, 10);
			ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
			CallLocalFunction("DeleteItem", "ddd", playerid, itemIndex, 1);
			SendCongratMessage(playerid, "{FFFFFF}�س���������ͧ���� (��Ҿ�ѧ�ҹ +10)");
			// RefreshInv2(playerid, td);
			// closeuse(playerid);
		}
		// �� PUT �ͧ���觵�Ǩ��ҷ����
        case 19090..19091,19092,18636,19487,19352,19064,19065,19066,19200,19141,2908,19314,19094,19136,18952,19346,19137,19067..19069,19554,18953,18954,18968,18967,18969,18955,18956,18957,18959,18926,18927,18928,18929,18930,18931,18932,18933,19104..19109,18921..18925,19519,19274,18906..18910,18970..18973,18947,18948,18949,18950,18951,19521: {
			if (playerData[playerid][pSlotItem][2] != 0) return ShowDialogSlotItem(playerid, 2);
			CheckAks3(playerid, itemModel, PickInvent[playerid]);
		}
		// �� PUT �ͧ���觵�Ǩ��ҷ����
		case 2102,2690,2045,19590,19631,2226,19591,1276,19317,19319,19318,19054,19055,19056,19057,19058,19847,2803,19878,2406,3026,19559,19636,2511,8492,19332,19333,19334,19335,19336,19337,19338: {
			if (playerData[playerid][pSlotItem][5] != 0) return ShowDialogSlotItem(playerid, 3);
			CheckAks(playerid, itemModel, PickInvent[playerid]);
		}
		// �� PUT �ͧ���觵�Ǩ��ҷ����
		case 18963,19036,19037,19038,19472,19350,19085,11704,6865,18911..18920: {
			if (playerData[playerid][pSlotItem][1] != 0) return ShowDialogSlotItem(playerid, 1);
			CheckAks2(playerid, itemModel, PickInvent[playerid]);
		}
		// �� PUT �ͧ���觵�Ǩ��ҷ����
		case 19011..19019: {
			if (playerData[playerid][pSlotItem][7] != 0) return ShowDialogSlotItem(playerid, 7);
			CheckAks8(playerid, itemModel, PickInvent[playerid]);
		}
		// �� PUT �ͧ���觵�Ǩ��ҷ����
		case 19039..19053: {
			if (playerData[playerid][pSlotItem][6] != 0) return ShowDialogSlotItem(playerid, 6);
			CheckAks7(playerid, itemModel, PickInvent[playerid]);
		}
		// �� PUT �ͧ���觵�Ǩ��ҷ����
		case 19421..19424: {
			if (playerData[playerid][pSlotItem][0] != 0) return ShowDialogSlotItem(playerid, 0);
			CheckAks6(playerid, itemModel, PickInvent[playerid]);
		}
		// ���� PUT ʡԹ���ҷ����
		case 1..311: {
			new skin = GetPlayerSkin(playerid);
            PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][46], 0x333333FF);
            timeskin[playerid] = 0;
            clickOnSkin[playerid] = 0;
            PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], (skin == DEFAULT_PLAYER_SKIN_MALE || skin == DEFAULT_PLAYER_SKIN_FEMALE) ? 0 : 1);
            PlayerTextDrawHide(playerid, InvTextDraws[playerid][46]);
            PlayerTextDrawShow(playerid, InvTextDraws[playerid][46]);
            CheckSuka(playerid);
            clickOnSkin[playerid] = 0;
		}
    }
    RefreshInv2(playerid, td);
    return 1;
}

stock bool:InfoItem(playerid, td) {
    new IDS = td;
    new ID = playerData[playerid][pInventory][IDS];
    deletevy(playerid);
    updateslot6(playerid);
    new str[570];
    for (new i = 0; i < 312; i++) {
        if (playerData[playerid][pInventory][IDS] == i) {
            if (GetPlayerSkin(playerid) != DEFAULT_PLAYER_SKIN_MALE && GetPlayerSkin(playerid) != DEFAULT_PLAYER_SKIN_FEMALE) {
                PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], 1);
                PlayerTextDrawHide(playerid, InvTextDraws[playerid][46]);
                PlayerTextDrawShow(playerid, InvTextDraws[playerid][46]);
            }
        }
    }
    PlayerTextDrawSetSelectable(playerid, Govnishe[playerid][IDS], 1);
    for (new i = 0; i < 7; i++) {
        DestroyPlayerTD(playerid, fstd_p[playerid][i]);
    }
    for (new i = 0; i < 8; i++) {
        DestroyPlayerTD(playerid, dropmenu[playerid][i]);
    }
    for (new i = 0; i < 6; i++) {
        DestroyPlayerTD(playerid, InfoItems[playerid][i]);
    }
    if (PickInvent[playerid] != INVALID_SLOT) {
        PlayerTextDrawBackgroundColor(playerid, Govnishe[playerid][td], 0x333333FF);
    }
    format(str, sizeof(str), "{FFFFFF}%s\n%s", ItemsInfo[ID][ItemName], ItemsInfo[ID][ItemInfos]);
	ShowInvInfoItems(playerid, str);
    RefreshInv2(playerid, td);
    return true;
}

stock ShowInvInfoItems(playerid, const str[]) {
	inline Response(response, listitem, string:inputtext[]) {
		#pragma unused listitem, inputtext
		if (response) {
			playerData[playerid][pDolboeb] = 0;
		}
	}
	Dialog_ShowCallback(playerid, using inline Response, 0
		, "����������ǡѺ����"
		, str
		, "�Դ"
		, ""
	);
	return 1;
}

stock ShowItemInfoDialog(playerid, page) {
    new str[4096];
    str[0] = EOS;

    new start = ITEM_START + (page * ITEMS_PER_PAGE);
    new end = start + ITEMS_PER_PAGE;

    if (end > MAX_ITEMS)
		end = MAX_ITEMS;

    for (new i = start; i < end; i++) {
        format(str, sizeof(str), "%s{FFFFFF}%d - %s\n", str, i, ItemsInfo[i][ItemName2]);
    }

    if (end < MAX_ITEMS)
        strcat(str, "{FFD700}>>> ˹�ҶѴ�\n");

    if (page > 0)
        strcat(str, "{FFD700}<<< ˹�ҡ�͹");

    SetPVarInt(playerid, "ItemInfoPage", page);

	inline Response(response, listitem, string:inputtext[]) {
		#pragma unused inputtext

		if (!response) @return 1;

		new _page = GetPVarInt(playerid, "ItemInfoPage");
		new _start = ITEM_START + (_page * ITEMS_PER_PAGE);
		new totalOnPage = min(ITEMS_PER_PAGE, MAX_ITEMS - _start);

		new hasNext = (_start + totalOnPage < MAX_ITEMS);
		new hasPrev = (_page > 0);

		if (hasNext && listitem == totalOnPage) {
			ShowItemInfoDialog(playerid, _page + 1);
			@return 1;
		}

		if (hasPrev && hasNext && listitem == totalOnPage + 1) {
			ShowItemInfoDialog(playerid, _page - 1);
			@return 1;
		}

		if (hasPrev && !hasNext && listitem == totalOnPage) {
			ShowItemInfoDialog(playerid, _page - 1);
			@return 1;
		}

		if (listitem < totalOnPage) {
			new itemid = _start + listitem;

			inline Response2(response2, listitem2, string:inputtext2[]) {
				#pragma unused listitem2
				if (!response2)
					@return ShowItemInfoDialog(playerid, 1);
				
				if (inputtext2[0] == '\0')
					@return 1;

				for (new i = 0; inputtext2[i] != '\0'; i++) {
					if (inputtext[i] < '0' || inputtext[i] > '9') {
						va_SendClientMessage(playerid, COLOR_RED, "[!] {FFFFFF}��س�������Ţ��ҹ��");
						ShowItemInfoDialog(playerid, 1);
						@return 1;
					}
				}

				va_SendClientMessage(
					playerid,
					COLOR_GREEN,
					"[������] {FFFFFF}�س��������¡�ù��ŧ㹤�ѧ�Թ��Ңͧ�س���º��������"
				);
				SendAdminMessage(COLOR_ADMIN
					, "AdmLog: %s ���������� %s ������ͧ �ӹǹ %i ���"
					, GetPlayerNameEx(playerid)
					, ItemsInfo[itemid][ItemName]
					, strval(inputtext2)
				);

				AddItem(playerid, itemid, strval(inputtext2));
				SaveInventory(playerid);
			}
			Dialog_ShowCallback(playerid, using inline Response2, DIALOG_STYLE_INPUT
				, "{ffffff}��͡�ӹǹ"
				, "{FFFFFF}��سҡ�͡�ӹǹ����ͧ������"
				, "��ŧ"
				, "¡��ԡ"
			);
		}
	}
	Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_LIST
		, "{ffcd66}ID - ����"
		, str
		, "���͡"
		, "¡��ԡ"
	);
	return 1;
}

stock ShowSkinInfoDialog(playerid, page) {
    new str[4096];
    str[0] = EOS;

    new start = SKIN_START + (page * ITEMS_PER_PAGE);
    new end = start + ITEMS_PER_PAGE;

    if (end > 312)
		end = 312;

    for (new i = start; i < end; i++) {
        format(str, sizeof(str), "%s{FFFFFF}%d - %s\n", str, i, ItemsInfo[i][ItemName2]);
    }

    if (end < 312)
        strcat(str, "{FFD700}>>> ˹�ҶѴ�\n");

    if (page > 0)
        strcat(str, "{FFD700}<<< ˹�ҡ�͹");

    SetPVarInt(playerid, "SkinInfoPage", page);

	inline Response(response, listitem, string:inputtext[]) {
		#pragma unused inputtext

		if (!response) @return 1;

		new _page = GetPVarInt(playerid, "SkinInfoPage");
		new _start = SKIN_START + (_page * ITEMS_PER_PAGE);
		new totalOnPage = min(ITEMS_PER_PAGE, 312 - _start);

		new hasNext = (_start + totalOnPage < 312);
		new hasPrev = (_page > 0);

		if (hasNext && listitem == totalOnPage) {
			ShowSkinInfoDialog(playerid, _page + 1);
			@return 1;
		}

		if (hasPrev && hasNext && listitem == totalOnPage + 1) {
			ShowSkinInfoDialog(playerid, _page - 1);
			@return 1;
		}

		if (hasPrev && !hasNext && listitem == totalOnPage) {
			ShowSkinInfoDialog(playerid, _page - 1);
			@return 1;
		}

		if (listitem < totalOnPage) {
			new itemid = _start + listitem;

			va_SendClientMessage(
				playerid,
				COLOR_GREEN,
				"[������] {FFFFFF}�س��������¡�ù��ŧ㹤�ѧ�Թ��Ңͧ�س���º��������"
			);
			SendAdminMessage(COLOR_ADMIN
				, "AdmLog: %s ������ʡԹ %s ���Ѻ����ͧ 1 ʡԹ"
				, GetPlayerNameEx(playerid)
				, ItemsInfo[itemid][ItemName]
			);

			AddItem(playerid, itemid, 1);
			SaveInventory(playerid);
		}
	}
	Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_LIST
		, "{ffcd66}ID - ����"
		, str
		, "���͡"
		, "¡��ԡ"
	);
	return 1;
}

stock GetInvSet(playerid) {
	new num;
	for (new i; i < MAX_SLOT_ITEMS; i++) {
	    if (playerData[playerid][pInventory][i] != 0) num++;
	}
	return num;
}

stock AddItem(playerid, itemid, amount) {
    new string[256];
    if (GetInvSet(playerid) >= MAX_SLOT_ITEMS) 
        return va_SendClientMessage(playerid, COLOR_RED, "[��ͼԴ��Ҵ] {FFFFFF}�س�վ�鹷��㹤�ѧ�Թ��������§��");

    for (new i = 0; i < 72; i++) {
        if (playerData[playerid][pInventory][i] != itemid) continue;
        if (!Custom_AddInvItem(playerid, i, itemid, amount)) continue;
        if (amount >= 2)
            format(string, sizeof(string), "[��¡����觢ͧ] {FFFFFF}�ա��������¡���������Ѻ�س '%s' (%d ���). �ҡ��ͧ����Դ����¡���Թ��Ңͧ�س �� 'Y'", ItemsInfo[itemid][ItemName2], amount);
        else
            format(string, sizeof(string), "[��¡����觢ͧ] {FFFFFF}�ա��������¡���������Ѻ�س '%s' �ҡ��ͧ����Դ����¡���Թ��Ңͧ�س �� 'Y'", ItemsInfo[itemid][ItemName2]);
        va_SendClientMessage(playerid, COLOR_YELLOW, string);
        SaveInventory(playerid);
        return 1;
    }

    for (new i = 0; i < 72; i++) {
        if (playerData[playerid][pInventory][i] != 0) continue;
        if (!Custom_SetInvItem(playerid, i, itemid, amount)) continue;
        if (amount >= 2)
            format(string, sizeof(string), "[��¡����觢ͧ] {FFFFFF}�ա��������¡���������Ѻ�س '%s' (%d ���). �ҡ��ͧ����Դ����¡���Թ��Ңͧ�س �� 'Y'", ItemsInfo[itemid][ItemName2], amount);
        else
            format(string, sizeof(string), "[��¡����觢ͧ] {FFFFFF}�ա��������¡���������Ѻ�س '%s' �ҡ��ͧ����Դ����¡���Թ��Ңͧ�س �� 'Y'", ItemsInfo[itemid][ItemName2]);
        va_SendClientMessage(playerid, COLOR_YELLOW, string);
        SaveInventory(playerid);
        return 1;
    }

    return 1;
}

/* ######################################################################## */
/* # ???????????  ?????  ????? ???????????  ?????       ?????   ????????? # */
/* #??????????????????  ????? ??????????????????       ?????   ???????????# */
/* # ????    ???? ????   ????  ????    ???? ????        ????  ???     ??? # */
/* # ???????????  ????   ????  ???????????  ????        ???? ????         # */
/* # ??????????   ????   ????  ???????????? ????        ???? ????         # */
/* # ????         ????   ????  ????    ???? ????      ? ???? ?????     ???# */
/* # ?????        ??????????   ???????????  ??????????? ????? ??????????? # */
/* #?????          ????????   ???????????  ??????????? ?????   ?????????  # */
/* ######################################################################## */

public Custom_AddInvItem(playerid, slot, itemid, quantity) {
	new
		max_quantity = 0,
		last_quantity,
		total_quantity;

	max_quantity = ItemsInfo[itemid][ItemQuantity];
	if (!max_quantity) return 0;
	if (playerData[playerid][pInventoryKolvo][slot] >= max_quantity) return 0;

	total_quantity = playerData[playerid][pInventoryKolvo][slot] + quantity;
	if (total_quantity > max_quantity) {
		last_quantity = total_quantity - max_quantity;
		playerData[playerid][pInventoryKolvo][slot] = max_quantity;
	} else playerData[playerid][pInventoryKolvo][slot] += quantity;
    if (TradeDone[playerid] == -1) RefreshInv2(playerid, slot);
	if (last_quantity) CallLocalFunction("AddItem", "ddd", playerid, itemid, last_quantity);
	return 1;
}

public Custom_SetInvItem(playerid, slot, itemid, quantity) {
	new
		max_quantity = 0,
		last_quantity;

	max_quantity = ItemsInfo[itemid][ItemQuantity];
	if (!max_quantity) return 0;
	if (playerData[playerid][pInventoryKolvo][slot] >= max_quantity)return 0;

	if (quantity > max_quantity) {
		last_quantity = quantity - max_quantity;
		quantity = max_quantity;
	}

	playerData[playerid][pInventory][slot] = itemid;
    playerData[playerid][pInventoryKolvo][slot] = quantity;
    InvSlotUpdate(playerid, slot, itemid);
    if (last_quantity) CallLocalFunction("AddItem", "ddd", playerid, itemid, last_quantity);
	return 1;
}

public CheepsTimer(playerid) {
    playerData[playerid][pCheepsTimer] = 0;
}

public DeleteItem(playerid, itemid, amount) {
    if (amount <= 0) return 1;
    if (itemid < 0 || itemid >= MAX_ITEMS) return 1;

    for (new i = 0; i < 72; i++) {
        if (playerData[playerid][pInventory][i] != itemid) continue;

        new current = playerData[playerid][pInventoryKolvo][i];

        if (amount >= current) {
            new remain = amount - current;
            playerData[playerid][pInventory][i] = 0;
            playerData[playerid][pInventoryKolvo][i] = 0;
            RefreshInv2(playerid, i);
            SaveInventory(playerid);
            if (remain > 0)
                CallLocalFunction("DeleteItem", "ddd", playerid, itemid, remain);
        } else {
            playerData[playerid][pInventoryKolvo][i] -= amount;
            RefreshInv2(playerid, i);
            SaveInventory(playerid);
        }
        return 1;
    }
    return 1;
}

/* ######################################################### */
/* # ?????   ?????    ???????       ???????    ?????   ????# */
/* #?????   ?????   ???????????   ??????????? ?????   ???? # */
/* # ????    ????  ???     ????? ???     ????? ????  ???   # */
/* # ???????????? ????      ????????      ???? ????????    # */
/* # ???????????? ????      ????????      ???? ?????????   # */
/* # ????    ???? ?????     ??? ?????     ???  ???? ?????  # */
/* # ?????   ????? ???????????   ???????????   ????? ??????# */
/* #?????   ?????    ???????       ???????    ?????   ???? # */
/* ######################################################### */

hook OnLoginFinished(playerid) {
	LoadInventoryKolvo(playerid);
	LoadInventory(playerid);
	LoadAks(playerid);
    return 1;
}

hook ResetArray(playerid) {
	clickOnSkin[playerid] = 0;
	return 1;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid) {
    if (playertextid == InvTextDraws[playerid][8]) {
		SwitchInventoryPage(playerid, 1);
		return 1;
	}

	if (playertextid == InvTextDraws[playerid][9]) {
        SwitchInventoryPage(playerid, 0);
		return 1;
	}

    if (playertextid == InfoItems[playerid][2]) {
        updateslot6(playerid);
        new item = playerData[playerid][pInventory][PickInvent[playerid]];
		new skin = GetPlayerSkin(playerid);

		if (item >= 1 && item < 312) {
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][46], 0x333333FF);

			timeskin[playerid] = 0;
			clickOnSkin[playerid] = 0;

			if (skin == DEFAULT_PLAYER_SKIN_MALE || skin == DEFAULT_PLAYER_SKIN_FEMALE) {
				PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], false);
			} else {
				PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], true);
			}

			PlayerTextDrawHide(playerid, InvTextDraws[playerid][46]);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][46]);
		}
        new IDS = PickInvent[playerid];
        new ID = playerData[playerid][pInventory][IDS];
        UseItem(playerid, IDS, ID, ItemsInfo[ID][ItemModel]);
        SetTimerEx("CheepsTimer",3000,0,"d",playerid);
		return 1;
    }

    if (playertextid == InfoItems[playerid][1]) {
        new IDS = PickInvent[playerid];
        RefreshInv2(playerid, PickInvent[playerid]);
        InfoItem(playerid, IDS);
        playerData[playerid][pDolboeb] = 1;
        updateslot6(playerid);
		return 1;
    }

    if (playertextid == InfoItems[playerid][0]) {
        deletevy(playerid);
		PlayerTextDrawSetSelectable(playerid, Govnishe[playerid][PickInvent[playerid]], 1);
		PlayerTextDrawHide(playerid, Govnishe[playerid][PickInvent[playerid]]);
		PlayerTextDrawShow(playerid, Govnishe[playerid][PickInvent[playerid]]);
		for (new i = 0; i < 6; i++) {
		    PlayerTextDrawHide(playerid, InfoItems[playerid][i]);
		}
		updateslot6(playerid);
		RefreshInv2(playerid, PickInvent[playerid]);
		PickInvent[playerid] = INVALID_SLOT;
		clickOnSkin[playerid] = 0;
		return 1;
	}

    if (playertextid == fstd_p[playerid][3]) {
        if (AksVid2[playerid] != 0) {
            if (playerData[playerid][pSlotItem][5] == 2) {
                ApplyAnimation(playerid,"FOOD","EAT_Burger",4.1,0,0,0,0,0,1);
            }
            for (new i = 0; i < 7; i++) {
                DestroyPlayerTD(playerid, fstd_p[playerid][i]);
            }
            AksVid2[playerid] = 0;
            return true;
        }
        new IDS = PickInvent[playerid];
        new ID = playerData[playerid][pInventory][IDS];
        UseItem(playerid, IDS, ID, ItemsInfo[ID][ItemModel]);
        SetTimerEx("CheepsTimer",3000,0,"d",playerid);
        updateslot6(playerid);
		return 1;
	}

    if (playertextid == fstd_p[playerid][2]) {
		if (AksVid2[playerid] != 0) {
		    for (new i = 0; i < 72; i++) {
                if (playerData[playerid][pInventory][i] != 0) continue;
                playerData[playerid][pInventory][i] = AksSlot[playerid][5];
                playerData[playerid][pInventoryKolvo][i] = 1;
                PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
                PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][34], 1649);
                PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][34], 0.000000, 0.000000, 90.000000, 2.000000);
                PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][34], 0x333333FF);
                PlayerTextDrawHide(playerid, InvTextDraws[playerid][34]);
                PlayerTextDrawShow(playerid, InvTextDraws[playerid][34]);

                playerData[playerid][pSlotItem][5] = 0;
                AksSlot[playerid][5] = 0;
                RemovePlayerAttachedObject(playerid, 5);
                AksVid[playerid] = 0;
                AksVid2[playerid] = 0;
                deletevy(playerid);
                playerData[playerid][pSlotItem][5] = 0;
                AksSlot[playerid][5] = 0;
                RefreshInv2(playerid, i);
                SaveAks(playerid);
                UpdatePlayerDataEx(playerid, "pSlotItem0", playerData[playerid][pSlotItem][0]);
                UpdatePlayerDataEx(playerid, "pSlotItem1", playerData[playerid][pSlotItem][1]);
                UpdatePlayerDataEx(playerid, "pSlotItem2", playerData[playerid][pSlotItem][2]);
                UpdatePlayerDataEx(playerid, "pSlotItem3", playerData[playerid][pSlotItem][3]);
                UpdatePlayerDataEx(playerid, "pSlotItem4", playerData[playerid][pSlotItem][4]);
                UpdatePlayerDataEx(playerid, "pSlotItem5", playerData[playerid][pSlotItem][5]);
                return true;
	  		}
	  		return true;
		}
  		deletevy(playerid);
        updateslot6(playerid);
		if (playerData[playerid][pInventoryKolvo][PickInvent[playerid]] >= 2) {
			if (GetInvSet(playerid) >= MAX_SLOT_ITEMS) return RefreshInv2(playerid, PickInvent[playerid]), SendErrorMessage(playerid, "{FFFFFF}�س�վ�鹷��㹡����������§��!");
			playerData[playerid][pInventoryKolvoDop] = playerData[playerid][pInventoryKolvo][PickInvent[playerid]];
			if (playerData[playerid][pInventoryKolvo][PickInvent[playerid]] % 2 == 0) {
			    playerData[playerid][pInventoryKolvo][PickInvent[playerid]] /= 2;
			} else {
			    playerData[playerid][pInventoryKolvo][PickInvent[playerid]] ++;
				playerData[playerid][pInventoryKolvo][PickInvent[playerid]] /= 2;
			}
			PlayerPlaySound(playerid, 17803, 0.0, 0.0, 0.0);
			va_SendClientMessage(playerid, COLOR_YELLOW, "�س������¡�ù�����º��������");
	    	for (new i = 0; i < 72; i++) {
                if (playerData[playerid][pInventory][i] != 0) continue;
                playerData[playerid][pInventory][i] = playerData[playerid][pInventory][PickInvent[playerid]];
                playerData[playerid][pInventoryKolvo][i] += playerData[playerid][pInventoryKolvo][PickInvent[playerid]];
                if (playerData[playerid][pInventoryKolvoDop] % 2 != 0) {
                    playerData[playerid][pInventoryKolvo][i] -= 1;
                }
                RefreshInv2(playerid, PickInvent[playerid]);
                RefreshInv2(playerid, i);
                return true;
	  		}
		} else {
			if (musorka[playerid] >= 1) {
			    RefreshInv2(playerid, PickInvent[playerid]);
				va_SendClientMessage(playerid, COLOR_RED, "[��ͼԴ��Ҵ] {FFFFFF}�س����ö�����觢ͧ��੾�Т�ҧ�ѧ�����ҹ��");
			}
			if (musorka[playerid] == 0) {
				// TODO: �к���駢ͧ (Drop Item System)
				new IDS = PickInvent[playerid];
        		new ID = playerData[playerid][pInventory][IDS];
				SetPVarInt(playerid, "dItemID", ID);
				SetPVarInt(playerid, "dItemSlot", IDS);
				DropitemsAskDialog(playerid);
				HideInventory(playerid);
			}
		}
		return 1;
    }

    if (playertextid == fstd_p[playerid][1]) {
        if (AksVid2[playerid] != 0) {
            new str[570];
            for (new i = 0; i < 7; i++) {
                DestroyPlayerTD(playerid, fstd_p[playerid][i]);
            }
            if (PickInvent[playerid] != INVALID_SLOT) {
                PlayerTextDrawBackgroundColor(playerid, Govnishe[playerid][PickInvent[playerid]], 0x333333FF);
            }
            format(str, sizeof(str), "{FFFFFF}%s\n%s", ItemsInfo[AksVid[playerid]][ItemName], ItemsInfo[AksVid[playerid]][ItemInfos]);
			ShowInvInfoItems(playerid, str);
            AksVid2[playerid] = 0;
            return true;
        }
        new IDS = PickInvent[playerid];
        RefreshInv2(playerid, PickInvent[playerid]);
        InfoItem(playerid, IDS);
        playerData[playerid][pDolboeb] = 1;
        updateslot6(playerid);
		return 1;
    }

	if (playertextid == dropmenu[playerid][4]) {
		new IDS = PickInvent[playerid];
		if (IDS < 0 || IDS >= MAX_INVENTORY_SLOTS) return 1; // guard
		new ID = playerData[playerid][pInventory][IDS];
		UseItem(playerid, IDS, ID, ItemsInfo[ID][ItemModel]);
		SetTimerEx("CheepsTimer", 3000, 0, "d", playerid);
		updateslot6(playerid);
		return 1;
	}

	if (playertextid == dropmenu[playerid][3]) {
		if (musorka[playerid] >= 1) {
		    RefreshInv2(playerid, PickInvent[playerid]);
			va_SendClientMessage(playerid, COLOR_RED, "[��ͼԴ��Ҵ] {FFFFFF}�س����ö�����觢ͧ��੾�Т�ҧ�ѧ�����ҹ��");
		}
		if (musorka[playerid] == 0) {
			// TODO: �к���駢ͧ (Drop Item System)
			new IDS = PickInvent[playerid];
			new ID = playerData[playerid][pInventory][IDS];
			SetPVarInt(playerid, "dItemID", ID);
			SetPVarInt(playerid, "dItemSlot", IDS);
			DropitemsAskDialog(playerid);
			HideInventory(playerid);
		}
		return 1;
	}

	if (playertextid == dropmenu[playerid][2]) {
        if (GetInvSet(playerid) >= MAX_SLOT_ITEMS) return RefreshInv2(playerid, PickInvent[playerid]), SendErrorMessage(playerid, "{FFFFFF}�س�վ�鹷��㹡����������§��!");
        playerData[playerid][pInventoryKolvoDop] = playerData[playerid][pInventoryKolvo][PickInvent[playerid]];
        if (playerData[playerid][pInventoryKolvo][PickInvent[playerid]] % 2 == 0) {
            playerData[playerid][pInventoryKolvo][PickInvent[playerid]] /= 2;
        } else {
            playerData[playerid][pInventoryKolvo][PickInvent[playerid]] ++;
            playerData[playerid][pInventoryKolvo][PickInvent[playerid]] /= 2;
        }
        PlayerPlaySound(playerid, 17803, 0.0, 0.0, 0.0);
        va_SendClientMessage(playerid, COLOR_YELLOW, "�س������¡�ù�����º��������");
        for (new i = 0; i < 72; i++) {
            if (playerData[playerid][pInventory][i] != 0) continue;
            playerData[playerid][pInventory][i] = playerData[playerid][pInventory][PickInvent[playerid]];
            playerData[playerid][pInventoryKolvo][i] += playerData[playerid][pInventoryKolvo][PickInvent[playerid]];
            if (playerData[playerid][pInventoryKolvoDop] % 2 != 0) {
                playerData[playerid][pInventoryKolvo][i] -= 1;
            }
            RefreshInv2(playerid, PickInvent[playerid]);
            RefreshInv2(playerid, i);
            return true;
        }
		return 1;
	}

	if (playertextid == dropmenu[playerid][1]) {
	    new IDS = PickInvent[playerid];
	    RefreshInv2(playerid, PickInvent[playerid]);
        InfoItem(playerid, IDS);
        playerData[playerid][pDolboeb] = 1;
		updateslot6(playerid);
		return 1;
	}

	if (playertextid == dropmenu[playerid][0]) {
	    for (new i = 0; i < 8; i++) {
		    DestroyPlayerTD(playerid, dropmenu[playerid][i]);
		}
		updateslot6(playerid);
		RefreshInv2(playerid, PickInvent[playerid]);
		PickInvent[playerid] = INVALID_SLOT;
		clickOnSkin[playerid] = 0;
		return 1;
	}

    if (playertextid == fstd_p[playerid][0]) {
        if (AksVid2[playerid] != 0) {
            for (new i = 0; i < 7; i++) {
			    DestroyPlayerTD(playerid, fstd_p[playerid][i]);
			}
			AksVid2[playerid] = 0;
			return true;
		}
  		deletevy(playerid);
		PlayerTextDrawSetSelectable(playerid, Govnishe[playerid][PickInvent[playerid]], 1);
		PlayerTextDrawHide(playerid, Govnishe[playerid][PickInvent[playerid]]);
		PlayerTextDrawShow(playerid, Govnishe[playerid][PickInvent[playerid]]);

		for (new i = 0; i < 7; i++) {
		    DestroyPlayerTD(playerid, fstd_p[playerid][i]);
		}
		updateslot6(playerid);
		RefreshInv2(playerid, PickInvent[playerid]);
		PickInvent[playerid] = INVALID_SLOT;
		clickOnSkin[playerid] = 0;
		return 1;
	}

	// �ç����� slot �˭� 72 ��ͧ
    for (new j = 0; j < 72; j++) {
        if (playertextid == Govnishe[playerid][j]) {
            PlayerTextDrawShow(playerid, InvTextDraws[playerid][58]);
            PlayerTextDrawShow(playerid, InvTextDraws[playerid][18]);
			new ID = PickInvent[playerid];
			if (AksVid2[playerid] != 0) {
			    PickInvent[playerid] = j;
			    if (playerData[playerid][pInventory][PickInvent[playerid]] == AksSlot[playerid][5]) {
			        playerData[playerid][pInventoryKolvo][PickInvent[playerid]] += 1;
			        RefreshInv2(playerid, PickInvent[playerid]);
			        PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
			        PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][34], 1649);
	       			PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][34], 0.000000, 0.000000, 90.000000, 2.000000);
	            	PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][34], 0x333333FF);
	            	PlayerTextDrawHide(playerid, InvTextDraws[playerid][34]);
	       			PlayerTextDrawShow(playerid, InvTextDraws[playerid][34]);
	       			playerData[playerid][pSlotItem][5] = 0;
	       			AksSlot[playerid][5] = 0;
	       			RemovePlayerAttachedObject(playerid, 5);
	       			UpdatePlayerDataEx(playerid, "pSlotItem5", playerData[playerid][pSlotItem][5]);
	       			SaveAks(playerid);
	       			if (addskate[playerid] > 0) {
	       			    RemovePlayerAttachedObject(playerid, 6);
                    	addskate[playerid] = 0;
					}
				} else {
					if (playerData[playerid][pInventory][PickInvent[playerid]] != 0) return true;
				    playerData[playerid][pInventory][PickInvent[playerid]] = AksSlot[playerid][5];
			        playerData[playerid][pInventoryKolvo][PickInvent[playerid]] = 1;
			        RefreshInv2(playerid, PickInvent[playerid]);
			        PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
			        PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][34], 1649);
	       			PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][34], 0.000000, 0.000000, 90.000000, 2.000000);
	            	PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][34], 0x333333FF);
	            	PlayerTextDrawHide(playerid, InvTextDraws[playerid][34]);
	       			PlayerTextDrawShow(playerid, InvTextDraws[playerid][34]);
	       			playerData[playerid][pSlotItem][5] = 0;
	       			AksSlot[playerid][5] = 0;
	       			RemovePlayerAttachedObject(playerid, 5);
	       			SaveAks(playerid);
	       			UpdatePlayerDataEx(playerid, "pSlotItem5", playerData[playerid][pSlotItem][5]);
	       			if (addskate[playerid] > 0) {
	       			    RemovePlayerAttachedObject(playerid, 6);
                    	addskate[playerid] = 0;
					}
				}
				for (new i = 0; i < 7; i++) {
				    DestroyPlayerTD(playerid, fstd_p[playerid][i]);
				}
				AksVid2[playerid] = 0;
				return true;
			}
            if (PickInvent[playerid] == INVALID_SLOT) {
                if (playerData[playerid][pInventory][j] != 0) {
                    PickInvent[playerid] = j;

                    PlayerTextDrawShow(playerid, InvTextDraws[playerid][58]);
                    PlayerTextDrawShow(playerid, InvTextDraws[playerid][18]);
                    PlayerTextDrawSetSelectable(playerid, Govnishe[playerid][j], 0);
                    PlayerTextDrawHide(playerid, Govnishe[playerid][j]);
                    PlayerTextDrawShow(playerid, Govnishe[playerid][j]);
                    for (new i = 0; i < 30; i++) {
                        if (PickInvent[playerid] == i) {
                            PlayerTextDrawSetSelectable(playerid, Govnishe[playerid][i+6], 0);
                            PlayerTextDrawHide(playerid, Govnishe[playerid][i+6]);
                            PlayerTextDrawShow(playerid, Govnishe[playerid][i+6]);
                        }
                    }
                    for (new i = 36; i < 66; i++) {
                        if (PickInvent[playerid] == i) {
                            PlayerTextDrawSetSelectable(playerid, Govnishe[playerid][i+6], 0);
                            PlayerTextDrawHide(playerid, Govnishe[playerid][i+6]);
                            PlayerTextDrawShow(playerid, Govnishe[playerid][i+6]);
                        }
                    }
                    OnPlayerClickSlot(playerid, PickInvent[playerid]);
                }
            } else {
                if (playerData[playerid][pInventory][j] != 0) {
                    if (PickInvent[playerid] == j) return 1;

                    playerData[playerid][pProstoTak] = playerData[playerid][pInventoryKolvo][ID];
                    playerData[playerid][pProstoTak2] = playerData[playerid][pInventory][ID];
                    playerData[playerid][pInventoryKolvo][ID] = playerData[playerid][pInventoryKolvo][j];
                    playerData[playerid][pInventory][ID] = playerData[playerid][pInventory][j];
                    playerData[playerid][pInventoryKolvo][j] = playerData[playerid][pProstoTak];
                    playerData[playerid][pInventory][j] = playerData[playerid][pProstoTak2];
                    playerData[playerid][pProstoTak2] = 0;
                    playerData[playerid][pProstoTak] = 0;

                    for (new i = 0; i < 6; i++) {
                        DestroyPlayerTD(playerid, InfoItems[playerid][i]);
                    }

                    for (new i = 0; i < 7; i++) {
                        DestroyPlayerTD(playerid, fstd_p[playerid][i]);
                    }

                    for (new i = 0; i < 8; i++) {
                        DestroyPlayerTD(playerid, dropmenu[playerid][i]);
                    }

                    //==========================================================
                    PlayerTextDrawColor(playerid, GovnisheKletki[playerid][ID], 0xAAAAAAFF);
                    PlayerTextDrawColor(playerid, GovnisheKletki[playerid][j], 0xAAAAAAFF);
                    InvSlotUpdate(playerid, ID, playerData[playerid][pInventory][ID]);
                    InvSlotUpdate(playerid, j, playerData[playerid][pInventory][j]);
                    deletevy(playerid);
                    updateslot6(playerid);

                    PickInvent[playerid] = INVALID_SLOT;
					clickOnSkin[playerid] = 0;

                    PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
                    if (playerData[playerid][pInventory][j] == playerData[playerid][pInventory][ID]) {
                        if (PickInvent[playerid] == j) return 1;
                        new quantity = ItemsInfo[playerData[playerid][pInventory][j]][ItemQuantity];
                        new quantity2 = playerData[playerid][pInventoryKolvo][j]+playerData[playerid][pInventoryKolvo][ID];
                        if (quantity2 >= quantity) {
                            if (quantity2 == quantity) {
                                playerData[playerid][pInventoryKolvo][j] += playerData[playerid][pInventoryKolvo][ID]; // ���������� �������� ID � �������� ��������� ������
                                playerData[playerid][pInventory][ID] = 0; // �������� �������� ������� ��������� ������
                                playerData[playerid][pInventoryKolvo][ID] = 0; // �������� �������� ���������� ������� ��������� ������
                                RefreshInv2(playerid, j);
                                RefreshInv2(playerid, ID);
                                return true;
                            }
                            new ostatok = quantity2 - quantity;
                            playerData[playerid][pInventoryKolvo][ID] = ostatok;
                            playerData[playerid][pInventoryKolvo][j] = quantity;
                            RefreshInv2(playerid, j);
                            RefreshInv2(playerid, ID);
                            return true;
                        }
                        playerData[playerid][pInventoryKolvo][j] += playerData[playerid][pInventoryKolvo][ID]; // ���������� �������� ID � �������� ��������� ������
                        playerData[playerid][pInventory][ID] = 0; // �������� �������� ������� ��������� ������
                        playerData[playerid][pInventoryKolvo][ID] = 0; // �������� �������� ���������� ������� ��������� ������
                        for (new i = 0; i < 6; i++) {
                            DestroyPlayerTD(playerid, InfoItems[playerid][i]);
                        }
                        for (new i = 0; i < 7; i++) {
                            DestroyPlayerTD(playerid, fstd_p[playerid][i]);
                        }
                        for (new i = 0; i < 8; i++) {
                            DestroyPlayerTD(playerid, dropmenu[playerid][i]);
                        }
                        updateslot6(playerid);
                        InvSlotUpdate(playerid, ID, playerData[playerid][pInventory][ID]);
                        InvSlotUpdate(playerid, j, playerData[playerid][pInventory][j]);
                        deletevy(playerid);
                        PickInvent[playerid] = INVALID_SLOT;
						clickOnSkin[playerid] = 0;
                        PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
                    }
                }
                if (playerData[playerid][pInventory][j] == 0) {
                    deletevy(playerid);
                    playerData[playerid][pInventory][j] = playerData[playerid][pInventory][ID];
                    playerData[playerid][pInventoryKolvo][j] = playerData[playerid][pInventoryKolvo][ID];
                    playerData[playerid][pInventory][ID] = 0;
                    playerData[playerid][pInventoryKolvo][ID] = 0;
                    for (new i = 0; i < 6; i++) {
                        DestroyPlayerTD(playerid, InfoItems[playerid][i]);
                    }
                    for (new i = 0; i < 7; i++) {
                        DestroyPlayerTD(playerid, fstd_p[playerid][i]);
                    }
                    for (new i = 0; i < 8; i++) {
                        DestroyPlayerTD(playerid, dropmenu[playerid][i]);
                    }
                    updateslot6(playerid);
                    PlayerTextDrawColor(playerid, GovnisheKletki[playerid][ID], 0xAAAAAAFF);
                    PlayerTextDrawColor(playerid, GovnisheKletki[playerid][j], 0xAAAAAAFF);
                    InvSlotUpdate(playerid, j, playerData[playerid][pInventory][j]);
                    InvSlotUpdate(playerid, ID, playerData[playerid][pInventory][ID]);
                    PickInvent[playerid] = INVALID_SLOT;
					clickOnSkin[playerid] = 0;
                    PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
                }
            }

			if (playerData[playerid][pSecondpage] == 0) {
		 		for (new i = 36; i < 72; i++) {
		 			PlayerTextDrawHide(playerid, GovnisheKletki[playerid][i]);
				}
			}

			if (playerData[playerid][pSecondpage] == 1) {
				for (new i = 0; i < 36; i++) {
					PlayerTextDrawHide(playerid, GovnisheKletki[playerid][i]);
				}
			}
			return 1;
        }
    }

	if (playertextid == InvTextDraws[playerid][46]) {
		if (GetInvSet(playerid) >= MAX_SLOT_ITEMS) return va_SendClientMessage(playerid, COLOR_RED, "[��ͼԴ��Ҵ] {FFFFFF}�س����վ�鹷��㹪�ͧ�红ͧ��§�ͷ��й�����ͼ���͡");
	    if (playerData[playerid][pSkin] != GetPlayerSkin(playerid)) {

			if (GetPVarInt(playerid, "usedGangSkin") == 1) {
				SetPlayerSkinEx(playerid, playerData[playerid][pSkin]);

				new string[24];
				format(string, sizeof(string), "ID:%d", GetPlayerSkin(playerid)),
				PlayerTextDrawSetString(playerid, InvTextDraws[playerid][45], string);
				PlayerTextDrawHide(playerid, InvTextDraws[playerid][45]);
				PlayerTextDrawShow(playerid, InvTextDraws[playerid][45]);
				PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][47], GetPlayerSkin(playerid));
				PlayerTextDrawHide(playerid, InvTextDraws[playerid][47]);
				PlayerTextDrawShow(playerid, InvTextDraws[playerid][47]);

				PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
				RefreshInv2(playerid, PickInvent[playerid]);
				SetPVarInt(playerid, "usedGangSkin", 0);
				return true;
			}

			RefreshInv2(playerid, PickInvent[playerid]);
			va_SendClientMessage(playerid, COLOR_RED, "[��ͼԴ��Ҵ] {FFFFFF}�����ʹ����ͼ������ҹ���͡");
			return true;
		}

		if (playerData[playerid][pSkin] != DEFAULT_PLAYER_SKIN_MALE && playerData[playerid][pSkin] != DEFAULT_PLAYER_SKIN_FEMALE) {
		    if (timeskin[playerid] == 1) return PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0), CheckSuka(playerid);
		    if (playerData[playerid][pSecondpage] == 1) {
		    	playerData[playerid][pSkin] = (playerData[playerid][pGender] == 1) ? DEFAULT_PLAYER_SKIN_MALE : DEFAULT_PLAYER_SKIN_FEMALE;
		    	UpdatePlayerDataEx(playerid, "Skin", playerData[playerid][pSkin]);
	         	PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
		        for (new i = 0; i < 72; i++) {
			        if (playerData[playerid][pInventory][i] != 0) continue;
			        playerData[playerid][pInventoryKolvo][i] = 1;
		        	playerData[playerid][pInventory][i] = GetPlayerSkin(playerid);
		        	SetPlayerSkinEx(playerid, (playerData[playerid][pGender] == 1) ? DEFAULT_PLAYER_SKIN_MALE : DEFAULT_PLAYER_SKIN_FEMALE);
		        	return true;
				}
			}
			if (playerData[playerid][pSecondpage] == 0) {
			    new str[17];
		        playerData[playerid][pSkin] = (playerData[playerid][pGender] == 1) ? DEFAULT_PLAYER_SKIN_MALE : DEFAULT_PLAYER_SKIN_FEMALE;
		        UpdatePlayerDataEx(playerid,"Skin",playerData[playerid][pSkin]);
		        PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
		        for (new i = 0; i < 72; i++) {
			        if (playerData[playerid][pInventory][i] != 0) continue;
			        playerData[playerid][pInventory][i] = GetPlayerSkin(playerid);
			        playerData[playerid][pInventoryKolvo][i] = 1;
					SaveInventory(playerid);
			        PlayerTextDrawSetPreviewModel(playerid, Govnishe[playerid][i], GetPlayerSkin(playerid));
			    	PlayerTextDrawSetPreviewRot(playerid, Govnishe[playerid][i], 0.000000, 0.000000, 0.000000, 1.000000);
			    	PlayerTextDrawHide(playerid, Govnishe[playerid][i]);
			    	PlayerTextDrawShow(playerid, Govnishe[playerid][i]);
	       			for (new j = 1; j < 312; j++) {
						if (playerData[playerid][pInventory][i] == j) {
							format(str, sizeof(str), "ID:%d", GetPlayerSkin(playerid)),
							PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][i], str);
							PlayerTextDrawColor(playerid, GovnisheKletki[playerid][i], 0xFFFFFFFF);
							PlayerTextDrawHide(playerid, GovnisheKletki[playerid][i]);
							PlayerTextDrawShow(playerid, GovnisheKletki[playerid][i]);
	       				}
	      			}
			    	SetPlayerSkinEx(playerid, (playerData[playerid][pGender] == 1) ? DEFAULT_PLAYER_SKIN_MALE : DEFAULT_PLAYER_SKIN_FEMALE);
			    	playerData[playerid][pSkin] = (playerData[playerid][pGender] == 1) ? DEFAULT_PLAYER_SKIN_MALE : DEFAULT_PLAYER_SKIN_FEMALE;
			    	UpdatePlayerDataEx(playerid, "Skin", playerData[playerid][pSkin]);
			    	return true;
			    }
			    playerData[playerid][pSkin] = (playerData[playerid][pGender] == 1) ? DEFAULT_PLAYER_SKIN_MALE : DEFAULT_PLAYER_SKIN_FEMALE;
		    }
		}
		else PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0), CheckSuka(playerid);
		return 1;
	}
    return 0;
}

hook OnPlayerWeaponChange(playerid, oldweapon, newweapon) {
    new cw = GetPlayerCustomWeaponIndex(playerid);
    if (cw != -1) {
        if (g_WeaponTable[cw][CW_BaseWeaponID] != newweapon) {
            ResetPlayerCustomWeapon(playerid);
        }
    }
}

hook OnPlayerDeath(playerid, killerid, reason) {
    ResetPlayerCustomWeapon(playerid);
    return 1;
}
