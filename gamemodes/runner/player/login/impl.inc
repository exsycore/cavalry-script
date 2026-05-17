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

stock bool:GetPlayerLoggedIn(playerid) {
	return (playerData[playerid][IsLoggedIn] == true) ? true : false;
}

stock SelectGenderDialog(playerid) {
	new hash[256];
	GetPVarString(playerid, "hash", hash, sizeof(hash));

	inline Response(response, listitem, string:inputtext[]) {
		#pragma unused inputtext
		if (!response) {
			SelectGender[playerid] = DEFAULT_PLAYER_SKIN_MALE;
			bcrypt_hash(playerid, "OnPasswordHash", hash, BCRYPT_COST);
			@return 1;
		}

		switch (listitem) {
			case 0: {
				SelectGender[playerid] = DEFAULT_PLAYER_SKIN_MALE;
				bcrypt_hash(playerid, "OnPasswordHash", hash, BCRYPT_COST);
			}
			case 1: {
				SelectGender[playerid] = DEFAULT_PLAYER_SKIN_FEMALE;
				bcrypt_hash(playerid, "OnPasswordHash", hash, BCRYPT_COST);
			}
		}
	}
	Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_LIST
		, "{FFFFFF}เลือกเพศ"
		, "{FFFFFF}ชาย\n{FFFFFF}หญิง"
		, "{FFFFFF}ถัดไป"
		, ""
	);
	return 1;
}

stock ShowDialog_Register(playerid) {
	new title[32];
	format(title, sizeof(title), REGISTER_TITLE);

	new string[512];
	format(string, sizeof(string), REGISTER_TEXT);
	TogglePlayerSpectating(playerid, true);

	InterpolateCameraPos(playerid, 2173.0742, -1046.8438, 74.5567, 2173.0742, -1046.8438, 74.5567, 10000);
	InterpolateCameraLookAt(playerid, 2172.1289, -1047.1642, 74.4168, 2172.1289, -1047.1642, 74.4168, 10000);

	inline Response(response, listitem, string:inputtext[]) {
		#pragma unused listitem
		if (!response) {
			va_SendClientMessage(playerid, COLOR_RED, "[!] {FFFFFF}ท่านได้ออกจากระบบเรียบร้อยแล้ว");
			va_SendClientMessage(playerid, COLOR_RED, "[!] {FFFFFF}ท่านสามารถใช้คำสั่ง (/q) เพื่อปิดหน้าต่างเกม");
			DelayedKick(playerid);
		} else {
			if (strlen(inputtext) <= 4) {
				va_SendClientMessage(playerid, COLOR_RED, "[!] {FFFFFF}รหัสผ่านต้องมีความยาวมากกว่า 4 ตัวอักษร");
				ShowDialog_Register(playerid);
				@return 1;
			}

			// hashPassword(playerid, inputtext);
			SetPVarString(playerid, "hash", inputtext);
			SelectGenderDialog(playerid);
		}
	}
	Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_PASSWORD
		, title
		, string
		, "{FFFFFF}ลงทะเบียน"
		, "{FFFFFF}ออกเกม"
	);
	return 1;
}

stock ShowDialog_Login(playerid) {
	new title[256];
	format(title, sizeof(title), LOGIN_TITLE);

	new string[256];
	format(string, sizeof string, LOGIN_TEXT);
	TogglePlayerSpectating(playerid, true);

	InterpolateCameraPos(playerid, 2173.0742, -1046.8438, 74.5567, 2173.0742, -1046.8438, 74.5567, 10000);
	InterpolateCameraLookAt(playerid, 2172.1289, -1047.1642, 74.4168, 2172.1289, -1047.1642, 74.4168, 10000);

	inline Response(response, litsitem, string:inputtext[]) {
		#pragma unused litsitem
		if (!response) {
			va_SendClientMessage(playerid, COLOR_RED, "[!] {FFFFFF}ท่านได้ออกจากระบบเรียบร้อยแล้ว");
			va_SendClientMessage(playerid, COLOR_RED, "[!] {FFFFFF}ท่านสามารถใช้คำสั่ง (/q) เพื่อปิดหน้าต่างเกม");
			DelayedKick(playerid);
		} else {
			new
				tempHash[BCRYPT_HASH_LENGTH];
			GetPVarString(playerid, "tempPassword", tempHash, sizeof(tempHash));
			bcrypt_verify(playerid, "OnPasswordCheck", inputtext, tempHash);
		}
	}
	Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_PASSWORD
		, title
		, string
		, "{FFFFFF}เข้าสู่ระบบ"
		, "{FFFFFF}ออกเกม"
	);
	return 1;
}

