#if defined _inc_impl
#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

/* ################################################################## */
/* #  ?????????  ???????????    ???????      ?????????  ?????   ????# */
/* # ???????????????????????  ???????????   ????????????????   ???? # */
/* #????    ??? ?   ????  ?  ???     ????? ???     ???  ????  ???   # */
/* #???????????     ????    ????      ????????          ????????    # */
/* # ???????????    ????    ????      ????????          ?????????   # */
/* # ???    ????    ????    ?????     ??? ?????     ??? ???? ?????  # */
/* #???????????     ?????    ???????????   ???????????  ????? ??????# */
/* # ?????????     ?????       ???????      ?????????  ?????   ???? # */
/* ################################################################## */

stock GetPlayerMoneyEx(playerid)
    return playerData[playerid][pMoney];
stock GetPlayerRedMoneyEx(playerid)
    return playerData[playerid][pRedMoney];

stock GivePlayerMoneyEx(playerid, money) {
    playerData[playerid][pMoney] += money;

    if (playerData[playerid][pMoney] < 0)
        playerData[playerid][pMoney] = 0;

    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, playerData[playerid][pMoney]);

    new str[64];
    format(str, sizeof str, "%s$%d", (money >= 0) ? ("~g~+") : ("~r~-"), (money >= 0) ? (money) : (-money));
    GameTextForPlayer(playerid, str, 2000, 5);

    Query(get_handle(), "UPDATE "PLAYER_TABLE" SET `playerMoney` = '%d' WHERE `playerID` = '%d'",
        playerData[playerid][pMoney],
        playerData[playerid][pID]);
    return 1;
}

stock GivePlayerRedMoneyEx(playerid, money) {
    playerData[playerid][pRedMoney] += money;

    if (playerData[playerid][pRedMoney] < 0)
        playerData[playerid][pRedMoney] = 0;

    Query(get_handle(), "UPDATE "PLAYER_TABLE" SET `playerRedMoney` = '%d' WHERE `playerID` = '%d'",
        playerData[playerid][pRedMoney],
        playerData[playerid][pID]);
    return 1;
}

stock SetPlayerMoneyEx(playerid, money) {
    playerData[playerid][pMoney] = money;

    if (playerData[playerid][pMoney] < 0)
        playerData[playerid][pMoney] = 0;

    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, playerData[playerid][pMoney]);

    Query(get_handle(), "UPDATE "PLAYER_TABLE" SET `playerMoney` = '%d' WHERE `playerID` = '%d'",
        playerData[playerid][pMoney],
        playerData[playerid][pID]);
    return 1;
}

stock SetPlayerRedMoneyEx(playerid, money) {
    playerData[playerid][pRedMoney] = money;

    if (playerData[playerid][pRedMoney] < 0)
        playerData[playerid][pRedMoney] = 0;

    Query(get_handle(), "UPDATE "PLAYER_TABLE" SET `playerRedMoney` = '%d' WHERE `playerID` = '%d'",
        playerData[playerid][pRedMoney],
        playerData[playerid][pID]);
    return 1;
}

stock HexToInt(const str[]) {
    new result = 0, i = 0;

    // ตัด 0x นำหน้าออก
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
        i = 2;
    else if (str[0] == '#')
        i = 1;

    while (str[i]) {
        result <<= 4;
        switch (str[i]) {
            case '0' .. '9': result |= str[i] - '0';
            case 'a' .. 'f': result |= str[i] - 'a' + 10;
            case 'A' .. 'F': result |= str[i] - 'A' + 10;
            default: return result; // หยุดถ้าเจออักขระไม่ใช่ hex
        }
        i++;
    }
    return result;
}

stock RemovePlayerWeapon(playerid, weaponid) {
	new plyWeapons[12];
	new plyAmmo[12];
	for (new slot = 0; slot != 12; slot++) {
		new wep, ammo;
		GetPlayerWeaponData(playerid, slot, wep, ammo);
		if (wep != weaponid) {
			GetPlayerWeaponData(playerid, slot, plyWeapons[slot], plyAmmo[slot]);
		}
	}
	ResetPlayerWeapons(playerid);
	for (new slot = 0; slot != 12; slot++) {
		GivePlayerWeapon(playerid, plyWeapons[slot], plyAmmo[slot]);
	}
}

stock GetPlayerNameEx(playerid) {
    new string[MAX_PLAYER_NAME + 1];
    GetPlayerName(playerid, string, sizeof(string));
    return string;
}

stock ClearPlayerChat(playerid, lines) {
	for (new i = 0; i <= lines; i++) {
	    SendClientMessage(playerid, COLOR_WHITE, "");
	}
	return 1;
}

