<div align="center">

```
 ??????? ?????? ???   ??? ?????? ???     ??????? ???   ???
???????????????????   ??????????????     ???????????? ????
???     ???????????   ??????????????     ???????? ???????
???     ???????????? ???????????????     ????????  ?????
???????????  ??? ??????? ???  ??????????????  ???   ???
 ??????????  ???  ?????  ???  ??????????????  ???   ???
```

<img src="https://img.shields.io/badge/SA%3AMP-0.3.7-c0392b?style=flat-square"/>
<img src="https://img.shields.io/badge/Language-Pawn-e67e22?style=flat-square"/>
<img src="https://img.shields.io/badge/Database-MySQL-3498db?style=flat-square"/>
<img src="https://img.shields.io/badge/Status-In%20Development-f39c12?style=flat-square"/>
<img src="https://img.shields.io/badge/License-Private-2c3e50?style=flat-square"/>

<br/>
<sub>A San Andreas Multiplayer roleplay gamemode — built from scratch.</sub>

</div>

---

## Overview

**Cavalry** is a full-featured SA:MP roleplay gamemode written in Pawn.  
Designed with a modular architecture using YSI4, MySQL, and Streamer as its core foundation.

---

## Dependencies

| Package | Version | Purpose |
|---|---|---|
| [YSI](https://github.com/pawn-lang/YSI-Includes) | latest | Hooks / Iterators / Inline callbacks |
| [mysql-plugin](https://github.com/pBlueG/SA-MP-MySQL) | R41-4 | Database layer |
| [sscanf2](https://github.com/Y-Less/sscanf) | latest | Command parameter parsing |
| [streamer](https://github.com/samp-incognito/samp-streamer-plugin) | 2.9.4 | Dynamic objects / areas / labels |
| .. etc ...

---

## Systems

### Vehicle
- [x] Dealership — buy & sell vehicles
- [ ] Spawn / Store / Recover
- [x] Lock & Unlock
- [x] Number plate customization
- [x] Mod & color persistence
- [x] Engine toggle

### Player
- [x] Registration & Login
- [ ] Character system
- [x] Inventory
- [x] Stats & Skills
- [x] Giftbox Player
- [x] Open Busk

### Jobs
- [ ] `<!-- add job name -->`
- [ ] `<!-- add job name -->`
- [ ] `<!-- add job name -->`

### Faction & Gang
- [ ] `<!-- add faction -->`
- [ ] `<!-- add gang -->`

### Property
- [ ] House ownership
- [ ] Business ownership

### Economy
- [ ] Bank system
- [ ] ATM
- [ ] `<!-- add economy system -->`

### Admin
- [x] Vehicle spot management (Spawn / Store / Recover)
- [ ] `<!-- add admin system -->`

---

## Installation

```bash
# Clone the repository
git clone https://github.com/exsycore/cavalry-script.git
cd cavalry-script

# Configure credentials
nano gamemodes/config.inc

# Compile & run
samp-server
```
---

## Team

| Username | Role |
|---|---|
| [exsycore](https://github.com/exsycore) | Lead Developer |
| [MeenCore](https://github.com/MeenCore) | Developer |

---

<div align="center">
<sub>CAVALRY — Private Repository — All rights reserved.</sub>
</div>
