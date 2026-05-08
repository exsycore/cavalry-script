#if defined _inc_impl
    #undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnPlayerSpawn(playerid) {
	return true;
}

hook OnGameModeInit() {
    mysql_tquery(get_handle(), "SELECT * FROM "VEHICLE_TABLE"", "LoadPlayerVehicle");

	return true;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispssenger) {
	if (IsVehicleOwner(playerid, vehicleid)) {
		if (ispssenger) return 1;
		SendTipsMessage(playerid, "กด 'N' เพื่อสตาร์ทเครื่องยนต์");
		SavePlayerVehicle(playerid, vehicleid);
	}
	return 1;
}

hook OnPlayerExitVehicle(playerid, vehicleid) {
	if (IsVehicleOwner(playerid, vehicleid)) {
		if ((Player.Vehicle[playerid][vehicleid][@spawned] == true)) {
			SavePlayerVehicle(playerid, vehicleid);
		}
	}
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	foreach (new i : Vehicle)
	{
		if (!GetPlayerLoggedIn(playerid)) continue;

		if ((strcmp(Player.Vehicle[playerid][i][@owner], ReturnPlayerName(playerid)) == 0))
		{
			if ((Player.Vehicle[playerid][i][@spawned] == true))
			{
				SavePlayerVehicle(playerid, i);
			}
		}
	}

	return true;
}

hook OnGameModeExit()
{
	foreach (new p : Player)
	{
		foreach (new i : Vehicle)
		{
			if ((strcmp(Player.Vehicle[p][i][@owner], ReturnPlayerName(p)) == 0))
			{
				if ((Player.Vehicle[p][i][@spawned] == true))
				{
					DespawnVehicleOwner(p, i);
				}
			}
		}
	}

	SetPlayerVehicleInDB();

	return true;
}

hook OnPlayerUpdate(playerid)
{
	SetTimerEx("UpdateFuel", 200, false, "i", playerid);

	return true;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if (newkeys & PRESS_N) {
		if (IsPlayerInAnyVehicle(playerid)) {
			new id = GetPlayerVehicleID(playerid);
			if (IsVehicleOwner(playerid, id)) {
				if (!GetEngineStatus(playerid)) {
					SetEngineStatus(id, true);
				} else {
					SetEngineStatus(id, false);
				}
			}
		}
	}
	return 1;
}

public UpdateFuel(playerid) {
	new playerState = GetPlayerState(playerid);
	if (playerState == PLAYER_STATE_DRIVER) {
		new
			vehicleid = GetPlayerVehicleID(playerid),
			Float:value = floatmul(floatdiv(GetVehicleSpeed(vehicleid), 200.0), 0.01);

		if (GetEngineStatus(vehicleid) && IsVehicleOwner(playerid, vehicleid)) {
			if (Player.Vehicle[playerid][vehicleid][@fuel] > 0) {
				Player.Vehicle[playerid][vehicleid][@fuel] -= value;
			} else {
				SetEngineStatus(vehicleid, false);
				Player.Vehicle[playerid][vehicleid][@fuel] = 0;
			}
		}
	}
	return 1;
}

public LoadPlayerVehicle(playerid)
{
	new
	    rows;
	cache_get_row_count(rows);

	for (new i = 0; i < rows && i < MAX_PLAYER_VEHICLE; i ++)
	{
		Player.Vehicle[playerid][i][@exists] = true;

		cache_get_value_name_int(i, "id", Player.Vehicle[playerid][i][@id]);
		cache_get_value_name_int(i, "ownerid", Player.Vehicle[playerid][i][@ownerid]);
		cache_get_value_name(i, "owner", Player.Vehicle[playerid][i][@owner]);
		cache_get_value_name(i, "plate", Player.Vehicle[playerid][i][@plate]);
		cache_get_value_name_int(i, "modelid", Player.Vehicle[playerid][i][@modelid]);
		cache_get_value_name_int(i, "color1", Player.Vehicle[playerid][i][@color1]);
		cache_get_value_name_int(i, "color2", Player.Vehicle[playerid][i][@color2]);

		cache_get_value_name_bool(i, "spawned", Player.Vehicle[playerid][i][@spawned]);
		cache_get_value_name_bool(i, "lock", Player.Vehicle[playerid][i][@lock]);

		cache_get_value_name_float(i, "posx", Player.Vehicle[playerid][i][@posx]);
		cache_get_value_name_float(i, "posy", Player.Vehicle[playerid][i][@posy]);
		cache_get_value_name_float(i, "posz", Player.Vehicle[playerid][i][@posz]);
		cache_get_value_name_float(i, "posa", Player.Vehicle[playerid][i][@posa]);
		cache_get_value_name_float(i, "fuel", Player.Vehicle[playerid][i][@fuel]);
		cache_get_value_name_float(i, "health", Player.Vehicle[playerid][i][@health]);
	}
	printf("[SYSTEM][DB] %i Vehicle owner loaded.", rows);

	return true;
}

