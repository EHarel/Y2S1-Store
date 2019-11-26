/*
This is an auxiliary, created originally for the function meant to add a product to a buyer's wishlist.
Its purpose is to gather together all the different sellers of a certain item, 
with matching idexes for the location of the product at each seller's merchandise array.

Note: we considered doing this (meaning, connecting all the sellers of a certain product) via Linked List.
But since we haven't yet learned how to create Linked Lists in C++, we chose to use this class with simple arrays.
*/

#pragma warning(disable:4996)
#ifndef __PRODSELL_H
#define __PRODSELL_H

//#include "Product.h"
//const int LEN = 31;
//class Product;

#include "Seller.h"
//class Seller;


class ProductSellerList
{
public:
	ProductSellerList(int phySize, const char* name);

	bool showAvailableSellers() const;
	int getLogSize() const;
	const Product* getProduct(int index)	const;

	bool addAvailableSeller(const Seller* seller, int index);
	bool increaseAvailSellersArray();

	~ProductSellerList();
private:
	char				prodName[LEN];
	const Seller**		availableSellers;
	int					availLogSize, availPhySize;
	int*				indexArray;
	/*
	This is an index array. It contains the index of the product in the according seller's array.
	indexArray[i] is the location of the product at the merchandise of seller at availableSellers[i]
	*/
	// int				indLogSize, indPhySize;
};

#endif