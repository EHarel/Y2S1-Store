#pragma warning(disable:4996)
#ifndef __FEEDBACK_H
#define __FEEDBACK_H

#include "Product.h"
#include "Date.h"
#include <string.h>

class Buyer;


class Feedback
{
private:
	const Product*			reviewedProduct;
	const Buyer*			feedbackGiver;
	char*					appraisal;
	Date					date;

public:
// C'tors and D'tor
	Feedback() = delete;
	Feedback(const Date& date, const Buyer* feedbackGiver, char* appraisal, const Product* product);
	Feedback(const Feedback&) = delete;
	~Feedback(); 

// Const methods
	inline const Date&		getDate()				const	{ return date; }
	inline const Buyer*		getFeedbackGiver()		const	{ return feedbackGiver; }
	inline const char*		getAppraisal()			const	{ return appraisal; }
	void					showFeedback()			const;
		
// Non-const methods
	bool					updateAppraisal(char* newFeedback, const char* feedbackGiver, const Date& newdate);
};
#endif 

/* Notes:
updateAppraisal
	No setters for date and feedback giver. We don't want these to be changed.
	However, you can change the appraisal you have given, and the method requires username verification, as well as a new date.
*/