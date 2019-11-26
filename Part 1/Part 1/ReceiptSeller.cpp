#include "ReceiptSeller.h"
#include <string.h>

ReceiptSeller::ReceiptSeller(const Product* product, const Buyer* buyer)
{
	strcpy(productName, product->getName());
	productPrice = product->getPrice();
	this->buyer = buyer;
}