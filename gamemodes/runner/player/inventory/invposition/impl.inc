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

stock ShowInvChangePos(playerid) {
    inline Response(response, listitem, string:inputtext[]) {
        #pragma unused listitem, inputtext
        if (!response) TogglePlayerControllable(playerid, false);
	    else TogglePlayerControllable(playerid, false);
    }
    Dialog_ShowCallback(playerid, using inline Response, 0
        , "ตำแหน่งกระเป๋า"
        , "{FFFFFF}คุณได้เปิดใช้งานโปรแกรมแก้ไขรายการสินค้าคงคลังแล้ว!\n{FFFFFF}หากต้องการเปลี่ยนตำแหน่ง ให้ใช้ลูกศรบน {B09403}NUMPAD หรือลูกศรธรรมดา{FFFFFF}\nหากต้องการบันทึกการเปลี่ยนแปลง ให้คลิก '{B09403}F{FFFFFF}' หรือ '{B09403}ENTER{FFFFFF}'"
        , "ยอมรับ"
        , ""
    );
    return 1;
}

stock InventoryPos(playerid, id, Float:speed) {
	new Float:X, Float:Y, string[500];
	if (GetPVarInt(playerid, "SpeedInv") == 1) speed += 2.5;
	switch (id) {
        case 0: {
            if (playerData[playerid][pInvPos_X] < -335) return true;
            X = playerData[playerid][pInvPos_X] -= speed;
            format(string, sizeof(string), "UPDATE `players` SET `InvPos_X`='%.2f' WHERE `playerID`='%d'", X, playerData[playerid][pID]);
            mysql_tquery(get_handle(), string);
            HideInventory(playerid);
            ShowInventory(playerid);
            CancelSelectTextDraw(playerid);
            format(string,sizeof(string),"~w~POSITION: ~y~%.2f, %.2f", playerData[playerid][pInvPos_X], playerData[playerid][pInvPos_Y]);
            GameTextForPlayer(playerid, string, 500, 4);
            TogglePlayerControllable(playerid, false);
            InvPosTime[playerid] += 0.1;
        }

        case 1: {
            if (playerData[playerid][pInvPos_X] > 12) return true;
            X = playerData[playerid][pInvPos_X] += speed;
            format(string, sizeof(string), "UPDATE `players` SET `InvPos_X`='%.2f' WHERE `playerID`='%d'", X, playerData[playerid][pID]);
            mysql_tquery(get_handle(), string);
            HideInventory(playerid);
            ShowInventory(playerid);
            CancelSelectTextDraw(playerid);
            format(string,sizeof(string),"~w~POSITION: ~y~%.2f, %.2f", playerData[playerid][pInvPos_X], playerData[playerid][pInvPos_Y]);
            GameTextForPlayer(playerid,string,500,4);
            TogglePlayerControllable(playerid, false);
            InvPosTime[playerid] += 0.1;
        }

        case 2: {
            if (playerData[playerid][pInvPos_Y] < -99) return true;
            Y = playerData[playerid][pInvPos_Y] -= speed;
            format(string, sizeof(string), "UPDATE `players` SET `InvPos_Y`='%.2f' WHERE `playerID`='%d'", Y, playerData[playerid][pID]);
            mysql_tquery(get_handle(), string);
            HideInventory(playerid);
            ShowInventory(playerid);
            CancelSelectTextDraw(playerid);
            format(string,sizeof(string),"~w~POSITION: ~y~%.2f, %.2f", playerData[playerid][pInvPos_X], playerData[playerid][pInvPos_Y]);
            GameTextForPlayer(playerid,string,500,4);
            TogglePlayerControllable(playerid, false);
            InvPosTime[playerid] += 0.1;
        }

        case 3: {
            if (playerData[playerid][pInvPos_Y] > 99) return true;
            Y = playerData[playerid][pInvPos_Y] += speed;
            format(string, sizeof(string), "UPDATE `players` SET `InvPos_Y`='%.2f' WHERE `playerID`='%d'", Y, playerData[playerid][pID]);
            mysql_tquery(get_handle(), string);
            HideInventory(playerid);
            ShowInventory(playerid);
            CancelSelectTextDraw(playerid);
            format(string,sizeof(string),"~w~POSITION: ~y~%.2f, %.2f", playerData[playerid][pInvPos_X], playerData[playerid][pInvPos_Y]);
            GameTextForPlayer(playerid,string,500,4);
            TogglePlayerControllable(playerid, false);
            InvPosTime[playerid] += 0.1;
        }
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

hook OnPlayerUpdate(playerid) {
    if (!IsPlayerNPC(playerid)) {
        if (IsPlayerConnected(playerid) && playerData[playerid][IsLoggedIn]) {
            new keys, lr, ud;
			GetPlayerKeys(playerid, keys, ud, lr);
            if (lr == KEY_LEFT && InvPosTime[playerid] < 1) {
                if (playerData[playerid][pInventori] == 2) return InventoryPos(playerid, 0, 2.5);
            }

            if (lr == KEY_RIGHT && InvPosTime[playerid] < 1) {
                if (playerData[playerid][pInventori] == 2) return InventoryPos(playerid, 1, 2.5);
            }

            if (ud == KEY_UP && InvPosTime[playerid] < 1)
			{
		 		if(playerData[playerid][pInventori] == 2) return InventoryPos(playerid, 2, 2.5);
			}

			if (ud == KEY_DOWN && InvPosTime[playerid] < 1)
			{
		 		if(playerData[playerid][pInventori] == 2) return InventoryPos(playerid, 3, 2.5);
			}
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if (newkeys & KEY_SECONDARY_ATTACK) {
		if (playerData[playerid][pInventori] == 2) {
		    TogglePlayerControllable(playerid, true);
		    playerData[playerid][pInventori] = 0;
   			PlayerTextDrawColor(playerid, InvTextDraws[playerid][3], 0x111111FF);
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][3], 0x111111FF);
			PlayerTextDrawHide(playerid, InvTextDraws[playerid][3]);
			PlayerTextDrawShow(playerid, InvTextDraws[playerid][3]);
      		SelectTextDraw(playerid, playerData[playerid][pColorInv]-50);
		}
	}
    return 1;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid) {
    if (playertextid == InvTextDraws[playerid][3]) {
 		PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
        ShowInvChangePos(playerid);

		PlayerTextDrawColor(playerid, InvTextDraws[playerid][3], playerData[playerid][pColorInv]);
		PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][3], playerData[playerid][pColorInv]);
		PlayerTextDrawHide(playerid, InvTextDraws[playerid][3]);
		PlayerTextDrawShow(playerid, InvTextDraws[playerid][3]);
		playerData[playerid][pInventori] = 2;
		TogglePlayerControllable(playerid, false);
		CancelSelectTextDraw(playerid);
	}
    return 0;
}
