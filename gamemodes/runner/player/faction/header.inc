#if defined _inc_header
#undef _inc_header
#endif

#include <YSI_Data\y_iterate>

#define MAX_FACTION_MEMBERS (20)
#define MAX_FACTION_RANK    (6)
#define INVALID_FACTION     (-1)

enum E_FACTION_ID {
    FACTION_POLICE = 0,
    FACTION_MECHANIC,
    FACTION_MEDICAL,
    MAX_FACTIONS
}

enum E_FACTION_DATA {
    FactionName[128],
    FactionColor,
    FactionSkin[MAX_FACTION_RANK],
    bool:FactionActive
}
new FactionData[MAX_FACTIONS][E_FACTION_DATA];

enum E_PLAYER_FACTION {
    PlayerFaction,
    PlayerFactionRank,
    PlayerFactionDuty,
    bool:PlayerOnDuty
}
new PlayerFactionData[MAX_PLAYERS][E_PLAYER_FACTION];

new Iterator:FactionMembers[MAX_FACTIONS]<MAX_PLAYERS>;
new Iterator:FactionDuty[MAX_FACTIONS]<MAX_PLAYERS>;

new STREAMER_TAG_3D_TEXT_LABEL:factionLabel[MAX_PLAYERS];