public SetPlayerVehicle(playerid)
{
	new
	    rows;
	cache_get_row_count(rows);

	for (new i = 0; i < rows; i ++)
	{
		new playerName[64];
		cache_get_value_name(i, "owner", playerName);

		UpdateOfflinePlayer(playerName);
	}

	return true;
}

stock GetEngineStatus(vehicleid) {
    static
        engine,
        lights,
        alarm,
        doors,
        bonnet,
        boot,
        objective;

    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

    if (engine != 1) return 0;
    return 1;
}

stock SetEngineStatus(vehicleid, status) {
    static
        engine,
        lights,
        alarm,
        doors,
        bonnet,
        boot,
        objective;

    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    
    return SetVehicleParamsEx(vehicleid, status, lights, alarm, doors, bonnet, boot, objective);
}

stock SetPlayerVehicleInDB()
{
	mysql_tquery(get_handle(), "SELECT id, ownerid, owner, spawned FROM "VEHICLE_TABLE"", "SetPlayerVehicle", "");
    return true;
}

stock UpdateOfflinePlayer(const name[])
{
    new query[256];
    mysql_format(get_handle(), query, sizeof(query), "UPDATE "VEHICLE_TABLE" SET \
	spawned = 0 WHERE owner = '%s'", name);
    mysql_tquery(get_handle(), query);

    return true;
}

stock SetVehicleParams(vehicleid, param, status)
{
	new params[7];
	GetVehicleParamsEx(vehicleid, params[0], params[1], params[2], params[3], params[4], params[5], params[6]);
	params[param] = status;
	return SetVehicleParamsEx(vehicleid, params[0], params[1], params[2], params[3], params[4], params[5], params[6]);
}

stock GetNearbyVehicle(playerid)
{
	new Float:x, Float:y, Float:z;

	for (new i = 0; i < MAX_VEHICLES; i ++)
	{
	    if (IsValidVehicle(i) && IsVehicleStreamedIn(i, playerid))
		{
	        GetVehiclePos(i, x, y, z);

	        if (IsPlayerInRangeOfPoint(playerid, 3.5, x, y, z))
			{
	            return i;
			}
		}
	}

	return INVALID_VEHICLE_ID;
}

stock ReturnVehicleName(vehicleid)
{
	new
		model = GetVehicleModel(vehicleid),
		name[32] = "None";

    if (model < 400 || model > 611) return name;

	format(name, sizeof name, g_arrVehicleNames[model - 400]);

	return name;
}

stock ReturnVehicleModelName(model)
{
	new
	    name[32] = "None";

    if (model < 400 || model > 611)
	    return name;

	format(name, sizeof name, g_arrVehicleNames[model - 400]);

	return name;
}

stock GetVehicleModelByName(const name[])
{
	if (isnumeric(name) && (strval(name) >= 400 && strval(name) <= 611)) return strval(name);

	for (new i = 0; i < sizeof g_arrVehicleNames; i ++)
	{
	    if (strfind(g_arrVehicleNames[i], name, true) != -1)
		{
	        return i + 400;
		}
	}

	return false;
}

stock DespawnVehicleOwner(playerid, vehicleid)
{
	Player.Vehicle[playerid][vehicleid][@spawned] = false;
	Player.Vehicle[playerid][vehicleid][@lock] = false;

	SavePlayerVehicle(playerid, vehicleid);

	DestroyVehicle(vehicleid);
	ResetVehicle(playerid, vehicleid);

	return true;
}

