/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

CREATE DATABASE IF NOT EXISTS `sampsvr` /*!40100 DEFAULT CHARACTER SET tis620 COLLATE tis620_thai_ci */;
USE `sampsvr`;

CREATE TABLE IF NOT EXISTS `atms` (
  `atmid` int(11) NOT NULL AUTO_INCREMENT,
  `interior` int(11) NOT NULL DEFAULT 0,
  `world` int(11) NOT NULL DEFAULT 0,
  `x` float NOT NULL DEFAULT 0,
  `y` float NOT NULL DEFAULT 0,
  `z` float NOT NULL DEFAULT 0,
  `rx` float NOT NULL DEFAULT 0,
  `ry` float NOT NULL DEFAULT 0,
  `rz` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`atmid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci;

REPLACE INTO `atms` (`atmid`, `interior`, `world`, `x`, `y`, `z`, `rx`, `ry`, `rz`) VALUES
	(1, 0, 0, 2463.48, 1396.1, 10.5503, 0, 0, 87.2999);

CREATE TABLE IF NOT EXISTS `dealership` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(64) NOT NULL DEFAULT 'Dealership',
  `posx` float NOT NULL DEFAULT 0,
  `posy` float NOT NULL DEFAULT 0,
  `posz` float NOT NULL DEFAULT 0,
  `posa` float NOT NULL DEFAULT 0,
  `interior` int(11) NOT NULL DEFAULT 0,
  `world` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

REPLACE INTO `dealership` (`id`, `name`, `posx`, `posy`, `posz`, `posa`, `interior`, `world`) VALUES
	(1, 'Google', 2200.39, 1389.53, 10.8203, 217.917, 0, 0);

CREATE TABLE IF NOT EXISTS `dealership_stock` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `shopid` int(11) NOT NULL,
  `modelid` int(11) NOT NULL DEFAULT 400,
  `color1` int(11) NOT NULL DEFAULT 1,
  `color2` int(11) NOT NULL DEFAULT 1,
  `price` int(11) NOT NULL DEFAULT 100000,
  `stock` int(11) NOT NULL DEFAULT 0,
  `name` varchar(64) NOT NULL DEFAULT 'Vehicle',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

REPLACE INTO `dealership_stock` (`id`, `shopid`, `modelid`, `color1`, `color2`, `price`, `stock`, `name`) VALUES
	(1, 1, 456, 1, 1, 100000000, 5, 'Yankee');

CREATE TABLE IF NOT EXISTS `dropitems` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `model_id` int(11) NOT NULL DEFAULT 0,
  `item_id` int(11) NOT NULL DEFAULT 0,
  `item_name` varchar(128) NOT NULL DEFAULT 'NULL',
  `count` int(11) NOT NULL DEFAULT 0,
  `pos_x` float NOT NULL DEFAULT 0,
  `pos_y` float NOT NULL DEFAULT 0,
  `pos_z` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;


CREATE TABLE IF NOT EXISTS `entrances` (
  `entranceid` int(11) NOT NULL AUTO_INCREMENT,
  `warpid` int(11) DEFAULT -1,
  `interior` int(11) NOT NULL DEFAULT 0,
  `world` int(11) NOT NULL DEFAULT 0,
  `tointerior` int(11) NOT NULL DEFAULT 0,
  `toworld` int(11) NOT NULL DEFAULT 0,
  `x` float NOT NULL DEFAULT 0,
  `y` float NOT NULL DEFAULT 0,
  `z` float NOT NULL DEFAULT 0,
  `a` float NOT NULL DEFAULT 0,
  `tox` float NOT NULL DEFAULT 0,
  `toy` float NOT NULL DEFAULT 0,
  `toz` float NOT NULL DEFAULT 0,
  `toa` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`entranceid`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

REPLACE INTO `entrances` (`entranceid`, `warpid`, `interior`, `world`, `tointerior`, `toworld`, `x`, `y`, `z`, `a`, `tox`, `toy`, `toz`, `toa`) VALUES
	(1, -1, 0, 0, 0, 0, 2482.21, 1361.18, 10.8203, 358.583, 2501.83, 1363.59, 10.8203, 2.0294),
	(2, -1, 0, 0, 0, 0, 2502.18, 1360.67, 10.8278, 2.821, 2481.86, 1363.34, 10.8125, 7.921),
	(3, -1, 0, 0, 0, 0, 1671.47, 1814.47, 10.8203, 85.6893, 0, 0, 0, 0);

CREATE TABLE IF NOT EXISTS `gachas` (
  `gachaID` int(12) NOT NULL AUTO_INCREMENT,
  `gachaName` varchar(64) DEFAULT NULL,
  `gachaItemName1` varchar(64) DEFAULT NULL,
  `gachaItemName2` varchar(64) DEFAULT NULL,
  `gachaItemName3` varchar(64) DEFAULT NULL,
  `gachaItemName4` varchar(64) DEFAULT NULL,
  `gachaItemName5` varchar(64) DEFAULT NULL,
  `gachaItemName6` varchar(64) DEFAULT NULL,
  `gachaItemName7` varchar(64) DEFAULT NULL,
  `gachaItemName8` varchar(64) DEFAULT NULL,
  `gachaItemName9` varchar(64) DEFAULT NULL,
  `gachaItemName10` varchar(64) DEFAULT NULL,
  `gachaItemName11` varchar(64) DEFAULT NULL,
  `gachaItemName12` varchar(64) DEFAULT NULL,
  `gachaItemName13` varchar(64) DEFAULT NULL,
  `gachaItemName14` varchar(64) DEFAULT NULL,
  `gachaItemName15` varchar(64) DEFAULT NULL,
  `gachaItemModel1` int(12) NOT NULL DEFAULT 18700,
  `gachaItemModel2` int(12) NOT NULL DEFAULT 18700,
  `gachaItemModel3` int(12) NOT NULL DEFAULT 18700,
  `gachaItemModel4` int(12) NOT NULL DEFAULT 18700,
  `gachaItemModel5` int(12) NOT NULL DEFAULT 18700,
  `gachaItemModel6` int(12) NOT NULL DEFAULT 18700,
  `gachaItemModel7` int(12) NOT NULL DEFAULT 18700,
  `gachaItemModel8` int(12) NOT NULL DEFAULT 18700,
  `gachaItemModel9` int(12) NOT NULL DEFAULT 18700,
  `gachaItemModel10` int(12) NOT NULL DEFAULT 18700,
  `gachaItemModel11` int(12) NOT NULL DEFAULT 18700,
  `gachaItemModel12` int(12) NOT NULL DEFAULT 18700,
  `gachaItemModel13` int(12) NOT NULL DEFAULT 18700,
  `gachaItemModel14` int(12) NOT NULL DEFAULT 18700,
  `gachaItemModel15` int(12) NOT NULL DEFAULT 18700,
  `gachaItemAmount1` int(12) NOT NULL DEFAULT 0,
  `gachaItemAmount2` int(12) NOT NULL DEFAULT 0,
  `gachaItemAmount3` int(12) NOT NULL DEFAULT 0,
  `gachaItemAmount4` int(12) NOT NULL DEFAULT 0,
  `gachaItemAmount5` int(12) NOT NULL DEFAULT 0,
  `gachaItemAmount6` int(12) NOT NULL DEFAULT 0,
  `gachaItemAmount7` int(12) NOT NULL DEFAULT 0,
  `gachaItemAmount8` int(12) NOT NULL DEFAULT 0,
  `gachaItemAmount9` int(12) NOT NULL DEFAULT 0,
  `gachaItemAmount10` int(12) NOT NULL DEFAULT 0,
  `gachaItemAmount11` int(12) NOT NULL DEFAULT 0,
  `gachaItemAmount12` int(12) NOT NULL DEFAULT 0,
  `gachaItemAmount13` int(12) NOT NULL DEFAULT 0,
  `gachaItemAmount14` int(12) NOT NULL DEFAULT 0,
  `gachaItemAmount15` int(12) NOT NULL DEFAULT 0,
  PRIMARY KEY (`gachaID`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

REPLACE INTO `gachas` (`gachaID`, `gachaName`, `gachaItemName1`, `gachaItemName2`, `gachaItemName3`, `gachaItemName4`, `gachaItemName5`, `gachaItemName6`, `gachaItemName7`, `gachaItemName8`, `gachaItemName9`, `gachaItemName10`, `gachaItemName11`, `gachaItemName12`, `gachaItemName13`, `gachaItemName14`, `gachaItemName15`, `gachaItemModel1`, `gachaItemModel2`, `gachaItemModel3`, `gachaItemModel4`, `gachaItemModel5`, `gachaItemModel6`, `gachaItemModel7`, `gachaItemModel8`, `gachaItemModel9`, `gachaItemModel10`, `gachaItemModel11`, `gachaItemModel12`, `gachaItemModel13`, `gachaItemModel14`, `gachaItemModel15`, `gachaItemAmount1`, `gachaItemAmount2`, `gachaItemAmount3`, `gachaItemAmount4`, `gachaItemAmount5`, `gachaItemAmount6`, `gachaItemAmount7`, `gachaItemAmount8`, `gachaItemAmount9`, `gachaItemAmount10`, `gachaItemAmount11`, `gachaItemAmount12`, `gachaItemAmount13`, `gachaItemAmount14`, `gachaItemAmount15`) VALUES
	(1, 'Newbie Gacha', 'Bobcat', 'Faggio', 'Bobcat', 'Cash', 'Faggio', 'Bobcat', 'Faggio', 'Bobcat', 'Faggio', 'Bobcat', 'Faggio', 'Bobcat', 'Faggio', 'Bobcat', 'Faggio', 422, 462, 422, 1212, 462, 422, 462, 422, 462, 422, 462, 422, 462, 422, 462, 1, 1, 1, 1000, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1),
	(2, 'Gacha Wave 1', 'Tomato', 'Cash', 'Wood Log', 'Cemen Pack', 'Fishing Line', 'Blue Flat Fish', 'Yellow Flat Fish', 'Cheetah', 'Fishing Rod', 'Cash', 'Bread', 'Sprunk Drink', 'Cash', 'Soap', 'Raw Fish', 19577, 1212, 19793, 2060, 19896, 1604, 1599, 415, 18632, 1212, 19579, 1546, 1212, 19874, 19630, 3, 1000, 2, 3, 2, 3, 3, 1, 1, 2000, 3, 2, 3000, 2, 2);

CREATE TABLE IF NOT EXISTS `gang` (
  `gangid` int(11) NOT NULL AUTO_INCREMENT,
  `gangName` varchar(128) NOT NULL DEFAULT 'NULL',
  `leaderName` varchar(128) NOT NULL DEFAULT 'NULL',
  `officerName` varchar(128) NOT NULL DEFAULT 'NULL',
  `color` varchar(10) NOT NULL DEFAULT 'ffffffff',
  `gangx` float NOT NULL DEFAULT 0,
  `gangy` float NOT NULL DEFAULT 0,
  `gangz` float NOT NULL DEFAULT -9999,
  `ganga` float NOT NULL DEFAULT 0,
  `gangskin1` int(11) NOT NULL DEFAULT -1,
  `gangskin2` int(11) NOT NULL DEFAULT -1,
  `gangskin3` int(11) NOT NULL DEFAULT -1,
  `money` int(11) NOT NULL DEFAULT 0,
  `redmoney` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`gangid`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

REPLACE INTO `gang` (`gangid`, `gangName`, `leaderName`, `officerName`, `color`, `gangx`, `gangy`, `gangz`, `ganga`, `gangskin1`, `gangskin2`, `gangskin3`, `money`, `redmoney`) VALUES
	(4, 'GAME MASTER', 'Easy_Core', 'NULL', 'f73e24ff', 2484.78, 1399.62, 10.8203, 310.034, -1, -1, -1, 500, 0);

CREATE TABLE IF NOT EXISTS `garage` (
  `garageid` int(11) NOT NULL AUTO_INCREMENT,
  `garagex` float NOT NULL DEFAULT 0,
  `garagey` float NOT NULL DEFAULT 0,
  `garagez` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`garageid`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

REPLACE INTO `garage` (`garageid`, `garagex`, `garagey`, `garagez`) VALUES
	(1, 2488.27, 1408.31, 10.8203);

CREATE TABLE IF NOT EXISTS `gps_locations` (
  `gpsid` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(64) NOT NULL DEFAULT '',
  `category` tinyint(4) NOT NULL DEFAULT 0,
  `x` float NOT NULL DEFAULT 0,
  `y` float NOT NULL DEFAULT 0,
  `z` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`gpsid`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

REPLACE INTO `gps_locations` (`gpsid`, `name`, `category`, `x`, `y`, `z`) VALUES
	(1, 'จุดเริ่มต้น', 0, 2487.48, 1386.15, 10.8203),
	(2, 'Test 1', 0, 1783.89, -1283.36, 13.4688);

CREATE TABLE IF NOT EXISTS `pawn` (
  `pawnid` int(11) NOT NULL AUTO_INCREMENT,
  `pawnx` float NOT NULL DEFAULT 0,
  `pawny` float NOT NULL DEFAULT 0,
  `pawnz` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`pawnid`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

REPLACE INTO `pawn` (`pawnid`, `pawnx`, `pawny`, `pawnz`) VALUES
	(1, 2504.05, 1413.4, 10.8203);

CREATE TABLE IF NOT EXISTS `pickcar` (
  `pickcarid` int(11) NOT NULL AUTO_INCREMENT,
  `pickcarx` float NOT NULL DEFAULT 0,
  `pickcary` float NOT NULL DEFAULT 0,
  `pickcarz` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`pickcarid`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

REPLACE INTO `pickcar` (`pickcarid`, `pickcarx`, `pickcary`, `pickcarz`) VALUES
	(1, 2488.24, 1419.01, 10.8203);

CREATE TABLE IF NOT EXISTS `players` (
  `playerID` int(11) NOT NULL AUTO_INCREMENT,
  `playerName` varchar(24) NOT NULL,
  `playerPassword` varchar(129) NOT NULL,
  `playerRegDate` varchar(90) NOT NULL,
  `playerPassport` int(11) NOT NULL DEFAULT 0,
  `playerGender` int(11) NOT NULL DEFAULT 0,
  `playerAdmin` int(11) NOT NULL DEFAULT 0,
  `playerExp` int(11) NOT NULL DEFAULT 0,
  `playerLevel` int(11) NOT NULL,
  `playerMoney` int(11) NOT NULL DEFAULT 0,
  `playerBank` int(11) NOT NULL DEFAULT 0,
  `playerRedMoney` int(11) NOT NULL DEFAULT 0,
  `playerHungry` float NOT NULL DEFAULT 0,
  `playerThirsty` float NOT NULL DEFAULT 0,
  `playerInDeath` int(11) NOT NULL DEFAULT 0,
  `playerInjuredTime` int(11) NOT NULL DEFAULT 0,
  `playerHealth` float NOT NULL,
  `playerArmour` float NOT NULL,
  `Skin` int(11) NOT NULL,
  `playerFaction` int(11) NOT NULL DEFAULT -1,
  `playerRank` int(11) NOT NULL DEFAULT 0,
  `playerGang` int(11) NOT NULL DEFAULT -1,
  `playerGangRank` int(11) NOT NULL DEFAULT 0,
  `playerGiftbox` int(11) NOT NULL DEFAULT 0,
  `playerGiftbox2` int(11) NOT NULL DEFAULT 0,
  `pPosX` float NOT NULL,
  `pPosY` float NOT NULL,
  `pPosZ` float NOT NULL,
  `pPosA` float NOT NULL,
  `pInvColors` int(11) NOT NULL DEFAULT 0,
  `InvPos_X` int(11) NOT NULL DEFAULT 0,
  `InvPos_Y` int(11) NOT NULL DEFAULT 0,
  `InvSize_X` int(11) NOT NULL DEFAULT 0,
  `InvSize_Y` int(11) NOT NULL DEFAULT 0,
  `Item` text DEFAULT NULL,
  `ItemKolvo` text DEFAULT NULL,
  `Aks` text DEFAULT NULL,
  `pSlotItem0` int(11) NOT NULL DEFAULT 0,
  `pSlotItem1` int(11) NOT NULL DEFAULT 0,
  `pSlotItem2` int(11) NOT NULL DEFAULT 0,
  `pSlotItem3` int(11) NOT NULL DEFAULT 0,
  `pSlotItem4` int(11) NOT NULL DEFAULT 0,
  `pSlotItem5` int(11) NOT NULL DEFAULT 0,
  `pSlotItem6` int(11) NOT NULL DEFAULT 0,
  `pSlotItem7` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`playerID`),
  UNIQUE KEY `playerName` (`playerName`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

REPLACE INTO `players` (`playerID`, `playerName`, `playerPassword`, `playerRegDate`, `playerPassport`, `playerGender`, `playerAdmin`, `playerExp`, `playerLevel`, `playerMoney`, `playerBank`, `playerRedMoney`, `playerHungry`, `playerThirsty`, `playerInDeath`, `playerInjuredTime`, `playerHealth`, `playerArmour`, `Skin`, `playerFaction`, `playerRank`, `playerGang`, `playerGangRank`, `playerGiftbox`, `playerGiftbox2`, `pPosX`, `pPosY`, `pPosZ`, `pPosA`, `pInvColors`, `InvPos_X`, `InvPos_Y`, `InvSize_X`, `InvSize_Y`, `Item`, `ItemKolvo`, `Aks`, `pSlotItem0`, `pSlotItem1`, `pSlotItem2`, `pSlotItem3`, `pSlotItem4`, `pSlotItem5`, `pSlotItem6`, `pSlotItem7`) VALUES
	(1, 'Easy_Core', '$2b$12$CYnKM./CqhAJ5Eg50xPd3ekShXTHvULatxnNKIaMc3IuhBso96Vmm', '4 พฤษภาคม 2026 - 03:34:02', 1, 2, 9999, 0, 1, 4800, 1411066406, 0, 57.39, 84, 0, 0, 95.19, 0, 12, 1, 5, -1, 0, 1, 1, 1657.96, 1796.7, 10.8203, 351.73, 21, 8, 10, -6, -6, '413,412,353,351,419,417,415,418,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,', '36,26,1,1,1,1,332,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,', '0,0,383,0,0,315,398,355,', 0, 0, 18947, 0, 0, 2406, 19050, 19011),
	(2, 'Tvz_Official', '$2b$12$Ot6QdSjdftApd/dNCC0dY.dFx0AMkRQ3SP8q3rADDelgBNkK7Nv/a', '7 พฤษภาคม 2026 - 20:44:16', 0, 1, 999, 0, 1, 95002901, 4999000, 0, 25.8001, 47.5, 0, 0, 50, 0, 230, 0, 5, -1, 0, 0, 0, 2485.42, 1377.43, 10.8421, 130.602, 0, -160, 8, 0, 0, '412,413,331,401,349,395,425,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,418,0,415,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,', '42,7,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,155,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,', '318,0,328,0,0,315,0,358,', 19422, 0, 18967, 0, 0, 2406, 0, 19014),
	(3, 'Easy_Easy', '$2b$12$larFUvlJKdyZ.k63Kdptw.3rEiWv67ogeyvokWo.ETAXRhqSea9xm', '8 พฤษภาคม 2026 - 12:50:34', 1, 1, 0, 0, 1, 1999, 0, 0, 32.9, 61.5, 0, 0, 50, 0, 18, -1, 0, 4, 1, 0, 0, 2489.81, 1394.36, 10.8203, 204.76, 0, 0, 0, 0, 0, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0),
	(4, 'Top_Core', '$2b$12$QHNbCdwccY0yHb0wC8yBq./aA8CX1qDeOCyRIGtcRuYqw4SXs0/Ba', '10 พฤษภาคม 2026 - 21:36:34', 1, 1, 9999, 0, 1, 1000054000, 99948000, 0, 94.4, 96, 0, 0, 78.69, 0, 29, -1, 0, -1, 0, 0, 0, 2497.23, 1409.28, 10.8203, 126.112, 14, 10, 98, 0, 0, '417,415,414,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,', '1,81,99,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,', '0,0,0,0,0,315,0,0,', 0, 0, 0, 0, 0, 2406, 0, 0),
	(5, 'Meen_Core', '$2b$12$bs7tMKKHhQ8BqLthPKgrh..WrWL/v9Dx6NIctBENv/uuaVG40/D1y', '12 พฤษภาคม 2026 - 15:25:46', 1, 1, 9999, 0, 1, 2800, 900, 0, 63.8002, 87, 0, 0, 50, 0, 72, -1, 0, -1, 0, 1, 0, 1669.3, 1812.67, 10.8203, 139.878, 0, 0, 0, 0, 0, '426,412,73,413,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,', '1,9,1,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,', NULL, 0, 0, 0, 0, 0, 0, 0, 0);

CREATE TABLE IF NOT EXISTS `pumps` (
  `pumpid` int(11) NOT NULL AUTO_INCREMENT,
  `interior` int(11) NOT NULL DEFAULT -1,
  `world` int(11) NOT NULL DEFAULT -1,
  `x` float NOT NULL DEFAULT 0,
  `y` float NOT NULL DEFAULT 0,
  `z` float NOT NULL DEFAULT -9999,
  PRIMARY KEY (`pumpid`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

REPLACE INTO `pumps` (`pumpid`, `interior`, `world`, `x`, `y`, `z`) VALUES
	(1, 0, 0, 2498.3, 1396.68, 10.8203);

CREATE TABLE IF NOT EXISTS `vehicle_spots` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` tinyint(4) NOT NULL DEFAULT 0 COMMENT '0=Spawn 1=Store 2=Recover',
  `x` float NOT NULL DEFAULT 0,
  `y` float NOT NULL DEFAULT 0,
  `z` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

REPLACE INTO `vehicle_spots` (`id`, `type`, `x`, `y`, `z`) VALUES
	(1, 0, 2490.67, 1403.06, 10.8203),
	(2, 1, 2493.26, 1396.96, 10.8203),
	(3, 2, 2494.72, 1392.31, 10.8203);

CREATE TABLE IF NOT EXISTS `vehicles` (
  `vehID` int(11) NOT NULL AUTO_INCREMENT,
  `vehModel` int(11) NOT NULL DEFAULT 0,
  `vehName` varchar(25) NOT NULL DEFAULT '0',
  `vehOwner` varchar(25) NOT NULL DEFAULT '-',
  `vehPlate` varchar(16) NOT NULL DEFAULT 'NULL',
  `vehPrice` int(11) NOT NULL DEFAULT 0,
  `vehLock` int(11) NOT NULL DEFAULT 0,
  `vehMod_1` int(11) NOT NULL DEFAULT 0,
  `vehMod_2` int(11) NOT NULL DEFAULT 0,
  `vehMod_3` int(11) NOT NULL DEFAULT 0,
  `vehMod_4` int(11) NOT NULL DEFAULT 0,
  `vehMod_5` int(11) NOT NULL DEFAULT 0,
  `vehMod_6` int(11) NOT NULL DEFAULT 0,
  `vehMod_7` int(11) NOT NULL DEFAULT 0,
  `vehMod_8` int(11) NOT NULL DEFAULT 0,
  `vehMod_9` int(11) NOT NULL DEFAULT 0,
  `vehMod_10` int(11) NOT NULL DEFAULT 0,
  `vehMod_11` int(11) NOT NULL DEFAULT 0,
  `vehMod_12` int(11) NOT NULL DEFAULT 0,
  `vehMod_13` int(11) NOT NULL DEFAULT 0,
  `vehMod_14` int(11) NOT NULL DEFAULT 0,
  `vehColorOne` int(11) NOT NULL DEFAULT 0,
  `vehColorTwo` int(11) NOT NULL DEFAULT 0,
  `vehX` float NOT NULL DEFAULT 0,
  `vehY` float NOT NULL DEFAULT 0,
  `vehZ` float NOT NULL DEFAULT 0,
  `vehA` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`vehID`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

REPLACE INTO `vehicles` (`vehID`, `vehModel`, `vehName`, `vehOwner`, `vehPlate`, `vehPrice`, `vehLock`, `vehMod_1`, `vehMod_2`, `vehMod_3`, `vehMod_4`, `vehMod_5`, `vehMod_6`, `vehMod_7`, `vehMod_8`, `vehMod_9`, `vehMod_10`, `vehMod_11`, `vehMod_12`, `vehMod_13`, `vehMod_14`, `vehColorOne`, `vehColorTwo`, `vehX`, `vehY`, `vehZ`, `vehA`) VALUES
	(3, 462, 'Faggio', 'Easy_Core', 'CC', 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1661.52, 1800.11, 10.4185, 168.183),
	(4, 522, 'NRG-500', 'Meen_Core', 'CC', 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2483.12, 1379.26, 10.311, 319.342),
	(5, 521, 'FCR-900', 'Meen_Core', 'CC', 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2486.52, 1385.48, 10.3654, 50.3461);

CREATE TABLE IF NOT EXISTS `vehicles_old` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `ownerid` int(11) NOT NULL,
  `owner` varchar(32) NOT NULL,
  `plate` varchar(32) NOT NULL,
  `spawned` tinyint(1) NOT NULL,
  `health` float NOT NULL,
  `modelid` int(11) NOT NULL,
  `color1` int(11) NOT NULL,
  `color2` int(11) NOT NULL,
  `posx` float NOT NULL DEFAULT 0,
  `posy` float NOT NULL DEFAULT 0,
  `posz` float NOT NULL DEFAULT 0,
  `posa` float NOT NULL DEFAULT 0,
  `lock` tinyint(1) NOT NULL DEFAULT 0,
  `fuel` float NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

REPLACE INTO `vehicles_old` (`id`, `ownerid`, `owner`, `plate`, `spawned`, `health`, `modelid`, `color1`, `color2`, `posx`, `posy`, `posz`, `posa`, `lock`, `fuel`) VALUES
	(1, 1, 'Easy_Core', 'Q6E3FKK', 0, 990.25, 462, 1, 1, 2483.61, 1405.82, 10.42, 110.25, 0, 98.16),
	(2, 3, 'Easy_Easy', '5IYUG02', 0, 250, 462, 1, 1, 2487.4, 1408.93, 10.82, 154.16, 0, 99.73);

/*!40103 SET TIME_ZONE=IFNULL(@OLD_TIME_ZONE, 'system') */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
