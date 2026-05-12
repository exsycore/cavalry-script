#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

stock CreatePlayerUI(playerid) {
    uimain[playerid][0] = CreatePlayerTextDraw(playerid, 529.000000, 378.000000, "ld_dual:white");
    PlayerTextDrawFont(playerid, uimain[playerid][0], 4);
    PlayerTextDrawLetterSize(playerid, uimain[playerid][0], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, uimain[playerid][0], 104.500000, 61.000000);
    PlayerTextDrawSetOutline(playerid, uimain[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, uimain[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, uimain[playerid][0], 1);
    PlayerTextDrawColor(playerid, uimain[playerid][0], 67372031);
    PlayerTextDrawBackgroundColor(playerid, uimain[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, uimain[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, uimain[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, uimain[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, uimain[playerid][0], 0);

    uimain[playerid][1] = CreatePlayerTextDraw(playerid, 522.000000, 370.000000, "ld_beat:chit");
    PlayerTextDrawFont(playerid, uimain[playerid][1], 4);
    PlayerTextDrawLetterSize(playerid, uimain[playerid][1], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, uimain[playerid][1], 15.500000, 19.000000);
    PlayerTextDrawSetOutline(playerid, uimain[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, uimain[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, uimain[playerid][1], 1);
    PlayerTextDrawColor(playerid, uimain[playerid][1], 67372031);
    PlayerTextDrawBackgroundColor(playerid, uimain[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, uimain[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, uimain[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, uimain[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, uimain[playerid][1], 0);

    uimain[playerid][2] = CreatePlayerTextDraw(playerid, 522.000000, 428.000000, "ld_beat:chit");
    PlayerTextDrawFont(playerid, uimain[playerid][2], 4);
    PlayerTextDrawLetterSize(playerid, uimain[playerid][2], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, uimain[playerid][2], 15.500000, 19.000000);
    PlayerTextDrawSetOutline(playerid, uimain[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, uimain[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, uimain[playerid][2], 1);
    PlayerTextDrawColor(playerid, uimain[playerid][2], 67372031);
    PlayerTextDrawBackgroundColor(playerid, uimain[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, uimain[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, uimain[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, uimain[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, uimain[playerid][2], 0);

    uimain[playerid][3] = CreatePlayerTextDraw(playerid, 625.000000, 428.000000, "ld_beat:chit");
    PlayerTextDrawFont(playerid, uimain[playerid][3], 4);
    PlayerTextDrawLetterSize(playerid, uimain[playerid][3], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, uimain[playerid][3], 15.500000, 19.000000);
    PlayerTextDrawSetOutline(playerid, uimain[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, uimain[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, uimain[playerid][3], 1);
    PlayerTextDrawColor(playerid, uimain[playerid][3], 67372031);
    PlayerTextDrawBackgroundColor(playerid, uimain[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, uimain[playerid][3], 50);
    PlayerTextDrawUseBox(playerid, uimain[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, uimain[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, uimain[playerid][3], 0);

    uimain[playerid][4] = CreatePlayerTextDraw(playerid, 625.000000, 370.000000, "ld_beat:chit");
    PlayerTextDrawFont(playerid, uimain[playerid][4], 4);
    PlayerTextDrawLetterSize(playerid, uimain[playerid][4], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, uimain[playerid][4], 15.500000, 19.000000);
    PlayerTextDrawSetOutline(playerid, uimain[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, uimain[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, uimain[playerid][4], 1);
    PlayerTextDrawColor(playerid, uimain[playerid][4], 67372031);
    PlayerTextDrawBackgroundColor(playerid, uimain[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, uimain[playerid][4], 50);
    PlayerTextDrawUseBox(playerid, uimain[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, uimain[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, uimain[playerid][4], 0);

    uimain[playerid][5] = CreatePlayerTextDraw(playerid, 529.000000, 373.500000, "ld_dual:white");
    PlayerTextDrawFont(playerid, uimain[playerid][5], 4);
    PlayerTextDrawLetterSize(playerid, uimain[playerid][5], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, uimain[playerid][5], 104.500000, 8.500000);
    PlayerTextDrawSetOutline(playerid, uimain[playerid][5], 1);
    PlayerTextDrawSetShadow(playerid, uimain[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, uimain[playerid][5], 1);
    PlayerTextDrawColor(playerid, uimain[playerid][5], 67372031);
    PlayerTextDrawBackgroundColor(playerid, uimain[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, uimain[playerid][5], 50);
    PlayerTextDrawUseBox(playerid, uimain[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, uimain[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, uimain[playerid][5], 0);

    uimain[playerid][6] = CreatePlayerTextDraw(playerid, 524.500000, 379.000000, "ld_dual:white");
    PlayerTextDrawFont(playerid, uimain[playerid][6], 4);
    PlayerTextDrawLetterSize(playerid, uimain[playerid][6], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, uimain[playerid][6], 9.000000, 58.500000);
    PlayerTextDrawSetOutline(playerid, uimain[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, uimain[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, uimain[playerid][6], 1);
    PlayerTextDrawColor(playerid, uimain[playerid][6], 67372031);
    PlayerTextDrawBackgroundColor(playerid, uimain[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, uimain[playerid][6], 50);
    PlayerTextDrawUseBox(playerid, uimain[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, uimain[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, uimain[playerid][6], 0);

    uimain[playerid][7] = CreatePlayerTextDraw(playerid, 529.000000, 435.000000, "ld_dual:white");
    PlayerTextDrawFont(playerid, uimain[playerid][7], 4);
    PlayerTextDrawLetterSize(playerid, uimain[playerid][7], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, uimain[playerid][7], 104.500000, 8.500000);
    PlayerTextDrawSetOutline(playerid, uimain[playerid][7], 1);
    PlayerTextDrawSetShadow(playerid, uimain[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, uimain[playerid][7], 1);
    PlayerTextDrawColor(playerid, uimain[playerid][7], 67372031);
    PlayerTextDrawBackgroundColor(playerid, uimain[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, uimain[playerid][7], 50);
    PlayerTextDrawUseBox(playerid, uimain[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, uimain[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, uimain[playerid][7], 0);

    uimain[playerid][8] = CreatePlayerTextDraw(playerid, 629.000000, 379.000000, "ld_dual:white");
    PlayerTextDrawFont(playerid, uimain[playerid][8], 4);
    PlayerTextDrawLetterSize(playerid, uimain[playerid][8], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, uimain[playerid][8], 9.000000, 58.500000);
    PlayerTextDrawSetOutline(playerid, uimain[playerid][8], 1);
    PlayerTextDrawSetShadow(playerid, uimain[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, uimain[playerid][8], 1);
    PlayerTextDrawColor(playerid, uimain[playerid][8], 67372031);
    PlayerTextDrawBackgroundColor(playerid, uimain[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, uimain[playerid][8], 50);
    PlayerTextDrawUseBox(playerid, uimain[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, uimain[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, uimain[playerid][8], 0);

    uimain[playerid][9] = CreatePlayerTextDraw(playerid, 529.000000, 389.500000, "ld_dual:white");
    PlayerTextDrawFont(playerid, uimain[playerid][9], 4);
    PlayerTextDrawLetterSize(playerid, uimain[playerid][9], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, uimain[playerid][9], 104.500000, 0.500000);
    PlayerTextDrawSetOutline(playerid, uimain[playerid][9], 1);
    PlayerTextDrawSetShadow(playerid, uimain[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, uimain[playerid][9], 1);
    PlayerTextDrawColor(playerid, uimain[playerid][9], 808464639);
    PlayerTextDrawBackgroundColor(playerid, uimain[playerid][9], 255);
    PlayerTextDrawBoxColor(playerid, uimain[playerid][9], 50);
    PlayerTextDrawUseBox(playerid, uimain[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, uimain[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, uimain[playerid][9], 0);

    uimain[playerid][10] = CreatePlayerTextDraw(playerid, 529.000000, 377.000000, "ID:");
    PlayerTextDrawFont(playerid, uimain[playerid][10], 1);
    PlayerTextDrawLetterSize(playerid, uimain[playerid][10], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, uimain[playerid][10], 682.000000, 16.000000);
    PlayerTextDrawSetOutline(playerid, uimain[playerid][10], 0);
    PlayerTextDrawSetShadow(playerid, uimain[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, uimain[playerid][10], 1);
    PlayerTextDrawColor(playerid, uimain[playerid][10], -1);
    PlayerTextDrawBackgroundColor(playerid, uimain[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, uimain[playerid][10], 50);
    PlayerTextDrawUseBox(playerid, uimain[playerid][10], 0);
    PlayerTextDrawSetProportional(playerid, uimain[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, uimain[playerid][10], 0);

    ui_player_id_text[playerid] = CreatePlayerTextDraw(playerid, 539.000000, 377.000000, "1000");
    PlayerTextDrawFont(playerid, ui_player_id_text[playerid], 1);
    PlayerTextDrawLetterSize(playerid, ui_player_id_text[playerid], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, ui_player_id_text[playerid], 682.000000, 16.000000);
    PlayerTextDrawSetOutline(playerid, ui_player_id_text[playerid], 0);
    PlayerTextDrawSetShadow(playerid, ui_player_id_text[playerid], 0);
    PlayerTextDrawAlignment(playerid, ui_player_id_text[playerid], 1);
    PlayerTextDrawColor(playerid, ui_player_id_text[playerid], -872414977);
    PlayerTextDrawBackgroundColor(playerid, ui_player_id_text[playerid], 255);
    PlayerTextDrawBoxColor(playerid, ui_player_id_text[playerid], 50);
    PlayerTextDrawUseBox(playerid, ui_player_id_text[playerid], 0);
    PlayerTextDrawSetProportional(playerid, ui_player_id_text[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, ui_player_id_text[playerid], 0);

    ui_player_level_text[playerid] = CreatePlayerTextDraw(playerid, 632.000000, 377.000000, "LEVEL: 100");
    PlayerTextDrawFont(playerid, ui_player_level_text[playerid], 1);
    PlayerTextDrawLetterSize(playerid, ui_player_level_text[playerid], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, ui_player_level_text[playerid], 682.000000, 16.000000);
    PlayerTextDrawSetOutline(playerid, ui_player_level_text[playerid], 0);
    PlayerTextDrawSetShadow(playerid, ui_player_level_text[playerid], 0);
    PlayerTextDrawAlignment(playerid, ui_player_level_text[playerid], 3);
    PlayerTextDrawColor(playerid, ui_player_level_text[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, ui_player_level_text[playerid], 255);
    PlayerTextDrawBoxColor(playerid, ui_player_level_text[playerid], 50);
    PlayerTextDrawUseBox(playerid, ui_player_level_text[playerid], 0);
    PlayerTextDrawSetProportional(playerid, ui_player_level_text[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, ui_player_level_text[playerid], 0);

    uimain[playerid][11] = CreatePlayerTextDraw(playerid, 526.000000, 391.000000, "ld_beat:chit");
    PlayerTextDrawFont(playerid, uimain[playerid][11], 4);
    PlayerTextDrawLetterSize(playerid, uimain[playerid][11], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, uimain[playerid][11], 15.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, uimain[playerid][11], 1);
    PlayerTextDrawSetShadow(playerid, uimain[playerid][11], 0);
    PlayerTextDrawAlignment(playerid, uimain[playerid][11], 1);
    PlayerTextDrawColor(playerid, uimain[playerid][11], 329251071);
    PlayerTextDrawBackgroundColor(playerid, uimain[playerid][11], 255);
    PlayerTextDrawBoxColor(playerid, uimain[playerid][11], 50);
    PlayerTextDrawUseBox(playerid, uimain[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, uimain[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, uimain[playerid][11], 0);

    uimain[playerid][12] = CreatePlayerTextDraw(playerid, 526.799987, 392.000000, "ld_beat:chit");
    PlayerTextDrawFont(playerid, uimain[playerid][12], 4);
    PlayerTextDrawLetterSize(playerid, uimain[playerid][12], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, uimain[playerid][12], 13.500000, 15.000000);
    PlayerTextDrawSetOutline(playerid, uimain[playerid][12], 1);
    PlayerTextDrawSetShadow(playerid, uimain[playerid][12], 0);
    PlayerTextDrawAlignment(playerid, uimain[playerid][12], 1);
    PlayerTextDrawColor(playerid, uimain[playerid][12], 67372031);
    PlayerTextDrawBackgroundColor(playerid, uimain[playerid][12], 255);
    PlayerTextDrawBoxColor(playerid, uimain[playerid][12], 50);
    PlayerTextDrawUseBox(playerid, uimain[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, uimain[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, uimain[playerid][12], 0);

    uimain[playerid][13] = CreatePlayerTextDraw(playerid, 530.000000, 395.000000, "XP");
    PlayerTextDrawFont(playerid, uimain[playerid][13], 1);
    PlayerTextDrawLetterSize(playerid, uimain[playerid][13], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, uimain[playerid][13], 682.000000, 16.000000);
    PlayerTextDrawSetOutline(playerid, uimain[playerid][13], 0);
    PlayerTextDrawSetShadow(playerid, uimain[playerid][13], 0);
    PlayerTextDrawAlignment(playerid, uimain[playerid][13], 1);
    PlayerTextDrawColor(playerid, uimain[playerid][13], 329251071);
    PlayerTextDrawBackgroundColor(playerid, uimain[playerid][13], 255);
    PlayerTextDrawBoxColor(playerid, uimain[playerid][13], 50);
    PlayerTextDrawUseBox(playerid, uimain[playerid][13], 0);
    PlayerTextDrawSetProportional(playerid, uimain[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, uimain[playerid][13], 0);

    uimain[playerid][14] = CreatePlayerTextDraw(playerid, 542.000000, 395.000000, "EXP");
    PlayerTextDrawFont(playerid, uimain[playerid][14], 1);
    PlayerTextDrawLetterSize(playerid, uimain[playerid][14], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, uimain[playerid][14], 682.000000, 16.000000);
    PlayerTextDrawSetOutline(playerid, uimain[playerid][14], 0);
    PlayerTextDrawSetShadow(playerid, uimain[playerid][14], 0);
    PlayerTextDrawAlignment(playerid, uimain[playerid][14], 1);
    PlayerTextDrawColor(playerid, uimain[playerid][14], 329251071);
    PlayerTextDrawBackgroundColor(playerid, uimain[playerid][14], 255);
    PlayerTextDrawBoxColor(playerid, uimain[playerid][14], 50);
    PlayerTextDrawUseBox(playerid, uimain[playerid][14], 0);
    PlayerTextDrawSetProportional(playerid, uimain[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, uimain[playerid][14], 0);

    ui_xp_percent[playerid] = CreatePlayerTextDraw(playerid, 634.000000, 396.000000, "100%");
    PlayerTextDrawFont(playerid, ui_xp_percent[playerid], 1);
    PlayerTextDrawLetterSize(playerid, ui_xp_percent[playerid], 0.129166, 0.850000);
    PlayerTextDrawTextSize(playerid, ui_xp_percent[playerid], 682.000000, 16.000000);
    PlayerTextDrawSetOutline(playerid, ui_xp_percent[playerid], 0);
    PlayerTextDrawSetShadow(playerid, ui_xp_percent[playerid], 0);
    PlayerTextDrawAlignment(playerid, ui_xp_percent[playerid], 3);
    PlayerTextDrawColor(playerid, ui_xp_percent[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, ui_xp_percent[playerid], 255);
    PlayerTextDrawBoxColor(playerid, ui_xp_percent[playerid], 50);
    PlayerTextDrawUseBox(playerid, ui_xp_percent[playerid], 0);
    PlayerTextDrawSetProportional(playerid, ui_xp_percent[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, ui_xp_percent[playerid], 0);

    uimain[playerid][15] = CreatePlayerTextDraw(playerid, 527.000000, 407.000000, "HUD:radar_burgershot");
    PlayerTextDrawFont(playerid, uimain[playerid][15], 4);
    PlayerTextDrawLetterSize(playerid, uimain[playerid][15], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, uimain[playerid][15], 13.000000, 14.500000);
    PlayerTextDrawSetOutline(playerid, uimain[playerid][15], 1);
    PlayerTextDrawSetShadow(playerid, uimain[playerid][15], 0);
    PlayerTextDrawAlignment(playerid, uimain[playerid][15], 1);
    PlayerTextDrawColor(playerid, uimain[playerid][15], -65281);
    PlayerTextDrawBackgroundColor(playerid, uimain[playerid][15], 255);
    PlayerTextDrawBoxColor(playerid, uimain[playerid][15], 50);
    PlayerTextDrawUseBox(playerid, uimain[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, uimain[playerid][15], 1);
    PlayerTextDrawSetSelectable(playerid, uimain[playerid][15], 0);

    uimain[playerid][16] = CreatePlayerTextDraw(playerid, 542.000000, 410.000000, "HUNGRY");
    PlayerTextDrawFont(playerid, uimain[playerid][16], 1);
    PlayerTextDrawLetterSize(playerid, uimain[playerid][16], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, uimain[playerid][16], 682.000000, 16.000000);
    PlayerTextDrawSetOutline(playerid, uimain[playerid][16], 0);
    PlayerTextDrawSetShadow(playerid, uimain[playerid][16], 0);
    PlayerTextDrawAlignment(playerid, uimain[playerid][16], 1);
    PlayerTextDrawColor(playerid, uimain[playerid][16], -175567361);
    PlayerTextDrawBackgroundColor(playerid, uimain[playerid][16], 255);
    PlayerTextDrawBoxColor(playerid, uimain[playerid][16], 50);
    PlayerTextDrawUseBox(playerid, uimain[playerid][16], 0);
    PlayerTextDrawSetProportional(playerid, uimain[playerid][16], 1);
    PlayerTextDrawSetSelectable(playerid, uimain[playerid][16], 0);

    ui_hungry_percent[playerid] = CreatePlayerTextDraw(playerid, 634.000000, 410.000000, "100%");
    PlayerTextDrawFont(playerid, ui_hungry_percent[playerid], 1);
    PlayerTextDrawLetterSize(playerid, ui_hungry_percent[playerid], 0.129166, 0.850000);
    PlayerTextDrawTextSize(playerid, ui_hungry_percent[playerid], 682.000000, 16.000000);
    PlayerTextDrawSetOutline(playerid, ui_hungry_percent[playerid], 0);
    PlayerTextDrawSetShadow(playerid, ui_hungry_percent[playerid], 0);
    PlayerTextDrawAlignment(playerid, ui_hungry_percent[playerid], 3);
    PlayerTextDrawColor(playerid, ui_hungry_percent[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, ui_hungry_percent[playerid], 255);
    PlayerTextDrawBoxColor(playerid, ui_hungry_percent[playerid], 50);
    PlayerTextDrawUseBox(playerid, ui_hungry_percent[playerid], 0);
    PlayerTextDrawSetProportional(playerid, ui_hungry_percent[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, ui_hungry_percent[playerid], 0);

    uimain[playerid][17] = CreatePlayerTextDraw(playerid, 527.500000, 423.000000, "HUD:radar_centre");
    PlayerTextDrawFont(playerid, uimain[playerid][17], 4);
    PlayerTextDrawLetterSize(playerid, uimain[playerid][17], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, uimain[playerid][17], 13.000000, 14.500000);
    PlayerTextDrawSetOutline(playerid, uimain[playerid][17], 1);
    PlayerTextDrawSetShadow(playerid, uimain[playerid][17], 0);
    PlayerTextDrawAlignment(playerid, uimain[playerid][17], 1);
    PlayerTextDrawColor(playerid, uimain[playerid][17], 549318911);
    PlayerTextDrawBackgroundColor(playerid, uimain[playerid][17], 255);
    PlayerTextDrawBoxColor(playerid, uimain[playerid][17], 50);
    PlayerTextDrawUseBox(playerid, uimain[playerid][17], 1);
    PlayerTextDrawSetProportional(playerid, uimain[playerid][17], 1);
    PlayerTextDrawSetSelectable(playerid, uimain[playerid][17], 0);

    uimain[playerid][18] = CreatePlayerTextDraw(playerid, 542.000000, 426.000000, "THIRSTY");
    PlayerTextDrawFont(playerid, uimain[playerid][18], 1);
    PlayerTextDrawLetterSize(playerid, uimain[playerid][18], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, uimain[playerid][18], 682.000000, 16.000000);
    PlayerTextDrawSetOutline(playerid, uimain[playerid][18], 0);
    PlayerTextDrawSetShadow(playerid, uimain[playerid][18], 0);
    PlayerTextDrawAlignment(playerid, uimain[playerid][18], 1);
    PlayerTextDrawColor(playerid, uimain[playerid][18], 549318911);
    PlayerTextDrawBackgroundColor(playerid, uimain[playerid][18], 255);
    PlayerTextDrawBoxColor(playerid, uimain[playerid][18], 50);
    PlayerTextDrawUseBox(playerid, uimain[playerid][18], 0);
    PlayerTextDrawSetProportional(playerid, uimain[playerid][18], 1);
    PlayerTextDrawSetSelectable(playerid, uimain[playerid][18], 0);

    ui_thirsty_percent[playerid] = CreatePlayerTextDraw(playerid, 634.000000, 425.000000, "100%");
    PlayerTextDrawFont(playerid, ui_thirsty_percent[playerid], 1);
    PlayerTextDrawLetterSize(playerid, ui_thirsty_percent[playerid], 0.129166, 0.850000);
    PlayerTextDrawTextSize(playerid, ui_thirsty_percent[playerid], 682.000000, 16.000000);
    PlayerTextDrawSetOutline(playerid, ui_thirsty_percent[playerid], 0);
    PlayerTextDrawSetShadow(playerid, ui_thirsty_percent[playerid], 0);
    PlayerTextDrawAlignment(playerid, ui_thirsty_percent[playerid], 3);
    PlayerTextDrawColor(playerid, ui_thirsty_percent[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, ui_thirsty_percent[playerid], 255);
    PlayerTextDrawBoxColor(playerid, ui_thirsty_percent[playerid], 50);
    PlayerTextDrawUseBox(playerid, ui_thirsty_percent[playerid], 0);
    PlayerTextDrawSetProportional(playerid, ui_thirsty_percent[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, ui_thirsty_percent[playerid], 0);

    ui_progress_xp[playerid] = CreatePlayerProgressBar(playerid, 570.000000, 397.000000, 53.500000, 5.500000, 329251071, 100.000000, 0);
    ui_progress_hungry[playerid] = CreatePlayerProgressBar(playerid, 570.000000, 411.000000, 53.500000, 5.500000, -175567361, 100.000000, 0);
    ui_progress_thirsty[playerid] = CreatePlayerProgressBar(playerid, 570.000000, 427.000000, 53.500000, 5.500000, 549318911, 100.000000, 0);
    
    SetPlayerProgressBarValue(playerid, ui_progress_xp[playerid],      100.0);
    SetPlayerProgressBarValue(playerid, ui_progress_hungry[playerid],   100.0);
    SetPlayerProgressBarValue(playerid, ui_progress_thirsty[playerid],  100.0);
    return 1;
}

stock UpdatePlayerUI(playerid) {
    if (!GetPlayerLoggedIn(playerid)) return 1;

    new str[32];

    // ID
    format(str, sizeof str, "%d", playerid);
    PlayerTextDrawSetString(playerid, ui_player_id_text[playerid], str);

    // Level
    format(str, sizeof str, "LEVEL: %d", playerData[playerid][pLevel]);
    PlayerTextDrawSetString(playerid, ui_player_level_text[playerid], str);

    // XP %
    new Float:xpPercent = float(GetPlayerLevelProgress(playerid));
    format(str, sizeof str, "%.0f%%", xpPercent);
    PlayerTextDrawSetString(playerid, ui_xp_percent[playerid], str);
    SetPlayerProgressBarValue(playerid, ui_progress_xp[playerid], xpPercent);

    // Hungry %
    format(str, sizeof str, "%.0f%%", playerData[playerid][pHungry]);
    PlayerTextDrawSetString(playerid, ui_hungry_percent[playerid], str);
    SetPlayerProgressBarValue(playerid, ui_progress_hungry[playerid], playerData[playerid][pHungry]);

    // Thirsty %
    format(str, sizeof str, "%.0f%%", playerData[playerid][pThirsty]);
    PlayerTextDrawSetString(playerid, ui_thirsty_percent[playerid], str);
    SetPlayerProgressBarValue(playerid, ui_progress_thirsty[playerid], playerData[playerid][pThirsty]);
    return 1;
}

stock ShowPlayerUI(playerid) {
    DestroyPlayerUI(playerid);
    CreatePlayerUI(playerid);
    UpdatePlayerUI(playerid);
    for (new i = 0; i < 19; i++) {
        PlayerTextDrawShow(playerid, uimain[playerid][i]);
    }
    PlayerTextDrawShow(playerid, ui_player_id_text[playerid]);
    PlayerTextDrawShow(playerid, ui_player_level_text[playerid]);
    PlayerTextDrawShow(playerid, ui_xp_percent[playerid]);
    PlayerTextDrawShow(playerid, ui_hungry_percent[playerid]);
    PlayerTextDrawShow(playerid, ui_thirsty_percent[playerid]);
    ShowPlayerProgressBar(playerid, ui_progress_xp[playerid]);
    ShowPlayerProgressBar(playerid, ui_progress_hungry[playerid]);
    ShowPlayerProgressBar(playerid, ui_progress_thirsty[playerid]);
    IsUICreated[playerid] = 1;
    return 1;
}

stock DestroyPlayerUI(playerid) {
    for (new i = 0; i < 19; i++) {
        DestroyPlayerTD(playerid, uimain[playerid][i]);
    }

    DestroyPlayerTD(playerid, ui_player_id_text[playerid]);
    DestroyPlayerTD(playerid, ui_player_level_text[playerid]);
    DestroyPlayerTD(playerid, ui_xp_percent[playerid]);
    DestroyPlayerTD(playerid, ui_hungry_percent[playerid]);
    DestroyPlayerTD(playerid, ui_thirsty_percent[playerid]);
    DestroyPlayerProgressBar(playerid, ui_progress_xp[playerid]);
    DestroyPlayerProgressBar(playerid, ui_progress_hungry[playerid]);
    DestroyPlayerProgressBar(playerid, ui_progress_thirsty[playerid]);
    IsUICreated[playerid] = 0;
    return 1;
}

ptask UpdateUITimer[1000](playerid) {
    if (!GetPlayerLoggedIn(playerid)) return 1;
    if (IsUICreated[playerid] == 0) return 1;
	UpdatePlayerUI(playerid);
    return 1;
}

hook OnPlayerConnect(playerid) {
    IsUICreated[playerid] = 0;
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
