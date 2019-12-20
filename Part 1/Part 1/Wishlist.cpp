#include "Wishlist.h"
#include "Product.h"
#include <iostream>
using namespace std;

// ----------------- C'TORS AND D'TOR ----------------- //
Wishlist::Wishlist()
{
	m_phySize = 10;
	m_logSize = 0;
	m_products = new const Product*[m_phySize];
	if (!m_products)
		exit(1);
	m_cartIndication = new bool[m_phySize];
	for (int i = 0; i < m_phySize; i++)
		m_cartIndication[i] = false;
}
Wishlist::~Wishlist()
{
	delete[]m_products;
}


// ----------------- GETTERS----------------- //
const Product*	Wishlist::getProduct(int index) const
{
	if (index<0 || index>m_logSize)
		return nullptr;
	return m_products[index];
}
bool Wishlist::getCartIndication(int i)	const
{
	if (i<0 || i>m_logSize)
		return false;
	return m_cartIndication[i];
}


// ----------------- MISC ----------------- //
bool Wishlist::showWishlist() const
{
	if (m_logSize == 0)	//	No items in wishlist.
	{
		cout << "Wishlist empty.\n\n";
		return false;
	}
	for (int i = 0; i < m_logSize; i++)
	{
		cout << "Wishlisted product " << i + 1 << endl;
		m_products[i]->showProduct();
		cout << endl;
	}
	return true;
}
void Wishlist::clearChosenProducts()
// Go over Wishlist and "clean" all the items checked for checkout. Use while loop because we don't want to always advance i.
{
	int i = 0;
	while (i < m_logSize)
	{
		if (m_cartIndication[i] == true) //	Location of a purchased item - need to "clear" it from the array
		{
			m_products[i] = m_products[m_logSize - 1];
			m_products[m_logSize - 1] = nullptr;
			m_cartIndication[i] = m_cartIndication[m_logSize - 1];
			m_cartIndication[m_logSize - 1] = false;
			m_logSize--;
			//	We don't advance the index because we must check the item we took from the end
		}
		else
			i++; //	Advance only if the product at the location is valid (that is, not nullptr)
	}
}
bool Wishlist::isWishlistedProduct(int serial)	const
{
	for (int i = 0; i < m_logSize; i++)
	{
		if (m_products[i]->getSerial() == serial)
			return true;
	}
	return false;
}
bool Wishlist::addToWishlist(const Product* product)		//	This function receives a chosen product and adds it to the cart.
{
	if (product == nullptr)
		return false;
	if (m_logSize == m_phySize)
		if (increaseWishlistSize() == false)
			return false;
	m_products[m_logSize] = product;
	m_cartIndication[m_logSize] = false;
	m_logSize++;
	return true;
}
bool Wishlist::increaseWishlistSize()
{
	m_phySize *= 2;
	const Product** temp = new const Product*[m_phySize];		//	Const because the cart is not able to change the product.
	bool* tempBool = new bool[m_phySize];
	if (!temp)		//	Failed to allocate.
		return false;

	for (int i = 0; i < m_logSize; i++)
	{
		temp[i] = m_products[i];
		tempBool[i] = m_cartIndication[i];
	}

	delete[]m_products;
	m_products = temp;
	delete[]m_cartIndication;
	m_cartIndication = tempBool;
	return true;
}
void Wishlist::changeProductCartStatus(int index)
{
	if (index<0 || index > m_logSize)
		return;
	m_cartIndication[index] = true;

}