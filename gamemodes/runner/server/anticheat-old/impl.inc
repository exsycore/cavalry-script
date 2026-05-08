#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
    print("--------------------------------------------------");
    print("\t");
    print("\t");
    print("  AntiCheat "ANTI_CHEAT_VERS" by EasyCore loaded  ");
    print("\t");
    print("\t");
    print("--------------------------------------------------");
    return 1;
}

hook OnPlayerConnect(playerid) {
    new version[24], pAuth[43];

    for (new i = 0; i < MAX_CHEATS; i++) {
        AC_Player[playerid][pCheat][i] = -1;
    }

    AC_Player[playerid][mobilePlayer] = false;
    AC_Player[playerid][pSuspicious] = false;
    AC_Player[playerid][pResponded] = false;
    AC_Player[playerid][checkSampAddr] = 0x0;
    
    GetPlayerVersion(playerid, version, sizeof(version));
    GPCI(playerid, pAuth, sizeof(pAuth));

    // if ( !strcmp ( MOBILE_CLIENT, pAuth, true ) ) {
    //     if ( AC_Player[playerid][pCheckSum] == 0xBEEF ) {
    //         AC_Player[playerid][mobilePlayer] = true;
    //         AC_Player[playerid][pResponded] = true;
    //     } else {
    //         SendErrorMessage(playerid, "เกิดข้อผิดพลาดในการตรวจสอบสิทธิ์ในเวอร์ชันมือถือ IP ของคุณถูกบล็อกชั่วคราว!");
	// 		SetTimerEx("kickPlayer", 1500, false, "ii", playerid, 1);
    //     }
    // }

	// if ( strcmp ( version, "0.3.7" ) == 0 && AC_Player[playerid][mobilePlayer] == false ) {
    //     SendErrorMessage(playerid, "เซิร์ฟเวอร์ต้องการเวอร์ชันไคลเอ็นต์ที่ใหม่กว่า 0.3.7 R1!");
    //     SetTimerEx("kickPlayer", 1500, false, "ii", playerid, 0);
    // }
    
	SendClientCheck(playerid, 0x47, 0, 0, 0x4);
    SendClientCheck(playerid, 0x48, 0, 0, 0x4);
    
	for (new i = 0; i < MAX_MEMADDR; i++) {
    	rMemAddr[i] = rrAddress(memory[i][memadr]);
    	SendClientCheck(playerid, 0x5, rMemAddr[i], 0x0, 0x4);
	}
	
    checkClientCheat(playerid);
    
    CallLocalFunction("OnClientCheckResponse", "iiii", playerid, 0x47, 0xCECECE, 255);
    CallLocalFunction("OnClientCheckResponse", "iiii", playerid, 0x48, 0xDEDEDE, 255);
    
    AC_Player[playerid][pCheckSum] = -1;
    SetTimerEx("checkPlayer", 2900, false, "i", playerid);
    return 1;
}

public OnClientCheckResponse(playerid, actionid, memaddr, retndata) {
    switch (actionid) {
        case 0x5: {
            if ( AC_Player[playerid][mobilePlayer] == false ) { AC_Player[playerid][pResponded] = true; }

		   	for (new i = 0; i < MAX_MEMADDR; i++) {
	            if (memaddr == rMemAddr[i]) {
	                if (retndata != memory[i][expectedValue]) {
	                    AC_Player[playerid][pCheat][i] = memory[i][cheatValue];
	                    break;
	                }
	            }
		    }
		}
        
        case 0x45: {
		    if ( memaddr == AC_Player[playerid][checkSampAddr] && retndata != 192 ) {
		        AC_Player[playerid][pCheat][14] = 15;
		    }
        }
        
        case 0x47: {
            if ( AC_Player[playerid][mobilePlayer] == false ) {
                if ( memaddr == 0xCECECE && retndata == 255 ) {
                	AC_Player[playerid][pSuspicious] = true;
                	SendClientCheck(playerid, 0x47, 0, 0, 0x4);
                } else {
                    AC_Player[playerid][pSuspicious] = false;
                }
            }
        }

        case 0x48: {
            if ( AC_Player[playerid][mobilePlayer] == false ) {
                if ( memaddr == 0xDEDEDE && retndata == 255 ) {
                	AC_Player[playerid][pSuspicious] = true;
                	SendClientCheck(playerid, 0x48, 0, 0, 0x4);
                } else {
                    AC_Player[playerid][pSuspicious] = false;
                }
            }
        }
    }
	return 1;
}

