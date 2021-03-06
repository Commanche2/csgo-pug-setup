#if defined _pugsetup_included
  #endinput
#endif
#define _pugsetup_included

// Different ways teams can be selected.
enum TeamType {
    TeamType_Manual,
    TeamType_Random,
    TeamType_Captains
};

// Different ways the map can be selected.
enum MapType {
    MapType_Current,
    MapType_Vote,
    MapType_Veto
};

// Permissions checking values.
enum Permissions {
    Permission_Captains,
    Permission_Leader
};

// Called when a setup menu is finished.
forward OnSetup(int client, TeamType teamType, MapType mapType, int playersPerTeam);

// Called when a player marks themselves as ready.
forward OnReady(int client);

// Called when a player marks themselves as unready.
forward OnUnready(int client);

// Called when the going-live process begins, before the lo3.
forward OnGoingLive();

// Called after the last restart when the game is completely live.
forward OnLive();

// Called when the match is over.
// If you plan on using the result of the demo file,
// I'd suggest adding a slight delay from when this is called
// to accomodate the time spent flushing the demo to disk.
forward OnMatchOver(bool hasDemo, const char demoFileName[]);

// Called when a client is not picked in a captain-selection game.
forward OnNotPicked(int client);

// Sets a game up with the given settings.
native void SetupGame(int gameTypeIndex, TeamType teamType, MapType mapType, int playersPerTeam, bool autolo3);

// Clears all game types.
native void ClearGameTypes();

// Returns the index of a game type, or -1 if it hasn't been registered.
native int FindGameType(const char name[]);

// Adds a game type to the game type list. These are fully reset every map.
// Returns the index of the game type.
native int AddGameType(const char name[], const char liveCfg[], const char mapList[], bool showInMenu=true, int teamSize=-1);

// Readies up a player.
native void ReadyPlayer(int client);

// Unreadies a player.
native void UnreadyPlayer(int client);

// Returns whether a client is ready.
// This is only valid when the game is setup AND not live.
native bool IsReady(int client);

// Returns if the game settings have been setup.
native bool IsSetup();

// Returns the team type being used.
// Only valid if IsSetup is true.
native TeamType GetTeamType();

// Returns the map type being used.
// Only valid if IsSetup is true.
native MapType GetMapType();

// Returns if there is currently a match setup.
native bool IsMatchLive();

// Sets the pug leader.
native void SetLeader(int client);

// Returns the pug leader, or -1 if not set.
native int GetLeader();

// Sets who is a captain.
// A captain number is either 1 or 2.
native void SetCaptain(int captainNumber, int client);

// Returns captain 1, or -1 if not set.
// A captain number is either 1 or 2.
native int GetCaptain(int captainNumber);

// Prints a plugin-formatted message to a client.
native void PugSetupMessage(int client, const char format[], any:...);

// Prints a plugin-formatted message to all clients.
native void PugSetupMessageToAll(const char format[], any:...);

// Returns the maximum number of players in the pug.
// Only valid if the game has already been setup.
native int GetPugMaxPlayers();

// Returns if a client was present when the game started.
// This doesn't include if the player disconnected and reconnected.
native bool PlayerAtStart(int client);

// Returns if the plugin has identified a player as having elevated permissions.
native bool IsPugAdmin(int client);

// Returns if a client satisfies a permission check.
native bool HasPermissions(int client, Permissions p);

// Sets random captains.
native void SetRandomCaptains();

public SharedPlugin:__pl_pugsetup = {
    name = "pugsetup",
    file = "pugsetup.smx",
#if defined REQUIRE_PLUGIN
    required = 1,
#else
    required = 0,
#endif
};

#if !defined REQUIRE_PLUGIN
public __pl_pugsetup_SetNTVOptional() {
    MarkNativeAsOptional("SetupGame");
    MarkNativeAsOptional("ClearGameTypes");
    MarkNativeAsOptional("AddGameType");
    MarkNativeAsOptional("FindGameType");
    MarkNativeAsOptional("ReadyPlayer");
    MarkNativeAsOptional("UnreadyPlayer");
    MarkNativeAsOptional("IsReady");
    MarkNativeAsOptional("IsSetup");
    MarkNativeAsOptional("GetTeamType");
    MarkNativeAsOptional("GetMapType");
    MarkNativeAsOptional("IsMatchLive");
    MarkNativeAsOptional("SetLeader");
    MarkNativeAsOptional("GetLeader");
    MarkNativeAsOptional("SetCaptain");
    MarkNativeAsOptional("GetCaptain");
    MarkNativeAsOptional("PugSetupMessage");
    MarkNativeAsOptional("PugSetupMessageToAll");
    MarkNativeAsOptional("GetPugMaxPlayers");
    MarkNativeAsOptional("PlayerAtStart");
    MarkNativeAsOptional("IsPugAdmin");
    MarkNativeAsOptional("HasPermissions");
    MarkNativeAsOptional("SetRandomCaptains");
}
#endif
