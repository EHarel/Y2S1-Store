#pragma warning(disable:4996)
#ifndef __DATE_H
#define __DATE_H

#include <iostream>
using namespace std;

class Date
{
private:
	unsigned int			m_day;
	unsigned int			m_month;
	unsigned int			m_year;

public:
// C'tors and D'tor
	Date() = delete;
	Date(int day, int month, int year);

// Const methods
	inline unsigned int		getDay()		const { return m_day; }
	inline unsigned int		getMonth()		const { return m_month; }
	inline unsigned int		getYear()		const { return m_year; }
	void					show()			const;

// Non-const methods
	bool					setDay(int day);
	bool					setMonth(int month);
	bool					setYear(int year);

	friend ostream&			operator<<(ostream& os, const Date& date);
};
#endif