stock ReturnDate() {
    new sendString[90], MonthStr[40], month, day, year;
    new hour, minute, second;

    getdate(year, month, day);
    gettime(hour, minute, second);

    switch (month) {
        case 1:  MonthStr = "มกราคม";
        case 2:  MonthStr = "กุมภาพันธ์";
        case 3:  MonthStr = "มีนาคม";
        case 4:  MonthStr = "เมษายน";
        case 5:  MonthStr = "พฤษภาคม";
        case 6:  MonthStr = "มิถุนายน";
        case 7:  MonthStr = "กรกฎาคม";
        case 8:  MonthStr = "สิงหาคม";
        case 9:  MonthStr = "กันยายน";
        case 10: MonthStr = "ตุลาคม";
        case 11: MonthStr = "พฤศจิกายน";
        case 12: MonthStr = "ธันวาคม";
    }

    format(sendString, 90, "%d %s %d - %02d:%02d:%02d", day, MonthStr, year, hour, minute, second);
    return sendString;
}

stock DelayedKick(playerid) {
    SetTimerEx("_DelayedKick", 500, false, "d", playerid);
    return 1;
}

stock UpdatePlayerDataEx(playerid, const fieldss[], data) {
	new str[144];
	format(str, 144, "UPDATE `players` SET `%s` = '%d' WHERE `playerID` = '%d'", fieldss, data, playerData[playerid][pID]);
	mysql_tquery (get_handle(), str);
	return true;
}

stock UpdatePlayerDataStr(playerid, const fieldss[], data) {
	new str[144];
	format(str, 144, "UPDATE `players` SET `%s` = '%s' WHERE `playerID` = '%d'", fieldss, data, playerData[playerid][pID]);
	mysql_tquery(get_handle(), str);
	return true;
}

stock acc_int_strcat(query[], len, const name[], number) {
	new string[256];
	format(string, sizeof(string), "`%s` = '%d',", name, number);
	strcat(query, string, len);
	return true;
}

stock acc_str_strcat(query[], len, const name[], const str[]) {
	new string[256];
	format(string, sizeof(string), "`%s` = '%s',", name, str);
	strcat(query, string, len);
	return true;
}

stock acc_float_strcat(query[], len, const name[], Float:number) {
	new string[256];
	format(string, sizeof(string), "`%s` = '%f',", name, number);
	strcat(query, string, len);
	return true;
}

stock Query(MySQL: handle, const query[], va_args<>) {
    new squery[1024];
    va_format(squery, sizeof(squery), query, va_start<2>);
    mysql_tquery(handle, squery);
    return 1;
}

stock SetPlayerHealthEx(playerid, Float:hp) {
    if (hp <= 0.0) hp = 0.0;
    if (hp > 100.0) hp = 100.0;

    playerData[playerid][pHealth] = hp;
    SetPlayerHealth(playerid, hp);
    return 1;
}

stock SavePlayerHealth(playerid) {
    new Float:hp;
    GetPlayerHealth(playerid, hp);
    playerData[playerid][pHealth] = hp;
    Query(get_handle(),
        "UPDATE "PLAYER_TABLE" SET `playerHealth` = '%.2f' WHERE `playerID` = '%d'",
        playerData[playerid][pHealth],
        playerData[playerid][pID]
    );
    return 1;
}

stock SetPlayerSkinEx(playerid, skin) {
	SetPlayerSkin(playerid, skin);

	for (new i = 0; i < 6; i++) AksDel[playerid][i] = 0;
	CheckItem(playerid);
	Pizda(playerid);
	for (new i = 0; i < 8; i++) {
		if (playerData[playerid][pSlotItem][i] != 0) GiveItem(playerid, playerData[playerid][pSlotItem][i]);
	}

	CheckInvs(playerid, 6);
	CheckInvs(playerid, 5);
	CheckInvs(playerid, 1);
	CheckInvs(playerid, 2);
	CheckInvs(playerid, 3);
	CheckInvs(playerid, 4);
	CheckInvs(playerid, 0);
	CheckInvs(playerid, 7);
	SetPlayerChatBubble(playerid, "กำลังเปลี่ยนสกิน", COLOR_GREEN, 10.0, 5000);
	return true;
}

stock SetPlayerAttachedObjectEx(playerid, index, modelid, bone, Float:fOffsetX = 0.0, Float:fOffsetY = 0.0, Float:fOffsetZ = 0.0, Float:fRotX = 0.0, Float:fRotY = 0.0, Float:fRotZ = 0.0, Float:fScaleX = 1.0, Float:fScaleY = 1.0, Float:fScaleZ = 1.0) {
	SetPlayerAttachedObject(playerid, index, modelid, bone, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
	return true;
}

/* ######################################################################## */
/* # ???????????  ?????  ????? ???????????  ?????       ?????   ????????? # */
/* #??????????????????  ????? ??????????????????       ?????   ???????????# */
/* # ????    ???? ????   ????  ????    ???? ????        ????  ???     ??? # */
/* # ???????????  ????   ????  ???????????  ????        ???? ????         # */
/* # ??????????   ????   ????  ???????????? ????        ???? ????         # */
/* # ????         ????   ????  ????    ???? ????      ? ???? ?????     ???# */
/* # ?????        ??????????   ???????????  ??????????? ????? ??????????? # */
/* #?????          ????????   ???????????  ??????????? ?????   ?????????  # */
/* ######################################################################## */

public _DelayedKick(playerid) {
    Kick(playerid);
    return 1;
}
