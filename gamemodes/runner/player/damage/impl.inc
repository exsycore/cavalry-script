#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

static Float:_WD_CalcDamage(issuerid, victimid, cw, bodypart) {
    new Float:base = g_WeaponTable[cw][CW_Damage];

    if (g_WeaponTable[cw][CW_DamageType] == DAMAGE_TYPE_RANGE && g_WeaponTable[cw][CW_Range] > 0.0) {
        new Float:ix, Float:iy, Float:iz, Float:vx, Float:vy, Float:vz;
        GetPlayerPos(issuerid, ix, iy, iz);
        GetPlayerPos(victimid, vx, vy, vz);
        new Float:dist = floatsqroot(
            (ix - vx) * (ix - vx) +
            (iy - vy) * (iy - vy) +
            (iz - vz) * (iz - vz)
        );
        if (dist > g_WeaponTable[cw][CW_Range]) base *= 0.70;
    }

    if (g_WeaponTable[cw][CW_HeadshotBonus] && bodypart == BODY_PART_HEAD) {
        base *= g_WeaponTable[cw][CW_HeadshotMult];
    }

    return base;
}

stock SetPlayerCustomWeapon(playerid, cwIndex) {
    if (cwIndex < -1 || cwIndex >= MAX_CUSTOM_WEAPONS) return 0;
    g_PlayerCustomWeapon[playerid] = cwIndex;
    return 1;
}

stock ResetPlayerCustomWeapon(playerid) {
    g_PlayerCustomWeapon[playerid] = -1;
}

stock GetPlayerCustomWeaponIndex(playerid) {
    return g_PlayerCustomWeapon[playerid];
}

stock FindCustomWeaponByName(const name[]) {
    new tmp[32];
    for (new i = 0; i < MAX_CUSTOM_WEAPONS; i++) {
        strmid(tmp, g_WeaponTable[i][CW_Name], 0, sizeof(tmp));
        if (!strcmp(tmp, name, true)) return i;
    }
    return -1;
}

stock GetPlayerWeaponDisplayName(playerid, output[], len = sizeof(output)) {
    new cw = g_PlayerCustomWeapon[playerid];
    if (cw == -1) {
        new WEAPON:wid = WEAPON:GetPlayerWeapon(playerid);
        GetWeaponName(wid, output, len);
    } else {
        strmid(output, g_WeaponTable[cw][CW_Name], 0, len);
    }
    return 1;
}

