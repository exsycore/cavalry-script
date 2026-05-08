#if defined _inc_header
#undef _inc_header
#endif

#define ANTI_CHEAT_VERS "1.0.0"

#define C_GREEN 0x20DD6AFF
#define C_ERROR 0xA01616FF

#define MOBILE_CLIENT "ED40ED0E8089CC44C08EE9580F4C8C44EE8EE990"

#define MAX_MEMADDR (14)
#define MAX_CHEATS (15)

native SendClientCheck(playerid, type, arg, offsetMem, size);

forward OnClientCheckResponse(playerid, actionid, memaddr, retndata);
forward checkPlayer(playerid);
forward kickPlayer(playerid, action);

enum PR_JoinData
{
    PR_iVersion,
    PR_byteMod,
    PR_byteNicknameLen,
    PR_NickName[24],
    PR_uiClientChallengeResponse,
    PR_byteAuthKeyLen,
    PR_auth_key[50],
    PR_iClientVerLen,
    PR_ClientVersion[30]
};

enum AC_PlayerData {
	bool:mobilePlayer,
	bool:pSuspicious,
	bool:pResponded,
	pCheat[MAX_CHEATS],
	checkSampAddr,
	pCheckSum
};

new AC_Player[MAX_PLAYERS][AC_PlayerData];

enum cheatData
{
    memadr,
    expectedValue,
    cheatValue
}

new memory[MAX_MEMADDR][cheatData] =
{
    { 0x06865E, 192, 1 },
    { 0xA88774, 72, 2 },
    { 0xDB6746, 192, 3 },
    { 0xFDB957, 68, 4 },
    { 0x52D558, 196, 5 },
    { 0xE4FC58, 64, 6 },
    { 0x1BA246, 8, 7 },
    { 0xB0C56F, 200, 8 },
    { 0xF9855E, 200, 9 },
    { 0x910152, 204, 10 },
    { 0xC7FB6E, 196, 11 },
    { 0xF4C853, 132, 12 },
    { 0xB47E74, 132, 13 },
    { 0x242C52, 192, 14 }
};

new memOffsets[9] = {
    0x0, 0x2, 0x4,
    0x6, 0x8, 0xA,
    0xC, 0xE, 0x10
};

new sampAddr[] = {
    0x41B04, 
    0x42044,
    0x41FF4, 
    0x41904  
};

new rMemAddr[MAX_MEMADDR];
