#if defined _inc_impl
    #undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
	mysql_tquery(get_handle(), "SELECT * FROM `garage`", "GarageLoad", "");
    return true;
}

hook OnPlayerConnect(playerid) {
	LoadGarageUI(playerid);
	return true;
}

hook OnPlayerDisconnect(playerid, reason) {
	DestroyUIGarage(playerid);
	return true;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if (PRESSED(KEY_NO)) {
		if (!IsPlayerInAnyVehicle(playerid)) {
			if (GarageNearest(playerid) != -1) {
				OpenGarageUI(playerid, true);
				//ShowDialogVehicle(playerid);
			}
		}
	}
	return true;
}

hook OnCancelDynTextDraw(playerid) {
	if (IsOpenGarageUI[playerid]) {
		OpenGarageUI(playerid, false);
	}
	return 1;
}

hook OnClickDynamicPlayerTD(playerid, PlayerText:playertextid) {
	if (IsOpenGarageUI[playerid]) {
		for (new i = 0; i < GARAGE_PER_PAGE; i++) {
			if (playertextid == Garage_Slot[playerid][i]) {
				new query[128];
				new index = GarageSlotIndex[playerid][i];

				if (index != -1 && Player.Vehicle[playerid][index][@exists]) {
					format(query, sizeof(query), "SELECT * FROM "VEHICLE_TABLE" WHERE ownerid = '%d' LIMIT %d, 1", playerData[playerid][pID], index);
					mysql_tquery(get_handle(), query, "OnPlayerSpawnVehicle", "i", playerid);
					OpenGarageUI(playerid, false);
				}
				return 0;
			}
		}

		if (playertextid == close_btn[playerid][0]) {
			OpenGarageUI(playerid, false);
			return 0;
		}
		
		for (new i = 0; i < GARAGE_PAGE_PREV; i++) {
			if (playertextid == Garage_UI_Page[playerid][i]) {
				GarageUIPage[playerid] = i;
				new query[128];
				mysql_format(get_handle(), query, sizeof(query), "SELECT * FROM "VEHICLE_TABLE" WHERE `ownerid` = %d", playerData[playerid][pID]);
				mysql_tquery(get_handle(), query, "RefreshUIGarage", "dd", playerid, LIST_VEHICLES);
				return 0;
			}
		}
	}
    return 0;
}

public OpenGarageUI(playerid, bool:enable) {
    if (enable == true) {
        IsOpenGarageUI[playerid] = true;

		new query[128];
		mysql_format(get_handle(), query, sizeof(query), "SELECT * FROM "VEHICLE_TABLE" WHERE `ownerid` = %d", playerData[playerid][pID]);
		mysql_tquery(get_handle(), query, "RefreshUIGarage", "dd", playerid, LIST_VEHICLES);
    } else {
        IsOpenGarageUI[playerid] = false;

        CancelSelectTextDraw(playerid);

		for (new i = 0; i < 8; i ++) {
			if (IsValidDynamicPlayerTextDraw(playerid, Garage_Slot[playerid][i]))
				PlayerTextDrawHide(playerid, Garage_Slot[playerid][i]);
		}
		for (new i = 0; i < 9; i ++) {
			if (IsValidDynamicPlayerTextDraw(playerid, Garage_UI[playerid][i]))
				PlayerTextDrawHide(playerid, Garage_UI[playerid][i]);
		}
		for (new i = 0; i < 1; i ++) {
			if (IsValidDynamicPlayerTextDraw(playerid, close_btn[playerid][i]))
				PlayerTextDrawHide(playerid, close_btn[playerid][i]);
		}
		for (new i = 0; i < 4; i ++) {
			if (IsValidDynamicPlayerTextDraw(playerid, Garage_UI_Page[playerid][i]))
				PlayerTextDrawHide(playerid, Garage_UI_Page[playerid][i]);
		}
    }
    return true;
}

