#ifndef __USER_H
#define __USER_H

//#include "Seller.h"
//#include "Buyer.h"
// #include <iostream>
// using namespace std;

class Seller;
class Buyer;
class Address;

int const LEN = 31;

class User
{
public:
	// enum eStatus { BUYER, Seller };
	User(char* name, int password, Address* address, Seller* Seller, Buyer* buyer);

	bool setUserName(const char* name);
	bool setPassword(const int password);
	bool setAddress(Address* address);
	bool setStatus(eStatus status);

	const char*		getName()		const;
	int				getPassword()	const;	//	Do we actually need this available?
	const Address&	getAddress()	const;
	eStatus			getStatus()		const;

private:
	char				m_userName[LEN];
	int					m_password;
	Address*			m_address;
	// eStatus				m_status;	//	a user can either buy or sell, but not be both
	Seller*				m_SellerJob;
	Buyer*				m_buyer;		//	EW CHANGE THIS


	// How to connect a user to his side-gig as a Seller or buyer?
	// A pointer to each of those objects? With the "forbidden" one being null?
}
#endif // !__USER_H
