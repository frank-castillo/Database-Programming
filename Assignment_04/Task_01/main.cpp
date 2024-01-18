#include <iostream>
#include <stdio.h>
#include <sqlite3.h>

using namespace std;

int main()
{
	sqlite3* db;
	char* gError = 0;
	string sqlQuery;

	int sq = sqlite3_open("Assignemnt_04", &db);

	if (!sq)
		cout << "Database created or opened with success!\n\n";
	else
		cout << "Failure to create or open the database\n\n";

	sqlQuery = "CREATE TABLE STUDENT("									 // Create table
		"StudentName   TEXT(40),"
		"StudentNumber INT        PRIMARY KEY,"
		"Class         INT,"
		"Major         TEXT(5));"

		"INSERT INTO STUDENT VALUES('Smith', 17, 1, 'CS');"
		"INSERT INTO STUDENT VALUES('Brown', 8, 2, 'CS');";

	int cTable = sqlite3_exec(db, sqlQuery.c_str(), NULL, 0, &gError);

	if (!cTable)
	{
		printf("STUDENT Table created with success!\n\n");
	}
	else
	{
		printf("Error: %s\n\n", gError);
	}

	sqlQuery = "CREATE TABLE COURSE("									 // Create table
		"CourseName    TEXT(50),"
		"CourseNumber  TEXT(20)        PRIMARY KEY,"
		"CreditHours   INT,"
		"Department    TEXT(10));"

		"INSERT INTO COURSE VALUES('Intro to Computer Science', 'CS1310', 4, 'CS');"
		"INSERT INTO COURSE VALUES('Data Structures', 'CS3320', 4, 'CS');"
		"INSERT INTO COURSE VALUES('Discrete Mathematics', 'MATH2410', 8, 'MATH');"
		"INSERT INTO COURSE VALUES('Database', 'CS3380', 8, 'CS');";

	cTable = sqlite3_exec(db, sqlQuery.c_str(), NULL, 0, &gError);

	if (!cTable)
	{
		printf("COURSE Table created with success!\n\n");
	}
	else
	{
		printf("Error: %s\n\n", gError);
	}

	sqlQuery = "CREATE TABLE SECTION("									 // Create table
		"SectionIdentifier    INT PRIMARY KEY,"
		"CourseNumber  TEXT(20),"
		"Semester      TEXT(10),"
		"Year          INT,"
		"Instructor    TEXT(20),"
		"FOREIGN KEY(CourseNumber) REFERENCES COURSE(CourseNumber));"

		"INSERT INTO SECTION VALUES(85, 'MATH2410', 'Fall', 18, 'King');"
		"INSERT INTO SECTION VALUES(92, 'CS1310', 'Spring', 16, 'Anderson');"
		"INSERT INTO SECTION VALUES(102, 'CS3320', 'Fall', 19, 'Kruth');"
		"INSERT INTO SECTION VALUES(112, 'MATH2410', 'Spring', 19, 'Chang');"
		"INSERT INTO SECTION VALUES(119, 'CS1310', 'Fall', 19, 'Anderson');"
		"INSERT INTO SECTION VALUES(135, 'CS3380', 'Fall', 19, 'Stone');";

	cTable = sqlite3_exec(db, sqlQuery.c_str(), NULL, 0, &gError);

	if (!cTable)
	{
		printf("SECTION Table created with success!\n\n");
	}
	else
	{
		printf("Error: %s\n\n", gError);
	}

	sqlQuery = "CREATE TABLE GRADE_REPORT("									 // Create table
		"StudentNumber      INT,"
		"SectionIdentifier  INT,"
		"Grade              TEXT(1),"
		"InternalIndex              INT PRIMARY KEY,"
		"FOREIGN KEY(StudentNumber) REFERENCES STUDENT(StudentNumber),"
		"FOREIGN KEY(SectionIdentifier) REFERENCES SECTION(SectionIdentifier));"

		"INSERT INTO GRADE_REPORT VALUES(17, 112, 'B', 1);"
		"INSERT INTO GRADE_REPORT VALUES(17, 119, 'C', 2);"
		"INSERT INTO GRADE_REPORT VALUES(8, 85, 'A', 3);"
		"INSERT INTO GRADE_REPORT VALUES(8, 92, 'A', 4);"
		"INSERT INTO GRADE_REPORT VALUES(8, 102, 'B', 5);"
		"INSERT INTO GRADE_REPORT VALUES(8, 135, 'A', 6);";

	cTable = sqlite3_exec(db, sqlQuery.c_str(), NULL, 0, &gError);

	if (!cTable)
	{
		printf("GRADE_REPORT Table created with success!\n\n");
	}
	else
	{
		printf("Error: %s\n\n", gError);
	}

	sqlQuery = "CREATE TABLE PREREQUESITE("									 // Create table
		"CourseNumber       TEXT(20),"
		"PrerequesiteNumber TEXT(20),"
		"InternalIndex              INT PRIMARY KEY,"
		"FOREIGN KEY(CourseNumber) REFERENCES COURSE(CourseNumber),"
		"FOREIGN KEY(PrerequesiteNumber) REFERENCES COURSE(CourseNumber));"

		"INSERT INTO PREREQUESITE VALUES('CS3380', 'CS3320', 1);"
		"INSERT INTO PREREQUESITE VALUES('CS3380', 'MATH2410', 2);"
		"INSERT INTO PREREQUESITE VALUES('CS3320', 'CS1310', 3);";

	cTable = sqlite3_exec(db, sqlQuery.c_str(), NULL, 0, &gError);

	if (!cTable)
	{
		printf("PREREQUESITE Table created with success!\n\n");
	}
	else
	{
		printf("Error: %s\n\n", gError);
	}
}