public OnSelectVehicle(playerid, threadid) {
	new
		rows;

	cache_get_row_count(rows);

	switch (threadid) {
		case LIST_VEHICLES: {
		    if (!rows) {
		        SendErrorMessage(playerid, "คุณไม่มีรถส่วนตัวเลย");
		    } else {
		        new string[1024], modelid;

				new plate[20];
				new query[128];
				new Float:fuel;
				new Float:health;

		        string = "ทะเบียน\tชื่อรุ่น\tน้ำมัน\tค่าความเสียหาย";

		        for (new i = 0; i < rows; i ++) {
					cache_get_value_name_int(i, "modelid", modelid);
					cache_get_value_name(i, "plate", plate);
					cache_get_value_name_float(i, "fuel", fuel);
					cache_get_value_name_float(i, "health", health);
		            format(string, sizeof string, "%s\nทะเบียน: {1E90FF}%s\t{FFFFFF}| ยานพาหนะ: {1E90FF}%s\t{FFFFFF}| น้ำมัน: {1E90FF}%.1f\t{FFFFFF}| ค่าความเสียหาย: {1E90FF}%.2f", string, plate, g_arrVehicleNames[modelid - 400], fuel, health);
				}

				inline const Loaded(pid, dialogid, response, listitem, string:inputtext[]) {
					#pragma unused dialogid, inputtext, pid

					if (!response) @return true;
					
					format(query, sizeof(query), "SELECT * FROM "VEHICLE_TABLE" WHERE ownerid = '%d' LIMIT %d, 1", playerData[playerid][pID], listitem);
					mysql_tquery(get_handle(), query, "OnPlayerSpawnVehicle", "i", playerid);
				}
				Dialog_ShowCallback(playerid, using inline Loaded, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}รถของคุณ", string, "เลือก", "ยกเลิก");
		    }
		}
	}
	return true;
}

public OnPlayerSpawnVehicle(playerid) {
	new rows_2;
	cache_get_row_count(rows_2);

	if (rows_2) {
		new Float:vx, Float:vy, Float:vz, Float:va, Float:health;
		new vehicleid, modelid, color1, color2;
		new plate[64];
		new bool:spawned;

		GetPlayerPos(playerid, vx, vy, vz);
		GetPlayerFacingAngle(playerid, va);

		cache_get_value_name(0, "plate", plate);
		cache_get_value_name_int(0, "modelid", modelid);
		cache_get_value_name_int(0, "color1", color1);
		cache_get_value_name_int(0, "color2", color2);
		cache_get_value_name_bool(0, "spawned", spawned);
		cache_get_value_name_float(0, "health", health);

		if (spawned) return SendErrorMessage(playerid, "คุณเรียกรถมาไว้แล้วคันหนึ่ง หากต้องการเรียกอีกคันหนึ่งโปรดเก็บอีกคันก่อน");

		if (health < 250) return SendErrorMessage(playerid, "รถของคุณพัง ไม่สามารถเรียกรถได้");

		vehicleid = CreateVehicle(modelid, vx, vy + 2.0, vz, va, color1, color2, -1);
		SetVehicleNumberPlate(vehicleid, plate);
		SetVehicleHealth(vehicleid, health);
		PutPlayerInVehicle(playerid, vehicleid, 0);
		
		SendGarageAction(playerid, "คุณได้ทำการเรียกรถส่วนตัวรุ่น %s ออกมาใช้งานแล้ว", ReturnVehicleName(vehicleid));

		if (vehicleid != INVALID_VEHICLE_ID) {
			cache_get_value_name_int(0, "id", Player.Vehicle[playerid][vehicleid][@id]);
			cache_get_value_name_int(0, "ownerid", Player.Vehicle[playerid][vehicleid][@ownerid]);
			cache_get_value_name(0, "owner", Player.Vehicle[playerid][vehicleid][@owner]);
			cache_get_value_name(0, "plate", Player.Vehicle[playerid][vehicleid][@plate]);
			cache_get_value_name_int(0, "modelid", Player.Vehicle[playerid][vehicleid][@modelid]);
			cache_get_value_name_int(0, "color1", Player.Vehicle[playerid][vehicleid][@color1]);
			cache_get_value_name_int(0, "color2", Player.Vehicle[playerid][vehicleid][@color2]);
			cache_get_value_name_bool(0, "spawned", Player.Vehicle[playerid][vehicleid][@spawned]);

			cache_get_value_name_float(0, "posx", Player.Vehicle[playerid][vehicleid][@posx]);
			cache_get_value_name_float(0, "posy", Player.Vehicle[playerid][vehicleid][@posy]);
			cache_get_value_name_float(0, "posz", Player.Vehicle[playerid][vehicleid][@posz]);
			cache_get_value_name_float(0, "posa", Player.Vehicle[playerid][vehicleid][@posa]);
			cache_get_value_name_float(0, "fuel", Player.Vehicle[playerid][vehicleid][@fuel]);
			cache_get_value_name_float(0, "health", Player.Vehicle[playerid][vehicleid][@health]);

			Player.Vehicle[playerid][vehicleid][@posx] = vx;
			Player.Vehicle[playerid][vehicleid][@posy] = vy;
			Player.Vehicle[playerid][vehicleid][@posz] = vz;
			Player.Vehicle[playerid][vehicleid][@posa] = va;
			Player.Vehicle[playerid][vehicleid][@spawned] = true;

			SavePlayerVehicle(playerid, vehicleid);
		}
	}
	return true;
}

