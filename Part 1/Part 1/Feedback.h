#pragma warning(disable:4996)
#ifndef __FEEDBACK_H
#define __FEEDBACK_H

const int FEED_LEN = 150;

#include "Date.h"
#include <string.h>

class Buyer;

class Feedback
{
public:
	Feedback() = delete;
	Feedback(Date* date, const Buyer* feedbackGiver, char* appraisal);

public:
	Date			getDate()					const;
	const Buyer*	getFeedbackGiver()			const;
	const char*		getAppraisal()				const;

	bool			setDate(Date* newDate);
	bool			setFeedbackGiver(const Buyer* giver);
	bool			setAppraisal(char* newFeedback);
private:
	Date			date;
	const Buyer*	feedbackGiver; // QUESTION: information about feedback provider - is it just a pointer to the customer, or the customer's details copied here?
	char			appraisal[FEED_LEN];
};
#endif 