#if defined _inc_impl
    #undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
	mysql_tquery(get_handle(), "SELECT * FROM `gang`", "GangLoad", "");
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if (PRESSED(KEY_NO)) {
        new gangid = GangNearest(playerid);

        if (gangid == -1)
            return 1;
        
        if (playerData[playerid][pGang] != Player.Gang[gangid][@id])
            return 1;

        OpenGangLocker(playerid, gangid);
	}
	return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    if (gangLabel[playerid] != Text3D:INVALID_3DTEXT_ID) {
        DestroyDynamic3DTextLabel(gangLabel[playerid]);
    }
    return 1;
}

public GangLoad() {
	new
	    rows,
        colorStr[12];

	cache_get_row_count(rows);

	for (new i = 0; i < rows; i ++) if (i < MAX_GANGS) {
	    Player.Gang[i][@exists] = true;
	    cache_get_value_name_int(i, "gangid", Player.Gang[i][@id]);
	    cache_get_value_name(i, "gangName", Player.Gang[i][@name]);
	    cache_get_value_name(i, "leaderName", Player.Gang[i][@leader]);
	    cache_get_value_name(i, "officerName", Player.Gang[i][@officer]);
	    cache_get_value_name(i, "color", colorStr);
        Player.Gang[i][@gangcolor] = HexToInt(colorStr);
	    cache_get_value_name_float(i, "gangx", Player.Gang[i][@gangx]);
	    cache_get_value_name_float(i, "gangy", Player.Gang[i][@gangy]);
	    cache_get_value_name_float(i, "gangz", Player.Gang[i][@gangz]);
	    cache_get_value_name_float(i, "ganga", Player.Gang[i][@ganga]);
	    cache_get_value_name_int(i, "gangskin1", Player.Gang[i][@gangskin][0]);
	    cache_get_value_name_int(i, "gangskin2", Player.Gang[i][@gangskin][1]);
	    cache_get_value_name_int(i, "gangskin3", Player.Gang[i][@gangskin][2]);
	    cache_get_value_name_int(i, "money", Player.Gang[i][@money]);
	    cache_get_value_name_int(i, "redmoney", Player.Gang[i][@redmoney]);
	    GangRefresh(i);
	}
	printf("[SYSTEM][DB] %i Gang loaded.", rows);
	return true;
}

public OnGangCreated(playerid, gangid) {
	if (gangid == -1 || !Player.Gang[gangid][@exists]) return false;

	Player.Gang[gangid][@id] = cache_insert_id();
	GangSave(gangid);
    SetPlayerGang(playerid, gangid, LEADER_GANG);
	return true;
}

stock GangNearest(playerid) {
    for (new i = 0; i < MAX_GANGS; i ++) if (Player.Gang[i][@exists] && IsPlayerInRangeOfPoint(playerid, 1.0, Player.Gang[i][@gangx], Player.Gang[i][@gangy], Player.Gang[i][@gangz])) {
		if (GetPlayerGang(playerid) == Player.Gang[i][@id]) {
            return i;
        }
	}
	return -1;
}

stock GangDelete(gangid) {
	if (gangid != -1 && Player.Gang[gangid][@exists]) {
        if (IsValidDynamicPickup(Player.Gang[gangid][@gangobject]))
		    DestroyDynamicPickup(Player.Gang[gangid][@gangobject]);
		
		if (IsValidDynamic3DTextLabel(Player.Gang[gangid][@gangtext3d]))
		    DestroyDynamic3DTextLabel(Player.Gang[gangid][@gangtext3d]);
		
        foreach (new i : Player) {
            if (GetPlayerGang(i) == Player.Gang[gangid][@id]) {
                playerData[i][pGang] = -1;
                playerData[i][pGangRank] = 0;
            }
        }

        Query(get_handle(), "UPDATE "PLAYER_TABLE" SET `playerGang` = '-1', `playerGangRank` = '0' WHERE `playerGang` = '%i'", Player.Gang[gangid][@id]);
        Query(get_handle(), "DELETE FROM "GANG_TABLE" WHERE `gangid` = '%d'", Player.Gang[gangid][@id]);

		Player.Gang[gangid][@exists] = false;
		Player.Gang[gangid][@id] = 0;
	}
	return true;
}

stock GangCreate(playerid, color, const name[], Float:x, Float:y, Float:z, Float:a) {
	for (new i = 0; i < MAX_GANGS; i ++) if (!Player.Gang[i][@exists]) {
	    Player.Gang[i][@exists] = true;
        strcopy(Player.Gang[i][@leader], ReturnPlayerName(playerid));
        strcopy(Player.Gang[i][@officer], "NULL");
        strcopy(Player.Gang[i][@name], name);
	    Player.Gang[i][@gangx] = x;
	    Player.Gang[i][@gangy] = y;
	    Player.Gang[i][@gangz] = z;
	    Player.Gang[i][@ganga] = a;
        Player.Gang[i][@gangcolor] = color;
        Player.Gang[i][@gangskin][0] = INVALID_GANG_SKIN;
        Player.Gang[i][@gangskin][1] = INVALID_GANG_SKIN;
        Player.Gang[i][@gangskin][2] = INVALID_GANG_SKIN;
        Player.Gang[i][@money] = 500;
        Player.Gang[i][@redmoney] = 0;

	    mysql_tquery(get_handle(), "INSERT INTO "GANG_TABLE" (`gangid`) VALUES(0)", "OnGangCreated", "dd", playerid, i);
		GangRefresh(i);
		return i;
	}
	return -1;
}

stock GangSave(gangid) {
	new
	    query[512];
	mysql_format(get_handle(), query, sizeof query, 
    "UPDATE "GANG_TABLE" SET `gangx` = '%.4f', `gangy` = '%.4f', `gangz` = '%.4f', `ganga` = '%.4f' \
    , `leaderName` = '%s', `officerName` = '%s', `gangskin1` = '%d', `gangskin2` = '%d', `gangskin3` = '%d' \
    , `gangName` = '%s', `color` = '%x', `money` = '%d', `redmoney` = '%d' WHERE `gangid` = '%d'",
	    Player.Gang[gangid][@gangx],
	    Player.Gang[gangid][@gangy],
	    Player.Gang[gangid][@gangz],
	    Player.Gang[gangid][@ganga],
	    Player.Gang[gangid][@leader],
	    Player.Gang[gangid][@officer],
        Player.Gang[gangid][@gangskin][0],
        Player.Gang[gangid][@gangskin][1],
        Player.Gang[gangid][@gangskin][2],
	    Player.Gang[gangid][@name],
	    Player.Gang[gangid][@gangcolor],
        Player.Gang[gangid][@money],
	    Player.Gang[gangid][@redmoney],
	    Player.Gang[gangid][@id]
	);
	return mysql_tquery(get_handle(), query);
}

stock bool:IsPlayerLeaderGang(playerid)
    return playerData[playerid][pGangRank] >= LEADER_GANG;

stock bool:IsPlayerOfficerGang(playerid)
    return playerData[playerid][pGangRank] >= OFFICER_GANG;

stock GetGangName(gangid) {
    new str[128];
    strcopy(str, Player.Gang[gangid][@name]);
    return str;
}

stock bool:IsValidPlayerGang(gangid)
    return Player.Gang[gangid][@exists];

stock GetPlayerGang(playerid)
    return playerData[playerid][pGang];

stock IsPlayerInGang(playerid, gangid)
    return (GetPlayerGangIndex(playerid) == Player.Gang[gangid][@id]);

