#include "Address.h"
#include <string.h>
#include <iostream>
using namespace std;

// ----------------- C'TORS AND D'TOR----------------- //
Address::Address(const char* street, int houseNumber, const char* city, const char* country) : street(NULL), city(NULL), country(NULL)
{
	setStreet(street);
	setHouse(houseNumber);
	setCity(city);
	setCountry(country);
}
Address::Address(const Address& other)	: street(NULL), city(NULL), country(NULL) //	Copy c'tor.
{
	*this = other;
}
Address::Address(Address&& other) //	Move c'tor.
{
	this->street = other.street;
	setHouse(other.houseNum);
	this->city = other.city;
	this->country = other.country;

	other.street = nullptr;
	other.city = nullptr;
	other.country = nullptr;
}
Address::~Address()							//	D'tor.
{
	delete[]street;
	delete[]city;
	delete[]country;
}


// ----------------- SETTERS ----------------- //
bool Address::setStreet(const char* street)
{
	if (checkLetterOnlyString(street) == false)
		return false;
	
	delete[](this->street);
	this->street = strdup(street);
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
	delete[](this->city);
	this->city = strdup(city);
	return true;
}
bool Address::setCountry(const char* country)
{
	if (checkLetterOnlyString(country) == false)
		return false;
	delete[](this->country);
	this->country = strdup(country);
	return true;
}


// ----------------- OPERATORS ----------------- //
const Address& Address::operator=(const Address& other)
{
	if (this == &other)
		return *this;

	delete[]street;
	delete[]city;
	delete[]country;

	street = strdup(other.street);
	houseNum = other.houseNum;
	city = strdup(other.city);
	country = strdup(other.country);

	return *this;
}
ostream& operator<<(ostream& os, const Address& address)
{
	os << "Street: " << address.street << endl;
	os << "House number: " << address.houseNum << endl;
	os << "City: " << address.city << endl;
	os << "Country: " << address.country << endl;
	return os;
}


// ----------------- MISC ----------------- //
bool Address::checkLetterOnlyString(const char* str) const
//This function receives a string and checks that it contains only letters, or a space.
//Used originally to check city and country names.
{
	int i = 0;
	char ch;

	while (str[i] != '\0')
	{
		ch = str[i];
		if ((ch <= 'z' && ch >= 'a') && (ch <= 'Z' && ch >= 'A') && (ch != ' '))
			return false;
		i++;
	}
	return true;
}
void Address::showAddress() const
{
	cout << street << " " << houseNum << ", " << city << ", " << country << endl;
}