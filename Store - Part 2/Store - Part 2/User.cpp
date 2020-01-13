#include "User.h"

User::User(const char* username, int password, const Address& address) : m_address(address), m_username(NULL)
{
	setUsername(username);
	m_password = 0; // For password verification - it requires some initial value.
	setPassword(password, 0);

	// Later on we'll add exceptions here.
}
User::User(const User& other) : m_address(other.m_address) 
{
	m_username = strdup(other.m_username);
	m_password = other.m_password;

	// We avoid calling operator== because then we'll also perform another placement for the address, after already creating it. Wasted action.
}
User::User(User&& other) : m_address(other.m_address) // # does this go through move constructor of address?
{
	m_username = other.m_username;
	m_password = other.m_password;

	other.m_username = nullptr;
}
User::~User()
{
	delete[]m_username;
}

// ----------------- SETTERS ----------------- //
bool User::setUsername(const char* username)
{
	if (checkValidUsername(username))
	{
		delete[]m_username;
		m_username = strdup(username);
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
bool User::checkValidUsername(const char* username) const
{
	int len = strlen(username);
	for (int i = 0; i < len; i++)
	{
		if (ForbiddenChar(username[i]))
			return false;
	}
	return true;
}
bool User::ForbiddenChar(char ch) const
{
	switch (ch)
	{
	case '!':
		return true;
	case '@':
		return true;
	case '#':
		return true;
	case '$':
		return true;
	case '%':
		return true;
	case '^':
		return true;
	case '&':
		return true;
	case '*':
		return true;
	case '(':
		return true;
	case ')':
		return true;
	default:
		return false;
	}
}
bool User::checkValidPassword(int password) const
{
	return (password >= 0);
}



// ----------------- OPERATORS ----------------- //
const User& User::operator=(const User& other)
{
	if (this != &other)
	{
		delete[]m_username;
		m_username = strdup(other.m_username);
		m_password = other.m_password;
		m_address = other.m_address;
	}
	return *this;
}



// ----------------- GLOBAL ----------------- //
ostream& operator<<(ostream& os, const User& user)
{
	os << "Username: " << user.m_username << endl;
	user.m_address.showAddress();
	cout << endl;
	user.toOs(os);
	cout << endl;
	return os;
}