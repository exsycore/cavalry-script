#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

stock CreatePlayerUI(playerid) {
    status_logo[playerid][0] = CreatePlayerTextDraw(playerid, 517.500000, 426.000000, "HUD:radar_burgershot");
    PlayerTextDrawFont(playerid, status_logo[playerid][0],              4);
    PlayerTextDrawLetterSize(playerid, status_logo[playerid][0],        0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, status_logo[playerid][0],          9.500000, 10.500000);
    PlayerTextDrawSetOutline(playerid, status_logo[playerid][0],        1);
    PlayerTextDrawSetShadow(playerid, status_logo[playerid][0],         0);
    PlayerTextDrawAlignment(playerid, status_logo[playerid][0],         1);
    PlayerTextDrawColor(playerid, status_logo[playerid][0],             -94);
    PlayerTextDrawBackgroundColor(playerid, status_logo[playerid][0],   255);
    PlayerTextDrawBoxColor(playerid, status_logo[playerid][0],          50);
    PlayerTextDrawUseBox(playerid, status_logo[playerid][0],            1);
    PlayerTextDrawSetProportional(playerid, status_logo[playerid][0],   1);
    PlayerTextDrawSetSelectable(playerid, status_logo[playerid][0],     0);

    status_logo[playerid][1] = CreatePlayerTextDraw(playerid, 534.500000, 426.000000, "HUD:radar_centre");
    PlayerTextDrawFont(playerid, status_logo[playerid][1],              4);
    PlayerTextDrawLetterSize(playerid, status_logo[playerid][1],        0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, status_logo[playerid][1],          9.500000, 10.500000);
    PlayerTextDrawSetOutline(playerid, status_logo[playerid][1],        1);
    PlayerTextDrawSetShadow(playerid, status_logo[playerid][1],         0);
    PlayerTextDrawAlignment(playerid, status_logo[playerid][1],         1);
    PlayerTextDrawColor(playerid, status_logo[playerid][1],             -94);
    PlayerTextDrawBackgroundColor(playerid, status_logo[playerid][1],   255);
    PlayerTextDrawBoxColor(playerid, status_logo[playerid][1],          50);
    PlayerTextDrawUseBox(playerid, status_logo[playerid][1],            1);
    PlayerTextDrawSetProportional(playerid, status_logo[playerid][1],   1);
    PlayerTextDrawSetSelectable(playerid, status_logo[playerid][1],     0);

    level_text[playerid] = CreatePlayerTextDraw(playerid, 530.000000, 439.000000, "LV: 100");
    PlayerTextDrawFont(playerid, level_text[playerid],                  2);
    PlayerTextDrawLetterSize(playerid, level_text[playerid],            0.104166, 0.900000);
    PlayerTextDrawTextSize(playerid, level_text[playerid],              620.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, level_text[playerid],            0);
    PlayerTextDrawSetShadow(playerid, level_text[playerid],             0);
    PlayerTextDrawAlignment(playerid, level_text[playerid],             3);
    PlayerTextDrawColor(playerid, level_text[playerid],                 -1);
    PlayerTextDrawBackgroundColor(playerid, level_text[playerid],       255);
    PlayerTextDrawBoxColor(playerid, level_text[playerid],              50);
    PlayerTextDrawUseBox(playerid, level_text[playerid],                0);
    PlayerTextDrawSetProportional(playerid, level_text[playerid],       1);
    PlayerTextDrawSetSelectable(playerid, level_text[playerid],         0);

    playerid_text[playerid] = CreatePlayerTextDraw(playerid, 635.000000, 414.000000, "ID: 1000");
    PlayerTextDrawFont(playerid, playerid_text[playerid],               2);
    PlayerTextDrawLetterSize(playerid, playerid_text[playerid],         0.104166, 0.900000);
    PlayerTextDrawTextSize(playerid, playerid_text[playerid],           620.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, playerid_text[playerid],         0);
    PlayerTextDrawSetShadow(playerid, playerid_text[playerid],          0);
    PlayerTextDrawAlignment(playerid, playerid_text[playerid],          3);
    PlayerTextDrawColor(playerid, playerid_text[playerid],              -1);
    PlayerTextDrawBackgroundColor(playerid, playerid_text[playerid],    255);
    PlayerTextDrawBoxColor(playerid, playerid_text[playerid],           50);
    PlayerTextDrawUseBox(playerid, playerid_text[playerid],             0);
    PlayerTextDrawSetProportional(playerid, playerid_text[playerid],    1);
    PlayerTextDrawSetSelectable(playerid, playerid_text[playerid],      0);

    HP_BAR[playerid]        = CreatePlayerProgressBar(playerid, 550.000000, 425.000000, 89.000000, 14.500000, -146922396, 100.000000, 0);
    THIRSTY_BAR[playerid]   = CreatePlayerProgressBar(playerid, 548.000000, 441.000000, 14.000000, 18.500000, 14535780, 100.000000, 2);
    HUNGRY_BAR[playerid]    = CreatePlayerProgressBar(playerid, 531.000000, 441.000000, 14.000000, 18.500000, -1429471132, 100.000000, 2);
    EXP_BAR[playerid]       = CreatePlayerProgressBar(playerid, 533.000000, 442.000000, 106.000000, 3.000000, -1428356865, 100.000000, 0);
    return 1;
}