stock Attached3DTextGangToPlayer(playerid, gangid) {
    if (IsValidDynamic3DTextLabel(gangLabel[playerid])) {
        DestroyDynamic3DTextLabel(gangLabel[playerid]);
        gangLabel[playerid] = INVALID_3DTEXT_ID;
    }

    new str[128];
    format(str, sizeof(str), "%s", GetGangName(gangid));
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    gangLabel[playerid] = CreateDynamic3DTextLabel(str, Player.Gang[gangid][@gangcolor] , x, y, z + 0.1, 8.0, .attachedplayer = playerid);
    return 1;
}

stock SetPlayerGang(playerid, gangid, rank = 1) {
    if (GetPlayerLoggedIn(playerid)) {
        if (playerData[playerid][pFaction] != INVALID_FACTION) return SendErrorMessage(playerid, "{FFFFFF}ผู้เล่นคนนี้อยู่ในหน่วยงานอยู่แล้วไม่สามารถเข้าร่วมกลุ่มใดได้");
        playerData[playerid][pGang] = Player.Gang[gangid][@id];
        playerData[playerid][pGangRank] = rank;

        Query(get_handle(), "UPDATE "PLAYER_TABLE" SET `playerGang` = '%i', `playerGangRank` = '%i' WHERE `playerID` = '%i'"
        , playerData[playerid][pGang]
        , playerData[playerid][pGangRank]
        , playerData[playerid][pID]);

        Attached3DTextGangToPlayer(playerid, gangid);
        UpdatePlayerPos(playerid);
        SpawnPlayer(playerid);
    }
    return 1;
}

stock RenameGang(gangid, const name[]) {
    if (gangid < 0 || gangid >= MAX_GANGS || !Player.Gang[gangid][@exists])
        return -1;

    strcopy(Player.Gang[gangid][@name], name);
    GangSave(gangid);
    return gangid;
}

stock ChangeGangColour(gangid, colour) {
    if (gangid < 0 || gangid >= MAX_GANGS || !Player.Gang[gangid][@exists])
        return -1;
    
    Player.Gang[gangid][@gangcolor] = colour;

    // foreach (new i : Player) {
    //     if (playerData[i][pGang] == Player.Gang[gangid][@id]) {
    //         SetPlayerColor(i, colour);
    //     }
    // }

    GangSave(gangid);
    return gangid;
}

stock ChangeGangPos(gangid, Float:x, Float:y, Float:z, Float:a) {
    if (gangid < 0 || gangid >= MAX_GANGS || !Player.Gang[gangid][@exists])
        return -1;
    
    Player.Gang[gangid][@gangx] = x;
    Player.Gang[gangid][@gangy] = y;
    Player.Gang[gangid][@gangz] = z;
    Player.Gang[gangid][@ganga] = a;

    GangSave(gangid);
    SetTimerEx("DelayedGangRefresh", 500, false, "i", gangid);
    return gangid;
}

stock GetPlayerGangIndex(playerid) {
    new dbid = playerData[playerid][pGang];
    for (new i = 0; i < MAX_GANGS; i++) {
        if (Player.Gang[i][@exists] && Player.Gang[i][@id] == dbid)
            return i;
    }
    return -1;
}

stock RemovePlayerFromGang(playerid, gangid) {
    if (GetPlayerLoggedIn(playerid)) {
        if (playerData[playerid][pGang] == Player.Gang[gangid][@id]) {

            playerData[playerid][pGang] = INVALID_GANG;
            playerData[playerid][pGangRank] = 0;

            Query(get_handle(), "UPDATE "PLAYER_TABLE" SET `playerGang` = '%i', `playerGangRank` = '%i' WHERE `playerID` = '%i'"
            , playerData[playerid][pGang]
            , playerData[playerid][pGangRank]
            , playerData[playerid][pID]);

            UpdatePlayerPos(playerid);
            DestroyDynamic3DTextLabel(gangLabel[playerid]);
            SpawnPlayer(playerid);
        }
    }
    return 1;
}

stock GangRefresh(gangid) {
	if (gangid != -1 && Player.Gang[gangid][@exists]) {
		if (IsValidDynamicPickup(Player.Gang[gangid][@gangobject]))
		    DestroyDynamicPickup(Player.Gang[gangid][@gangobject]);
		
		if (IsValidDynamic3DTextLabel(Player.Gang[gangid][@gangtext3d]))
		    DestroyDynamic3DTextLabel(Player.Gang[gangid][@gangtext3d]);

		Player.Gang[gangid][@gangobject] = CreateDynamicPickup(MODEL_GANGS, 23, Player.Gang[gangid][@gangx], Player.Gang[gangid][@gangy], Player.Gang[gangid][@gangz]);
  		Player.Gang[gangid][@gangtext3d] = CreateDynamic3DTextLabel(TEXT3D_GANGS, -1, Player.Gang[gangid][@gangx], Player.Gang[gangid][@gangy], Player.Gang[gangid][@gangz], 5.0, INVALID_VEHICLE_ID, INVALID_PLAYER_ID, 0);
	}
	return true;
}

public DelayedGangRefresh(gangid) {
	if (gangid != -1 && Player.Gang[gangid][@exists]) {
		if (IsValidDynamicPickup(Player.Gang[gangid][@gangobject]))
		    DestroyDynamicPickup(Player.Gang[gangid][@gangobject]);
		
		if (IsValidDynamic3DTextLabel(Player.Gang[gangid][@gangtext3d]))
		    DestroyDynamic3DTextLabel(Player.Gang[gangid][@gangtext3d]);

        SetTimerEx("DelayedGangRefresh2", 500, false, "i", gangid);
	}
	return true;
}

public DelayedGangRefresh2(gangid) {
	if (gangid != -1 && Player.Gang[gangid][@exists]) {
		Player.Gang[gangid][@gangobject] = CreateDynamicPickup(MODEL_GANGS, 23, Player.Gang[gangid][@gangx], Player.Gang[gangid][@gangy], Player.Gang[gangid][@gangz]);
  		Player.Gang[gangid][@gangtext3d] = CreateDynamic3DTextLabel(TEXT3D_GANGS, -1, Player.Gang[gangid][@gangx], Player.Gang[gangid][@gangy], Player.Gang[gangid][@gangz], 5.0, INVALID_VEHICLE_ID, INVALID_PLAYER_ID, 0);
	}
	return true;
}

