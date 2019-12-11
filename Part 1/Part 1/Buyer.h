/* Notes:
	getPassword
		Doesn't exist, intentionally.
*/
#pragma warning(disable:4996)
#ifndef __BUYER_H
#define __BUYER_H

#include "Wishlist.h"
#include "Cart.h"
#include "Address.h"
#include "PurchaseHistory.h"


const int EMPTY = -1;	//	For the index array. 

class Buyer
{
private:
	char*						username;
	int							password;
	Address						address;
	Wishlist					wishlist;
	Cart						cart;
	PurchaseHistory				history;	//	History of all past purchases. It contains receipts.

public:
// Constructors and Destructor
	Buyer() = delete;
	Buyer(const char* name, int password, const Address& address);
	Buyer(const Buyer&) = delete;	//	No copying of buyers. Each account is unique.
	~Buyer();

//	Getters
	const char*					getUsername()					const;
	bool						passwordCheck(int password)		const;
	void						showBuyer()						const;

	const Address&				getAddress()					const;
	Address&					getAddress();
	const Wishlist&				getWishlist()					const;
	Wishlist&					getWishlist();
	const Cart&					getCart()						const;
	Cart&						getCart();
	const PurchaseHistory&		getPurchaseHistory()			const;
	PurchaseHistory&			getPurchaseHistory();

//	Setters
	bool						changeUsername(const char* username);
	bool						resetPassword(int newPassword, int currentPasswordVerification);
	bool						setAddress(const Address& address);	

	bool						proceedToCheckout(Receipt* receipt);	//	 This function pays for the items in the Checkout line, and removes them from the wishlist.

	friend class System;
};
#endif 

