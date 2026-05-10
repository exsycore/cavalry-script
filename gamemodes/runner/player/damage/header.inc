#if defined _inc_header
#undef _inc_header
#endif

#define BODY_PART_HEAD (9)

enum E_CUSTOM_WEAPON {
    CW_Name[32],            /// ชื่อที่แสดง เช่น "Desert Eagle+", "AK-47 Elite"
    WEAPON:CW_BaseWeaponID, /// weapon id ฐาน (ใช้ตรวจ OnPlayerDamage)
    Float:CW_Damage,        /// ดาเมจต่อนัด
    CW_DamageType,          /// DAMAGE_TYPE_STATIC / DAMAGE_TYPE_MULTIPLIER / DAMAGE_TYPE_RANGE
    Float:CW_Range,         /// ระยะยิงสูงสุด (0.0 = ใช้ค่าเดิม)
    bool:CW_HeadshotBonus,  /// เพิ่มดาเมจเมื่อยิงหัว
    Float:CW_HeadshotMult,  /// ตัวคูณ headshot (เช่น 2.0 = x2)
    bool:CW_AffectsArmour,  /// โดนเกราะก่อนไหม
    bool:CW_TorsoOnly,      /// เกราะโดนแค่ torso ไหม
    CW_SoundHit,            /// เสียงเมื่อโดน (0 = ไม่มี)
}

