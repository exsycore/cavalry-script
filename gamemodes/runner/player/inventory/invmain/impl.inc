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

stock CheckInvs(playerid, type) {
    if (type == 7) {
	    if (playerData[playerid][pSlotItem][7] == 0) {
	        PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][36], 1649);
			PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][36], ItemsInfo[0][POSTDx], ItemsInfo[0][POSTDy], ItemsInfo[0][POSTDz], ItemsInfo[0][POSTDc]);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][36], 0xFFFFFFFF);
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][36], 0x333333FF);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][36]);
			return true;
		}

	    new OG = AksSlot[playerid][7];
		PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][36], playerData[playerid][pSlotItem][7]);
		PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][36], ItemsInfo[OG][POSTDx], ItemsInfo[OG][POSTDy], ItemsInfo[OG][POSTDz], ItemsInfo[OG][POSTDc]);
  		PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][36], ItemsInfo[OG][ItemAksColor]);
  		
        if (AksDel[playerid][7] == 1) PlayerTextDrawColor(playerid, InvTextDraws[playerid][36], 0x888888FF);
  		else PlayerTextDrawColor(playerid, InvTextDraws[playerid][36], 0xFFFFFFFF);
	}

    if  (type == 6) {
	    if (playerData[playerid][pSlotItem][6] == 0) {
	        PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][32], 1649);
			PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][32], ItemsInfo[0][POSTDx], ItemsInfo[0][POSTDy], ItemsInfo[0][POSTDz], ItemsInfo[0][POSTDc]);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][32], 0xFFFFFFFF);
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][32], 0x333333FF);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][32]);
			return true;
		}

	    new OG = AksSlot[playerid][6];
		PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][32], playerData[playerid][pSlotItem][6]);
		PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][32], ItemsInfo[OG][POSTDx], ItemsInfo[OG][POSTDy], ItemsInfo[OG][POSTDz], ItemsInfo[OG][POSTDc]);
  		PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][32], ItemsInfo[OG][ItemAksColor]);
  		
        if (AksDel[playerid][6] == 1) PlayerTextDrawColor(playerid, InvTextDraws[playerid][32], 0x888888FF);
  		else PlayerTextDrawColor(playerid, InvTextDraws[playerid][32], 0xFFFFFFFF);
	}

	if (type == 5) {
	    if (playerData[playerid][pSlotItem][5] == 0) {
	        PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][34], 1649);
			PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][34], ItemsInfo[0][POSTDx], ItemsInfo[0][POSTDy], ItemsInfo[0][POSTDz], ItemsInfo[0][POSTDc]);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][34], 0xFFFFFFFF);
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][34], 0x333333FF);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][34]);
			return true;
		}

	    new OG = AksSlot[playerid][5];
		PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][34], playerData[playerid][pSlotItem][5]);
		PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][34], ItemsInfo[OG][POSTDx], ItemsInfo[OG][POSTDy], ItemsInfo[OG][POSTDz], ItemsInfo[OG][POSTDc]);
  		PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][34], ItemsInfo[OG][ItemAksColor]);
  		
        if (AksDel[playerid][5] == 1) PlayerTextDrawColor(playerid, InvTextDraws[playerid][34], 0x888888FF);
  		else PlayerTextDrawColor(playerid, InvTextDraws[playerid][34], 0xFFFFFFFF);
	}

	if (type == 1) {
	    if (playerData[playerid][pSlotItem][1] == 0) {
	        PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][42], 1649);
			PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][42], ItemsInfo[0][POSTDx], ItemsInfo[0][POSTDy], ItemsInfo[0][POSTDz], ItemsInfo[0][POSTDc]);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][42], 0xFFFFFFFF);
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][42], 0x333333FF);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][42]);
			return true;
		}

	    new OG = AksSlot[playerid][1];
		PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][42], playerData[playerid][pSlotItem][1]);
		PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][42], ItemsInfo[OG][POSTDx], ItemsInfo[OG][POSTDy], ItemsInfo[OG][POSTDz], ItemsInfo[OG][POSTDc]);
  		PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][42], ItemsInfo[OG][ItemAksColor]);
  		
        if (AksDel[playerid][1] == 1) PlayerTextDrawColor(playerid, InvTextDraws[playerid][42], 0x888888FF);
  		else PlayerTextDrawColor(playerid, InvTextDraws[playerid][42], 0xFFFFFFFF);
	}

	if (type == 2) {
	    if (playerData[playerid][pSlotItem][2] == 0) {
	        PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][44], 1649);
			PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][44], ItemsInfo[0][POSTDx], ItemsInfo[0][POSTDy], ItemsInfo[0][POSTDz], ItemsInfo[0][POSTDc]);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][44], 0xFFFFFFFF);
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][44], 0x333333FF);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][44]);
			return true;
		}

	    new OG = AksSlot[playerid][2];
		PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][44], playerData[playerid][pSlotItem][2]);
		PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][44], ItemsInfo[OG][POSTDx], ItemsInfo[OG][POSTDy], ItemsInfo[OG][POSTDz], ItemsInfo[OG][POSTDc]);
  		PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][44], ItemsInfo[OG][ItemAksColor]);
  		
        if (AksDel[playerid][2] == 1) PlayerTextDrawColor(playerid, InvTextDraws[playerid][44], 0x888888FF);
  		else PlayerTextDrawColor(playerid, InvTextDraws[playerid][44], 0xFFFFFFFF);
	}

	if (type == 3) {
	    if (playerData[playerid][pSlotItem][3] == 0) {
	        PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][40], 1649);
			PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][40], ItemsInfo[0][POSTDx], ItemsInfo[0][POSTDy], ItemsInfo[0][POSTDz], ItemsInfo[0][POSTDc]);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][40], 0xFFFFFFFF);
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][40], 0x333333FF);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][40]);
			return true;
		}

	    new OG = AksSlot[playerid][3];
		PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][40], playerData[playerid][pSlotItem][3]);
		PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][40], ItemsInfo[OG][POSTDx], ItemsInfo[OG][POSTDy], ItemsInfo[OG][POSTDz], ItemsInfo[OG][POSTDc]);
  		PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][40], ItemsInfo[OG][ItemAksColor]);
  		
        if (AksDel[playerid][3] == 1) PlayerTextDrawColor(playerid, InvTextDraws[playerid][40], 0x888888FF);
  		else PlayerTextDrawColor(playerid, InvTextDraws[playerid][40], 0xFFFFFFFF);
	}

	if (type == 4) {
	    if (playerData[playerid][pSlotItem][4] == 0) {
	        PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][30], 1649);
			PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][30], ItemsInfo[0][POSTDx], ItemsInfo[0][POSTDy], ItemsInfo[0][POSTDz], ItemsInfo[0][POSTDc]);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][30], 0xFFFFFFFF);
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][30], 0x333333FF);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][30]);
			return true;
		}

	    new OG = AksSlot[playerid][4];
		PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][30], playerData[playerid][pSlotItem][4]);
		PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][30], ItemsInfo[OG][POSTDx], ItemsInfo[OG][POSTDy], ItemsInfo[OG][POSTDz], ItemsInfo[OG][POSTDc]);
  		PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][30], ItemsInfo[OG][ItemAksColor]);
  		
        if (playerData[playerid][pMoney] < 5000000) PlayerTextDrawColor(playerid, InvTextDraws[playerid][30], 0x888888FF);
  		else PlayerTextDrawColor(playerid, InvTextDraws[playerid][30], 0xFFFFFFFF);
	}

	if (type == 0) {
	    if (playerData[playerid][pSlotItem][0] == 0) {
	        PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][38], 1649);
			PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][38], ItemsInfo[0][POSTDx], ItemsInfo[0][POSTDy], ItemsInfo[0][POSTDz], ItemsInfo[0][POSTDc]);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][38], 0xFFFFFFFF);
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][38], 0x333333FF);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][38]);
			return true;
		}

	    new OG = AksSlot[playerid][0];
		PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][38], playerData[playerid][pSlotItem][0]);
		PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][38], ItemsInfo[OG][POSTDx], ItemsInfo[OG][POSTDy], ItemsInfo[OG][POSTDz], ItemsInfo[OG][POSTDc]);
  		PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][38], ItemsInfo[OG][ItemAksColor]);
  		
        if (AksDel[playerid][0] == 1) PlayerTextDrawColor(playerid, InvTextDraws[playerid][38], 0x888888FF);
  		else PlayerTextDrawColor(playerid, InvTextDraws[playerid][38], 0xFFFFFFFF);
	}

	if (type == 5) PlayerTextDrawShow(playerid, InvTextDraws[playerid][34]);
	if (type == 1) PlayerTextDrawShow(playerid, InvTextDraws[playerid][42]);
	if (type == 2) PlayerTextDrawShow(playerid, InvTextDraws[playerid][44]);
	if (type == 3) PlayerTextDrawShow(playerid, InvTextDraws[playerid][40]);
	if (type == 4) PlayerTextDrawShow(playerid, InvTextDraws[playerid][30]);
	if (type == 0) PlayerTextDrawShow(playerid, InvTextDraws[playerid][38]);
	if (type == 6) PlayerTextDrawShow(playerid, InvTextDraws[playerid][32]);
	if (type == 7) PlayerTextDrawShow(playerid, InvTextDraws[playerid][36]);
	return true;
}

