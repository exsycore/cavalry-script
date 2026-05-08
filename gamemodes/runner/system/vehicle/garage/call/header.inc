#if defined _inc_header
    #undef _inc_header
#endif

#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_inline>

#define MAX_GARAGE (50)
#define	LIST_VEHICLES (1)

#define GARAGE_PER_PAGE (8)
#define GARAGE_PAGE_PREV (4)

enum E_PLAYER_GARAGE {
    E_PLAYER_Garage_id,
    E_PLAYER_Garage_garageobject,
    E_PLAYER_Garage_garageobject2,
    E_PLAYER_Garage_garageicon,

    Float:E_PLAYER_Garage_garagex,
    Float:E_PLAYER_Garage_garagey,
    Float:E_PLAYER_Garage_garagez,

    Text3D:E_PLAYER_Garage_garagetext3d,
    bool:E_PLAYER_Garage_exists          
}

new PlayerGarage[MAX_GARAGE][E_PLAYER_GARAGE];

new MODEL_GARAGE = 19134;
new TEXT3D_GARAGE[128] = "{146923}Garage\n{FFFFFF}กดปุ่ม 'N' เพื่อเปิดการาจของท่าน";

new PlayerText: Garage_UI[MAX_PLAYERS][9];
new PlayerText: close_btn[MAX_PLAYERS][1];
new PlayerText: Garage_UI_Page[MAX_PLAYERS][4];
new PlayerText: Garage_Slot[MAX_PLAYERS][8];

new GarageUIPage[MAX_PLAYERS];
new GarageSlotIndex[MAX_PLAYERS][GARAGE_PER_PAGE];
new bool:IsOpenGarageUI[MAX_PLAYERS];

forward OnPlayerSpawnVehicle(playerid);
forward GarageLoad();
forward OnGarageCreated(garageid);
forward OnSelectVehicle(playerid, threadid);
forward OpenGarageUI(playerid, bool:enable);
forward RefreshUIGarage(playerid, threadid);