stock LoadPlayerData(playerid) {
	cache_get_value_name_int(0, "playerID", playerData[playerid][pID]);
    cache_get_value_name(0, "playerRegDate", playerData[playerid][pRegisterDate], 90);
	cache_get_value_name_int(0, "playerGender", playerData[playerid][pGender]);
	cache_get_value_name_int(0, "playerAdmin", playerData[playerid][pAdmin]);
	cache_get_value_name_int(0, "pInvColors", playerData[playerid][pInvColors]);
	cache_get_value_name_int(0, "Skin", playerData[playerid][pSkin]);
	cache_get_value_name_int(0, "playerMoney", playerData[playerid][pMoney]);
	cache_get_value_name_int(0, "playerBank", playerData[playerid][pBank]);
	cache_get_value_name_int(0, "playerRedMoney", playerData[playerid][pRedMoney]);
	cache_get_value_name_float(0, "pPosX", playerData[playerid][pPosX]);
	cache_get_value_name_float(0, "pPosY", playerData[playerid][pPosY]);
	cache_get_value_name_float(0, "pPosZ", playerData[playerid][pPosZ]);
	cache_get_value_name_float(0, "pPosA", playerData[playerid][pPosA]);
	cache_get_value_name_float(0, "playerHealth", playerData[playerid][pHealth]);
	cache_get_value_name_float(0, "playerArmour", playerData[playerid][pArmour]);
	cache_get_value_name_int(0, "playerExp", playerData[playerid][pExp]);
	cache_get_value_name_int(0, "playerLevel", playerData[playerid][pLevel]);
	cache_get_value_name_float(0, "playerHungry", playerData[playerid][pHungry]);
	cache_get_value_name_float(0, "playerThirsty", playerData[playerid][pThirsty]);
	cache_get_value_name_int(0, "playerInDeath", playerData[playerid][pInDeath]);
	cache_get_value_name_int(0, "playerInjuredTime", playerData[playerid][pInjuredTime]);
	cache_get_value_name_int(0, "playerFaction", playerData[playerid][pFaction]);
	cache_get_value_name_int(0, "playerRank", playerData[playerid][pRank]);
	cache_get_value_name_int(0, "playerGang", playerData[playerid][pGang]);
	cache_get_value_name_int(0, "playerGangRank", playerData[playerid][pGangRank]);
	cache_get_value_name_int(0, "playerPassport", playerData[playerid][pPassport]);
	cache_get_value_name_int(0, "playerGiftbox", playerData[playerid][pGiftbox]);
	cache_get_value_name_int(0, "playerGiftbox2", playerData[playerid][pGiftbox2]);

	// ================================== INVENTORY ======================================
	cache_get_value_name_float(0, "InvPos_X", playerData[playerid][pInvPos_X]);
	cache_get_value_name_float(0, "InvPos_Y", playerData[playerid][pInvPos_Y]);
	cache_get_value_name_float(0, "InvSize_X", playerData[playerid][pInvSize_X]);
	cache_get_value_name_float(0, "InvSize_Y", playerData[playerid][pInvSize_Y]);
	cache_get_value_name_int(0, "pInvColors", playerData[playerid][pInvColors]);
	cache_get_value_name_int(0, "pSlotItem0", playerData[playerid][pSlotItem][0]);
	cache_get_value_name_int(0, "pSlotItem1", playerData[playerid][pSlotItem][1]);
	cache_get_value_name_int(0, "pSlotItem2", playerData[playerid][pSlotItem][2]);
	cache_get_value_name_int(0, "pSlotItem3", playerData[playerid][pSlotItem][3]);
	cache_get_value_name_int(0, "pSlotItem4", playerData[playerid][pSlotItem][4]);
	cache_get_value_name_int(0, "pSlotItem5", playerData[playerid][pSlotItem][5]);
	cache_get_value_name_int(0, "pSlotItem6", playerData[playerid][pSlotItem][6]);
	cache_get_value_name_int(0, "pSlotItem7", playerData[playerid][pSlotItem][7]);
	// ===================================================================================
	return 1;
}

