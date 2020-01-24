#include "User.h"
#include "ValidationHelper.h"
#include <fstream>

User::User(const string& username, int password, const Address& address) : m_address(address)
{
	setUsername(username);
	m_password = 0; // For password verification - it requires some initial value.
	setPassword(password, 0);
}

// ----------------- SETTERS ----------------- //
bool User::setUsername(const string& username)
{
	if(ValidationHelper::ValidName(username))
	{
		m_username = username;
		return true;
	}
	return false;
}
bool User::setPassword(int password, int currentPasswordVerification)
{
	if (currentPasswordVerification != m_password)
		return false;
	if (checkValidPassword(password) == false)
		return false;
	m_password = password;
	return true;
}
bool User::setAddress(const Address& other)
{
	// other address is valid, otherwise it wouldn't have been constructed. No need to check value validity.
	m_address = other;
	return true;
}


// ----------------- PROTECTED ----------------- //
bool User::checkValidPassword(int password) const
{
	return (password >= 0);
}


// ----------------- GLOBAL ----------------- //
ostream& operator<<(ostream& os, const User& user)
{
	if (typeid(os) == typeid(ofstream)) // Check if writing into file.
	{
		os << user.m_address << "\n" << user.m_username << "\n" << user.m_password; // Address first, because when reading from file, we must initialize it first
	}
	else // Writing not into file.
	{
		os << "Username: " << user.m_username << endl;
		os << "Address: " << user.m_address << endl;
		user.toOs(os);
		cout << endl;
	}
	return os;
}
istream & operator>>(istream & in, User & user)
{
	getline(in, user.m_username);
	in >> user.m_password;

	return in;
}
