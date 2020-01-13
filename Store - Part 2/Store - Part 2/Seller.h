#pragma warning(disable:4996)
#ifndef __Seller_H
#define __Seller_H

#include "User.h"
#include "Feedback.h"

class Buyer;
class Receipt;


class Seller : virtual public User
{
protected:
	const Feedback**		m_feedbacks;							//	dynamically allocated array of feedbacks received
	int						m_feedLogSize, m_feedPhySize;			//	sizes for the feedback array
	Product**				m_catalog;								//	dynamically allocated array of products
	int						m_catLogSize, m_catPhySize;

	static int				seller_count;

// Private Methods
	bool					increaseFeedbackSize();
	bool					increaseMerchandiseSize();

public:
// C'tors and D'tor
	Seller() = delete;	
	Seller(const char* username, int password, const Address& address);
	Seller(const Seller&);
	Seller(Seller&&);
	virtual ~Seller();

//	Const methods
	inline int				getCatalogLogSize()					const	{ return m_catLogSize; }
	const Product*			getProduct(const char* name)		const;	
	const Product*			getProduct(int serial)				const;
	inline int				GetSellerCount()					const	{ return seller_count; }
	void					showSeller()						const;
	void					showAllMerchandise()				const;
	void					showAllFeedbacks()					const;

//	Non-const methods
	bool					addFeedback(const Feedback* feedback);
	bool					addProductToMerch(Product* product);




	virtual void			toOs(ostream& os)				const	override;



	friend class System;
};
#endif