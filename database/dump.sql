-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: May 22, 2025 at 07:55 AM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Database: `sampsvr`
--

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

CREATE TABLE IF NOT EXISTS `garage` (
  `garageid` int(11) NOT NULL AUTO_INCREMENT,
  `garagex` float NOT NULL DEFAULT 0,
  `garagey` float NOT NULL DEFAULT 0,
  `garagez` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`garageid`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

CREATE TABLE IF NOT EXISTS `gps_locations` (
  `gpsid` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(64) NOT NULL DEFAULT '',
  `category` tinyint(4) NOT NULL DEFAULT 0,
  `x` float NOT NULL DEFAULT 0,
  `y` float NOT NULL DEFAULT 0,
  `z` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`gpsid`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

CREATE TABLE IF NOT EXISTS `pawn` (
  `pawnid` int(11) NOT NULL AUTO_INCREMENT,
  `pawnx` float NOT NULL DEFAULT 0,
  `pawny` float NOT NULL DEFAULT 0,
  `pawnz` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`pawnid`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

CREATE TABLE IF NOT EXISTS `pickcar` (
  `pickcarid` int(11) NOT NULL AUTO_INCREMENT,
  `pickcarx` float NOT NULL DEFAULT 0,
  `pickcary` float NOT NULL DEFAULT 0,
  `pickcarz` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`pickcarid`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

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

CREATE TABLE IF NOT EXISTS `pumps` (
  `pumpid` int(11) NOT NULL AUTO_INCREMENT,
  `interior` int(11) NOT NULL DEFAULT -1,
  `world` int(11) NOT NULL DEFAULT -1,
  `x` float NOT NULL DEFAULT 0,
  `y` float NOT NULL DEFAULT 0,
  `z` float NOT NULL DEFAULT -9999,
  PRIMARY KEY (`pumpid`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

CREATE TABLE IF NOT EXISTS `vehicle_spots` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` tinyint(4) NOT NULL DEFAULT 0 COMMENT '0=Spawn 1=Store 2=Recover',
  `x` float NOT NULL DEFAULT 0,
  `y` float NOT NULL DEFAULT 0,
  `z` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

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

COMMIT;

/*!40103 SET TIME_ZONE=IFNULL(@OLD_TIME_ZONE, 'system') */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
