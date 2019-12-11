#include "Cart.h"
#include "Product.h"

#include <iostream>
using namespace std;

Cart::Cart()
{
	phySize = 10;
	logSize = 0;
	cart = new const Product*[phySize];
	if (!cart)
		exit(1);

	cost = 0;
}

Cart::~Cart()
{
	delete[]cart;
}

double Cart::getCost() const
{
	return cost;
}

const Product** Cart::getProducts() const	
{
	return cart;
}
int Cart::getLogSize() const
{
	return logSize;
}
const Buyer* Cart::getOwner() const
{
	return cartOwner;
}

void Cart::showCart() const
{
	if (logSize == 0)	//	No items in cart.
	{
		cout << "Cart empty.\n\n";
		return;
	}
	for (int i = 0; i < logSize; i++)
	{
		cout << "Cart product " << i + 1 << endl;
		cart[i]->showProduct();
		cout << endl;
	}
}

bool Cart::addToCart(const Product* product)
{
	if (!product)
		return false;
	if (logSize == phySize)
		if (increaseCartSize() == false)
			return false;
	cart[logSize] = product;
	logSize++;
	cost = cost + product->getPrice();
	return true;
}
bool Cart::increaseCartSize()
{
	phySize *= 2;
	const Product** temp = new const Product*[phySize];
	if (!temp)
		return false;
	for (int i = 0; i < logSize; i++)
		temp[i] = cart[i];
	delete[]cart;
	cart = temp;
	return true;
}

void Cart::emptyCart()
{
	for (int i = 0; i < logSize; i++)
	{
		cart[i] = nullptr;
	}
	logSize = 0;
	cost = 0;
}

