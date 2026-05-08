#if defined _inc_impl
    #undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
	mysql_tquery(get_handle(), "SELECT * FROM `pickcar`", "PickcarLoad", "");
    return true;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if (PRESSED(KEY_NO)) {
		if (IsPlayerInAnyVehicle(playerid)) {
			new i = GetPlayerVehicleID(playerid);
			if (PickcarNearest(playerid) != -1) {
				if (IsValidVehicle(i) && Player.Vehicle[playerid][i][@id] > 0 && IsVehicleOwner(playerid, i)) {
					SendGarageAction(playerid, "คุณได้ทำการเก็บรถส่วนตัวรุ่น %s เรียบร้อยแล้ว", ReturnVehicleName(i));
					DespawnVehicleOwner(playerid, i);
				}
			}
		}
	}
	return true;
}

public PickcarLoad() {
	new
	    rows;

	cache_get_row_count(rows);

	for (new i = 0; i < rows; i ++) if (i < MAX_PICKCAR) {
	    Player.Pickcar[i][@exists] = true;
	    cache_get_value_name_int(i, "pickcarid", Player.Pickcar[i][@id]);
	    cache_get_value_name_float(i, "pickcarx", Player.Pickcar[i][@pickcarx]);
	    cache_get_value_name_float(i, "pickcary", Player.Pickcar[i][@pickcary]);
	    cache_get_value_name_float(i, "pickcarz", Player.Pickcar[i][@pickcarz]);
	    PickcarRefresh(i);
	}
	printf("[SYSTEM][DB] %i Pickcar loaded.", rows);
	return true;
}

public OnPickcarCreated(pickcarid) {
	if (pickcarid == -1 || !Player.Pickcar[pickcarid][@exists]) return false;

	Player.Pickcar[pickcarid][@id] = cache_insert_id();
	PickcarSave(pickcarid);
	return true;
}

stock PickcarNearest(playerid) {
    for (new i = 0; i != MAX_PICKCAR; i ++) if (Player.Pickcar[i][@exists] && IsPlayerInRangeOfPoint(playerid, 4.0, Player.Pickcar[i][@pickcarx], Player.Pickcar[i][@pickcary], Player.Pickcar[i][@pickcarz])) {
		return i;
	}
	return -1;
}

stock PickcarDelete(pickcarid) {
	if (pickcarid != -1 && Player.Pickcar[pickcarid][@exists]) {
	    new
	        string[64];

        if (IsValidDynamicPickup(Player.Pickcar[pickcarid][@pickcarobject]))
		    DestroyDynamicPickup(Player.Pickcar[pickcarid][@pickcarobject]);
		
		if (IsValidDynamicObject(Player.Pickcar[pickcarid][@pickcarobject2]))
		    DestroyDynamicObject(Player.Pickcar[pickcarid][@pickcarobject2]);

		if (IsValidDynamic3DTextLabel(Player.Pickcar[pickcarid][@pickcartext3d]))
		    DestroyDynamic3DTextLabel(Player.Pickcar[pickcarid][@pickcartext3d]);
		
		if (IsValidDynamicMapIcon(Player.Pickcar[pickcarid][@pickcaricon]))
		    DestroyDynamicMapIcon(Player.Pickcar[pickcarid][@pickcaricon]);

		mysql_format(get_handle(), string, sizeof string, "DELETE FROM `pickcar` WHERE `pickcarid` = '%d'", Player.Pickcar[pickcarid][@id]);
		mysql_tquery(get_handle(), string);

		Player.Pickcar[pickcarid][@exists] = false;
		Player.Pickcar[pickcarid][@id] = 0;
	}
	return true;
}

stock PickcarCreate(Float:x, Float:y, Float:z) {
	for (new i = 0; i < MAX_PICKCAR; i ++) if (!Player.Pickcar[i][@exists]) {
	    Player.Pickcar[i][@exists] = true;
	    Player.Pickcar[i][@pickcarx] = x;
	    Player.Pickcar[i][@pickcary] = y;
	    Player.Pickcar[i][@pickcarz] = z;

	    mysql_tquery(get_handle(), "INSERT INTO `pickcar` (`pickcarid`) VALUES(0)", "OnPickcarCreated", "d", i);
		PickcarRefresh(i);
		return i;
	}
	return -1;
}

stock PickcarSave(pickcarid) {
	new
	    query[220];
	mysql_format(get_handle(), query, sizeof query, "UPDATE `pickcar` SET `pickcarx` = '%.4f', `pickcary` = '%.4f', `pickcarz` = '%.4f' WHERE `pickcarid` = '%d'",
	    Player.Pickcar[pickcarid][@pickcarx],
	    Player.Pickcar[pickcarid][@pickcary],
	    Player.Pickcar[pickcarid][@pickcarz],
	    Player.Pickcar[pickcarid][@id]
	);
	return mysql_tquery(get_handle(), query);
}