stock PanelCreateGang(playerid) {
	if (!IsPlayerAdminEx(playerid)) return true;

	inline const CreateGang(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused dialogid, pid, inputtext

		if (!response) @return true;

		switch (listitem) {
			case 0 : {
                inline inLineSetGangName(res, list, string:input[]) {
                    #pragma unused list
                    if (!res) @return PanelCreateGang(playerid);
                    new
                        Float:x,
                        Float:y,
                        Float:z,
                        Float:a,
                        gName[128],
                        gColor;

                    GetPlayerPos(playerid, x, y, z);
                    GetPlayerFacingAngle(playerid, a);

                    strcopy(gName, input);

                    inline inLineSetGangColor(res2, list2, string:input2[]) {
                        #pragma unused list2
                        if (!res2) @return PanelCreateGang(playerid);
                        new colorStr[12];
                        strmid(colorStr, input2, 0, sizeof(colorStr));
                        if (colorStr[0] == '0' && (colorStr[1] == 'x' || colorStr[1] == 'X'))
                            strmid(colorStr, colorStr, 2, sizeof(colorStr));
                        else if (colorStr[0] == '#')
                            strmid(colorStr, colorStr, 1, sizeof(colorStr));
                        
                        gColor = HexToInt(colorStr);

                        new id = GangCreate(playerid, gColor, gName, x, y, z, a);
                        if (id == -1) {
                            SendErrorMessage(playerid, "ความจุของ 'Gang' ในฐานข้อมูลเต็มแล้ว (ติดต่อผู้พัฒนา)");
                            @return 1;
                        }

                        SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ได้สร้าง Gang:{%06x}%s {FFFFFF}ขึ้นมาใหม่แล้ว ID: %d", ReturnPlayerName(playerid), gColor >>> 8, gName, id);
                    }
                    Dialog_ShowCallback(playerid, using inline inLineSetGangColor, DIALOG_STYLE_INPUT, "{FFFFFF}ตั้งสีแก็งค์", "{FFFFFF}ตั้วอย่าง: {FF0000}0xFF0000FF", "สร้าง", "ยกเลิก");
                }
                Dialog_ShowCallback(playerid, using inline inLineSetGangName, DIALOG_STYLE_INPUT, "{FFFFFF}ตั้งชื่อแก็งค์", "{FFFFFF}โปรดตั้งชื่อแก็งค์ได้เลย", "ไปต่อ", "ยกเลิก");
			}
			case 1 : {
				GangDeleteDialog(playerid);
			}
			case 2 : {
				GangIDList(playerid);
			}
            case 3: {
                inline inLineRenameID(res, list, string:input[]) {
                    #pragma unused list
                    if (!res) @return PanelCreateGang(playerid);
                    new gangid = strval(input);

                    if (gangid < 0 || gangid >= MAX_GANGS || !Player.Gang[gangid][@exists]) {
                        SendErrorMessage(playerid, "{FFFFFF}ไม่พบ Gang ID นั้น");
                        @return PanelCreateGang(playerid);
                    }

                    inline inLineRename(res2, list2, string:input2[]) {
                        #pragma unused list2
                        if (!res2) @return PanelCreateGang(playerid);

                        if (isnull(input2)) @return SendErrorMessage(playerid, "{FFFFFF}ห้ามมีค่าว่างเด็ดขาด");

                        RenameGang(gangid, input2);
                        SendAdminMessage(COLOR_ADMIN, "AdmLog: %s เปลี่ยนชื่อกลุ่ม %d เป็น %s เรียบร้อยแล้ว", ReturnPlayerName(playerid), gangid, input2);
                    }
                    new str[256];
                    format(str, sizeof(str), "{FFFFFF}ชื่อกลุ่มเดิม: {%06x}%s\n{CC0000}กรุณาระบุชื่อกลุ่มใหม่", Player.Gang[gangid][@gangcolor] >>> 8, Player.Gang[gangid][@name]);
                    Dialog_ShowCallback(playerid, using inline inLineRename, DIALOG_STYLE_INPUT, "{FFFFFF}เปลี่ยนชื่อกลุ่ม", str, "{FFFFFF}เปลี่ยน", "{FFFFFF}ยกเลิก");
                }
                Dialog_ShowCallback(playerid, using inline inLineRenameID, DIALOG_STYLE_INPUT, "{FFFFFF}ID กลุ่ม", "{FFFFFF}ระบุ ID ของกลุ่มนั้น", "{FFFFFF}ไปต่อ", "{FFFFFF}ยกเลิก");
            }
            case 4: {
                inline inLineChangeColorID(res, list, string:input[]) {
                    #pragma unused list
                    if (!res) @return PanelCreateGang(playerid);
                    new gangid = strval(input);

                    if (gangid < 0 || gangid >= MAX_GANGS || !Player.Gang[gangid][@exists]) {
                        SendErrorMessage(playerid, "{FFFFFF}ไม่พบ Gang ID นั้น");
                        @return PanelCreateGang(playerid);
                    }

                    inline inLineChange(res2, list2, string:input2[]) {
                        #pragma unused list2
                        if (!res2) @return PanelCreateGang(playerid);

                        if (isnull(input2)) @return SendErrorMessage(playerid, "{FFFFFF}ห้ามมีค่าว่างเด็ดขาด");

                        new colorStr[12];
                        strmid(colorStr, input2, 0, sizeof(colorStr));
                        if (colorStr[0] == '0' && (colorStr[1] == 'x' || colorStr[1] == 'X'))
                            strmid(colorStr, colorStr, 2, sizeof(colorStr));
                        else if (colorStr[0] == '#')
                            strmid(colorStr, colorStr, 1, sizeof(colorStr));
                        
                        new gColor = HexToInt(colorStr);

                        ChangeGangColour(gangid, gColor);
                        SendAdminMessage(COLOR_ADMIN, "AdmLog: %s เปลี่ยนสีกลุ่ม %s เป็น {%06x}IIIII "EC_ADMIN"เรียบร้อยแล้ว", ReturnPlayerName(playerid), Player.Gang[gangid][@name], gColor >>> 8);
                    }
                    new str[256];
                    format(str, sizeof(str), "{FFFFFF}ตั้วอย่าง: {FF0000}0xFF0000FF\n{FFFFFF}สีเดิม: {%06x}IIIII\n{FFFFFF} ของกลุ่ม: %s", Player.Gang[gangid][@gangcolor] >>> 8, Player.Gang[gangid][@name]);
                    Dialog_ShowCallback(playerid, using inline inLineChange, DIALOG_STYLE_INPUT, "{FFFFFF}เปลี่ยนสีกลุ่ม", str, "{FFFFFF}เปลี่ยน", "{FFFFFF}ยกเลิก");
                }
                Dialog_ShowCallback(playerid, using inline inLineChangeColorID, DIALOG_STYLE_INPUT, "{FFFFFF}ID กลุ่ม", "{FFFFFF}ระบุ ID ของกลุ่มนั้น", "{FFFFFF}ไปต่อ", "{FFFFFF}ยกเลิก");
            }
            case 5: {
                inline inLineChangePosID(res, list, string:input[]) {
                    #pragma unused list
                    if (!res) @return PanelCreateGang(playerid);
                    new gangid = strval(input);

                    if (gangid < 0 || gangid >= MAX_GANGS || !Player.Gang[gangid][@exists]) {
                        SendErrorMessage(playerid, "{FFFFFF}ไม่พบ Gang ID นั้น");
                        @return PanelCreateGang(playerid);
                    }

                    inline inLineChange(res2, list2, string:input2[]) {
                        #pragma unused list2, input2
                        if (!res2) @return PanelCreateGang(playerid);

                        new Float:x, Float:y, Float:z, Float:a;
                        GetPlayerPos(playerid, x, y, z), GetPlayerFacingAngle(playerid, a);
                        ChangeGangPos(gangid, x, y, z, a);
                        SendAdminMessage(COLOR_ADMIN, "AdmLog: %s เปลี่ยนตำแหน่งที่ตั้งกลุ่ม {%06x}%s "EC_ADMIN"เรียบร้อยแล้ว", ReturnPlayerName(playerid), Player.Gang[gangid][@gangcolor] >>> 8, Player.Gang[gangid][@name]);
                    }
                    new str[256];
                    format(str, sizeof(str), "{FFFFFF}คุณยืนยันที่จะเปลี่ยนตำแหน่งที่ตั้งกลุ่ม {%06x}%s {FFFFFF}หรือไม่", Player.Gang[gangid][@gangcolor] >>> 8, Player.Gang[gangid][@name]);
                    Dialog_ShowCallback(playerid, using inline inLineChange, DIALOG_STYLE_MSGBOX, "{FFFFFF}เปลี่ยนตำแหน่งที่ตั้งกลุ่ม", str, "{FFFFFF}เปลี่ยน", "{FFFFFF}ยกเลิก");
                }
                Dialog_ShowCallback(playerid, using inline inLineChangePosID, DIALOG_STYLE_INPUT, "{FFFFFF}ID กลุ่ม", "{FFFFFF}ระบุ ID ของกลุ่มนั้น", "{FFFFFF}ไปต่อ", "{FFFFFF}ยกเลิก");
            }
            case 6: {
                inline inLineChangeSkin(res, list, string:input[]) {
                    #pragma unused list
                    if (!res) @return PanelCreateGang(playerid);
                    new gangid = strval(input);

                    if (gangid < 0 || gangid >= MAX_GANGS || !Player.Gang[gangid][@exists]) {
                        SendErrorMessage(playerid, "{FFFFFF}ไม่พบ Gang ID นั้น");
                        @return PanelCreateGang(playerid);
                    }

                    new skinList[512] = "{FFFFFF}Slot\t{000000}-\t{FFFFFF}สถานะ\n";
                    for (new s = 0; s < 3; s++) {
                        new line[128];
                        if (Player.Gang[gangid][@gangskin][s] == INVALID_GANG_SKIN)
                            format(line, sizeof(line), "{FFFFFF}สกิน Slot %d\t{000000}-\t{AAAAAA}ว่าง\n", s + 1);
                        else
                            format(line, sizeof(line), "{FFFFFF}สกิน Slot %d\t{000000}-\t{00FF00}ID: %d\n", s + 1, Player.Gang[gangid][@gangskin][s]);
                        strcat(skinList, line, sizeof(skinList));
                    }

                    inline inLineSelectSlot(res2, list2, string:input2[]) {
                        #pragma unused input2
                        if (!res2) @return PanelCreateGang(playerid);
                        if (list2 < 0 || list2 >= 3) @return 1;

                        new slot = list2;

                        new info[256];
                        format(info, sizeof(info),
                            "{FFFFFF}Slot %d | สกินปัจจุบัน: {%06x}%s\n\n{FFFFFF}กรอก ID สกินที่ต้องการ\n{AAAAAA}(กรอก -1 เพื่อลบสกินออก)",
                            slot + 1,
                            Player.Gang[gangid][@gangskin][slot] == INVALID_GANG_SKIN ? 0xAAAAAAFF >>> 8 : 0x00FF00FF >>> 8,
                            Player.Gang[gangid][@gangskin][slot] == INVALID_GANG_SKIN ? "ว่าง" : ""
                        );

                        inline inLineInputSkin(res3, list3, string:input3[]) {
                            #pragma unused list3
                            if (!res3) @return PanelCreateGang(playerid);

                            if (isnull(input3)) {
                                SendErrorMessage(playerid, "{FFFFFF}กรุณากรอก ID สกิน");
                                @return PanelCreateGang(playerid);
                            }

                            new skinid = strval(input3);

                            if (skinid == INVALID_GANG_SKIN) {
                                Player.Gang[gangid][@gangskin][slot] = INVALID_GANG_SKIN;
                                GangSave(gangid);
                                SendWarningMessage(playerid, "{FFFFFF}ลบสกิน Slot %d ออกเรียบร้อยแล้ว", slot + 1);
                                @return PanelCreateGang(playerid);
                            }

                            if (skinid < 0 || skinid > 311) {
                                SendErrorMessage(playerid, "{FFFFFF}ID สกินต้องอยู่ระหว่าง 0 - 311 หรือ -1 เพื่อลบ");
                                @return PanelCreateGang(playerid);
                            }

                            for (new s = 0; s < 3; s++) {
                                if (s == slot) continue;
                                if (Player.Gang[gangid][@gangskin][s] == skinid) {
                                    SendErrorMessage(playerid, "{FFFFFF}สกิน ID นี้ถูกใช้ใน Slot %d แล้ว", s + 1);
                                    @return PanelCreateGang(playerid);
                                }
                            }

                            Player.Gang[gangid][@gangskin][slot] = skinid;
                            GangSave(gangid);

                            SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ตั้งค่าสกิน Slot %d เป็น ID {00FF00}%d "EC_ADMIN"ของกลุ่ม {%06x}%s "EC_ADMIN"เรียบร้อยแล้ว", ReturnPlayerName(playerid), slot + 1, skinid, Player.Gang[gangid][@gangcolor] >>> 8, GetGangName(gangid));
                        }
                        Dialog_ShowCallback(playerid, using inline inLineInputSkin, DIALOG_STYLE_INPUT, "{FFFFFF}กรอก ID สกิน", info, "{FFFFFF}ยืนยัน", "{FFFFFF}กลับ");
                    }

                    new title[128];
                    format(title, sizeof(title), "{FFFFFF}ตั้งค่าสกินกลุ่ม - {%06x}%s", Player.Gang[gangid][@gangcolor] >>> 8, GetGangName(gangid));
                    Dialog_ShowCallback(playerid, using inline inLineSelectSlot, DIALOG_STYLE_TABLIST_HEADERS, title, skinList, "{FFFFFF}เลือก Slot", "{FFFFFF}กลับ");
                }
                Dialog_ShowCallback(playerid, using inline inLineChangeSkin, DIALOG_STYLE_INPUT, "{FFFFFF}ID กลุ่ม", "{FFFFFF}ระบุ ID ของกลุ่มนั้น", "{FFFFFF}ไปต่อ", "{FFFFFF}ยกเลิก");
            }
		}
	}
	Dialog_ShowCallback(playerid, using inline CreateGang, DIALOG_STYLE_LIST, "{FFFFFF}AdminPanel (Gang)", "{FFFFFF}สร้าง\n{FF0000}ลบ\n{FFFFFF}ไอดีที่มีอยู่\n{FFFFFF}เปลี่ยนชื่อ\n{FFFFFF}เปลี่ยนสีกลุ่ม\n{FFFFFF}ย้ายตำแหน่งกลุ่ม\n{FFFFFF}ตั้งสกินกลุ่ม", "เลือก", "ยกเลิก");
	
	return true;
}

