#pragma warning(disable:4996)
#ifndef __DATE_H
#define __DATE_H

//#include <iostream>
//using namespace std;

class Date
{
private:
	unsigned int			day;
	unsigned int			month;
	unsigned int			year;

public:
// C'tors and D'tor
	Date() = delete;
	Date(unsigned int day, unsigned int month, unsigned int year);

// Const methods
	inline unsigned int		getDay()		const { return day; }
	inline unsigned int		getMonth()		const { return month; }
	inline unsigned int		getYear()		const { return year; }
	void					show()			const;

// Non-const methods
	bool					setDay(unsigned int day);
	bool					setMonth(unsigned int month);
	bool					setYear(unsigned int year);
};
#endif