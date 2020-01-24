#pragma warning(disable:4996)
#ifndef __Seller_H
#define __Seller_H

#include "User.h"
#include "Feedback.h"
#include <vector>

class Buyer;
class Receipt;

class Seller : virtual public User
{
protected:
	vector<Product*>		m_catalog;
	vector<const Feedback*> m_feedbacks;

	static int				seller_count;

public:
// C'tors and D'tor
							Seller() = delete;	
							Seller(const string& username, int password, const Address& address) : User(username, password, address) { ++seller_count; }
							Seller(const Seller&) = delete; // No copying of users.
							Seller(Seller&&) = delete;
							Seller(ifstream& in) : User(in) { ++seller_count; }
	virtual					~Seller() { --seller_count; }

//	Getters
	inline int				getCatalogLogSize()					const	{ return m_catalog.size(); }
	const Product*			getProduct(const string& name)		const;	
	const Product*			getProduct(int serial)				const;
	inline static int		GetSellerCount()							{ return seller_count; }

//	Non-const methods
	void					addProductToMerch(Product& product);
	void 					addFeedback(const Feedback& feedback);

// Show Methods
	void					showSeller()						const;
	void					showAllMerchandise()				const;
	void					showAllFeedbacks()					const;
	virtual void			toOs(ostream& os)					const	override;

	const Seller&			operator=(const Seller& other) = delete;

	friend class System;
};
#endif