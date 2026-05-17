#if defined _inc_impl
#undef
#endif

#include <YSI_Coding\y_hooks>

stock GetExpRequired(level) {
    if (level <= 0)         return 0;
    if (level >= MAX_PLAYER_LEVELS) return 0;

    return floatround(LEVEL_BASE * floatpower(float(level), LEVEL_EXPONENT));
}

stock GetExpRequiredTotal(level) {
    if (level <= 1) return 0;

    new total = 0;
    for (new i = 1; i < level; i++)
        total += GetExpRequired(i);
    return total;
}

stock CheckPlayerLevelUp(playerid) {
    if (!GetPlayerLoggedIn(playerid)) return 0;

    new level   = playerData[playerid][pLevel];
    new exp     = playerData[playerid][pExp];
    new changed = 0;

    if (level >= MAX_PLAYER_LEVELS) {
        playerData[playerid][pLevel] = MAX_PLAYER_LEVELS;
        return 0;
    }

    while (level < MAX_PLAYER_LEVELS) {
        new required = GetExpRequired(level);
        if (exp < required) break;

        exp -= required;
        level ++;
        changed++;
    }

    if (changed) {
        playerData[playerid][pLevel] = level;
        playerData[playerid][pExp]   = exp;

        Query(get_handle(),
            "UPDATE "PLAYER_TABLE" SET `playerLevel` = '%d', `playerExp` = '%d' WHERE `playerID` = '%d'",
            playerData[playerid][pLevel],
            playerData[playerid][pExp],
            playerData[playerid][pID]
        );

        SetPlayerScore(playerid, playerData[playerid][pLevel]);

        for (new i = 0; i < changed; i++) {
            new lv = playerData[playerid][pLevel] - (changed - 1 - i);
            va_SendClientMessage(playerid, COLOR_GREEN,
                "[Congrat]: {FFFFFF}คุณขึ้นเป็น Level {FFD700}%d {FFFFFF}แล้ว! (ต้องการ EXP ถัดไป: {AAFFAA}%d{FFFFFF})",
                lv,
                lv < MAX_PLAYER_LEVELS ? GetExpRequired(lv) : 0
            );
        }

        if (playerData[playerid][pLevel] >= MAX_PLAYER_LEVELS) {
            va_SendClientMessage(playerid, COLOR_RED,
                "[ข้อผิดพลาด]: {FFFFFF}คุณถึง Level สูงสุด {FF4444}%d {FFFFFF}แล้ว! (บอสแมพ)",
                MAX_PLAYER_LEVELS
            );
        }
    }
    return changed;
}

stock GetPlayerExpToNextLevel(playerid) {
    new level = playerData[playerid][pLevel];
    if (level >= MAX_PLAYER_LEVELS) return 0;
    return GetExpRequired(level) - playerData[playerid][pExp];
}

stock GetPlayerLevelProgress(playerid) {
    new level = playerData[playerid][pLevel];
    if (level >= MAX_PLAYER_LEVELS) return 100;

    new required = GetExpRequired(level);
    if (required <= 0) return 100;

    return floatround(float(playerData[playerid][pExp]) / float(required) * 100.0);
}

stock GetPlayerExp(playerid) {
	return playerData[playerid][pExp];
}

stock GetPlayerLevel(playerid) {
	return playerData[playerid][pLevel];
}

stock SetPlayerExp(playerid, exp) {
    if (exp < 0) exp = 0;
    playerData[playerid][pExp] = exp;
    SetPlayerScore(playerid, playerData[playerid][pLevel]);
    Query(get_handle(),
        "UPDATE "PLAYER_TABLE" SET `playerExp` = '%d' WHERE `playerID` = '%d'",
        playerData[playerid][pExp],
        playerData[playerid][pID]
    );
    return 1;
}

stock GivePlayerExp(playerid, exp) {
    if (playerData[playerid][pLevel] >= MAX_PLAYER_LEVELS) return 0;

    playerData[playerid][pExp] += exp;
    if (playerData[playerid][pExp] < 0)
        playerData[playerid][pExp] = 0;

    SetPlayerScore(playerid, playerData[playerid][pLevel]);

    CheckPlayerLevelUp(playerid);
    return 1;
}

stock SetPlayerLevel(playerid, level) {
    if (level < 0)          level = 0;
    if (level > MAX_PLAYER_LEVELS)  level = MAX_PLAYER_LEVELS;

    playerData[playerid][pLevel] = level;
    playerData[playerid][pExp]   = 0;
    SetPlayerScore(playerid, playerData[playerid][pLevel]);
    Query(get_handle(),
        "UPDATE "PLAYER_TABLE" SET `playerLevel` = '%d', `playerExp` = '0' WHERE `playerID` = '%d'",
        playerData[playerid][pLevel],
        playerData[playerid][pID]
    );
    return 1;
}

stock GivePlayerLevel(playerid, level) {
    new newlevel = playerData[playerid][pLevel] + level;
    if (newlevel < 0)          newlevel = 0;
    if (newlevel > MAX_PLAYER_LEVELS)  newlevel = MAX_PLAYER_LEVELS;

    playerData[playerid][pLevel] = newlevel;
    playerData[playerid][pExp]   = 0;
    SetPlayerScore(playerid, playerData[playerid][pLevel]);
    Query(get_handle(),
        "UPDATE "PLAYER_TABLE" SET `playerLevel` = '%d', `playerExp` = '0' WHERE `playerID` = '%d'",
        playerData[playerid][pLevel],
        playerData[playerid][pID]
    );
    return 1;
}

stock ShowPlayerExpInfo(playerid, targetid) {
    new level    = playerData[targetid][pLevel];
    new exp      = playerData[targetid][pExp];
    new required = (level < MAX_PLAYER_LEVELS) ? GetExpRequired(level) : 0;
    new progress = GetPlayerLevelProgress(targetid);

    va_SendClientMessage(playerid, -1,
        "{FFFF00}[ EXP ] {FFFFFF}%s | Lv.{FFFF00}%d {FFFFFF}| EXP: {AAFFAA}%d{FFFFFF}/{AAFFAA}%d {FFFFFF}| Progress: {FFFF00}%d%%",
        ReturnPlayerRPName(targetid),
        level,
        exp,
        required,
        progress
    );
}