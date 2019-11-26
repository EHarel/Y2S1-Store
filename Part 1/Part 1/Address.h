#pragma warning(disable:4996)
#ifndef __ADDRESS_H
#define __ADDRESS_H

#include "Product.h"	//	PROBLEM: the only reason this is here is because of const int LEN. We should find a different solution to this.

class Address 
{
public:
	Address() = delete;	//	make it clear we don't want a default constructor - add it to all classes
	Address(char* street, int houseNumber, char* city, char* country);

//	Getters
	const char* getStreet()		const;
	int			getHouseNum()	const;
	const char*	getCity()		const;
	const char*	getCountry()	const;

	void		showAddress()	const;

//	Setters
	bool setStreet(const char* street);
	bool setHouse(const int num);
	bool setCity(const char* city);
	bool setCountry(const char* country);


	//	DESTRUCTOR
private:
	char		street[LEN];
	int			houseNum;
	char		city[LEN];
	char		country[LEN];
};
#endif