#if defined _inc_header
    #undef _inc_header
#endif

#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_inline>

#define PUMP_TABLE "pumps"

#define MAX_PUMP        (50)
#define PUMP_TEXT       "{C62C28}ปั้มน้ำมัน\n{FFFFFF}กด {FFFF00}H {FFFFFF}เพื่อเติมน้ำมัน (ต้องอยู่บนรถ)"
#define FUEL_PRICE_PER_UNIT (1)

enum E_PLAYER_PUMP {
    E_PLAYER_Pump_id,
    E_PLAYER_Pump_obj,
    E_PLAYER_Pump_text,
    E_PLAYER_Pump_interior,
    E_PLAYER_Pump_world,

    Float:E_PLAYER_Pump_x,
    Float:E_PLAYER_Pump_y,
    Float:E_PLAYER_Pump_z,

    E_PLAYER_Pump_warpid,

    bool:E_PLAYER_Pump_exists          
}

new PlayerPump[MAX_PUMP][E_PLAYER_PUMP];

new MODEL_PUMP = 3632;

new Float:g_FuelPrice = FUEL_PRICE_PER_UNIT;

forward PumpLoad();
forward OnPumpCreated(pumpid);
