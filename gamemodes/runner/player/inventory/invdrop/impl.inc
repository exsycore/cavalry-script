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

/*
 * @brief This dialog for ask the player how many to drop.
 * @param playerid Player ID in server.
 * @retval true Dropitems is finished.
 * @retval false Player is not logged in or player cancel to dropitem.
 */
stock DropitemsAskDialog(playerid) {
    if (!playerData[playerid][IsLoggedIn]) return 1;

    inline Response(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, listitem
        if (!response) @return 1;

        new counterItems;
        new itemID = GetPVarInt(playerid, "dItemID");
        new itemSlot = GetPVarInt(playerid, "dItemSlot");
        new Float:pX, Float:pY, Float:pZ;

        counterItems = strval(inputtext);

        if (counterItems <= 0) {
            SendErrorMessage(playerid, "{FFFFFF}จำนวนไม่ถูกต้อง");
            @return 1;
        }

        if (counterItems > playerData[playerid][pInventoryKolvo][itemSlot]) {
            SendErrorMessage(playerid, "{FFFFFF}จำนวนไอเทมของคุณไม่เพียงพอ");
            @return 1;
        }

        if (itemID < 0 || itemID >= MAX_ITEMS) {
            SendErrorMessage(playerid, "ไม่พบไอเทมดังกล่าวที่ตรงกับระบบ");
            @return 1;
        }

        GetPlayerPos(playerid, pX, pY, pZ);

        DropItemsCreate(ItemsInfo[itemID][ItemName], ItemsInfo[itemID][ItemModel], itemID, pX, pY, pZ, counterItems);
        CallLocalFunction("DeleteItem", "ddd", playerid, itemID, counterItems);
        PlayerPlaySound(playerid, 6801, 0.0, 0.0, 0.0);
        va_SendClientMessage(playerid, COLOR_RED, "[!] {FFFFFF}คุณทิ้งไอเทม %s จำนวน %i ลงพื้นเรียบร้อยแล้ว", ItemsInfo[itemID][ItemName], counterItems);
    }
    Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_INPUT
        , "{FFFFFF}ทิ้งไอเทม"
        , "{FFFFFF}กรุณากรอกจำนวนที่ต้องการทิ้งลงพื้น\n"EC_RED"* โปรดระวังภายในเซิร์ฟเวอร์จะมีการรีเซ็ทไอเทมที่ตกพื้น"
        , "{FFFFFF}ทิ้ง"
        , "{FFFFFF}ยกเลิก"
    );
    return 1;
}

/*
 * @brief For checking if player is near of dropitems or not.
 * @param playerid Player ID in server.
 * @retval true Player is nearest.
 * @retval false Player is not nearest.
 */
stock bool:IsNearestDropItems(playerid) {
    if (playerData[playerid][IsLoggedIn]) {
        for (new i = 0; i < MAX_DROP_ITEMS; i++) {
            if (dropData[i][dExists] &&
                IsPlayerInRangeOfPoint(playerid, 1.8,
                dropData[i][dPos][0],
                dropData[i][dPos][1],
                dropData[i][dPos][2])) {
                return true;
            }
        }
    }
    return false;
}

/*
 * @brief Get a dropitems ID if player nearest dropitems.
 * @param playerid Player ID in server.
 * @return DropItems ID
 * @retval -1 Player is not nearest dropitems.
 */
stock GetNearestDropItemsID(playerid) {
    if (playerData[playerid][IsLoggedIn]) {
        for (new i = 0; i < MAX_DROP_ITEMS; i++) {
            if (dropData[i][dExists] &&
                IsPlayerInRangeOfPoint(playerid, 1.8,
                dropData[i][dPos][0],
                dropData[i][dPos][1],
                dropData[i][dPos][2])) {
                return i;
            }
        }
    }
    return -1;
}

/*
 * @brief For refresh the object and 3dtext of DropItems.
 * @param did DropItems ID.
 * @return Boolean finish or not.
 */
