#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

stock ResetArrays(playerid) {
    playerData[playerid][pID] = 0;
    playerData[playerid][pGender] = 0;
    playerData[playerid][LoginTimer] = 0;
    playerData[playerid][IsLoggedIn] = false;
    playerData[playerid][pRegisterDate][0] = EOS;
	playerData[playerid][pAdmin] = 0;
    playerData[playerid][pExp] = 0;
    playerData[playerid][pLevel] = 0;
    playerData[playerid][pInDeath]      = 0;
    playerData[playerid][pInjuredTimer] = -1;
    playerData[playerid][pInjuredTime]  = 0;

    playerData[playerid][pDolboeb] = 0;
    playerData[playerid][pDopKletki] = 0;
    playerData[playerid][pTrashOpen] = 0;
    playerData[playerid][pInventoryKolvoDop] = 0;
    playerData[playerid][pProstoTak] = 0;
	playerData[playerid][pProstoTak2] = 0;

    for (new i; i < 7; i++) playerData[playerid][pSlotItem][i] = 0;
    for (new i; i < 72; i++) playerData[playerid][pInventory][i] = 0;
    for (new i; i < 72; i++) playerData[playerid][pInventoryKolvo][i] = 0;
	return 1;
}

hook OnPlayerConnect(playerid) {
    ResetArrays(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    if (playerData[playerid][LoginTimer]) {
        KillTimer(playerData[playerid][LoginTimer]);
        playerData[playerid][LoginTimer] = 0;
    }
    
    playerData[playerid][IsLoggedIn] = false;
    return 1;
}
