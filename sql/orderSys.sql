/*
Navicat MySQL Data Transfer

Source Server         : 192.168.200.128_3306
Source Server Version : 50505
Source Host           : 192.168.200.128:3306
Source Database       : orderSys

Target Server Type    : MYSQL
Target Server Version : 50505
File Encoding         : 65001

Date: 2022-04-20 20:16:13
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `bills`
-- ----------------------------
DROP TABLE IF EXISTS `bills`;
CREATE TABLE `bills` (
  `dealID` varchar(255) NOT NULL,
  `tableID` int(11) DEFAULT NULL,
  `dishID` int(11) DEFAULT NULL,
  `status` int(11) DEFAULT NULL,
  `time` datetime DEFAULT NULL,
  `operator` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`dealID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Records of bills
-- ----------------------------
INSERT INTO `bills` VALUES ('202204200001', '2', '1', '1', '2022-04-20 19:26:30', 'dong');
INSERT INTO `bills` VALUES ('202204200002', '3', '1', '3', '2022-04-20 19:29:45', 'dong');
INSERT INTO `bills` VALUES ('202204200003', '3', '1', '3', '2022-04-20 19:32:24', 'dong');
INSERT INTO `bills` VALUES ('202204200004', '3', '1', '3', '2022-04-20 19:41:47', 'dong');
INSERT INTO `bills` VALUES ('202204200005', '3', '2', '3', '2022-04-20 19:42:12', 'dong');

-- ----------------------------
-- Table structure for `menu`
-- ----------------------------
DROP TABLE IF EXISTS `menu`;
CREATE TABLE `menu` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `price` double DEFAULT NULL,
  `status` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Records of menu
-- ----------------------------
INSERT INTO `menu` VALUES ('1', '面', '8', '0');
INSERT INTO `menu` VALUES ('2', '米饭', '2', '0');

-- ----------------------------
-- Table structure for `orders`
-- ----------------------------
DROP TABLE IF EXISTS `orders`;
CREATE TABLE `orders` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `tableID` int(11) DEFAULT NULL,
  `dishID` int(11) DEFAULT NULL,
  `status` int(11) DEFAULT NULL,
  `comment` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `sdasd` (`dishID`),
  CONSTRAINT `sdasd` FOREIGN KEY (`dishID`) REFERENCES `menu` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Records of orders
-- ----------------------------

-- ----------------------------
-- Table structure for `user`
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `id` int(20) NOT NULL,
  `type` int(11) NOT NULL,
  `name` varchar(20) NOT NULL,
  `passwd` varchar(20) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES ('10001', '1', 'dong', '123');
INSERT INTO `user` VALUES ('10002', '2', 'xi', '123');
INSERT INTO `user` VALUES ('10003', '0', 'root', '123');
