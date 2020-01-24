#include "Date.h"

// ----------------- C'TORS AND D'TOR ----------------- //
Date::Date(int day, int month, int year)
{
	setDay(day);
	setMonth(month);
	setYear(year);
}


// ----------------- SETTERS ----------------- //
bool Date::setDay(int day)
{
	if (day < 0 || day>31)
		return false;
	m_day = day;
	return true;
}
bool Date::setMonth(int month)
{
	if (month < 0 || month>12)
		return false;
	m_month = month;
	return true;
}
bool Date::setYear(int year)
{
	if (year < 1900 || year>2030)	//	If we knew how to use current time, we would have set the current date as the upper limit.
		return false;
	m_year = year;
	return true;
}


// ----------------- MISC ----------------- //
void Date::show() const
{
	cout << *this << endl;
}

ostream & operator<<(ostream & os, const Date & date)
{
	os << date.m_day << " / " << date.m_month << " / " << date.m_year << endl;
	return os;
}
