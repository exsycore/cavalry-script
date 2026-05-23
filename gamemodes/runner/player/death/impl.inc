#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

stock RescuePlayer(playerid) {
    if (!playerData[playerid][pInDeath]) return 0;

    playerData[playerid][pInDeath]     = 0;
    playerData[playerid][pInjuredTime] = 0;
    if ((playerData[playerid][pInjuredTimer]) != -1) {
        KillTimer(playerData[playerid][pInjuredTimer]);
        playerData[playerid][pInjuredTimer] = -1;
    }

    SetPlayerHealth(playerid, 50.0);
    TogglePlayerControllable(playerid, true);
    ClearAnimations(playerid);

    UpdatePlayerData(playerid);
    return 1;
}

stock StartInjured(playerid, bool:resetTime = true) {
    if ((playerData[playerid][pInjuredTimer]) != -1) {
        KillTimer(playerData[playerid][pInjuredTimer]);
        playerData[playerid][pInjuredTimer] = -1;
    }

    playerData[playerid][pInDeath] = 1;

    if (resetTime || playerData[playerid][pInjuredTime] <= 0) {
        playerData[playerid][pInjuredTime] = INJURED_TIME;
    }

    SetPlayerPos(playerid,
        playerData[playerid][pPosX],
        playerData[playerid][pPosY],
        playerData[playerid][pPosZ]
    );
    SetPlayerFacingAngle(playerid, playerData[playerid][pPosA]);
    SetPlayerHealth(playerid, 50.0);
    TogglePlayerControllable(playerid, false);
    ApplyAnimation(playerid, "WUZI", "CS_Dead_Guy", 4.1, 0, 1, 1, 1, 0, 1);

    new msg[64], name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));
    format(msg, sizeof(msg), "* %s ได้รับบาดเจ็บสาหัส ต้องการความช่วยเหลือ!", name);
    SendNearbyMessage(playerid, 10.0, COLOR_PURPLE, msg);

    playerData[playerid][pInjuredTimer] = SetTimerEx(
        "OnInjuredTick", 1000, true, "i", playerid
    );

    UpdatePlayerData(playerid);
    return 1;
}

hook OnPlayerConnect(playerid) {
    playerData[playerid][pInDeath]      = 0;
    playerData[playerid][pInjuredTimer] = -1;
    playerData[playerid][pInjuredTime]  = 0;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    if ((playerData[playerid][pInjuredTimer]) != -1) {
        KillTimer(playerData[playerid][pInjuredTimer]);
        playerData[playerid][pInjuredTimer] = -1;
    }
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason) {
    if (!GetPlayerLoggedIn(playerid)) return 1;

    GetPlayerPos(playerid,
        playerData[playerid][pPosX],
        playerData[playerid][pPosY],
        playerData[playerid][pPosZ]
    );
    GetPlayerFacingAngle(playerid, playerData[playerid][pPosA]);

    StartInjured(playerid, true); // reset เวลาใหม่
    return 1;
}

hook OnPlayerSpawn(playerid) {
    if (playerData[playerid][pInDeath] == 1) {
        StartInjured(playerid, false);
    }
    return 1;
}

hook OnLoginFinished(playerid) {
    if (playerData[playerid][pInDeath] == 1) {
        if (playerData[playerid][pInjuredTime] > 0) {
            StartInjured(playerid, false);
        } else {
            playerData[playerid][pInDeath] = 0;
            SetPlayerPos(playerid, DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z);
            SetPlayerFacingAngle(playerid, DEFAULT_POS_A);
            UpdatePlayerData(playerid);
        }
    }
    return 1;
}

public OnInjuredTick(playerid) {
    if (!playerData[playerid][pInDeath]) {
        if ((playerData[playerid][pInjuredTimer]) != -1) {
            KillTimer(playerData[playerid][pInjuredTimer]);
            playerData[playerid][pInjuredTimer] = -1;
        }
        return;
    }

    playerData[playerid][pInjuredTime]--;

    new str[48];
    format(str, sizeof(str), "~w~Respawn Time: ~r~%d ~w~sec",
        playerData[playerid][pInjuredTime]);
    GameTextForPlayer(playerid, str, 1100, 3);

    if (playerData[playerid][pInjuredTime] <= 0) {
        if ((playerData[playerid][pInjuredTimer]) != -1) {
            KillTimer(playerData[playerid][pInjuredTimer]);
            playerData[playerid][pInjuredTimer] = -1;
        }
        SetPlayerPos(playerid, DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z);
        SetPlayerFacingAngle(playerid, DEFAULT_POS_A);
        RescuePlayer(playerid);
    }
}
