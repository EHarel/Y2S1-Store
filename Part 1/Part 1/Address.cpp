#include "Address.h"
#include <string.h>
#include <iostream>
using namespace std;

static bool checkLetterOnlyString(const char* str);



Address::Address(char* street, int houseNumber, char* city, char* country)
{
	setStreet(street);
	setHouse(houseNumber);
	setCity(city);
	setCountry(country);
}



// ----------------- GETTERS ----------------- //

const char* Address::getStreet()		const
{
	return street;
}

int			Address::getHouseNum()	const
{
	return houseNum;
}

const char*	Address::getCity()		const
{
	return city;
}

const char*	Address::getCountry()	const
{
	return country;
}

void		Address::showAddress()	const
{
	cout << street << " " << houseNum << ", " << city << ", " << country << endl;
}

// ----------------- SETTERS ----------------- //

bool Address::setStreet(const char* street)
{
	if (checkLetterOnlyString(street) == false)
		return false;
	strcpy(this->street, street);
	return true;
}

bool Address::setHouse(const int num)
{
	if (num < 1)
		return false;
	this->houseNum = num;
	return true;
}

bool Address::setCity(const char* city)
{

	if (checkLetterOnlyString(city) == false)
		return false;
	strcpy(this->city, city);
	return true;
}

bool Address::setCountry(const char* country)
{
	if (checkLetterOnlyString(country) == false)
		return false;
	strcpy(this->country, country);
	return true;
}





// ----------------- STATIC FUNCTION IMPLEMENTATION ----------------- //

static bool checkLetterOnlyString(const char* str)
//This function receives a string and checks that it contains only letters.
//Used originally to check city and country names.
{
	int i = 0;
	char ch;

	while (str[i] != '\0')
	{
		ch = str[i];
		if ((ch <= 'z' && ch >= 'a') && (ch <= 'Z' && ch >= 'A'))
			return false;
		i++;
	}
	return true;
}