stock bool:DropItemsRefresh(did) {
    if (did == -1 || !dropData[did][dExists])
        return false;

    if (IsValidDynamicObject(dropData[did][dObjectID]))
        DestroyDynamicObject(dropData[did][dObjectID]);

    if (IsValidDynamic3DTextLabel(dropData[did][d3DText]))
        DestroyDynamic3DTextLabel(dropData[did][d3DText]);
    
    dropData[did][dObjectID] = CreateDynamicObject(dropData[did][dModelID]
        , dropData[did][dPos][0]
        , dropData[did][dPos][1]
        , dropData[did][dPos][2]
        , 0.0
        , 0.0
        , 0.0
    );
    new string[128];
    string[0] = EOS;
    format(string, sizeof(string), DROP_3DTEXT, dropData[did][dName], dropData[did][dCount]);
    dropData[did][d3DText] = CreateDynamic3DTextLabel(string
        , -1
        , dropData[did][dPos][0]
        , dropData[did][dPos][1]
        , dropData[did][dPos][2]
        , 8.0
    );
    return true;
}

/*
 * @brief For create dropitems in server and insert into database.
 * @param name Item name.
 * @param modelid Model ID.
 * @param dPosX Position X.
 * @param dPosY Position Y.
 * @param dPosZ Position Z.
 * @param count Counter of items for drop.
 * @retval true Create is finished.
 * @retval false Create is not finish because MAX_DROP_ITEMS.
 */
stock DropItemsCreate(const name[], modelid, itemid, Float:dPosX, Float:dPosY, Float:dPosZ, count) {
    if (itemid < 0 || itemid >= MAX_ITEMS) {
        printf("%d Invalid item", itemid);
        return 1;
    }

    for (new i = 0; i < MAX_DROP_ITEMS; i++) {
        if (dropData[i][dExists]) continue;

        dropData[i][dExists] = true;

        new x_l = random(2);
        new y_l = random(2);
        new Float:x = dPosX + x_l;
        new Float:y = dPosY + y_l;
        new Float:z = dPosZ - 1.0;

        dropData[i][dModelID] = modelid;
        dropData[i][dItemID] = itemid;
        dropData[i][dPos][0] = x;
        dropData[i][dPos][1] = y;
        dropData[i][dPos][2] = z;
        dropData[i][dCount] = count;
        strcopy(dropData[i][dName], name, 128);

        mysql_tquery(get_handle(), "INSERT INTO "DROP_ITEMS_TABLE" (`id`) VALUES(0)", "OnDropItemsCreated", "d", i);
        DropItemsRefresh(i);
        return i;
    }
    return -1;
}

/*
 * @brief For save dropitems into database.
 * @param id Dropitems ID.
 * @return query into database.
 */
stock DropItemsSave(id) {
    new query[512];
    mysql_format(get_handle(), query, sizeof(query)
        , "UPDATE "DROP_ITEMS_TABLE" SET `item_name` = '%e', `model_id` = '%i', `item_id` = '%i', `pos_x` = '%.4f', `pos_y` = '%.4f', `pos_z` = '%.4f', `count` = '%d' WHERE `id` = '%d'"
        , dropData[id][dName]
        , dropData[id][dModelID]
        , dropData[id][dItemID]
        , dropData[id][dPos][0]
        , dropData[id][dPos][1]
        , dropData[id][dPos][2]
        , dropData[id][dCount]
        , dropData[id][dID]
    );
    return mysql_tquery(get_handle(), query);
}

/*
 * @brief For delete dropitems from database.
 * @param did Dropitems ID.
 * @retval true Delete finished.
 * @retval false The dropitems that ID is not exists.
 */
stock bool:DropItemsDelete(did) {
    if (dropData[did][dID] != -1 && dropData[did][dExists]) {
        new query[256];

        if (IsValidDynamicObject(dropData[did][dObjectID]))
            DestroyDynamicObject(dropData[did][dObjectID]);

        if (IsValidDynamic3DTextLabel(dropData[did][d3DText]))
            DestroyDynamic3DTextLabel(dropData[did][d3DText]);
        
        mysql_format(get_handle(), query, sizeof(query), "DELETE FROM "DROP_ITEMS_TABLE" WHERE `id` = '%d'", dropData[did][dID]);
        mysql_tquery(get_handle(), query);

        dropData[did][dExists] = false;
        return true;
    }
    return false;
}