stock ResetVehicle(playerid, vehicleid)
{
	Player.Vehicle[playerid][vehicleid][@id] = 0;
	Player.Vehicle[playerid][vehicleid][@ownerid] = 0;
	Player.Vehicle[playerid][vehicleid][@owner] = 0;

	strcpy(Player.Vehicle[playerid][vehicleid][@plate], "None", 32);

	Player.Vehicle[playerid][vehicleid][@modelid] = 0;
	Player.Vehicle[playerid][vehicleid][@color1] = 0;
	Player.Vehicle[playerid][vehicleid][@color2] = 0;
	Player.Vehicle[playerid][vehicleid][@posx] = 0;
	Player.Vehicle[playerid][vehicleid][@posy] = 0;
	Player.Vehicle[playerid][vehicleid][@posz] = 0;
	Player.Vehicle[playerid][vehicleid][@posa] = 0;
	Player.Vehicle[playerid][vehicleid][@fuel] = 0;
	Player.Vehicle[playerid][vehicleid][@health] = 0;
	Player.Vehicle[playerid][vehicleid][@spawned] = false;
	Player.Vehicle[playerid][vehicleid][@lock] = false;
}

stock IsVehicleOwner(playerid, vehicleid)
{
	return (Player.Vehicle[playerid][vehicleid][@ownerid] == playerData[playerid][pID]) && (Player.Vehicle[playerid][vehicleid][@ownerid] != 0);
}

stock GetLockStatus(vehicleid) {
	static
	    engine,
	    lights,
	    alarm,
	    doors,
	    bonnet,
	    boot,
	    objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if (doors != 1) return false;
	return true;
}

stock SetLockStatus(vehicleid, status) {
	static
	    engine,
	    lights,
	    alarm,
	    doors,
	    bonnet,
	    boot,
	    objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return SetVehicleParamsEx(vehicleid, engine, lights, alarm, status, bonnet, boot, objective);
}

stock GenerateRandomPlate()
{
    new plate[MAX_PLATE_LENGTH + 1];

    for (new i = 0; i < MAX_PLATE_LENGTH; i ++)
	{
        plate[i] = CHAR_SET[random(sizeof CHAR_SET - 1)];
    }

    plate[MAX_PLATE_LENGTH] = '\0';

    return plate;
}

stock CreatePlayerVehicle(playerid, modelid, colorPrimary, colorSecondary)
{
	for (new i = 0; i < MAX_PLAYER_VEHICLE; i ++) {
		if (!Player.Vehicle[playerid][i][@exists]) {
			new plate[20];
			new query[256 + MAX_PLAYER_NAME + 1];
			plate = GenerateRandomPlate();

			Player.Vehicle[playerid][i][@exists] = true;

			mysql_format(get_handle(), query, sizeof query, "INSERT INTO "VEHICLE_TABLE" (ownerid, owner, modelid, plate, spawned, color1, color2, fuel, health) VALUES('%d', '%e', '%d', '%e', '0', '%d', '%d', '100', '1000')", playerData[playerid][pID], ReturnPlayerName(playerid), modelid, plate, colorPrimary, colorSecondary);
			mysql_tquery(get_handle(), query);
			break;
		}
	}
	return 1;
}

stock DeletePlayerVehicle(playerid, vehicleid)
{
	if (vehicleid != -1)
	{
	    new
	        string[64];

		format(string, sizeof(string), "DELETE FROM "VEHICLE_TABLE" WHERE `ownerid` = '%d'", Player.Vehicle[playerid][vehicleid][@ownerid]);
		mysql_tquery(get_handle(), string);

		Player.Vehicle[playerid][vehicleid][@exists] = false;
		Player.Vehicle[playerid][vehicleid][@id] = 0;
	}

	return true;
}

stock SavePlayerVehicle(playerid, vehicleid)
{
    new query[524];
	new Float:health;

	GetVehicleHealth(vehicleid, health);

	Player.Vehicle[playerid][vehicleid][@health] = health;

	GetPlayerPos(playerid, Player.Vehicle[playerid][vehicleid][@posx], Player.Vehicle[playerid][vehicleid][@posy], Player.Vehicle[playerid][vehicleid][@posz]);
	GetPlayerFacingAngle(playerid, Player.Vehicle[playerid][vehicleid][@posa]);

    mysql_format(get_handle(), query, sizeof query,
        "UPDATE "VEHICLE_TABLE" SET `owner` = '%e', `ownerid` = '%d', `plate` = '%e', `spawned` = '%d', `modelid` = '%d', \
		`color1` = '%d', `color2` = '%d', `posx` = '%.2f', `posy` = '%.2f', `posz` = '%.2f', `posa` = '%.2f', `lock` = '%d', \
		`fuel` = '%.2f', `health` = '%.2f' WHERE `id` = '%d'",
        Player.Vehicle[playerid][vehicleid][@owner],
        Player.Vehicle[playerid][vehicleid][@ownerid],
		Player.Vehicle[playerid][vehicleid][@plate],
		Player.Vehicle[playerid][vehicleid][@spawned],
		Player.Vehicle[playerid][vehicleid][@modelid],
		Player.Vehicle[playerid][vehicleid][@color1],
		Player.Vehicle[playerid][vehicleid][@color2],
		Player.Vehicle[playerid][vehicleid][@posx],
		Player.Vehicle[playerid][vehicleid][@posy],
		Player.Vehicle[playerid][vehicleid][@posz],
		Player.Vehicle[playerid][vehicleid][@posa],
		Player.Vehicle[playerid][vehicleid][@lock],
		Player.Vehicle[playerid][vehicleid][@fuel],
		Player.Vehicle[playerid][vehicleid][@health],
		Player.Vehicle[playerid][vehicleid][@id]
	);
	mysql_tquery(get_handle(), query);
	return 1;
}

