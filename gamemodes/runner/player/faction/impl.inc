#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

stock InitFactions() {
    // --- Police ---
    strcopy(FactionData[FACTION_POLICE][FactionName], "Los Santos Police Dept");
    FactionData[FACTION_POLICE][FactionColor]       = 0x4400FFFF;
    FactionData[FACTION_POLICE][FactionSkin][0]     = 280;   // Rank 0 – Officer
    FactionData[FACTION_POLICE][FactionSkin][1]     = 281;   // Rank 1 – Corporal
    FactionData[FACTION_POLICE][FactionSkin][2]     = 282;   // Rank 2 – Sergeant
    FactionData[FACTION_POLICE][FactionSkin][3]     = 283;   // Rank 3 – Lieutenant
    FactionData[FACTION_POLICE][FactionSkin][4]     = 284;   // Rank 4 – Chief
    FactionData[FACTION_POLICE][FactionSkin][5]     = 284;   // Rank 4 – CEO
    FactionData[FACTION_POLICE][FactionActive]      = true;

    // --- Doctor ---
    strcopy(FactionData[FACTION_MEDICAL][FactionName], "Los Santos Medical Center");
    FactionData[FACTION_MEDICAL][FactionColor]       = 0xFF70FFFF;
    FactionData[FACTION_MEDICAL][FactionSkin][0]     = 160;   // Rank 0 – Intern
    FactionData[FACTION_MEDICAL][FactionSkin][1]     = 160;   // Rank 1 – Nurse
    FactionData[FACTION_MEDICAL][FactionSkin][2]     = 160;   // Rank 2 – Doctor
    FactionData[FACTION_MEDICAL][FactionSkin][3]     = 160;   // Rank 3 – Specialist
    FactionData[FACTION_MEDICAL][FactionSkin][4]     = 160;   // Rank 4 – Chief Medical
    FactionData[FACTION_MEDICAL][FactionSkin][5]     = 160;   // Rank 5 – CEO Medical
    FactionData[FACTION_MEDICAL][FactionActive]      = true;

    // --- Mechanic ---
    strcopy(FactionData[FACTION_MECHANIC][FactionName], "LS Auto Repair Workshop");
    FactionData[FACTION_MECHANIC][FactionColor]     = 0xFFAA22FF;
    FactionData[FACTION_MECHANIC][FactionSkin][0]   = 176;   // Rank 0 – Apprentice
    FactionData[FACTION_MECHANIC][FactionSkin][1]   = 176;   // Rank 1 – Technician
    FactionData[FACTION_MECHANIC][FactionSkin][2]   = 176;   // Rank 2 – Senior Tech
    FactionData[FACTION_MECHANIC][FactionSkin][3]   = 176;   // Rank 3 – Foreman
    FactionData[FACTION_MECHANIC][FactionSkin][4]   = 176;   // Rank 4 – Workshop Chief
    FactionData[FACTION_MECHANIC][FactionSkin][5]   = 176;   // Rank 4 – Workshop CEO
    FactionData[FACTION_MECHANIC][FactionActive]    = true;
}

stock GetPlayerFaction(playerid)
    return PlayerFactionData[playerid][PlayerFaction];

stock GetPlayerFactionRank(playerid)
    return PlayerFactionData[playerid][PlayerFactionRank];

stock bool:IsPlayerOnDuty(playerid)
    return PlayerFactionData[playerid][PlayerOnDuty];

stock bool:IsPlayerInFaction(playerid, factionid)
    return (PlayerFactionData[playerid][PlayerFaction] == factionid);

stock GetFactionName(factionid) {
    new str[128];
    strcopy(str, FactionData[factionid][FactionName]);
    return str;
}

stock Attach3DTextFactionToPlayer(playerid, factionid) {
    new str[128];
    format(str, sizeof(str), "%s", GetFactionName(factionid));
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    factionLabel[playerid] = CreateDynamic3DTextLabel(str, FactionData[factionid][FactionColor], x, y, z + 1.5, 9.0, .attachedplayer = playerid);
    return 1;
}

