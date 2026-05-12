#pragma warning disable 213, 239, 200 /// disable boolean tags & disable const warning

#pragma dynamic 21418764    /// Stack/heap size fix

#define YSI_NO_AUTO_VA
#define YSI_NO_HEAP_MALLOC
#define YSI_NO_MODE_CACHE
#define YSI_NO_OPTIMISATION_MESSAGE

#include <a_samp>           /// SA-MP included MeenCore 1 1 1 1 1

#undef MAX_PLAYERS
#define MAX_PLAYERS (2)

#include <crashdetect>      /// crash info for server
#include <sscanf2>          /// scanf similar c language
#include <a_mysql>          /// mysql for store data of player to database
#include <YSF>
#include <streamer>         /// infinite object
#include <Pawn.RakNet>      /// client RPC
#include <sampvoice>        /// voice chat in SA:MP

#define DEBUG
#include <nex-ac_en.lang>
#include <nex-ac>           /// anticheater

#define OVERRIDE_NATIVE_GAMETEXT /// This line should be added before including GameText+!
#include <gametext_plus>

#include <cec>              /// colours tags for thai language
#include <samp_bcrypt>      /// hash system with bcrypt super security!

#include "configs"          /// the configuration of server

#include <progress2>        /// progress bar for client

#include <weapon-config>    /// check for damage

/// main logic
#include "runner\runner"
#include "runner\runner"

main() {}
