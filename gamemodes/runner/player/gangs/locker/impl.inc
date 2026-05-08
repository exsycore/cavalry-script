#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid) {
    SetPVarInt(playerid, "usedGangSkin", 0);
    return 1;
}

public OpenGangLocker(playerid, gangid) {
    if (playerData[playerid][pGang] != Player.Gang[gangid][@id])
        return 1;
    
    inline inLineMenu(res, list, string:input[]) {
        #pragma unused input
        if (!res) @return 1;

        switch (list) {
            case 0: {
                new skinList[256], skinCount;
                for (new s = 0; s < 3; s++) {
                    if (Player.Gang[gangid][@gangskin][s] != INVALID_GANG_SKIN) {
                        new line[64];
                        format(line, sizeof(line), "{FFFFFF}สกิน %d (ID: %d)\n", s + 1, Player.Gang[gangid][@gangskin][s]);
                        strcat(skinList, line, sizeof(skinList));
                        skinCount++;
                    }
                }

                if (!skinCount) {
                    SendErrorMessage(playerid, "{FFFFFF}กลุ่มนี้ยังไม่มีสกินที่กำหนดไว้");
                    @return 1;
                }

                inline inLineGangSkinList(res2, list2, string:input2[]) {
                    #pragma unused input2
                    if (!res2) @return OpenGangLocker(playerid, gangid);
                    if (list2 < 0 || list2 >= skinCount) @return 1;

                    new slotFound, skinid = INVALID_GANG_SKIN;
                    for (new s = 0; s < 3; s++) {
                        if (Player.Gang[gangid][@gangskin][s] != INVALID_GANG_SKIN) {
                            if (slotFound == list2) { skinid = Player.Gang[gangid][@gangskin][s]; break; }
                            slotFound++;
                        }
                    }

                    if (skinid == INVALID_GANG_SKIN) @return 1;

                    if (GetPVarInt(playerid, "usedGangSkin") == 1) {
                        SendErrorMessage(playerid, "{FFFFFF}คุณต้องถอดสกินแก๊งออกก่อนจึงจะสามารถใช้งานสกินใหม่ได้");
                        @return 1;
                    }
                    
                    SetPlayerSkin(playerid, skinid);
                    SetPVarInt(playerid, "usedGangSkin", 1);

                    SendCongratMessage(playerid, "{FFFFFF}เปลี่ยนสกินเป็น ID {%06x}%d {FFFFFF}เรียบร้อยแล้ว", Player.Gang[gangid][@gangcolor] >>> 8, skinid);
                    SendWarningMessage(playerid, "{FFFFFF}สกินจะอยู่กับคุณตลอดที่อยู่ในเกมเมื่อคุณออกจากเกมสกินเหล่านั้นจะหายไป");
                    SendWarningMessage(playerid, "{FFFFFF}แต่ไม่ต้องห่วงคุณสามารถกลับไปที่ Locker เพื่อไปใช้งานสกินได้อีกครั้ง");
                }
                Dialog_ShowCallback(playerid, using inline inLineGangSkinList, DIALOG_STYLE_LIST, "{FFFFFF}เลือกสกิน", skinList, "{FFFFFF}เลือก", "{FFFFFF}กลับ");
            }
            case 1: {
                new info[256];
                inline inLineMoney(res2, list2, string:in[]) {
                    #pragma unused in
                    if (!res2) @return OpenGangLocker(playerid, gangid);

                    switch (list2) {
                        case 0: {
                            format(info, sizeof(info), "{FFFFFF}จำนวนเงิน: {00FF00}%d%s",
                                Player.Gang[gangid][@money],
                                IsPlayerOfficerGang(playerid) ? "\n{FFFFFF}ฝากเงิน\n{FFFFFF}ถอนเงิน" : ""
                            );
                            @return Dialog_ShowCallback(playerid, using inline inLineMoney, DIALOG_STYLE_LIST, "{FFFFFF}เงินเขียวในแก๊ง", info, "{FFFFFF}เลือก", "{FFFFFF}กลับ");
                        }
                        case 1: {
                            if (!IsPlayerOfficerGang(playerid)) @return SendErrorMessage(playerid, "{FFFFFF}ต้องมีสิทธ์เข้าถึงโดยรองหัวหน้ากลุ่มขึ้นไป");

                            inline inLineDeposit(res3, list3, string:input3[]) {
                                #pragma unused list3
                                if (!res3) @return OpenGangLocker(playerid, gangid);

                                if (isnull(input3)) {
                                    SendErrorMessage(playerid, "{FFFFFF}กรุณากรอกจำนวนเงิน");
                                    @return OpenGangLocker(playerid, gangid);
                                }

                                new amount = strval(input3);

                                if (amount <= 0) {
                                    SendErrorMessage(playerid, "{FFFFFF}จำนวนเงินต้องมากกว่า 0");
                                    @return OpenGangLocker(playerid, gangid);
                                }
                                if (playerData[playerid][pMoney] < amount) {
                                    SendErrorMessage(playerid, "{FFFFFF}เงินของคุณไม่เพียงพอ");
                                    @return OpenGangLocker(playerid, gangid);
                                }

                                GivePlayerMoneyEx(playerid, -amount);
                                Player.Gang[gangid][@money] += amount;

                                GangSave(gangid);
                                SendCongratMessage(playerid, "{FFFFFF}ฝากเงินเขียว {00FF00}$%d {FFFFFF}เรียบร้อย (คงเหลือในแก๊ง: {00FF00}$%d{FFFFFF})", amount, Player.Gang[gangid][@money]);
                            }
                            Dialog_ShowCallback(playerid, using inline inLineDeposit, DIALOG_STYLE_INPUT, "{FFFFFF}ฝากเงินเข้าแก๊ง", "{FFFFFF}กรอกจำนวนที่ต้องการฝาก", "{FFFFFF}ฝาก", "{FFFFFF}กลับ");
                        }
                        case 2: {
                            if (!IsPlayerOfficerGang(playerid)) @return SendErrorMessage(playerid, "{FFFFFF}ต้องมีสิทธ์เข้าถึงโดยรองหัวหน้ากลุ่มขึ้นไป");
                            
                            inline inLineWithdraw(res3, list3, string:input3[]) {
                                #pragma unused list3
                                if (!res3) @return OpenGangLocker(playerid, gangid);

                                if (isnull(input3)) {
                                    SendErrorMessage(playerid, "{FFFFFF}กรุณากรอกจำนวนเงิน");
                                    @return OpenGangLocker(playerid, gangid);
                                }

                                new amount = strval(input3);

                                if (amount <= 0) {
                                    SendErrorMessage(playerid, "{FFFFFF}จำนวนเงินต้องมากกว่า 0");
                                    @return OpenGangLocker(playerid, gangid);
                                }
                                if (Player.Gang[gangid][@money] < amount) {
                                    SendErrorMessage(playerid, "{FFFFFF}เงินในแก๊งไม่เพียงพอ");
                                    @return OpenGangLocker(playerid, gangid);
                                }

                                GivePlayerMoneyEx(playerid, amount);
                                Player.Gang[gangid][@money] -= amount;

                                GangSave(gangid);
                                SendCongratMessage(playerid, "{FFFFFF}ถอนเงินเขียว {00FF00}$%d {FFFFFF}เรียบร้อย (คงเหลือในแก๊ง: {00FF00}$%d{FFFFFF})", amount, Player.Gang[gangid][@money]);
                            }
                            Dialog_ShowCallback(playerid, using inline inLineWithdraw, DIALOG_STYLE_INPUT, "{FFFFFF}ฝากเงินเข้าแก๊ง", "{FFFFFF}กรอกจำนวนที่ต้องการฝาก", "{FFFFFF}ฝาก", "{FFFFFF}กลับ");
                        }
                    }
                }
                format(info, sizeof(info), "{FFFFFF}จำนวนเงิน: {00FF00}%d%s", Player.Gang[gangid][@money], (IsPlayerOfficerGang(playerid)) ? "\n{FFFFFF}ฝากเงิน\n{FFFFFF}ถอนเงิน" : "");
                Dialog_ShowCallback(playerid, using inline inLineMoney, DIALOG_STYLE_LIST, "{FFFFFF}เงินเขียวในแก๊ง", info, "{FFFFFF}เลือก", "{FFFFFF}กลับ");
            }
            case 2: {
                new info[256];
                inline inLineMoney(res2, list2, string:in[]) {
                    #pragma unused in
                    if (!res2) @return OpenGangLocker(playerid, gangid);

                    switch (list2) {
                        case 0: {
                            format(info, sizeof(info), "{FFFFFF}จำนวนเงิน: {FF0000}%d%s",
                                Player.Gang[gangid][@redmoney],
                                IsPlayerOfficerGang(playerid) ? "\n{FFFFFF}ฝากเงิน\n{FFFFFF}ถอนเงิน" : ""
                            );
                            @return Dialog_ShowCallback(playerid, using inline inLineMoney, DIALOG_STYLE_LIST, "{FFFFFF}เงินแดงในแก๊ง", info, "{FFFFFF}เลือก", "{FFFFFF}กลับ");
                        }
                        case 1: {
                            if (!IsPlayerOfficerGang(playerid)) @return SendErrorMessage(playerid, "{FFFFFF}ต้องมีสิทธ์เข้าถึงโดยรองหัวหน้ากลุ่มขึ้นไป");

                            inline inLineDeposit(res3, list3, string:input3[]) {
                                #pragma unused list3
                                if (!res3) @return OpenGangLocker(playerid, gangid);

                                if (isnull(input3)) {
                                    SendErrorMessage(playerid, "{FFFFFF}กรุณากรอกจำนวนเงิน");
                                    @return OpenGangLocker(playerid, gangid);
                                }

                                new amount = strval(input3);

                                if (amount <= 0) {
                                    SendErrorMessage(playerid, "{FFFFFF}จำนวนเงินต้องมากกว่า 0");
                                    @return OpenGangLocker(playerid, gangid);
                                }
                                if (playerData[playerid][pRedMoney] < amount) {
                                    SendErrorMessage(playerid, "{FFFFFF}เงินของคุณไม่เพียงพอ");
                                    @return OpenGangLocker(playerid, gangid);
                                }

                                GivePlayerRedMoneyEx(playerid, -amount);
                                Player.Gang[gangid][@redmoney] += amount;

                                GangSave(gangid);
                                SendCongratMessage(playerid, "{FFFFFF}ฝากเงินแดง {00FF00}$%d {FFFFFF}เรียบร้อย (คงเหลือในแก๊ง: {00FF00}$%d{FFFFFF})", amount, Player.Gang[gangid][@redmoney]);
                            }
                            Dialog_ShowCallback(playerid, using inline inLineDeposit, DIALOG_STYLE_INPUT, "{FFFFFF}ฝากเงินเข้าแก๊ง", "{FFFFFF}กรอกจำนวนที่ต้องการฝาก", "{FFFFFF}ฝาก", "{FFFFFF}กลับ");
                        }
                        case 2: {
                            if (!IsPlayerOfficerGang(playerid)) @return SendErrorMessage(playerid, "{FFFFFF}ต้องมีสิทธ์เข้าถึงโดยรองหัวหน้ากลุ่มขึ้นไป");
                            
                            inline inLineWithdraw(res3, list3, string:input3[]) {
                                #pragma unused list3
                                if (!res3) @return OpenGangLocker(playerid, gangid);

                                if (isnull(input3)) {
                                    SendErrorMessage(playerid, "{FFFFFF}กรุณากรอกจำนวนเงิน");
                                    @return OpenGangLocker(playerid, gangid);
                                }

                                new amount = strval(input3);

                                if (amount <= 0) {
                                    SendErrorMessage(playerid, "{FFFFFF}จำนวนเงินต้องมากกว่า 0");
                                    @return OpenGangLocker(playerid, gangid);
                                }
                                if (Player.Gang[gangid][@redmoney] < amount) {
                                    SendErrorMessage(playerid, "{FFFFFF}เงินในแก๊งไม่เพียงพอ");
                                    @return OpenGangLocker(playerid, gangid);
                                }

                                GivePlayerRedMoneyEx(playerid, amount);
                                Player.Gang[gangid][@redmoney] -= amount;

                                GangSave(gangid);
                                SendCongratMessage(playerid, "{FFFFFF}ถอนเงินแดง {00FF00}$%d {FFFFFF}เรียบร้อย (คงเหลือในแก๊ง: {00FF00}$%d{FFFFFF})", amount, Player.Gang[gangid][@redmoney]);
                            }
                            Dialog_ShowCallback(playerid, using inline inLineWithdraw, DIALOG_STYLE_INPUT, "{FFFFFF}ฝากเงินเข้าแก๊ง", "{FFFFFF}กรอกจำนวนที่ต้องการฝาก", "{FFFFFF}ฝาก", "{FFFFFF}กลับ");
                        }
                    }
                }
                format(info, sizeof(info), "{FFFFFF}จำนวนเงิน: {FF0000}%d%s", Player.Gang[gangid][@redmoney], (IsPlayerOfficerGang(playerid)) ? "\n{FFFFFF}ฝากเงิน\n{FFFFFF}ถอนเงิน" : "");
                Dialog_ShowCallback(playerid, using inline inLineMoney, DIALOG_STYLE_LIST, "{FFFFFF}เงินแดงในแก๊ง", info, "{FFFFFF}เลือก", "{FFFFFF}กลับ");
            }
        }
    }
    Dialog_ShowCallback(playerid, using inline inLineMenu, DIALOG_STYLE_LIST, "{FFFFFF}Locker", "{FFFFFF}สกิน\n{00FF00}เงินเขียว\n{FF0000}เงินแดง", "{FFFFFF}ไปต่อ", "{FFFFFF}ยกเลิก");
    return 1;
}
