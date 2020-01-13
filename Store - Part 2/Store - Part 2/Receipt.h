#pragma warning(disable:4996)
#ifndef __BUYRECEIPT_H
#define __BUYRECEIPT_H

#include "Cart.h"
#include <string.h>
#include <iostream>
using namespace std;

class Product;
class Seller;
class Buyer;
class Feedback;

class Receipt
{
private:
	const Product**				products;	//	Array of purchased products.
	const Feedback**			feedbacks;	//	Feedbacks the buyer has left for these products. 
	int							numOfProducts;
	double						totalCost;
	const Buyer*				buyer;

public:
// C'tors and D'tor
	Receipt() = delete;
	Receipt(const Cart& cart);
	Receipt(const Receipt& other);
	Receipt(Receipt&& other);
	~Receipt();

// Const methods
	inline int					getNumOfProducts()							const	{ return numOfProducts; }
	inline const Product**		getProducts()								const	{ return products; }
	inline const Feedback**		getFeedbacks()								const	{ return feedbacks; }
	const Product*				GetProduct(int index)						const;	//	Get by index
	const Product*				GetProduct(const char* product_name, const char* seller_name)	const;	//	Get by product and seller names
	bool						LeftFeedbackForProduct(int index)			const; // Check if already left feedback for specific product
	bool						LeftFeedbackForProduct(const Product* prod)	const; // Check if already left feedback for specific product


// Operators
	const Receipt&				operator=(const Receipt& other);
	friend ostream&				operator<<(ostream& os, const Receipt& rec);

// Non-const methods
	bool						addFeedbackToProd(const char* prodName, const char* sellerName, const Feedback* feedback);
};
#endif 

/*
Constructor:
	This class receives from a Buyer the following:
	-	checkoutItems - an array of all the items the buyer chose for checkout, and its size.
		The constructor allocates an array of similar size,
		and then COPIES all the products.
		It does not keep pointers to the actual product,
		meaning the Buyer has his own copy of the product.
		This makes them independent - say, if a seller removes the item.
	-	totalCost

Fields
	Access to sellers of products is possible through the products themselves,
	since the class Product has a pointer to the seller of said product.

	Feedback Array:
		Every time the buyer creates/leaves feedback for a seller,
		the system also adds his feedback in his purchase history.
		This allows the buyer to also keep track of the feedback he himself has left.
		It also shows if he left feedback for a specific item or not.

Setters
	No setters for numOfProducts and totalCost, to make them unchangeable. A receipt is meant to be permanent, as it is now.
	Cannot initalize them with init line because they rely on data from the Cart which is also sent to the constructor.
*/