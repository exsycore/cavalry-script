#if defined _inc_header
#undef _inc_header
#endif

#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_inline>

#define MAX_DEALERSHIPS         (20)      // จำนวนร้านสูงสุด
#define MAX_DEALERSHIP_STOCK    (30)      // รถต่อร้านสูงสุด
#define DEALERSHIP_TABLE        "dealership"
#define DEALERSHIP_STOCK_TABLE  "dealership_stock"

enum E_DEALERSHIP {
    ds_id,
    ds_name[64],
    Float:ds_posx,
    Float:ds_posy,
    Float:ds_posz,
    Float:ds_posa,
    ds_interior,
    ds_world,
    bool:ds_exists,

    // runtime (ไม่ save ลง DB)
    ds_pickup,          // pickup สำหรับเข้าร้าน
    ds_label,           // 3D text label
    ds_previewVehicle,  // vehicle preview ที่โชว์หน้าร้าน
    ds_stockCount       // จำนวนรถที่มีในร้านนี้
}

enum E_DS_STOCK {
    dss_id,
    dss_shopid,
    dss_modelid,
    dss_color1,
    dss_color2,
    dss_price,
    dss_name[64],
    dss_stock,
    bool:dss_exists
}

new DealershipData[MAX_DEALERSHIPS][E_DEALERSHIP];
new DealershipStock[MAX_DEALERSHIPS][MAX_DEALERSHIP_STOCK][E_DS_STOCK];

new PlayerDealershipID[MAX_PLAYERS]     = {-1, ...};
new PlayerDealershipPage[MAX_PLAYERS]   = {0,  ...};

forward LoadDealerships();
forward LoadDealershipStock();
forward OnDealershipCreated(shopid);
forward OnDealershipStockAdded(shopid, slot);
