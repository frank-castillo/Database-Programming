#include <iostream>
#include <mysql.h>

using std::cout;
using std::endl;

int main(int argc, char** argv)
{
	MYSQL* con;
	con = mysql_init(0);

	cout << "Hello Bergenstein!" << endl;
	return 0;
}