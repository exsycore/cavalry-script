#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid) {
    if (GetPVarInt(playerid, "hasVoiceOnClient") == -1) {
        SendErrorMessage(playerid, "{FFFFFF}ระบบไม่พบปลั๊กอินไมค์โครโฟนเสริมโปรดตรวจสอบหรือติดต่อแอดมิน");
    } else if (GetPVarInt(playerid, "hasVoiceOnClient") == 0) {
        SendErrorMessage(playerid, "{FFFFFF}ระบบตรวจสอบได้ว่าไม่พบอุปกรณ์ของคุณโปรดตรวจสอบหรือติดต่อแอดมิน");
    } else {
        SendClientMessage(playerid, -1, "{FFFFFF}กด {00FF00}'B' {FFFFFF}เพื่อสนทนาใกล้เคียง");
    }
    return 1;
}