hook OnGameModeInit() {
    // weapon-config
	SetCbugAllowed(true);
    SetVehiclePassengerDamage(true);
    SetDisableSyncBugs(true);
    SetDamageFeed(true);
    SetDamageSounds(false, false);
    SetCustomArmourRules(true, true);
    SetCustomFallDamage(true, 25.0, -0.6);

    SetWeaponDamage(WEAPON:WEAPON_BRASSKNUCKLE, DAMAGE_TYPE_MULTIPLIER, 1.2);
    SetWeaponDamage(WEAPON:WEAPON_GOLFCLUB,     DAMAGE_TYPE_MULTIPLIER, 1.5);
    SetWeaponDamage(WEAPON:WEAPON_NITESTICK,    DAMAGE_TYPE_MULTIPLIER, 1.3);
    SetWeaponDamage(WEAPON:WEAPON_KNIFE,        DAMAGE_TYPE_MULTIPLIER, 1.0);
    SetWeaponDamage(WEAPON:WEAPON_BAT,          DAMAGE_TYPE_MULTIPLIER, 1.4);
    SetWeaponDamage(WEAPON:WEAPON_SHOVEL,       DAMAGE_TYPE_MULTIPLIER, 1.3);
    SetWeaponDamage(WEAPON:WEAPON_POOLSTICK,    DAMAGE_TYPE_MULTIPLIER, 1.2);
    SetWeaponDamage(WEAPON:WEAPON_KATANA,       DAMAGE_TYPE_MULTIPLIER, 2.0);
    SetWeaponDamage(WEAPON:WEAPON_CHAINSAW,     DAMAGE_TYPE_MULTIPLIER, 3.0);

    SetWeaponDamage(WEAPON:WEAPON_COLT45,   DAMAGE_TYPE_STATIC, 22.0);
    SetWeaponDamage(WEAPON:WEAPON_SILENCED, DAMAGE_TYPE_STATIC, 28.0);
    SetWeaponDamage(WEAPON:WEAPON_DEAGLE,   DAMAGE_TYPE_STATIC, 35.0);

    SetWeaponDamage(WEAPON:WEAPON_SHOTGUN,  DAMAGE_TYPE_STATIC,  8.0);
    SetWeaponDamage(WEAPON:WEAPON_SAWEDOFF, DAMAGE_TYPE_STATIC, 10.0);
    SetWeaponDamage(WEAPON:WEAPON_SHOTGSPA, DAMAGE_TYPE_STATIC, 12.0);

    SetWeaponDamage(WEAPON:WEAPON_UZI,  DAMAGE_TYPE_STATIC, 18.0);
    SetWeaponDamage(WEAPON:WEAPON_MP5,  DAMAGE_TYPE_STATIC, 20.0);
    SetWeaponDamage(WEAPON:WEAPON_TEC9, DAMAGE_TYPE_STATIC, 18.0);

    SetWeaponDamage(WEAPON:WEAPON_AK47, DAMAGE_TYPE_STATIC, 34.0);
    SetWeaponDamage(WEAPON:WEAPON_M4,   DAMAGE_TYPE_STATIC, 30.0);

    SetWeaponDamage(WEAPON:WEAPON_RIFLE,
        DAMAGE_TYPE_RANGE, 45.0,  80.0,
                           40.0, 150.0,
                           30.0);
    SetWeaponDamage(WEAPON:WEAPON_SNIPER,
        DAMAGE_TYPE_RANGE, 55.0,  50.0,
                           50.0, 200.0,
                           40.0);
    
    SetWeaponArmourRule(WEAPON:WEAPON_COLT45,    true,  false);
    SetWeaponArmourRule(WEAPON:WEAPON_SILENCED,  true,  false);
    SetWeaponArmourRule(WEAPON:WEAPON_DEAGLE,    true,  false);
    SetWeaponArmourRule(WEAPON:WEAPON_UZI,       true,  false);
    SetWeaponArmourRule(WEAPON:WEAPON_MP5,       true,  true);
    SetWeaponArmourRule(WEAPON:WEAPON_TEC9,      true,  false);
    SetWeaponArmourRule(WEAPON:WEAPON_AK47,      true,  true);
    SetWeaponArmourRule(WEAPON:WEAPON_M4,        true,  true);
    SetWeaponArmourRule(WEAPON:WEAPON_RIFLE,     true,  true);
    SetWeaponArmourRule(WEAPON:WEAPON_SNIPER,    true,  false);
    SetWeaponArmourRule(WEAPON:WEAPON_SHOTGUN,   true,  true);
    SetWeaponArmourRule(WEAPON:WEAPON_SAWEDOFF,  true,  true);
    SetWeaponArmourRule(WEAPON:WEAPON_SHOTGSPA,  true,  true);
    SetWeaponArmourRule(WEAPON:WEAPON_KNIFE,     false, false);
    SetWeaponArmourRule(WEAPON:WEAPON_BAT,       false, false);
    SetWeaponArmourRule(WEAPON:WEAPON_KATANA,    false, false);
    SetWeaponArmourRule(WEAPON:WEAPON_CHAINSAW,  false, false);

    printf("[WD] Weapon Damage System initialised. Custom weapons: %d", MAX_CUSTOM_WEAPONS);
    return 1;
}

hook OnPlayerDamage(&playerid, &Float:amount, &issuerid, &weapon, &bodypart) {
    if (!GetPlayerLoggedIn(playerid)) return 1;

    if (issuerid != INVALID_PLAYER_ID) {
        new cw = g_PlayerCustomWeapon[issuerid];
        if (cw != -1 && g_WeaponTable[cw][CW_BaseWeaponID] == weapon) {
            amount = _WD_CalcDamage(issuerid, playerid, cw, bodypart);
            SetWeaponArmourRule(
                WEAPON:weapon,
                g_WeaponTable[cw][CW_AffectsArmour],
                g_WeaponTable[cw][CW_TorsoOnly]
            );
        }
    }
    return 1;
}

