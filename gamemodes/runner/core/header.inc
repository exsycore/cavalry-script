#if defined _inc_header
#undef _inc_header
#endif

#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>
#include <YSI_Visual\y_commands>
#include <YSI_Core\y_master>

new PlayerText:buildVersionName[MAX_PLAYERS];

enum int {};
enum void {};

#if !defined IsValidVehicle
	native bool:IsValidVehicle(vehicleid);
#endif
