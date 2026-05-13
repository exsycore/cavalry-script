#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_GACHA (50)

new 
	playerTimerGacha[MAX_PLAYERS],
	playerCoutingGacha[MAX_PLAYERS],
	playerMaxCoutingGacha[MAX_PLAYERS],
	playerTimeCountingGacha[MAX_PLAYERS],
	playerGetLastItemGacha[MAX_PLAYERS],
	playerGetLastItemColorGacha[MAX_PLAYERS],
	playerGetLastItemNameGacha[MAX_PLAYERS][64],
	playerStampGoldItemGacha[MAX_PLAYERS],
	playerStampBlueItemGacha[MAX_PLAYERS],
	playerStampGreenItemGacha[MAX_PLAYERS],
	playerGetGachaBoxID[MAX_PLAYERS],
	playerGetGachaItemInvIndex[MAX_PLAYERS],
	playerOpenGachaAuto[MAX_PLAYERS];

enum gachaInfo {
	gachaID,
	gachaName[64]
};
new 
	GachaData[MAX_GACHA][gachaInfo],
	GaChaItemName[MAX_GACHA][15][64],
	GaChaItemModel[MAX_GACHA][15],
	GaChaItemAmount[MAX_GACHA][15];