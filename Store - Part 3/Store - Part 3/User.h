/*
Abstract Base Class for Buyer and Seller.
*/
#ifndef __USER_H
#define __USER_H

#include "Address.h"
#include <string>

class User
{
protected:
	string					m_username;
	int						m_password;
	Address					m_address;


public: // C'tors:
							User(const string& username, int password, const Address& address);
							User(const User& other) = delete;
							User(User&& other) = delete;
							User(ifstream& in) : m_address(in) { in >> *this; }
	virtual					~User() {  }

public: 
	inline const string&	getUsername()				const	{ return m_username; }
	inline Address&			getAddress()						{ return m_address; }
	inline const Address&	getAddress()				const	{ return m_address; }
	
	inline bool				passwordCheck(int password)	const	{ return m_password == password; } 
	bool					checkValidPassword(int password)			const;


	bool					setUsername(const string& username);
	bool					setPassword(int newPassword, int currentPasswordVerification);
	bool					setAddress(const Address& other);

	
// Operators
	const User&				operator=(const User& other) = delete;


	virtual void			toOs(ostream& os) const = 0;
	friend ostream&			operator<<(ostream& os, const User& user);
	friend istream&			operator>>(istream& in, User& user);

	friend class System;
};
#endif // !__USER_H