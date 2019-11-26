#include "Feedback.h"

Feedback::Feedback(Date* date, const Buyer* feedbackGiver, char* appraisal) : date(this->date)	// not sure 'bout that
{
	setDate(date);
	setFeedbackGiver(feedbackGiver);
	setAppraisal(appraisal);
}

// ----------------- GETTERS ----------------- //

Date Feedback::getDate() const
{
	return this->date;
}

const Buyer* Feedback::getFeedbackGiver() const
{
	return this->feedbackGiver;
}

const char* Feedback::getAppraisal() const
{
	return this->appraisal;
}

// ----------------- SETTERS ----------------- //

bool Feedback::setDate(Date* newDate)
{
	this->date = *newDate;	// shallow copy?
	return true;
}

bool Feedback::setFeedbackGiver(const Buyer* giver)
{
	this->feedbackGiver = giver;
	return true;
}

bool Feedback::setAppraisal(char* newAppraisal)
{
	if (strlen(newAppraisal) >= FEED_LEN)		// check if new feedback length is over FEED_LEN- return false
		return false;
	else
	{
		strcpy(this->appraisal, newAppraisal);
		return true;
	}
}