CREATE DATABASE  IF NOT EXISTS `task_02` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `task_02`;
-- MySQL dump 10.13  Distrib 8.0.28, for Win64 (x86_64)
--
-- Host: localhost    Database: task_02
-- ------------------------------------------------------
-- Server version	8.0.27

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `course`
--

DROP TABLE IF EXISTS `course`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `course` (
  `CourseName` text,
  `CourseNumber` varchar(30) NOT NULL,
  `CreditHours` smallint unsigned DEFAULT NULL,
  `Department` text,
  PRIMARY KEY (`CourseNumber`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `course`
--

LOCK TABLES `course` WRITE;
/*!40000 ALTER TABLE `course` DISABLE KEYS */;
INSERT INTO `course` VALUES ('Intro to Computer Science','CS1310',4,'CS'),('Data Structures','CS3320',4,'CS'),('Database','CS3380',3,'CS'),('Discrete Mathematics','MATH2410',3,'MATH');
/*!40000 ALTER TABLE `course` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `grade_report`
--

DROP TABLE IF EXISTS `grade_report`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `grade_report` (
  `StudentNumber` int unsigned DEFAULT NULL,
  `SectionIdentifier` int unsigned DEFAULT NULL,
  `Grade` varchar(1) DEFAULT NULL,
  `myIndex` int unsigned NOT NULL,
  PRIMARY KEY (`myIndex`),
  KEY `StudentNumber` (`StudentNumber`),
  KEY `SectionIdentifier` (`SectionIdentifier`),
  CONSTRAINT `grade_report_ibfk_1` FOREIGN KEY (`StudentNumber`) REFERENCES `student` (`StudentNumber`),
  CONSTRAINT `grade_report_ibfk_2` FOREIGN KEY (`SectionIdentifier`) REFERENCES `section` (`SectionIdentifier`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `grade_report`
--

LOCK TABLES `grade_report` WRITE;
/*!40000 ALTER TABLE `grade_report` DISABLE KEYS */;
INSERT INTO `grade_report` VALUES (17,112,'B',1),(17,119,'C',2),(8,85,'A',3),(8,92,'A',4),(8,102,'B',5),(8,135,'A',6);
/*!40000 ALTER TABLE `grade_report` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `prerequesite`
--

DROP TABLE IF EXISTS `prerequesite`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `prerequesite` (
  `CourseNumber` varchar(30) DEFAULT NULL,
  `PrerequesiteNumber` varchar(30) DEFAULT NULL,
  `myIndex` int unsigned NOT NULL,
  PRIMARY KEY (`myIndex`),
  KEY `CourseNumber` (`CourseNumber`),
  KEY `PrerequesiteNumber` (`PrerequesiteNumber`),
  CONSTRAINT `prerequesite_ibfk_1` FOREIGN KEY (`CourseNumber`) REFERENCES `course` (`CourseNumber`),
  CONSTRAINT `prerequesite_ibfk_2` FOREIGN KEY (`PrerequesiteNumber`) REFERENCES `course` (`CourseNumber`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `prerequesite`
--

LOCK TABLES `prerequesite` WRITE;
/*!40000 ALTER TABLE `prerequesite` DISABLE KEYS */;
INSERT INTO `prerequesite` VALUES ('CS3380','CS3320',1),('CS3380','MATH2410',2),('CS3320','CS1310',3);
/*!40000 ALTER TABLE `prerequesite` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `section`
--

DROP TABLE IF EXISTS `section`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `section` (
  `SectionIdentifier` int unsigned NOT NULL,
  `CourseNumber` varchar(30) DEFAULT NULL,
  `Semester` varchar(30) DEFAULT NULL,
  `sYear` smallint unsigned DEFAULT NULL,
  `Instructor` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`SectionIdentifier`),
  KEY `CourseNumber` (`CourseNumber`),
  CONSTRAINT `section_ibfk_1` FOREIGN KEY (`CourseNumber`) REFERENCES `course` (`CourseNumber`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `section`
--

LOCK TABLES `section` WRITE;
/*!40000 ALTER TABLE `section` DISABLE KEYS */;
INSERT INTO `section` VALUES (85,'MATH2410','Fall',18,'King'),(92,'CS1310','Spring',16,'Anderson'),(102,'CS3320','Fall',19,'Kruth'),(112,'MATH2410','Spring',19,'Chang'),(119,'CS1310','Fall',19,'Anderson'),(135,'CS3380','Fall',19,'Stone');
/*!40000 ALTER TABLE `section` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `student`
--

DROP TABLE IF EXISTS `student`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `student` (
  `StudentName` text,
  `StudentNumber` int unsigned NOT NULL,
  `Class` int unsigned DEFAULT NULL,
  `Major` text,
  PRIMARY KEY (`StudentNumber`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `student`
--

LOCK TABLES `student` WRITE;
/*!40000 ALTER TABLE `student` DISABLE KEYS */;
INSERT INTO `student` VALUES ('Brown',8,2,'CS'),('Smith',17,1,'CS');
/*!40000 ALTER TABLE `student` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-04-26 16:40:51
