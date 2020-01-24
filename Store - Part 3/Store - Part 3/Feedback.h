#pragma warning(disable:4996)
#ifndef __FEEDBACK_H
#define __FEEDBACK_H

#include "Product.h"
#include "Date.h"

class Buyer;

class Feedback
{
private:
	const Product&			m_reviewed_product;
	string					m_appraisal;
	const Buyer&			m_feedback_giver;
	Date					m_date;

public:
// C'tors and D'tor
	Feedback() = delete;
	Feedback(const Date& date, const Buyer& feedbackGiver, const string& appraisal, const Product& product);
	Feedback(const Feedback& other);
	Feedback(Feedback&& other);

// Const methods
	inline const Date&		getDate()				const	{ return m_date; }
	inline const Buyer&		getFeedbackGiver()		const	{ return m_feedback_giver; }
	inline const string&	getAppraisal()			const	{ return m_appraisal; }
	void					showFeedback()			const;
		
// Non-const methods
	bool					updateAppraisal(const string& newFeedback, const string& feedbackGiver, const Date& newdate);

//Operators
	friend ostream&			operator<<(ostream& os, const Feedback& fb);
};
#endif 

/* Notes:
updateAppraisal
	No setters for date and feedback giver. We don't want these to be changed.
	However, you can change the appraisal you have given, and the method requires username verification, as well as a new date.
*/