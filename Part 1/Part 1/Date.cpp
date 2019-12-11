#include "Date.h"
#include <iostream>
using namespace std;

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
void Date::show()					const
{
	cout << day << " / " << month << " / " << year << endl;
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
	return true;
}

bool Date::setYear(unsigned int year)
{
	if (year < 1900 || year>2030)	//	If we knew how to use current time, we would have set the current date as the upper limit.
		return false;
	this->year = year;
	return true;
}