stock GetFactionRankName(factionid, rank) {
    new PoliceRanks[MAX_FACTION_RANK][] = {
        "Officer", "Corporal", "Sergeant", "Lieutenant", "Chief", "CEO"
    };
    new DoctorRanks[MAX_FACTION_RANK][] = {
        "Intern", "Nurse", "Doctor", "Specialist", "Chief Medical", "CEO"
    };
    new MechanicRanks[MAX_FACTION_RANK][] = {
        "Apprentice", "Technician", "Senior Technician", "Foreman", "Workshop Chief", "CEO"
    };

    new str[256];
    switch (factionid) {
        case FACTION_POLICE:    strcopy(str, PoliceRanks[rank]);
        case FACTION_MECHANIC:  strcopy(str, MechanicRanks[rank]);
        case FACTION_MEDICAL:   strcopy(str, DoctorRanks[rank]);
        default:                strcopy(str, "Unknown");
    }
    return str;
}

stock JoinFaction(playerid, factionid, rank = 0) {
    if (factionid < 0 || factionid >= MAX_FACTIONS) return 0;
    if (!FactionData[factionid][FactionActive])      return 0;

    new prevFaction = PlayerFactionData[playerid][PlayerFaction];
    if (prevFaction != INVALID_FACTION) {
        Iter_Remove(FactionMembers[prevFaction], playerid);
        if (PlayerFactionData[playerid][PlayerOnDuty])
            Iter_Remove(FactionDuty[prevFaction], playerid);
    }

    PlayerFactionData[playerid][PlayerFaction]     = factionid;
    PlayerFactionData[playerid][PlayerFactionRank] = rank;
    PlayerFactionData[playerid][PlayerOnDuty]      = false;

    playerData[playerid][pFaction] = factionid;
    playerData[playerid][pRank] = rank;

    Iter_Add(FactionMembers[factionid], playerid);

    UpdatePlayerPos(playerid);
    UpdatePlayerData(playerid);
    Attach3DTextFactionToPlayer(playerid, factionid);
    SpawnPlayer(playerid);
    SendCongratMessage(playerid, "{FFFFFF}เข้าร่วมหน่วยงาน: {%06x}%s {FFFFFF}ตำแหน่ง: {%06x}%s", FactionData[factionid][FactionColor] >>> 8, GetFactionName(factionid), FactionData[factionid][FactionColor] >>> 8, GetFactionRankName(factionid, rank));
    return 1;
}

stock LeaveFaction(playerid) {
    new factionid = PlayerFactionData[playerid][PlayerFaction];
    if (factionid == INVALID_FACTION) return 0;

    if (PlayerFactionData[playerid][PlayerOnDuty])
        Iter_Remove(FactionDuty[factionid], playerid);

    Iter_Remove(FactionMembers[factionid], playerid);

    PlayerFactionData[playerid][PlayerFaction]     = INVALID_FACTION;
    PlayerFactionData[playerid][PlayerFactionRank] = 0;
    PlayerFactionData[playerid][PlayerOnDuty]      = false;

    playerData[playerid][pFaction] = INVALID_FACTION;
    playerData[playerid][pRank] = 0;

    UpdatePlayerPos(playerid);
    UpdatePlayerData(playerid);
    DestroyDynamic3DTextLabel(factionLabel[playerid]);
    SpawnPlayer(playerid);
    SendWarningMessage(playerid, "{FFFFFF}คุณออกจากหน่วยงานแล้ว");
    return 1;
}

stock SetPlayerDuty(playerid, bool:onDuty) {
    new factionid = PlayerFactionData[playerid][PlayerFaction];
    if (factionid == INVALID_FACTION) return 0;

    if (onDuty && !PlayerFactionData[playerid][PlayerOnDuty]) {
        PlayerFactionData[playerid][PlayerOnDuty] = true;
        Iter_Add(FactionDuty[factionid], playerid);

        new rank = PlayerFactionData[playerid][PlayerFactionRank];
        SetPlayerSkin(playerid, FactionData[factionid][FactionSkin][rank]);
        SetPlayerColor(playerid, FactionData[factionid][FactionColor]);

        SendCongratMessage(playerid, "{FFFFFF}คุณอยู่ในเวรแล้ว (ON DUTY)");
    } else if (!onDuty && PlayerFactionData[playerid][PlayerOnDuty]) {
        PlayerFactionData[playerid][PlayerOnDuty] = false;
        Iter_Remove(FactionDuty[factionid], playerid);

        SetPlayerSkin(playerid, playerData[playerid][pSkin]);

        SendCongratMessage(playerid, "{FFFFFF}คุณออกจากเวรแล้ว (OFF DUTY)");
    }
    return 1;
}

