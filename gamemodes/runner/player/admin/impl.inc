#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

YCMD:arevive(playerid, const params[], help) {
    if (!GetPlayerLoggedIn(playerid)) return 1;
    if (!IsPlayerAdminEx(playerid)) return 1;

    new userId;
    if (sscanf(params, "d", userId))
        return SendSyntaxMessage(playerid, "/arevive [ไอดี]");
    
    if (!IsPlayerConnected(userId))
        return SendErrorMessage(playerid, "ผู้เล่นคนนี้ยังไม่ออนไลน์");

    if (!GetPlayerLoggedIn(userId))
        return SendErrorMessage(playerid, "ผู้เล่นคนนี้ยังไม่เข้าสู่ระบบ");

    RescuePlayer(userId);
    SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ได้ทำการชุบชีวิตของ %s[%d]", ReturnPlayerName(playerid), ReturnPlayerName(userId), userId);
    return 1;
}

YCMD:sethealth(playerid, const params[], help) {
    if (!GetPlayerLoggedIn(playerid)) return 1;
    if (!IsPlayerAdminEx(playerid)) return 1;

    new userId, playerHealth;
    if (sscanf(params, "dd", userId, playerHealth))
        return SendSyntaxMessage(playerid, "/sethealth [ไอดี] [จำนวนเลือด]");
    
    if (!IsPlayerConnected(userId))
        return SendErrorMessage(playerid, "ผู้เล่นคนนี้ยังไม่ออนไลน์");

    if (!GetPlayerLoggedIn(userId))
        return SendErrorMessage(playerid, "ผู้เล่นคนนี้ยังไม่เข้าสู่ระบบ");

    SetPlayerHealth(userId, playerHealth);
    UpdatePlayerData(playerid);

    SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ได้ทำการปรับเลือดของ %s[%d] เป็น %d", ReturnPlayerName(playerid), ReturnPlayerName(userId), userId, playerHealth);

    Query(get_handle()
        , "UPDATE "PLAYER_TABLE" SET `playerHealth` = '%.2f' WHERE `playerID` = '%i' LIMIT 1;"
        , playerData[userId][pHealth]
        , playerData[userId][pID]
    );
    return 1;
}

YCMD:sethungry(playerid, const params[], help) {
    if (!GetPlayerLoggedIn(playerid)) return 1;
    if (!IsPlayerAdminEx(playerid)) return 1;

    new userId, hungryVal;
    if (sscanf(params, "dd", userId, hungryVal))
        return SendSyntaxMessage(playerid, "/sethungry [ไอดี] [ค่าความหิว]");
    
    if (!IsPlayerConnected(userId))
        return SendErrorMessage(playerid, "ผู้เล่นคนนี้ยังไม่ออนไลน์");

    if (!GetPlayerLoggedIn(userId))
        return SendErrorMessage(playerid, "ผู้เล่นคนนี้ยังไม่เข้าสู่ระบบ");

    SetPlayerHungry(userId, hungryVal);

    SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ได้ทำการปรับค่าความหิวของ %s[%d] เป็น %d", ReturnPlayerName(playerid), ReturnPlayerName(userId), userId, hungryVal);
    return 1;
}

YCMD:setthirsty(playerid, const params[], help) {
    if (!GetPlayerLoggedIn(playerid)) return 1;
    if (!IsPlayerAdminEx(playerid)) return 1;

    new userId, thirstyVal;
    if (sscanf(params, "dd", userId, thirstyVal))
        return SendSyntaxMessage(playerid, "/setthirsty [ไอดี] [ค่าความหิวน้ำ]");
    
    if (!IsPlayerConnected(userId))
        return SendErrorMessage(playerid, "ผู้เล่นคนนี้ยังไม่ออนไลน์");

    if (!GetPlayerLoggedIn(userId))
        return SendErrorMessage(playerid, "ผู้เล่นคนนี้ยังไม่เข้าสู่ระบบ");

    SetPlayerThirsty(userId, thirstyVal);

    SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ได้ทำการปรับค่าความหิวน้ำของ %s[%d] เป็น %d", ReturnPlayerName(playerid), ReturnPlayerName(userId), userId, thirstyVal);
    return 1;
}

