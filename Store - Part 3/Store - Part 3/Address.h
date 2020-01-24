#pragma warning(disable:4996)
#ifndef __ADDRESS_H
#define __ADDRESS_H

#include <string>
#include <iostream>
#include <fstream>
#include "ValidationHelper.h"
using namespace std;	

class Address 
{
private: 
	string						m_street;
	int							m_house_num;
	string						m_city;
	string						m_country;

public:
// C'tors and D'tor
								Address(const string& street, int houseNumber, const string& city, const string& country);
								Address(ifstream& in) { in >> *this; }

//	Getters
	inline const string&		getStreet()			const { return m_street; }
	inline int					getHouseNum()		const { return m_house_num; }
	inline const string&		getCity()			const { return m_city; }
	inline const string&		getCountry()		const { return m_country; }
	void						showAddress()		const;

//	Setters
	bool						setStreet(const string& street);
	bool						setHouse(const int num);
	bool						setCity(const string& city);
	bool						setCountry(const string& country);

// Operators
	const Address&				operator=(const Address& other);
	friend ostream&				operator<<(ostream& out, const Address& address);
	friend istream&				operator>>(istream& in, Address& address);
};
#endif