public GarageLoad() {
	new
	    rows;

	cache_get_row_count(rows);

	for (new i = 0; i < rows; i ++) if (i < MAX_GARAGE) {
	    Player.Garage[i][@exists] = true;

	    cache_get_value_name_int(i, "garageid", Player.Garage[i][@id]);
	    cache_get_value_name_float(i, "garagex", Player.Garage[i][@garagex]);
	    cache_get_value_name_float(i, "garagey", Player.Garage[i][@garagey]);
	    cache_get_value_name_float(i, "garagez", Player.Garage[i][@garagez]);

	    GarageRefresh(i);
	}
	printf("[SYSTEM][DB] %i Garage loaded.", rows);
	return true;
}

public OnGarageCreated(garageid) {
	if (garageid == -1 || !Player.Garage[garageid][@exists]) return false;

	Player.Garage[garageid][@id] = cache_insert_id();
	GarageSave(garageid);
	return true;
}

stock GarageNearest(playerid) {
    for (new i = 0; i != MAX_GARAGE; i ++) if (Player.Garage[i][@exists] && IsPlayerInRangeOfPoint(playerid, 4.0, Player.Garage[i][@garagex], Player.Garage[i][@garagey], Player.Garage[i][@garagez])) {
		return i;
	}
	return -1;
}

stock GarageDelete(garageid) {
	if (garageid != -1 && Player.Garage[garageid][@exists]) {
	    new
	        string[64];

        if (IsValidDynamicPickup(Player.Garage[garageid][@garageobject]))
		    DestroyDynamicPickup(Player.Garage[garageid][@garageobject]);
		
		if (IsValidDynamicObject(Player.Garage[garageid][@garageobject2]))
		    DestroyDynamicObject(Player.Garage[garageid][@garageobject2]);

		if (IsValidDynamic3DTextLabel(Player.Garage[garageid][@garagetext3d]))
		    DestroyDynamic3DTextLabel(Player.Garage[garageid][@garagetext3d]);
		
		if (IsValidDynamicMapIcon(Player.Garage[garageid][@garageicon]))
		    DestroyDynamicMapIcon(Player.Garage[garageid][@garageicon]);

		mysql_format(get_handle(), string, sizeof string, "DELETE FROM `garage` WHERE `garageid` = '%d'", Player.Garage[garageid][@id]);
		mysql_tquery(get_handle(), string);

		Player.Garage[garageid][@exists] = false;
		Player.Garage[garageid][@id] = 0;
	}
	return true;
}

stock GarageCreate(Float:x, Float:y, Float:z) {
	for (new i = 0; i < MAX_GARAGE; i ++) if (!Player.Garage[i][@exists]) {
	    Player.Garage[i][@exists] = true;
	    Player.Garage[i][@garagex] = x;
	    Player.Garage[i][@garagey] = y;
	    Player.Garage[i][@garagez] = z;

	    mysql_tquery(get_handle(), "INSERT INTO `garage` (`garageid`) VALUES(0)", "OnGarageCreated", "d", i);
		GarageRefresh(i);
		return i;
	}
	return -1;
}

stock GarageSave(garageid) {
	new
	    query[220];

	mysql_format(get_handle(), query, sizeof query, "UPDATE `garage` SET `garagex` = '%.4f', `garagey` = '%.4f', `garagez` = '%.4f' WHERE `garageid` = '%d'",
	    Player.Garage[garageid][@garagex],
	    Player.Garage[garageid][@garagey],
	    Player.Garage[garageid][@garagez],
	    Player.Garage[garageid][@id]
	);
	return mysql_tquery(get_handle(), query);
}

