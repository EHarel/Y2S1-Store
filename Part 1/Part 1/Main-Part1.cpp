#pragma warning(disable:4996)
#include "Source.h"

void main()
{
	char name[LEN];
	cout << "Enter the name of the system: ";
	cin >> name;
	getchar();

	System system(name);
	runMenu(system);
}

/*
How about two arrays - one for Buyers, one for Sellers

SERIAL NUMBER: how to do it? just a global number to advance?
FOr each category of items - a number that starts differently
e.g.
electric - 10000000
children - 20000000
...

QUESTIONS: is there a limit on the amount of feedback a buyer can give a seller?

To do:
	In system add array of products
	
	When we do setName, make sure that old name is deleted (it's likely dynamically allocated) (relevant with unknown name size that we need to reallocate/increase like in Tirgul 3)

	In searchUserName, do we need to check valid input length?

	-	string checks - length, copy, etc

*/

