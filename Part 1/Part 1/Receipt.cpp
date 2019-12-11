#include "Product.h"
#include "Buyer.h"
#include "Receipt.h"
#include <string.h>
#include "Seller.h"

#include <iostream>
using namespace std;

Receipt::Receipt(const Cart& cart)
/*
The constructor of Receipt receives the buyer's cart, and copies from it all the products.
*/
{
	numOfProducts = cart.getLogSize();
	totalCost = cart.getCost();
	buyer = cart.getOwner();

	products = new const Product*[numOfProducts];
	feedbacks = new const Feedback*[numOfProducts];
	const Product** cartProducts = cart.getProducts();
	for (int i = 0; i < numOfProducts; i++)
	{
		products[i] = new const Product((*cartProducts[i]));
		if (!products[i])
			exit(1);
		feedbacks[i] = nullptr;
	}

}

Receipt::~Receipt()
{
	for (int i = 0; i < numOfProducts; i++)
	{
		delete products[i];
		delete feedbacks[i];
	}
	delete[]products;
	delete[]feedbacks;
}


const Product* Receipt::getProductByIndex(int i)		const
{
	if (i<0 || i>numOfProducts)	//	Index out of range.
		return nullptr;
	return products[i];
}


int Receipt::getNumOfProducts()						const
{
	return numOfProducts;
}
const Product** Receipt::getProducts()				const
{
	return products;
}





bool Receipt::addFeedbackToProd(const char* prodName, const char* sellerName, const Feedback* feedback)
{
	for(int i = 0; i < numOfProducts; i++)
	{
		if (strcmp(products[i]->getName(), prodName) == 0) // Check product name match.
		{
			if (strcmp(products[i]->getSeller()->getUsername(), sellerName) == 0) // Check seller name match (could have several sellers selling similar products).
			{
				if (feedbacks[i] != nullptr) // Feedback was already given.
					return false;
				feedbacks[i] = feedback;
				return true;
			}
		}
	}
	return false;
}