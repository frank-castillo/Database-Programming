#include <iostream>
#include <stdio.h>
#include <sqlite3.h>

// int sqlite3_open(const char* filename, sqlite3** ppDB);

using namespace std;

int callback(void* data, int argc, char** argv, char** azColName);

int main()
{
	// We'll die here
	// JUST END ME!!!!
	// TODO:
	// Kill myself

	sqlite3* db; // This is a container for your database
	char* gError = 0;
	string sql;

	int sq = sqlite3_open("\mydatabase.db", &db);

	if (sq!=SQLITE_OK)
	{
		cout << "Error: %s\n\n", gError;
	}
	else
	{
		cout << "Congratulations, database created/opened with success!\n\n";
	}

	sql = "CREATE TABLE students("									 // Create table
		  "Student_ID   INT        PRIMARY KEY,"
		  "Student_name TEXT(40),"
		  "City         TEXT(40),"
		  "Age          INT);"

		  "INSERT INTO students VALUES(1, 'Raju', 'Chennal', 25);";	 // Insert data

	int cTable = sqlite3_exec(db,			//Container
							  sql.c_str(),	// const string
							  NULL,			// Null for callback
							  0,			// zero
							  &gError);		//Error

	if (cTable != SQLITE_OK)
	{
		cout << "Error: " << gError <<"\n\n", gError;
	}
	else
	{
		cout << "Table created with success!\n\n";
	}

	sql = "INSERT INTO students VALUES(2, 'Rajuuuiuu', 'Chedfsdfsdnnal', 45);"
		  "INSERT INTO students VALUES(3, 'Aere', 'Asas', 46);"
		  "INSERT INTO students VALUES(4, 'Aero', 'Osas', 34);"
		  "INSERT INTO students VALUES(5, 'Arere', 'Usas', 54);"
		;

	cTable = sqlite3_exec(db, sql.c_str(), NULL, 0, &gError);

	if (cTable != SQLITE_OK)
	{
		cout << "Error: " << gError << "\n\n", gError;
	}
	else
	{
		cout << "Data inserted into table with success!\n\n";
	}

	sql = "SELECT * FROM students";

	int recoverData = sqlite3_exec(db,			//Container
								   sql.c_str(),	// const string
								   callback,	// Null for callback
								   0,			// zero
								   &gError);	//Error

	if (recoverData != SQLITE_OK)
	{
		cout << "Error: %s\n\n", gError;
	}
	else
	{
		cout << "The select query works!\n\n";
	}

	sqlite3_close(db);
	return 0;

	//auto database = std::make_unique<sqlite3*>();
	//int sq2 = sqlite3_open("\mydatabase.db", &*database);
}

int callback(void* data, int argc, char** argv, char** azColName)
{
	for (int row = 0; row < argc; row++)
	{
		cout << argv[row] << " | ";
	}

	cout << endl;

	return 0;
}