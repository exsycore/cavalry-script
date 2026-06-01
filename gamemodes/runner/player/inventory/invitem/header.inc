#if defined _inc_header
#undef _inc_header
#endif

#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_inline>

forward CheepsTimer(playerid);
forward DeleteItem(playerid, itemid, amount);
forward Custom_AddInvItem(playerid, slot, itemid, quantity);
forward Custom_SetInvItem(playerid, slot, itemid, quantity);

#define SKIN_START (1)
#define ITEM_START (312)
#define ITEMS_PER_PAGE (60)
#define INVALID_SLOT (-1)
#define MAX_INVENTORY_SLOTS (72)

new clickOnSkin[MAX_PLAYERS];
new bool:weaponOn[MAX_PLAYERS] = {false, ...};
new g_PlayerLastAmmo[MAX_PLAYERS] = {-1, ...};
new FishingRod[MAX_PLAYERS];

stock bool:HasItem(playerid, itemid);
stock GetItemAmount(playerid, itemid);
stock GetItemAmountByName(playerid, const name[]);