hook OnPlayerDamageDone(playerid, Float:amount, issuerid, WEAPON:weapon, bodypart) {
    if (!GetPlayerLoggedIn(playerid)) return 1;

    new issuerName[MAX_PLAYER_NAME], victimName[MAX_PLAYER_NAME];
    new weapName[32];

    GetPlayerName(playerid,  victimName,  MAX_PLAYER_NAME);
    GetPlayerName(issuerid,  issuerName,  MAX_PLAYER_NAME);

    if (issuerid != INVALID_PLAYER_ID) {
        new cw = g_PlayerCustomWeapon[issuerid];
        if (cw != -1) strmid(weapName, g_WeaponTable[cw][CW_Name], 0, sizeof(weapName));
        else GetWeaponName(weapon, weapName, sizeof(weapName));
    } else {
        GetWeaponName(weapon, weapName, sizeof(weapName));
    }

    // printf("[DMG] %s ? %s | %.1f HP | %s | bodypart:%d", issuerName, victimName, amount, weapName, bodypart);
    return 1;
}

hook OnPlayerConnect(playerid) {
    g_PlayerCustomWeapon[playerid] = -1;
    return 1;
}

hook OnPlayerUpdate(playerid) {
    new weapon = GetPlayerWeapon(playerid);
    if (weapon != GetPVarInt(playerid, "iCurrentWeapon")) {
        CallLocalFunction("OnPlayerChangeWeapon", "iii", playerid, GetPVarInt(playerid, "iCurrentWeapon"), weapon);
        SetPVarInt(playerid, "iCurrentWeapon", weapon);
    }
    return 1;
}

public OnPlayerChangeWeapon(playerid, oldweapon, newweapon) {
    new cw = GetPlayerCustomWeaponIndex(playerid);

    if (cw != -1) {
        if (g_WeaponTable[cw][CW_BaseWeaponID] != newweapon) {
            ResetPlayerCustomWeapon(playerid);
        }
    } else {
        for (new i = 0; i < MAX_INVENTORY_SLOTS; i++) {
            new idx = playerData[playerid][pInventory][i];
            if (idx <= 0) continue;

            new itemName[128];
            strmid(itemName, ItemsInfo[idx][ItemName2], 0, sizeof(itemName));

            new cwIndex = FindCustomWeaponByName(itemName);
            if (cwIndex == -1) continue;

            if (g_WeaponTable[cwIndex][CW_BaseWeaponID] == newweapon) {
                SetPlayerCustomWeapon(playerid, cwIndex);
                break;
            }
        }
    }
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason) {
    ResetPlayerWeapons(playerid);
    ResetPlayerCustomWeapon(playerid);
    return 1;
}

YCMD:setcw(playerid, string:params[], help) {
    if (!IsPlayerAdminEx(playerid)) return SendClientMessage(playerid, -1, "Admin only.");
    new idx;
    if (sscanf(params, "i", idx)) return SendClientMessage(playerid, -1, "Usage: /setcw [index]");
    if (idx < 0 || idx >= MAX_CUSTOM_WEAPONS) return SendClientMessage(playerid, -1, "Index ไม่ถูกต้อง");
    SetPlayerCustomWeapon(playerid, idx);
    new msg[64];
    format(msg, sizeof(msg), "[WD] Equipped: %s", g_WeaponTable[idx][CW_Name]);
    SendClientMessage(playerid, 0x00FF00FF, msg);
    return 1;
}

YCMD:clearcw(playerid, string:params[], help) {
    ResetPlayerCustomWeapon(playerid);
    SendClientMessage(playerid, 0xFFFFFFFF, "[WD] Custom weapon cleared.");
    return 1;
}

YCMD:cwlist(playerid, string:params[], help) {
    SendClientMessage(playerid, 0xFFFFFFAA, "=== Custom Weapon List ===");
    new msg[64];
    for (new i = 0; i < MAX_CUSTOM_WEAPONS; i++) {
        format(msg, sizeof(msg), "[%02d] %s (baseID:%d | %.1fdmg)",
            i, g_WeaponTable[i][CW_Name],
            g_WeaponTable[i][CW_BaseWeaponID],
            g_WeaponTable[i][CW_Damage]);
        SendClientMessage(playerid, 0xFFFFFFFF, msg);
    }
    return 1;
}