public checkPlayer(playerid) {
    if ( AC_Player[playerid][mobilePlayer] == true ) {
        SendClientMessage(playerid, C_GREEN, "คุณกำลังเล่นเกม SA-MP เวอร์ชันมือถืออยู่");
    }
    
    if ( AC_Player[playerid][pSuspicious] == true ) {
        SendErrorMessage(playerid, "ระบบตรวจพบว่าคุณอาจกำลังใช้ม็อดบางอย่าง หากคุณคิดว่านี่เป็นข้อผิดพลาด โปรดติดต่อผู้ดูแลระบบ");
        SetTimerEx("kickPlayer", 1500, false, "ii", playerid, 0);
    }
    if ( AC_Player[playerid][pResponded] == false ) {
        SendErrorMessage(playerid, "ระบบตรวจพบว่าคุณอาจกำลังใช้ม็อดบางอย่าง หากคุณคิดว่านี่เป็นข้อผิดพลาด โปรดติดต่อผู้ดูแลระบบ");
        SetTimerEx("kickPlayer", 1500, false, "ii", playerid, 0);
    }
    
	for (new i = 0; i < MAX_CHEATS; i++) {
    	switch ( AC_Player[playerid][pCheat][i] ) {
		    case 1:cheatDetected(playerid, "[1] S0beit", 0);
		    case 2:cheatDetected(playerid, "[2] CLEO", 0);
		    case 3:cheatDetected(playerid, "[3] CLEO", 0);
		    case 4:cheatDetected(playerid, "[4] CLEO", 0);
			case 5:cheatDetected(playerid, "[5] CLEO / MoonLoader", 0);
			case 6:cheatDetected(playerid, "[6] CLEO / MoonLoader", 0);
			case 7:cheatDetected(playerid, "[7] CLEO", 0);
			case 8:cheatDetected(playerid, "SilentPatch", 0);
			case 9:cheatDetected(playerid, "SampFuncs", 0);
			case 10:cheatDetected(playerid, "[2] SampFuncs", 0);
			case 11:cheatDetected(playerid, "[2] S0beit", 0);
			case 12:cheatDetected(playerid, "Modified VorbisFile.dll", 0);
			case 13:cheatDetected(playerid, "UltraWH", 0);
			case 14:cheatDetected(playerid, "Silent Aim", 0);
			case 15:cheatDetected(playerid, "[3] S0beit", 0);
		}
	}
    return 1;
}

hook OnIncomingRPC(playerid, rpcid, BitStream:bs) {
    switch ( rpcid ) {
        case 25: {
            new data[PR_JoinData];

    		BS_ReadValue( bs, PR_INT32, data[PR_iVersion], PR_UINT8, data[PR_byteMod], PR_UINT8, data[PR_byteNicknameLen], PR_STRING, data[PR_NickName], data[PR_byteNicknameLen],
        		PR_UINT32, data[PR_uiClientChallengeResponse],
        		PR_UINT8, data[PR_byteAuthKeyLen],
        		PR_STRING, data[PR_auth_key], data[PR_byteAuthKeyLen],
        		PR_UINT8, data[PR_iClientVerLen]
    		);
    		
    		BS_ReadValue( bs, PR_STRING, data[PR_ClientVersion], (data[PR_iClientVerLen] >= 30 ? 30:data[PR_iClientVerLen]) );
            BS_ReadUint16(bs, AC_Player[playerid][pCheckSum]);
        }
    }
    return 1;
}

public kickPlayer(playerid, action) {
	switch ( action ) {
		case 0:Kick(playerid);
		case 1: {
  			new pIP[16+1];

        	GetPlayerIp(playerid, pIP, sizeof(pIP));
			BlockIpAddress(pIP, 60 * 3000);
		}
	}
	return 1;
}

static cheatDetected(playerid, const cName[], allow) {
	new pName[MAX_PLAYER_NAME+1], string[128];

	GetPlayerName(playerid, pName, sizeof(pName));

	switch ( allow ) {
	    case 0: {
		    printf("[DETECTION] Player %s using %s - Kicked", pName, cName);

		    SendClientMessage(playerid, C_GREEN, "---------------------------------------------------");
		    format(string, 128, "[ERROR] ระบบตรวจพบว่าคุณกำลังใช้ %s โปรดลบออกและกลับไปยังเซิร์ฟเวอร์!", cName);
			SendClientMessage(playerid, C_ERROR, string);
			SetTimerEx("kickPlayer", 1500, false, "ii", playerid, 0);
		}
		case 1: printf("[DETECTION] Player %s using %s - Allowed", pName, cName);
	}
    return 1;
}

static checkClientCheat(playerid) {
    new version[24], rSampAddr;
    GetPlayerVersion(playerid, version, sizeof(version));

    new randIndex = random(sizeof(memOffsets));
    new rSampOffset = memOffsets[randIndex];

    if ( strcmp ( version, "0.3.DL-R1", true ) == 0 ) rSampAddr = sampAddr[0];

    if ( strcmp ( version, "0.3.7-R5", true ) == 0 ) rSampAddr = sampAddr[1];

    if ( strcmp ( version, "0.3.7-R4", true ) == 0 ) rSampAddr = sampAddr[2];

   	if ( strcmp ( version, "0.3.7-R3", true ) == 0 ) rSampAddr = sampAddr[3];

    SendClientCheck(playerid, 0x45, rSampAddr - rSampOffset, rSampOffset, 0x4);

    AC_Player[playerid][checkSampAddr] = rSampAddr - rSampOffset;
    return 1;
}

static rrAddress(input) {
    new result;

    #emit LOAD.S.pri input
    #emit CONST.alt 0xFF
    #emit AND
    #emit CONST.alt 16
    #emit SHL
    #emit STOR.S.pri result

    #emit LOAD.S.pri input
    #emit CONST.alt 0xFF00
    #emit AND
    #emit LOAD.S.alt result
    #emit ADD
    #emit STOR.S.pri result

    #emit LOAD.S.pri input
    #emit CONST.alt 0xFF0000
    #emit AND
    #emit CONST.alt 16
    #emit SHR
    #emit LOAD.S.alt result
    #emit ADD
    #emit STOR.S.pri result

    return result;
}
