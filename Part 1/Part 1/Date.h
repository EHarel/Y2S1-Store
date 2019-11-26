#pragma warning(disable:4996)
#ifndef __DATE_H
#define __DATE_H

class Date
{
public:
	Date(unsigned int day, unsigned int month, unsigned int year);

	inline unsigned int getDay()		const;
	inline unsigned int getMonth()		const;
	inline unsigned int getYear()		const;

	bool setDay(unsigned int day);
	bool setMonth(unsigned int month);
	bool setYear(unsigned int year);

private:
	unsigned int	day;
	unsigned int	month;
	unsigned int	year;
};
#endif