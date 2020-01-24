#pragma warning(disable:4996)
#ifndef __BUYER_H
#define __BUYER_H

#include "Wishlist.h"
#include "Cart.h"
#include "Receipt.h"
#include "User.h"
#include "PointerArray.h"
#include <vector>


class Buyer: virtual public User
{
protected:
	Wishlist						m_wishlist;
	Cart							m_cart;
	PointerArray<Receipt>			m_history;	//	History of all past purchases.
	//vector<Receipt*>				m_history;  // History of all past purchases.

	static int						buyer_count;

protected: // Copy and Move c'tor - We don't want to allow copying outside the system's inner uses


public:
// C'tors and D'tor
									Buyer() = delete;
									Buyer(const string& username, int password, const Address& address) : User(username, password, address), m_cart(this) { ++buyer_count; }
									Buyer(const Buyer& other) = delete; // No copying of users.
									Buyer(const Buyer&& other) = delete;
									Buyer(ifstream& in) : User(in), m_cart(&(*this)) { ++buyer_count; }
	virtual							~Buyer() { --buyer_count; }

//	Getters
	inline const Wishlist&			getWishlist()					const	{ return m_wishlist; }
	inline Wishlist&				getWishlist()							{ return m_wishlist; }
	inline const Cart&				getCart()						const	{ return m_cart; }
	inline Cart&					getCart()								{ return m_cart; }
	inline const PointerArray<Receipt>&	getPurchaseHistory()	const		{ return m_history; }
	inline PointerArray<Receipt>&			getPurchaseHistory()			{ return m_history; }
	inline static int				GetBuyerCount()							{ return buyer_count; }

//	Non-const Methods
	bool							Checkout(Receipt& receipt);	//	 This function pays for the items in the Checkout line, and removes them from the wishlist.

// Show Methods
	void							showBuyer()						const;
	void							ShowPurchasedItems()			const;
	virtual void					toOs(ostream& os)				const	override;

// Operators
	inline bool						operator>(const Buyer& other)	const { return m_wishlist.m_cost > other.m_wishlist.m_cost; }	// These operators compare the cost of each buyer's wishlist
	inline bool						operator>=(const Buyer& other)	const { return m_wishlist.m_cost >= other.m_wishlist.m_cost; }
	inline bool						operator==(const Buyer& other)	const { return m_wishlist.m_cost == other.m_wishlist.m_cost; }
	inline bool						operator<(const Buyer& other)	const { return m_wishlist.m_cost < other.m_wishlist.m_cost; }
	inline bool						operator<=(const Buyer& other)	const { return m_wishlist.m_cost <= other.m_wishlist.m_cost; }
	const Buyer&					operator=(const Buyer& other) = delete; // No copying of users.

	friend class System;
};
#endif 