stock GangDeleteDialog(playerid) {
	inline const DeleteGang(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused dialogid, listitem, pid

		if (!response) @return true;

		new id = 0;
		
		if (sscanf(inputtext, "d", id)) {
			SendErrorMessage(playerid, "ต้องป้อนรูปแบบเลขเท่านั้น");
			@return PanelCreateGang(playerid);
		}
		
		if ((id < 0 || id >= MAX_GANGS) || !Player.Gang[id][@exists]) {
			SendErrorMessage(playerid, "ไม่มีไอดีที่เก็บรถนี้อยู่ในฐานข้อมูล");
			@return PanelCreateGang(playerid);
		}

		GangDelete(id);
		SendAdminMessage(COLOR_ADMIN, "AdmLog: %s ได้ลบ Gang: {%06x}%s "EC_ADMIN"ออกจากเซิร์ฟเวอร์แล้ว", ReturnPlayerName(playerid), Player.Gang[id][@gangcolor] >>> 8, GetGangName(id));
	}
	Dialog_ShowCallback(playerid, using inline DeleteGang, DIALOG_STYLE_INPUT, "{FFFFFF}DeleteGang", "ป้อน ID Gang นั้น", "ลบ", "ยกเลิก");
	return true;
}

stock GangIDList(playerid) {
	new count = 0;
	new string[1660], string2[1660] = "";

	for (new i = 0; i < MAX_GANGS; i ++) if (Player.Gang[i][@exists]) {
		format(string, sizeof(string), "{%06x}%s\t{FFFFFF}%d\t{FFFFFF}ID: %d\n", Player.Gang[i][@gangcolor] >>> 8, GetGangName(i), i, Player.Gang[i][@id] - 1);
		strcat(string2, string);

		count ++;
	}

	if (!count) return SendErrorMessage(playerid, "เซิร์ฟเวอร์ยังไม่ได้เพิ่ม 'Gang'");

	inline const Loaded(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused pid, dialogid, inputtext, listitem

		if (!response) @return true;

		if (response) @return true;
	}
	format(string, sizeof(string), "รายการ\tIndex\tID\n%s", string2);
	Dialog_ShowCallback(playerid, using inline Loaded, DIALOG_STYLE_TABLIST_HEADERS, "GangIDList", string, "ปิด", "");
	return true;
}