stock bool:FactionMessage(playerid, factionid, const str[]) {
	foreach (new i : FactionMembers[factionid]) {
		va_SendClientMessage(i, -1, "{%06x}[%s] - (%s):{FFFFFF} %s", FactionData[factionid][FactionColor] >>> 8, GetFactionName(factionid), ReturnPlayerRPName(playerid), str);
    }
	return true;
}

stock GetFactionMemberCount(factionid)
    return Iter_Count(FactionMembers[factionid]);

stock GetFactionDutyCount(factionid)
    return Iter_Count(FactionDuty[factionid]);

YCMD:duty(playerid, params[], help) {
    new factionid = GetPlayerFaction(playerid);
    if (factionid == INVALID_FACTION)
        return SendErrorMessage(playerid, "{FFFFFF}คุณไม่ได้อยู่ในหน่วยงานใด");

    new bool:onDuty = IsPlayerOnDuty(playerid);
    SetPlayerDuty(playerid, !onDuty);
    return 1;
}

YCMD:fmembers(playerid, params[], help) {
    new factionid = GetPlayerFaction(playerid);
    if (factionid == INVALID_FACTION)
        return SendErrorMessage(playerid, "{FFFFFF}คุณไม่ได้อยู่ในหน่วยงานใด");

    new msg[128];
    format(msg, sizeof(msg),
        "[Faction] %s | สมาชิก: %d | ปฏิบัติหน้าที่: %d",
        GetFactionName(factionid),
        GetFactionMemberCount(factionid),
        GetFactionDutyCount(factionid)
    );
    SendClientMessage(playerid, FactionData[factionid][FactionColor], msg);

    foreach (new i : FactionDuty[factionid]) {
        format(msg, sizeof(msg), "  • %s [%s]", ReturnPlayerName(i), GetFactionRankName(factionid, PlayerFactionData[i][PlayerFactionRank]));
        SendClientMessage(playerid, 0xCCCCCCFF, msg);
    }
    return 1;
}

YCMD:fchat(playerid, params[], help) {
    new factionid = GetPlayerFaction(playerid);
    if (factionid == INVALID_FACTION)
        return SendErrorMessage(playerid, "{FFFFFF}คุณไม่ได้อยู่ในหน่วยงานใด");
    
    new text[512];
    if (sscanf(params, "s[512]", text))
        return SendSyntaxMessage(playerid, "/fchat [ข้อความ]");

    FactionMessage(playerid, factionid, text);
    return 1;
}

YCMD:revive(playerid, params[], help) {
    if (!IsPlayerInFaction(playerid, FACTION_MEDICAL) || !IsPlayerOnDuty(playerid))
        return SendErrorMessage(playerid, "{FFFFFF}ต้องเป็นหมอและอยู่ในเวร");

    new targetid = INVALID_PLAYER_ID;
    if (sscanf(params, "u", targetid) || !IsPlayerConnected(targetid))
        return SendSyntaxMessage(playerid, "/revive [ไอดี/ชื่อ]");

    if (!playerData[targetid][pInDeath])
        return SendErrorMessage(playerid, "ผู้เล่นคนนั้นไม่ได้รับบาดเจ็บใดๆ");

    RescuePlayer(targetid);

    new msg[128];
    format(msg, sizeof(msg), "ฉันได้ช่วยชีวิต %s", ReturnPlayerName(playerid), ReturnPlayerName(targetid));
    FactionMessage(playerid, FACTION_MEDICAL, msg);
    SendCongratMessage(targetid, "{FFFFFF}คุณได้รับการรักษาแล้ว!");
    return 1;
}

YCMD:repaircar(playerid, params[], help) {
    if (!IsPlayerInFaction(playerid, FACTION_MECHANIC) || !IsPlayerOnDuty(playerid))
        return SendErrorMessage(playerid, "{FFFFFF}ต้องเป็นช่างและอยู่ในเวร");

    new vehicleid = GetPlayerVehicleID(playerid);
    if (!IsPlayerInAnyVehicle(playerid))
        return SendErrorMessage(playerid, "คุณต้องอยู่ในรถเพื่อซ่อม");

    RepairVehicle(vehicleid);
    SetVehicleHealth(vehicleid, 1000.0);

    new msg[128];
    format(msg, sizeof(msg), "[ช่างยนต์] %s ซ่อมรถเรียบร้อย", ReturnPlayerName(playerid));
    SendClientMessage(playerid, FactionData[FACTION_MECHANIC][FactionColor], msg);
    GameTextForPlayer(playerid, "~g~~h~~h~Repaired!", 3000, 1);
    return 1;
}