stock UpdatePlayerUI(playerid) {
    if (!GetPlayerLoggedIn(playerid)) return 1;

    new str[32];
    format(str, sizeof str, "LV: %d",   playerData[playerid][pLevel]);
    PlayerTextDrawSetString(playerid,   level_text[playerid],       str);

    format(str, sizeof str, "ID: %d",   playerid);
    PlayerTextDrawSetString(playerid,   playerid_text[playerid],    str);

    new Float:hp;
    GetPlayerHealth(playerid, hp);
    SetPlayerProgressBarValue(playerid, HP_BAR[playerid],           hp);
    SetPlayerProgressBarValue(playerid, HUNGRY_BAR[playerid],       playerData[playerid][pHungry]);
    SetPlayerProgressBarValue(playerid, THIRSTY_BAR[playerid],      playerData[playerid][pThirsty]);
    SetPlayerProgressBarValue(playerid, EXP_BAR[playerid],          float(GetPlayerLevelProgress(playerid)));
    return 1;
}

stock ShowPlayerUI(playerid) {
    PlayerTextDrawShow(playerid,    status_logo[playerid][0]);
    PlayerTextDrawShow(playerid,    status_logo[playerid][1]);
    PlayerTextDrawShow(playerid,    level_text[playerid]);
    PlayerTextDrawShow(playerid,    playerid_text[playerid]);
    ShowPlayerProgressBar(playerid, HP_BAR[playerid]);
    ShowPlayerProgressBar(playerid, HUNGRY_BAR[playerid]);
    ShowPlayerProgressBar(playerid, THIRSTY_BAR[playerid]);
    ShowPlayerProgressBar(playerid, EXP_BAR[playerid]);
    return 1;
}

stock HidePlayerUI(playerid) {
    PlayerTextDrawHide(playerid,    status_logo[playerid][0]);
    PlayerTextDrawHide(playerid,    status_logo[playerid][1]);
    PlayerTextDrawHide(playerid,    level_text[playerid]);
    PlayerTextDrawHide(playerid,    playerid_text[playerid]);
    HidePlayerProgressBar(playerid, HP_BAR[playerid]);
    HidePlayerProgressBar(playerid, HUNGRY_BAR[playerid]);
    HidePlayerProgressBar(playerid, THIRSTY_BAR[playerid]);
    HidePlayerProgressBar(playerid, EXP_BAR[playerid]);
    return 1;
}

stock DestroyPlayerUI(playerid) {
    for (new i = 0; i < 2; i++) {
        if (IsValidDynamicPlayerTextDraw(playerid, status_logo[playerid][i])) {
            PlayerTextDrawDestroy(playerid, status_logo[playerid][i]);
        }
        status_logo[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (IsValidDynamicPlayerTextDraw(playerid, level_text[playerid])) {
        PlayerTextDrawDestroy(playerid, level_text[playerid]);
    }
    level_text[playerid] = PlayerText:INVALID_TEXT_DRAW;
    if (IsValidDynamicPlayerTextDraw(playerid, playerid_text[playerid])) {
        PlayerTextDrawDestroy(playerid, playerid_text[playerid]);
    }
    playerid_text[playerid] = PlayerText:INVALID_TEXT_DRAW;
    if (IsValidPlayerProgressBar(playerid, HP_BAR[playerid])) {
        DestroyPlayerProgressBar(playerid, HP_BAR[playerid]);
    }
    HP_BAR[playerid] = PlayerBar:INVALID_PLAYER_BAR_ID;
    if (IsValidPlayerProgressBar(playerid, HUNGRY_BAR[playerid])) {
        DestroyPlayerProgressBar(playerid, HUNGRY_BAR[playerid]);
    }
    HUNGRY_BAR[playerid] = PlayerBar:INVALID_PLAYER_BAR_ID;
    if (IsValidPlayerProgressBar(playerid, THIRSTY_BAR[playerid])) {
        DestroyPlayerProgressBar(playerid, THIRSTY_BAR[playerid]);
    }
    THIRSTY_BAR[playerid] = PlayerBar:INVALID_PLAYER_BAR_ID;
    if (IsValidPlayerProgressBar(playerid, EXP_BAR[playerid])) {
        DestroyPlayerProgressBar(playerid, EXP_BAR[playerid]);
    }
    EXP_BAR[playerid] = PlayerBar:INVALID_PLAYER_BAR_ID;
}

ptask UpdateUITimer[1000](playerid) {
    if (!GetPlayerLoggedIn(playerid)) return 1;
	UpdatePlayerUI(playerid);
    return 1;
}

hook OnPlayerConnect(playerid) {
    for (new i = 0; i < 2; i++) status_logo[playerid][i] = PlayerText:INVALID_TEXT_DRAW;

    level_text[playerid]    = PlayerText:INVALID_TEXT_DRAW;
    playerid_text[playerid] = PlayerText:INVALID_TEXT_DRAW;
    HP_BAR[playerid]        = PlayerBar:INVALID_PLAYER_BAR_ID;
    HUNGRY_BAR[playerid]    = PlayerBar:INVALID_PLAYER_BAR_ID;
    THIRSTY_BAR[playerid]   = PlayerBar:INVALID_PLAYER_BAR_ID;
    EXP_BAR[playerid]       = PlayerBar:INVALID_PLAYER_BAR_ID;

    CreatePlayerUI(playerid);
    return 1;
}

hook OnPlayerSpawn(playerid) {
    if (!GetPlayerLoggedIn(playerid)) return 1;
    UpdatePlayerUI(playerid);
    ShowPlayerUI(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    DestroyPlayerUI(playerid);
    return 1;
}