stock DauningStreet2(playerid) {
    #include <textdraws\inventory2>
	return true;
}

stock bool:ShowInventory(playerid) {
    DestroyPlayerUI(playerid);

    DestroyPlayerTD(playerid, kletka[playerid][0]);
    DestroyPlayerTD(playerid, kletka[playerid][1]);

    for (new i = 0; i < 63; i++) {
        DestroyPlayerTD(playerid, InvTextDraws[playerid][i]);
    }

    for (new i = 0; i < 72; i++) {
        DestroyPlayerTD(playerid,Govnishe[playerid][i]);
    }

    for (new i = 0; i < 72; i++) {
        DestroyPlayerTD(playerid,GovnisheKletki[playerid][i]);
    }

    for (new i = 0; i < 4; i++) {
        DestroyPlayerTD(playerid, TDinvTrash[playerid][i]);
    }

    for (new i = 0; i < 6; i++) {
        DestroyPlayerTD(playerid, InfoItems[playerid][i]);
    }

    for (new i = 0; i < 6; i++) {
        DestroyPlayerTD(playerid, fstd_p[playerid][i]);
    }

    DauningStreet2(playerid);
    for (new i = 0; i < 72; i++) {
        PlayerTextDrawSetSelectable(playerid, Govnishe[playerid][i], 1);
    }

    for (new a = 0; a < 72; a++) {
        if (playerData[playerid][pDopInv][a] == 1) {
            PlayerTextDrawSetSelectable(playerid, Govnishe[playerid][a], 0);
            PlayerTextDrawColor(playerid, Govnishe[playerid][a], 0x777777FF);
        }
    }

    SetPVarInt(playerid, "isInventory", 1);
    SetPlayerChatBubble(playerid, "กำลังเปิดกระเป๋า", COLOR_PURPLE, 10.0, 1500);
    new string[128];
    new Float:health;
    new skin = GetPlayerSkin(playerid);
    PlayerTextDrawSetString(playerid, kletka[playerid][0], "~<~");
    format(string,sizeof(string),"ID:%d",skin),
    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][45], string);
    GetPlayerHealth(playerid,health);
    format(string,sizeof(string),"HP: %.0f",health),
    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][13], string);
    new Float:armour;
    GetPlayerArmour(playerid,armour);
    format(string,sizeof(string),"ARM: %.0f",armour),
    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][14], string);
    PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][47], GetPlayerSkin(playerid));
    PlayerTextDrawColor(playerid, InvTextDraws[playerid][8], 0x333333FF);
    PlayerTextDrawColor(playerid, InvTextDraws[playerid][9], playerData[playerid][pColorInv]);
    new carid = GetPlayerVehicleID(playerid);
    if (IsPlayerInVehicle(playerid, carid)) {
        AksDel[playerid][5] = 1;
        RemovePlayerAttachedObject(playerid, 5);
    }

    if (playerData[playerid][pSlotItem][6] != 0) CheckInvs(playerid, 6);
    if (playerData[playerid][pSlotItem][5] != 0) CheckInvs(playerid, 5);
    if (playerData[playerid][pSlotItem][1] != 0) CheckInvs(playerid, 1);
    if (playerData[playerid][pSlotItem][2] != 0) CheckInvs(playerid, 2);
    if (playerData[playerid][pSlotItem][3] != 0) CheckInvs(playerid, 3);
    if (playerData[playerid][pSlotItem][4] != 0) CheckInvs(playerid, 4);
    if (playerData[playerid][pSlotItem][0] != 0) CheckInvs(playerid, 0);
    if (playerData[playerid][pSlotItem][7] != 0) CheckInvs(playerid, 7);

    for (new i = 0; i < 72; i++) {
        if (playerData[playerid][pInventoryKolvo][i] < 1) {
            playerData[playerid][pInventoryKolvo][i] = 0;
            playerData[playerid][pInventory][i] = 0;
        }
    }
    
    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][27], "MENU");
    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][25], "SETTINGS");
    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][23], "CARS");
    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][21], "BUSINESS");
    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][19], "DONATE");
    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][16], "FAMILY");
    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][11], "INVENTORY");
    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][55], "HELP");
    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][53], "REPORT");
    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][6],  "CLOSE");
    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][62], "QUEST");
    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][60], "REWARDS");

    InvUpdateToColor(playerid);
    if (GetPlayerSkin(playerid) == DEFAULT_PLAYER_SKIN_MALE || GetPlayerSkin(playerid) == DEFAULT_PLAYER_SKIN_FEMALE) {
        PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], 0);
        PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][46], 1649);
        PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][46], 0.000000, 0.000000, 90.000000, 2.000000);
        PlayerTextDrawSetString(playerid, InvTextDraws[playerid][45], "");
    } else {
        PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], 1);
	}
    new str[28];
    for (new j = 0; j < 36; j++) {
        new ID = playerData[playerid][pInventory][j];
        PlayerTextDrawSetPreviewModel(playerid, Govnishe[playerid][j], ItemsInfo[ID][ItemModel]);
        PlayerTextDrawSetPreviewRot(playerid, Govnishe[playerid][j], ItemsInfo[ID][POSTDx], ItemsInfo[ID][POSTDy], ItemsInfo[ID][POSTDz], ItemsInfo[ID][POSTDc]);
        PlayerTextDrawBackgroundColor(playerid, Govnishe[playerid][j], ItemsInfo[ID][ItemColor]);
        format(string,sizeof(string), "%d",playerData[playerid][pInventoryKolvo][j]),
        PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
    }
    for (new j = 0; j < 36; j++) {
        if (playerData[playerid][pInventoryKolvo][j] == 0 || playerData[playerid][pInventoryKolvo][j] == 1) {
            format(string,sizeof(string), ""),
            PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
        }
        if (playerData[playerid][pInventory][j] == 313) {
            if (playerData[playerid][pChestTime] < 60) {
                format(string,sizeof(string),"%d SEC", playerData[playerid][pChestTime]);
                PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
            }
            if (playerData[playerid][pChestTime] == 0) {
                PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], "");
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
        // Optimized: Directly use the item ID instead of looping through 1-311
        new itemID = playerData[playerid][pInventory][j];
        if (itemID >= 1 && itemID <= 311 && itemID != 313 && itemID < 590) {
            format(str, sizeof(str), "ID:%d", itemID);
            PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], str);
            PlayerTextDrawColor(playerid, GovnisheKletki[playerid][j], 0xFFFFFFFF);
        }
    }

    PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][46], 0x333333FF);
    PlayerTextDrawLetterSize(playerid, kletka[playerid][0], 0.134524, 0.754709);
    PlayerTextDrawShow(playerid, kletka[playerid][0]);
    PlayerTextDrawShow(playerid, kletka[playerid][1]);
    for (new i = 0; i < 63; i++) {
        PlayerTextDrawShow(playerid, InvTextDraws[playerid][i]);
    }
    for (new i = 0; i < 36; i++) {
        PlayerTextDrawShow(playerid, Govnishe[playerid][i]);
    }
    for (new i = 0; i < 36; i++) {
        PlayerTextDrawShow(playerid, GovnisheKletki[playerid][i]);
    }
    for (new i = 2; i < 4; i++) {
        PlayerTextDrawShow(playerid, TDinvTrash[playerid][i]);
    }
    SelectTextDraw(playerid, playerData[playerid][pColorInv]-50);
    PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][40], 0x333333FF);
	return true;
}