stock InvitePlayerToGang(playerid, targetid) {
    if (!IsPlayerConnected(targetid) || !GetPlayerLoggedIn(targetid)) return 1;
    
    inline inLineInvite(res, list, string:input[]) {
        #pragma unused list, input
        if (!res) @return 1;

        SetPlayerGang(targetid, playerData[playerid][pGang], 1);
        SendCongratMessage(targetid, "{FFFFFF}คุณได้ตอบรับคำเชิญเข้าร่วมกลุ่มแล้ว");
        SendCongratMessage(playerid, "{FFFFFF}%s ได้ตอบรับคำเชิญเข้าร่วมกลุ่มแล้ว", ReturnPlayerRPName(targetid));
    }
    Dialog_ShowCallback(targetid, using inline inLineInvite, DIALOG_STYLE_MSGBOX, "{FFFFFF}คำเชิญเข้าร่วมกลุ่ม", "{FFFFFF}ท่านสามารถตอบรับคำเชิญหรือไม่ก็ได้", "{FFFFFF}ตอบรับ", "{FFFFFF}ปิด");
    return 1;
}

YCMD:invite(playerid, string:params[], help) {
    if (!GetPlayerLoggedIn(playerid)) return SendErrorMessage(playerid, "{FFFFFF}กรุณาล็อกอินให้สำเร็จก่อนจึงจะใช้คำสั่งได้");
    if (GetPlayerGangIndex(playerid) == INVALID_GANG) return SendErrorMessage(playerid, "{FFFFFF}คุณต้องอยู่ในกลุ่มและเป็นต้องมีสิทธิ์ใช้งาน");
    if (IsPlayerLeaderGang(playerid) || IsPlayerOfficerGang(playerid)) {
        new targetid;
        if (sscanf(params, "u", targetid))
            return SendSyntaxMessage(playerid, "/invite [ไอดี/ชื่อ]");
        
        if (!IsPlayerConnected(targetid))
            return SendErrorMessage(playerid, "{FFFFFF}ผู้เล่นคนนี้ไม่ได้ออนไลน์");
        if (!GetPlayerLoggedIn(targetid))
            return SendErrorMessage(playerid, "{FFFFFF}ผู้เล่นคนนี้ยังไม่ได้เข้าสู่ระบบ");
        if (playerid == targetid)
            return SendErrorMessage(playerid, "{FFFFFF}ไม่สามารถเชิญตัวเองได้");
        if (playerData[targetid][pGang] != INVALID_GANG)
            return SendErrorMessage(playerid, "{FFFFFF}ผู้เล่นคนนี้มีกลุ่มอยู่แล้วไม่สามารถเชิญได้");

        InvitePlayerToGang(playerid, targetid);

    } else return SendErrorMessage(playerid, "{FFFFFF}คุณไม่มีสิทธ์ใช้คำสั่งขั้นสูงได้");
    return 1;
}

