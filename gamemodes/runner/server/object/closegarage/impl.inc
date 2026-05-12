#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
    CreateDynamicObject(971, 1968.47839, 2162.16748, 11.31600,   0.00000, 0.00000, -90.00000); // LV
	CreateDynamicObject(971, 720.07300, -462.58569, 17.23430,   0.00000, 0.00000, 0.00000); // Dillimore
	CreateDynamicObject(971, -99.92000, 1111.42896, 20.90000,   0.00000, 0.00000, 0.00000); // Fort Carson
	CreateDynamicObject(971, -1420.69995, 2591.14771, 56.94000,   0.00000, 0.00000, -180.00000); // LV
	CreateDynamicObject(971, -1935.00000, 239.48129, 35.51500,   0.00000, 0.00000, 0.00000); // SF
	CreateDynamicObject(971, -1904.47009, 277.84760, 43.50000,   0.00000, 0.00000, 0.00000); // SF
	CreateDynamicObject(971, 2071.62280, -1830.77295, 14.94440,   0.00000, 0.00000, 90.00000); // LS
	CreateDynamicObject(971, 1025.79028, -1029.45764, 32.00000,   0.00000, 0.00000, 0.00000); // LS
	CreateDynamicObject(971, 1042.33875, -1025.97498, 31.87860,   0.00000, 0.00000, 0.00000); // LS
	CreateDynamicObject(971, 488.26001, -1735.25928, 12.73790,   0.00000, 0.00000, -7.80000); // LS
	CreateDynamicObject(971, -2425.36475, 1028.08203, 52.70790,   0.00000, 0.00000, 180.00000); // SF
	CreateDynamicObject(971, 2394.18579, 1483.60706, 13.36593,   0.00000, 0.00000, 0.00000); // LV
	CreateDynamicObject(971, 2387.00000, 1043.56226, 12.29850,   0.00000, 0.00000, 0.00000); // LV
    return 1;
}