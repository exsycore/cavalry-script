#if defined _inc_header
    #undef _inc_header
#endif

#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_inline>
#include <YSI_Extra\y_inline_mysql>

#define GANG_TABLE          "gang"
#define MAX_GANGS           (50)
#define MAX_GANGS_MEMBERS   (8)

#define INVALID_GANG_SKIN   (-1)
#define INVALID_GANG        (-1)

#define LEADER_GANG         (5)
#define OFFICER_GANG        (4)

enum E_PLAYER_GANGS {
    E_PLAYER_Gang_id,
    E_PLAYER_Gang_name[128],
    E_PLAYER_Gang_leader[128],
    E_PLAYER_Gang_officer[128],
    E_PLAYER_Gang_gangcolor,
    E_PLAYER_Gang_gangobject,
    E_PLAYER_Gang_money,
    E_PLAYER_Gang_redmoney,
    E_PLAYER_Gang_gangskin[3],

    Float:E_PLAYER_Gang_gangx,
    Float:E_PLAYER_Gang_gangy,
    Float:E_PLAYER_Gang_gangz,
    Float:E_PLAYER_Gang_ganga,

    Text3D:E_PLAYER_Gang_gangtext3d,
    bool:E_PLAYER_Gang_exists          
}

new PlayerGang[MAX_GANGS][E_PLAYER_GANGS];

new MODEL_GANGS         = 1210;
new TEXT3D_GANGS[128]   = "คลัง/ตู้เซฟ\n{FFFFFF}กดปุ่ม 'N' เพื่อเปิดคลังหรือตู้เซฟ";
new STREAMER_TAG_3D_TEXT_LABEL:gangLabel[MAX_PLAYERS];

forward GangLoad();
forward OnGangCreated(playerid, gangid);
forward DelayedGangRefresh(gangid);
forward DelayedGangRefresh2(gangid);

#include "locker\header"
