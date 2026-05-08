#if defined _inc_header
    #undef _inc_header
#endif

#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_inline>

#define MAX_PAWNCAR (50)

enum E_PLAYER_PAWN {
    E_PLAYER_Pawn_id,
    E_PLAYER_Pawn_pawnpickup,
    E_PLAYER_Pawn_pawnicon,

    Float:E_PLAYER_Pawn_pawnx,
    Float:E_PLAYER_Pawn_pawny,
    Float:E_PLAYER_Pawn_pawnz,

    Text3D:E_PLAYER_Pawn_pawntext3d,
    bool:E_PLAYER_Pawn_exists          
}

new PlayerPawn[MAX_PAWNCAR][E_PLAYER_PAWN];

new MODEL_PAWN = 19132;
new TEXT3D_PAWN[128] = "{d13d32}จุดพาวน์รถ\n{FFFFFF}กดปุ่ม 'N' เพื่อพาวน์รถของท่าน";

forward public PawnLoad();
forward public OnPawnCreated(pawnid);
forward public OnPlayerSpawnVehicle2(playerid, listitem);