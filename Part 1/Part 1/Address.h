#pragma warning(disable:4996)
#ifndef __ADDRESS_H
#define __ADDRESS_H

class Address 
{
private: // All the strings are dynamically allocated.
	char*		street;
	int			houseNum;
	char*		city;
	char*		country;

public:
// Constructors and Destructor
	Address() = delete;	// No default constructor.
	Address(const char* street, int houseNumber, const char* city, const char* country);
	Address(const Address& other);
	Address(Address&& other);
	~Address();

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

// Operators
	const Address& operator=(const Address& other);
};
#endif