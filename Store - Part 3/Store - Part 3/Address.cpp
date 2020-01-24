#include "Address.h"
#include "ValidationHelper.h"

// ----------------- C'TORS AND D'TOR----------------- //
Address::Address(const string& street, int houseNumber, const string& city, const string& country) //: street(NULL), city(NULL), country(NULL)
{
	setStreet(street);
	setHouse(houseNumber);
	setCity(city);
	setCountry(country);
}


// ----------------- SETTERS ----------------- //
bool Address::setStreet(const string& street)
{
	if (ValidationHelper::ValidName(street))
	{
		m_street = street;
		return true;
	}
	return false;
}
bool Address::setHouse(const int num)
{
	if (num < 1)
		return false;
	m_house_num = num;
	return true;
}
bool Address::setCity(const string& city)
{
	if (ValidationHelper::ValidName(city))
	{
		m_city = city;
		return true;
	}
	return false;
}
bool Address::setCountry(const string& country)
{
	if (ValidationHelper::ValidName(country))
	{
		m_country = country;

		return true;
	}
	return false;
}


// ----------------- OPERATORS ----------------- //
const Address& Address::operator=(const Address& other)
{
	if (this != &other)
	{
		m_street = other.m_street;
		m_house_num = other.m_house_num;
		m_city = other.m_city;
		m_country = other.m_country;
	}

	return *this;
}
ostream& operator<<(ostream& out, const Address& address)
{
	if (typeid(out) == typeid(ofstream)) // Check if writing into file
	{
		out << address.m_street << "\n" << address.m_house_num << " " << address.m_city << "\n" << address.m_country; // Remove commas
		// Print with \n because names could include whitespace, which would disrupt reading from the file
	}
	else // Not writing into file
	{
		out << address.m_street << " " << address.m_house_num << ", " << address.m_city << ", " << address.m_country; // Add commas
	}
	return out;
}
istream & operator>>(istream & in, Address & address)
{

	getline(in, address.m_street);
	in >> address.m_house_num;
	getline(in, address.m_city); 
	getline(in, address.m_country);

	return in;
}


// ----------------- MISC ----------------- //
void Address::showAddress() const
{
	cout << "Address: " << m_street << " " << m_house_num << ", " << m_city << ", " << m_country << endl;
}