stock Equipment(playerid) {
    if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return 1;

    new listitems[512] = "", str[512] = "";
    new nearIndex = -1;

    for (new i = 0; i != MAX_DROP_ITEMS; i ++) if (dropData[i][dExists] && IsPlayerInRangeOfPoint(playerid, 1.8, dropData[i][dPos][0], dropData[i][dPos][1], dropData[i][dPos][2])) {

        format(str, sizeof(str), "{FFFFFF}%s\t{FFFFFF}%d\n", dropData[i][dName], dropData[i][dCount]);
        strcat(listitems, str);
        nearIndex = i;
    }

    if (nearIndex == -1) // ไม่เจอของที่ตกอยู่
        return 1;
    
    if (GetInvSet(playerid) >= MAX_SLOT_ITEMS) {
        SendErrorMessage(playerid, "กระเป๋าของคุณเต็มแล้ว");
        return 1;
    }

    Drop_Index[playerid] = nearIndex; // เก็บ index ที่เจอไว้ก่อน

    inline Response(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, listitem, inputtext
        if (!response) @return 1;
        TakeInv2(playerid);
    }

    format(str, sizeof(str), "{FFFFFF}รายการ\t{FFFFFF}จำนวนที่มี\n%s", listitems);
    Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}เก็บของ", str, "เก็บ", "ปิด");
    return 1;
}

stock TakeInv2(playerid) {
    inline Response(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, listitem

        if (!response) @return Equipment(playerid);

        new index = Drop_Index[playerid];
        new integer;

        if (index == -1) @return 1;

        if (sscanf(inputtext, "d", integer)) {
            SendPlayerAction(playerid, "กรุณาระบุจำนวนที่ต้องการเก็บ");
            @return Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_INPUT, "{FFFFFF}เก็บของ", "{FFFFFF}ระบุจำนวน", "เก็บ", "กลับ");
        }

        if (integer > dropData[index][dCount])
            @return SendErrorMessage(playerid, "{FFFFFF}จำนวนที่คุณต้องการเก็บมากกว่าของที่ต้องการเก็บ (%d/%d)", integer, dropData[index][dCount]);

        if (dropData[index][dCount] <= 0)
            @return SendErrorMessage(playerid, "{FFFFFF}มีคนเก็บไปแล้ว");

        if (integer == dropData[index][dCount]) {
            AddItem(playerid, dropData[index][dItemID], integer);
            dropData[index][dCount] -= integer;
            DropItemsDelete(index);
        } else {
            AddItem(playerid, dropData[index][dItemID], integer);
            dropData[index][dCount] -= integer;
            DropItemsSave(index);
            DropItemsRefresh(index);
        }
    }
    Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_INPUT, "{FFFFFF}เก็บของ", "{FFFFFF}ระบุจำนวน", "เก็บ", "กลับ");
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

public OnDropItemsLoad() {
    new rows;
    if (!cache_get_row_count(rows)) {
        printf("[SYSTEM][DB] NULL DropItem loaded.");
    } else {
        for (new i = 0; i < rows; i++) if (i < MAX_DROP_ITEMS) {
            dropData[i][dExists] = true;

            cache_get_value_name_int(i, "id", dropData[i][dID]);
            cache_get_value_name_int(i, "model_id", dropData[i][dModelID]);
            cache_get_value_name_int(i, "item_id", dropData[i][dItemID]);
            cache_get_value_name(i, "item_name", dropData[i][dName], 64);
            cache_get_value_name_float(i, "pos_x", dropData[i][dPos][0]);
            cache_get_value_name_float(i, "pos_y", dropData[i][dPos][1]);
            cache_get_value_name_float(i, "pos_z", dropData[i][dPos][2]);
            cache_get_value_name_int(i, "count", dropData[i][dCount]);

            DropItemsRefresh(i);
        }
        printf("[SYSTEM][DB] %d DropItem loaded.", rows);
    }
    return 1;
}

public OnDropItemsCreated(id) {
    if (id == -1 || !dropData[id][dExists]) return 0;

    dropData[id][dID] = cache_insert_id();
    DropItemsSave(id);
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

hook OnGameModeInit() {
    mysql_tquery(get_handle(), "SELECT * FROM "DROP_ITEMS_TABLE"", "OnDropItemsLoad");
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if (PRESSED(KEY_CROUCH)) {
        Equipment(playerid);
    }
    return 1;
}
