#pragma warning(disable:4996)
#ifndef __ADDRESS_H
#define __ADDRESS_H

class Address 
{
private: 
	char*					street;
	int						houseNum;
	char*					city;
	char*					country;

// Private Methods
	bool					checkLetterOnlyString(const char* str)	const;


public:
// C'tors and D'tor
	Address(const char* street, int houseNumber, const char* city, const char* country);
	Address(const Address& other);
	Address(Address&& other);
	~Address();

//	Getters
	inline const char*		getStreet()			const { return street; }
	inline int				getHouseNum()		const { return houseNum; }
	inline const char*		getCity()			const { return city; }
	inline const char*		getCountry()		const { return country; }
	void					showAddress()		const;

//	Setters
	bool					setStreet(const char* street);
	bool					setHouse(const int num);
	bool					setCity(const char* city);
	bool					setCountry(const char* country);

// Operators
	const Address&			operator=(const Address& other);
};
#endif