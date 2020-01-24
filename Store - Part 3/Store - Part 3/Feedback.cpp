#include "Feedback.h"
#include "Buyer.h"

// ----------------- C'TORS AND D'TOR ----------------- //
Feedback::Feedback(const Date& date, const Buyer& feedbackGiver, const string& appraisal, const Product& product) : m_date(date), m_reviewed_product(product), m_feedback_giver(feedbackGiver)
{
	m_appraisal = appraisal;
}
Feedback::Feedback(const Feedback & other) : m_date(other.m_date), m_reviewed_product(other.m_reviewed_product), m_feedback_giver(other.m_feedback_giver)
{
	m_appraisal = other.m_appraisal;
}
Feedback::Feedback(Feedback && other) : m_date(move(m_date)), m_reviewed_product(other.m_reviewed_product), m_feedback_giver(other.m_feedback_giver)
{
	m_appraisal = other.m_appraisal;
}

void Feedback::showFeedback() const
{
	cout << "Feedback about " << m_reviewed_product.getName() << " by user " << m_feedback_giver.getUsername() << ":\n";
	cout << m_appraisal << endl;
	cout << m_date << endl;
}
bool Feedback::updateAppraisal(const string& new_feedback, const string& buyer_attempting_to_change, const Date& newdate)
{
	if (m_feedback_giver.getUsername() == buyer_attempting_to_change) // Check that the person trying to change the feedback is the one who gave it in the first place
		return false;
	m_date = newdate;

	m_appraisal = new_feedback;

	return true;
}

ostream & operator<<(ostream & os, const Feedback & fb)
{
	os << "Feedback of " << fb.m_reviewed_product.getName() << " by " << fb.m_feedback_giver.getUsername() << endl; 
	os << "Feedback: " << fb.m_appraisal << endl; 
	os << "Given on date: " << fb.m_date << endl;
	return os;
}