/// คำสั่งสำหรับเจ้าของกลุ่ม
YCMD:gangpanel(playerid, string:params[], help) {
    if (!GetPlayerLoggedIn(playerid)) return SendErrorMessage(playerid, "{FFFFFF}กรุณาล็อกอินให้สำเร็จก่อนจึงจะใช้คำสั่งได้");
    if (GetPlayerGangIndex(playerid) == INVALID_GANG) return SendErrorMessage(playerid, "{FFFFFF}คุณต้องอยู่ในกลุ่มและเป็นประธานกลุ่ม");
    if (!IsPlayerOfficerGang(playerid)) return SendErrorMessage(playerid, "{FFFFFF}คุณไม่มีสิทธ์ใช้คำสั่งประธานกลุ่มได้");

    inline inLineOne(res, list, string:input[]) {
        #pragma unused input
        if (!res) @return 1;
        switch (list) {
            case 0: {
                new query[512];
                mysql_format(get_handle(), query, sizeof(query), "SELECT `playerName`, `playerGangRank` FROM `"PLAYER_TABLE"` WHERE `playerGang` = '%d'", GetPlayerGang(playerid));
                inline inLineTwo() {

                    new 
                        memberList[1024] = "{FFFFFF}ชื่อ\t{000000}-\t{FFFFFF}สถานะ\n",
                        memberCount,
                        rows;
                    cache_get_row_count(rows);

                    for (new r = 0; r < rows; r++) {
                        new name[MAX_PLAYER_NAME + 1], line[128];
                        cache_get_value_name(r, "playerName", name);

                        new bool:isOnline = false;
                        foreach (new i : Player) {
                            new pname[MAX_PLAYER_NAME + 1];
                            GetPlayerName(i, pname, sizeof(pname));
                            if (!strcmp(pname, name, true)) { isOnline = true; break; }
                        }

                        format(line, sizeof(line), "{FFFFFF}%s\t{000000}-\t{%06x}[%s]\n",
                            name,
                            isOnline ? 0x00FF00FF >>> 8 : 0xAAAAAAFF >>> 8,
                            isOnline ? "ออนไลน์" : "ออฟไลน์"
                        );

                        strcat(memberList, line, sizeof(memberList));
                        memberCount++;
                    }

                    new title[128];
                    format(title, sizeof(title), "{FFFFFF}สมาชิกกลุ่ม (%d คน)", memberCount);

                    inline inLineMemberList(res2, list2, string:input2[]) {
                        #pragma unused list2, input2
                        if (!res2) @return Command_ReProcess(playerid, "/gangpanel", 0);
                        @return Command_ReProcess(playerid, "/gangpanel", 0);
                    }
                    Dialog_ShowCallback(playerid, using inline inLineMemberList, DIALOG_STYLE_TABLIST_HEADERS, title, memberList, "{FFFFFF}กลับ", "");
                }
                MySQL_TQueryInline(get_handle(), using inline inLineTwo, query);
            }
            case 1: {
                new query[512];
                mysql_format(get_handle(), query, sizeof(query), "SELECT `playerName`, `playerGangRank` FROM `"PLAYER_TABLE"` WHERE `playerGang` = '%d'", GetPlayerGang(playerid));
                inline inLineTwo() {
                    new
                        memberList[1024] = "{FFFFFF}ชื่อ\t{000000}-\t{FFFFFF}สถานะ\n",
                        memberCount,
                        rows;
                    cache_get_row_count(rows);

                    new memberNames[MAX_GANGS_MEMBERS][MAX_PLAYER_NAME + 1];

                    for (new r = 0; r < rows; r++) {
                        new name[MAX_PLAYER_NAME + 1], line[128];
                        cache_get_value_name(r, "playerName", name);

                        new bool:isOnline = false;
                        foreach (new i : Player) {
                            new pname[MAX_PLAYER_NAME + 1];
                            GetPlayerName(i, pname, sizeof(pname));
                            if (!strcmp(pname, name, true)) { isOnline = true; break; }
                        }

                        format(line, sizeof(line), "{FFFFFF}%s\t{000000}-\t{%06x}[%s]\n",
                            name,
                            isOnline ? 0x00FF00FF >>> 8 : 0xAAAAAAFF >>> 8,
                            isOnline ? "ออนไลน์" : "ออฟไลน์"
                        );
                        strcat(memberList, line, sizeof(memberList));

                        strmid(memberNames[memberCount], name, 0, MAX_PLAYER_NAME);
                        memberCount++;
                    }

                    new title[128];
                    format(title, sizeof(title), "{FFFFFF}สมาชิกกลุ่ม (%d คน)", memberCount);

                    inline inLineMemberList(res2, list2, string:input2[]) {
                        #pragma unused input2
                        if (!res2) @return Command_ReProcess(playerid, "/gangpanel", 0);
                        if (list2 < 0 || list2 >= memberCount) @return 1;

                        new selectedName[MAX_PLAYER_NAME + 1];
                        strmid(selectedName, memberNames[list2], 0, MAX_PLAYER_NAME);

                        new targetid = INVALID_PLAYER_ID;
                        foreach (new i : Player) {
                            new pname[MAX_PLAYER_NAME + 1];
                            GetPlayerName(i, pname, sizeof(pname));
                            if (!strcmp(pname, selectedName, true)) { targetid = i; break; }
                        }

                        if (targetid == playerid) {
                            SendErrorMessage(playerid, "{FFFFFF}ไม่สามารถปลดตัวเองได้");
                            @return Command_ReProcess(playerid, "/gangpanel", 0);
                        }

                        new gangid = GetPlayerGangIndex(playerid);

                        if (IsPlayerConnected(targetid)) {
                            RemovePlayerFromGang(targetid, gangid);
                            SendWarningMessage(targetid, "{FFFFFF}คุณถูกปลดออกจากกลุ่มแล้ว");
                        } else {
                            Query(get_handle(), "UPDATE `"PLAYER_TABLE"` SET `playerGang` = -1, `playerGangRank` = 0 \
                            WHERE `playerName` = '%s' AND `playerGang` = '%d'"
                            , selectedName
                            , Player.Gang[gangid][@id]);
                        }
                        SendCongratMessage(playerid, "{FFFFFF}คุณได้ทำการปลด {%06x}%s {FFFFFF}เรียบร้อยแล้ว", Player.Gang[gangid][@gangcolor] >>> 8, ReturnPlayerRPName(targetid));
                        @return Command_ReProcess(playerid, "/gangpanel", 0);
                    }
                    Dialog_ShowCallback(playerid, using inline inLineMemberList, DIALOG_STYLE_TABLIST_HEADERS, title, memberList, "{FFFFFF}ปลด", "{FFFFFF}กลับ");
                }
                MySQL_TQueryInline(get_handle(), using inline inLineTwo, query);
            }
            case 2: {
                if (!IsPlayerLeaderGang(playerid))
                    return SendErrorMessage(playerid, "{FFFFFF}คุณต้องเป็น Leader เท่านั้น");

                new query[512];
                mysql_format(get_handle(), query, sizeof(query), "SELECT `playerName`, `playerGangRank` FROM `"PLAYER_TABLE"` WHERE `playerGang` = '%d'", GetPlayerGang(playerid));
                inline inLineTwo() {
                    new
                        memberList[1024] = "{FFFFFF}ชื่อ\t{000000}-\t{FFFFFF}สถานะ\n",
                        memberCount,
                        rows;
                    cache_get_row_count(rows);

                    new memberNames[MAX_GANGS_MEMBERS][MAX_PLAYER_NAME + 1];

                    for (new r = 0; r < rows; r++) {
                        new name[MAX_PLAYER_NAME + 1], line[128];
                        cache_get_value_name(r, "playerName", name);

                        new bool:isOnline = false;
                        foreach (new i : Player) {
                            new pname[MAX_PLAYER_NAME + 1];
                            GetPlayerName(i, pname, sizeof(pname));
                            if (!strcmp(pname, name, true)) { isOnline = true; break; }
                        }

                        format(line, sizeof(line), "{FFFFFF}%s\t{000000}-\t{%06x}[%s]\n",
                            name,
                            isOnline ? 0x00FF00FF >>> 8 : 0xAAAAAAFF >>> 8,
                            isOnline ? "ออนไลน์" : "ออฟไลน์"
                        );
                        strcat(memberList, line, sizeof(memberList));

                        strmid(memberNames[memberCount], name, 0, MAX_PLAYER_NAME);
                        memberCount++;
                    }

                    new title[128];
                    format(title, sizeof(title), "{FFFFFF}สมาชิกกลุ่ม (%d คน)", memberCount);

                    inline inLineMemberList(res2, list2, string:input2[]) {
                        #pragma unused input2
                        if (!res2) @return Command_ReProcess(playerid, "/gangpanel", 0);
                        if (list2 < 0 || list2 >= memberCount) @return 1;

                        new selectedName[MAX_PLAYER_NAME + 1];
                        strmid(selectedName, memberNames[list2], 0, MAX_PLAYER_NAME);

                        new targetid = INVALID_PLAYER_ID;
                        foreach (new i : Player) {
                            new pname[MAX_PLAYER_NAME + 1];
                            GetPlayerName(i, pname, sizeof(pname));
                            if (!strcmp(pname, selectedName, true)) { targetid = i; break; }
                        }

                        if (targetid == playerid) {
                            SendErrorMessage(playerid, "{FFFFFF}ไม่สามารถแต่งตั้งให้ตัวเองเป็นเจ้าของกลุ่มได้");
                            @return Command_ReProcess(playerid, "/gangpanel", 0);
                        }

                        new gangid = GetPlayerGangIndex(playerid);

                        if (IsPlayerConnected(targetid)) {
                            SetPlayerGang(targetid, gangid, LEADER_GANG);
                            SetPlayerGang(playerid, gangid, OFFICER_GANG);
                            va_SendClientMessage(targetid, -1, "{%06x}[%s] {FFFFFF}คุณถูกตั้งเป็น Leader โดย {%06x}%s"
                            , Player.Gang[gangid][@gangcolor] >>> 8
                            , GetGangName(gangid)
                            , Player.Gang[gangid][@gangcolor] >>> 8
                            , ReturnPlayerRPName(playerid));
                        } else {
                            Query(get_handle(), "UPDATE `"PLAYER_TABLE"` SET `playerGangRank` = '5' WHERE `playerName` = '%s' AND `playerGang` = '%d'"
                            , selectedName
                            , Player.Gang[gangid][@id]);
                        }

                        SendCongratMessage(playerid, "{FFFFFF}คุณได้ทำการโอนกรรมสิทธิ์ให้ {%06x}%s {FFFFFF}เรียบร้อยแล้ว", Player.Gang[gangid][@gangcolor] >>> 8, ReturnPlayerRPName(targetid));
                        @return Command_ReProcess(playerid, "/gangpanel", 0);
                    }
                    Dialog_ShowCallback(playerid, using inline inLineMemberList, DIALOG_STYLE_TABLIST_HEADERS, title, memberList, "{FFFFFF}โอนทันที", "{FFFFFF}กลับ");
                }
                MySQL_TQueryInline(get_handle(), using inline inLineTwo, query);
            }
            case 3: {
                inline inLineInvite(res2, list2, string:input2[]) {
                    #pragma unused list2
                    if (!res2) @return Command_ReProcess(playerid, "/gangpanel", 0);
                    new str[128];
                    format(str, sizeof(str), "/invite %i", strval(input2));
                    Command_ReProcess(playerid, str, 0);
                }
                Dialog_ShowCallback(playerid, using inline inLineInvite, DIALOG_STYLE_INPUT, "{FFFFFF}ส่งคำเชิญเข้าร่วมกลุ่ม", "{FFFFFF}กรุณากรอก ID ผู้เล่นที่ต้องการเชิญ", "{FFFFFF}เชิญ", "{FFFFFF}กลับ");
            }
        }
    }
    new panelTitle[256];
    format(panelTitle, sizeof(panelTitle), "{FFFFFF}แผงจัดการกลุ่ม - {%06x}%s", Player.Gang[GetPlayerGangIndex(playerid)][@gangcolor] >>> 8, GetGangName(GetPlayerGangIndex(playerid)));
    Dialog_ShowCallback(playerid, using inline inLineOne, DIALOG_STYLE_LIST, panelTitle, "{FFFFFF}รายชื่อสมาชิก\n{FFFFFF}ปลดออกจากกลุ่ม\n{FF0000}โอนกรรมสิทธิ์\n{FFFFFF}ส่งคำเชิญ", "{FFFFFF}ไปต่อ", "{FFFFFF}ออก");
    return 1;
}

