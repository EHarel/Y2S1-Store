/*
Abstract Base Class for Buyer and Seller.
*/
#ifndef __USER_H
#define __USER_H

#include "Address.h"
#include <iostream>
using namespace std;

class User
{
protected:
	char*					m_username;
	int						m_password;
	Address					m_address;


protected:
	bool					checkValidUsername(const char* username)	const;
	bool					ForbiddenChar(char ch)						const;
	bool					checkValidPassword(int password)			const;

public:
	/*C'tor */				User(const char* username, int password, const Address& address);
							User(const User& other);
							User(User&& other);
	virtual					~User();

	inline const char*		getUsername()				const	{ return m_username; }
	inline Address&			getAddress()						{ return m_address; }
	inline const Address&	getAddress()				const	{ return m_address; }
	
	inline bool				passwordCheck(int password)	const	{ return m_password == password; }


	bool					setUsername(const char* username);
	bool					setPassword(int newPassword, int currentPasswordVerification);
	bool					setAddress(const Address& other);

	
// Operators
	const User&				operator=(const User& other);


	virtual void			toOs(ostream& os) const = 0;
	friend ostream&			operator<<(ostream& os, const User& user);

	friend class System;
};
#endif // !__USER_H