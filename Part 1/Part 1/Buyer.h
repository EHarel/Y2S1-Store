#pragma warning(disable:4996)
#ifndef __BUYER_H
#define __BUYER_H

#include "Wishlist.h"
#include "Cart.h"
#include "Address.h"
#include "PurchaseHistory.h"

class Buyer
{
private:
	char*							username;
	int								password;
	Address							address;
	Wishlist						wishlist;
	Cart							cart;
	PurchaseHistory					history;	//	History of all past purchases. It contains receipts.

public:
// C'tors and D'tor
	Buyer() = delete;
	Buyer(const char* name, int password, const Address& address);
	Buyer(const Buyer&) = delete;	//	No copying of buyers. Each account is a unique snowflake.
	~Buyer();

//	Getters
	inline const char*				getUsername()					const	{ return username; }
	inline bool						passwordCheck(int password)		const	{ return this->password == password; }
	inline const Address&			getAddress()					const	{ return address; }
	inline Address&					getAddress()							{ return address; }
	inline const Wishlist&			getWishlist()					const	{ return wishlist; }
	inline Wishlist&				getWishlist()							{ return wishlist; }
	inline const Cart&				getCart()						const	{ return cart; }
	inline Cart&					getCart()								{ return cart; }
	inline const PurchaseHistory&	getPurchaseHistory()			const	{ return history; }
	inline PurchaseHistory&			getPurchaseHistory()					{ return history; }
	void							showBuyer()						const;


//	Non-const Methods
	bool							changeUsername(const char* username);
	bool							resetPassword(int newPassword, int currentPasswordVerification);
	bool							setAddress(const Address& address);	
	bool							proceedToCheckout(Receipt* receipt);	//	 This function pays for the items in the Checkout line, and removes them from the wishlist.

	friend class System;
};
#endif 