stock UpdatePlayerPos(playerid) {
	if (!IsPlayerConnected(playerid)) return 1;
	if (!GetPlayerLoggedIn(playerid)) return 1;

	GetPlayerPos(playerid,
		playerData[playerid][pPosX],
		playerData[playerid][pPosY],
		playerData[playerid][pPosZ]
	);
	GetPlayerFacingAngle(playerid, playerData[playerid][pPosA]);
	Query(get_handle(), "UPDATE "PLAYER_TABLE" SET `pPosX` = '%.2f', `pPosY` = '%.2f', `pPosZ` = '%.2f', `pPosA` = '%.2f' WHERE `playerID` = '%i'"
	, playerData[playerid][pPosX]
	, playerData[playerid][pPosY]
	, playerData[playerid][pPosZ]
	, playerData[playerid][pPosA]
	, playerData[playerid][pID]);
	return 1;
}

stock SavePlayerBank(playerid) {
	if (!IsPlayerConnected(playerid)) return 1;
	if (!GetPlayerLoggedIn(playerid)) return 1;

	Query(get_handle(), "UPDATE "PLAYER_TABLE" SET `playerBank` = '%d' WHERE `playerID` = '%i'"
	, playerData[playerid][pBank]
	, playerData[playerid][pID]);
	return 1;
}