new const g_WeaponTable[][E_CUSTOM_WEAPON] = {
    /// [ชื่ออาวุธ]            [เลขอาวุธ]                  [ดาเมจ]
    { "Brass Knuckle",      WEAPON_BRASSKNUCKLE,      1.2,  DAMAGE_TYPE_MULTIPLIER, 0.0,  false, 1.0, false, false },
    { "Golf Club",          WEAPON_GOLFCLUB,          1.5,  DAMAGE_TYPE_MULTIPLIER, 0.0,  false, 1.0, false, false },
    { "Nightstick",         WEAPON_NITESTICK,         1.3,  DAMAGE_TYPE_MULTIPLIER, 0.0,  false, 1.0, false, false },
    { "Knife",              WEAPON_KNIFE,             1.0,  DAMAGE_TYPE_MULTIPLIER, 0.0,  false, 1.0, false, false },
    { "Baseball Bat",       WEAPON_BAT,               1.4,  DAMAGE_TYPE_MULTIPLIER, 0.0,  false, 1.0, false, false },
    { "Shovel",             WEAPON_SHOVEL,            1.3,  DAMAGE_TYPE_MULTIPLIER, 0.0,  false, 1.0, false, false },
    { "Pool Cue",           WEAPON_POOLSTICK,         1.2,  DAMAGE_TYPE_MULTIPLIER, 0.0,  false, 1.0, false, false },
    { "Katana",             WEAPON_KATANA,            2.0,  DAMAGE_TYPE_MULTIPLIER, 0.0,  true,  3.0, false, false },
    { "Chainsaw",           WEAPON_CHAINSAW,          3.0,  DAMAGE_TYPE_MULTIPLIER, 0.0,  false, 1.0, false, false },
    { "Dildo",              WEAPON_DILDO,             0.8,  DAMAGE_TYPE_MULTIPLIER, 0.0,  false, 1.0, false, false },
    { "Dildo2",             WEAPON_DILDO2,            0.8,  DAMAGE_TYPE_MULTIPLIER, 0.0,  false, 1.0, false, false },
    { "Vibrator",           WEAPON_VIBRATOR,          0.8,  DAMAGE_TYPE_MULTIPLIER, 0.0,  false, 1.0, false, false },
    { "Vibrator2",          WEAPON_VIBRATOR2,         0.8,  DAMAGE_TYPE_MULTIPLIER, 0.0,  false, 1.0, false, false },
    { "Flower",             WEAPON_FLOWER,            0.5,  DAMAGE_TYPE_MULTIPLIER, 0.0,  false, 1.0, false, false },
    { "Cane",               WEAPON_CANE,              0.7,  DAMAGE_TYPE_MULTIPLIER, 0.0,  false, 1.0, false, false },

    { "Grenade",            WEAPON_GRENADE,           1.5,  DAMAGE_TYPE_MULTIPLIER, 0.0, false, 1.0, false, false },
    { "Teargas",            WEAPON_TEARGAS,           0.3,  DAMAGE_TYPE_MULTIPLIER, 0.0, false, 1.0, false, false },
    { "Molotov",            WEAPON_MOLTOV,            1.2,  DAMAGE_TYPE_MULTIPLIER, 0.0, false, 1.0, false, false },
    { "Satchel",            WEAPON_SATCHEL,           2.0,  DAMAGE_TYPE_MULTIPLIER, 0.0, false, 1.0, false, false },
    { "Bomb",               WEAPON_BOMB,              2.5,  DAMAGE_TYPE_MULTIPLIER, 0.0, false, 1.0, false, false },

    { "Colt 45",            WEAPON_COLT45,            22.0, DAMAGE_TYPE_STATIC, 0.0, false, 1.5, true,  false },
    { "Silenced Pistol",    WEAPON_SILENCED,          28.0, DAMAGE_TYPE_STATIC, 0.0, true,  2.0, true,  false },
    { "Desert Eagle",       WEAPON_DEAGLE,            35.0, DAMAGE_TYPE_STATIC, 0.0, true,  2.0, true,  false },
    { "Desert Eagle+",      WEAPON_DEAGLE,            50.0, DAMAGE_TYPE_STATIC, 0.0, true,  2.5, false, false },
    { "Shotgun",            WEAPON_SHOTGUN,           8.0,  DAMAGE_TYPE_STATIC, 0.0, false, 1.0, true, true },
    { "Sawnoff Shotgun",    WEAPON_SAWEDOFF,          10.0, DAMAGE_TYPE_STATIC, 0.0, false, 1.0, true, true },
    { "Combat Shotgun",     WEAPON_SHOTGSPA,          12.0, DAMAGE_TYPE_STATIC, 0.0, false, 1.0, true, true },
    { "Micro Uzi",          WEAPON_UZI,               18.0, DAMAGE_TYPE_STATIC, 0.0, false, 1.5, true, false },
    { "MP5",                WEAPON_MP5,               20.0, DAMAGE_TYPE_STATIC, 0.0, true,  1.8, true, true  },
    { "Tec-9",              WEAPON_TEC9,              18.0, DAMAGE_TYPE_STATIC, 0.0, false, 1.5, true, false },
    { "AK-47",              WEAPON_AK47,              34.0, DAMAGE_TYPE_STATIC, 0.0, true, 2.0, true, true  },
    { "M4",                 WEAPON_M4,                30.0, DAMAGE_TYPE_STATIC, 0.0, true, 2.0, true, true  },
    { "Rifle",              WEAPON_RIFLE,             40.0, DAMAGE_TYPE_RANGE, 150.0, true, 2.0, false, false },
    { "Sniper Rifle",       WEAPON_SNIPER,            50.0, DAMAGE_TYPE_RANGE, 200.0, true, 2.5, false, false },
    { "Rocket Launcher",    WEAPON_ROCKETLAUNCHER,    2.0,  DAMAGE_TYPE_MULTIPLIER, 0.0, false, 1.0, false, false },
    { "Heat Seeker",        WEAPON_HEATSEEKER,        2.0,  DAMAGE_TYPE_MULTIPLIER, 0.0, false, 1.0, false, false },
    { "Flamethrower",       WEAPON_FLAMETHROWER,      0.5,  DAMAGE_TYPE_MULTIPLIER, 0.0, false, 1.0, false, false },
    { "Minigun",            WEAPON_MINIGUN,           1.5,  DAMAGE_TYPE_MULTIPLIER, 0.0, false, 1.0, false, false },
    { "Spraycan",           WEAPON_SPRAYCAN,          0.1,  DAMAGE_TYPE_MULTIPLIER, 0.0, false, 1.0, false, false },
    { "Fire Extinguisher",  WEAPON_FIREEXTINGUISHER,  0.1,  DAMAGE_TYPE_MULTIPLIER, 0.0, false, 1.0, false, false },
    { "Camera",             WEAPON_CAMERA,            0.0,  DAMAGE_TYPE_MULTIPLIER, 0.0, false, 1.0, false, false },

    { "Vehicle",            WEAPON_VEHICLE,           2.0,  DAMAGE_TYPE_MULTIPLIER, 0.0, false, 1.0, false, false },
    { "Drowning",           WEAPON_DROWN,             1.0,  DAMAGE_TYPE_MULTIPLIER, 0.0, false, 1.0, false, false },
    { "Collision",          WEAPON_COLLISION,         1.0,  DAMAGE_TYPE_MULTIPLIER, 0.0, false, 1.0, false, false }
};

#define MAX_CUSTOM_WEAPONS (sizeof(g_WeaponTable))

new g_PlayerCustomWeapon[MAX_PLAYERS] = { -1, ... };

forward OnPlayerChangeWeapon(playerid, oldweapon, newweapon);
