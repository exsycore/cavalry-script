#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_FISH (1)
#define DEFAULT_FISH_ROD (5000)

#define DEFAULT_POS_FISHING_X (2156.1802)
#define DEFAULT_POS_FISHING_Y (-93.0639)
#define DEFAULT_POS_FISHING_Z (2.7636)
#define DEFAULT_POS_FISHING_A (60.3935)

#define DEFAULT_POS_SELL_FISHING_X (0.0)
#define DEFAULT_POS_SELL_FISHING_Y (0.0)
#define DEFAULT_POS_SELL_FISHING_Z (0.0)
#define DEFAULT_POS_SELL_FISHING_A (0.0)

#define SendErrorFishingMessage(%0,%1) \
	va_SendClientMessage(%0, COLOR_RED, "[¢ÈÕº‘¥æ≈“¥]: {FFFFFF}"%1)

forward PlayerFishingUnfreeze(playerid);

enum FISH_DATA {
    fishID,
    Float: fishPosX,
	Float: fishPosY,
	Float: fishPosZ,
	Float: fishPosA,
    Text3D: fish3D,
    fishPickup
};
new const fishData[MAX_FISH][FISH_DATA] = {
	{ 0, 2120.6895, -110.3804, 1.2515, 128.2375, Text3D: INVALID_3DTEXT_ID, -1 }
	/*{ 1, 873.6452, -2205.3767, 1.2286, 90.6779, Text3D: INVALID_3DTEXT_ID, -1 },
	{ 2, 863.0575, -2205.5664, 0.8659, 92.2750, Text3D: INVALID_3DTEXT_ID, -1 },
	{ 3, 851.1927, -2205.4417, 0.9898, 88.6559, Text3D: INVALID_3DTEXT_ID, -1 },
	{ 4, 839.2246, -2205.5935, 0.7889, 93.5576, Text3D: INVALID_3DTEXT_ID, -1 },
	{ 5, 824.4041, -2205.2805, 0.7679, 88.1703, Text3D: INVALID_3DTEXT_ID, -1 },
	{ 6, 811.5417, -2205.5085, 0.9605, 89.7475, Text3D: INVALID_3DTEXT_ID, -1 }*/
};