stock UpdatePlayerData(playerid) {
    if (!playerData[playerid][IsLoggedIn]) return false;

	if (playerData[playerid][pInDeath] == 0) {
        UpdatePlayerPos(playerid);
		SavePlayerHealth(playerid);
    }

    new query[2048];
	query = "UPDATE "PLAYER_TABLE" SET ";
	acc_int_strcat(query, sizeof(query), "playerAdmin", playerData[playerid][pAdmin]);
	acc_int_strcat(query, sizeof(query), "pInvColors", playerData[playerid][pInvColors]);
	acc_int_strcat(query, sizeof(query), "Skin", playerData[playerid][pSkin]);
	acc_int_strcat(query, sizeof(query), "playerMoney", playerData[playerid][pMoney]);
	acc_int_strcat(query, sizeof(query), "playerBank", playerData[playerid][pBank]);
	acc_int_strcat(query, sizeof(query), "playerRedMoney", playerData[playerid][pRedMoney]);
	acc_float_strcat(query, sizeof(query), "pPosX", playerData[playerid][pPosX]);
	acc_float_strcat(query, sizeof(query), "pPosY", playerData[playerid][pPosY]);
	acc_float_strcat(query, sizeof(query), "pPosZ", playerData[playerid][pPosZ]);
	acc_float_strcat(query, sizeof(query), "pPosA", playerData[playerid][pPosA]);
	acc_float_strcat(query, sizeof(query), "playerHealth", playerData[playerid][pHealth]);
	acc_float_strcat(query, sizeof(query), "playerArmour", playerData[playerid][pArmour]);
	acc_int_strcat(query, sizeof(query), "playerExp", playerData[playerid][pExp]);
	acc_int_strcat(query, sizeof(query), "playerLevel", playerData[playerid][pLevel]);
	acc_float_strcat(query, sizeof(query), "playerHungry", playerData[playerid][pHungry]);
	acc_float_strcat(query, sizeof(query), "playerThirsty", playerData[playerid][pThirsty]);
	acc_int_strcat(query, sizeof(query), "playerInDeath", playerData[playerid][pInDeath]);
	acc_int_strcat(query, sizeof(query), "playerInjuredTime", playerData[playerid][pInjuredTime]);
	acc_int_strcat(query, sizeof(query), "playerFaction", playerData[playerid][pFaction]);
	acc_int_strcat(query, sizeof(query), "playerRank", playerData[playerid][pRank]);
	acc_int_strcat(query, sizeof(query), "playerGang", playerData[playerid][pGang]);
	acc_int_strcat(query, sizeof(query), "playerGangRank", playerData[playerid][pGangRank]);
	acc_int_strcat(query, sizeof(query), "playerPassport", playerData[playerid][pPassport]);
	acc_int_strcat(query, sizeof(query), "playerGiftbox", playerData[playerid][pGiftbox]);
	acc_int_strcat(query, sizeof(query), "playerGiftbox2", playerData[playerid][pGiftbox2]);

	// ================================== INVENTORY ======================================
	acc_float_strcat(query, sizeof(query), "InvPos_X", playerData[playerid][pInvPos_X]);
	acc_float_strcat(query, sizeof(query), "InvPos_Y", playerData[playerid][pInvPos_Y]);
	acc_float_strcat(query, sizeof(query), "InvSize_X", playerData[playerid][pInvSize_X]);
	acc_float_strcat(query, sizeof(query), "InvSize_Y", playerData[playerid][pInvSize_Y]);
	acc_int_strcat(query, sizeof(query), "pSlotItem0", playerData[playerid][pSlotItem][0]);
	acc_int_strcat(query, sizeof(query), "pSlotItem1", playerData[playerid][pSlotItem][1]);
	acc_int_strcat(query, sizeof(query), "pSlotItem2", playerData[playerid][pSlotItem][2]);
	acc_int_strcat(query, sizeof(query), "pSlotItem3", playerData[playerid][pSlotItem][3]);
	acc_int_strcat(query, sizeof(query), "pSlotItem4", playerData[playerid][pSlotItem][4]);
	acc_int_strcat(query, sizeof(query), "pSlotItem5", playerData[playerid][pSlotItem][5]);
	acc_int_strcat(query, sizeof(query), "pSlotItem6", playerData[playerid][pSlotItem][6]);
	acc_int_strcat(query, sizeof(query), "pSlotItem7", playerData[playerid][pSlotItem][7]);
	// ===================================================================================
	
	strdel(query, strlen(query)-1, strlen(query));
	new tmpQuery[2048];
	format(tmpQuery, sizeof(tmpQuery), "%s WHERE `playerID` = '%d'", query, playerData[playerid][pID]);
	mysql_query(get_handle(), tmpQuery, false);
    return true;
}

