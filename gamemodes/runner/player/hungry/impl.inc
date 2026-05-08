#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

stock Float:GetPlayerHungry(playerid) {
    return playerData[playerid][pHungry];
}

stock Float:GetPlayerThirsty(playerid) {
    return playerData[playerid][pThirsty];
}

stock SetPlayerHungry(playerid, Float:value) {
    playerData[playerid][pHungry] = value;
    Query(get_handle()
        , "UPDATE "PLAYER_TABLE" SET `playerHungry` = '%.2f' WHERE `playerID` = '%i' LIMIT 1;"
        , playerData[playerid][pHungry]
        , playerData[playerid][pID]
    );
    return 1;
}

stock SetPlayerThirsty(playerid, Float:value) {
    playerData[playerid][pThirsty] = value;
    Query(get_handle()
        , "UPDATE "PLAYER_TABLE" SET `playerThirsty` = '%.2f' WHERE `playerID` = '%i' LIMIT 1;"
        , playerData[playerid][pThirsty]
        , playerData[playerid][pID]
    );
    return 1;
}

stock GivePlayerHungry(playerid, Float:value) {
    playerData[playerid][pHungry] += value;
    Query(get_handle()
        , "UPDATE "PLAYER_TABLE" SET `playerHungry` = '%.2f' WHERE `playerID` = '%i' LIMIT 1;"
        , playerData[playerid][pHungry]
        , playerData[playerid][pID]
    );
    return 1;
}

stock GivePlayerThirsty(playerid, Float:value) {
    playerData[playerid][pThirsty] += value;
    Query(get_handle()
        , "UPDATE "PLAYER_TABLE" SET `playerThirsty` = '%.2f' WHERE `playerID` = '%i' LIMIT 1;"
        , playerData[playerid][pThirsty]
        , playerData[playerid][pID]
    );
    return 1;
}

stock PlayerSpeed(playerid) {
    new Float:X, Float:Y, Float:Z;
    if (!IsPlayerInAnyVehicle(playerid)) GetPlayerVelocity(playerid, X, Y, Z);
    return floatround(floatsqroot(X * X + Y * Y + Z * Z) * 170.0);
}

public HungryTime(playerid) {
    new playerSpeed = PlayerSpeed(playerid);

    if (playerSpeed <= 0) {
        FullnessTick[playerid] += HUNGRY_TICK_IDLE;
    } else if (playerSpeed < 10) {
        FullnessTick[playerid] += HUNGRY_TICK_WALK;
    } else {
        FullnessTick[playerid] += playerSpeed / 3;
    }

    if (FullnessTick[playerid] < HUNGRY_TICK_MAX) return 1;

    FullnessTick[playerid] = 0;

    static Float:sHealth;
    new Hungry  = floatround(GetPlayerHungry(playerid));
    new Thirsty = floatround(GetPlayerThirsty(playerid));
    GetPlayerHealth(playerid, sHealth);

    SetPlayerHungry(playerid, GetPlayerHungry(playerid) - 0.7);
    SetPlayerThirsty(playerid, GetPlayerThirsty(playerid) - 0.5);

    switch (Hungry) {
        case 1 .. 20: {
            SetPlayerHealth(playerid, sHealth - 2.0);
            SendWarningMessage(playerid, "ค่าความหิวของคุณเหลือน้อยแล้ว รีบไปหาอะไรกินก่อนที่เลือดจะหมด");
        }
        case 0, -1: {
            SetPlayerHealth(playerid, sHealth - 3.0);
            SendWarningMessage(playerid, "ค่าความหิวของคุณไม่เหลือแล้ว เลือดจะลดมากขึ้น");
        }
    }
    switch (Thirsty) {
        case 1 .. 20: {
            SetPlayerHealth(playerid, sHealth - 2.0);
            SendWarningMessage(playerid, "ค่าน้ำของคุณเหลือน้อยแล้ว รีบไปหาอะไรดื่มก่อนที่เลือดจะหมด");
        }
        case 0, -1: {
            SetPlayerHealth(playerid, sHealth - 3.0);
            SendWarningMessage(playerid, "ค่าน้ำของคุณไม่เหลือแล้ว เลือดจะลดมากขึ้น");
        }
    }
    return 1;
}

hook OnPlayerConnect(playerid) {
    return 1;
}

hook OnPlayerSpawn(playerid) {
    KillTimer(HungryTimer[playerid]);
    HungryTimer[playerid] = SetTimerEx("HungryTime", 1000, true, "d", playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    KillTimer(HungryTimer[playerid]);
    HungryTimer[playerid] = 0;
    FullnessTick[playerid] = 0;
    return 1;
}