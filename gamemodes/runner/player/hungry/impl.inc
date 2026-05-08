#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

stock loadedStatusUI(playerid) {
    statusUI[playerid][0] = CreatePlayerTextDraw(playerid, 535.000000, 413.000000, "ld_beat:chit");
    PlayerTextDrawFont(playerid, statusUI[playerid][0], 4);
    PlayerTextDrawLetterSize(playerid, statusUI[playerid][0], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, statusUI[playerid][0], 26.500000, 33.000000);
    PlayerTextDrawSetOutline(playerid, statusUI[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, statusUI[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, statusUI[playerid][0], 1);
    PlayerTextDrawColor(playerid, statusUI[playerid][0], 774778879);
    PlayerTextDrawBackgroundColor(playerid, statusUI[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, statusUI[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, statusUI[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, statusUI[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, statusUI[playerid][0], 0);

    statusUI[playerid][1] = CreatePlayerTextDraw(playerid, 609.000000, 413.000000, "ld_beat:chit");
    PlayerTextDrawFont(playerid, statusUI[playerid][1], 4);
    PlayerTextDrawLetterSize(playerid, statusUI[playerid][1], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, statusUI[playerid][1], 26.500000, 33.000000);
    PlayerTextDrawSetOutline(playerid, statusUI[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, statusUI[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, statusUI[playerid][1], 1);
    PlayerTextDrawColor(playerid, statusUI[playerid][1], 774778879);
    PlayerTextDrawBackgroundColor(playerid, statusUI[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, statusUI[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, statusUI[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, statusUI[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, statusUI[playerid][1], 0);

    statusUI[playerid][2] = CreatePlayerTextDraw(playerid, 615.000000, 421.000000, "HUD:radar_burgershot");
    PlayerTextDrawFont(playerid, statusUI[playerid][2], 4);
    PlayerTextDrawLetterSize(playerid, statusUI[playerid][2], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, statusUI[playerid][2], 14.500000, 15.500000);
    PlayerTextDrawSetOutline(playerid, statusUI[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, statusUI[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, statusUI[playerid][2], 1);
    PlayerTextDrawColor(playerid, statusUI[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, statusUI[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, statusUI[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, statusUI[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, statusUI[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, statusUI[playerid][2], 0);

    statusUI[playerid][3] = CreatePlayerTextDraw(playerid, 541.000000, 421.000000, "HUD:radar_diner");
    PlayerTextDrawFont(playerid, statusUI[playerid][3], 4);
    PlayerTextDrawLetterSize(playerid, statusUI[playerid][3], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, statusUI[playerid][3], 14.500000, 15.500000);
    PlayerTextDrawSetOutline(playerid, statusUI[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, statusUI[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, statusUI[playerid][3], 1);
    PlayerTextDrawColor(playerid, statusUI[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, statusUI[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, statusUI[playerid][3], 50);
    PlayerTextDrawUseBox(playerid, statusUI[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, statusUI[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, statusUI[playerid][3], 0);

    hungryProgressbar[playerid] = CreatePlayerProgressBar(playerid, 556.000000, 425.000000, 62.000000, 4.000000, 1119680511, 100.000000, 0);
    SetPlayerProgressBarMaxValue(playerid, hungryProgressbar[playerid], 100.00);
    thirstyProgressbar[playerid] = CreatePlayerProgressBar(playerid, 617.000000, 432.000000, 59.500000, 4.000000, -411098625, 100.000000, 1);
    SetPlayerProgressBarMaxValue(playerid, thirstyProgressbar[playerid], 100.00);
    return 1;
}

stock DestroyStatusUI(playerid) {
    for (new i = 0; i < 4; i++) {
        if (IsValidDynamicPlayerTextDraw(playerid, statusUI[playerid][i])) {
            PlayerTextDrawDestroy(playerid, statusUI[playerid][i]);
        }
        statusUI[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (IsValidPlayerProgressBar(playerid, hungryProgressbar[playerid])) {
        DestroyPlayerProgressBar(playerid, hungryProgressbar[playerid]);
    }
    hungryProgressbar[playerid] = PlayerBar:INVALID_PLAYER_BAR_ID;

    if (IsValidPlayerProgressBar(playerid, thirstyProgressbar[playerid])) {
        DestroyPlayerProgressBar(playerid, thirstyProgressbar[playerid]);
    }
    thirstyProgressbar[playerid] = PlayerBar:INVALID_PLAYER_BAR_ID;
}

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

stock ShowStatusUI(playerid, bool:toggles) {
    if (toggles) {
        if (StatusUIStatus[playerid] == 1) return 1;

        StatusUIStatus[playerid] = 1;

        for (new i = 0; i < 4; i++) {
            if (IsValidDynamicPlayerTextDraw(playerid, statusUI[playerid][i])) PlayerTextDrawShow(playerid, statusUI[playerid][i]);
        }

        SetPlayerProgressBarValue(playerid, hungryProgressbar[playerid], GetPlayerHungry(playerid));
        ShowPlayerProgressBar(playerid, hungryProgressbar[playerid]);
        SetPlayerProgressBarValue(playerid, thirstyProgressbar[playerid], GetPlayerThirsty(playerid));
        ShowPlayerProgressBar(playerid, thirstyProgressbar[playerid]);
    } else {
        if (StatusUIStatus[playerid] == 0) return 1;

        StatusUIStatus[playerid] = 0;
        for (new i = 0; i < 4; i++) {
            if (IsValidDynamicPlayerTextDraw(playerid, statusUI[playerid][i])) PlayerTextDrawHide(playerid, statusUI[playerid][i]);
        }

        HidePlayerProgressBar(playerid, hungryProgressbar[playerid]);
        HidePlayerProgressBar(playerid, thirstyProgressbar[playerid]);
    }
    return 1;
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

    SetPlayerProgressBarValue(playerid, hungryProgressbar[playerid], GetPlayerThirsty(playerid));
    SetPlayerProgressBarValue(playerid, thirstyProgressbar[playerid], GetPlayerHungry(playerid));

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
    for (new i = 0; i < 4; i++) statusUI[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
    hungryProgressbar[playerid]  = PlayerBar:INVALID_PLAYER_BAR_ID;
    thirstyProgressbar[playerid] = PlayerBar:INVALID_PLAYER_BAR_ID;
    StatusUIStatus[playerid] = 0;

    loadedStatusUI(playerid);
    return 1;
}

hook OnPlayerSpawn(playerid) {
    KillTimer(HungryTimer[playerid]);
    ShowStatusUI(playerid, true);
    HungryTimer[playerid] = SetTimerEx("HungryTime", 1000, true, "d", playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    KillTimer(HungryTimer[playerid]);
    HungryTimer[playerid] = 0;
    FullnessTick[playerid] = 0;
    StatusUIStatus[playerid] = 0;

    DestroyStatusUI(playerid);
    return 1;
}