stock HideInventory(playerid) {
    for (new i = 0; i < 2; i++) {
        DestroyPlayerTD(playerid, kletka[playerid][i]);
    }
    for (new i = 0; i < 63; i++) {
        DestroyPlayerTD(playerid, InvTextDraws[playerid][i]);
    }
    for (new i = 0; i < 72; i++) {
        DestroyPlayerTD(playerid, Govnishe[playerid][i]);
    }
    for (new i = 0; i < 72; i++) {
        DestroyPlayerTD(playerid, GovnisheKletki[playerid][i]);
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
    for (new i = 0; i < 7; i++) {
        DestroyPlayerTD(playerid, TDinv[playerid][i]);
    }
    for (new i = 0; i < 4; i++) {
        DestroyPlayerTD(playerid, TDinvTrash[playerid][i]);
    }
    if (playerData[playerid][pTypeSpeed] == 1) {
        for (new i = 0; i < 7; i++) DestroyPlayerTD(playerid, speeddraw[playerid][i]);
    }
    playerData[playerid][pSecondpage] = 0;
	SetPVarInt(playerid, "isInventory", 0);
    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][48], "~<~");
    CancelSelectTextDraw(playerid);
    ShowPlayerUI(playerid);
    return true;
}

stock bool:DelayedRefreshInv(playerid) {
	HideInventory(playerid);
	SetTimerEx("DelayedRefreshInv2", 100, false, "i", playerid);
	return true;
}