stock accountCreate(playerid, const hash[]) {
	new query[1024];
	mysql_format(get_handle(), query, sizeof(query),
	"INSERT INTO "PLAYER_TABLE" \
	(`playerName`, `playerPassword`, `playerRegDate`, `Skin`, `pPosX`, `pPosY`, `pPosZ`, `pPosA`, `playerHealth`, `playerArmour`\
	,`playerExp`, `playerLevel`, `playerGender`, `playerHungry`, `playerThirsty`, `playerInDeath`, `playerInjuredTime`, `playerFaction`\
	,`playerRank`, `playerMoney`, `playerRedMoney`, `playerBank`, `playerPassport`, `playerGiftbox`, `playerGiftbox2`) \
	VALUES \
	('%e', '%e', '%e', '%d', '%.2f', '%.2f', '%.2f', '%.2f', '%.2f', '%.2f', '%.2f', '%i', '%i', '%.2f', '%.2f', '%d', '%d', '%d', '%d',\
	'%d', '%d', '%d', '%d', '%d', '%d')"
		, GetPlayerNameEx(playerid)
		, hash
		, ReturnDate()
		, SelectGender[playerid]
		, DEFAULT_POS_X
		, DEFAULT_POS_Y
		, DEFAULT_POS_Z
		, DEFAULT_POS_A
		, DEFAULT_PLAYER_HEALTH
		, DEFAULT_PLAYER_ARMOUR
		, DEFAULT_PLAYER_EXP
		, DEFAULT_PLAYER_LEVEL
		, (SelectGender[playerid] == 18) ? GENDER_MALE : GENDER_FEMALE
		, DEFAULT_PLAYER_HUNGRY
		, DEFAULT_PLAYER_THIRSTY
		, 0
		, 0
		, DEFAULT_PLAYER_FACTION
		, DEFAULT_PLAYER_RANK
		, DEFAULT_MONEY
		, DEFAULT_RED_MONEY
		, DEFAULT_PLAYER_BANK
		, DEFAULT_PLAYER_PASSPORT
		, DEFAULT_PLAYER_GIFTBOX
		, DEFAULT_PLAYER_GIFTBOX2
	);
	mysql_tquery(get_handle(), query, "OnPlayerRegister", "d", playerid);
	return 1;
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

public OnPasswordHash(playerid) {
    new
        hash[BCRYPT_HASH_LENGTH];
    bcrypt_get_hash(hash);
    accountCreate(playerid, hash);
    return 1;
}

public OnPasswordCheck(playerid, bool:match) {
	if (match) {
		new
			query[300];

		DeletePVar(playerid, "tempPassword");

		mysql_format(get_handle(), query, sizeof(query), "SELECT * FROM "PLAYER_TABLE" WHERE `playerName` = '%e'", GetPlayerNameEx(playerid));
		mysql_tquery(get_handle(), query, "OnLoginFinished", "d", playerid);
	} else {
		va_SendClientMessage(playerid, COLOR_RED, "[!] {FFFFFF}รหัสผ่านไม่ถูกต้อง กรุณาลองใหม่อีกครั้ง");
		ShowDialog_Login(playerid);
	}
	return 1;
}

public OnPlayerLoaded(playerid) {
	new rows;
    cache_get_row_count(rows);

	if (!rows) {
		ClearPlayerChat(playerid, 20);
		ClearPlayerChat(playerid, 1);
		ShowDialog_Register(playerid);
		return 1;
	}

	new
        tempPassword[BCRYPT_HASH_LENGTH];
    cache_get_value_name(0, "playerPassword", tempPassword);
	SetPVarString(playerid, "tempPassword", tempPassword);

	ShowDialog_Login(playerid);

	ClearPlayerChat(playerid, 20);
	ClearPlayerChat(playerid, 1);
	
	playerData[playerid][LoginTimer] = SetTimerEx("OnLoginTimeout", SECONDS_TO_LOGIN * 1000, false, "d", playerid);
	return 1;
}

public OnAccountCheck(playerid) {
	new query[103];
	mysql_format(get_handle(), query, sizeof query, "SELECT * FROM "PLAYER_TABLE" WHERE `playerName` = '%e' LIMIT 1", GetPlayerNameEx(playerid));
	mysql_tquery(get_handle(), query, "OnPlayerLoaded", "d", playerid);
	return 1;
}

public OnPlayerRegister(playerid) {
	playerData[playerid][pID] = cache_insert_id();
	SetTimerEx("OnAccountCheck", 400, false, "d", playerid);
	va_SendClientMessage(playerid, COLOR_GREEN, "[!] {FFFFFF}การลงทะเบียนเสร็จสมบูรณ์ กรุณาเข้าสู่ระบบเพื่อเริ่มเล่นเกม");
	playerData[playerid][LoginTimer] = SetTimerEx("OnLoginTimeout", SECONDS_TO_LOGIN * 1000, false, "d", playerid);
	return 1;
}

public OnLoginTimeout(playerid) {
    if (!playerData[playerid][IsLoggedIn]) {
        va_SendClientMessage(playerid, COLOR_RED, "[!] {FFFFFF}ท่านใช้เวลาในการเข้าสู่ระบบเกินกำหนด");
        DelayedKick(playerid);
    }
    return 1;
}

/* ######################################################### */
/* # ?????   ?????    ???????       ???????    ?????   ????# */
/* #?????   ?????   ???????????   ??????????? ?????   ???? # */
/* # ????    ????  ???     ????? ???     ????? ????  ???   # */
/* # ???????????? ????      ????????      ???? ????????    # */
/* # ???????????? ????      ????????      ???? ?????????   # */
/* # ????    ???? ?????     ??? ?????     ???  ???? ?????  # */
/* # ?????   ????? ???????????   ???????????   ????? ??????# */
/* #?????   ?????    ???????       ???????    ?????   ???? # */
/* ######################################################### */

hook OnGameModeExit() {
	foreach (new p : Player) {
		if (IsPlayerConnected(p)) {
			if (playerData[p][IsLoggedIn]) {
				UpdatePlayerData(p);
			}
		}
	}
	return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
	if (playerData[playerid][IsLoggedIn]) {
		UpdatePlayerData(playerid);
	}
	return 1;
}

hook OnPlayerRequestClass(playerid, classid) {
	if (!playerData[playerid][IsLoggedIn]) {
	    new
			string[MAX_PLAYER_NAME + 1],
			charCounts[5];

	   	GetPlayerName(playerid, string, sizeof(string));

		for (new n; string[n] != '\0'; n++) {
			switch (string[n]) {
				case '[', ']', '.', '$', '(', ')', '@', '=': charCounts[1]++;
				case '_': charCounts[0]++;
				case '0' .. '9': charCounts[2]++;
				case 'a' .. 'z': charCounts[3]++;
				case 'A' .. 'Z': charCounts[4]++;
			}
		}

		if (strfind(string, "yourname" , true) != -1) {
			TogglePlayerSpectating(playerid, true);
			SetTimerEx("OnAccountCheck", 400, false, "d", playerid);
			return 1;
		}

		if (charCounts[0] == 0 || charCounts[0] >= 3) {
			va_SendClientMessage(playerid, COLOR_RED, "[!] {FFFFFF}ชื่อของคุณไม่ถูกต้องตามหลักเซิร์ฟเวอร์ ตัวอย่าง: Firstname_Lastname");
			SetTimerEx("_KickPlayerDelayed", 500, false, "d", playerid);
			return 1;
		}

		TogglePlayerSpectating(playerid, true);
		SetTimerEx("OnAccountCheck", 400, false, "d", playerid);
	} else {
	    SpawnPlayer(playerid);
	}
	return 1;
}

timer SetHealth[500](playerid) {
	SetPlayerHealth(playerid, playerData[playerid][pHealth]);
}

hook OnPlayerSpawn(playerid) {
	if (!GetPlayerLoggedIn(playerid)) return 1;

	SetPlayerPosEx(playerid
		, playerData[playerid][pPosX]
		, playerData[playerid][pPosY]
		, playerData[playerid][pPosZ]
		, playerData[playerid][pPosA]
	);

	if (playerData[playerid][pHealth] > 0.0)
		defer SetHealth(playerid);
    else
        SetPlayerHealth(playerid, 100.0);

	SetPlayerArmour(playerid, playerData[playerid][pArmour]);

	SetPlayerSkin(playerid, playerData[playerid][pSkin]);
	SetPlayerMoneyEx(playerid, playerData[playerid][pMoney]);
	SetPlayerColor(playerid, 0xFFFFFFFF);
	SetPlayerLevel(playerid, playerData[playerid][pLevel]);

	if (playerData[playerid][pFaction] != INVALID_FACTION) {
		Attach3DTextFactionToPlayer(playerid, playerData[playerid][pFaction]);
	} else if (playerData[playerid][pGang] != INVALID_GANG) {
        new gangIndex = GetPlayerGangIndex(playerid);

        if (gangIndex == -1 || !Player.Gang[gangIndex][@exists]) {
            playerData[playerid][pGang]     = INVALID_GANG;
            playerData[playerid][pGangRank] = 0;
			Query(get_handle(), "UPDATE "PLAYER_TABLE" SET `playerGang` = '%d', `playerGangRank` = '%d' WHERE `playerID` = '%d'"
			, playerData[playerid][pGang]
			, playerData[playerid][pGangRank]
			, playerData[playerid][pID]);
        } else {
            Attached3DTextGangToPlayer(playerid, gangIndex);
        }
    }
	
	TogglePlayerControllable(playerid, false);

	if (!playerData[playerid][pInDeath]) {
		SetTimerEx("EndCameraMoveToSpawn", 3400, false, "d", playerid);
		InterpolateCameraPos(playerid, playerData[playerid][pPosX], playerData[playerid][pPosY], playerData[playerid][pPosZ] + 75.0, playerData[playerid][pPosX], playerData[playerid][pPosY], playerData[playerid][pPosZ], 4200, CAMERA_MOVE);
		InterpolateCameraLookAt(playerid, playerData[playerid][pPosX], playerData[playerid][pPosY], playerData[playerid][pPosZ] - 90.0, playerData[playerid][pPosX], playerData[playerid][pPosY], playerData[playerid][pPosZ], 4200, CAMERA_MOVE);
	}
    return 1;
}

hook OnLoginFinished(playerid) {
	LoadPlayerData(playerid);
	ClearPlayerChat(playerid, 20);

	if (playerData[playerid][pPassport] == DEFAULT_PLAYER_PASSPORT) {
		inline Response(res, list, string:in[]) {
			#pragma unused in, list
			if (res) @return DelayedKick(playerid);
			else @return DelayedKick(playerid);
		}
		Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_MSGBOX,
			"{FFFFFF}ระบบ Passport",
			"{FF0000}แจ้งเตือน: {FFFFFF}คุณไม่มี Passport เพื่อเข้าสู่เมือง Cavalry City\n{FFFFFF}ติดต่อแอดมินที่ดิสคอร์ด: Link",
			"{FFFFFF}ตกลง",
			"");
		DelayedKick(playerid);
		return 1;
	}
	
	if (playerData[playerid][LoginTimer]) {
		KillTimer(playerData[playerid][LoginTimer]);
		playerData[playerid][LoginTimer] = 0;
	}
	
	playerData[playerid][IsLoggedIn] = true;

	if (GetPVarInt(playerid, "hasVoiceOnClient") == NO_SAMPVOICE_PLUGIN) {
        SendErrorMessage(playerid, "{FFFFFF}ระบบไม่พบปลั๊กอินไมค์โครโฟนเสริมโปรดตรวจสอบหรือติดต่อแอดมิน");
    } else if (GetPVarInt(playerid, "hasVoiceOnClient") == NO_SAMPVOICE_DEVICE) {
        SendErrorMessage(playerid, "{FFFFFF}ระบบตรวจสอบได้ว่าไม่พบอุปกรณ์ของคุณโปรดตรวจสอบหรือติดต่อแอดมิน");
    } else SendClientMessage(playerid, -1, "กด {00FF00}'B'{FFFFFF} เพื่อสนทนาด้วยเสียงในพื้นที่ใกล้เคียง");
	
	va_SendClientMessage(playerid, COLOR_GREEN, "[!] {FFFFFF}ท่านได้เข้าสู่ระบบเรียบร้อยแล้ว");
	va_SendClientMessage(playerid, COLOR_GREEN, "[!] {FFFFFF}ยินดีต้อนรับกลับคุณ %s เล่นให้สนุก", GetPlayerNameEx(playerid));

	TogglePlayerSpectating(playerid, false);
	SpawnPlayer(playerid);
    return 1;
}
