#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid) {
	PlayerJobCountTD[playerid][0] = CreatePlayerTextDraw(playerid, 429.000000, 220.000000, "_");
	PlayerTextDrawFont(playerid, PlayerJobCountTD[playerid][0], 1);
	PlayerTextDrawLetterSize(playerid, PlayerJobCountTD[playerid][0], 0.600000, 1.300003);
	PlayerTextDrawTextSize(playerid, PlayerJobCountTD[playerid][0], 298.500000, 39.000000);
	PlayerTextDrawSetOutline(playerid, PlayerJobCountTD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, PlayerJobCountTD[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, PlayerJobCountTD[playerid][0], 2);
	PlayerTextDrawColor(playerid, PlayerJobCountTD[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, PlayerJobCountTD[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, PlayerJobCountTD[playerid][0], -13224193);
	PlayerTextDrawUseBox(playerid, PlayerJobCountTD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, PlayerJobCountTD[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerJobCountTD[playerid][0], 0);

	PlayerJobCountTD[playerid][1] = CreatePlayerTextDraw(playerid, 380.000000, 220.000000, "_");
	PlayerTextDrawFont(playerid, PlayerJobCountTD[playerid][1], 1);
	PlayerTextDrawLetterSize(playerid, PlayerJobCountTD[playerid][1], 0.600000, 1.300003);
	PlayerTextDrawTextSize(playerid, PlayerJobCountTD[playerid][1], 298.500000, 50.000000);
	PlayerTextDrawSetOutline(playerid, PlayerJobCountTD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, PlayerJobCountTD[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, PlayerJobCountTD[playerid][1], 2);
	PlayerTextDrawColor(playerid, PlayerJobCountTD[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, PlayerJobCountTD[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, PlayerJobCountTD[playerid][1], -13224193);
	PlayerTextDrawUseBox(playerid, PlayerJobCountTD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, PlayerJobCountTD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerJobCountTD[playerid][1], 0);

	PlayerJobCountTD[playerid][2] = CreatePlayerTextDraw(playerid, 429.000000, 221.000000, "100%");
	PlayerTextDrawFont(playerid, PlayerJobCountTD[playerid][2], 2);
	PlayerTextDrawLetterSize(playerid, PlayerJobCountTD[playerid][2], 0.220833, 1.100003);
	PlayerTextDrawTextSize(playerid, PlayerJobCountTD[playerid][2], 298.500000, 37.500000);
	PlayerTextDrawSetOutline(playerid, PlayerJobCountTD[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, PlayerJobCountTD[playerid][2], 0);
	PlayerTextDrawAlignment(playerid, PlayerJobCountTD[playerid][2], 2);
	PlayerTextDrawColor(playerid, PlayerJobCountTD[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, PlayerJobCountTD[playerid][2], 255);
	PlayerTextDrawBoxColor(playerid, PlayerJobCountTD[playerid][2], 370546431);
	PlayerTextDrawUseBox(playerid, PlayerJobCountTD[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, PlayerJobCountTD[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerJobCountTD[playerid][2], 0);

	PlayerProgressJob[playerid] = CreatePlayerProgressBar(playerid, 356.000000, 221.000000, 52.000000, 10.500000, -13224193, 100.000000, 0);
	SetPlayerProgressBarBgColour(playerid, PlayerProgressJob[playerid], 0xFFFFFFFF, true);
	return true;
}

forward OnProgressUpdate(playerid, progress, objectid);
forward OnProgressFinish(playerid, objectid);

stock StartProgress(playerid, duration, startvalue = 0, objectid) {
	if (ProgressState[playerid] == 1)
		return false;

	stop ProgressTimer[playerid];
	ProgressTimer[playerid] = repeat ProgressUpdate(playerid, objectid);

	ProgressLimit[playerid] = duration;
	ProgressCount[playerid] = startvalue;
	ProgressState[playerid] = 1;
	ProgressObject[playerid] = objectid;

	SetPlayerProgressBarMaxValue(playerid, PlayerProgressJob[playerid], ProgressLimit[playerid]);
	SetPlayerProgressBarValue(playerid, PlayerProgressJob[playerid], ProgressCount[playerid]);
	ShowPlayerProgressBar(playerid, PlayerProgressJob[playerid]);
	PlayerTextDrawShow(playerid, PlayerJobCountTD[playerid][0]);
	PlayerTextDrawShow(playerid, PlayerJobCountTD[playerid][1]);
	PlayerTextDrawShow(playerid, PlayerJobCountTD[playerid][2]);
	return true;
}

stock StopProgress(playerid) {
	if (ProgressState[playerid] == 0)
		return false;

	stop ProgressTimer[playerid];
	ProgressLimit[playerid] = 0;
	ProgressCount[playerid] = 0;
	ProgressState[playerid] = 0;
	ProgressObject[playerid] = INVALID_OBJECT_ID;

	HidePlayerProgressBar(playerid, PlayerProgressJob[playerid]);
	PlayerTextDrawHide(playerid, PlayerJobCountTD[playerid][0]);
	PlayerTextDrawHide(playerid, PlayerJobCountTD[playerid][1]);
	PlayerTextDrawHide(playerid, PlayerJobCountTD[playerid][2]);

	ClearAnimations(playerid);
	return true;
}

stock timer ProgressUpdate[100](playerid, objectid) {
	if (ProgressCount[playerid] >= ProgressLimit[playerid]) {
		StopProgress(playerid);
		CallLocalFunction("OnProgressFinish", "dd", playerid, objectid);
		return;
	}

	SetPlayerProgressBarMaxValue(playerid, PlayerProgressJob[playerid], ProgressLimit[playerid]);
	SetPlayerProgressBarValue(playerid, PlayerProgressJob[playerid], ProgressCount[playerid]);
	ShowPlayerProgressBar(playerid, PlayerProgressJob[playerid]);

	CallLocalFunction("OnProgressUpdate", "ddd", playerid, ProgressCount[playerid], objectid);
	
	static 
		string[32];

	ProgressCount[playerid]++;

	new Float:current_progress;
	if (ProgressLimit[playerid] == 0) { } else { current_progress = (ProgressCount[playerid]*100/ProgressLimit[playerid]); }

	format(string, sizeof string, "%.0f%c", current_progress, '%');
	PlayerTextDrawSetString(playerid, PlayerJobCountTD[playerid][2], string);
	return;
}