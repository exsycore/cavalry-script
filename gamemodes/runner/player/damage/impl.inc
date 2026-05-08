#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnPlayerDamageDone(playerid, Float:amount, issuerid, WEAPON:weapon, bodypart) {
    if (!GetPlayerLoggedIn(playerid)) return 1;
    return 1;
}