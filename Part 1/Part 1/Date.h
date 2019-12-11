#pragma warning(disable:4996)
#ifndef __DATE_H
#define __DATE_H

class Date
{
private:
	unsigned int			day;
	unsigned int			month;
	unsigned int			year;

public:
	Date() = delete;
	Date(unsigned int day, unsigned int month, unsigned int year);

// Const methods
	inline unsigned int		getDay()		const;
	inline unsigned int		getMonth()		const;
	inline unsigned int		getYear()		const;
	void					show()			const;

// Non-const methods
	bool					setDay(unsigned int day);
	bool					setMonth(unsigned int month);
	bool					setYear(unsigned int year);
};
#endif