#if defined _inc_impl
    #undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
	mysql_tquery(get_handle(), "SELECT * FROM `pawn`", "PawnLoad", "");
	return true;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if (PRESSED(KEY_NO)) {
		if (!IsPlayerInAnyVehicle(playerid)) {
			if (PawnNearest(playerid) != -1) {
				ShowDialogPawnVehicle(playerid);
			}
		}
	}
	return true;
}

public PawnLoad() {
	new
	    rows;

	cache_get_row_count(rows);

	for (new i = 0; i < rows; i ++) if (i < MAX_PAWNCAR) {
	    Player.Pawn[i][@exists] = true;

	    cache_get_value_name_int(i, "pawnid", Player.Pawn[i][@id]);
	    cache_get_value_name_float(i, "pawnx", Player.Pawn[i][@pawnx]);
	    cache_get_value_name_float(i, "pawny", Player.Pawn[i][@pawny]);
	    cache_get_value_name_float(i, "pawnz", Player.Pawn[i][@pawnz]);

	    PawnRefresh(i);
	}
	printf("[SYSTEM][DB] %i Pawn loaded.", rows);
	return true;
}

public OnPawnCreated(pawnid) {
	if (pawnid == -1 || !Player.Pawn[pawnid][@exists]) return false;

	Player.Pawn[pawnid][@id] = cache_insert_id();
	PawnSave(pawnid);
	return true;
}

stock PawnNearest(playerid) {
    for (new i = 0; i != MAX_PAWNCAR; i ++) if (Player.Pawn[i][@exists] && IsPlayerInRangeOfPoint(playerid, 4.0, Player.Pawn[i][@pawnx], Player.Pawn[i][@pawny], Player.Pawn[i][@pawnz])) {
		return i;
	}
	return -1;
}

stock PawnDelete(pawnid) {
	if (pawnid != -1 && Player.Pawn[pawnid][@exists]) {
	    new
	        string[64];

        if (IsValidDynamicPickup(Player.Pawn[pawnid][@pawnpickup]))
		    DestroyDynamicPickup(Player.Pawn[pawnid][@pawnpickup]);

		if (IsValidDynamic3DTextLabel(Player.Pawn[pawnid][@pawntext3d]))
		    DestroyDynamic3DTextLabel(Player.Pawn[pawnid][@pawntext3d]);
		
		if (IsValidDynamicMapIcon(Player.Pawn[pawnid][@pawnicon]))
		    DestroyDynamicMapIcon(Player.Pawn[pawnid][@pawnicon]);

		mysql_format(get_handle(), string, sizeof string, "DELETE FROM `pawn` WHERE `pawnid` = '%d'", Player.Pawn[pawnid][@id]);
		mysql_tquery(get_handle(), string);

		Player.Pawn[pawnid][@exists] = false;
		Player.Pawn[pawnid][@id] = 0;
	}
	return true;
}

stock PawnCreate(Float:x, Float:y, Float:z) {
	for (new i = 0; i < MAX_PAWNCAR; i ++) if (!Player.Pawn[i][@exists]) {
	    Player.Pawn[i][@exists] = true;
	    Player.Pawn[i][@pawnx] = x;
	    Player.Pawn[i][@pawny] = y;
	    Player.Pawn[i][@pawnz] = z;

	    mysql_tquery(get_handle(), "INSERT INTO `pawn` (`pawnid`) VALUES(0)", "OnPawnCreated", "d", i);
		PawnRefresh(i);
		return i;
	}
	return -1;
}

stock PawnSave(pawnid) {
	new
	    query[220];
	mysql_format(get_handle(), query, sizeof query, "UPDATE `pawn` SET `pawnx` = '%.4f', `pawny` = '%.4f', `pawnz` = '%.4f' WHERE `pawnid` = '%d'",
	    Player.Pawn[pawnid][@pawnx],
	    Player.Pawn[pawnid][@pawny],
	    Player.Pawn[pawnid][@pawnz],
	    Player.Pawn[pawnid][@id]
	);
	return mysql_tquery(get_handle(), query);
}

stock PawnRefresh(pawnid) {
	if (pawnid != -1 && Player.Pawn[pawnid][@exists]) {
		if (IsValidDynamicPickup(Player.Pawn[pawnid][@pawnpickup]))
		    DestroyDynamicPickup(Player.Pawn[pawnid][@pawnpickup]);

		if (IsValidDynamic3DTextLabel(Player.Pawn[pawnid][@pawntext3d]))
		    DestroyDynamic3DTextLabel(Player.Pawn[pawnid][@pawntext3d]);

		if (IsValidDynamicMapIcon(Player.Pawn[pawnid][@pawnicon]))
		    DestroyDynamicMapIcon(Player.Pawn[pawnid][@pawnicon]);

		Player.Pawn[pawnid][@pawnpickup] = CreateDynamicPickup(MODEL_PAWN, 23, Player.Pawn[pawnid][@pawnx], Player.Pawn[pawnid][@pawny], Player.Pawn[pawnid][@pawnz]);
  		Player.Pawn[pawnid][@pawntext3d] = CreateDynamic3DTextLabel(TEXT3D_PAWN, -1, Player.Pawn[pawnid][@pawnx], Player.Pawn[pawnid][@pawny], Player.Pawn[pawnid][@pawnz], 5.0, INVALID_VEHICLE_ID, INVALID_PLAYER_ID, 0);
		Player.Pawn[pawnid][@pawnicon] = CreateDynamicMapIcon(Player.Pawn[pawnid][@pawnx], Player.Pawn[pawnid][@pawny], Player.Pawn[pawnid][@pawnz], 48, 0);
	}
	return true;
}

