#include "Wishlist.h"
#include "Product.h"
#include "ValidationHelper.h"
#include <iostream>
using namespace std;

// ----------------- C'TORS AND D'TOR ----------------- //
Wishlist::Wishlist()
{
	m_cost = 0;

	for (auto ind : m_cartIndication)
		ind = false;
}
Wishlist::Wishlist(const Wishlist& other) 
{
	*this = other;
}
Wishlist::Wishlist(Wishlist&& other) : m_products(NULL), m_cartIndication(NULL)
{
	m_products = move(other.m_products);
	m_cartIndication = move(other.m_cartIndication);
	m_cost = other.m_cost;
	m_buyer = other.m_buyer;
	other.m_buyer = nullptr;
}


// ----------------- GETTERS----------------- //
const Product*	Wishlist::getProduct(int index) const
{
	if (index<0 || index>=(int)m_products.size())
		return nullptr;
	return m_products[index];
}
bool Wishlist::getCartIndication(int i)	const
{
	if (i<0 || i>=(int)m_products.size())
		return false;
	return m_cartIndication[i];
}


// ----------------- MISC ----------------- //
bool Wishlist::showWishlist() const
{
	if (m_products.empty())	//	No items in wishlist.
	{
		cout << "Wishlist empty.\n\n";
		return false;
	}

	int i = 1;
	for (auto prod : m_products)
	{
		cout << "Wishlisted product " << i++ << endl;
		cout << *prod << endl;
	}
	return true;
}
void Wishlist::clearChosenProducts()
// Go over Wishlist and "clean" all the items checked for checkout. Use while loop because we don't want to always advance i.

{
	vector<const Product*>::iterator itr = m_products.begin();
	vector<const Product*>::iterator itr_end = m_products.end();
	vector<const Product*>::iterator itr_last_element = itr_end - 1;

	vector<bool>::iterator bool_itr = m_cartIndication.begin();
	vector<bool>::iterator bool_itr_end = m_cartIndication.end();
	vector<bool>::iterator last_bool_itr = bool_itr_end - 1;


	while (itr != itr_end)
	{
		if (*bool_itr == true)//	Location of a purchased item - need to "clear" it from the array
		{
			if (itr != itr_last_element)
			{
				itr = m_products.erase(itr);
				itr_end = m_products.end();
				itr_last_element = itr_end - 1; // Frankly, we don't know why this works like this, but it does. See known issues.
			}
			else
			{
				itr = m_products.erase(itr);
				itr_end = m_products.end();
			}

			bool_itr = m_cartIndication.erase(bool_itr);
		}
		else
		{
			++itr;
			++bool_itr;
		} //	Advance only if the product at the location is valid (that is, not nullptr)
	}
}
const Wishlist & Wishlist::operator=(const Wishlist& other)
{
	if (this != &other)
	{
		m_cost = other.m_cost;

		m_products.clear();
		m_cartIndication.clear();

		int size = other.m_products.size();
		m_products.reserve(size);
		m_cartIndication.reserve(size);

		m_buyer = other.m_buyer;

		vector<const Product*>::const_iterator itr = other.m_products.begin();
		vector<const Product*>::const_iterator itr_end = other.m_products.end();
		vector<bool>::const_iterator bool_itr = other.m_cartIndication.begin();

		for (; itr != itr_end; ++itr, ++bool_itr)
		{
			m_products.push_back(*itr);
			m_cartIndication.push_back(*bool_itr);
		}
	}
	return *this;
}
bool Wishlist::isWishlistedProduct(int serial)	const
{
	vector<const Product*>::const_iterator itr = m_products.begin();
	vector<const Product*>::const_iterator itr_end = m_products.end();

	for (; itr != itr_end; ++itr)
	{
		if ((*itr)->getSerial() == serial)
			return true;
	}
	return false;
}
bool Wishlist::addToWishlist(const Product* product)		//	This function receives a chosen product and adds it to the cart.
{
	if (product == nullptr)
		return false;

	ValidationHelper::ManageSize<const Product*>(m_products);
	ValidationHelper::ManageSize<bool>(m_cartIndication);

	m_products.push_back(product);
	m_cartIndication.push_back(false);
	m_cost = m_cost + product->getPrice();
	return true;
}
void Wishlist::changeProductCartStatus(int index)
{
	if (index<0 || index > (int)m_products.size())
		return;
	m_cartIndication[index] = true;

}

ostream & operator<<(ostream & os, const Wishlist & wl)
{
	if (wl.m_products.empty())
		os << "Wishlist is empty. This user desires nothing in life.\n";
	else
	{
		os << "Cost of all items in wishlist: " << wl.m_cost << endl << endl;
		os << "Wishlisted products: \n";

		vector<const Product*>::const_iterator itr = wl.m_products.begin();
		vector<const Product*>::const_iterator itr_end = wl.m_products.end();
		for(;itr!=itr_end;++itr)
			os << **itr << endl;
	}
	return os;
}