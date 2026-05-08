#include <a_samp>
#include <sampvoice>

new SV_LSTREAM:local_stream[MAX_PLAYERS] = { SV_NULL, ... };

public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid) {
    if (keyid == 0x42) {
        if (local_stream[playerid]) {
            if (!SvHasSpeakerInStream(local_stream[playerid], playerid)) {
                SvAttachSpeakerToStream(local_stream[playerid], playerid);
            }
        }
    }
}

public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid) {
    if (keyid == 0x42) {
        if (local_stream[playerid]) {
            if (SvHasSpeakerInStream(local_stream[playerid], playerid)) {
                SvDetachSpeakerFromStream(local_stream[playerid], playerid);
                SendClientMessage(playerid, -1, "กด {00FF00}'B'{FFFFFF} เพื่อสนทนาด้วยเสียงในพื้นที่ใกล้เคียง");
            }
        }
    }
}

public OnPlayerConnect(playerid) {
    if (SvGetVersion(playerid) == SV_NULL) {
        SetPVarInt(playerid, "hasVoiceOnClient", -1);
    } else if (SvHasMicro(playerid) == SV_FALSE) {
        SetPVarInt(playerid, "hasVoiceOnClient", 0);
    } else if ((local_stream[playerid] = SvCreateDLStreamAtPlayer(40.0, SV_INFINITY, playerid, 0xff0000ff, "Local"))) {
        SvAddKey(playerid, 0x42);
        SetPVarInt(playerid, "hasVoiceOnClient", 1);
    }
    return 1;
}

public OnPlayerDisconnect(playerid, reason) {
    if (local_stream[playerid]) {
        SvDeleteStream(local_stream[playerid]);
        local_stream[playerid] = SV_NULL;
    }
    return 1;
}