YCMD:givemoney(playerid, string:params[], help) {
    if (!GetPlayerLoggedIn(playerid)) return 1;
    if (!IsPlayerAdminEx(playerid)) return 1;

    new targetid, money;
    if (sscanf(params, "ui", targetid, money))
        return SendSyntaxMessage(playerid, "/givemoney [ไอดี/ชื่อ] [จำนวน]");
    
    if (!IsPlayerConnected(targetid))
        return SendErrorMessage(playerid, "ผู้เล่นคนนี้ยังไม่ออนไลน์");

    if (!GetPlayerLoggedIn(targetid))
        return SendErrorMessage(playerid, "ผู้เล่นคนนี้ยังไม่เข้าสู่ระบบ");

    GivePlayerMoneyEx(targetid, money);
    SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ได้เพิ่มเงินเขียวให้กับ %s[%d] เป็นจำนวน %d บาท", ReturnPlayerName(playerid), ReturnPlayerName(targetid), targetid, money);
    return 1;
}

YCMD:setmoney(playerid, string:params[], help) {
    if (!GetPlayerLoggedIn(playerid)) return 1;
    if (!IsPlayerAdminEx(playerid)) return 1;

    new targetid, money;
    if (sscanf(params, "ui", targetid, money))
        return SendSyntaxMessage(playerid, "/setmoney [ไอดี/ชื่อ] [จำนวน]");
    
    if (!IsPlayerConnected(targetid))
        return SendErrorMessage(playerid, "ผู้เล่นคนนี้ยังไม่ออนไลน์");

    if (!GetPlayerLoggedIn(targetid))
        return SendErrorMessage(playerid, "ผู้เล่นคนนี้ยังไม่เข้าสู่ระบบ");

    SetPlayerMoneyEx(targetid, money);
    SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ได้ปรับเงินเขียวให้กับ %s[%d] เป็นจำนวน %d บาท", ReturnPlayerName(playerid), ReturnPlayerName(targetid), targetid, money);
    return 1;
}

