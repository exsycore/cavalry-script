#if defined _inc_exit
#undef _inc_exit
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeExit() {
	mysql_close(g_SQL);
	return 1;
}
