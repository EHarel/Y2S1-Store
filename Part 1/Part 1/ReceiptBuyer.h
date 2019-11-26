#pragma warning(disable:4996)
#ifndef __BUYRECEIPT_H
#define __BUYRECEIPT_H

class Product;
class Seller;
class Buyer;

class ReceiptBuyer
{
public:
	ReceiptBuyer() = delete;
	ReceiptBuyer(const Product*** cart, int cartSize, double totalCost, const Buyer* buyer);

	const Product* getProductByIndex(int i)		const;

	~ReceiptBuyer();
private:
	const Product**				products;	//	Array of purchased products.
	//	const Seller**			seller;	//	QUESTION: Do we need an array of sellers, or is it enough that each product links to the seller?
	//	const int					productsSize;	-> doesn't work! I wanted to make this unchangeable once it's initialized
	int productsSize;
		//const double				totalCost;	//	const? will this reasonably change?
	double totalCost;
	const Buyer*				buyer;
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
*/