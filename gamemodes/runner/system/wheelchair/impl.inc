#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid) {
    playerWheelchair[playerid] = 0;
    return 1;
}

hook OnPlayerUpdate(playerid) {
    if (playerWheelchair[playerid] == 1) {
        new Float: a;
        new Keys, ud, lr;
        GetPlayerKeys(playerid, Keys, ud, lr);
        if (ud < 0) {
            SetPlayerForwardVelocity(playerid, 0.16, -0.03);
        }
        if (ud > 0) {
            SetPlayerForwardVelocity(playerid, -0.16, -0.03);
        }
        if (lr > 0) {
            GetPlayerFacingAngle(playerid, a);
            SetPlayerFacingAngle(playerid, a-10);
        }
        if (lr < 0) {
            GetPlayerFacingAngle(playerid, a);
            SetPlayerFacingAngle(playerid, a+10);
        }
    }
    return 1;
}

YCMD:wheelchair(playerid, const params[], help) {
    if (playerWheelchair[playerid] == 0) {
        ApplyAnimation(playerid, "PED", "SEAT_IDLE", 4.1, 0, 0, 0, 1, 0, 1);
        SetPlayerAttachedObject(playerid,0, 1369, 1, -0.276000, 0.089999, -0.011999, 178.699661, 92.599975, 3.100000, 0.876001, 0.734000, 0.779000);
        playerWheelchair[playerid] = 1;
    } else if (playerWheelchair[playerid] == 1) {
        ApplyAnimation(playerid, "PED", "SEAT_UP", 4.0, 0, 0, 0, 0, 0, 1);
        RemovePlayerAttachedObject(playerid , 0);
        playerWheelchair[playerid] = 0;
    }
    return 1;
}