YCMD:hire(playerid, params[], help) {
    if (!IsPlayerAdminEx(playerid))
        return 1;

    new targetid, factionid, rank = 0;
    if (sscanf(params, "udd", targetid, factionid, rank))
        return SendSyntaxMessage(playerid, "/hire [ไอดี/ชื่อ] [ไอดีหน่วยงาน] [แรงค์]");

    if (!IsPlayerConnected(targetid))
        return SendErrorMessage(playerid, "ผู้เล่นคนนี้ยังไม่ออนไลน์");

    if (!GetPlayerLoggedIn(targetid))
        return SendErrorMessage(playerid, "ผู้เล่นคนนี้ยังไม่เข้าสู่ระบบ");
    
    if (factionid < 0 || factionid >= MAX_FACTIONS)
        return SendErrorMessage(playerid, "faction id ไม่ถูกต้อง (0-%d)", MAX_FACTIONS - 1);

    if (rank < 0 || rank >= MAX_FACTION_RANK)
        return SendErrorMessage(playerid, "rank ไม่ถูกต้อง (0-%d)", MAX_FACTION_RANK - 1);

    JoinFaction(targetid, factionid, rank);

    SendAdminMessage(COLOR_ADMIN, "AdmLog: %s รับ %s เข้า %s (Rank %d)", ReturnPlayerName(playerid), ReturnPlayerName(targetid), GetFactionName(factionid), rank);
    return 1;
}

YCMD:fire(playerid, params[], help) {
    if (!IsPlayerAdminEx(playerid))
        return 1;

    new targetid;
    if (sscanf(params, "u", targetid) || !IsPlayerConnected(targetid))
        return SendSyntaxMessage(playerid, "/fire [ไอดี/ชื่อ]");

    if (!IsPlayerConnected(targetid))
        return SendErrorMessage(playerid, "ผู้เล่นคนนี้ยังไม่ออนไลน์");

    if (!GetPlayerLoggedIn(targetid))
        return SendErrorMessage(playerid, "ผู้เล่นคนนี้ยังไม่เข้าสู่ระบบ");

    LeaveFaction(targetid);

    SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ปลด %s ออกจากหน่วยงาน", ReturnPlayerName(playerid), ReturnPlayerName(targetid));
    return 1;
}

hook OnGameModeInit() {
    InitFactions();
    for (new i = 0; i < MAX_FACTIONS; i++) {
        Iter_Init(FactionMembers[i]);
        Iter_Init(FactionDuty[i]);
    }
    printf("[SYSTEM][FACTION] Faction system loaded (%d factions)", MAX_FACTIONS);
    return 1;
}

hook OnPlayerConnect(playerid) {
    PlayerFactionData[playerid][PlayerFaction]     = INVALID_FACTION;
    PlayerFactionData[playerid][PlayerFactionRank] = 0;
    PlayerFactionData[playerid][PlayerOnDuty]      = false;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    new factionid = PlayerFactionData[playerid][PlayerFaction];
    if (factionid != INVALID_FACTION) {
        Iter_Remove(FactionMembers[factionid], playerid);
        if (PlayerFactionData[playerid][PlayerOnDuty])
            Iter_Remove(FactionDuty[factionid], playerid);
    }
    DestroyDynamic3DTextLabel(factionLabel[playerid]);
    return 1;
}

hook OnPlayerSpawn(playerid) {
    new factionid = playerData[playerid][pFaction];

    PlayerFactionData[playerid][PlayerFaction] = playerData[playerid][pFaction];
    PlayerFactionData[playerid][PlayerFactionRank] = playerData[playerid][pRank];
    PlayerFactionData[playerid][PlayerOnDuty] = false;

    if (factionid == INVALID_FACTION) return 1;

    if (!Iter_Contains(FactionMembers[factionid], playerid))
        Iter_Add(FactionMembers[factionid], playerid);
    
    return 1;
}
