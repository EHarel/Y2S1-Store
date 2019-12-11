#pragma warning(disable:4996)
#ifndef __BUYRECEIPT_H
#define __BUYRECEIPT_H

#include "Cart.h"

class Product;
class Seller;
class Buyer;
class Feedback;

class Receipt
{
private:
	const Product**			products;	//	Array of purchased products.
	const Feedback**		feedbacks;	//	Feedbacks the buyer has left for these products.
	// CHANGE TO CONST! THE FEEDBACK
	int						numOfProducts;
	double					totalCost;
	const Buyer*			buyer;

public:
// Constructors and Destructor
	Receipt() = delete;
	Receipt(const Cart& cart);
	~Receipt();

// Const methods
	const Product*			getProductByIndex(int i)		const;
	int						getNumOfProducts()						const;
	const Product**			getProducts()				const;

// Non-const methods
	const Feedback**		getFeedbacks() const { return feedbacks; }
	bool					addFeedbackToProd(const char* prodName, const char* sellerName, const Feedback* feedback);
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

Setters
	No setters for numOfProducts and totalCost, to make them unchangeable.
	Cannot initalize them with init line because they rely on data from the Cart which is also sent to the constructor.
*/