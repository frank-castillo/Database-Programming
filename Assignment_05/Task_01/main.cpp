#include <iostream>
#include <stdio.h>
#include <sqlite3.h>

using namespace std;

int Callback(void* data,int argc, char** argv, char** azColName)
{
	for (int row = 0; row < argc; row++)
	{
		cout << azColName[row] << " : " << argv[row] << " | ";
	}

	cout << endl;

	return 0;
}

void ShowTable(sqlite3* db, const string tableName)
{
	string displayQuery = "SELECT * FROM " + tableName + "; ";
	sqlite3_exec(db, displayQuery.c_str(), Callback, NULL, NULL);
}

void ResetTable(sqlite3* db, char* error , const string tableName)
{
	string dropQuery = "DROP TABLE IF EXISTS " + tableName + "; ";
	int exit = sqlite3_exec(db, dropQuery.c_str(), NULL, 0, &error);

	if (exit != SQLITE_OK)
	{
		cout << "ERROR DROPPING: " + tableName + "\n\n";
	}
	else
	{
		cout << "SUCCESSFULLY DROPPED: " + tableName + "\n\n";
	}
}

int main(int argc, char** argv)
{
	sqlite3* db;
	char* gError = 0;
	string sqlQuery;
	string tableName;

	int sq = sqlite3_open("Assignemnt_05", &db);

	if (sq != SQLITE_OK)
	{
		cout << "Database created or opened with success!\n\n";
	}
	else
	{
		cout << "Failure to create or open the database\n\n";
	}

	tableName = "STATIONS";
	ResetTable(db, gError, tableName);

	sqlQuery = "CREATE TABLE STATIONS("									 // Create table
		"ID				INT PRIMARY KEY,"
		"City			VARCHAR(50),"
		"State			VARCHAR(50),"
		"Latitude		DECIMAL,"
		"Longitude		DECIMAL);"

		"INSERT INTO STATIONS VALUES(1, 'Asheville',		'North Carolina',	35.6,	82.6);"
		"INSERT INTO STATIONS VALUES(2, 'Burlignton',		'North Carolina',	36.1,	79.4);"
		"INSERT INTO STATIONS VALUES(3, 'Chapel Hill',		'North Carolina',	35.9,	79.1);"
		"INSERT INTO STATIONS VALUES(4, 'Davidson',			'North Carolina',	35.5,	80.8);"
		"INSERT INTO STATIONS VALUES(5, 'Elizabeth City',	'North Carolina',	36.3,	76.3);"
		"INSERT INTO STATIONS VALUES(6, 'Fargo',			'North Dakota',		46.9,	96.8);"
		"INSERT INTO STATIONS VALUES(7, 'Grand Forks',		'North Dakota',		47.9,	97.0);"
		"INSERT INTO STATIONS VALUES(8, 'Hettinger',		'North Dakota',		46.0,	102.6);"
		"INSERT INTO STATIONS VALUES(9, 'Inkster',			'North Dakota',		48.2,	97.6);";

	int cTable = sqlite3_exec(db, sqlQuery.c_str(), NULL, 0, &gError);

	if (cTable == SQLITE_OK)
	{
		cout << "STATIONS Table created with success!\n\n";
	}
	else
	{
		cout << "Error: " << gError << "\n\n";
	}

	ShowTable(db, tableName);

	sqlQuery = "UPDATE STATIONS SET City = 'Florence', State = 'Colorado', Latitude = 'NULL', Longitude = 'NULL' WHERE ID = 1;";
	sqlQuery += "UPDATE STATIONS SET City = 'Austin', State = 'Nevada', Latitude = 5.11, Longitude = 1.23 WHERE ID = 3;";
	sqlQuery += "UPDATE STATIONS SET State = 'Vancouver' WHERE ID = 6;";
	sqlQuery += "UPDATE STATIONS SET Longitude = 'NULL' WHERE ID = 8;";

	int alterTable = sqlite3_exec(db, sqlQuery.c_str(), NULL, 0, &gError);
	
	if (alterTable == SQLITE_OK)
	{
		cout << "\n\nSTATIONS Table modified with success!\n\n";
	}
	else
	{
		cout << "\n\nError: "<< gError << "\n\n";
	}

	ShowTable(db, tableName);

	sqlite3_close(db);
	return 0;
}