YCMD:agangpanel(playerid, const params[], help) {
    if (!IsPlayerAdminEx(playerid)) return 1;
    if (!GetPlayerLoggedIn(playerid)) return 1;
    PanelCreateGang(playerid);
    return 1;
}

YCMD:ganginfo(playerid, string:params[], help) {
    if (!GetPlayerLoggedIn(playerid))
        return SendErrorMessage(playerid, "{FFFFFF}กรุณาล็อกอินก่อน");

    new gangid = GetPlayerGangIndex(playerid);
    if (gangid == INVALID_GANG || gangid == -1)
        return SendErrorMessage(playerid, "{FFFFFF}คุณไม่ได้อยู่ในกลุ่มใด");

    new str[512];
    format(str, sizeof str,
        "{FFFFFF}ชื่อกลุ่ม : {%06x}%s\n\
        {FFFFFF}หัวหน้า : {FFFF00}%s\n\
        {FFFFFF}รอง : {FFFF00}%s\n\
        {FFFFFF}เงินกลุ่ม : {00FF00}$%d\n\
        {FFFFFF}เงินแดง : {FF0000}$%d\n\
        {FFFFFF}สกิน : %d / %d / %d",
        Player.Gang[gangid][@gangcolor] >>> 8, Player.Gang[gangid][@name],
        Player.Gang[gangid][@leader],
        Player.Gang[gangid][@officer],
        Player.Gang[gangid][@money],
        Player.Gang[gangid][@redmoney],
        Player.Gang[gangid][@gangskin][0],
        Player.Gang[gangid][@gangskin][1],
        Player.Gang[gangid][@gangskin][2]
    );

    new title[128];
    format(title, sizeof title, "{%06x}%s {FFFFFF}- ข้อมูลกลุ่ม",
        Player.Gang[gangid][@gangcolor] >>> 8, Player.Gang[gangid][@name]);

    inline Close(res, list, string:input[]) {
        #pragma unused res, list, input
    }
    Dialog_ShowCallback(playerid, using inline Close, DIALOG_STYLE_MSGBOX, title, str, "{FFFFFF}ปิด", "");
    return 1;
}

YCMD:setgang(playerid, string:params[], help) {
    if (!IsPlayerAdminEx(playerid)) return 1;
    if (!GetPlayerLoggedIn(playerid)) return 1;

    new targetid, gangid, rank;
    if (sscanf(params, "udd", targetid, gangid, rank))
        return SendSyntaxMessage(playerid, "/setgang [ไอดีผู้เล่น] [GangIndex] [Rank]");

    if (!IsPlayerConnected(targetid))
        return SendErrorMessage(playerid, "{FFFFFF}ผู้เล่นคนนี้ไม่ได้ออนไลน์");
    if (!GetPlayerLoggedIn(targetid))
        return SendErrorMessage(playerid, "{FFFFFF}ผู้เล่นคนนี้ยังไม่ล็อกอิน");
    if (gangid < 0 || gangid >= MAX_GANGS || !Player.Gang[gangid][@exists])
        return SendErrorMessage(playerid, "{FFFFFF}ไม่พบ GangIndex นั้น");
    if (rank < 1 || rank > LEADER_GANG)
        return SendErrorMessage(playerid, "{FFFFFF}Rank ต้องอยู่ระหว่าง 1 - %d", LEADER_GANG);

    SetPlayerGang(targetid, gangid, rank);
    SendAdminMessage(COLOR_ADMIN,
        "AdmLog: %s เซ็ต %s เข้ากลุ่ม {%06x}%s "EC_ADMIN"Rank: %d",
        ReturnPlayerName(playerid), ReturnPlayerName(targetid),
        Player.Gang[gangid][@gangcolor] >>> 8, Player.Gang[gangid][@name], rank);
    va_SendClientMessage(targetid, COLOR_GREEN, "แจ้งเตือน: {FFFFFF}คุณถูกเพิ่มเข้ากลุ่ม {%06x}%s {FFFFFF}Rank: %d",
        Player.Gang[gangid][@gangcolor] >>> 8, Player.Gang[gangid][@name], rank);
    return 1;
}

YCMD:removegang(playerid, string:params[], help) {
    if (!IsPlayerAdminEx(playerid)) return 1;
    if (!GetPlayerLoggedIn(playerid)) return 1;

    new targetid;
    if (sscanf(params, "u", targetid))
        return SendSyntaxMessage(playerid, "/removegang [ไอดีผู้เล่น]");

    if (!IsPlayerConnected(targetid))
        return SendErrorMessage(playerid, "{FFFFFF}ผู้เล่นคนนี้ไม่ได้ออนไลน์");
    if (!GetPlayerLoggedIn(targetid))
        return SendErrorMessage(playerid, "{FFFFFF}ผู้เล่นคนนี้ยังไม่ล็อกอิน");

    new gangid = GetPlayerGangIndex(targetid);
    if (gangid == -1)
        return SendErrorMessage(playerid, "{FFFFFF}ผู้เล่นคนนี้ไม่ได้อยู่ในกลุ่มใด");

    SendAdminMessage(COLOR_ADMIN,
        "AdmLog: %s นำ %s ออกจากกลุ่ม {%06x}%s",
        ReturnPlayerName(playerid), ReturnPlayerName(targetid),
        Player.Gang[gangid][@gangcolor] >>> 8, Player.Gang[gangid][@name]);

    RemovePlayerFromGang(targetid, gangid);
    SendWarningMessage(targetid, "{FFFFFF}คุณถูกแอดมินนำออกจากกลุ่ม");
    return 1;
}

