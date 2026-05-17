# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Importance

This project use tis620 encoding only, Please claude use tis-620 only to edit files in project

## Project Overview

**Cavalry City** — a SA-MP 0.3.7 roleplay gamemode written in **Pawn**, targeting a Thai-language community. Currently in **Pre-Beta** status.

## Build & Run

**Compile:**
```bash
pawno/pawncc.exe gamemodes/main.pwn --% -Dgamemodes -;+ -(+ -d3 -O1
```
Output: `gamemodes/main.amx`

**Run:**
```bash
samp-server.exe
```

## Configuration Files

| File | Purpose |
|---|---|
| `server.cfg` | SA-MP server settings (port 7777, plugins, gamemode) |
| `mysql.ini` | MySQL credentials (database: `sampsvr`) |
| `gamemodes/configs.inc` | All server constants: spawn pos, default money/skin/health, gender, key-press macros, message macros, `OO_TYPE` accessor pattern |
| `database/dump.sql` | Full MySQL schema and seed data |

## Architecture

### Two-Pass Include System ("Runner")

The most distinctive pattern: `main.pwn` includes `runner/runner.inc` **twice**. On the first pass, all `header.inc` files are loaded (forward declarations, enums, variables). On the second pass, all `impl.inc` files are loaded (implementations). This resolves Pawn's forward-reference limitations.

```pawn
#include "runner\runner"   // pass 1: headers
#include "runner\runner"   // pass 2: implementations
```

Controlled by preprocessor guards `RUNNER_@@@@_HEADER` and `RUNNER_@@@@_IMPL`.

### Module Structure (`gamemodes/runner/`)

- `core/` — Server init/exit hooks, build version textdraw
- `db/` — MySQL connection (`mysql_connect_file`), charset `tis620`, server name/mode setup
- `variables/` — Global state, `playerData` array (per-player enum with ~50+ fields)
- `cmd/` — Command processing, login enforcement, command logging
- `player/` — Player subsystems: login (bcrypt), admin, chat, damage, death, faction, gangs, hungry/thirsty, inventory (9 sub-modules), level/XP, fall detection
- `system/` — World systems: vehicle ownership/dealership, entrance/exit teleportation, ATM banking, GPS, car shop, gas pumps, gacha/loot boxes, wheelchair, HUD/UI
- `server/` — Anti-cheat (nex-ac), voice chat (sampvoice), map objects
- `fixed/` — Animation fixes
- `util/` — Color constants (29 colors), helper functions (money format, hex, SQL query wrapper)

### Key Libraries & Plugins

- **YSI4** — `y_hooks`, `y_commands` (YCMD), `y_inline`, `y_timers`, `y_dialog`, `y_master`
- **MySQL R41-4** — All queries are threaded (`mysql_tquery`), helper `Query()` wraps `va_format` + `mysql_tquery`
- **Pawn.RakNet** — Low-level packet/RPC interception
- **nex-ac** — Anti-cheat
- **sampvoice** — Proximity voice chat
- **bcrypt** — Password hashing (`$2b$12$` format)
- **Streamer** — Extended object/area/3D text streaming

### Code Patterns

- **Macro-based OOP:** `OO_TYPE` macro and `Player.` prefix create pseudo-OOP accessors for player data (e.g., `Player.id[playerid]`)
- **Hook-based callbacks:** All SA-MP callbacks use YSI hooks (`hook OnPlayerConnect`, etc.) with `DEFINE_HOOK_REPLACEMENT__(OnPlayer, OP_)` shorthand
- **Message macros** (defined in `configs.inc`): `SendErrorMessage`, `SendTipsMessage`, `SendPlayerAction`, `SendSyntaxMessage`, `SendWarningMessage`, `SendCongratMessage`, `SendGarageAction`
- **Key-press macros:** `PRESSED(%0)`, `RELEASED(%0)`, `PRESS_Y`, `PRESS_F`, `PRESS_TAB`, etc.
- **Dialogs:** Use YSI's inline callback pattern: `inline Response(...) { ... } Dialog_ShowCallback(playerid, using inline Response, ...)`
- **Iterators:** `Iterator: ServerVehicles`, `Iterator: PrivateVehicles`
- **Naming:** Hungarian notation (`g_SQL` for global MySQL handle), player arrays sized to `MAX_PLAYERS`

### Database (MySQL)

Database: `sampsvr`, charset: `tis620` (Thai). Key tables: `players`, `vehicles`, `dealership`, `dealership_stock`, `atms`, `entrances`, `gang`, `garage`, `gps_locations`, `pumps`, `dropitems`, `gachas`.

### Plugins (loaded in order)

`crashdetect`, `pawnraknet`, `sscanf`, `mysql`, `YSF`, `streamer`, `sampvoice`, `cec`, `samp_bcrypt`, `bscrashfix`
