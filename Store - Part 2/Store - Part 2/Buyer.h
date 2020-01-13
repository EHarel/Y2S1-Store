#pragma warning(disable:4996)
#ifndef __BUYER_H
#define __BUYER_H

#include "Wishlist.h"
#include "Cart.h"
#include "PurchaseHistory.h"
#include "User.h"


class Buyer: virtual public User
{
protected:
	Wishlist						m_wishlist;
	Cart							m_cart;
	PurchaseHistory					m_history;	//	History of all past purchases. It contains receipts.

	static int						buyer_count;


public:
// C'tors and D'tor
	Buyer() = delete;
	Buyer(const char* username, int password, const Address& address) : User(username, password, address) { ++buyer_count; }
	Buyer(const Buyer&);
	Buyer(const Buyer&&); // # check tirgul 6 with the cats, meow
	virtual ~Buyer(); // # what do we insert here?

//	Getters
	inline const Wishlist&			getWishlist()					const	{ return m_wishlist; }
	inline Wishlist&				getWishlist()							{ return m_wishlist; }
	inline const Cart&				getCart()						const	{ return m_cart; }
	inline Cart&					getCart()								{ return m_cart; }
	inline const PurchaseHistory&	getPurchaseHistory()			const	{ return m_history; }
	inline PurchaseHistory&			getPurchaseHistory()					{ return m_history; }
	void							showBuyer()						const;
	inline int						GetBuyerCount()					const	{ return buyer_count; }

//	Non-const Methods
	bool							proceedToCheckout(Receipt* receipt);	//	 This function pays for the items in the Checkout line, and removes them from the wishlist.



// Operators
	inline bool						operator>(const Buyer& other)	const { return m_wishlist.m_cost > other.m_wishlist.m_cost; }	// These operators compare the cost of each buyer's wishlist
	inline bool						operator>=(const Buyer& other)	const { return m_wishlist.m_cost >= other.m_wishlist.m_cost; }
	inline bool						operator==(const Buyer& other)	const { return m_wishlist.m_cost == other.m_wishlist.m_cost; }
	inline bool						operator<(const Buyer& other)	const { return m_wishlist.m_cost < other.m_wishlist.m_cost; }
	inline bool						operator<=(const Buyer& other)	const { return m_wishlist.m_cost <= other.m_wishlist.m_cost; }
	const Buyer&					operator=(const Buyer& other); // # bug! chapter 7 page 23
	// move operator=? #

	virtual void					toOs(ostream& os)				const	override;
	friend class System;
};
#endif 