stock DestroyPlayerTD(playerid, &PlayerText:td) {
	if (td != PlayerText:-1) {
		PlayerTextDrawDestroy(playerid, td);
		td = PlayerText:-1;
	}
	return true;
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

public DelayedRefreshInv2(playerid) {
	ShowInventory(playerid);
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

hook OnPlayerLoaded(playerid) {
    // ShowInventory(playerid);
    // HideInventory(playerid);
    return 1;
}

hook OnGameModeInit() {
    SetTimer("GrandTimer", 1000, true);
	return 1;
}

hook OnPlayerConnect(playerid) {
    playerData[playerid][pInvColors] = 0;
    playerData[playerid][pInventori] = 0;

    ShkafOpen[playerid] = 0;
    TradeDone[playerid] = -1;
    TradeDone2[playerid] = 0;
    AksVid[playerid] = 0;
    AksVid2[playerid] = 0;
    timeskin[playerid] = 0;
    timeaks[playerid] = 0;
    PickInventTrash[playerid] = 31;
    BagazhnikOpen[playerid] = 0;
    AndruxaTop[playerid] = 0;

    for (new i = 0; i < 10; i++) {
		TradeItem[playerid][i] = 0;
		TradeItemKolvo[playerid][i] = 0;
	}
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if (newkeys & PRESS_Y) {
        if (playerData[playerid][pInventori] > 0) return 1;
        if (playerData[playerid][pInventori2] == 1) return 1;

        ShowInventory(playerid);
    }

    if (PRESSED(PRESS_SHIFT) && playerData[playerid][pInventori] > 0) {
		SetPVarInt(playerid, "SpeedInv", 1);
	} else if (RELEASED(PRESS_SHIFT) && playerData[playerid][pInventori] > 0) {
		SetPVarInt(playerid, "SpeedInv", 0);
	}
    return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid) {
	if (GetPVarInt(playerid, "isInventory") == 1) {
		for (new i = 1; i <= 3; i++) {
			if (playerData[playerid][pInventori] == i) return 1;
		}
		if (clickedid == Text:INVALID_TEXT_DRAW) {
			HideInventory(playerid);
			return 1;
		}
	}
    return 0;
}
