#if defined _inc_header
	#undef _inc_header
#endif

#define     MAX_APPLE          11
#define		APPLE_AMOUNT	   50
#define     APPLE_OBJECT       717
#define		APPLE_TIME	       1000
#define     APPLE_TEXT         "[Apple Growers]\n{FFFFFF}กด N เพื่อเก็บน้ำแอปเปิ้ล\n{FFE200}จำนวน 50 ลูก"

#define SendErrorMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_RED, "[ERROR]: {FFFFFF}"%1)

new ApplePick[MAX_PLAYERS];
new AppleStart[MAX_PLAYERS];
new AppleCount[MAX_PLAYERS];
new AppleProcress[MAX_PLAYERS];

enum E_APPLE_DATA {
	appleID,
	bool: appleExists,
	appleObject,
    Float: applePosX,
	Float: applePosY,
	Float: applePosZ,
	Text3D: appleText3D,
    Apple3DText[80],
    AppleAmount,
};

new const AppleData[MAX_APPLE][E_APPLE_DATA] = {
	{ INVALID_STREAMER_ID, true, APPLE_OBJECT, 1250.0171,-2367.4282,10.0103, Text3D: INVALID_3DTEXT_ID, APPLE_TEXT, APPLE_AMOUNT },
	{ INVALID_STREAMER_ID, true, APPLE_OBJECT, 1256.5117,-2379.3113,10.0103, Text3D: INVALID_3DTEXT_ID, APPLE_TEXT, APPLE_AMOUNT },
	{ INVALID_STREAMER_ID, true, APPLE_OBJECT, 1259.1796,-2389.9395,10.0103, Text3D: INVALID_3DTEXT_ID, APPLE_TEXT, APPLE_AMOUNT },
	{ INVALID_STREAMER_ID, true, APPLE_OBJECT, 1257.6785,-2399.5190,10.0103, Text3D: INVALID_3DTEXT_ID, APPLE_TEXT, APPLE_AMOUNT },
	{ INVALID_STREAMER_ID, true, APPLE_OBJECT, 1233.4410,-2410.3887,10.0103, Text3D: INVALID_3DTEXT_ID, APPLE_TEXT, APPLE_AMOUNT },
	{ INVALID_STREAMER_ID, true, APPLE_OBJECT, 1250.4612,-2408.0964,10.0103, Text3D: INVALID_3DTEXT_ID, APPLE_TEXT, APPLE_AMOUNT },
	{ INVALID_STREAMER_ID, true, APPLE_OBJECT, 1231.0887,-2401.3521,10.0103, Text3D: INVALID_3DTEXT_ID, APPLE_TEXT, APPLE_AMOUNT },
	{ INVALID_STREAMER_ID, true, APPLE_OBJECT, 1241.3854,-2409.1531,10.0103, Text3D: INVALID_3DTEXT_ID, APPLE_TEXT, APPLE_AMOUNT },
	{ INVALID_STREAMER_ID, true, APPLE_OBJECT, 1227.9408,-2394.9209,10.0103, Text3D: INVALID_3DTEXT_ID, APPLE_TEXT, APPLE_AMOUNT },
	{ INVALID_STREAMER_ID, true, APPLE_OBJECT, 1223.2269,-2387.2354,10.0103, Text3D: INVALID_3DTEXT_ID, APPLE_TEXT, APPLE_AMOUNT },
	{ INVALID_STREAMER_ID, true, APPLE_OBJECT, 1225.6143,-2381.9412,10.0103, Text3D: INVALID_3DTEXT_ID, APPLE_TEXT, APPLE_AMOUNT }
};

stock ShowJobInApple(playerid) {
    if (Player.Auth[playerid][@isloggedin] == false) 
        return true;

    new string[1024];
	new string2[1024];

    format(string, sizeof(string), "{ffffff}หัวข้อ\t{000000}-\t{000000}-\n");
	strcat(string2,string);
	
    format(string, sizeof(string), "{ffffff}เข้าสู่งาน\t{000000}-\t{000000}-\n");
	strcat(string2,string);

    format(string, sizeof(string), "{ffffff}ออกจากงาน\t{000000}-\t{000000}-\n");
	strcat(string2,string);

	Dialog_Show(playerid, AppleJobIn, DIALOG_STYLE_TABLIST_HEADERS, "สมัครงาน แอปเปิ้ล", string2, "เลือก", "ปิด");
    return true;
}