YCMD:setofficer(playerid, string:params[], help) {
    if (!GetPlayerLoggedIn(playerid))
        return SendErrorMessage(playerid, "{FFFFFF}กรุณาล็อกอินก่อน");

    new gangid = GetPlayerGangIndex(playerid);
    new bool:isAdmin = IsPlayerAdminEx(playerid);

    if (!isAdmin) {
        if (gangid == -1)
            return SendErrorMessage(playerid, "{FFFFFF}คุณไม่ได้อยู่ในกลุ่ม");
        if (!IsPlayerLeaderGang(playerid))
            return SendErrorMessage(playerid, "{FFFFFF}คุณต้องเป็น Leader เท่านั้น");
    }

    new targetid;
    if (sscanf(params, "u", targetid))
        return SendSyntaxMessage(playerid, "/setofficer [ไอดีผู้เล่น]");

    if (!IsPlayerConnected(targetid))
        return SendErrorMessage(playerid, "{FFFFFF}ผู้เล่นคนนี้ไม่ได้ออนไลน์");
    if (!GetPlayerLoggedIn(targetid))
        return SendErrorMessage(playerid, "{FFFFFF}ผู้เล่นคนนี้ยังไม่ล็อกอิน");
    if (targetid == playerid)
        return SendErrorMessage(playerid, "{FFFFFF}ไม่สามารถตั้งตัวเองได้");

    new tGangId = GetPlayerGangIndex(targetid);
    if (!isAdmin && (tGangId == -1 || Player.Gang[tGangId][@id] != Player.Gang[gangid][@id]))
        return SendErrorMessage(playerid, "{FFFFFF}ผู้เล่นคนนี้ไม่ได้อยู่ในกลุ่มเดียวกัน");

    new targetGangId = isAdmin ? tGangId : gangid;
    if (targetGangId == -1)
        return SendErrorMessage(playerid, "{FFFFFF}ผู้เล่นคนนี้ไม่ได้อยู่ในกลุ่มใด");

    playerData[targetid][pGangRank] = OFFICER_GANG;
    Query(get_handle(),
        "UPDATE "PLAYER_TABLE" SET `playerGangRank` = '%d' WHERE `playerID` = '%i'",
        OFFICER_GANG, playerData[targetid][pID]);

    strcopy(Player.Gang[targetGangId][@officer], ReturnPlayerName(targetid));
    GangSave(targetGangId);

    va_SendClientMessage(targetid, COLOR_GREEN, "แจ้งเตือน: {FFFFFF}คุณได้รับตำแหน่ง {FFFF00}Officer {FFFFFF}ของกลุ่ม {%06x}%s",
        Player.Gang[targetGangId][@gangcolor] >>> 8, Player.Gang[targetGangId][@name]);
    SendCongratMessage(playerid, "{FFFFFF}ตั้ง %s เป็น Officer เรียบร้อยแล้ว", ReturnPlayerRPName(targetid));
    return 1;
}

YCMD:leavegang(playerid, string:params[], help) {
    if (!GetPlayerLoggedIn(playerid))
        return SendErrorMessage(playerid, "{FFFFFF}กรุณาล็อกอินก่อน");

    new gangid = GetPlayerGangIndex(playerid);
    if (gangid == -1)
        return SendErrorMessage(playerid, "{FFFFFF}คุณไม่ได้อยู่ในกลุ่มใด");

    if (playerData[playerid][pGangRank] >= LEADER_GANG)
        return SendErrorMessage(playerid, "{FFFFFF}Leader ต้องโอนกรรมสิทธิ์ก่อนจึงจะออกได้");

    inline Confirm(res, list, string:input[]) {
        #pragma unused list, input
        if (!res) @return 1;
        new gid = GetPlayerGangIndex(playerid);
        if (gid == -1) @return 1;
        RemovePlayerFromGang(playerid, gid);
        SendWarningMessage(playerid, "{FFFFFF}คุณออกจากกลุ่มเรียบร้อยแล้ว");
    }
    new str[256];
    format(str, sizeof str,
        "{DD0000}คุณยืนยันจะออกจากกลุ่ม {%06x}%s {DD0000}หรือไม่?",
        Player.Gang[gangid][@gangcolor] >>> 8, Player.Gang[gangid][@name]);
    Dialog_ShowCallback(playerid, using inline Confirm, DIALOG_STYLE_MSGBOX,
        "{FFFFFF}ออกจากกลุ่ม", str, "{FFFFFF}ยืนยัน", "{FFFFFF}ยกเลิก");
    return 1;
}

YCMD:gangmenu(playerid, string:params[], help) {
    if (!GetPlayerLoggedIn(playerid)) return 1;
    if (GetPlayerGang(playerid) == INVALID_GANG) return 1;

    inline GangMenu(res, list, string:in[]) {
        #pragma unused in
        if (!res) @return 1;

        switch (list) {
            case 0: {
                new query[512];
                mysql_format(get_handle(), query, sizeof(query), "SELECT `playerName`, `playerGangRank` FROM `"PLAYER_TABLE"` WHERE `playerGang` = '%d'", GetPlayerGang(playerid));
                inline inLineTwo() {

                    new 
                        memberList[1024] = "{FFFFFF}ชื่อ\t{000000}-\t{FFFFFF}สถานะ\n",
                        memberCount,
                        rows;
                    cache_get_row_count(rows);

                    for (new r = 0; r < rows; r++) {
                        new name[MAX_PLAYER_NAME + 1], line[128];
                        cache_get_value_name(r, "playerName", name);

                        new bool:isOnline = false;
                        foreach (new i : Player) {
                            new pname[MAX_PLAYER_NAME + 1];
                            GetPlayerName(i, pname, sizeof(pname));
                            if (!strcmp(pname, name, true)) { isOnline = true; break; }
                        }

                        format(line, sizeof(line), "{FFFFFF}%s\t{000000}-\t{%06x}[%s]\n",
                            name,
                            isOnline ? 0x00FF00FF >>> 8 : 0xAAAAAAFF >>> 8,
                            isOnline ? "ออนไลน์" : "ออฟไลน์"
                        );

                        strcat(memberList, line, sizeof(memberList));
                        memberCount++;
                    }

                    new title[128];
                    format(title, sizeof(title), "{FFFFFF}สมาชิกกลุ่ม (%d คน)", memberCount);

                    inline inLineMemberList(res2, list2, string:input2[]) {
                        #pragma unused list2, input2
                        if (!res2) @return Command_ReProcess(playerid, "/gangmenu", 0);
                        @return Command_ReProcess(playerid, "/gangmenu", 0);
                    }
                    Dialog_ShowCallback(playerid, using inline inLineMemberList, DIALOG_STYLE_TABLIST_HEADERS, title, memberList, "{FFFFFF}กลับ", "");
                }
                MySQL_TQueryInline(get_handle(), using inline inLineTwo, query);
            }
            case 1: {
                Command_ReProcess(playerid, "/leavegang", 0);
            }
        }
    }
    new title[256];
    format(title, sizeof(title), "{%06x}%s{FFFFFF} - สมาชิก", Player.Gang[GetPlayerGangIndex(playerid)][@gangcolor] >>> 8, GetGangName(GetPlayerGangIndex(playerid)));
    Dialog_ShowCallback(playerid, using inline GangMenu, DIALOG_STYLE_LIST, title, "{FFFFFF}รายชื่อสมาชิก\n{DD0000}ออกจากแก๊ง", "{FFFFFF}เลือก", "{FFFFFF}ออก");
    return 1;
}

#include "locker\impl"
