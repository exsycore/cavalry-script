#if defined _inc_header
    #undef _inc_header
#endif

forward public LoadPlayerVehicle(playerid);
forward public SetPlayerVehicle(playerid);
forward public UpdateFuel(playerid);

#define MAX_PLATE_LENGTH (7)
#define MAX_PLAYER_VEHICLE (50)
#define VEHICLE_TABLE "vehicles"

// Speed conversion factor (SA-MP velocity to km/h)
#define VELOCITY_TO_KMH (181.5)

enum E_PLAYER_VEHICLE {
    E_PLAYER_Vehicle_id,                          // ไอดีสำคัญ
    E_PLAYER_Vehicle_ownerid,                     // ไอดีสำคัญ2
    E_PLAYER_Vehicle_modelid,                     // หมายเลขรถ (vehicle model ID)
    E_PLAYER_Vehicle_color1,         	          // สีรถหลัก
    E_PLAYER_Vehicle_color2,         	          // สีรถรอง
    E_PLAYER_Vehicle_owner[MAX_PLAYER_NAME + 1],  // ชื่อเจ้าของรถ
    E_PLAYER_Vehicle_plate[MAX_PLATE_LENGTH + 1], // ทะเบียนรถ
    bool:E_PLAYER_Vehicle_spawned,                // รถถูกเรียกมาใว้แล้วหรือไม่
    bool:E_PLAYER_Vehicle_exists,                 // รถคันนี้มีจริงหรือไม่
    bool:E_PLAYER_Vehicle_lock,

    Float:E_PLAYER_Vehicle_posx,
    Float:E_PLAYER_Vehicle_posy,
    Float:E_PLAYER_Vehicle_posz,
    Float:E_PLAYER_Vehicle_posa,
    Float:E_PLAYER_Vehicle_fuel,
    Float:E_PLAYER_Vehicle_health
}
new PlayerVehicle[MAX_PLAYERS][MAX_PLAYER_VEHICLE][E_PLAYER_VEHICLE]; // จัดเก็บข้อมูลรถของแต่ละผู้เล่น

new const CHAR_SET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
new const g_arrVehicleNames[][] = {
    "Landstalker", "Bravura", "Buffalo", "Linerunner", "Perrenial", "Sentinel", "Dumper", "Firetruck", "Trashmaster",
    "Stretch", "Manana", "Infernus", "Voodoo", "Pony", "Mule", "Cheetah", "Ambulance", "Leviathan", "Moonbeam",
    "Esperanto", "Taxi", "Washington", "Bobcat", "Whoopee", "BF Injection", "Hunter", "Premier", "Enforcer",
    "Securicar", "Banshee", "Predator", "Bus", "Rhino", "Barracks", "Hotknife", "Trailer", "Previon", "Coach",
    "Cabbie", "Stallion", "Rumpo", "RC Bandit", "Romero", "Packer", "Monster", "Admiral", "Squalo", "Seasparrow",
    "Pizzaboy", "Tram", "Trailer", "Turismo", "Speeder", "Reefer", "Tropic", "Flatbed", "Yankee", "Caddy", "Solair",
    "Berkley's RC Van", "Skimmer", "PCJ-600", "Faggio", "Freeway", "RC Baron", "RC Raider", "Glendale", "Oceanic",
    "Sanchez", "Sparrow", "Patriot", "Quad", "Coastguard", "Dinghy", "Hermes", "Sabre", "Rustler", "ZR-350", "Walton",
    "Regina", "Comet", "BMX", "Burrito", "Camper", "Marquis", "Baggage", "Dozer", "Maverick", "News Chopper", "Rancher",
    "FBI Rancher", "Virgo", "Greenwood", "Jetmax", "Hotring", "Sandking", "Blista Compact", "Police Maverick",
    "Boxville", "Benson", "Mesa", "RC Goblin", "Hotring Racer A", "Hotring Racer B", "Bloodring Banger", "Rancher",
    "Super GT", "Elegant", "Journey", "Bike", "Mountain Bike", "Beagle", "Cropduster", "Stunt", "Tanker", "Roadtrain",
    "Nebula", "Majestic", "Buccaneer", "Shamal", "Hydra", "FCR-900", "NRG-500", "HPV1000", "Cement Truck", "Tow Truck",
    "Fortune", "Cadrona", "SWAT Truck", "Willard", "Forklift", "Tractor", "Combine", "Feltzer", "Remington", "Slamvan",
    "Blade", "Streak", "Freight", "Vortex", "Vincent", "Bullet", "Clover", "Sadler", "Firetruck", "Hustler", "Intruder",
    "Primo", "Cargobob", "Tampa", "Sunrise", "Merit", "Utility", "Nevada", "Yosemite", "Windsor", "Monster", "Monster",
    "Uranus", "Jester", "Sultan", "Stratum", "Elegy", "Raindance", "RC Tiger", "Flash", "Tahoma", "Savanna", "Bandito",
    "Freight Flat", "Streak Carriage", "Kart", "Mower", "Dune", "Sweeper", "Broadway", "Tornado", "AT-400", "DFT-30",
    "Huntley", "Stafford", "BF-400", "News Van", "Tug", "Trailer", "Emperor", "Wayfarer", "Euros", "Hotdog", "Club",
    "Freight Box", "Trailer", "Andromada", "Dodo", "RC Cam", "Launch", "LSPD Cruiser", "SFPD Cruiser", "LVPD Cruiser",
    "Police Rancher", "Picador", "S.W.A.T", "Alpha", "Phoenix", "Glendale", "Sadler", "Luggage", "Luggage", "Stairs",
    "Boxville", "Tiller", "Utility Trailer"
};

#include "garage\header"