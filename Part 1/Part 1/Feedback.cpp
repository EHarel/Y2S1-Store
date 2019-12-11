#include "Feedback.h"
#include "Product.h"
#include "Buyer.h"
#include <iostream>
using namespace std;

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

// ----------------- GETTERS ----------------- //

const Date& Feedback::getDate() const
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

void Feedback::showFeedback()				const
{
	cout << "Feedback about " << reviewedProduct->getName() << " by user " << feedbackGiver->getUsername() << ":\n";
	cout << appraisal << endl;
	date.show();
	cout << endl;
}


// ----------------- SETTERS ----------------- //

bool Feedback::updateAppraisal(char* newFeedback, const char* feedbackGiver, const Date& newdate)
{
	if (strcmp(this->feedbackGiver->getUsername(), feedbackGiver) != 0)
		return false;

	this->date = newdate;
	delete[]appraisal;
	appraisal = strdup(newFeedback);
	return true;
}


