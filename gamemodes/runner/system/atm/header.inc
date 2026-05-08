#if defined _inc_atm_header
    #undef _inc_atm_header
#endif

#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_inline>

#define ATM_TABLE       "atms"
#define MAX_ATM         (100)
#define MODEL_ATM       (19324)
#define ATM_USE_RANGE   (2.5)
#define ATM_LABEL_COLOR (0x00DD00FF)
#define ATM_TEXT "[ATM]\n{FFFFFF}กด 'N' เพื่อใช้งาน"

enum E_ATM {
    E_ATM_id,
    E_ATM_interior,
    E_ATM_world,

    Float:E_ATM_x,
    Float:E_ATM_y,
    Float:E_ATM_z,
    Float:E_ATM_rx,
    Float:E_ATM_ry,
    Float:E_ATM_rz,

    STREAMER_TAG_OBJECT:E_ATM_obj,
    Text3D:E_ATM_label,

    bool:E_ATM_exists
}

new ATMData[MAX_ATM][E_ATM];

new ATM_EditingID[MAX_PLAYERS] = {-1, ...};

forward ATMLoad();
forward OnATMCreated(atmid);