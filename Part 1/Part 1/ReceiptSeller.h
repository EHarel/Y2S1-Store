#pragma warning(disable:4996)
#ifndef __RECEIPTSELL_H
#define __RECEIPTSELL_H

#include "Product.h"

class Product;
class Buyer;

class ReceiptSeller
{
public:
	ReceiptSeller() = delete;
	ReceiptSeller(const Product* product, const Buyer* buyer);


private:
	char			productName[LEN];
	double			productPrice;
	const Buyer*	buyer;
};
#endif