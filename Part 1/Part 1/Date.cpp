#include "Date.h"


Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
	setDay(day);
	setMonth(month);
	setYear(year);
}



// ------------------------------- GETTERS ------------------------------- //

unsigned int Date::getDay()		const
{
	return day;
}
unsigned int Date::getMonth()		const
{
	return month;
}
unsigned int Date::getYear()		const
{
	return year;
}


bool Date::setDay(unsigned int day)
{
	if (day < 0 || day>31)
		return false;
	this->day = day;
	return true;
}

bool Date::setMonth(unsigned int month)
{
	if (month < 0 || month>12)
		return false;
	this->month = month;
}

bool Date::setYear(unsigned int year)
{
	// CHECKS!
	this->year = year;
	return true;
}