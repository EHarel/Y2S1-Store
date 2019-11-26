#include "Product.h"
#include "Buyer.h"
#include "ReceiptBuyer.h"


ReceiptBuyer::ReceiptBuyer(const Product*** cart, int cartSize, double totalCost, const Buyer* buyer)
{
	productsSize = cartSize;
	this->products = new const Product*[productsSize];
	if (!products)
		return;

	for (int i = 0; i < productsSize; i++)
	{
		products[i] = new const Product(*(*(cart[i])));
		if (!products[i])
			return;
	}

	this->totalCost = totalCost;
	this->buyer = buyer;
}

ReceiptBuyer::~ReceiptBuyer()
{
	for (int i = 0; i < productsSize; i++)
		delete products[i];
	delete[]products;
}


const Product* ReceiptBuyer::getProductByIndex(int i)		const
{
	if (i<0 || i>productsSize)	//	Index out of range.
		return nullptr;
	return products[i];
}