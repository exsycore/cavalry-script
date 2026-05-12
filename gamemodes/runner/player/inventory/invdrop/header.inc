#if defined _inc_header
#undef _inc_header
#endif

#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_inline>

forward OnDropItemsLoad();   /// Load drop items if having in database
forward OnDropItemsCreated(id);  /// Create to save in database

forward ClearItemsDrops();
forward DropItemsWarning1();
forward DropItemsWarning2();
forward DoClearItemsDrops();

#define ONE_HOUR_MS     (3600000)
#define TWO_MINUTES_MS  (120000)
#define ONE_MINUTE_MS   (60000)

#define MAX_DROP_ITEMS (300)    /// Max drop items can having in server
#define DROP_ITEMS_TABLE "dropitems"    /// DropItems table name

new DROP_3DTEXT[128] = ""EC_WHITE"ไอเทมที่ตกอยู่: "EC_GREEN"%s\n"EC_GREEN"%d "EC_WHITE"ชิ้น";  /// String for 3DText same pattern

/// Struct of dropData
enum DropEnum {
    dID,
    dObjectID,
    dModelID,
    dItemID,
    Text3D:d3DText,
    dName[128],
    dCount,
    Float:dPos[3],
    bool:dExists
};
new dropData[MAX_DROP_ITEMS][DropEnum];

new Drop_Index[MAX_PLAYERS];