stock LoadGarageUI(playerid) {
    Garage_UI[playerid][0] = CreatePlayerTextDraw(playerid, 188.000, 124.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, Garage_UI[playerid][0], 269.000, 206.000);
    PlayerTextDrawAlignment(playerid, Garage_UI[playerid][0], 1);
    PlayerTextDrawColor(playerid, Garage_UI[playerid][0], 538976511);
    PlayerTextDrawSetShadow(playerid, Garage_UI[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, Garage_UI[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_UI[playerid][0], 255);
    PlayerTextDrawFont(playerid, Garage_UI[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, Garage_UI[playerid][0], 1);

    Garage_UI[playerid][1] = CreatePlayerTextDraw(playerid, 182.000, 119.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, Garage_UI[playerid][1], 277.000, 220.000);
    PlayerTextDrawAlignment(playerid, Garage_UI[playerid][1], 1);
    PlayerTextDrawColor(playerid, Garage_UI[playerid][1], 538976511);
    PlayerTextDrawSetShadow(playerid, Garage_UI[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, Garage_UI[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_UI[playerid][1], 255);
    PlayerTextDrawFont(playerid, Garage_UI[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, Garage_UI[playerid][1], 1);

    Garage_UI[playerid][2] = CreatePlayerTextDraw(playerid, 186.000, 119.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, Garage_UI[playerid][2], 265.000, 213.000);
    PlayerTextDrawAlignment(playerid, Garage_UI[playerid][2], 1);
    PlayerTextDrawColor(playerid, Garage_UI[playerid][2], 538976511);
    PlayerTextDrawSetShadow(playerid, Garage_UI[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, Garage_UI[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_UI[playerid][2], 255);
    PlayerTextDrawFont(playerid, Garage_UI[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, Garage_UI[playerid][2], 1);

    Garage_UI[playerid][3] = CreatePlayerTextDraw(playerid, 188.000, 134.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, Garage_UI[playerid][3], 265.000, 190.000);
    PlayerTextDrawAlignment(playerid, Garage_UI[playerid][3], 1);
    PlayerTextDrawColor(playerid, Garage_UI[playerid][3], 538976511);
    PlayerTextDrawSetShadow(playerid, Garage_UI[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, Garage_UI[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_UI[playerid][3], 255);
    PlayerTextDrawFont(playerid, Garage_UI[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, Garage_UI[playerid][3], 1);

    Garage_UI[playerid][4] = CreatePlayerTextDraw(playerid, 210.000, 127.000, "GARAGE");
    PlayerTextDrawLetterSize(playerid, Garage_UI[playerid][4], 0.170, 1.099);
    PlayerTextDrawTextSize(playerid, Garage_UI[playerid][4], 4.000, 3.000);
    PlayerTextDrawAlignment(playerid, Garage_UI[playerid][4], 1);
    PlayerTextDrawColor(playerid, Garage_UI[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, Garage_UI[playerid][4], 4);
    PlayerTextDrawSetOutline(playerid, Garage_UI[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_UI[playerid][4], 150);
    PlayerTextDrawFont(playerid, Garage_UI[playerid][4], 2);
    PlayerTextDrawSetProportional(playerid, Garage_UI[playerid][4], 1);

    Garage_UI[playerid][5] = CreatePlayerTextDraw(playerid, 189.000, 122.000, "HUD:radar_impound");
    PlayerTextDrawTextSize(playerid, Garage_UI[playerid][5], 17.000, 19.000);
    PlayerTextDrawAlignment(playerid, Garage_UI[playerid][5], 1);
    PlayerTextDrawColor(playerid, Garage_UI[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, Garage_UI[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, Garage_UI[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_UI[playerid][5], 255);
    PlayerTextDrawFont(playerid, Garage_UI[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, Garage_UI[playerid][5], 1);

    Garage_UI[playerid][6] = CreatePlayerTextDraw(playerid, 182.000, 142.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, Garage_UI[playerid][6], 277.000, 1.000);
    PlayerTextDrawAlignment(playerid, Garage_UI[playerid][6], 1);
    PlayerTextDrawColor(playerid, Garage_UI[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, Garage_UI[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, Garage_UI[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_UI[playerid][6], 255);
    PlayerTextDrawFont(playerid, Garage_UI[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, Garage_UI[playerid][6], 1);

    Garage_UI[playerid][7] = CreatePlayerTextDraw(playerid, 445.000, 125.000, "X");
    PlayerTextDrawLetterSize(playerid, Garage_UI[playerid][7], 0.170, 1.099);
    PlayerTextDrawTextSize(playerid, Garage_UI[playerid][7], 4.000, 3.000);
    PlayerTextDrawAlignment(playerid, Garage_UI[playerid][7], 1);
    PlayerTextDrawColor(playerid, Garage_UI[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, Garage_UI[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, Garage_UI[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_UI[playerid][7], 150);
    PlayerTextDrawFont(playerid, Garage_UI[playerid][7], 2);
    PlayerTextDrawSetProportional(playerid, Garage_UI[playerid][7], 1);

    Garage_UI[playerid][8] = CreatePlayerTextDraw(playerid, 188.000, 302.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, Garage_UI[playerid][8], 265.000, 23.000);
    PlayerTextDrawAlignment(playerid, Garage_UI[playerid][8], 1);
    PlayerTextDrawColor(playerid, Garage_UI[playerid][8], 1077952767);
    PlayerTextDrawSetShadow(playerid, Garage_UI[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, Garage_UI[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_UI[playerid][8], 255);
    PlayerTextDrawFont(playerid, Garage_UI[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, Garage_UI[playerid][8], 1);

    close_btn[playerid][0] = CreatePlayerTextDraw(playerid, 437.000, 118.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, close_btn[playerid][0], 21.000, 25.000);
    PlayerTextDrawAlignment(playerid, close_btn[playerid][0], 1);
    PlayerTextDrawColor(playerid, close_btn[playerid][0], -602653441);
    PlayerTextDrawSetShadow(playerid, close_btn[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, close_btn[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, close_btn[playerid][0], 255);
    PlayerTextDrawFont(playerid, close_btn[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, close_btn[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, close_btn[playerid][0], 1);

    Garage_Slot[playerid][0] = CreatePlayerTextDraw(playerid, 187.000, 150.000, "_");
    PlayerTextDrawTextSize(playerid, Garage_Slot[playerid][0], 66.000, 74.000);
    PlayerTextDrawAlignment(playerid, Garage_Slot[playerid][0], 1);
    PlayerTextDrawColor(playerid, Garage_Slot[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, Garage_Slot[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, Garage_Slot[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_Slot[playerid][0], 85);
    PlayerTextDrawFont(playerid, Garage_Slot[playerid][0], 5);
    PlayerTextDrawSetProportional(playerid, Garage_Slot[playerid][0], 0);
    PlayerTextDrawSetPreviewModel(playerid, Garage_Slot[playerid][0], 448);
    PlayerTextDrawSetPreviewRot(playerid, Garage_Slot[playerid][0], 0.000, 0.000, -37.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, Garage_Slot[playerid][0], 0, 0);
    PlayerTextDrawSetSelectable(playerid, Garage_Slot[playerid][0], 1);

    Garage_Slot[playerid][1] = CreatePlayerTextDraw(playerid, 254.000, 150.000, "_");
    PlayerTextDrawTextSize(playerid, Garage_Slot[playerid][1], 66.000, 74.000);
    PlayerTextDrawAlignment(playerid, Garage_Slot[playerid][1], 1);
    PlayerTextDrawColor(playerid, Garage_Slot[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, Garage_Slot[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, Garage_Slot[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_Slot[playerid][1], 85);
    PlayerTextDrawFont(playerid, Garage_Slot[playerid][1], 5);
    PlayerTextDrawSetProportional(playerid, Garage_Slot[playerid][1], 0);
    PlayerTextDrawSetPreviewModel(playerid, Garage_Slot[playerid][1], 448);
    PlayerTextDrawSetPreviewRot(playerid, Garage_Slot[playerid][1], 0.000, 0.000, -37.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, Garage_Slot[playerid][1], 0, 0);
    PlayerTextDrawSetSelectable(playerid, Garage_Slot[playerid][1], 1);

    Garage_Slot[playerid][2] = CreatePlayerTextDraw(playerid, 321.000, 150.000, "_");
    PlayerTextDrawTextSize(playerid, Garage_Slot[playerid][2], 66.000, 74.000);
    PlayerTextDrawAlignment(playerid, Garage_Slot[playerid][2], 1);
    PlayerTextDrawColor(playerid, Garage_Slot[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, Garage_Slot[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, Garage_Slot[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_Slot[playerid][2], 85);
    PlayerTextDrawFont(playerid, Garage_Slot[playerid][2], 5);
    PlayerTextDrawSetProportional(playerid, Garage_Slot[playerid][2], 0);
    PlayerTextDrawSetPreviewModel(playerid, Garage_Slot[playerid][2], 448);
    PlayerTextDrawSetPreviewRot(playerid, Garage_Slot[playerid][2], 0.000, 0.000, -37.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, Garage_Slot[playerid][2], 0, 0);
    PlayerTextDrawSetSelectable(playerid, Garage_Slot[playerid][2], 1);

    Garage_Slot[playerid][3] = CreatePlayerTextDraw(playerid, 388.000, 150.000, "_");
    PlayerTextDrawTextSize(playerid, Garage_Slot[playerid][3], 66.000, 74.000);
    PlayerTextDrawAlignment(playerid, Garage_Slot[playerid][3], 1);
    PlayerTextDrawColor(playerid, Garage_Slot[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, Garage_Slot[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, Garage_Slot[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_Slot[playerid][3], 85);
    PlayerTextDrawFont(playerid, Garage_Slot[playerid][3], 5);
    PlayerTextDrawSetProportional(playerid, Garage_Slot[playerid][3], 0);
    PlayerTextDrawSetPreviewModel(playerid, Garage_Slot[playerid][3], 448);
    PlayerTextDrawSetPreviewRot(playerid, Garage_Slot[playerid][3], 0.000, 0.000, -37.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, Garage_Slot[playerid][3], 0, 0);
    PlayerTextDrawSetSelectable(playerid, Garage_Slot[playerid][3], 1);

    Garage_Slot[playerid][4] = CreatePlayerTextDraw(playerid, 388.000, 225.000, "_");
    PlayerTextDrawTextSize(playerid, Garage_Slot[playerid][4], 66.000, 74.000);
    PlayerTextDrawAlignment(playerid, Garage_Slot[playerid][4], 1);
    PlayerTextDrawColor(playerid, Garage_Slot[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, Garage_Slot[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, Garage_Slot[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_Slot[playerid][4], 85);
    PlayerTextDrawFont(playerid, Garage_Slot[playerid][4], 5);
    PlayerTextDrawSetProportional(playerid, Garage_Slot[playerid][4], 0);
    PlayerTextDrawSetPreviewModel(playerid, Garage_Slot[playerid][4], 448);
    PlayerTextDrawSetPreviewRot(playerid, Garage_Slot[playerid][4], 0.000, 0.000, -37.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, Garage_Slot[playerid][4], 0, 0);
    PlayerTextDrawSetSelectable(playerid, Garage_Slot[playerid][4], 1);

    Garage_Slot[playerid][5] = CreatePlayerTextDraw(playerid, 321.000, 225.000, "_");
    PlayerTextDrawTextSize(playerid, Garage_Slot[playerid][5], 66.000, 74.000);
    PlayerTextDrawAlignment(playerid, Garage_Slot[playerid][5], 1);
    PlayerTextDrawColor(playerid, Garage_Slot[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, Garage_Slot[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, Garage_Slot[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_Slot[playerid][5], 85);
    PlayerTextDrawFont(playerid, Garage_Slot[playerid][5], 5);
    PlayerTextDrawSetProportional(playerid, Garage_Slot[playerid][5], 0);
    PlayerTextDrawSetPreviewModel(playerid, Garage_Slot[playerid][5], 448);
    PlayerTextDrawSetPreviewRot(playerid, Garage_Slot[playerid][5], 0.000, 0.000, -37.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, Garage_Slot[playerid][5], 0, 0);
    PlayerTextDrawSetSelectable(playerid, Garage_Slot[playerid][5], 1);

    Garage_Slot[playerid][6] = CreatePlayerTextDraw(playerid, 254.000, 225.000, "_");
    PlayerTextDrawTextSize(playerid, Garage_Slot[playerid][6], 66.000, 74.000);
    PlayerTextDrawAlignment(playerid, Garage_Slot[playerid][6], 1);
    PlayerTextDrawColor(playerid, Garage_Slot[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, Garage_Slot[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, Garage_Slot[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_Slot[playerid][6], 85);
    PlayerTextDrawFont(playerid, Garage_Slot[playerid][6], 5);
    PlayerTextDrawSetProportional(playerid, Garage_Slot[playerid][6], 0);
    PlayerTextDrawSetPreviewModel(playerid, Garage_Slot[playerid][6], 448);
    PlayerTextDrawSetPreviewRot(playerid, Garage_Slot[playerid][6], 0.000, 0.000, -37.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, Garage_Slot[playerid][6], 0, 0);
    PlayerTextDrawSetSelectable(playerid, Garage_Slot[playerid][6], 1);

    Garage_Slot[playerid][7] = CreatePlayerTextDraw(playerid, 187.000, 225.000, "_");
    PlayerTextDrawTextSize(playerid, Garage_Slot[playerid][7], 66.000, 74.000);
    PlayerTextDrawAlignment(playerid, Garage_Slot[playerid][7], 1);
    PlayerTextDrawColor(playerid, Garage_Slot[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, Garage_Slot[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, Garage_Slot[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_Slot[playerid][7], 85);
    PlayerTextDrawFont(playerid, Garage_Slot[playerid][7], 5);
    PlayerTextDrawSetProportional(playerid, Garage_Slot[playerid][7], 0);
    PlayerTextDrawSetPreviewModel(playerid, Garage_Slot[playerid][7], 448);
    PlayerTextDrawSetPreviewRot(playerid, Garage_Slot[playerid][7], 0.000, 0.000, -37.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, Garage_Slot[playerid][7], 0, 0);
    PlayerTextDrawSetSelectable(playerid, Garage_Slot[playerid][7], 1);

    Garage_UI_Page[playerid][0] = CreatePlayerTextDraw(playerid, 306.000, 308.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, Garage_UI_Page[playerid][0], 7.000, 9.000);
    PlayerTextDrawAlignment(playerid, Garage_UI_Page[playerid][0], 1);
    PlayerTextDrawColor(playerid, Garage_UI_Page[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, Garage_UI_Page[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, Garage_UI_Page[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_UI_Page[playerid][0], 255);
    PlayerTextDrawFont(playerid, Garage_UI_Page[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, Garage_UI_Page[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, Garage_UI_Page[playerid][0], 1);

    Garage_UI_Page[playerid][1] = CreatePlayerTextDraw(playerid, 313.000, 308.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, Garage_UI_Page[playerid][1], 7.000, 9.000);
    PlayerTextDrawAlignment(playerid, Garage_UI_Page[playerid][1], 1);
    PlayerTextDrawColor(playerid, Garage_UI_Page[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, Garage_UI_Page[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, Garage_UI_Page[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_UI_Page[playerid][1], 255);
    PlayerTextDrawFont(playerid, Garage_UI_Page[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, Garage_UI_Page[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, Garage_UI_Page[playerid][1], 1);

    Garage_UI_Page[playerid][2] = CreatePlayerTextDraw(playerid, 320.000, 308.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, Garage_UI_Page[playerid][2], 7.000, 9.000);
    PlayerTextDrawAlignment(playerid, Garage_UI_Page[playerid][2], 1);
    PlayerTextDrawColor(playerid, Garage_UI_Page[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, Garage_UI_Page[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, Garage_UI_Page[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_UI_Page[playerid][2], 255);
    PlayerTextDrawFont(playerid, Garage_UI_Page[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, Garage_UI_Page[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, Garage_UI_Page[playerid][2], 1);

    Garage_UI_Page[playerid][3] = CreatePlayerTextDraw(playerid, 327.000, 308.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, Garage_UI_Page[playerid][3], 7.000, 9.000);
    PlayerTextDrawAlignment(playerid, Garage_UI_Page[playerid][3], 1);
    PlayerTextDrawColor(playerid, Garage_UI_Page[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, Garage_UI_Page[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, Garage_UI_Page[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, Garage_UI_Page[playerid][3], 255);
    PlayerTextDrawFont(playerid, Garage_UI_Page[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, Garage_UI_Page[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, Garage_UI_Page[playerid][3], 1);
    return 1;
}

stock DestroyUIGarage(playerid) {
    for (new i = 0; i < 8; i ++) {
        PlayerTextDrawDestroy(playerid, Garage_Slot[playerid][i]);
    }
	for (new i = 0; i < 9; i ++) {
        PlayerTextDrawDestroy(playerid, Garage_UI[playerid][i]);
    }
	for (new i = 0; i < 1; i ++) {
        PlayerTextDrawDestroy(playerid, close_btn[playerid][i]);
    }
	for (new i = 0; i < 4; i ++) {
        PlayerTextDrawDestroy(playerid, Garage_UI_Page[playerid][i]);
    }
    return 1;
}