stock PanelCreatePawn(playerid) {
	if (!IsPlayerAdminEx(playerid)) return true;
	if (GetPlayerInterior(playerid) != 0) return true;

	inline const CreatePawn(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused dialogid, inputtext, pid

		if (!response) @return true;

		switch (listitem) {
			case 0 : {
				new
					Float:x,
					Float:y,
					Float:z;

				GetPlayerPos(playerid, x, y, z);

				new id = PawnCreate(x, y, z);

				if (id == -1) {
					SendErrorMessage(playerid, "ความจุของ 'จุดพาวน์รถ' ในฐานข้อมูลเต็มแล้ว (ติดต่อผู้พัฒนา)");
					@return 1;
				}

				SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ได้สร้าง 'จุดพาวน์รถ' ขึ้นมาใหม่แล้ว ID: %d", ReturnPlayerName(playerid), id);
			}
			case 1 : {
				PawnDeleteDialog(playerid);
			}
			case 2 : {
				PawnIDList(playerid);
			}
		}
	}
	Dialog_ShowCallback(playerid, using inline CreatePawn, DIALOG_STYLE_LIST, "{FFFFFF}จุดพาวน์รถ", "สร้าง\nลบ\nไอดีที่มีอยู่", "เลือก", "ยกเลิก");
	return true;
}

stock PawnDeleteDialog(playerid) {
	inline const DeletePickcar(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused dialogid, listitem, pid

		if (!response) @return true;

		new id = 0;
		
		if (sscanf(inputtext, "d", id)) {
			SendErrorMessage(playerid, "ต้องป้อนรูปแบบเลขเท่านั้น");
			@return PanelCreatePawn(playerid);
		}
		
		if ((id < 0 || id >= MAX_PAWNCAR) || !Player.Pawn[id][@exists]) {
			SendErrorMessage(playerid, "ไม่มีไอดีที่เก็บรถนี้อยู่ในฐานข้อมูล");
			@return PanelCreatePawn(playerid);
		}

		PawnDelete(id);
		SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ได้ลบ 'จุดพาวน์รถ' ID: %d", ReturnPlayerName(playerid), id);
	}
	Dialog_ShowCallback(playerid, using inline DeletePickcar, DIALOG_STYLE_INPUT, "{FFFFFF}ลบจุดพาวน์รถ", "ป้อน ID Pickcar นั้น", "ลบ", "ยกเลิก");
	return true;
}

stock PawnIDList(playerid) {
	new count = 0;
	new string[1660], string2[1660] = "";

	for (new i = 0; i < MAX_PAWNCAR; i ++) if (Player.Pawn[i][@exists]) {
		format(string, sizeof(string), "{FFFFFF}[%d].\t{FFFFFF}-\t{FFFFFF}ID: %d\n", count, Player.Pawn[i][@id]);
		strcat(string2, string);

		count ++;
	}

	if (!count) return SendErrorMessage(playerid, "เซิร์ฟเวอร์ยังไม่ได้เพิ่ม 'จุดพาวน์รถ'");

	inline const Loaded(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused pid, dialogid, inputtext, listitem

		if (!response) @return true;

		if (response) @return true;
	}
	format(string, sizeof(string), "Index\t-\tID\n%s", string2);
	Dialog_ShowCallback(playerid, using inline Loaded, DIALOG_STYLE_TABLIST_HEADERS, "PawnIDList", string, "ปิด", "");
	return true;
}

stock ShowDialogPawnVehicle(playerid) {
	new query[1024 + MAX_PLAYER_NAME + 1];
	new vehicleList[1024];
	new string2[1024] = "";
	new count = 0;

	for (new i = 1; i < MAX_VEHICLES; i ++) {
		if ((IsValidVehicle(i)) && (IsVehicleOwner(playerid, i)) && (Player.Vehicle[playerid][i][@spawned] == true)) {
			format(vehicleList, sizeof vehicleList, "{FFFFFF}ทะเบียน: %s\t{FFFFFF} | เจ้าของ: %s |\t{FFFFFF} หมายเลขรถ: %d\n", Player.Vehicle[playerid][i][@plate], Player.Vehicle[playerid][i][@owner], Player.Vehicle[playerid][i][@modelid]);
			strcat(string2, vehicleList);
			count ++;
		}
	}

	if (!count) return SendErrorMessage(playerid, "คุณไม่มีรถที่ต้องพาวน์");

	inline const Loaded(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused dialogid, inputtext, pid

		if (!response) @return true;
		
		format(query, sizeof(query), "SELECT * FROM "VEHICLE_TABLE" WHERE ownerid = '%d' LIMIT %d, 1", playerData[playerid][pID], listitem);
		mysql_tquery(get_handle(), query, "OnPlayerSpawnVehicle2", "ii", playerid, listitem);
	}
	format(vehicleList, sizeof vehicleList, "{FFFFFF}ทะเบียน\t{FFFFFF}เจ้าของรถ\t{FFFFFF}หมายเลขรถ\n%s", string2);
	Dialog_ShowCallback(playerid, using inline Loaded, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}รถของคุณ", vehicleList, "เลือก", "ยกเลิก");
	return true;
}

public OnPlayerSpawnVehicle2(playerid, listitem) {
	new rows_2;
	cache_get_row_count(rows_2);

	if (rows_2) {
		new count;
		for (new i = 0; i < MAX_VEHICLES; i ++) {
			if ((strcmp(Player.Vehicle[playerid][i][@owner], ReturnPlayerName(playerid)) == 0) && (Player.Vehicle[playerid][i][@spawned] == true) && (count++ == listitem)) {
				RepairVehicle(i);
				DespawnVehicleOwner(playerid, i);

				SendGarageAction(playerid, "คุณได้ทำการพาวน์รถส่วนตัวเรียบร้อยแล้ว");
				
				return true;
			}
		}
	}
	return true;
}