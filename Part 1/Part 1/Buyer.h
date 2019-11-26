// Notes at the bottom of the page.
#pragma warning(disable:4996)
#ifndef __BUYER_H
#define __BUYER_H

#include "Product.h"
// class Product;

class Address;
class ReceiptBuyer;

const int EMPTY = -1;	//	For the index array. S

class Buyer
{
public:
	Buyer() = delete;
	Buyer(char* name, int password, Address* address);

public:
//	Getters
	const char* getUsername()							const;
	const Address* getAddress()							const;
	const Product** getWishlist()							const;
	int getCartLogSize()								const;
	bool Buyer::passwordCheck(int password)				const;

	void showBuyer()									const;
	bool showAllWishlistProducts()						const;

	const Product** getWishlistProductAddress(int index)		const;
	double getCurrentCheckoutCost()						const;
	int getWishLogSize()								const;
	const Product*** getCart()							const;	//	Items for check-out.
	int Buyer::getCheckoutLogSize()						const;

//	Setters
	bool changeUsername(const char* username);
	bool resetPassword(const int password);
	bool setAddress(Address* address);		//	QUESTION: can it be const address?

	bool addToWishlist(const Product* product);
	bool increaseWishlistSize();

	/*
	addToCheckout receives products that are meant to be in the wishlist,
	and adds them to an array of items to be checked out.
	It must also receive the index of the item in the wishlist,
	in order to check that the item truly is from the wishlist.
	This is because only wishlisted items can be chosen for checkout.
	*/
	bool addToCart(const Product** product);
	bool increaseCartSize();

	bool proceedToCheckout(ReceiptBuyer* receipt);	//	 This function pays for the items in the Checkout line, and removes them from the wishlist.
	bool increasePurchaseHistorySize();

	~Buyer();	//	DESTRUCTOR
private:
	char				username[LEN];
	int					password;
	Address*			address;

// Wishlist
	const Product**		wishlist;	//	this is an array of products that the buyer considers purchasing. Dynamically allocated
	int					wishLogSize, wishPhySize;		//	Variables to manage the dynamic cart array.

// Cart \ Checkout
	const Product***	cart;		//	Items to be purchased - the cart elements point to products in the wishlist. It's *** to make it easier to remove them from the wishlist at checkout.
	int					cartLogSize, cartPhySize;

	double				currCheckoutCost;
	ReceiptBuyer**		purchaseHistory;				//	an array of past purchases
	int					historyLogSize, historyPhySize;
	// Product* ownedProducts;	//	??? do we need this?
};
#endif 
/* Notes:


getPassword
	Doesn't exist, intentionally.
*/