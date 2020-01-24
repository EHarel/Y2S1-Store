#include "Cart.h"
#include "Product.h"
#include "ValidationHelper.h"


// ----------------- C'TORS AND D'TOR ----------------- //
Cart::Cart(const Cart & other)
{
	*this = other;
}
Cart::Cart(Cart && other) : m_cart(move(other.m_cart))
{
	m_cost = other.m_cost;
	m_cart_owner = other.m_cart_owner;
	other.m_cart_owner = nullptr;
}


void Cart::showCart() const
{
	if (m_cart.empty())
	{
		cout << "Cart empty. Nothing to show.\n\n";
		return;

	}

	vector<const Product*>::const_iterator	itr = m_cart.begin();
	vector<const Product*>::const_iterator	itr_end = m_cart.end();


	for (int i=1; itr != itr_end; ++itr, ++i)
	{
		cout << "Cart product " << i << endl;
		cout << **itr << endl;
	}
}
bool Cart::addToCart(const Product& product)
{
	ValidationHelper::ManageSize<const Product*>(m_cart); // Check and increase the size if needed

	m_cart.push_back(&product);
	m_cost = m_cost + product.getPrice();
	return true;
}
void Cart::emptyCart()
{
	m_cart.clear();
	m_cost = 0;
}

const Product * Cart::operator[](int i) const
{
	if(i<0||i>=(int)m_cart.size())
		return nullptr;
	return m_cart[i];
}

const Cart & Cart::operator=(const Cart & other)
{
	if (this != &other)
	{
		m_cart.clear();
		m_cart.reserve(other.m_cart.capacity());
		m_cart = other.m_cart;

		this->m_cost = other.m_cost;
		this->m_cart_owner = other.m_cart_owner;

		vector<const Product*>::const_iterator	itr = m_cart.begin();
		vector<const Product*>::const_iterator	itr_end = m_cart.end();

		for (; itr != itr_end; ++itr)
			m_cart.push_back(*itr); 
	}
	return *this;
}
ostream& operator<<(ostream& os, const Cart& cart)
{
	if (cart.m_cart.empty())
	{
		os << "Cart is empty. Nothing to print. Begone!\n";
		return os;
	}

	vector<const Product*>::const_iterator	itr = cart.m_cart.begin();
	vector<const Product*>::const_iterator	itr_end = cart.m_cart.end();

	for (; itr != itr_end; ++itr)
	{
		os << **itr << endl;
	}
	
	os << "Total cost: " << cart.m_cost << endl;
	return os;
}