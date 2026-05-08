#if defined _inc_header
    #undef _inc_header
#endif

#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_inline>

#define MAX_PICKCAR (50)

enum E_PLAYER_PICKCAR {
    E_PLAYER_Pickcar_id,
    E_PLAYER_Pickcar_pickcarobject,
    E_PLAYER_Pickcar_pickcarobject2,
    E_PLAYER_Pickcar_pickcaricon,

    Float:E_PLAYER_Pickcar_pickcarx,
    Float:E_PLAYER_Pickcar_pickcary,
    Float:E_PLAYER_Pickcar_pickcarz,

    Text3D:E_PLAYER_Pickcar_pickcartext3d,
    bool:E_PLAYER_Pickcar_exists          
}

new PlayerPickcar[MAX_PICKCAR][E_PLAYER_PICKCAR];

new MODEL_PICKCAR = 19133;
new TEXT3D_PICKCAR[128] = "{d13d32}Pickup Car\n{FFFFFF}กดปุ่ม 'N' เพื่อเก็บรถของท่านของท่าน";

forward public PickcarLoad();
forward public OnPickcarCreated(pickcarid);

YCMD:garagepanel(playerid, const params[], help) {
	if (!IsPlayerAdminEx(playerid)) return true;
	
	inline const Loaded(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused dialogid, inputtext, pid

		if (!response) @return true;

		switch (listitem) {
			case 0 : {
				PanelCreateGarage(playerid);
				break;
			}
			case 1 : {
				PanelCreatePickcar(playerid);
				break;
			}
			case 2 : {
				PanelCreatePawn(playerid);
				break;
			}
		}
	}
	Dialog_ShowCallback(playerid, using inline Loaded, DIALOG_STYLE_LIST, "{FFFFFF}Garage", "การาจ\nที่เก็บรถ\nจุดพาวน์รถ", "เลือก", "ยกเลิก");
    return true;
}