stock PickcarRefresh(pickcarid) {
	if (pickcarid != -1 && Player.Pickcar[pickcarid][@exists]) {
		if (IsValidDynamicPickup(Player.Pickcar[pickcarid][@pickcarobject]))
		    DestroyDynamicPickup(Player.Pickcar[pickcarid][@pickcarobject]);
		
		if (IsValidDynamicObject(Player.Pickcar[pickcarid][@pickcarobject2]))
		    DestroyDynamicObject(Player.Pickcar[pickcarid][@pickcarobject2]);

		if (IsValidDynamic3DTextLabel(Player.Pickcar[pickcarid][@pickcartext3d]))
		    DestroyDynamic3DTextLabel(Player.Pickcar[pickcarid][@pickcartext3d]);

		if (IsValidDynamicMapIcon(Player.Pickcar[pickcarid][@pickcaricon]))
		    DestroyDynamicMapIcon(Player.Pickcar[pickcarid][@pickcaricon]);

		Player.Pickcar[pickcarid][@pickcarobject] = CreateDynamicPickup(MODEL_PICKCAR, 23, Player.Pickcar[pickcarid][@pickcarx], Player.Pickcar[pickcarid][@pickcary], Player.Pickcar[pickcarid][@pickcarz]);
		Player.Pickcar[pickcarid][@pickcarobject2] = CreateDynamicObject(1316, Player.Pickcar[pickcarid][@pickcarx], Player.Pickcar[pickcarid][@pickcary], Player.Pickcar[pickcarid][@pickcarz] - 0.9, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
		SetDynamicObjectMaterial(Player.Pickcar[pickcarid][@pickcarobject2], 0, -1, "none", "none", 0xFFCC0000);
  		Player.Pickcar[pickcarid][@pickcartext3d] = CreateDynamic3DTextLabel(TEXT3D_PICKCAR, -1, Player.Pickcar[pickcarid][@pickcarx], Player.Pickcar[pickcarid][@pickcary], Player.Pickcar[pickcarid][@pickcarz], 5.0, INVALID_VEHICLE_ID, INVALID_PLAYER_ID, 0);
		Player.Pickcar[pickcarid][@pickcaricon] = CreateDynamicMapIcon(Player.Pickcar[pickcarid][@pickcarx], Player.Pickcar[pickcarid][@pickcary], Player.Pickcar[pickcarid][@pickcarz], 51, 0);
	}
	return true;
}

stock PanelCreatePickcar(playerid) {
	if (!IsPlayerAdminEx(playerid)) return true;
	if (GetPlayerInterior(playerid) != 0) return true;

	inline const CreatePickcar(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused dialogid, inputtext, pid

		if (!response) @return true;

		switch (listitem) {
			case 0 : {
				new
					Float:x,
					Float:y,
					Float:z;

				GetPlayerPos(playerid, x, y, z);

				new id = PickcarCreate(x, y, z);

				if (id == -1) {
					SendErrorMessage(playerid, "ความจุของ 'Pickcar' ในฐานข้อมูลเต็มแล้ว (ติดต่อผู้พัฒนา)");
					@return 1;
				}

				SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ได้สร้าง 'Pickcar' ขึ้นมาใหม่แล้ว ID: %d", ReturnPlayerName(playerid), id);
			}
			case 1 : {
				PickcarDeleteDialog(playerid);
			}
			case 2 : {
				PickcarIDList(playerid);
			}
		}
	}
	Dialog_ShowCallback(playerid, using inline CreatePickcar, DIALOG_STYLE_LIST, "{FFFFFF}PanelPickcar", "สร้าง\nลบ\nไอดีที่มีอยู่", "เลือก", "ยกเลิก");
	
	return true;
}

stock PickcarDeleteDialog(playerid) {
	inline const DeletePickcar(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused dialogid, listitem, pid

		if (!response) @return true;

		new id = 0;
		
		if (sscanf(inputtext, "d", id)) {
			SendErrorMessage(playerid, "ต้องป้อนรูปแบบเลขเท่านั้น");
			@return PanelCreatePickcar(playerid);
		}
		
		if ((id < 0 || id >= MAX_PICKCAR) || !Player.Pickcar[id][@exists]) {
			SendErrorMessage(playerid, "ไม่มีไอดีที่เก็บรถนี้อยู่ในฐานข้อมูล");
			@return PanelCreatePickcar(playerid);
		}

		PickcarDelete(id);
		SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ได้ลบ 'Pickcar' ID: %d", ReturnPlayerName(playerid), id);
	}
	Dialog_ShowCallback(playerid, using inline DeletePickcar, DIALOG_STYLE_INPUT, "{FFFFFF}DeletePickcar", "ป้อน ID Pickcar นั้น", "ลบ", "ยกเลิก");
	return true;
}

stock PickcarIDList(playerid) {
	new count = 0;
	new string[1660], string2[1660] = "";

	for (new i = 0; i < MAX_PICKCAR; i ++) if (Player.Pickcar[i][@exists]) {
		format(string, sizeof(string), "{FFFFFF}[%d].\t{FFFFFF}-\t{FFFFFF}ID: %d\n", i, Player.Pickcar[i][@id]);
		strcat(string2, string);
		count ++;
	}

	if (!count) return SendErrorMessage(playerid, "เซิร์ฟเวอร์ยังไม่ได้เพิ่ม 'Pickcar'");

	inline const Loaded(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused pid, dialogid, inputtext, listitem

		if (!response) @return true;

		if (response) @return true;
	}
	format(string, sizeof(string), "Index\t-\tID\n%s", string2);
	Dialog_ShowCallback(playerid, using inline Loaded, DIALOG_STYLE_TABLIST_HEADERS, "PickcarIDList", string, "ปิด", "");
	return true;
}