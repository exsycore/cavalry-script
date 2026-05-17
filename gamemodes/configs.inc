#if defined _inc_configs
#undef _inc_configs
#endif

#define CGEN_MEMORY (50000)

// สามารถเปิดใช้งานเวลา Test กันตัวเองด้วยเน็ตเดียวกันได้
#define DISABLE_ANTICHEAT

#define SERVER_NAME 	"[SA:MP] Cavalry City | Pre-Beta"
#define	SERVER_MODE		"Roleplay"
#define SERVER_LANGUAGE "Thai"
#define SERVER_WEBSITE  "-"
#define SERVER_COLOUR 	(0xF73E24FF)

#define DEFAULT_POS_X (2845.8337)
#define DEFAULT_POS_Y (2415.3398)
#define DEFAULT_POS_Z (11.0690)
#define DEFAULT_POS_A (225.4016)

#define DEFAULT_MONEY 		(0)
#define DEFAULT_RED_MONEY	(0)
#define DEFAULT_PLAYER_BANK	(0)

#define DEFAULT_PLAYER_SKIN_MALE (18)
#define DEFAULT_PLAYER_SKIN_FEMALE (56)

#define DEFAULT_PLAYER_HEALTH (100.00)
#define DEFAULT_PLAYER_ARMOUR (0.00)

#define DEFAULT_LOAD_OBJECT (2000) // 2 sec

#define DEFAULT_PLAYER_EXP   (0.00)
#define DEFAULT_PLAYER_LEVEL (1)

#define GENDER_MALE (1)
#define GENDER_FEMALE (2)

#define DEFAULT_PLAYER_HUNGRY (100.0)
#define DEFAULT_PLAYER_THIRSTY (100.0)

#define DEFAULT_PLAYER_FACTION (-1)
#define DEFAULT_PLAYER_RANK (0)

#define DEFAULT_PLAYER_PASSPORT (0)

#define DEFAULT_PLAYER_GIFTBOX (0)
#define DEFAULT_PLAYER_GIFTBOX2 (0)

#define MODEL_NULL (18700)

// ===================================================================================

#define PRESSED(%0) (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define RELEASED(%0) (((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))

#define PRESS_Y (65536)
#define PRESS_C (2)
#define PRESS_N (131072)
#define PRESS_F (16)
#define PRESS_TAB (1)
#define PRESS_H (262144)
#define PRESS_CAPSLOCK (128)
#define PRESS_SHIFT (32)
#define PRESS_CTRL (4)
#define PRESS_ALT (1024)
#define PRESS_QSPACE(256)
#define PRESS_E (64)
#define PRESS_Q (256)

#define OO_TYPE(%6,%7)%0[%1] (_:@vb:@va:%6:%7@%0[%1]
#define @va:%6:%7@%0[%1][@%2] %7%0[%1])[E_%6_%0_%2]
#define @vb:@va:%6:%7@%0[%1][%2][@%3] %7%0[%1])[%2][E_%6_%0_%3]

#define Player. OO_TYPE(PLAYER, Player)

#define SendErrorMessage(%0,%1) \
	va_SendClientMessage(%0, COLOR_RED, "[ข้อผิดพลาด]: {FFFFFF}"%1)
	
#define SendTipsMessage(%0,%1) \
	va_SendClientMessage(%0, COLOR_GRAY, "[เคล็ดลับ]: {FFFFFF}"%1)

#define SendPlayerAction(%0,%1) \
	va_SendClientMessage(%0, COLOR_GREEN, "[>>] {FFFFFF}"%1)

#define SendGarageAction(%0,%1) \
	va_SendClientMessage(%0, COLOR_ORANGE, "[การาจ]: {FFFFFF}"%1)

#define SendSyntaxMessage(%0,%1) \
	va_SendClientMessage(%0, COLOR_CLIENT, "[Syntax]: {FFFFFF}"%1)

#define SendWarningMessage(%0,%1) \
	va_SendClientMessage(%0, COLOR_RED, "[Warning]: {FFFFFF}"%1)

#define SendCongratMessage(%0,%1) \
	va_SendClientMessage(%0, COLOR_GREEN, "[Congrat]: {FFFFFF}"%1)

DEFINE_HOOK_REPLACEMENT__(OnPlayer   , OP_);