#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
    new Variable;

	Variable = CreateActor(72, DEFAULT_POS_GIFTBOX_X, DEFAULT_POS_GIFTBOX_Y, DEFAULT_POS_GIFTBOX_Z, DEFAULT_POS_GIFTBOX_A);
	CreateDynamic3DTextLabel("{ffff00}ลุงเริง คนชอบหมี\n{ffffff}รับของขวัญจากฉันไปสิ!\n{ffffff}กด {00FF00}N", -1, DEFAULT_POS_GIFTBOX_X, DEFAULT_POS_GIFTBOX_Y, DEFAULT_POS_GIFTBOX_Z+1.4, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1);
	ApplyActorAnimation(Variable, "PED", "IDLE_HBHB", 4.0, 1, 1, 1, 0, 0);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if (newkeys & KEY_NO && !IsPlayerInAnyVehicle(playerid)) {
		if (IsPlayerInRangeOfPoint(playerid, 2, DEFAULT_POS_GIFTBOX_X, DEFAULT_POS_GIFTBOX_Y, DEFAULT_POS_GIFTBOX_Z)) {
			Giftbox(playerid);
		}
    }
    return 1;
}

public Giftbox(playerid) {
    new string2[356], string3[356], body[256];

    format(string2, sizeof(string2), "%s", (playerData[playerid][pGiftbox] == 0) ? "{FF6600}ยังไม่ได้รับ" : "{33FF00}รับไปแล้ว");
    format(string2, sizeof(string2), "%s", (playerData[playerid][pGiftbox2] == 0) ? "{FF6600}ยังไม่ได้รับ" : "{33FF00}รับไปแล้ว");

    format(body, sizeof(body),
        "{FFFFFF}รับของจากลุงเริง\t\t%s\n\
        {FFFFFF}สอบใบขับขี่\t\t%s",
        string2, string3);

    inline GiftboxPlayer(res, list, string:in[]) {
        #pragma unused in
        if (!res) @return 1;

        switch (list) {
            case 0: { // รับของ 1
                if (playerData[playerid][pGiftbox] == 1) 
					return SendErrorMessage(playerid, "คุณไม่สามารถรับของซ้ำได้เนื่องจากคุณรับไปแล้ว");

				SendPlayerAction(playerid, "คุณได้รับเงินจำนวน $%d บาท", DEFAULT_MONEY_GIFTBOX);
				SendPlayerAction(playerid, "คุณได้รับเบอร์เกอร์ไก่ จำนวน %d ชิ้น", DEFAULT_ITEM_GIFTBOX);
				SendPlayerAction(playerid, "คุณได้รับเป๊ปซี่ จำนวน %d ชิ้น", DEFAULT_ITEM_GIFTBOX);
                
                AddItemByName(playerid, "เบอร์เกอร์ไก่", DEFAULT_ITEM_GIFTBOX);
                AddItemByName(playerid, "เป๊ปซี่", DEFAULT_ITEM_GIFTBOX);

                GivePlayerMoneyEx(playerid, DEFAULT_MONEY_GIFTBOX);
			
				playerData[playerid][pGiftbox] = 1;

                inline ShowOnlyGiftt(_res, _list, string:_in[]) {
                    #pragma unused _res, _list, _in
                    @return 1;
                }
                Dialog_ShowCallback(playerid, using inline ShowOnlyGiftt, DIALOG_STYLE_LIST, "รับของขวัญเด็กใหม่",
                    "{FFFFFF}คุณได้รับเงิน {009900}$2000 บาท\n\
                    {FFFFFF}ขนมปัง {FF0099}+10\n\
                    {FFFFFF}น้ำเปล่า {66FFFF}+10", "ตกลง", "ปิด");

				//PlayAudioStreamForPlayer(playerid, "http://45.83.207.32/music/giftbox.mp3", 2594.2402,1889.6318,11.0234, 10.0, 1);
            }
            case 1: { // รับของ 2
                if (playerData[playerid][pGiftbox2] == 1) 
					return SendErrorMessage(playerid, "คุณไม่สามารถรับของซ้ำได้เนื่องจากคุณทำไปแล้ว");

				/*if (!Inventory_HasItem(playerid, "ใบขับขี่รถยนต์"))
					return SendErrorMessage(playerid, "กรุณาไปสถานที่สอบใบขับขี่เพื่อรับของจากลูกลุงเริง!");*/

				GivePlayerMoneyEx(playerid, DEFAULT_MONEY_GIFTBOX2);
				SendPlayerAction(playerid, "คุณได้รับเงินจำนวน $%d บาท", DEFAULT_MONEY_GIFTBOX2);
			
				playerData[playerid][pGiftbox2] = 1;

				//PlayAudioStreamForPlayer(playerid, "http://45.83.207.32/music/giftbox.mp3", 2594.2402,1889.6318,11.0234, 10.0, 1);
            }
        }
    }
    Dialog_ShowCallback(playerid, using inline GiftboxPlayer, DIALOG_STYLE_LIST,
        "{FFFFFF}ทำเควสรับของกับลุงเริง",
        body, "ตกลง", "ยกเลิก");
    return 1;
}