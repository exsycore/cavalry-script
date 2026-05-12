#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

new 
	busketHat[MAX_PLAYERS], 
	Float: busketX[MAX_PLAYERS], 
	Float: busketY[MAX_PLAYERS], 
	Float: busketZ[MAX_PLAYERS], 
	bool: busketStats[MAX_PLAYERS];

new 
	Text3D: busket3DText[MAX_PLAYERS], 
	busketMoney[MAX_PLAYERS];

stock CheckPlayerOwnerBusket(playerid) {
	new ownerbusk = -1;
    foreach (new i : Player) {
        if (IsPlayerInRangeOfPoint(playerid, 2.0, busketX[i], busketY[i], busketZ[i])) {
            return i;
        }
    }
    return ownerbusk;
}

hook OnPlayerConnect(playerid) {
	busketHat[playerid] = INVALID_OBJECT_ID;
    busketX[playerid] = 0.0;
    busketY[playerid] = 0.0;
    busketZ[playerid] = 0.0;
    busketMoney[playerid] = 0;
    busketStats[playerid] = false;
	return true;
}

hook OnPlayerDisconnect(playerid, reason) {
    if (busketStats[playerid]) {
		if (IsValidDynamic3DTextLabel(busket3DText[playerid]))
			DestroyDynamic3DTextLabel(busket3DText[playerid]);

		if (IsValidDynamicObject(busketHat[playerid]))
			DestroyDynamicObject(busketHat[playerid]);

		busketX[playerid] = 0.0;
		busketY[playerid] = 0.0;
		busketZ[playerid] = 0.0;
		busketMoney[playerid] = 0;
		busketStats[playerid] = false;
    }
	return true;
}