stock GetVehicleSpeed(vehicleid)
{
    new Float:V[3];
    GetVehicleVelocity(vehicleid, V[0], V[1], V[2]);
    return floatround(floatsqroot(V[0] * V[0] + V[1] * V[1] + V[2] * V[2]) * VELOCITY_TO_KMH);
}

YCMD:lock(playerid, const params[], help)
{
	if (!GetPlayerLoggedIn(playerid)) return 1;

	new id = GetNearbyVehicle(playerid);

	if (id == INVALID_VEHICLE_ID) return SendErrorMessage(playerid, "คุณต้องอยู่ไกล้รถของคุณจึงจะสามารถล็อกได้");

	if (IsVehicleOwner(playerid, id))
	{
		if (!Player.Vehicle[playerid][id][@lock])
		{
			Player.Vehicle[playerid][id][@lock] = true;
			SendClientMessage(playerid, -1, "คุณได้ทำการล็อครถเรียบร้อยแล้ว");
		}
		else
		{
			Player.Vehicle[playerid][id][@lock] = false;
			SendClientMessage(playerid, -1, "คุณได้ทำการปลดล็อครถเรียบร้อยแล้ว");
		}

		SetLockStatus(id, Player.Vehicle[playerid][id][@lock]);
		SavePlayerVehicle(playerid, id);
	}
	
	return 1;
}

YCMD:givecar(playerid, const params[], help) {
    if (help) return SendErrorMessage(playerid, "Not supported");

	if (!IsPlayerAdminEx(playerid)) return SendErrorMessage(playerid, "Not supported");

	if (sscanf(params, "uddd", params[0], params[1], params[2], params[3]))
        return SendSyntaxMessage(playerid, "/givecar [ชื่อ/ไอดี] [ไอดีรถ] [สี1] [สี2]");

	if (params[0] == INVALID_PLAYER_ID)
        return va_SendClientMessage(playerid, COLOR_RED, "[Error]: ผู้เล่นไอดีนั้นไม่ได้ออนไลน์อยู่");

    if (!GetPlayerLoggedIn(params[0]))
        return va_SendClientMessage(playerid, COLOR_RED, "[Error]: ผู้เล่นคนนั้นยังไม่ได้ Login");

	CreatePlayerVehicle(params[0], params[1], params[2], params[3]);

    SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ได้สร้างรถให้ %s รุ่น %s", ReturnPlayerName(playerid), ReturnPlayerName(params[0]), ReturnVehicleModelName(params[1]));
    // SendAdminAction(playerid, ""EC_WHITE"ได้สร้างรถให้ "EC_GREEN"%s "EC_WHITE"รุ่น "EC_GREEN"%s", ReturnPlayerName(params[0]), ReturnVehicleModelName(params[1]));
    // SendPlayerAction(params[0], ""EC_WHITE"คุณได้รับรถรุ่น "EC_GREEN"%s "EC_WHITE"จากแอดมิน "EC_RED"%s", ReturnVehicleModelName(params[1]), ReturnPlayerName(playerid));

    // LogWrite("logs/givecar.log", "(ADMIN) %s[DBID:%i] Give vehicle %s to Player %s[DBID:%i]"
    //     , ReturnPlayerName(playerid)
    //     , Player[playerid][ID]
    //     , ReturnVehicleModelName(params[1])
    //     , ReturnPlayerName(params[0])
    //     , Player[params[0]][ID]
    // );

	return 1;
}

#include "garage\impl"