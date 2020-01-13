#include "Feedback.h"
#include "Buyer.h"

// ----------------- C'TORS AND D'TOR ----------------- //
Feedback::Feedback(const Date& date, const Buyer* feedbackGiver, char* appraisal, const Product* product) : date(date), appraisal(nullptr)
{
	this->feedbackGiver = feedbackGiver;
	this->appraisal = strdup(appraisal);
	this->reviewedProduct = product;
}
Feedback::Feedback(const Feedback & other) : date(date), appraisal(NULL)
{
	*this = other;
}
Feedback::Feedback(Feedback && other) : date(date), appraisal(NULL)
{
	*this = other;
	other.appraisal = nullptr;
}
Feedback::~Feedback()
{
	delete []appraisal;
}


void Feedback::showFeedback() const
{
	cout << "Feedback about " << reviewedProduct->getName() << " by user " << feedbackGiver->getUsername() << ":\n";
	cout << appraisal << endl;
	date.show();
	cout << endl;
}
const Feedback & Feedback::operator=(const Feedback & other)
{
	if (this != &other)
	{
		reviewedProduct = other.reviewedProduct;
		feedbackGiver = other.feedbackGiver;
		delete[]appraisal;
		appraisal = strdup(other.appraisal);
		if (appraisal == nullptr) // Allocation check
			exit(1);
	}
	return *this;
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

ostream & operator<<(ostream & os, const Feedback & fb)
{
	os << "Feedback of " << *(fb.reviewedProduct) << " by " << fb.feedbackGiver->getUsername() << endl; // # check what it prints for buyer, since we didn't implement << 
	os << "Feedback: " << *(fb.appraisal) << endl;
	os << "Given on date: " << fb.date << endl;
	return os;
}