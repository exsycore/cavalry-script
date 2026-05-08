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

stock InventorySize(playerid, id, Float:speed) {
	new Float:X, Float:Y, string[500];
	if (GetPVarInt(playerid, "SpeedInv") == 1) speed += 0.5;
	switch (id) {
		case 0: {
			if (playerData[playerid][pInvSize_X] < -5) return true;
			X = playerData[playerid][pInvSize_X] -= speed;
			format(string, sizeof(string), "UPDATE `players` SET `InvSize_X`='%.2f' WHERE `playerID`='%d'", X, playerData[playerid][pID]);
			mysql_tquery(get_handle(), string);
			HideInventory(playerid);
			ShowInventory(playerid);
			CancelSelectTextDraw(playerid);
			format(string,sizeof(string),"~w~SIZE: ~y~%.2f, %.2f", playerData[playerid][pInvSize_X], playerData[playerid][pInvSize_Y]);
			GameTextForPlayer(playerid,string,500,4);
			TogglePlayerControllable(playerid, false);
			InvPosTime[playerid] += 0.1;
		}
		case 1: {
			if (playerData[playerid][pInvSize_X] > 5) return true;
			X = playerData[playerid][pInvSize_X] += speed;
			format(string, sizeof(string), "UPDATE `players` SET `InvSize_X`='%.2f' WHERE `playerID`='%d'", X, playerData[playerid][pID]);
			mysql_tquery(get_handle(), string);
			HideInventory(playerid);
			ShowInventory(playerid);
			CancelSelectTextDraw(playerid);
			format(string,sizeof(string),"~w~SIZE: ~y~%.2f, %.2f", playerData[playerid][pInvSize_X], playerData[playerid][pInvSize_Y]);
			GameTextForPlayer(playerid,string,500,4);
			TogglePlayerControllable(playerid, false);
			InvPosTime[playerid] += 0.1;
		}
		case 2: {
			if (playerData[playerid][pInvSize_Y] < -5) return true;
			Y = playerData[playerid][pInvSize_Y] -= speed;
			format(string, sizeof(string), "UPDATE `players` SET `InvSize_Y`='%.2f' WHERE `playerID`='%d'", Y, playerData[playerid][pID]);
			mysql_tquery(get_handle(), string);
			HideInventory(playerid);
			ShowInventory(playerid);
			CancelSelectTextDraw(playerid);
			format(string,sizeof(string),"~w~SIZE: ~y~%.2f, %.2f", playerData[playerid][pInvSize_X], playerData[playerid][pInvSize_Y]);
			GameTextForPlayer(playerid,string,500,4);
            TogglePlayerControllable(playerid, false);
            InvPosTime[playerid] += 0.1;
		}
		case 3: {
			if (playerData[playerid][pInvSize_Y] > 5) return true;
			Y = playerData[playerid][pInvSize_Y] += speed;
			format(string, sizeof(string), "UPDATE `players` SET `InvSize_Y`='%.2f' WHERE `playerID`='%d'", Y, playerData[playerid][pID]);
			mysql_tquery(get_handle(), string);
			HideInventory(playerid);
			ShowInventory(playerid);
			CancelSelectTextDraw(playerid);
			format(string,sizeof(string),"~w~SIZE: ~y~%.2f, %.2f", playerData[playerid][pInvSize_X], playerData[playerid][pInvSize_Y]);
			GameTextForPlayer(playerid,string,500,4);
			TogglePlayerControllable(playerid, false);
            InvPosTime[playerid] += 0.1;
		}
	}
	return 1;
}

stock ShowInvChangeSize(playerid) {
	inline Response(response, listitem, string:inputtext[]) {
		#pragma unused listitem, inputtext
		if (!response) TogglePlayerControllable(playerid, false);
		else TogglePlayerControllable(playerid, false);
	}
	Dialog_ShowCallback(playerid, using inline Response, 0
		, "ตัวแก้ไขขนาด"
		, "{FFFFFF}คุณได้เปิดใช้งานตัวแก้ไขขนาดสินค้าคงคลังแล้ว!\n{FFFFFF}หากต้องการเปลี่ยนขนาด ให้ใช้ลูกศรบน {B09403}NUMPAD หรือลูกศรธรรมดา{FFFFFF}\nหากต้องการบันทึกการเปลี่ยนแปลง ให้คลิก '{B09403}F{FFFFFF}' หรือ '{B09403}ENTER{FFFFFF}'"
		, "ยอมรับ"
		, ""
	);
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

public GrandTimer() {
	foreach (new i : Player) {
		if (!IsPlayerNPC(i)) {
            if (IsPlayerConnected(i) && playerData[i][IsLoggedIn]) {
                if (InvPosTime[i] > 1) { InvPosTime[i] = 0; }
            }
        }
	}
    return true;
}

hook OnPlayerUpdate(playerid) {
    if (!IsPlayerNPC(playerid)) {
        if (IsPlayerConnected(playerid) && playerData[playerid][IsLoggedIn]) {
            new keys, lr, ud;
			GetPlayerKeys(playerid, keys, ud, lr);
            if (lr == KEY_LEFT && InvPosTime[playerid] < 1) {
                if (playerData[playerid][pInventori] == 3) return InventorySize(playerid, 0, 0.5);
            }

            if (lr == KEY_RIGHT && InvPosTime[playerid] < 1) {
                if (playerData[playerid][pInventori] == 3) return InventorySize(playerid, 1, 0.5);
            }

            if (ud == KEY_UP && InvPosTime[playerid] < 1)
			{
		 		if(playerData[playerid][pInventori] == 3) return InventorySize(playerid, 2, 0.5);
			}

			if (ud == KEY_DOWN && InvPosTime[playerid] < 1)
			{
		 		if(playerData[playerid][pInventori] == 3) return InventorySize(playerid, 3, 0.5);
			}
        }
    }
    return 1;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid) {
    if (playertextid == InvTextDraws[playerid][5]) {
 		PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
		ShowInvChangeSize(playerid);

		PlayerTextDrawColor(playerid, InvTextDraws[playerid][5], playerData[playerid][pColorInv]);
		PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][5], playerData[playerid][pColorInv]);
		PlayerTextDrawHide(playerid, InvTextDraws[playerid][5]);
		PlayerTextDrawShow(playerid, InvTextDraws[playerid][5]);
		playerData[playerid][pInventori] = 3;
		TogglePlayerControllable(playerid, false);
		CancelSelectTextDraw(playerid);
		//SelectTextDraw(playerid, -1);
	}
    return 0;
}
