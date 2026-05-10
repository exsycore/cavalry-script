#if defined _inc_impl
    #undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
    mysql_tquery(get_handle(), "SELECT * FROM "ATM_TABLE"", "ATMLoad", "");
    return true;
}

hook OnPlayerConnect(playerid) {
    ATM_Page[playerid]           = ATM_PAGE_NONE;
    ATM_InputAmount[playerid]    = 0;
    ATM_TransferTarget[playerid] = INVALID_PLAYER_ID;
    ATM_CreateTD(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    ATM_Close(playerid);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if (newkeys & KEY_NO) {
        if (ATM_Page[playerid] != ATM_PAGE_NONE) return 1; // เปิดอยู่แล้ว

        new atmid = ATMNearest(playerid);
        if (atmid == -1) return 1;
        if (!GetPlayerLoggedIn(playerid)) return 1;

        inline ATMChoice(res, list, string:in[]) {
            #pragma unused in
            if (!res) @return 1;
            switch (list) {
                case 0: { // ฝาก/ถอน
                    ATM_Page[playerid] = ATM_PAGE_MAIN;
                    ATM_ShowMain(playerid);
                }
                case 1: { // โอนเงิน ? เลือกผู้รับก่อน
                    ATM_ShowTransferTargetDialog(playerid);
                }
            }
        }
        Dialog_ShowCallback(playerid, using inline ATMChoice, DIALOG_STYLE_LIST,
            "{FFFFFF}ATM — เลือกรายการ",
            "{FFFFFF}ฝาก / ถอนเงิน\n{FFFFFF}โอนเงิน",
            "{FFFFFF}เลือก", "{FFFFFF}ปิด");
    }
    return 1;
}

hook OnClickDynamicPlayerTD(playerid, PlayerText:playertextid) {
    if (ATM_Page[playerid] == ATM_PAGE_NONE) return 1;

    if (playertextid == atm_exit_btn[playerid]) {
        ATM_Close(playerid);
        return 0;
    }

    if (ATM_Page[playerid] == ATM_PAGE_MAIN) {
        if (playertextid == atm_withdraw_btn[playerid]) {
            ATM_ShowNumpad(playerid, ATM_MODE_DEPOSIT);
            return 0;
        }
        if (playertextid == atm_deposit_btn[playerid]) {
            ATM_ShowNumpad(playerid, ATM_MODE_WITHDRAW);
            return 0;
        }
        // Quick withdraw $100
        if (playertextid == atm_quick_withdraw_btn_0[playerid]) {
            ATM_InputAmount[playerid] = 100;
            ATM_Mode[playerid]        = ATM_MODE_WITHDRAW;
            ATM_Confirm(playerid);
            return 0;
        }
        // Quick withdraw $500
        if (playertextid == atm_quick_withdraw_btn_1[playerid]) {
            ATM_InputAmount[playerid] = 500;
            ATM_Mode[playerid]        = ATM_MODE_WITHDRAW;
            ATM_Confirm(playerid);
            return 0;
        }
        // Quick withdraw $1000
        if (playertextid == atm_quick_withdraw_btn_2[playerid]) {
            ATM_InputAmount[playerid] = 1000;
            ATM_Mode[playerid]        = ATM_MODE_WITHDRAW;
            ATM_Confirm(playerid);
            return 0;
        }
        // Deposit All
        if (playertextid == atm_quick_deposit_all_btn[playerid]) {
            ATM_InputAmount[playerid] = playerData[playerid][pMoney];
            ATM_Mode[playerid]        = ATM_MODE_DEPOSIT;
            ATM_Confirm(playerid);
            return 0;
        }
        return 0;
    }

    if (ATM_Page[playerid] == ATM_PAGE_NUMPAD) {
        if (playertextid == atm_num_7_btn[playerid]) { ATM_NumpadPress(playerid, 7); return 1; }
        if (playertextid == atm_num_8_btn[playerid]) { ATM_NumpadPress(playerid, 8); return 1; }
        if (playertextid == atm_num_9_btn[playerid]) { ATM_NumpadPress(playerid, 9); return 1; }
        if (playertextid == atm_num_4_btn[playerid]) { ATM_NumpadPress(playerid, 4); return 1; }
        if (playertextid == atm_num_5_btn[playerid]) { ATM_NumpadPress(playerid, 5); return 1; }
        if (playertextid == atm_num_6_btn[playerid]) { ATM_NumpadPress(playerid, 6); return 1; }
        if (playertextid == atm_num_1_btn[playerid]) { ATM_NumpadPress(playerid, 1); return 1; }
        if (playertextid == atm_num_2_btn[playerid]) { ATM_NumpadPress(playerid, 2); return 1; }
        if (playertextid == atm_num_3_btn[playerid]) { ATM_NumpadPress(playerid, 3); return 1; }
        if (playertextid == atm_num_0_btn[playerid]) { ATM_NumpadPress(playerid, 0); return 1; }
        if (playertextid == atm_num_clear_btn[playerid]) { ATM_NumpadClear(playerid); return 1; }
        if (playertextid == atm_confirm_btn[playerid]) {
            ATM_Confirm(playerid);
            return 0;
        }
        return 0;
    }
    return 0;
}

hook OnCancelDynTextDraw(playerid) {
    if (ATM_Page[playerid] != ATM_PAGE_NONE) {
        ATM_Close(playerid);
    }
    return 1;
}

stock ATM_CreateTD(playerid) {
    atm_main[playerid][0] = CreatePlayerTextDraw(playerid, 206.000000, 130.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_main[playerid][0], 4);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][0], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][0], 232.000000, 217.000000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][0], 1);
    PlayerTextDrawColor(playerid, atm_main[playerid][0], 1448499455);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][0], 0);

    atm_main[playerid][1] = CreatePlayerTextDraw(playerid, 208.000000, 134.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_main[playerid][1], 4);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][1], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][1], 227.500000, 45.500000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][1], 1);
    PlayerTextDrawColor(playerid, atm_main[playerid][1], -16843009);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][1], 0);

    atm_main[playerid][2] = CreatePlayerTextDraw(playerid, 208.000000, 178.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_main[playerid][2], 4);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][2], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][2], 116.500000, 137.500000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][2], 1);
    PlayerTextDrawColor(playerid, atm_main[playerid][2], -387389185);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][2], 0);

    atm_main[playerid][3] = CreatePlayerTextDraw(playerid, 322.000000, 178.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_main[playerid][3], 4);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][3], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][3], 113.500000, 137.500000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][3], 1);
    PlayerTextDrawColor(playerid, atm_main[playerid][3], -589505281);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][3], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][3], 0);

    atm_main[playerid][4] = CreatePlayerTextDraw(playerid, 218.000000, 145.000000, "ATM");
    PlayerTextDrawFont(playerid, atm_main[playerid][4], 2);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][4], 0.283333, 2.149998);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][4], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][4], 1);
    PlayerTextDrawColor(playerid, atm_main[playerid][4], 255);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][4], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][4], 0);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][4], 0);

    atm_main[playerid][5] = CreatePlayerTextDraw(playerid, 406.000000, 142.000000, "HUD:radar_cash");
    PlayerTextDrawFont(playerid, atm_main[playerid][5], 4);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][5], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][5], 24.000000, 28.500000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][5], 1);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][5], 1);
    PlayerTextDrawColor(playerid, atm_main[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][5], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][5], 0);

    atm_main[playerid][6] = CreatePlayerTextDraw(playerid, 221.000000, 198.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_main[playerid][6], 4);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][6], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][6], 86.500000, 0.500000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][6], 1);
    PlayerTextDrawColor(playerid, atm_main[playerid][6], -1431655681);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][6], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][6], 0);

    atm_main[playerid][7] = CreatePlayerTextDraw(playerid, 221.000000, 214.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_main[playerid][7], 4);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][7], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][7], 86.500000, 0.500000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][7], 1);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][7], 1);
    PlayerTextDrawColor(playerid, atm_main[playerid][7], -1431655681);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][7], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][7], 0);

    atm_main[playerid][8] = CreatePlayerTextDraw(playerid, 221.000000, 231.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_main[playerid][8], 4);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][8], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][8], 86.500000, 0.500000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][8], 1);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][8], 1);
    PlayerTextDrawColor(playerid, atm_main[playerid][8], -1431655681);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][8], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][8], 0);

    atm_main[playerid][9] = CreatePlayerTextDraw(playerid, 221.000000, 202.000000, "Cash");
    PlayerTextDrawFont(playerid, atm_main[playerid][9], 1);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][9], 0.174999, 0.800000);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][9], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][9], 0);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][9], 1);
    PlayerTextDrawColor(playerid, atm_main[playerid][9], 255);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][9], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][9], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][9], 0);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][9], 0);

    atm_main[playerid][10] = CreatePlayerTextDraw(playerid, 221.000000, 219.000000, "Balance");
    PlayerTextDrawFont(playerid, atm_main[playerid][10], 1);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][10], 0.174999, 0.800000);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][10], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][10], 0);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][10], 1);
    PlayerTextDrawColor(playerid, atm_main[playerid][10], 255);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][10], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][10], 0);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][10], 0);

    atm_cash_text[playerid] = CreatePlayerTextDraw(playerid, 306.000000, 202.000000, "$999999999");
    PlayerTextDrawFont(playerid, atm_cash_text[playerid], 1);
    PlayerTextDrawLetterSize(playerid, atm_cash_text[playerid], 0.174999, 0.800000);
    PlayerTextDrawTextSize(playerid, atm_cash_text[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, atm_cash_text[playerid], 0);
    PlayerTextDrawSetShadow(playerid, atm_cash_text[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_cash_text[playerid], 3);
    PlayerTextDrawColor(playerid, atm_cash_text[playerid], 255);
    PlayerTextDrawBackgroundColor(playerid, atm_cash_text[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_cash_text[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_cash_text[playerid], 0);
    PlayerTextDrawSetProportional(playerid, atm_cash_text[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_cash_text[playerid], 0);

    atm_balance_text[playerid] = CreatePlayerTextDraw(playerid, 306.000000, 219.000000, "$999999999");
    PlayerTextDrawFont(playerid, atm_balance_text[playerid], 1);
    PlayerTextDrawLetterSize(playerid, atm_balance_text[playerid], 0.174999, 0.800000);
    PlayerTextDrawTextSize(playerid, atm_balance_text[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, atm_balance_text[playerid], 0);
    PlayerTextDrawSetShadow(playerid, atm_balance_text[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_balance_text[playerid], 3);
    PlayerTextDrawColor(playerid, atm_balance_text[playerid], 255);
    PlayerTextDrawBackgroundColor(playerid, atm_balance_text[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_balance_text[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_balance_text[playerid], 0);
    PlayerTextDrawSetProportional(playerid, atm_balance_text[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_balance_text[playerid], 0);

    atm_withdraw_btn[playerid] = CreatePlayerTextDraw(playerid, 223.000000, 235.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_withdraw_btn[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_withdraw_btn[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_withdraw_btn[playerid], 39.500000, 19.500000);
    PlayerTextDrawSetOutline(playerid, atm_withdraw_btn[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_withdraw_btn[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_withdraw_btn[playerid], 1);
    PlayerTextDrawColor(playerid, atm_withdraw_btn[playerid], 1035547135);
    PlayerTextDrawBackgroundColor(playerid, atm_withdraw_btn[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_withdraw_btn[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_withdraw_btn[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_withdraw_btn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_withdraw_btn[playerid], 1);

    atm_deposit_btn[playerid] = CreatePlayerTextDraw(playerid, 263.000000, 235.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_deposit_btn[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_deposit_btn[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_deposit_btn[playerid], 39.500000, 19.500000);
    PlayerTextDrawSetOutline(playerid, atm_deposit_btn[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_deposit_btn[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_deposit_btn[playerid], 1);
    PlayerTextDrawColor(playerid, atm_deposit_btn[playerid], 1035547135);
    PlayerTextDrawBackgroundColor(playerid, atm_deposit_btn[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_deposit_btn[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_deposit_btn[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_deposit_btn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_deposit_btn[playerid], 1);

    atm_main[playerid][11] = CreatePlayerTextDraw(playerid, 233.000000, 240.000000, "Deposit");
    PlayerTextDrawFont(playerid, atm_main[playerid][11], 1);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][11], 0.158333, 1.000000);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][11], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][11], 0);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][11], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][11], 1);
    PlayerTextDrawColor(playerid, atm_main[playerid][11], -1);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][11], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][11], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][11], 0);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][11], 0);

    atm_main[playerid][12] = CreatePlayerTextDraw(playerid, 270.000000, 240.000000, "Withdraw");
    PlayerTextDrawFont(playerid, atm_main[playerid][12], 1);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][12], 0.158333, 1.000000);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][12], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][12], 0);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][12], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][12], 1);
    PlayerTextDrawColor(playerid, atm_main[playerid][12], -1);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][12], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][12], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][12], 0);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][12], 0);

    atm_main[playerid][13] = CreatePlayerTextDraw(playerid, 220.000000, 258.000000, "Quick actions");
    PlayerTextDrawFont(playerid, atm_main[playerid][13], 1);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][13], 0.166666, 1.200000);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][13], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][13], 0);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][13], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][13], 1);
    PlayerTextDrawColor(playerid, atm_main[playerid][13], 255);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][13], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][13], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][13], 0);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][13], 0);

    atm_quick_withdraw_btn_0[playerid] = CreatePlayerTextDraw(playerid, 223.000000, 271.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_quick_withdraw_btn_0[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_quick_withdraw_btn_0[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_quick_withdraw_btn_0[playerid], 39.500000, 19.500000);
    PlayerTextDrawSetOutline(playerid, atm_quick_withdraw_btn_0[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_quick_withdraw_btn_0[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_quick_withdraw_btn_0[playerid], 1);
    PlayerTextDrawColor(playerid, atm_quick_withdraw_btn_0[playerid], -1010579969);
    PlayerTextDrawBackgroundColor(playerid, atm_quick_withdraw_btn_0[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_quick_withdraw_btn_0[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_quick_withdraw_btn_0[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_quick_withdraw_btn_0[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_quick_withdraw_btn_0[playerid], 1);

    atm_main[playerid][14] = CreatePlayerTextDraw(playerid, 243.000000, 277.000000, "Withdraw $100");
    PlayerTextDrawFont(playerid, atm_main[playerid][14], 1);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][14], 0.133332, 0.850000);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][14], 422.500000, 56.500000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][14], 0);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][14], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][14], 2);
    PlayerTextDrawColor(playerid, atm_main[playerid][14], 1953724671);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][14], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][14], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][14], 0);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][14], 0);

    atm_quick_withdraw_btn_1[playerid] = CreatePlayerTextDraw(playerid, 263.000000, 271.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_quick_withdraw_btn_1[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_quick_withdraw_btn_1[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_quick_withdraw_btn_1[playerid], 39.500000, 19.500000);
    PlayerTextDrawSetOutline(playerid, atm_quick_withdraw_btn_1[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_quick_withdraw_btn_1[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_quick_withdraw_btn_1[playerid], 1);
    PlayerTextDrawColor(playerid, atm_quick_withdraw_btn_1[playerid], -1010579969);
    PlayerTextDrawBackgroundColor(playerid, atm_quick_withdraw_btn_1[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_quick_withdraw_btn_1[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_quick_withdraw_btn_1[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_quick_withdraw_btn_1[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_quick_withdraw_btn_1[playerid], 1);

    atm_main[playerid][15] = CreatePlayerTextDraw(playerid, 283.000000, 277.000000, "Withdraw $500");
    PlayerTextDrawFont(playerid, atm_main[playerid][15], 1);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][15], 0.133332, 0.850000);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][15], 422.500000, 56.500000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][15], 0);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][15], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][15], 2);
    PlayerTextDrawColor(playerid, atm_main[playerid][15], 1953724671);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][15], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][15], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][15], 0);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][15], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][15], 0);

    atm_quick_withdraw_btn_2[playerid] = CreatePlayerTextDraw(playerid, 223.000000, 291.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_quick_withdraw_btn_2[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_quick_withdraw_btn_2[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_quick_withdraw_btn_2[playerid], 39.500000, 19.500000);
    PlayerTextDrawSetOutline(playerid, atm_quick_withdraw_btn_2[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_quick_withdraw_btn_2[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_quick_withdraw_btn_2[playerid], 1);
    PlayerTextDrawColor(playerid, atm_quick_withdraw_btn_2[playerid], -1010579969);
    PlayerTextDrawBackgroundColor(playerid, atm_quick_withdraw_btn_2[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_quick_withdraw_btn_2[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_quick_withdraw_btn_2[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_quick_withdraw_btn_2[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_quick_withdraw_btn_2[playerid], 1);

    atm_main[playerid][16] = CreatePlayerTextDraw(playerid, 243.000000, 296.000000, "Withdraw $1000");
    PlayerTextDrawFont(playerid, atm_main[playerid][16], 1);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][16], 0.133332, 0.850000);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][16], 422.500000, 56.500000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][16], 0);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][16], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][16], 2);
    PlayerTextDrawColor(playerid, atm_main[playerid][16], 1953724671);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][16], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][16], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][16], 0);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][16], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][16], 0);

    atm_quick_deposit_all_btn[playerid] = CreatePlayerTextDraw(playerid, 263.000000, 291.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_quick_deposit_all_btn[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_quick_deposit_all_btn[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_quick_deposit_all_btn[playerid], 39.500000, 19.500000);
    PlayerTextDrawSetOutline(playerid, atm_quick_deposit_all_btn[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_quick_deposit_all_btn[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_quick_deposit_all_btn[playerid], 1);
    PlayerTextDrawColor(playerid, atm_quick_deposit_all_btn[playerid], -1010579969);
    PlayerTextDrawBackgroundColor(playerid, atm_quick_deposit_all_btn[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_quick_deposit_all_btn[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_quick_deposit_all_btn[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_quick_deposit_all_btn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_quick_deposit_all_btn[playerid], 1);

    atm_main[playerid][17] = CreatePlayerTextDraw(playerid, 283.000000, 296.000000, "Deposit All");
    PlayerTextDrawFont(playerid, atm_main[playerid][17], 1);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][17], 0.133332, 0.850000);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][17], 422.500000, 56.500000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][17], 0);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][17], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][17], 2);
    PlayerTextDrawColor(playerid, atm_main[playerid][17], 1953724671);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][17], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][17], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][17], 0);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][17], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][17], 0);

    atm_main[playerid][18] = CreatePlayerTextDraw(playerid, 208.000000, 315.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_main[playerid][18], 4);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][18], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][18], 227.500000, 29.000000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][18], 1);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][18], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][18], 1);
    PlayerTextDrawColor(playerid, atm_main[playerid][18], 1060914687);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][18], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][18], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][18], 1);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][18], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][18], 0);

    atm_exit_btn[playerid] = CreatePlayerTextDraw(playerid, 221.000000, 321.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_exit_btn[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_exit_btn[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_exit_btn[playerid], 39.500000, 19.500000);
    PlayerTextDrawSetOutline(playerid, atm_exit_btn[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_exit_btn[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_exit_btn[playerid], 1);
    PlayerTextDrawColor(playerid, atm_exit_btn[playerid], 1650551039);
    PlayerTextDrawBackgroundColor(playerid, atm_exit_btn[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_exit_btn[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_exit_btn[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_exit_btn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_exit_btn[playerid], 1);

    atm_main[playerid][19] = CreatePlayerTextDraw(playerid, 235.000000, 326.000000, "Exit");
    PlayerTextDrawFont(playerid, atm_main[playerid][19], 1);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][19], 0.174999, 0.949999);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][19], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][19], 0);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][19], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][19], 1);
    PlayerTextDrawColor(playerid, atm_main[playerid][19], -1);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][19], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][19], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][19], 0);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][19], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][19], 0);

    atm_num_7_btn[playerid] = CreatePlayerTextDraw(playerid, 338.000000, 194.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_num_7_btn[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_num_7_btn[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_num_7_btn[playerid], 26.000000, 27.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_7_btn[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_num_7_btn[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_7_btn[playerid], 1);
    PlayerTextDrawColor(playerid, atm_num_7_btn[playerid], -1010579969);
    PlayerTextDrawBackgroundColor(playerid, atm_num_7_btn[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_7_btn[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_7_btn[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_num_7_btn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_7_btn[playerid], 1);

    atm_num_8_btn[playerid] = CreatePlayerTextDraw(playerid, 365.000000, 194.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_num_8_btn[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_num_8_btn[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_num_8_btn[playerid], 26.000000, 27.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_8_btn[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_num_8_btn[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_8_btn[playerid], 1);
    PlayerTextDrawColor(playerid, atm_num_8_btn[playerid], -1010579969);
    PlayerTextDrawBackgroundColor(playerid, atm_num_8_btn[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_8_btn[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_8_btn[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_num_8_btn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_8_btn[playerid], 1);

    atm_num_9_btn[playerid] = CreatePlayerTextDraw(playerid, 392.000000, 194.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_num_9_btn[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_num_9_btn[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_num_9_btn[playerid], 26.000000, 27.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_9_btn[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_num_9_btn[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_9_btn[playerid], 1);
    PlayerTextDrawColor(playerid, atm_num_9_btn[playerid], -1010579969);
    PlayerTextDrawBackgroundColor(playerid, atm_num_9_btn[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_9_btn[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_9_btn[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_num_9_btn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_9_btn[playerid], 1);

    atm_num_4_btn[playerid] = CreatePlayerTextDraw(playerid, 338.000000, 223.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_num_4_btn[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_num_4_btn[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_num_4_btn[playerid], 26.000000, 27.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_4_btn[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_num_4_btn[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_4_btn[playerid], 1);
    PlayerTextDrawColor(playerid, atm_num_4_btn[playerid], -1010579969);
    PlayerTextDrawBackgroundColor(playerid, atm_num_4_btn[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_4_btn[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_4_btn[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_num_4_btn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_4_btn[playerid], 1);

    atm_num_5_btn[playerid] = CreatePlayerTextDraw(playerid, 365.000000, 223.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_num_5_btn[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_num_5_btn[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_num_5_btn[playerid], 26.000000, 27.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_5_btn[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_num_5_btn[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_5_btn[playerid], 1);
    PlayerTextDrawColor(playerid, atm_num_5_btn[playerid], -1010579969);
    PlayerTextDrawBackgroundColor(playerid, atm_num_5_btn[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_5_btn[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_5_btn[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_num_5_btn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_5_btn[playerid], 1);

    atm_num_6_btn[playerid] = CreatePlayerTextDraw(playerid, 392.000000, 223.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_num_6_btn[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_num_6_btn[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_num_6_btn[playerid], 26.000000, 27.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_6_btn[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_num_6_btn[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_6_btn[playerid], 1);
    PlayerTextDrawColor(playerid, atm_num_6_btn[playerid], -1010579969);
    PlayerTextDrawBackgroundColor(playerid, atm_num_6_btn[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_6_btn[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_6_btn[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_num_6_btn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_6_btn[playerid], 1);

    atm_num_1_btn[playerid] = CreatePlayerTextDraw(playerid, 338.000000, 252.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_num_1_btn[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_num_1_btn[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_num_1_btn[playerid], 26.000000, 27.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_1_btn[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_num_1_btn[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_1_btn[playerid], 1);
    PlayerTextDrawColor(playerid, atm_num_1_btn[playerid], -1010579969);
    PlayerTextDrawBackgroundColor(playerid, atm_num_1_btn[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_1_btn[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_1_btn[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_num_1_btn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_1_btn[playerid], 1);

    atm_num_2_btn[playerid] = CreatePlayerTextDraw(playerid, 365.000000, 252.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_num_2_btn[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_num_2_btn[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_num_2_btn[playerid], 26.000000, 27.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_2_btn[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_num_2_btn[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_2_btn[playerid], 1);
    PlayerTextDrawColor(playerid, atm_num_2_btn[playerid], -1010579969);
    PlayerTextDrawBackgroundColor(playerid, atm_num_2_btn[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_2_btn[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_2_btn[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_num_2_btn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_2_btn[playerid], 1);

    atm_num_3_btn[playerid] = CreatePlayerTextDraw(playerid, 392.000000, 252.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_num_3_btn[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_num_3_btn[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_num_3_btn[playerid], 26.000000, 27.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_3_btn[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_num_3_btn[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_3_btn[playerid], 1);
    PlayerTextDrawColor(playerid, atm_num_3_btn[playerid], -1010579969);
    PlayerTextDrawBackgroundColor(playerid, atm_num_3_btn[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_3_btn[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_3_btn[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_num_3_btn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_3_btn[playerid], 1);

    atm_num_0_btn[playerid] = CreatePlayerTextDraw(playerid, 365.000000, 281.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_num_0_btn[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_num_0_btn[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_num_0_btn[playerid], 26.000000, 27.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_0_btn[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_num_0_btn[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_0_btn[playerid], 1);
    PlayerTextDrawColor(playerid, atm_num_0_btn[playerid], -1010579969);
    PlayerTextDrawBackgroundColor(playerid, atm_num_0_btn[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_0_btn[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_0_btn[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_num_0_btn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_0_btn[playerid], 1);

    atm_num_clear_btn[playerid] = CreatePlayerTextDraw(playerid, 392.000000, 281.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_num_clear_btn[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_num_clear_btn[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_num_clear_btn[playerid], 26.000000, 27.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_clear_btn[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_num_clear_btn[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_clear_btn[playerid], 1);
    PlayerTextDrawColor(playerid, atm_num_clear_btn[playerid], -1010579969);
    PlayerTextDrawBackgroundColor(playerid, atm_num_clear_btn[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_clear_btn[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_clear_btn[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_num_clear_btn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_clear_btn[playerid], 1);

    atm_num_0[playerid] = CreatePlayerTextDraw(playerid, 351.000000, 204.000000, "7");
    PlayerTextDrawFont(playerid, atm_num_0[playerid], 1);
    PlayerTextDrawLetterSize(playerid, atm_num_0[playerid], 0.220833, 1.149999);
    PlayerTextDrawTextSize(playerid, atm_num_0[playerid], 422.500000, 56.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_0[playerid], 0);
    PlayerTextDrawSetShadow(playerid, atm_num_0[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_0[playerid], 2);
    PlayerTextDrawColor(playerid, atm_num_0[playerid], 1953724671);
    PlayerTextDrawBackgroundColor(playerid, atm_num_0[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_0[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_0[playerid], 0);
    PlayerTextDrawSetProportional(playerid, atm_num_0[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_0[playerid], 0);

    atm_num_1[playerid] = CreatePlayerTextDraw(playerid, 378.000000, 204.000000, "8");
    PlayerTextDrawFont(playerid, atm_num_1[playerid], 1);
    PlayerTextDrawLetterSize(playerid, atm_num_1[playerid], 0.220833, 1.149999);
    PlayerTextDrawTextSize(playerid, atm_num_1[playerid], 422.500000, 56.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_1[playerid], 0);
    PlayerTextDrawSetShadow(playerid, atm_num_1[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_1[playerid], 2);
    PlayerTextDrawColor(playerid, atm_num_1[playerid], 1953724671);
    PlayerTextDrawBackgroundColor(playerid, atm_num_1[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_1[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_1[playerid], 0);
    PlayerTextDrawSetProportional(playerid, atm_num_1[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_1[playerid], 0);

    atm_num_2[playerid] = CreatePlayerTextDraw(playerid, 405.000000, 204.000000, "9");
    PlayerTextDrawFont(playerid, atm_num_2[playerid], 1);
    PlayerTextDrawLetterSize(playerid, atm_num_2[playerid], 0.220833, 1.149999);
    PlayerTextDrawTextSize(playerid, atm_num_2[playerid], 422.500000, 56.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_2[playerid], 0);
    PlayerTextDrawSetShadow(playerid, atm_num_2[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_2[playerid], 2);
    PlayerTextDrawColor(playerid, atm_num_2[playerid], 1953724671);
    PlayerTextDrawBackgroundColor(playerid, atm_num_2[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_2[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_2[playerid], 0);
    PlayerTextDrawSetProportional(playerid, atm_num_2[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_2[playerid], 0);

    atm_num_3[playerid] = CreatePlayerTextDraw(playerid, 351.000000, 232.000000, "4");
    PlayerTextDrawFont(playerid, atm_num_3[playerid], 1);
    PlayerTextDrawLetterSize(playerid, atm_num_3[playerid], 0.220833, 1.149999);
    PlayerTextDrawTextSize(playerid, atm_num_3[playerid], 422.500000, 56.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_3[playerid], 0);
    PlayerTextDrawSetShadow(playerid, atm_num_3[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_3[playerid], 2);
    PlayerTextDrawColor(playerid, atm_num_3[playerid], 1953724671);
    PlayerTextDrawBackgroundColor(playerid, atm_num_3[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_3[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_3[playerid], 0);
    PlayerTextDrawSetProportional(playerid, atm_num_3[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_3[playerid], 0);

    atm_num_4[playerid] = CreatePlayerTextDraw(playerid, 378.000000, 232.000000, "5");
    PlayerTextDrawFont(playerid, atm_num_4[playerid], 1);
    PlayerTextDrawLetterSize(playerid, atm_num_4[playerid], 0.220833, 1.149999);
    PlayerTextDrawTextSize(playerid, atm_num_4[playerid], 422.500000, 56.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_4[playerid], 0);
    PlayerTextDrawSetShadow(playerid, atm_num_4[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_4[playerid], 2);
    PlayerTextDrawColor(playerid, atm_num_4[playerid], 1953724671);
    PlayerTextDrawBackgroundColor(playerid, atm_num_4[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_4[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_4[playerid], 0);
    PlayerTextDrawSetProportional(playerid, atm_num_4[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_4[playerid], 0);

    atm_num_5[playerid] = CreatePlayerTextDraw(playerid, 405.000000, 232.000000, "6");
    PlayerTextDrawFont(playerid, atm_num_5[playerid], 1);
    PlayerTextDrawLetterSize(playerid, atm_num_5[playerid], 0.220833, 1.149999);
    PlayerTextDrawTextSize(playerid, atm_num_5[playerid], 422.500000, 56.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_5[playerid], 0);
    PlayerTextDrawSetShadow(playerid, atm_num_5[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_5[playerid], 2);
    PlayerTextDrawColor(playerid, atm_num_5[playerid], 1953724671);
    PlayerTextDrawBackgroundColor(playerid, atm_num_5[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_5[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_5[playerid], 0);
    PlayerTextDrawSetProportional(playerid, atm_num_5[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_5[playerid], 0);

    atm_num_6[playerid] = CreatePlayerTextDraw(playerid, 351.000000, 261.000000, "1");
    PlayerTextDrawFont(playerid, atm_num_6[playerid], 1);
    PlayerTextDrawLetterSize(playerid, atm_num_6[playerid], 0.220833, 1.149999);
    PlayerTextDrawTextSize(playerid, atm_num_6[playerid], 422.500000, 56.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_6[playerid], 0);
    PlayerTextDrawSetShadow(playerid, atm_num_6[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_6[playerid], 2);
    PlayerTextDrawColor(playerid, atm_num_6[playerid], 1953724671);
    PlayerTextDrawBackgroundColor(playerid, atm_num_6[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_6[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_6[playerid], 0);
    PlayerTextDrawSetProportional(playerid, atm_num_6[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_6[playerid], 0);

    atm_num_7[playerid] = CreatePlayerTextDraw(playerid, 378.000000, 261.000000, "2");
    PlayerTextDrawFont(playerid, atm_num_7[playerid], 1);
    PlayerTextDrawLetterSize(playerid, atm_num_7[playerid], 0.220833, 1.149999);
    PlayerTextDrawTextSize(playerid, atm_num_7[playerid], 422.500000, 56.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_7[playerid], 0);
    PlayerTextDrawSetShadow(playerid, atm_num_7[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_7[playerid], 2);
    PlayerTextDrawColor(playerid, atm_num_7[playerid], 1953724671);
    PlayerTextDrawBackgroundColor(playerid, atm_num_7[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_7[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_7[playerid], 0);
    PlayerTextDrawSetProportional(playerid, atm_num_7[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_7[playerid], 0);

    atm_num_8[playerid] = CreatePlayerTextDraw(playerid, 405.000000, 261.000000, "3");
    PlayerTextDrawFont(playerid, atm_num_8[playerid], 1);
    PlayerTextDrawLetterSize(playerid, atm_num_8[playerid], 0.220833, 1.149999);
    PlayerTextDrawTextSize(playerid, atm_num_8[playerid], 422.500000, 56.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_8[playerid], 0);
    PlayerTextDrawSetShadow(playerid, atm_num_8[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_8[playerid], 2);
    PlayerTextDrawColor(playerid, atm_num_8[playerid], 1953724671);
    PlayerTextDrawBackgroundColor(playerid, atm_num_8[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_8[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_8[playerid], 0);
    PlayerTextDrawSetProportional(playerid, atm_num_8[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_8[playerid], 0);

    atm_num_10[playerid] = CreatePlayerTextDraw(playerid, 405.000000, 291.000000, "C");
    PlayerTextDrawFont(playerid, atm_num_10[playerid], 1);
    PlayerTextDrawLetterSize(playerid, atm_num_10[playerid], 0.220833, 1.149999);
    PlayerTextDrawTextSize(playerid, atm_num_10[playerid], 422.500000, 56.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_10[playerid], 0);
    PlayerTextDrawSetShadow(playerid, atm_num_10[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_10[playerid], 2);
    PlayerTextDrawColor(playerid, atm_num_10[playerid], 1953724671);
    PlayerTextDrawBackgroundColor(playerid, atm_num_10[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_10[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_10[playerid], 0);
    PlayerTextDrawSetProportional(playerid, atm_num_10[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_10[playerid], 0);

    atm_num_9[playerid] = CreatePlayerTextDraw(playerid, 378.000000, 291.000000, "0");
    PlayerTextDrawFont(playerid, atm_num_9[playerid], 1);
    PlayerTextDrawLetterSize(playerid, atm_num_9[playerid], 0.220833, 1.149999);
    PlayerTextDrawTextSize(playerid, atm_num_9[playerid], 422.500000, 56.500000);
    PlayerTextDrawSetOutline(playerid, atm_num_9[playerid], 0);
    PlayerTextDrawSetShadow(playerid, atm_num_9[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_num_9[playerid], 2);
    PlayerTextDrawColor(playerid, atm_num_9[playerid], 1953724671);
    PlayerTextDrawBackgroundColor(playerid, atm_num_9[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_num_9[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_num_9[playerid], 0);
    PlayerTextDrawSetProportional(playerid, atm_num_9[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_num_9[playerid], 0);

    atm_page_input_0[playerid] = CreatePlayerTextDraw(playerid, 208.000000, 178.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_page_input_0[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_page_input_0[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_page_input_0[playerid], 116.500000, 137.000000);
    PlayerTextDrawSetOutline(playerid, atm_page_input_0[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_page_input_0[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_page_input_0[playerid], 1);
    PlayerTextDrawColor(playerid, atm_page_input_0[playerid], -387389185);
    PlayerTextDrawBackgroundColor(playerid, atm_page_input_0[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_page_input_0[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_page_input_0[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_page_input_0[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_page_input_0[playerid], 0);

    atm_page_input_1[playerid] = CreatePlayerTextDraw(playerid, 221.000000, 246.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_page_input_1[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_page_input_1[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_page_input_1[playerid], 86.500000, 0.500000);
    PlayerTextDrawSetOutline(playerid, atm_page_input_1[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_page_input_1[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_page_input_1[playerid], 1);
    PlayerTextDrawColor(playerid, atm_page_input_1[playerid], -1431655681);
    PlayerTextDrawBackgroundColor(playerid, atm_page_input_1[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_page_input_1[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_page_input_1[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_page_input_1[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_page_input_1[playerid], 0);

    atm_page_input_2[playerid] = CreatePlayerTextDraw(playerid, 221.000000, 262.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_page_input_2[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_page_input_2[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_page_input_2[playerid], 86.500000, 0.500000);
    PlayerTextDrawSetOutline(playerid, atm_page_input_2[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_page_input_2[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_page_input_2[playerid], 1);
    PlayerTextDrawColor(playerid, atm_page_input_2[playerid], -1431655681);
    PlayerTextDrawBackgroundColor(playerid, atm_page_input_2[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_page_input_2[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_page_input_2[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_page_input_2[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_page_input_2[playerid], 0);

    atm_page_input_3[playerid] = CreatePlayerTextDraw(playerid, 221.000000, 279.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_page_input_3[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_page_input_3[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_page_input_3[playerid], 86.500000, 0.500000);
    PlayerTextDrawSetOutline(playerid, atm_page_input_3[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_page_input_3[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_page_input_3[playerid], 1);
    PlayerTextDrawColor(playerid, atm_page_input_3[playerid], -1431655681);
    PlayerTextDrawBackgroundColor(playerid, atm_page_input_3[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_page_input_3[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_page_input_3[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_page_input_3[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_page_input_3[playerid], 0);

    atm_page_input_4[playerid] = CreatePlayerTextDraw(playerid, 221.000000, 251.000000, "Cash");
    PlayerTextDrawFont(playerid, atm_page_input_4[playerid], 1);
    PlayerTextDrawLetterSize(playerid, atm_page_input_4[playerid], 0.174999, 0.800000);
    PlayerTextDrawTextSize(playerid, atm_page_input_4[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, atm_page_input_4[playerid], 0);
    PlayerTextDrawSetShadow(playerid, atm_page_input_4[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_page_input_4[playerid], 1);
    PlayerTextDrawColor(playerid, atm_page_input_4[playerid], 255);
    PlayerTextDrawBackgroundColor(playerid, atm_page_input_4[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_page_input_4[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_page_input_4[playerid], 0);
    PlayerTextDrawSetProportional(playerid, atm_page_input_4[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_page_input_4[playerid], 0);

    atm_page_input_5[playerid] = CreatePlayerTextDraw(playerid, 221.000000, 267.000000, "Balance");
    PlayerTextDrawFont(playerid, atm_page_input_5[playerid], 1);
    PlayerTextDrawLetterSize(playerid, atm_page_input_5[playerid], 0.174999, 0.800000);
    PlayerTextDrawTextSize(playerid, atm_page_input_5[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, atm_page_input_5[playerid], 0);
    PlayerTextDrawSetShadow(playerid, atm_page_input_5[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_page_input_5[playerid], 1);
    PlayerTextDrawColor(playerid, atm_page_input_5[playerid], 255);
    PlayerTextDrawBackgroundColor(playerid, atm_page_input_5[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_page_input_5[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_page_input_5[playerid], 0);
    PlayerTextDrawSetProportional(playerid, atm_page_input_5[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_page_input_5[playerid], 0);

    atm_page_input_6[playerid] = CreatePlayerTextDraw(playerid, 306.000000, 250.000000, "$999999999");
    PlayerTextDrawFont(playerid, atm_page_input_6[playerid], 1);
    PlayerTextDrawLetterSize(playerid, atm_page_input_6[playerid], 0.174999, 0.800000);
    PlayerTextDrawTextSize(playerid, atm_page_input_6[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, atm_page_input_6[playerid], 0);
    PlayerTextDrawSetShadow(playerid, atm_page_input_6[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_page_input_6[playerid], 3);
    PlayerTextDrawColor(playerid, atm_page_input_6[playerid], 255);
    PlayerTextDrawBackgroundColor(playerid, atm_page_input_6[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_page_input_6[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_page_input_6[playerid], 0);
    PlayerTextDrawSetProportional(playerid, atm_page_input_6[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_page_input_6[playerid], 0);

    atm_page_input_7[playerid] = CreatePlayerTextDraw(playerid, 306.000000, 267.000000, "$999999999");
    PlayerTextDrawFont(playerid, atm_page_input_7[playerid], 1);
    PlayerTextDrawLetterSize(playerid, atm_page_input_7[playerid], 0.174999, 0.800000);
    PlayerTextDrawTextSize(playerid, atm_page_input_7[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, atm_page_input_7[playerid], 0);
    PlayerTextDrawSetShadow(playerid, atm_page_input_7[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_page_input_7[playerid], 3);
    PlayerTextDrawColor(playerid, atm_page_input_7[playerid], 255);
    PlayerTextDrawBackgroundColor(playerid, atm_page_input_7[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_page_input_7[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_page_input_7[playerid], 0);
    PlayerTextDrawSetProportional(playerid, atm_page_input_7[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_page_input_7[playerid], 0);

    atm_page_input_8[playerid] = CreatePlayerTextDraw(playerid, 219.000000, 216.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_page_input_8[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_page_input_8[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_page_input_8[playerid], 91.000000, 18.000000);
    PlayerTextDrawSetOutline(playerid, atm_page_input_8[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_page_input_8[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_page_input_8[playerid], 1);
    PlayerTextDrawColor(playerid, atm_page_input_8[playerid], -16843009);
    PlayerTextDrawBackgroundColor(playerid, atm_page_input_8[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_page_input_8[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_page_input_8[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_page_input_8[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_page_input_8[playerid], 0);

    atm_page_input_9[playerid] = CreatePlayerTextDraw(playerid, 219.000000, 206.000000, "Withdraw amount");
    PlayerTextDrawFont(playerid, atm_page_input_9[playerid], 1);
    PlayerTextDrawLetterSize(playerid, atm_page_input_9[playerid], 0.174999, 0.800000);
    PlayerTextDrawTextSize(playerid, atm_page_input_9[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, atm_page_input_9[playerid], 0);
    PlayerTextDrawSetShadow(playerid, atm_page_input_9[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_page_input_9[playerid], 1);
    PlayerTextDrawColor(playerid, atm_page_input_9[playerid], 255);
    PlayerTextDrawBackgroundColor(playerid, atm_page_input_9[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_page_input_9[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_page_input_9[playerid], 0);
    PlayerTextDrawSetProportional(playerid, atm_page_input_9[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_page_input_9[playerid], 0);

    atm_page_input_10[playerid] = CreatePlayerTextDraw(playerid, 223.000000, 221.000000, "$9999999999999999");
    PlayerTextDrawFont(playerid, atm_page_input_10[playerid], 1);
    PlayerTextDrawLetterSize(playerid, atm_page_input_10[playerid], 0.174999, 0.800000);
    PlayerTextDrawTextSize(playerid, atm_page_input_10[playerid], 306.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, atm_page_input_10[playerid], 0);
    PlayerTextDrawSetShadow(playerid, atm_page_input_10[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_page_input_10[playerid], 1);
    PlayerTextDrawColor(playerid, atm_page_input_10[playerid], 255);
    PlayerTextDrawBackgroundColor(playerid, atm_page_input_10[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_page_input_10[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_page_input_10[playerid], 0);
    PlayerTextDrawSetProportional(playerid, atm_page_input_10[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_page_input_10[playerid], 0);

    atm_confirm_btn[playerid] = CreatePlayerTextDraw(playerid, 378.000000, 321.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, atm_confirm_btn[playerid], 4);
    PlayerTextDrawLetterSize(playerid, atm_confirm_btn[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, atm_confirm_btn[playerid], 39.500000, 19.500000);
    PlayerTextDrawSetOutline(playerid, atm_confirm_btn[playerid], 1);
    PlayerTextDrawSetShadow(playerid, atm_confirm_btn[playerid], 0);
    PlayerTextDrawAlignment(playerid, atm_confirm_btn[playerid], 1);
    PlayerTextDrawColor(playerid, atm_confirm_btn[playerid], 1650551039);
    PlayerTextDrawBackgroundColor(playerid, atm_confirm_btn[playerid], 255);
    PlayerTextDrawBoxColor(playerid, atm_confirm_btn[playerid], 50);
    PlayerTextDrawUseBox(playerid, atm_confirm_btn[playerid], 1);
    PlayerTextDrawSetProportional(playerid, atm_confirm_btn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, atm_confirm_btn[playerid], 1);

    atm_main[playerid][20] = CreatePlayerTextDraw(playerid, 386.000000, 326.000000, "Confirm");
    PlayerTextDrawFont(playerid, atm_main[playerid][20], 1);
    PlayerTextDrawLetterSize(playerid, atm_main[playerid][20], 0.174999, 0.949999);
    PlayerTextDrawTextSize(playerid, atm_main[playerid][20], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, atm_main[playerid][20], 0);
    PlayerTextDrawSetShadow(playerid, atm_main[playerid][20], 0);
    PlayerTextDrawAlignment(playerid, atm_main[playerid][20], 1);
    PlayerTextDrawColor(playerid, atm_main[playerid][20], -1);
    PlayerTextDrawBackgroundColor(playerid, atm_main[playerid][20], 255);
    PlayerTextDrawBoxColor(playerid, atm_main[playerid][20], 50);
    PlayerTextDrawUseBox(playerid, atm_main[playerid][20], 0);
    PlayerTextDrawSetProportional(playerid, atm_main[playerid][20], 1);
    PlayerTextDrawSetSelectable(playerid, atm_main[playerid][20], 0);
    return 1;
}

stock ATM_DestroyTD(playerid) {
    for (new i = 0; i < 21; i++) {
        if (IsValidDynamicPlayerTextDraw(playerid, atm_main[playerid][i])) {
            PlayerTextDrawDestroy(playerid, atm_main[playerid][i]);
            atm_main[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
        }
    }

    if (IsValidDynamicPlayerTextDraw(playerid, atm_cash_text[playerid])) {
        PlayerTextDrawDestroy(playerid, atm_cash_text[playerid]);
        atm_cash_text[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (IsValidDynamicPlayerTextDraw(playerid, atm_balance_text[playerid])) {
        PlayerTextDrawDestroy(playerid, atm_balance_text[playerid]);
        atm_balance_text[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (IsValidDynamicPlayerTextDraw(playerid, atm_withdraw_btn[playerid])) {
        PlayerTextDrawDestroy(playerid, atm_withdraw_btn[playerid]);
        atm_withdraw_btn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (atm_deposit_btn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, atm_deposit_btn[playerid]);
        atm_deposit_btn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (atm_quick_withdraw_btn_0[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, atm_quick_withdraw_btn_0[playerid]);
        atm_quick_withdraw_btn_0[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (atm_quick_withdraw_btn_1[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, atm_quick_withdraw_btn_1[playerid]);
        atm_quick_withdraw_btn_1[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (atm_quick_withdraw_btn_2[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, atm_quick_withdraw_btn_2[playerid]);
        atm_quick_withdraw_btn_2[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (atm_quick_deposit_all_btn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, atm_quick_deposit_all_btn[playerid]);
        atm_quick_deposit_all_btn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (atm_exit_btn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, atm_exit_btn[playerid]);
        atm_exit_btn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (atm_num_7_btn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, atm_num_7_btn[playerid]);
        atm_num_7_btn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (atm_num_8_btn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, atm_num_8_btn[playerid]);
        atm_num_8_btn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (atm_num_9_btn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, atm_num_9_btn[playerid]);
        atm_num_9_btn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (atm_num_4_btn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, atm_num_4_btn[playerid]);
        atm_num_4_btn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (atm_num_5_btn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, atm_num_5_btn[playerid]);
        atm_num_5_btn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (atm_num_6_btn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, atm_num_6_btn[playerid]);
        atm_num_6_btn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (atm_num_1_btn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, atm_num_1_btn[playerid]);
        atm_num_1_btn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (atm_num_2_btn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, atm_num_2_btn[playerid]);
        atm_num_2_btn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (atm_num_3_btn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, atm_num_3_btn[playerid]);
        atm_num_3_btn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (atm_num_0_btn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, atm_num_0_btn[playerid]);
        atm_num_0_btn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (atm_num_clear_btn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, atm_num_clear_btn[playerid]);
        atm_num_clear_btn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    for (new i = 0; i <= 10; i++) {
        if (atm_page_input_0[playerid] != PlayerText:INVALID_TEXT_DRAW) {
            PlayerTextDrawDestroy(playerid, atm_page_input_0[playerid]);
            atm_page_input_0[playerid] = PlayerText:INVALID_TEXT_DRAW;
        }
    }

    if (atm_confirm_btn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, atm_confirm_btn[playerid]);
        atm_confirm_btn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    return 1;
}

stock ATM_ShowMain(playerid) {
    // อัพเดทตัวเลข cash/balance ก่อนโชว์
    new str[32];
    format(str, sizeof str, "$%d", playerData[playerid][pMoney]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_cash_text[playerid]))
        PlayerTextDrawSetString(playerid, atm_cash_text[playerid], str);

    format(str, sizeof str, "$%d", playerData[playerid][pBank]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_balance_text[playerid]))
        PlayerTextDrawSetString(playerid, atm_balance_text[playerid], str);

    for (new i = 0; i < 20; i++) {
        if (i == 10) {
            if (IsValidDynamicPlayerTextDraw(playerid, atm_cash_text[playerid]))
                PlayerTextDrawShow(playerid, atm_cash_text[playerid]);
            if (IsValidDynamicPlayerTextDraw(playerid, atm_balance_text[playerid]))
                PlayerTextDrawShow(playerid, atm_balance_text[playerid]);
        } else if (i == 11) {
            if (IsValidDynamicPlayerTextDraw(playerid, atm_withdraw_btn[playerid]))
                PlayerTextDrawShow(playerid, atm_withdraw_btn[playerid]);
        } else if (i == 12) {
            if (IsValidDynamicPlayerTextDraw(playerid, atm_deposit_btn[playerid]))
                PlayerTextDrawShow(playerid, atm_deposit_btn[playerid]);
        } else if (i == 14) {
            if (IsValidDynamicPlayerTextDraw(playerid, atm_quick_withdraw_btn_0[playerid]))
                PlayerTextDrawShow(playerid, atm_quick_withdraw_btn_0[playerid]);
        } else if (i == 15) {
            if (IsValidDynamicPlayerTextDraw(playerid, atm_quick_withdraw_btn_1[playerid]))
                PlayerTextDrawShow(playerid, atm_quick_withdraw_btn_1[playerid]);
        } else if (i == 16) {
            if (IsValidDynamicPlayerTextDraw(playerid, atm_quick_withdraw_btn_2[playerid]))
                PlayerTextDrawShow(playerid, atm_quick_withdraw_btn_2[playerid]);
        } else if (i == 17) {
            if (IsValidDynamicPlayerTextDraw(playerid, atm_quick_deposit_all_btn[playerid]))
                PlayerTextDrawShow(playerid, atm_quick_deposit_all_btn[playerid]);
        } else if (i == 19) {
            if (IsValidDynamicPlayerTextDraw(playerid, atm_exit_btn[playerid]))
                PlayerTextDrawShow(playerid, atm_exit_btn[playerid]);
        }
        if (IsValidDynamicPlayerTextDraw(playerid, atm_main[playerid][i]))
            PlayerTextDrawShow(playerid, atm_main[playerid][i]);
    }
    SelectTextDraw(playerid, 0x303030FF);
    return 1;
}

stock ATM_HideMain(playerid) {
    if (IsValidDynamicPlayerTextDraw(playerid, atm_withdraw_btn[playerid]))
        PlayerTextDrawHide(playerid, atm_withdraw_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_deposit_btn[playerid]))
        PlayerTextDrawHide(playerid, atm_deposit_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_quick_withdraw_btn_0[playerid]))
        PlayerTextDrawHide(playerid, atm_quick_withdraw_btn_0[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_quick_withdraw_btn_1[playerid]))
        PlayerTextDrawHide(playerid, atm_quick_withdraw_btn_1[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_quick_deposit_all_btn[playerid]))
        PlayerTextDrawHide(playerid, atm_quick_deposit_all_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_exit_btn[playerid]))
        PlayerTextDrawHide(playerid, atm_exit_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_quick_withdraw_btn_2[playerid]))
        PlayerTextDrawHide(playerid, atm_quick_withdraw_btn_2[playerid]);

    for (new i = 0; i < 21; i++) {
        if (IsValidDynamicPlayerTextDraw(playerid, atm_main[playerid][i]))
            PlayerTextDrawHide(playerid, atm_main[playerid][i]);
    }
    if (IsValidDynamicPlayerTextDraw(playerid, atm_cash_text[playerid]))
        PlayerTextDrawHide(playerid, atm_cash_text[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_balance_text[playerid]))
        PlayerTextDrawHide(playerid, atm_balance_text[playerid]);
    return 1;
}

stock ATM_ShowNumpad(playerid, mode) {
    ATM_Mode[playerid]        = mode;
    ATM_InputAmount[playerid] = 0;
    ATM_Page[playerid]        = ATM_PAGE_NUMPAD;

    // อัพเดท label ตาม mode
    new modeLabel[32];
    if (mode == ATM_MODE_WITHDRAW)     modeLabel = "Withdraw amount";
    else if (mode == ATM_MODE_DEPOSIT) modeLabel = "Deposit amount";
    else                               modeLabel = "Transfer amount";

    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_9[playerid]))
        PlayerTextDrawSetString(playerid, atm_page_input_9[playerid], modeLabel);

    // อัพเดท label row
    if (mode == ATM_MODE_TRANSFER) {
        if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_4[playerid]))
            PlayerTextDrawSetString(playerid, atm_page_input_4[playerid], "To");
        if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_5[playerid]))
            PlayerTextDrawSetString(playerid, atm_page_input_5[playerid], "Balance");

        new tName[MAX_PLAYER_NAME + 1];
        GetPlayerName(ATM_TransferTarget[playerid], tName, sizeof tName);
        if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_6[playerid]))
            PlayerTextDrawSetString(playerid, atm_page_input_6[playerid], tName);
    } else {
        if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_4[playerid]))
            PlayerTextDrawSetString(playerid, atm_page_input_4[playerid], "Cash");
        if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_5[playerid]))
            PlayerTextDrawSetString(playerid, atm_page_input_5[playerid], "Balance");

        new str[32];
        format(str, sizeof str, "$%d", playerData[playerid][pMoney]);
        if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_6[playerid]))
            PlayerTextDrawSetString(playerid, atm_page_input_6[playerid], str);
    }
    new str[32];
    format(str, sizeof str, "$%d", playerData[playerid][pBank]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_7[playerid]))
        PlayerTextDrawSetString(playerid, atm_page_input_7[playerid], str);

    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_10[playerid]))
        PlayerTextDrawSetString(playerid, atm_page_input_10[playerid], "$0");

    for (new i = 6; i < 19; i++) {
        if (i == 10) {
            if (IsValidDynamicPlayerTextDraw(playerid, atm_cash_text[playerid]))
                PlayerTextDrawHide(playerid, atm_cash_text[playerid]);
            if (IsValidDynamicPlayerTextDraw(playerid, atm_balance_text[playerid]))
                PlayerTextDrawHide(playerid, atm_balance_text[playerid]);
        } else if (i == 11) {
            if (IsValidDynamicPlayerTextDraw(playerid, atm_withdraw_btn[playerid]))
                PlayerTextDrawHide(playerid, atm_withdraw_btn[playerid]);
        } else if (i == 12) {
            if (IsValidDynamicPlayerTextDraw(playerid, atm_deposit_btn[playerid]))
                PlayerTextDrawHide(playerid, atm_deposit_btn[playerid]);
        } else if (i == 14) {
            if (IsValidDynamicPlayerTextDraw(playerid, atm_quick_withdraw_btn_0[playerid]))
                PlayerTextDrawHide(playerid, atm_quick_withdraw_btn_0[playerid]);
        } else if (i == 15) {
            if (IsValidDynamicPlayerTextDraw(playerid, atm_quick_withdraw_btn_1[playerid]))
                PlayerTextDrawHide(playerid, atm_quick_withdraw_btn_1[playerid]);
        } else if (i == 16) {
            if (IsValidDynamicPlayerTextDraw(playerid, atm_quick_withdraw_btn_2[playerid]))
                PlayerTextDrawHide(playerid, atm_quick_withdraw_btn_2[playerid]);
        } else if (i == 17) {
            if (IsValidDynamicPlayerTextDraw(playerid, atm_quick_deposit_all_btn[playerid]))
                PlayerTextDrawHide(playerid, atm_quick_deposit_all_btn[playerid]);
        }
        if (IsValidDynamicPlayerTextDraw(playerid, atm_main[playerid][i]))
            PlayerTextDrawHide(playerid, atm_main[playerid][i]);
    }

    // โชว์ page_input panel
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_0[playerid]))
        PlayerTextDrawShow(playerid, atm_page_input_0[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_1[playerid]))
        PlayerTextDrawShow(playerid, atm_page_input_1[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_2[playerid]))
        PlayerTextDrawShow(playerid, atm_page_input_2[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_3[playerid]))
        PlayerTextDrawShow(playerid, atm_page_input_3[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_4[playerid]))
        PlayerTextDrawShow(playerid, atm_page_input_4[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_5[playerid]))
        PlayerTextDrawShow(playerid, atm_page_input_5[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_6[playerid]))
        PlayerTextDrawShow(playerid, atm_page_input_6[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_7[playerid]))
        PlayerTextDrawShow(playerid, atm_page_input_7[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_8[playerid]))
        PlayerTextDrawShow(playerid, atm_page_input_8[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_9[playerid]))
        PlayerTextDrawShow(playerid, atm_page_input_9[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_10[playerid]))
        PlayerTextDrawShow(playerid, atm_page_input_10[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_confirm_btn[playerid]))
        PlayerTextDrawShow(playerid, atm_confirm_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_main[playerid][20]))
        PlayerTextDrawShow(playerid, atm_main[playerid][20]); // "Confirm" text

    // โชว์ numpad
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_7_btn[playerid]))
        PlayerTextDrawShow(playerid, atm_num_7_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_8_btn[playerid]))
        PlayerTextDrawShow(playerid, atm_num_8_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_9_btn[playerid]))
        PlayerTextDrawShow(playerid, atm_num_9_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_4_btn[playerid]))
        PlayerTextDrawShow(playerid, atm_num_4_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_5_btn[playerid]))
        PlayerTextDrawShow(playerid, atm_num_5_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_6_btn[playerid]))
        PlayerTextDrawShow(playerid, atm_num_6_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_1_btn[playerid]))
        PlayerTextDrawShow(playerid, atm_num_1_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_2_btn[playerid]))
        PlayerTextDrawShow(playerid, atm_num_2_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_3_btn[playerid]))
        PlayerTextDrawShow(playerid, atm_num_3_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_0_btn[playerid]))
        PlayerTextDrawShow(playerid, atm_num_0_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_clear_btn[playerid]))
        PlayerTextDrawShow(playerid, atm_num_clear_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_0[playerid]))
        PlayerTextDrawShow(playerid, atm_num_0[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_1[playerid]))
        PlayerTextDrawShow(playerid, atm_num_1[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_2[playerid]))
        PlayerTextDrawShow(playerid, atm_num_2[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_3[playerid]))
        PlayerTextDrawShow(playerid, atm_num_3[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_4[playerid]))
        PlayerTextDrawShow(playerid, atm_num_4[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_5[playerid]))
        PlayerTextDrawShow(playerid, atm_num_5[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_6[playerid]))
        PlayerTextDrawShow(playerid, atm_num_6[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_7[playerid]))
        PlayerTextDrawShow(playerid, atm_num_7[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_8[playerid]))
        PlayerTextDrawShow(playerid, atm_num_8[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_9[playerid]))
        PlayerTextDrawShow(playerid, atm_num_9[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_10[playerid]))
        PlayerTextDrawShow(playerid, atm_num_10[playerid]);

    SelectTextDraw(playerid, 0x303030FF);
    return 1;
}

stock ATM_HideNumpad(playerid) {
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_0[playerid]))
        PlayerTextDrawHide(playerid, atm_page_input_0[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_1[playerid]))
        PlayerTextDrawHide(playerid, atm_page_input_1[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_2[playerid]))
        PlayerTextDrawHide(playerid, atm_page_input_2[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_3[playerid]))
        PlayerTextDrawHide(playerid, atm_page_input_3[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_4[playerid]))
        PlayerTextDrawHide(playerid, atm_page_input_4[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_5[playerid]))
        PlayerTextDrawHide(playerid, atm_page_input_5[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_6[playerid]))
        PlayerTextDrawHide(playerid, atm_page_input_6[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_7[playerid]))
        PlayerTextDrawHide(playerid, atm_page_input_7[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_8[playerid]))
        PlayerTextDrawHide(playerid, atm_page_input_8[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_9[playerid]))
        PlayerTextDrawHide(playerid, atm_page_input_9[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_10[playerid]))
        PlayerTextDrawHide(playerid, atm_page_input_10[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_confirm_btn[playerid]))
        PlayerTextDrawHide(playerid, atm_confirm_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_main[playerid][20]))
        PlayerTextDrawHide(playerid, atm_main[playerid][20]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_7_btn[playerid]))
        PlayerTextDrawHide(playerid, atm_num_7_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_8_btn[playerid]))
        PlayerTextDrawHide(playerid, atm_num_8_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_9_btn[playerid]))
        PlayerTextDrawHide(playerid, atm_num_9_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_4_btn[playerid]))
        PlayerTextDrawHide(playerid, atm_num_4_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_5_btn[playerid]))
        PlayerTextDrawHide(playerid, atm_num_5_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_6_btn[playerid]))
        PlayerTextDrawHide(playerid, atm_num_6_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_1_btn[playerid]))
        PlayerTextDrawHide(playerid, atm_num_1_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_2_btn[playerid]))
        PlayerTextDrawHide(playerid, atm_num_2_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_3_btn[playerid]))
        PlayerTextDrawHide(playerid, atm_num_3_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_0_btn[playerid]))
        PlayerTextDrawHide(playerid, atm_num_0_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_clear_btn[playerid]))
        PlayerTextDrawHide(playerid, atm_num_clear_btn[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_0[playerid]))
        PlayerTextDrawHide(playerid, atm_num_0[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_1[playerid]))
        PlayerTextDrawHide(playerid, atm_num_1[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_2[playerid]))
        PlayerTextDrawHide(playerid, atm_num_2[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_3[playerid]))
        PlayerTextDrawHide(playerid, atm_num_3[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_4[playerid]))
        PlayerTextDrawHide(playerid, atm_num_4[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_5[playerid]))
        PlayerTextDrawHide(playerid, atm_num_5[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_6[playerid]))
        PlayerTextDrawHide(playerid, atm_num_6[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_7[playerid]))
        PlayerTextDrawHide(playerid, atm_num_7[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_8[playerid]))
        PlayerTextDrawHide(playerid, atm_num_8[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_9[playerid]))
        PlayerTextDrawHide(playerid, atm_num_9[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_num_10[playerid]))
        PlayerTextDrawHide(playerid, atm_num_10[playerid]);
    return 1;
}

stock ATM_Close(playerid) {
    ATM_HideMain(playerid);
    ATM_HideNumpad(playerid);
    ATM_Page[playerid]          = ATM_PAGE_NONE;
    ATM_InputAmount[playerid]   = 0;
    ATM_TransferTarget[playerid]= INVALID_PLAYER_ID;
    CancelSelectTextDraw(playerid);
    return 1;
}

stock ATM_NumpadPress(playerid, digit) {
    // จำกัด 9 หลัก กัน overflow
    if (ATM_InputAmount[playerid] > 99999999) return 1;
    ATM_InputAmount[playerid] = ATM_InputAmount[playerid] * 10 + digit;

    new str[32];
    format(str, sizeof str, "$%d", ATM_InputAmount[playerid]);
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_10[playerid])) {
        PlayerTextDrawSetString(playerid, atm_page_input_10[playerid], str);
        PlayerTextDrawShow(playerid, atm_page_input_10[playerid]);
    }
    return 1;
}

stock ATM_NumpadClear(playerid) {
    ATM_InputAmount[playerid] = 0;
    if (IsValidDynamicPlayerTextDraw(playerid, atm_page_input_10[playerid])) {
        PlayerTextDrawSetString(playerid, atm_page_input_10[playerid], "$0");
        PlayerTextDrawShow(playerid, atm_page_input_10[playerid]);
    }
    return 1;
}

stock ATM_Confirm(playerid) {
    new amount = ATM_InputAmount[playerid];
    if (amount <= 0) {
        SendErrorMessage(playerid, "{FFFFFF}กรุณากรอกจำนวนเงิน");
        return 1;
    }

    switch (ATM_Mode[playerid]) {
        case ATM_MODE_WITHDRAW: {
            if (playerData[playerid][pBank] < amount) {
                SendErrorMessage(playerid, "{FFFFFF}ยอดเงินในธนาคารไม่พอ");
                ATM_NumpadClear(playerid);
                return 1;
            }
            playerData[playerid][pBank] -= amount;
            GivePlayerMoneyEx(playerid, amount);
            SavePlayerBank(playerid);
            ApplyAnimation(playerid, "DEALER", "shop_pay", 4.1, 0, 1, 1, 0, 0, 1);
            SendCongratMessage(playerid, "{FFFFFF}ถอนเงิน {FF4444}$%d{FFFFFF} | ยอดธนาคาร: {FF4444}$%d", amount, playerData[playerid][pBank]);
        }
        case ATM_MODE_DEPOSIT: {
            if (playerData[playerid][pMoney] < amount) {
                SendErrorMessage(playerid, "{FFFFFF}เงินสดไม่พอ");
                ATM_NumpadClear(playerid);
                return 1;
            }
            GivePlayerMoneyEx(playerid, -amount);
            playerData[playerid][pBank] += amount;
            SavePlayerBank(playerid);
            ApplyAnimation(playerid, "DEALER", "shop_pay", 4.1, 0, 1, 1, 0, 0, 1);
            SendCongratMessage(playerid, "{FFFFFF}ฝากเงิน {00DD00}$%d{FFFFFF} | ยอดธนาคาร: {00DD00}$%d", amount, playerData[playerid][pBank]);
        }
        case ATM_MODE_TRANSFER: {
            new targetid = ATM_TransferTarget[playerid];
            if (!IsPlayerConnected(targetid) || !GetPlayerLoggedIn(targetid)) {
                SendErrorMessage(playerid, "{FFFFFF}ผู้รับออฟไลน์แล้ว");
                ATM_Close(playerid);
                return 1;
            }
            if (playerData[playerid][pBank] < amount) {
                SendErrorMessage(playerid, "{FFFFFF}ยอดเงินในธนาคารไม่พอ");
                ATM_NumpadClear(playerid);
                return 1;
            }
            if (targetid == playerid) {
                SendErrorMessage(playerid, "{FFFFFF}ไม่สามารถโอนให้ตัวเองได้");
                return 1;
            }
            playerData[playerid][pBank] -= amount;
            playerData[targetid][pBank] += amount;
            SavePlayerBank(playerid);
            SavePlayerBank(targetid);
            ApplyAnimation(playerid, "DEALER", "shop_pay", 4.1, 0, 1, 1, 0, 0, 1);
            SendCongratMessage(playerid, "{FFFFFF}โอนเงิน {00DD00}$%d{FFFFFF} ให้ %s | คงเหลือ: {00DD00}$%d", amount, ReturnPlayerRPName(targetid), playerData[playerid][pBank]);
            SendCongratMessage(targetid, "{FFFFFF}ได้รับโอน {00DD00}$%d{FFFFFF} จาก %s", amount, ReturnPlayerRPName(playerid));
        }
    }
    ATM_Close(playerid);
    return 1;
}

stock ATM_ShowTransferTargetDialog(playerid) {
    inline ChooseMethod(res, list, string:in[]) {
        #pragma unused in
        if (!res) @return 1;
        switch (list) {
            case 0: ATM_ShowTransferList(playerid);
            case 1: ATM_ShowTransferByID(playerid);
        }
    }
    Dialog_ShowCallback(playerid, using inline ChooseMethod, DIALOG_STYLE_LIST,
        "{FFFFFF}โอนเงิน — เลือกวิธี",
        "{FFFFFF}เลือกจากรายชื่อผู้เล่น Online\n{FFFFFF}พิมพ์ Player ID",
        "{FFFFFF}เลือก", "{FFFFFF}ยกเลิก");
    return 1;
}

stock ATM_ShowTransferList(playerid) {
    new body[2048] = "", count = 0;
    new mapping[MAX_PLAYERS];

    foreach (new i : Player) {
        if (i == playerid || !GetPlayerLoggedIn(i)) continue;
        new row[64];
        format(row, sizeof row, "[%d] %s\n", i, ReturnPlayerName(i));
        strcat(body, row, sizeof body);
        mapping[count++] = i;
    }

    if (!count) {
        SendErrorMessage(playerid, "{FFFFFF}ไม่มีผู้เล่นออนไลน์คนอื่น");
        return 1;
    }

    static s_map[MAX_PLAYERS], s_count;
    s_count = count;
    for (new i = 0; i < count; i++) s_map[i] = mapping[i];

    inline PickPlayer(res, list, string:in[]) {
        #pragma unused in
        if (!res) @return 1;
        if (list >= s_count) @return 1;

        new targetid = s_map[list];
        if (!IsPlayerConnected(targetid) || !GetPlayerLoggedIn(targetid)) {
            SendErrorMessage(playerid, "{FFFFFF}ผู้เล่นออฟไลน์แล้ว");
            @return ATM_ShowTransferList(playerid);
        }
        ATM_TransferTarget[playerid] = targetid;
        ATM_Page[playerid]           = ATM_PAGE_NUMPAD;
        ATM_ShowMain(playerid);
        ATM_ShowNumpad(playerid, ATM_MODE_TRANSFER);
    }
    Dialog_ShowCallback(playerid, using inline PickPlayer, DIALOG_STYLE_LIST,
        "{FFFFFF}เลือกผู้รับโอน", body, "{FFFFFF}เลือก", "{FFFFFF}กลับ");
    return 1;
}

stock ATM_ShowTransferByID(playerid) {
    inline InputID(res, list, string:in[]) {
        #pragma unused list
        if (!res) @return 1;

        new targetid = strval(in);
        if (targetid == playerid) {
            SendErrorMessage(playerid, "{FFFFFF}ไม่สามารถโอนให้ตัวเองได้");
            @return ATM_ShowTransferByID(playerid);
        }
        if (!IsPlayerConnected(targetid) || !GetPlayerLoggedIn(targetid)) {
            SendErrorMessage(playerid, "{FFFFFF}ไม่พบผู้เล่น ID นี้");
            @return ATM_ShowTransferByID(playerid);
        }
        ATM_TransferTarget[playerid] = targetid;
        ATM_Page[playerid]           = ATM_PAGE_NUMPAD;
        ATM_ShowMain(playerid);
        ATM_ShowNumpad(playerid, ATM_MODE_TRANSFER);
    }
    Dialog_ShowCallback(playerid, using inline InputID, DIALOG_STYLE_INPUT,
        "{FFFFFF}โอนเงิน — พิมพ์ Player ID",
        "{FFFFFF}กรอก Player ID ของผู้รับ",
        "{FFFFFF}ยืนยัน", "{FFFFFF}กลับ");
    return 1;
}

public ATMLoad() {
    new rows;
    cache_get_row_count(rows);

    for (new i = 0; i < rows && i < MAX_ATM; i++) {
        ATMData[i][E_ATM_exists] = true;
        cache_get_value_name_int(i,   "atmid",    ATMData[i][E_ATM_id]);
        cache_get_value_name_int(i,   "interior", ATMData[i][E_ATM_interior]);
        cache_get_value_name_int(i,   "world",    ATMData[i][E_ATM_world]);
        cache_get_value_name_float(i, "x",        ATMData[i][E_ATM_x]);
        cache_get_value_name_float(i, "y",        ATMData[i][E_ATM_y]);
        cache_get_value_name_float(i, "z",        ATMData[i][E_ATM_z]);
        cache_get_value_name_float(i, "rx",       ATMData[i][E_ATM_rx]);
        cache_get_value_name_float(i, "ry",       ATMData[i][E_ATM_ry]);
        cache_get_value_name_float(i, "rz",       ATMData[i][E_ATM_rz]);
        ATMRefresh(i);
    }
    printf("[SYSTEM][DB] %d ATM loaded.", rows);
    return true;
}

public OnATMCreated(atmid) {
    if (atmid == -1 || !ATMData[atmid][E_ATM_exists]) return false;
    ATMData[atmid][E_ATM_id] = cache_insert_id();
    ATMSave(atmid);
    return true;
}

stock ATMSave(atmid) {
    new query[512];
    mysql_format(get_handle(), query, sizeof query,
        "UPDATE "ATM_TABLE" SET \
        `interior`='%d', `world`='%d', \
        `x`='%.4f', `y`='%.4f', `z`='%.4f', \
        `rx`='%.4f', `ry`='%.4f', `rz`='%.4f' \
        WHERE `atmid`='%d'",
        ATMData[atmid][E_ATM_interior],
        ATMData[atmid][E_ATM_world],
        ATMData[atmid][E_ATM_x],  ATMData[atmid][E_ATM_y],  ATMData[atmid][E_ATM_z],
        ATMData[atmid][E_ATM_rx], ATMData[atmid][E_ATM_ry], ATMData[atmid][E_ATM_rz],
        ATMData[atmid][E_ATM_id]);
    return mysql_tquery(get_handle(), query);
}

stock ATMCreate(interior, virtualworld, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
    for (new i = 0; i < MAX_ATM; i++) {
        if (!ATMData[i][E_ATM_exists]) {
            ATMData[i][E_ATM_exists]   = true;
            ATMData[i][E_ATM_interior] = interior;
            ATMData[i][E_ATM_world]    = virtualworld;
            ATMData[i][E_ATM_x]  = x;   ATMData[i][E_ATM_y]  = y;   ATMData[i][E_ATM_z]  = z;
            ATMData[i][E_ATM_rx] = rx;  ATMData[i][E_ATM_ry] = ry;  ATMData[i][E_ATM_rz] = rz;

            mysql_tquery(get_handle(),
                "INSERT INTO "ATM_TABLE" (`atmid`) VALUES(0)",
                "OnATMCreated", "d", i);
            ATMRefresh(i);
            return i;
        }
    }
    return -1;
}

stock ATMDelete(atmid) {
    if (atmid == -1 || !ATMData[atmid][E_ATM_exists]) return false;

    if (IsValidDynamicObject(ATMData[atmid][E_ATM_obj]))
        DestroyDynamicObject(ATMData[atmid][E_ATM_obj]);

    if (IsValidDynamic3DTextLabel(ATMData[atmid][E_ATM_label]))
        DestroyDynamic3DTextLabel(ATMData[atmid][E_ATM_label]);

    new query[64];
    mysql_format(get_handle(), query, sizeof query,
        "DELETE FROM "ATM_TABLE" WHERE `atmid`='%d'", ATMData[atmid][E_ATM_id]);
    mysql_tquery(get_handle(), query);

    ATMData[atmid][E_ATM_exists] = false;
    ATMData[atmid][E_ATM_id]     = 0;
    return true;
}

stock ATMRefresh(atmid) {
    if (atmid == -1 || !ATMData[atmid][E_ATM_exists]) return false;

    if (IsValidDynamicObject(ATMData[atmid][E_ATM_obj]))
        DestroyDynamicObject(ATMData[atmid][E_ATM_obj]);

    if (IsValidDynamic3DTextLabel(ATMData[atmid][E_ATM_label]))
        DestroyDynamic3DTextLabel(ATMData[atmid][E_ATM_label]);

    ATMData[atmid][E_ATM_obj] = CreateDynamicObject(
        MODEL_ATM,
        ATMData[atmid][E_ATM_x],  ATMData[atmid][E_ATM_y],  ATMData[atmid][E_ATM_z],
        ATMData[atmid][E_ATM_rx], ATMData[atmid][E_ATM_ry], ATMData[atmid][E_ATM_rz],
        ATMData[atmid][E_ATM_world],
        ATMData[atmid][E_ATM_interior]
    );

    ATMData[atmid][E_ATM_label] = CreateDynamic3DTextLabel(
        ATM_TEXT,
        ATM_LABEL_COLOR,
        ATMData[atmid][E_ATM_x],
        ATMData[atmid][E_ATM_y],
        ATMData[atmid][E_ATM_z] + 1.2,
        ATM_USE_RANGE * 3.0,
        .worldid  = ATMData[atmid][E_ATM_world],
        .interiorid = ATMData[atmid][E_ATM_interior]
    );
    return true;
}

stock ATMNearest(playerid) {
    for (new i = 0; i < MAX_ATM; i++) {
        if (ATMData[i][E_ATM_exists] && 
            GetPlayerInterior(playerid) == ATMData[i][E_ATM_interior] &&
            GetPlayerVirtualWorld(playerid) == ATMData[i][E_ATM_world] &&
            IsPlayerInRangeOfPoint(playerid, ATM_USE_RANGE,
            ATMData[i][E_ATM_x], ATMData[i][E_ATM_y], ATMData[i][E_ATM_z]))
        {
            return i;
        }
    }
    return -1;
}

stock ATMDialogUse(playerid) {
    new str[512];

    inline const Menu(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return true;

        switch (listitem) {
            case 0: ATMDialogUse(playerid); // refresh
            case 1: ATMDialogDeposit(playerid);
            case 2: ATMDialogWithdraw(playerid);
            case 3: ATMDialogTransfer(playerid);
        }
    }

    format(str, sizeof str, "{AAAAAA}ยอดเงินธนาคาร: {00DD00}$%d\n{FFFFFF}ฝากเงิน\n{FF4444}ถอนเงิน\n{FFFFFF}โอนเงิน", playerData[playerid][pBank]);
    Dialog_ShowCallback(playerid, using inline Menu, DIALOG_STYLE_LIST, "{FFFFFF}ตู้ ATM", str, "เลือก", "ยกเลิก");
    return true;
}

stock ATMDialogDeposit(playerid) {
    inline const Input(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return ATMDialogUse(playerid);

        new amount = 0;
        if (sscanf(inputtext, "d", amount) || amount <= 0) {
            SendErrorMessage(playerid, "{FFFFFF}กรุณาป้อนจำนวนเงินที่ถูกต้อง");
            @return ATMDialogDeposit(playerid);
        }

        if (playerData[playerid][pMoney] < amount) {
            SendErrorMessage(playerid, "{FFFFFF}เงินสดไม่เพียงพอ");
            @return ATMDialogDeposit(playerid);
        }

        GivePlayerMoneyEx(playerid, -amount);
        playerData[playerid][pBank] += amount;

        // บันทึกลง DB
        SavePlayerBank(playerid);
        ApplyAnimation(playerid, "DEALER", "shop_pay", 4.1, 0, 1, 1, 0, 0, 1);
        SendCongratMessage(playerid, "{FFFFFF}คุณฝากเงิน {00DD00}$%d{FFFFFF} | ยอดธนาคาร: {00DD00}$%d{FFFFFF} | เงินสด: {00DD00}$%d", amount, playerData[playerid][pBank], playerData[playerid][pMoney]);
        @return ATMDialogUse(playerid);
    }

    new str[128];
    format(str, sizeof str, "{FFFFFF}เงินสดในมือ: {FFFF00}$%d\n\n{FFFFFF}ป้อนจำนวนเงินที่ต้องการฝาก", playerData[playerid][pMoney]);
    Dialog_ShowCallback(playerid, using inline Input, DIALOG_STYLE_INPUT, "{FFFFFF}ฝากเงิน", str, "ฝาก", "ย้อนกลับ");
    return true;
}

stock ATMDialogWithdraw(playerid) {
    inline const Input(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return ATMDialogUse(playerid);

        new amount = 0;
        if (sscanf(inputtext, "d", amount) || amount <= 0) {
            SendErrorMessage(playerid, "{FFFFFF}กรุณาป้อนจำนวนเงินที่ถูกต้อง");
            @return ATMDialogWithdraw(playerid);
        }

        if (playerData[playerid][pBank] < amount) {
            SendErrorMessage(playerid, "{FFFFFF}ยอดเงินในธนาคารไม่เพียงพอ");
            @return ATMDialogWithdraw(playerid);
        }

        playerData[playerid][pBank] -= amount;
        GivePlayerMoneyEx(playerid, amount);

        SavePlayerBank(playerid);
        ApplyAnimation(playerid, "DEALER", "shop_pay", 4.1, 0, 1, 1, 0, 0, 1);
        SendCongratMessage(playerid, "{FFFFFF}คุณฝากเงิน {FF4444}$%d{FFFFFF} | ยอดธนาคาร: {FF4444}$%d{FFFFFF} | เงินสด: {FF4444}$%d", amount, playerData[playerid][pBank], playerData[playerid][pMoney]);
        @return ATMDialogUse(playerid);
    }

    new str[128];
    format(str, sizeof str, "{FFFFFF}ยอดเงินธนาคาร: {00DD00}$%d\n\n{FFFFFF}ป้อนจำนวนเงินที่ต้องการถอน", playerData[playerid][pBank]);
    Dialog_ShowCallback(playerid, using inline Input, DIALOG_STYLE_INPUT, "{FFFFFF}ถอนเงิน", str, "ถอน", "ย้อนกลับ");
    return true;
}

stock ATMDialogTransfer(playerid) {
    inline const ChooseMethod(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return ATMDialogUse(playerid);

        switch (listitem) {
            case 0: ATMDialogTransferList(playerid);
            case 1: ATMDialogTransferByID(playerid);
        }
    }
    Dialog_ShowCallback(playerid, using inline ChooseMethod, DIALOG_STYLE_LIST,
        "{FFFFFF}โอนเงิน — เลือกวิธี",
        "{FFFFFF}เลือกจากรายการผู้เล่น Online\n{FFFFFF}พิมพ์ Player ID",
        "เลือก", "ย้อนกลับ");
    return true;
}

stock ATMDialogTransferList(playerid) {
    new str[2048] = "";
    new count = 0;
    new mapping[MAX_PLAYERS];

    foreach (new i : Player) {
        if (i == playerid) continue;
        if (!GetPlayerLoggedIn(i)) continue;

        new row[64];
        format(row, sizeof row, "[%d] %s\n", i, ReturnPlayerName(i));
        strcat(str, row);
        mapping[count] = i;
        count++;
    }

    if (!count) {
        SendErrorMessage(playerid, "ไม่มีผู้เล่นออนไลน์คนอื่น");
        return ATMDialogTransfer(playerid);
    }

    static s_map[MAX_PLAYERS], s_count;
    s_count = count;
    for (new i = 0; i < count; i++) s_map[i] = mapping[i];

    inline const PickPlayer(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return ATMDialogTransfer(playerid);
        if (listitem >= s_count) @return true;

        new targetid = s_map[listitem];
        if (!IsPlayerConnected(targetid) || !GetPlayerLoggedIn(targetid)) {
            SendErrorMessage(playerid, "{FFFFFF}ผู้เล่นคนนั้นออฟไลน์แล้ว");
            @return ATMDialogTransferList(playerid);
        }
        ATMDialogTransferAmount(playerid, targetid);
    }
    Dialog_ShowCallback(playerid, using inline PickPlayer, DIALOG_STYLE_LIST, "{FFFFFF}เลือกผู้รับโอน", str, "เลือก", "ย้อนกลับ");
    return true;
}

stock ATMDialogTransferByID(playerid) {
    inline const InputID(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return ATMDialogTransfer(playerid);

        new targetid = -1;
        if (sscanf(inputtext, "d", targetid)) {
            SendErrorMessage(playerid, "กรุณาป้อนเป็นตัวเลข ID เท่านั้น");
            @return ATMDialogTransferByID(playerid);
        }

        if (targetid == playerid) {
            SendErrorMessage(playerid, "ไม่สามารถโอนเงินให้ตัวเองได้");
            @return ATMDialogTransferByID(playerid);
        }

        if (!IsPlayerConnected(targetid) || !GetPlayerLoggedIn(targetid)) {
            SendErrorMessage(playerid, "ไม่พบผู้เล่น ID นี้ หรือยังไม่ได้ล็อกอิน");
            @return ATMDialogTransferByID(playerid);
        }

        ATMDialogTransferAmount(playerid, targetid);
    }
    Dialog_ShowCallback(playerid, using inline InputID, DIALOG_STYLE_INPUT,
        "{FFFFFF}โอนเงิน — พิมพ์ Player ID",
        "ป้อน Player ID ของผู้ที่ต้องการโอนเงินให้",
        "ยืนยัน", "ย้อนกลับ");
    return true;
}

stock ATMDialogTransferAmount(playerid, targetid) {
    inline const InputAmount(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return ATMDialogTransfer(playerid);

        new amount = 0;
        if (sscanf(inputtext, "d", amount) || amount <= 0) {
            SendErrorMessage(playerid, "กรุณาป้อนจำนวนเงินที่ถูกต้อง");
            @return ATMDialogTransferAmount(playerid, targetid);
        }

        if (playerData[playerid][pBank] < amount) {
            SendErrorMessage(playerid, "ยอดเงินในธนาคารไม่เพียงพอ");
            @return ATMDialogTransferAmount(playerid, targetid);
        }

        if (!IsPlayerConnected(targetid) || !GetPlayerLoggedIn(targetid)) {
            SendErrorMessage(playerid, "ผู้เล่นคนนั้นออฟไลน์แล้ว");
            @return ATMDialogTransfer(playerid);
        }

        playerData[playerid][pBank] -= amount;
        playerData[targetid][pBank] += amount;

        SavePlayerBank(playerid);
        SavePlayerBank(targetid);

        ApplyAnimation(playerid, "DEALER", "shop_pay", 4.1, 0, 1, 1, 0, 0, 1);
        SendCongratMessage(playerid, "{FFFFFF}โอนเงิน {00DD00}$%d{FFFFFF} ให้ %s (ID:%d) | ยอดคงเหลือ: {00DD00}$%d", amount, ReturnPlayerRPName(targetid), targetid, playerData[playerid][pBank]);
        SendCongratMessage(targetid, "{FFFFFF}ได้รับโอนเงิน {00DD00}$%d{FFFFFF} จาก %s (ID:%d) | ยอดคงเหลือ: {00DD00}$%d", amount, ReturnPlayerRPName(playerid), playerid, playerData[targetid][pBank]);
        @return ATMDialogUse(playerid);
    }

    new str[128];
    format(str, sizeof str, "{FFFFFF}โอนให้: {FFFF00}%s {AAAAAA}(ID:%d)\n{AAAAAA}ยอดธนาคารของคุณ: {00DD00}$%d\n\n{FFFFFF}ป้อนจำนวนเงินที่ต้องการโอน", ReturnPlayerRPName(targetid), targetid, playerData[playerid][pBank]);
    Dialog_ShowCallback(playerid, using inline InputAmount, DIALOG_STYLE_INPUT, "{FFFFFF}โอนเงิน", str, "โอน", "ย้อนกลับ");
    return true;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT:objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
    new atmid = ATM_EditingID[playerid];
    if (atmid == -1) return true;

    if (response == EDIT_RESPONSE_CANCEL) {
        ATMRefresh(atmid);
        ATM_EditingID[playerid] = -1;
        SendWarningMessage(playerid, "{FFFFFF}ยกเลิกการย้ายตำแหน่ง");
        return true;
    }

    if (response == EDIT_RESPONSE_FINAL) {
        ATMData[atmid][E_ATM_x]  = x;   ATMData[atmid][E_ATM_y]  = y;   ATMData[atmid][E_ATM_z]  = z;
        ATMData[atmid][E_ATM_rx] = rx;  ATMData[atmid][E_ATM_ry] = ry;  ATMData[atmid][E_ATM_rz] = rz;
        ATMSave(atmid);
        ATMRefresh(atmid); // รีเฟรช label ให้ตามตำแหน่งใหม่
        ATM_EditingID[playerid] = -1;

        SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ย้าย ATM ID:%d -> (%.1f,%.1f,%.1f) RX:%.1f RY:%.1f RZ:%.1f", ReturnPlayerName(playerid), atmid, x, y, z, rx, ry, rz);
    }
    return true;
}

stock PanelATM(playerid) {
    if (!IsPlayerAdminEx(playerid)) return true;

    inline const MainMenu(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return true;

        switch (listitem) {
            case 0: ATMDialogCreate(playerid);
            case 1: ATMDialogDelete(playerid);
            case 2: ATMDialogEdit(playerid);
            case 3: ATMDialogList(playerid);
            case 4: ATMDialogWarpTo(playerid);
        }
    }
    Dialog_ShowCallback(playerid, using inline MainMenu, DIALOG_STYLE_LIST,
        "{FFFFFF}AdminPanel (ATM)",
        "สร้าง ATM\n\
        ลบ ATM\n\
        ย้าย/หมุน ATM (Edit Mode)\n\
        รายการ ATM ทั้งหมด\n\
        วาร์ปไปหา ATM",
        "เลือก", "ยกเลิก");
    return true;
}

YCMD:aatm(playerid, string:params[], help) {
    if (!GetPlayerLoggedIn(playerid)) return 1;
    if (!IsPlayerAdminEx(playerid)) return SendErrorMessage(playerid, "คุณไม่สามารถใช้คำสั่งนี้ได้ โปรดอย่าใช้มันแอดมินกำลังดูคุณอยู่");

    PanelATM(playerid);
    return 1;
}

stock ATMDialogCreate(playerid) {
    inline const Confirm(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, inputtext, pid
        if (!response) @return PanelATM(playerid);

        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);

        new id = ATMCreate(
            GetPlayerInterior(playerid),
            GetPlayerVirtualWorld(playerid),
            x, y, z, 0.0, 0.0, 0.0);

        if (id == -1) {
            SendErrorMessage(playerid, "{FFFFFF}ความจุ ATM เต็มแล้ว (MAX_ATM)");
            @return true;
        }
        SendAdminMessage(COLOR_ADMIN, "AdmLog: %s สร้าง ATM ID:%d ที่ (%.1f,%.1f,%.1f)", ReturnPlayerName(playerid), id, x, y, z);
        SendCongratMessage(playerid, "{FFFFFF}ATM สร้างแล้ว ID:%d — ใช้เมนู [ย้าย/หมุน] เพื่อจัดตำแหน่ง", id);
    }
    Dialog_ShowCallback(playerid, using inline Confirm, DIALOG_STYLE_MSGBOX,
        "{FFFFFF}สร้าง ATM",
        "สร้าง ATM ณ ตำแหน่งของคุณ?\n\n\
        {AAAAAA}Object จะถูกวางที่พิกัดปัจจุบัน\n\
        จากนั้นใช้ [ย้าย/หมุน ATM] เพื่อปรับตำแหน่งด้วย Edit Mode",
        "ยืนยัน", "ยกเลิก");
    return true;
}

stock ATMDialogDelete(playerid) {
    inline const InputID(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, listitem, pid
        if (!response) @return PanelATM(playerid);

        new id = -1;
        if (sscanf(inputtext, "d", id) || id < 0 || id >= MAX_ATM || !ATMData[id][E_ATM_exists]) {
            SendErrorMessage(playerid, "{FFFFFF}ID ไม่ถูกต้องหรือไม่มีอยู่ในระบบ");
            @return PanelATM(playerid);
        }
        new dbid = ATMData[id][E_ATM_id];
        ATMDelete(id);
        SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ลบ ATM LocalID:%d (DB:%d)", ReturnPlayerName(playerid), id, dbid);
    }
    Dialog_ShowCallback(playerid, using inline InputID, DIALOG_STYLE_INPUT,
        "{FFFFFF}ลบ ATM",
        "ป้อน Local ID ของ ATM ที่ต้องการลบ\n{AAAAAA}(ดู ID ได้จากเมนู รายการ ATM)",
        "ลบ", "ยกเลิก");
    return true;
}

stock ATMDialogEdit(playerid) {
    new string[4096] = "";
    new count = 0;
    new mapping[MAX_ATM];

    for (new i = 0; i < MAX_ATM; i++) {
        if (!ATMData[i][E_ATM_exists]) continue;
        new row[128];
        format(row, sizeof row,
            "{FFFFFF}%d {AAAAAA}DB:%d (%.1f, %.1f, %.1f)\n",
            i, ATMData[i][E_ATM_id],
            ATMData[i][E_ATM_x], ATMData[i][E_ATM_y], ATMData[i][E_ATM_z]);
        strcat(string, row);
        mapping[count] = i;
        count++;
    }

    if (!count) {
        SendErrorMessage(playerid, "{FFFFFF}ยังไม่มี ATM ในระบบ");
        return PanelATM(playerid);
    }

    static s_map[MAX_ATM], s_count;
    s_count = count;
    for (new i = 0; i < count; i++) s_map[i] = mapping[i];

    inline const Pick(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return PanelATM(playerid);
        if (listitem >= s_count) @return true;

        new atmid = s_map[listitem];
        ATM_EditingID[playerid] = atmid;

        SetPlayerPos(playerid,
            ATMData[atmid][E_ATM_x],
            ATMData[atmid][E_ATM_y],
            ATMData[atmid][E_ATM_z]);
        SetPlayerInterior(playerid,     ATMData[atmid][E_ATM_interior]);
        SetPlayerVirtualWorld(playerid, ATMData[atmid][E_ATM_world]);

        EditDynamicObject(playerid, ATMData[atmid][E_ATM_obj]);
        SendWarningMessage(playerid, "{FFFFFF}Edit Mode — ลาก/หมุน object แล้วกด Enter เพื่อบันทึก, ESC เพื่อยกเลิก");
    }
    Dialog_ShowCallback(playerid, using inline Pick, DIALOG_STYLE_LIST, "เลือก ATM ที่ต้องการย้าย/หมุน", string, "Edit", "ยกเลิก");
    return true;
}

stock ATMDialogList(playerid) {
    new string[4096] = "";
    new count = 0;

    for (new i = 0; i < MAX_ATM; i++) {
        if (!ATMData[i][E_ATM_exists]) continue;
        new row[256];
        format(row, sizeof row,
            "{FFFFFF}%d {AAAAAA}DB:%d %.1f,%.1f,%.1f RX:%.0f RY:%.0f RZ:%.0f INT:%d VW:%d\n",
            i, ATMData[i][E_ATM_id],
            ATMData[i][E_ATM_x], ATMData[i][E_ATM_y], ATMData[i][E_ATM_z],
            ATMData[i][E_ATM_rx], ATMData[i][E_ATM_ry], ATMData[i][E_ATM_rz],
            ATMData[i][E_ATM_interior], ATMData[i][E_ATM_world]);
        strcat(string, row);
        count++;
    }

    if (!count) return SendErrorMessage(playerid, "{FFFFFF}ยังไม่มี ATM ในระบบ");

    inline const Close(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, inputtext, listitem, response
        @return true;
    }
    Dialog_ShowCallback(playerid, using inline Close, DIALOG_STYLE_LIST,
        "รายการ ATM", string, "ปิด", "");
    return true;
}

stock ATMDialogWarpTo(playerid) {
    new string[4096] = "";
    new count = 0;
    new mapping[MAX_ATM];

    for (new i = 0; i < MAX_ATM; i++) {
        if (!ATMData[i][E_ATM_exists]) continue;
        new row[128];
        format(row, sizeof row,
            "{FFFFFF}%d {AAAAAA}DB:%d (%.1f, %.1f, %.1f) INT:%d VW:%d\n",
            i, ATMData[i][E_ATM_id],
            ATMData[i][E_ATM_x], ATMData[i][E_ATM_y], ATMData[i][E_ATM_z],
            ATMData[i][E_ATM_interior], ATMData[i][E_ATM_world]);
        strcat(string, row);
        mapping[count] = i;
        count++;
    }

    if (!count) {
        SendErrorMessage(playerid, "{FFFFFF}ยังไม่มี ATM ในระบบ");
        return PanelATM(playerid);
    }

    static s_map[MAX_ATM], s_count;
    s_count = count;
    for (new i = 0; i < count; i++) s_map[i] = mapping[i];

    inline const WarpMenu(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext, pid
        if (!response) @return PanelATM(playerid);
        if (listitem >= s_count) @return true;

        new atmid = s_map[listitem];
        SetPlayerPos(playerid,
            ATMData[atmid][E_ATM_x],
            ATMData[atmid][E_ATM_y],
            ATMData[atmid][E_ATM_z]);
        SetPlayerInterior(playerid,     ATMData[atmid][E_ATM_interior]);
        SetPlayerVirtualWorld(playerid, ATMData[atmid][E_ATM_world]);
        SendCongratMessage(playerid, "{FFFFFF}วาร์ปไปยัง ATM ID:%d (DB:%d)", atmid, ATMData[atmid][E_ATM_id]);
    }
    Dialog_ShowCallback(playerid, using inline WarpMenu, DIALOG_STYLE_LIST,
        "วาร์ปไปหา ATM", string, "วาร์ป", "ยกเลิก");
    return true;
}
