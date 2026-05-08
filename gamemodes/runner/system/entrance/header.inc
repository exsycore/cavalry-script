#if defined _inc_header
    #undef _inc_header
#endif

#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_inline>

#define ENTRANCE_TABLE "entrances"

#define MAX_ENTRANCE        (50)
#define ENTRANCE_COOLDOWN   (5000) // millis

enum E_PLAYER_ENTRANCE {
    E_PLAYER_Entrance_id,
    E_PLAYER_Entrance_obj,
    E_PLAYER_Entrance_interior,
    E_PLAYER_Entrance_world,
    E_PLAYER_Entrance_tointerior,
    E_PLAYER_Entrance_toworld,

    Float:E_PLAYER_Entrance_x,
    Float:E_PLAYER_Entrance_y,
    Float:E_PLAYER_Entrance_z,
    Float:E_PLAYER_Entrance_a,
    Float:E_PLAYER_Entrance_tox,
    Float:E_PLAYER_Entrance_toy,
    Float:E_PLAYER_Entrance_toz,
    Float:E_PLAYER_Entrance_toa,

    E_PLAYER_Entrance_warpid,

    bool:E_PLAYER_Entrance_exists          
}

new PlayerEntrance[MAX_ENTRANCE][E_PLAYER_ENTRANCE];

new MODEL_ENTRANCE = 19197;
new EntranceCooldown[MAX_PLAYERS];

forward EntranceLoad();
forward OnEntranceCreated(entranceid);
