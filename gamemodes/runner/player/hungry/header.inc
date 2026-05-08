#if defined _inc_header
#undef _inc_header
#endif

#define HUNGRY_TICK_IDLE    1
#define HUNGRY_TICK_WALK    3
#define HUNGRY_TICK_MAX     60

forward HungryTime(playerid);

new HungryTimer[MAX_PLAYERS];
new FullnessTick[MAX_PLAYERS];
new StatusUIStatus[MAX_PLAYERS];

new PlayerText:statusUI[MAX_PLAYERS][4];
new PlayerBar:hungryProgressbar[MAX_PLAYERS];
new PlayerBar:thirstyProgressbar[MAX_PLAYERS];
