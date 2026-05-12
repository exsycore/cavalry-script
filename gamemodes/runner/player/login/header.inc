#if defined _inc_header
#undef _inc_header
#endif

#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_inline>

#define SECONDS_TO_LOGIN    (60)

#define PLAYER_TABLE "players"

forward OnPasswordHash(playerid);
forward OnPasswordCheck(playerid, bool:match);
forward public OnLoginFinished(playerid);

// =================================================

forward OnAccountCheck(playerid);
forward OnPlayerLoaded(playerid);
forward OnPlayerRegister(playerid);
forward OnLoginTimeout(playerid);

new REGISTER_TITLE[32] = "{FFFFFF}การลงทะเบียน";
new REGISTER_TEXT[512] = "{FFFFFF}ยินดีต้อนรับสู่ระบบสมาชิก\n{C0C0C0}กรุณาสร้างบัญชีผู้ใช้งานใหม่\n\n{C0C0C0}เพื่อใช้ในการบันทึกข้อมูลและเข้าสู่ระบบ\n\n{AAAAAA}* โปรดกรอกรหัสผ่านให้ยากต่อการคาดเดาเพื่อความปลอดภัยของท่านเอง";

new LOGIN_TITLE[32] = "{FFFFFF}การเข้าสู่ระบบ";
new LOGIN_TEXT[512] = "{FFFFFF}ยินดีต้อนรับกลับ\n\n{C0C0C0}กรุณาเข้าสู่ระบบด้วยบัญชีผู้ใช้งานของท่าน\n{C0C0C0}เพื่อดำเนินการต่อจากข้อมูลที่ได้บันทึกไว้\n\n{AAAAAA}* โปรดกรอกรหัสผ่านให้ถูกต้อง";

enum PLAYER_DATA {
	pID,
	pGender,
	pRegisterDate[90],
	pAdmin,
	LoginTimer,
	bool: IsLoggedIn,
	pMoney,
	pBank,
	pRedMoney,
    pSkin,
    Float: pPosX,
    Float: pPosY,
    Float: pPosZ,
    Float: pPosA,
    Float: pHealth,
    Float: pArmour,
    pExp,
    pLevel,
    Float: pHungry,
    Float: pThirsty,
    pInDeath,
    pInjuredTimer,
    pInjuredTime,
    pFaction,
    pRank,
    pGang,
    pGangRank,
    pEquippedWeaponSlot,
    pPassport,

    // ============================ [INVENTORY] ===============================

	pSecondpage,
    pInventory[72],         // เก็บ Item ID ในแต่ละ Slot (72 Slots)
    pInventoryKolvo[72],    // เก็บจำนวน Item ในแต่ละ Slot
    pInventoryKolvoDop,
    pDopInv[72],            // Inventory เสริม (สำหรับรถ/ตู้เสื้อผ้า)
    pSlotItem[8],           // Slot สำหรับอุปกรณ์ตกแต่ง (8 ชิ้น) ? ใช้ใน invnew.pwn
    pInventori,             // สถานะเปิด Inventory (0 = ปิด, 1 = เปิด)
    pInventori2,            // สถานะเปิด Inventory แบบพิเศษ
    pInvColors,             // ธีมสีของ Inventory (0-8) ? ใช้ใน invnew.pwn
    pColorInv,              // สีที่เลือก ? ใช้ใน invnew.pwn
    pChestTime,             // เวลาเปิดหีบ (สำหรับ Item พิเศษ)

    // ใบอนุญาตต่างๆ (ถ้ายังไม่มี)
    pCarLic,                // ใบขับขี่รถยนต์
    pBikeLic,               // ใบขับขี่มอเตอร์ไซค์
    pBoatLic,               // ใบขับขี่เรือ
    pFlyLic,                // ใบขับขี่เครื่องบิน
    pGunLic,                // ใบอนุญาตพกพาอาวุธ

    pTypeSpeed,
    Float: pInvPos_X,
    Float: pInvPos_Y,
    Float: pInvSize_X,
    Float: pInvSize_Y,

    pCheepsTimer,
    pDolboeb,
    pDopKletki,
    pTrashOpen,
    pProstoTak2,
	pProstoTak

    // =========================================================================
};
new playerData[MAX_PLAYERS][PLAYER_DATA];

new SelectGender[MAX_PLAYERS] = 0;
