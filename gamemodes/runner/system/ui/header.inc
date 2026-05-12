#if defined _inc_header
#undef _inc_header
#endif

new PlayerText:uimain[MAX_PLAYERS][19];
new PlayerText:ui_player_id_text[MAX_PLAYERS];
new PlayerText:ui_player_level_text[MAX_PLAYERS];
new PlayerText:ui_xp_percent[MAX_PLAYERS];
new PlayerText:ui_hungry_percent[MAX_PLAYERS];
new PlayerText:ui_thirsty_percent[MAX_PLAYERS];
new PlayerBar:ui_progress_xp[MAX_PLAYERS];
new PlayerBar:ui_progress_hungry[MAX_PLAYERS];
new PlayerBar:ui_progress_thirsty[MAX_PLAYERS];

new IsUICreated[MAX_PLAYERS];
