#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid) {
	if (playertextid == InvTextDraws[playerid][7]) {
        HideInventory(playerid);
        return 1;
    }
	if (playertextid == InvTextDraws[playerid][26]) { /// Settings Button
        PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
		SendClientMessage(playerid, COLOR_LBLUE, "Settings Button");
        HideInventory(playerid);
		return 1;
	}
	if (playertextid == InvTextDraws[playerid][28]) { /// Menu Button
        PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
		SendClientMessage(playerid, COLOR_LBLUE, "Menu Button");
        HideInventory(playerid);
		return 1;
	}
	if (playertextid == InvTextDraws[playerid][24]) { /// Cars Button
        PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
		SendClientMessage(playerid, COLOR_LBLUE, "Cars Button");
        HideInventory(playerid);
		return 1;
	}
	if (playertextid == InvTextDraws[playerid][22]) { /// Bussiness Button
        PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
		SendClientMessage(playerid, COLOR_LBLUE, "Bussiness Button");
        HideInventory(playerid);
		return 1;
	}
	if (playertextid == InvTextDraws[playerid][20]) { /// Donate Button
        PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
		SendClientMessage(playerid, COLOR_LBLUE, "Donate Button");
  		HideInventory(playerid);
		return 1;
	}
	if (playertextid == InvTextDraws[playerid][17]) { /// Family Button
		if (GetPlayerGang(playerid) != -1) {
			if (playerData[playerid][pGangRank] >= 4) {
				Command_ReProcess(playerid, "/gangpanel", 0);
			} else Command_ReProcess(playerid, "/gangmenu", 0);
			PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
			HideInventory(playerid);
		}
		else return SendErrorMessage(playerid, "{FFFFFF}คุณยังไม่ได้เข้าร่วมกลุ่มใดๆ");
		return 1;
	}
	if (playertextid == InvTextDraws[playerid][54]) { /// Report Button
		SendClientMessage(playerid, COLOR_LBLUE, "Report Button");
		HideInventory(playerid);
		return 1;
	}
    if (playertextid == InvTextDraws[playerid][52]) { /// GPS Button
		GPSDialogCategory(playerid);
		HideInventory(playerid);
		return 1;
	}
	if (playertextid == InvTextDraws[playerid][56]) { /// Help Button
		SendClientMessage(playerid, COLOR_LBLUE, "Help Button");
		HideInventory(playerid);
		return 1;
	}
	if (playertextid == TDinvTrash[playerid][2]) { /// Reward Button
		SendClientMessage(playerid, COLOR_LBLUE, "Reward Button");
		HideInventory(playerid);
		return 1;
	}
	if (playertextid == TDinvTrash[playerid][3]) { /// Quest Button
		SendClientMessage(playerid, COLOR_LBLUE, "Quest Button");
		HideInventory(playerid);
		return 1;
	}
	return 0;
}