YCMD:busk(playerid, const params[], help) {
	if (!busketStats[playerid] && !GetPlayerLoggedIn(playerid)) {
		/*if (!Inventory_HasItem(playerid, "บัตรเปิดหมวก"))
    		return SendErrorMessage(playerid, "คุณไม่มีบัตรเปิดหมวก เลยไม่สามารถเปิดหมวกได้! [ซื้อได้ที่ร้านค้า]");*/

	    new str[128];

		busketStats[playerid] = true;

		GetPlayerPos(playerid, busketX[playerid], busketY[playerid], busketZ[playerid]);

	    busketHat[playerid] = CreateDynamicObject(19317, busketX[playerid], busketY[playerid], busketZ[playerid]-0.9, 3.66000, 90.70010, 88.98000);

        format(str, sizeof(str), "%s\n{00ff00}$0\n{ffffff}กด {00ff00}'N'{ffffff} เพื่อให้เงิน", ReturnPlayerName(playerid));
		busket3DText[playerid] = CreateDynamic3DTextLabel(str, -1, busketX[playerid], busketY[playerid], busketZ[playerid], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, -1, 10.0);
	} else return SendErrorMessage(playerid, "คุณได้วางหมวกแล้ว!");
	return true;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if (newkeys & KEY_NO && !IsPlayerInAnyVehicle(playerid)) {
		new 
			owner = CheckPlayerOwnerBusket(playerid),
			str[512];

		if (owner == -1) return true;

		if (owner == playerid) {
			if (!IsPlayerInRangeOfPoint(playerid, 2.0, busketX[playerid], busketY[playerid], busketZ[playerid]))
				return true;

			format(str, sizeof(str),
				"{ffffff}เงินในหมวก\t{1BF909}%s\n\
				{32d9e7}> {ffffff}เก็บเงิน\n\
				{F96B09}> {ffffff}เก็บหมวก",
				FormatMoney(busketMoney[playerid])
			);
			inline const BusketMain(pid, dialogid, response, listitem, string:inputtext[]) {
				#pragma unused pid, dialogid, inputtext

				if (!response) return true;

				switch (listitem) {
					case 1: { // เก็บเงิน
						if (busketMoney[playerid] <= 0) {
							inline const Msg(pids, dialogids, responses, listitems, string:inputtexts[]) {
								#pragma unused pids, dialogids, listitems, inputtexts
								if (!responses) return true;
							}
							return Dialog_ShowCallback(playerid, using inline Msg,
								DIALOG_STYLE_MSGBOX,
								"แจ้งเตือน",
								"{1BF909}[!] {ffffff}หมวกยังไม่มีเงินเลย..",
								"ตกลง", ""
							);
						}

						new msg[128];

						GivePlayerMoneyEx(playerid, busketMoney[playerid]);

						format(msg, sizeof(msg),
							"{1BF909}[!] {ffffff}คุณเก็บเงินจากหมวก : {1BF909}%s",
							FormatMoney(busketMoney[playerid])
						);

						inline const Msg2(pids, dialogids, responses, listitems, string:inputtexts[]) {
							#pragma unused pids, dialogids, listitems, inputtexts
							if (!responses) return true;
						}
						Dialog_ShowCallback(playerid, using inline Msg2,
							DIALOG_STYLE_MSGBOX,
							"แจ้งเตือน",
							msg,
							"ตกลง", ""
						);

						busketMoney[playerid] = 0;

						format(msg, sizeof(msg),
							"%s\n{00ff00}$%s\n{ffffff}กด 'N' เพื่อให้เงิน",
							ReturnPlayerName(playerid),
							FormatMoney(busketMoney[playerid])
						);

						UpdateDynamic3DTextLabelText(busket3DText[playerid], 0xFFFFFFFF, msg);
					}
					case 2: { // เก็บหมวก
						if (IsValidDynamic3DTextLabel(busket3DText[playerid]))
							DestroyDynamic3DTextLabel(busket3DText[playerid]);

						if (IsValidDynamicObject(busketHat[playerid]))
							DestroyDynamicObject(busketHat[playerid]);

						busketX[playerid] = 0.0;
						busketY[playerid] = 0.0;
						busketZ[playerid] = 0.0;
						busketMoney[playerid] = 0;
						busketStats[playerid] = false;
					}
				}
				return true;
			}
			Dialog_ShowCallback(playerid, using inline BusketMain,
				DIALOG_STYLE_TABLIST,
				"หมวกของฉัน",
				str,
				"ตกลง", "ออก"
			);
		} else {
			if (!IsPlayerInRangeOfPoint(playerid, 2.0, busketX[owner], busketY[owner], busketZ[owner]))
				return true;

			format(str, sizeof(str),
				"{ffffff}กรอกเงินที่ต้องการให้\n\
				สูงสุด {1BF909}$1,000\n\
				เงินคุณ: %s",
				FormatMoney(GetPlayerMoneyEx(playerid))
			);

			inline const GiveMoney(pid, dialogid, response, listitem, string:inputtext[]) {
				#pragma unused pid, dialogid, listitem

				if (!response) return true;

				new money = strval(inputtext);
				new target = CheckPlayerOwnerBusket(playerid);

				if (money <= 0 || money > 1000) {
					inline const Msg(pids, dialogids, responses, listitems, string:inputtexts[]) {
						#pragma unused pids, dialogids, listitems, inputtexts
						if (!responses) return true;
					}
					return Dialog_ShowCallback(playerid, using inline Msg,
						DIALOG_STYLE_MSGBOX,
						"แจ้งเตือน",
						"{1BF909}[!] {ffffff}ใส่เงิน 1 - 1000 เท่านั้น",
						"ตกลง", ""
					);
				}
				if (money > GetPlayerMoneyEx(playerid)) {
					inline const Msg2(pids, dialogids, responses, listitems, string:inputtexts[]) {
						#pragma unused pids, dialogids, listitems, inputtexts
						if (!responses) return true;
					}
					return Dialog_ShowCallback(playerid, using inline Msg2,
						DIALOG_STYLE_MSGBOX,
						"แจ้งเตือน",
						"{1BF909}[!] {ffffff}เงินคุณไม่พอ!",
						"ตกลง", ""
					);
				}

				if (target == -1) return true;

				GivePlayerMoneyEx(playerid, -money);
				busketMoney[target] += money;

				inline const Done(pids, dialogids, responses, listitems, string:inputtexts[]) {
					#pragma unused pids, dialogids, listitems, inputtexts
					if (!responses) return true;
				}
				Dialog_ShowCallback(playerid, using inline Done,
					DIALOG_STYLE_MSGBOX,
					"แจ้งเตือน",
					"{1BF909}[!] {ffffff}ให้เงินสำเร็จ!",
					"ตกลง", ""
				);

				new msg[128];
				format(msg, sizeof(msg),
					"%s\n{00ff00}$%s\n{ffffff}กด 'N' เพื่อให้เงิน",
					ReturnPlayerName(target),
					FormatMoney(busketMoney[target])
				);

				UpdateDynamic3DTextLabelText(busket3DText[target], 0xFFFFFFFF, msg);
				return true;
			}

			Dialog_ShowCallback(playerid, using inline GiveMoney,
				DIALOG_STYLE_INPUT,
				"เปิดหมวก",
				str,
				"ตกลง", "ออก"
			);
		}
	}
    return true;
}