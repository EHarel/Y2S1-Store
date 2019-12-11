#include "Buyer.h"
#include "Product.h"
#include "Address.h"
#include <string.h>
#include <iostream>
using namespace std;



Buyer::Buyer(const char* name, int password, const Address& address) : address(address)
{
	this->username = strdup(name);
	this->password = password;
}

Buyer::~Buyer()
{
	delete[]username;
}

// ------------------------------- GETTERS ------------------------------- //

const char*		Buyer::getUsername()					const
{
	return username;
}
const Address& Buyer::getAddress()						const
{
	return address;
}
Address& Buyer::getAddress()
{
	return address;
}
const Wishlist& Buyer::getWishlist()					const
{
	return wishlist;
}
Wishlist& Buyer::getWishlist()
{
	return wishlist;
}
const Cart& Buyer::getCart()							const
{
	return cart;
}
Cart& Buyer::getCart()
{
	return cart;
}
const PurchaseHistory& Buyer::getPurchaseHistory()		const
{
	return history;
}
PurchaseHistory& Buyer::getPurchaseHistory()
{
	return history;
}

void Buyer::showBuyer()									const
{
	cout << "Username: " << username << endl;
	address.showAddress();
	cout << endl;
}

bool Buyer::passwordCheck(int password)					const
// This function receives a password and compares it with the user's password, to see if it is the same.
{
	if (this->password == password)
		return true;
	else
		return false;
}



// ------------------------------- SETTERS ------------------------------- //

bool Buyer::changeUsername(const char* username)
{
	strcpy(this->username, username);
	return true;
}

bool Buyer::resetPassword(int newPassword, int currentPasswordVerification)
{
	if (currentPasswordVerification != password)
		return false;
	if (newPassword < 0)	//	Cannot enter negative number.
		return false;
	if (password < 0)
		return false;		//	cannot enter negative number
	this->password = password;
	return true;
}

bool Buyer::setAddress(const Address& other)
{
	address = other;
	return true;
}

bool Buyer::proceedToCheckout(Receipt* receipt)
{
	if (!receipt)
		return false;
	if (history.logSize == history.phySize)	//	No more space.
		if (!history.increasePurchaseHistorySize())	//	If failed to increase.
			return false;
	history.receipts[history.logSize++] = receipt;	//	Add receipt to history.

	wishlist.cleanNullptrs();
	cart.emptyCart();
	return true;
}



/*
Note 1
	Our purpose is to place nullptrs in the Wishlist, wherever there's a product we purchased.
	Eventually, we will "cut out" all these nullptrs in the array, by moving the pointers around,
	so that the array won't have any "fat" of nullptrs.
	We don't do this just yet, because the cart array still points to locations in the wishlist,
	where there are products we still need to buy.
	So only after this loop is done, we'll go over the Wishlist once again, separately,
	and remove all the nullptrs by moving pointers around.

*/