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

CREATE TABLE IF NOT EXISTS `dropitems` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `model_id` int(11) NOT NULL,
  `item_name` varchar(64) NOT NULL,
  `count` int(11) NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

CREATE TABLE IF NOT EXISTS `players` (
  `playerID` int(11) NOT NULL AUTO_INCREMENT,
  `playerName` varchar(24) NOT NULL,
  `playerPassword` varchar(129) NOT NULL,
  `playerRegDate` varchar(90) NOT NULL,
  `playerGender` int(11) NOT NULL DEFAULT 0,
  `playerAdmin` int(11) NOT NULL DEFAULT 0,
  `playerExp` float NOT NULL,
  `playerLevel` int(11) NOT NULL,
  `playerHealth` float NOT NULL,
  `playerArmour` float NOT NULL,
  `Skin` int(11) NOT NULL,
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

/*!40103 SET TIME_ZONE=IFNULL(@OLD_TIME_ZONE, 'system') */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
