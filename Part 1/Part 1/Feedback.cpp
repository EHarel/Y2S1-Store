#include "Feedback.h"
#include "Buyer.h"

// ----------------- C'TORS AND D'TOR ----------------- //
Feedback::Feedback(const Date& date, const Buyer* feedbackGiver, char* appraisal, const Product* product) : date(date), appraisal(nullptr)
{
	this->feedbackGiver = feedbackGiver;
	this->appraisal = strdup(appraisal);
	this->reviewedProduct = product;
}
Feedback::~Feedback()
{
	delete []appraisal;
}


void Feedback::showFeedback()				const
{
	cout << "Feedback about " << reviewedProduct->getName() << " by user " << feedbackGiver->getUsername() << ":\n";
	cout << appraisal << endl;
	date.show();
	cout << endl;
}
bool Feedback::updateAppraisal(char* newFeedback, const char* feedbackGiver, const Date& newdate)
{
	if (strcmp(this->feedbackGiver->getUsername(), feedbackGiver) != 0)
		return false;

	this->date = newdate;
	delete[]appraisal;
	appraisal = strdup(newFeedback);
	return true;
}