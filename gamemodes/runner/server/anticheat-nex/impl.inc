#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

public OnCheatDetected(playerid, ip_address[], type, code) {
    if (type) BlockIpAddress(ip_address, 0);
    else {
        switch (code) {
            case 0:  SendAdminMessage(COLOR_YELLOW, "%s(%d) AirBreak (onfoot) มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 1:  SendAdminMessage(COLOR_YELLOW, "%s(%d) AirBreak (in vehicle) มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 2:  SendAdminMessage(COLOR_YELLOW, "%s(%d) Teleport hack (onfoot) มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 3:  SendAdminMessage(COLOR_YELLOW, "%s(%d) Teleport hack (in vehicle) มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 4:  SendAdminMessage(COLOR_YELLOW, "%s(%d) Teleport hack (into/between vehicles) มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 5:  SendAdminMessage(COLOR_YELLOW, "%s(%d) Teleport hack (vehicle to player) มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 6:  SendAdminMessage(COLOR_YELLOW, "%s(%d) Teleport hack (pickups) มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 7:  SendAdminMessage(COLOR_YELLOW, "%s(%d) FlyHack (onfoot) มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 8:  SendAdminMessage(COLOR_YELLOW, "%s(%d) FlyHack (in vehicle) มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 9:  SendAdminMessage(COLOR_YELLOW, "%s(%d) SpeedHack (onfoot) มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 10: SendAdminMessage(COLOR_YELLOW, "%s(%d) SpeedHack (in vehicle) มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 11: SendAdminMessage(COLOR_YELLOW, "%s(%d) Health hack (in vehicle) มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 12: SendAdminMessage(COLOR_YELLOW, "%s(%d) Health hack (onfoot) มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 13: SendAdminMessage(COLOR_YELLOW, "%s(%d) Armour hack มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 14: SendAdminMessage(COLOR_YELLOW, "%s(%d) Money hack มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 15: SendAdminMessage(COLOR_YELLOW, "%s(%d) Weapon hack มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 16: SendAdminMessage(COLOR_YELLOW, "%s(%d) Ammo hack (add) มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 17: SendAdminMessage(COLOR_YELLOW, "%s(%d) Ammo hack (infinite) มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 18: SendAdminMessage(COLOR_YELLOW, "%s(%d) Special actions hack มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 19: SendAdminMessage(COLOR_YELLOW, "%s(%d) GodMode from bullets (onfoot) มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 20: SendAdminMessage(COLOR_YELLOW, "%s(%d) GodMode from bullets (in vehicle) มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 21: SendAdminMessage(COLOR_YELLOW, "%s(%d) Invisible hack มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 22: SendAdminMessage(COLOR_YELLOW, "%s(%d) Lagcomp-spoof มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 23: SendAdminMessage(COLOR_YELLOW, "%s(%d) Tuning hack มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 24: SendAdminMessage(COLOR_YELLOW, "%s(%d) Parkour mod มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 25: SendAdminMessage(COLOR_YELLOW, "%s(%d) Quick turn มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 26: SendAdminMessage(COLOR_YELLOW, "%s(%d) Rapid fire มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 27: SendAdminMessage(COLOR_YELLOW, "%s(%d) FakeSpawn มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 28: SendAdminMessage(COLOR_YELLOW, "%s(%d) FakeKill มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 29: SendAdminMessage(COLOR_YELLOW, "%s(%d) Pro Aim มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 30: SendAdminMessage(COLOR_YELLOW, "%s(%d) CJ run มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 31: SendAdminMessage(COLOR_YELLOW, "%s(%d) CarShot มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 32: SendAdminMessage(COLOR_YELLOW, "%s(%d) CarJack มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 33: SendAdminMessage(COLOR_YELLOW, "%s(%d) UnFreeze มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 34: SendAdminMessage(COLOR_YELLOW, "%s(%d) AFK Ghost มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 35: SendAdminMessage(COLOR_YELLOW, "%s(%d) Full Aiming มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 36: SendAdminMessage(COLOR_YELLOW, "%s(%d) Fake NPC มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 37: SendAdminMessage(COLOR_YELLOW, "%s(%d) Reconnect มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 38: SendAdminMessage(COLOR_YELLOW, "%s(%d) High ping มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 39: SendAdminMessage(COLOR_YELLOW, "%s(%d) Dialog hack มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 40: {
                SendClientMessage(playerid, -1, MAX_CONNECTS_MSG);
                AntiCheatKickWithDesync(playerid, code);
            }
            case 41: {
                SendClientMessage(playerid, -1, UNKNOWN_CLIENT_MSG);
                AntiCheatKickWithDesync(playerid, code);
            }
            case 42: SendAdminMessage(COLOR_YELLOW, "%s(%d) Rcon hack มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 43: SendAdminMessage(COLOR_YELLOW, "%s(%d) Tuning crasher มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 44: SendAdminMessage(COLOR_YELLOW, "%s(%d) Invalid seat crasher มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 45: SendAdminMessage(COLOR_YELLOW, "%s(%d) Dialog crasher มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 46: SendAdminMessage(COLOR_YELLOW, "%s(%d) Attached object crasher มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 47: SendAdminMessage(COLOR_YELLOW, "%s(%d) Weapon crasher มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 48: SendAdminMessage(COLOR_YELLOW, "%s(%d) Connection flood มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 49: SendAdminMessage(COLOR_YELLOW, "%s(%d) Callback flood มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 50: SendAdminMessage(COLOR_YELLOW, "%s(%d) Seat change flood มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 51: SendAdminMessage(COLOR_YELLOW, "%s(%d) DoS attack มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            case 52: SendAdminMessage(COLOR_YELLOW, "%s(%d) NOPs hack มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            default: {
                SendAdminMessage(COLOR_YELLOW, "%s(%d) (ไม่ทราบประเภท) มีความเป็นไปได้ที่จะใช้โปรแกรมโกงโปรดตรวจสอบ", ReturnPlayerName(playerid), playerid);
            }
        }
    }
    return 1;
}
