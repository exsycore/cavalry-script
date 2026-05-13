#if defined _inc_header
	#undef _inc_header
#endif

new 
    ProgressLimit[MAX_PLAYERS],
	ProgressCount[MAX_PLAYERS],
	Timer: ProgressTimer[MAX_PLAYERS],
	ProgressState[MAX_PLAYERS],
	ProgressObject[MAX_PLAYERS];

new 
    PlayerText: PlayerJobCountTD[MAX_PLAYERS][3],
    PlayerBar: PlayerProgressJob[MAX_PLAYERS];