#include "Wishlist.h"
#include "Product.h"
#include <iostream>
using namespace std;

Wishlist::Wishlist()
{
	phySize = 10;
	logSize = 0;
	products = new const Product*[phySize];
	if (!products)
		exit(1);
	cartIndication = new bool[phySize];
	for (int i = 0; i < phySize; i++)
		cartIndication[i] = false;
}

Wishlist::~Wishlist()
{
	delete[]products;
}

bool Wishlist::showWishlist() const
{
	if (logSize == 0)	//	No items in wishlist.
	{
		cout << "Wishlist empty.\n\n";
		return false;
	}
	for (int i = 0; i < logSize; i++)
	{
		cout << "Wishlisted product " << i + 1 << endl;
		products[i]->showProduct();
		cout << endl;
	}
	return true;
}

const Product*	Wishlist::getProduct(int index) const
{
	if (index<0 || index>logSize)
		return nullptr;
	return products[index];
}

bool Wishlist::isWishlistedProduct(int serial)	const
{
	for (int i = 0; i < logSize; i++)
	{
		if (products[i]->getSerial() == serial)
			return true;
	}
	return false;
}

int Wishlist::getLogSize() const
{
	return logSize;
}

bool Wishlist::addToWishlist(const Product* product)		//	This function receives a chosen product and adds it to the cart.
{
	if (product == nullptr)
		return false;
	if (logSize == phySize)
		if (increaseWishlistSize() == false)
			return false;
	products[logSize] = product;
	cartIndication[logSize] = false;
	logSize++;
	return true;
}
bool Wishlist::increaseWishlistSize()
{
	phySize *= 2;
	const Product** temp = new const Product*[phySize];		//	Const because the cart is not able to change the product.
	bool* tempBool = new bool[phySize];
	if (!temp)		//	Failed to allocate.
		return false;

	for (int i = 0; i < logSize; i++)
	{
		temp[i] = products[i];
		tempBool[i] = cartIndication[i];
	}

	delete[]products;
	products = temp;
	delete[]cartIndication;
	cartIndication = tempBool;
	return true;
}

void Wishlist::changeProductCartStatus(int index)
{
	if (index<0 || index > logSize)
		return;
	cartIndication[index] = true;

}

bool Wishlist::getCartIndication(int i)	const
{
	return cartIndication[i];
}

void Wishlist::cleanNullptrs()
// Go over Wishlist and "clean" all the items checked for checkout. Use while loop because we don't want to always advance i.
{
	int i = 0;
	while(i<logSize)
	{
		if (cartIndication[i] == true) //	Location of a purchased item - need to "clear" it from the array
		{
			products[i] = products[logSize - 1];
			products[logSize - 1] = nullptr;
			cartIndication[i] = cartIndication[logSize - 1];
			cartIndication[logSize - 1] = false;
			logSize--;
			//	We don't advance the index because we must check the item we took from the end
		}
		else
			i++; //	Advance only if the product at the location is valid (that is, not nullptr)
	}
}

const Buyer* Wishlist::getOwner()	const
{ 
	return wishlistOwner; 
}