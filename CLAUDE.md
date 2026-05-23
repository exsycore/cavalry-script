# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

**Cavalry** is a SA:MP 0.3.7 roleplay gamemode written in Pawn, using a modular architecture powered by YSI4, MySQL, and Streamer. The project is in active development (Pre-Beta). Language is Thai-oriented (Thai UI strings, Thai server language).

## Build & Compile

The Pawn compiler (`pawno/pawncc.exe`) compiles `gamemodes/main.pwn` into `gamemodes/main.amx`.

**VS Code build task** (default build task in `.vscode/tasks.json`):
```
pawno\pawncc.exe gamemodes\main.pwn --% -Dgamemodes -;+ -(+ -d3 -O1
```

Flags:
- `-d3` — full debug info
- `-O1` — optimization level 1
- `-;+` — require semicolons
- `-(` — require parentheses on function calls

**Run server:** Execute `samp-server.exe` (requires `server.cfg`, MySQL running, and all plugins in `plugins/`).

## Architecture

### Entry Point
`gamemodes/main.pwn` — includes all dependencies (YSI, MySQL, Streamer, sscanf, etc.), then includes `configs` and `runner/runner` twice (once for headers, once for implementations).

### Two-Pass Include System
`runner/runner.inc` uses a two-pass pattern via include guards:
1. **First pass** (`RUNNER_@@@@_HEADER`): includes all `header.inc` files — declares enums, forwards, stocks, variables
2. **Second pass** (`RUNNER_@@@@_IMPL`): includes all `impl.inc` files — implements callbacks, hooks, and function bodies

`main.pwn` includes `"runner\runner"` twice to trigger both passes. This is critical — do not remove the duplicate include.

### Module Structure (`gamemodes/runner/`)
Each module has `header.inc` (declarations) and `impl.inc` (implementations), sometimes with a `callape.inc` that combines both:

| Directory | Purpose |
|---|---|
| `core/` | YSI includes (y_hooks, y_timers, y_commands, y_master), base declarations |
| `db/` | MySQL connection (`g_SQL` handle), database initialization |
| `util/` | Utility functions and colour definitions |
| `variables/` | Global variable declarations |
| `fixed/` | SA-MP fixes (animation fixes) |
| `player/` | Player systems: login, inventory, admin, chat, damage, death, level, hungry, faction, gangs, falljump |
| `server/` | Server systems: anticheat (nex-ac), voicechat (sampvoice), map objects, progress bars |
| `cmd/` | Command definitions |
| `system/` | Game systems: vehicle, entrance, atm, gps, ui, busk, wheelchair, gachas, jobs (apple, fishing, mining) |

### Key Conventions

- **Player data** uses an OOP-like macro pattern: `Player.varName[playerid]` expands via `OO_TYPE` macros in `configs.inc`
- **Hook replacement**: `DEFINE_HOOK_REPLACEMENT__(OnPlayer, OP_)` shortens callback names (e.g., `OP_Connect` instead of `OnPlayerConnect`)
- **YSI4 hooks**: all callbacks are hooked via `hook` (y_hooks), not `public`/`OnPlayer*` directly
- **Commands**: defined with `YCMD:` prefix using y_commands
- **Message macros**: `SendErrorMessage`, `SendSyntaxMessage`, `SendTipsMessage`, etc. defined in `configs.inc` using `va_SendClientMessage` (variadic)
- **Key press macros**: `PRESSED(%0)`, `RELEASED(%0)`, `PRESS_*` constants in `configs.inc`
- **Database**: MySQL via `mysql-plugin` R41-4, connection handle is global `g_SQL`, database name `sampsvr`, credentials in `mysql.ini`

### Key Files
- `gamemodes/configs.inc` — server config, constants, macros, key press definitions
- `gamemodes/runner/db/header.inc` — MySQL handle (`g_SQL`) and `get_handle()` stock
- `gamemodes/runner/core/header.inc` — base YSI includes and `buildVersionName` PlayerText
- `database/dump.sql` — database schema

### Plugins (server.cfg)
crashdetect, pawnraknet, sscanf, mysql, YSF, streamer, sampvoice, cec, encore, samp_bcrypt, bscrashfix

### Filterscripts
`sampvoice` — voice chat filterscript (`filterscripts/sampvoice.pwn`)

## Important Notes

- `MAX_PLAYERS` is overridden to `2` in `main.pwn` (development/testing mode)
- `CGEN_MEMORY` is set to `50000` in `configs.inc` for y_hooks code generation
- `DISABLE_ANTICHEAT` is defined in `configs.inc` — anticheat is currently disabled for testing
- The `.gitignore` excludes `*.amx`, `*.txt`, and binaries — compiled output and logs are not tracked