stock GarageRefresh(garageid) {
	if (garageid != -1 && Player.Garage[garageid][@exists]) {
		if (IsValidDynamicPickup(Player.Garage[garageid][@garageobject]))
		    DestroyDynamicPickup(Player.Garage[garageid][@garageobject]);
		
		if (IsValidDynamicObject(Player.Garage[garageid][@garageobject2]))
		    DestroyDynamicObject(Player.Garage[garageid][@garageobject2]);

		if (IsValidDynamic3DTextLabel(Player.Garage[garageid][@garagetext3d]))
		    DestroyDynamic3DTextLabel(Player.Garage[garageid][@garagetext3d]);

		if (IsValidDynamicMapIcon(Player.Garage[garageid][@garageicon]))
		    DestroyDynamicMapIcon(Player.Garage[garageid][@garageicon]);

		Player.Garage[garageid][@garageobject] = CreateDynamicPickup(MODEL_GARAGE, 23, Player.Garage[garageid][@garagex], Player.Garage[garageid][@garagey], Player.Garage[garageid][@garagez]);
		Player.Garage[garageid][@garageobject2] = CreateDynamicObject(1316, Player.Garage[garageid][@garagex], Player.Garage[garageid][@garagey], Player.Garage[garageid][@garagez] - 0.9, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
		SetDynamicObjectMaterial(Player.Garage[garageid][@garageobject2], 0, -1, "none", "none", 0xFF00FF00);  		Player.Garage[garageid][@garagetext3d] = CreateDynamic3DTextLabel(TEXT3D_GARAGE, -1, Player.Garage[garageid][@garagex], Player.Garage[garageid][@garagey], Player.Garage[garageid][@garagez], 5.0, INVALID_VEHICLE_ID, INVALID_PLAYER_ID, 0);
		Player.Garage[garageid][@garageicon] = CreateDynamicMapIcon(Player.Garage[garageid][@garagex], Player.Garage[garageid][@garagey], Player.Garage[garageid][@garagez], 55, 0);
	}
	return true;
}

stock PanelCreateGarage(playerid) {
	if (!IsPlayerAdminEx(playerid)) return 1;
	if (GetPlayerInterior(playerid) != 0) return 1;

	inline const CreateGarage(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused dialogid, inputtext, pid

		if (!response) @return 1;

		switch (listitem) {
			case 0 : {
				new
					Float:x,
					Float:y,
					Float:z;

				GetPlayerPos(playerid, x, y, z);

				new id = GarageCreate(x, y, z);
				if (id == -1)
				{
					SendErrorMessage(playerid, "ความจุของ 'Garage' ในฐานข้อมูลเต็มแล้ว (ติดต่อผู้พัฒนา)");
					@return 1;
				}
				SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ได้สร้าง 'Garage' ขึ้นมาใหม่แล้ว ID: %d", ReturnPlayerName(playerid), id);
			}
			case 1 : {
				GarageDeleteDialog(playerid);
			}
			case 2 : {
				GarageIDList(playerid);
			}
		}
	}
	Dialog_ShowCallback(playerid, using inline CreateGarage, DIALOG_STYLE_LIST, "{FFFFFF}PanelGarage", "สร้าง\nลบ\nไอดีที่มีอยู่", "เลือก", "ยกเลิก");
	return 1;
}

stock GarageDeleteDialog(playerid) {
	inline const DeleteGarage(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused dialogid, listitem, pid

		if (!response) @return true;

		new id = 0;
		
		if (sscanf(inputtext, "d", id)) {
			SendErrorMessage(playerid, "ต้องป้อนรูปแบบเลขเท่านั้น");
			@return PanelCreateGarage(playerid);
		}
		
		if ((id < 0 || id >= MAX_GARAGE) || !Player.Garage[id][@exists]) {
			SendErrorMessage(playerid, "ไม่มีไอดีที่เก็บรถนี้อยู่ในฐานข้อมูล");
			@return PanelCreateGarage(playerid);
		}

		GarageDelete(id);
		SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ได้ลบ 'Garage' ID: %d", ReturnPlayerName(playerid), id);
	}
	Dialog_ShowCallback(playerid, using inline DeleteGarage, DIALOG_STYLE_INPUT, "{FFFFFF}DeleteGarage", "ป้อน ID Garage นั้น", "ลบ", "ยกเลิก");
	return true;
}

stock GarageIDList(playerid) {
	new count = 0;
	new string[1660], string2[1660] = "";

	for (new i = 0; i < MAX_GARAGE; i ++) if (Player.Garage[i][@exists]) {
		format(string, sizeof(string), "{FFFFFF}[%d].\t{FFFFFF}-\t{FFFFFF}ID: %d\n", count, Player.Garage[i][@id]);
		strcat(string2, string);

		count ++;
	}

	if (!count) return SendErrorMessage(playerid, "เซิร์ฟเวอร์ยังไม่ได้เพิ่ม 'Garage'");

	inline const Loaded(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused pid, dialogid, inputtext, listitem

		if (!response) @return true;

		if (response) @return true;
	}
	format(string, sizeof(string), "Index\t-\tID\n%s", string2);
	Dialog_ShowCallback(playerid, using inline Loaded, DIALOG_STYLE_TABLIST_HEADERS, "GarageIDList", string, "ปิด", "");
	return true;
}

public RefreshUIGarage(playerid, threadid) {
	new
		rows;

	cache_get_row_count(rows);

	switch (threadid) {
		case LIST_VEHICLES: {
			for (new i = 0; i < 8; i ++) {
				if (IsValidDynamicPlayerTextDraw(playerid, Garage_Slot[playerid][i]))
					PlayerTextDrawHide(playerid, Garage_Slot[playerid][i]);
			}
			for (new i = 0; i < 9; i ++) {
				if (IsValidDynamicPlayerTextDraw(playerid, Garage_UI[playerid][i]))
					PlayerTextDrawHide(playerid, Garage_UI[playerid][i]);
			}
			for (new i = 0; i < 1; i ++) {
				if (IsValidDynamicPlayerTextDraw(playerid, close_btn[playerid][i]))
					PlayerTextDrawHide(playerid, close_btn[playerid][i]);
			}
			for (new i = 0; i < 4; i ++) {
				if (IsValidDynamicPlayerTextDraw(playerid, Garage_UI_Page[playerid][i]))
					PlayerTextDrawHide(playerid, Garage_UI_Page[playerid][i]);
			}

		    if (!rows) {
		        SendErrorMessage(playerid, "คุณไม่มีรถส่วนตัวเลย");
		    } else {
				SelectTextDraw(playerid, 0xFFFFFF60);

				new page = GarageUIPage[playerid];

				for (new i = 0; i < GARAGE_PAGE_PREV; i++) {
					PlayerTextDrawColor(playerid, Garage_UI_Page[playerid][i], (i == page) ? 0x505050FF : 0xFFFFFFFF);
				}

				for (new i = 0; i < 9; i ++) {
					if (IsValidDynamicPlayerTextDraw(playerid, Garage_UI[playerid][i]))
						PlayerTextDrawShow(playerid, Garage_UI[playerid][i]);
				}
				for (new i = 0; i < 1; i ++) {
					if (IsValidDynamicPlayerTextDraw(playerid, close_btn[playerid][i]))
						PlayerTextDrawShow(playerid, close_btn[playerid][i]);
				}
				for (new i = 0; i < 4; i ++) {
					if (IsValidDynamicPlayerTextDraw(playerid, Garage_UI_Page[playerid][i]))
						PlayerTextDrawShow(playerid, Garage_UI_Page[playerid][i]);
				}

		        new start = page * GARAGE_PER_PAGE;
				new end = start + GARAGE_PER_PAGE;
				new s = 0;

				for (new i = start; i < rows && i < end; i++) {
					new bool:spawned, modelid, plate[32], Float:fuel, Float:health;

					cache_get_value_name_int(i, "modelid", modelid);
					cache_get_value_name(i, "plate", plate);
					cache_get_value_name_float(i, "fuel", fuel);
					cache_get_value_name_float(i, "health", health);
					cache_get_value_name_bool(i, "spawned", spawned);

					if (spawned) {
						if (IsValidDynamicPlayerTextDraw(playerid, Garage_Slot[playerid][s])) {
							PlayerTextDrawBackgroundColor(playerid, Garage_Slot[playerid][s], 0xFF505080);
							PlayerTextDrawSetPreviewModel(playerid, Garage_Slot[playerid][s], modelid);
							PlayerTextDrawShow(playerid, Garage_Slot[playerid][s]);
						}
					} else {
						if (IsValidDynamicPlayerTextDraw(playerid, Garage_Slot[playerid][s])) {
							PlayerTextDrawBackgroundColor(playerid, Garage_Slot[playerid][s], 808464639);
							PlayerTextDrawSetPreviewModel(playerid, Garage_Slot[playerid][s], modelid);
							PlayerTextDrawShow(playerid, Garage_Slot[playerid][s]);
						}
					}

					GarageSlotIndex[playerid][s] = s; // Or map to real vehicle ID if needed

					s++;
				}
		    }
		}
	}
	return true;
}