#pragma warning(disable:4996)
#ifndef __FEEDBACK_H
#define __FEEDBACK_H

#include "Date.h"
#include <string.h>

class Buyer;
class Product;

static const int FEED_LEN = 150;

class Feedback
{
private:
	const Product*	reviewedProduct;
	const Buyer*	feedbackGiver;
	char*			appraisal;
	Date			date;

public:
// Constructors and Destructor
	Feedback() = delete;
	Feedback(const Date& date, const Buyer* feedbackGiver, char* appraisal, const Product* product);
	Feedback(const Feedback&) = delete;
	~Feedback(); 

// Const methods
	const Date&				getDate()					const;
	const Buyer*			getFeedbackGiver()			const;
	const char*				getAppraisal()				const;
	void					showFeedback()				const;
	static const int		getFeedLen()		{ return FEED_LEN; }

// Non-const methods
	bool					updateAppraisal(char* newFeedback, const char* feedbackGiver, const Date& newdate);
};
#endif 

/* Notes:

updateAppraisal
	No setters for date and feedback giver. We don't want these to be changed.
	However, you can change the appraisal you have given, and the method requires username verification, as well as a new date.

*/