#if defined _inc_header
    #undef _inc_header
#endif

#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_inline>

#define GPS_TABLE    "gps_locations"
#define MAX_GPS      (200)
#define GPS_CP_SIZE  (3.0)
#define GPS_CP_SD    (200.0)

#define GPS_CAT_PLACE       (0)   // สถานที่ทั่วไป
#define GPS_CAT_WORK        (1)   // ที่ทำงาน (ถูกกฎหมาย)
#define GPS_CAT_ILLEGAL     (2)   // ที่ทำงาน (ผิดกฎหมาย)
#define GPS_CAT_MAX         (3)

new const GPS_CAT_NAME[GPS_CAT_MAX][] = {
    "สถานที่",
    "ที่ทำงาน",
    "ที่ทำงาน (ผิดกฎหมาย)"
};

new const GPS_CAT_COLOR[GPS_CAT_MAX][] = {
    "{FFFFFF}",
    "{FFFFFF}",
    "{FF4444}"
};

enum E_GPS {
    E_GPS_id,
    E_GPS_name[64],
    E_GPS_category,

    Float:E_GPS_x,
    Float:E_GPS_y,
    Float:E_GPS_z,

    bool:E_GPS_exists
}

new GPSData[MAX_GPS][E_GPS];

new GPS_ActiveID[MAX_PLAYERS]       = {-1, ...};
new STREAMER_TAG_CP:GPS_CP[MAX_PLAYERS];

forward GPSLoad();
forward OnGPSCreated(gpsid);