YCMD:setadmin(playerid, const params[], help) {
	if (!GetPlayerLoggedIn(playerid)) return 1;
    if (!IsPlayerAdminEx(playerid)) return 1;
	
    new userid, level;
    if (sscanf(params, "ud", userid, level))
        return va_SendClientMessage(playerid, COLOR_WHITE, "/setadmin [ไอดี/ชื่อ] [เลเวล]");

    if (!GetPlayerLoggedIn(playerid))
        return va_SendClientMessage(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ผู้เล่นไอดีนี้ไม่ได้ล็อกอิน");

    if (userid == INVALID_PLAYER_ID)
        return va_SendClientMessage(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ผู้เล่นไอดีนี้ไม่ได้อยู่ในเกม");

    playerData[userid][pAdmin] = level;
    UpdatePlayerData(userid);
    
    SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ได้ปรับเลเวลแอดมินให้กับ %s(%d) เป็นแอดมินเลเวล %d", GetPlayerNameEx(playerid), GetPlayerNameEx(userid), userid, level);
    return 1;
}

YCMD:adminmenu(playerid, string:params[], help) {
    if (!GetPlayerLoggedIn(playerid)) return 1;
    if (!IsPlayerAdminEx(playerid)) return 1;

    inline AdminMenu(res, list, string:in[]) {
        #pragma unused in
        if (!res) @return 1;

        switch (list) {
            case 0: { // หมวดหมู่ทั่วไป
                inline GeneralAdmin(res2, list2, string:in2[]) {
                    #pragma unused in2
                    if (!res2) @return Command_ReProcess(playerid, "/adminmenu", 0);

                    switch (list2) {
                        case 0: { // ปรับเลือด
                            inline InputHP(res3, list3, string:in3[]) {
                                #pragma unused list3
                                if (!res3) @return Command_ReProcess(playerid, "/adminmenu", 0);

                                new userId, hp;
                                if (sscanf(in3, "dd", userId, hp)) {
                                    SendErrorMessage(playerid, "{FFFFFF}รูปแบบไม่ถูกต้อง เช่น: 5 100");
                                    @return Command_ReProcess(playerid, "/adminmenu", 0);
                                }
                                new str[64];
                                format(str, sizeof str, "/sethealth %d %d", userId, hp);
                                Command_ReProcess(playerid, str, 0);
                            }
                            Dialog_ShowCallback(playerid, using inline InputHP, DIALOG_STYLE_INPUT,
                                "{FFFFFF}ปรับเลือด",
                                "{FFFFFF}กรอก: {FFFF00}[ไอดี] [จำนวนเลือด]\n{AAAAAA}ตัวอย่าง: 5 100",
                                "{FFFFFF}ยืนยัน", "{FFFFFF}กลับ");
                        }
                        case 1: { // ปรับค่าอาหาร
                            inline InputHungry(res3, list3, string:in3[]) {
                                #pragma unused list3
                                if (!res3) @return Command_ReProcess(playerid, "/adminmenu", 0);

                                new userId, val;
                                if (sscanf(in3, "dd", userId, val)) {
                                    SendErrorMessage(playerid, "{FFFFFF}รูปแบบไม่ถูกต้อง เช่น: 5 100");
                                    @return Command_ReProcess(playerid, "/adminmenu", 0);
                                }
                                new str[64];
                                format(str, sizeof str, "/sethungry %d %d", userId, val);
                                Command_ReProcess(playerid, str, 0);
                            }
                            Dialog_ShowCallback(playerid, using inline InputHungry, DIALOG_STYLE_INPUT,
                                "{FFFFFF}ปรับค่าอาหาร",
                                "{FFFFFF}กรอก: {FFFF00}[ไอดี] [ค่าความหิว]\n{AAAAAA}ตัวอย่าง: 5 100",
                                "{FFFFFF}ยืนยัน", "{FFFFFF}กลับ");
                        }
                        case 2: { // ปรับค่าน้ำ
                            inline InputThirsty(res3, list3, string:in3[]) {
                                #pragma unused list3
                                if (!res3) @return Command_ReProcess(playerid, "/adminmenu", 0);

                                new userId, val;
                                if (sscanf(in3, "dd", userId, val)) {
                                    SendErrorMessage(playerid, "{FFFFFF}รูปแบบไม่ถูกต้อง เช่น: 5 100");
                                    @return Command_ReProcess(playerid, "/adminmenu", 0);
                                }
                                new str[64];
                                format(str, sizeof str, "/setthirsty %d %d", userId, val);
                                Command_ReProcess(playerid, str, 0);
                            }
                            Dialog_ShowCallback(playerid, using inline InputThirsty, DIALOG_STYLE_INPUT,
                                "{FFFFFF}ปรับค่าน้ำ",
                                "{FFFFFF}กรอก: {FFFF00}[ไอดี] [ค่าความหิวน้ำ]\n{AAAAAA}ตัวอย่าง: 5 100",
                                "{FFFFFF}ยืนยัน", "{FFFFFF}กลับ");
                        }
                        case 3: { // ปรับจำนวนเงิน (setmoney)
                            inline InputSetMoney(res3, list3, string:in3[]) {
                                #pragma unused list3
                                if (!res3) @return Command_ReProcess(playerid, "/adminmenu", 0);

                                new userId, money;
                                if (sscanf(in3, "dd", userId, money)) {
                                    SendErrorMessage(playerid, "{FFFFFF}รูปแบบไม่ถูกต้อง เช่น: 5 50000");
                                    @return Command_ReProcess(playerid, "/adminmenu", 0);
                                }
                                new str[64];
                                format(str, sizeof str, "/setmoney %d %d", userId, money);
                                Command_ReProcess(playerid, str, 0);
                            }
                            Dialog_ShowCallback(playerid, using inline InputSetMoney, DIALOG_STYLE_INPUT,
                                "{FFFFFF}ปรับจำนวนเงิน",
                                "{FFFFFF}กรอก: {FFFF00}[ไอดี] [จำนวนเงิน]\n{AAAAAA}ตัวอย่าง: 5 50000",
                                "{FFFFFF}ยืนยัน", "{FFFFFF}กลับ");
                        }
                        case 4: { // เพิ่มจำนวนเงิน (givemoney)
                            inline InputGiveMoney(res3, list3, string:in3[]) {
                                #pragma unused list3
                                if (!res3) @return Command_ReProcess(playerid, "/adminmenu", 0);

                                new userId, money;
                                if (sscanf(in3, "dd", userId, money)) {
                                    SendErrorMessage(playerid, "{FFFFFF}รูปแบบไม่ถูกต้อง เช่น: 5 10000");
                                    @return Command_ReProcess(playerid, "/adminmenu", 0);
                                }
                                new str[64];
                                format(str, sizeof str, "/givemoney %d %d", userId, money);
                                Command_ReProcess(playerid, str, 0);
                            }
                            Dialog_ShowCallback(playerid, using inline InputGiveMoney, DIALOG_STYLE_INPUT,
                                "{FFFFFF}เพิ่มจำนวนเงิน",
                                "{FFFFFF}กรอก: {FFFF00}[ไอดี] [จำนวนเงิน]\n{AAAAAA}ตัวอย่าง: 5 10000",
                                "{FFFFFF}ยืนยัน", "{FFFFFF}กลับ");
                        }
                        case 5: { // ชุบชีวิต (arevive)
                            inline InputRevive(res3, list3, string:in3[]) {
                                #pragma unused list3
                                if (!res3) @return Command_ReProcess(playerid, "/adminmenu", 0);

                                new userId;
                                if (sscanf(in3, "d", userId)) {
                                    SendErrorMessage(playerid, "{FFFFFF}กรอกไอดีผู้เล่นให้ถูกต้อง");
                                    @return Command_ReProcess(playerid, "/adminmenu", 0);
                                }
                                new str[32];
                                format(str, sizeof str, "/arevive %d", userId);
                                Command_ReProcess(playerid, str, 0);
                            }
                            Dialog_ShowCallback(playerid, using inline InputRevive, DIALOG_STYLE_INPUT,
                                "{FFFFFF}ชุบชีวิตผู้เล่น",
                                "{FFFFFF}กรอก: {FFFF00}[ไอดี]\n{AAAAAA}ตัวอย่าง: 5",
                                "{FFFFFF}ยืนยัน", "{FFFFFF}กลับ");
                        }
                        case 6: { // ให้ยศแอดมิน
                            inline InputGiveMoney(res3, list3, string:in3[]) {
                                #pragma unused list3
                                if (!res3) @return Command_ReProcess(playerid, "/adminmenu", 0);

                                new userId, money;
                                if (sscanf(in3, "dd", userId, money)) {
                                    SendErrorMessage(playerid, "{FFFFFF}รูปแบบไม่ถูกต้อง เช่น: 5 10");
                                    @return Command_ReProcess(playerid, "/adminmenu", 0);
                                }
                                new str[64];
                                format(str, sizeof str, "/setadmin %d %d", userId, money);
                                Command_ReProcess(playerid, str, 0);
                            }
                            Dialog_ShowCallback(playerid, using inline InputGiveMoney, DIALOG_STYLE_INPUT,
                                "{FFFFFF}ให้ยศแอดมิน",
                                "{FFFFFF}กรอก: {FFFF00}[ไอดี] [ระดับยศ แนะนำ 6 ขึ้นไป]\n{AAAAAA}ตัวอย่าง: 5 10",
                                "{FFFFFF}ยืนยัน", "{FFFFFF}กลับ");
                        }
                        case 7: { // เสกสกินเข้ากระเป๋า
                            Command_ReProcess(playerid, "/skinsinfo", 0);
                        }
                        case 8: { // เสกไอเทมเข้าประเป๋า
                            Command_ReProcess(playerid, "/itemsinfo", 0);
                        }
                        case 9: {
                            inline InputGiveCar(res3, list3, string:in3[]) {
                                #pragma unused list3
                                if (!res3) @return Command_ReProcess(playerid, "/adminmenu", 0);

                                new userId, model, c1, c2;
                                if (sscanf(in3, "uddd", userId, model, c1, c2)) {
                                    SendErrorMessage(playerid, "{FFFFFF}รูปแบบไม่ถูกต้อง เช่น: 0 522 2 2");
                                    @return Command_ReProcess(playerid, "/adminmenu", 0);
                                }
                                new str[64];
                                format(str, sizeof str, "/givecar %d %d %d %d", userId, model, c1, c2);
                                Command_ReProcess(playerid, str, 0);
                            }
                            Dialog_ShowCallback(playerid, using inline InputGiveCar, DIALOG_STYLE_INPUT,
                                "{FFFFFF}เสกรถเข้าตัว",
                                "{FFFFFF}กรอก: {FFFF00}[ไอดี] [ไอดีรถ] [สี1] [สี2]\n{AAAAAA}ตัวอย่าง: 0 522 2 2",
                                "{FFFFFF}ยืนยัน", "{FFFFFF}กลับ");
                        }
                        case 10: {
                            SetTimer("AutoDespawn_Execute", 100, false);
                        }
                        case 11: {
                            for (new i = 0; i < MAX_DROP_ITEMS; i++) {
                                if (IsValidDynamicPickup(dropData[i][dObjectID]))
                                    DestroyDynamicPickup(dropData[i][dObjectID]);

                                if (IsValidDynamic3DTextLabel(dropData[i][d3DText]))
                                    DestroyDynamic3DTextLabel(dropData[i][d3DText]);

                                dropData[i][dExists] = false;
                            }
                            mysql_tquery(get_handle(), "TRUNCATE TABLE " DROP_ITEMS_TABLE "");
                            SendClientMessageToAll(COLOR_RED, "[!] {FFFFFF}ไอเทมที่ตกพื้นทั้งหมดถูกลบเรียบร้อยแล้ว");
                        }
                    }
                }
                Dialog_ShowCallback(playerid, using inline GeneralAdmin, DIALOG_STYLE_LIST,
                    "{FFFFFF}Admin Menu -> ทั่วไป",
                    "{FFFFFF}ปรับเลือด\n\
                    {FFFFFF}ปรับค่าอาหาร\n\
                    {FFFFFF}ปรับค่าน้ำ\n\
                    {FFFFFF}ปรับจำนวนเงิน\n\
                    {FFFFFF}เพิ่มจำนวนเงิน\n\
                    {FFFFFF}ชุบชีวิตผู้เล่น\n\
                    {FFFFFF}ให้ยศแอดมิน\n\
                    {FFFFFF}เสกสกินเข้ากระเป๋า\n\
                    {FFFFFF}เสกไอเทมเข้าประเป๋า\n\
                    {FFFFFF}เสกรถเข้าตัว\n\
                    {FFFFFF}รีรถส่วนตัวทั้งเซิร์ฟ\n\
                    {FFFFFF}รีไอเทมที่ดรอปทั้งเซิร์ฟ",
                    "{FFFFFF}เลือก", "{FFFFFF}กลับ");
            }
            case 1: { // หมวดหมู่แก๊ง (ปล่อยว่าง)
                inline GeneralAdmin(res2, list2, string:in2[]) {
                    #pragma unused in2
                    if (!res2) @return Command_ReProcess(playerid, "/adminmenu", 0);

                    switch (list2) {
                        case 0: { // จัดการแก๊ง
                            Command_ReProcess(playerid, "/agangpanel", 0);
                        }
                        case 1: { // ตั้งเข้าร่วมกลุ่ม
                            inline InPutSetGang(res3, list3, string:in3[]) {
                                #pragma unused list3
                                if (!res3) @return Command_ReProcess(playerid, "/adminmenu", 0);

                                new userId, gangIndex, rank;
                                if (sscanf(in3, "udd", userId, gangIndex, rank)) {
                                    SendErrorMessage(playerid, "{FFFFFF}รูปแบบไม่ถูกต้อง เช่น: 5 1 5");
                                    @return Command_ReProcess(playerid, "/adminmenu", 0);
                                }
                                new str[64];
                                format(str, sizeof str, "/setgang %d %d %d", userId, gangIndex, rank);
                                Command_ReProcess(playerid, str, 0);
                            }
                            Dialog_ShowCallback(playerid, using inline InPutSetGang, DIALOG_STYLE_INPUT,
                                "{FFFFFF}ตั้งเข้าร่วมกลุ่ม",
                                "{FFFFFF}กรอก: {FFFF00}[ไอดี] [index ของกลุ่ม] [ยศ]\n{AAAAAA}ตัวอย่าง: 5 1 5",
                                "{FFFFFF}ยืนยัน", "{FFFFFF}กลับ");
                        }
                        case 2: { // นำออกจากแก๊ง
                            inline RemoveFromGang(res3, list3, string:in3[]) {
                                #pragma unused list3
                                if (!res3) @return Command_ReProcess(playerid, "/adminmenu", 0);

                                new userId;
                                if (sscanf(in3, "u", userId)) {
                                    SendErrorMessage(playerid, "{FFFFFF}รูปแบบไม่ถูกต้อง เช่น: 5");
                                    @return Command_ReProcess(playerid, "/adminmenu", 0);
                                }
                                new str[64];
                                format(str, sizeof str, "/removegang %d", userId);
                                Command_ReProcess(playerid, str, 0);
                            }
                            Dialog_ShowCallback(playerid, using inline RemoveFromGang, DIALOG_STYLE_INPUT,
                                "{FFFFFF}นำออกจากแก๊ง",
                                "{FFFFFF}กรอก: {FFFF00}[ไอดี]\n{AAAAAA}ตัวอย่าง: 5",
                                "{FFFFFF}ยืนยัน", "{FFFFFF}กลับ");
                        }
                        case 3: { // ตั้ง officer
                            inline Officer(res3, list3, string:in3[]) {
                                #pragma unused list3
                                if (!res3) @return Command_ReProcess(playerid, "/adminmenu", 0);

                                new userId;
                                if (sscanf(in3, "u", userId)) {
                                    SendErrorMessage(playerid, "{FFFFFF}รูปแบบไม่ถูกต้อง เช่น: 5");
                                    @return Command_ReProcess(playerid, "/adminmenu", 0);
                                }
                                new str[64];
                                format(str, sizeof str, "/setofficer %d", userId);
                                Command_ReProcess(playerid, str, 0);
                            }
                            Dialog_ShowCallback(playerid, using inline Officer, DIALOG_STYLE_INPUT,
                                "{FFFFFF}ตั้ง Officer",
                                "{FFFFFF}กรอก: {FFFF00}[ไอดี]\n{AAAAAA}ตัวอย่าง: 5",
                                "{FFFFFF}ยืนยัน", "{FFFFFF}กลับ");
                        }
                    }
                }
                Dialog_ShowCallback(playerid, using inline GeneralAdmin, DIALOG_STYLE_LIST,
                    "{FFFFFF}Admin Menu -> หมวดหมู่แก๊ง",
                    "{FFFFFF}จัดการแก๊ง\n\
                    {FFFFFF}ตั้งเข้าร่วมกลุ่ม\n\
                    {FFFFFF}นำออกจากแก๊ง\n\
                    {FFFFFF}ตั้ง Officer",
                    "{FFFFFF}เลือก", "{FFFFFF}กลับ");
            }
            case 2: { // หมวดหมู่ GPS (ปล่อยว่าง)
                Command_ReProcess(playerid, "/agps", 0);
            }
            case 3: { // หมวดหมู่ Entrance (ปล่อยว่าง)
                Command_ReProcess(playerid, "/aentrance", 0);
            }
            case 4: { // หมวดหมู่ ATM (ปล่อยว่าง)
                Command_ReProcess(playerid, "/aatm", 0);
            }
            case 5: { // หมวดหมู่หน่วยงาน
                inline GeneralAdmin(res2, list2, string:in2[]) {
                    #pragma unused in2
                    if (!res2) @return Command_ReProcess(playerid, "/adminmenu", 0);

                    switch (list2) {
                        case 0: { // แต่งตั้ง
                            inline SetFaction(res3, list3, string:in3[]) {
                                #pragma unused list3
                                if (!res3) @return Command_ReProcess(playerid, "/adminmenu", 0);

                                new userId, gangIndex, rank;
                                if (sscanf(in3, "udd", userId, gangIndex, rank)) {
                                    SendErrorMessage(playerid, "{FFFFFF}รูปแบบไม่ถูกต้อง เช่น: 5 1 5");
                                    @return Command_ReProcess(playerid, "/adminmenu", 0);
                                }
                                new str[64];
                                format(str, sizeof str, "/hire %d %d %d", userId, gangIndex, rank);
                                Command_ReProcess(playerid, str, 0);
                            }
                            Dialog_ShowCallback(playerid, using inline SetFaction, DIALOG_STYLE_INPUT,
                                "{FFFFFF}แต่งตั้ง",
                                "{FFFFFF}กรอก: {FFFF00}[ไอดี] [ID ของกลุ่ม] [ยศ]\n\
                                {AAAAAA}ตัวอย่าง: 5 1 5\n\
                                {FFFFFF}ID: 0 (ตำรวจ)\n\
                                {FFFFFF}ID: 1 (ช่าง)\n\
                                {FFFFFF}ID: 2 (หมอ)",
                                "{FFFFFF}ยืนยัน", "{FFFFFF}กลับ");
                        }
                        case 1: { // ปลดออก
                            inline RemoveFromFaction(res3, list3, string:in3[]) {
                                #pragma unused list3
                                if (!res3) @return Command_ReProcess(playerid, "/adminmenu", 0);

                                new userId;
                                if (sscanf(in3, "u", userId)) {
                                    SendErrorMessage(playerid, "{FFFFFF}รูปแบบไม่ถูกต้อง เช่น: 5");
                                    @return Command_ReProcess(playerid, "/adminmenu", 0);
                                }
                                new str[64];
                                format(str, sizeof str, "/fire %d", userId);
                                Command_ReProcess(playerid, str, 0);
                            }
                            Dialog_ShowCallback(playerid, using inline RemoveFromFaction, DIALOG_STYLE_INPUT,
                                "{FFFFFF}ปลดออก",
                                "{FFFFFF}กรอก: {FFFF00}[ไอดี]\n{AAAAAA}ตัวอย่าง: 5",
                                "{FFFFFF}ยืนยัน", "{FFFFFF}กลับ");
                        }
                    }
                }
                Dialog_ShowCallback(playerid, using inline GeneralAdmin, DIALOG_STYLE_LIST,
                    "{FFFFFF}Admin Menu -> หมวดหมู่หน่วยงาน",
                    "{FFFFFF}แต่งตั้ง\n\
                    {FFFFFF}ปลดออก",
                    "{FFFFFF}เลือก", "{FFFFFF}กลับ");
            }
            case 6: { // หมวดหมู่ Garage/Pickcar/Pawncar
                Command_ReProcess(playerid, "/garagepanel", 0);
            }
            case 7: { // หมวดหมู่ Car Shop
                Command_ReProcess(playerid, "/adealership", 0);
            }
            case 8: { // หมวดหมู่ Pump
                Command_ReProcess(playerid, "/apump", 0);
            }
        }
    }
    Dialog_ShowCallback(playerid, using inline AdminMenu, DIALOG_STYLE_LIST,
        "{FFFFFF}Admin Menu",
        "{FFFFFF}หมวดหมู่ทั่วไป\n\
        {FFFFFF}หมวดหมู่แก๊ง\n\
        {FFFFFF}หมวดหมู่ GPS\n\
        {FFFFFF}หมวดหมู่ Entrance\n\
        {FFFFFF}หมวดหมู่ ATM\n\
        {FFFFFF}หมวดหมู่หน่วยงาน\n\
        {FFFFFF}หมวดหมู่ Garage/Pickcar/Pawncar\n\
        {FFFFFF}หมวดหมู่ Car Shop\n\
        {FFFFFF}หมวดหมู่ Pump",
        "{FFFFFF}เลือก", "{FFFFFF}ปิด");
    return 1;
}

#if defined DISABLE_ANTICHEAT
    hook OnGameModeInit() {
        for (new i = 0; i < 53; i++)
            EnableAntiCheat(i, 0);
        return 1;
    }
#else
    hook OnPlayerConnect(playerid) {
        if (IsPlayerAdminEx(playerid)) {
            for (new i = 0; i < 53; i++)
                EnableAntiCheatForPlayer(playerid, i, 0);
        }
        return 1;
    }
#endif

hook OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ) {
    if (IsPlayerAdminEx(playerid)) {
        SetPlayerPosFindZ(playerid, fX, fY, fZ);
    }
    return 1;
}
