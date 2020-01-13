#include "Cart.h"
#include "Product.h"


// ----------------- C'TORS AND D'TOR ----------------- //
Cart::Cart()
{
	m_phy_size = 10;
	m_log_size = 0;
	m_cart = new const Product*[m_phy_size];
	if (!m_cart)
		exit(1);

	m_cost = 0;
}
Cart::Cart(const Cart & other) : m_cart(NULL)
{
	*this = other;
}
Cart::Cart(Cart && other)
{
	*this = other;
	other.m_cart = nullptr;
}
Cart::~Cart()
{
	delete[]m_cart;
}



void Cart::showCart() const
{
	if (m_log_size == 0)	//	No items in cart.
	{
		cout << "Cart empty.\n\n";
		return;
	}
	for (int i = 0; i < m_log_size; i++)
	{
		cout << "Cart product " << i + 1 << endl;
		m_cart[i]->showProduct();
		cout << endl;
	}
}
bool Cart::addToCart(const Product* product)
{
	if (!product)
		return false;
	if (m_log_size == m_phy_size)
		if (increaseCartSize() == false)
			return false;
	m_cart[m_log_size] = product;
	m_log_size++;
	m_cost = m_cost + product->getPrice();
	return true;
}
bool Cart::increaseCartSize()
{
	m_phy_size *= 2;
	const Product** temp = new const Product*[m_phy_size];
	if (!temp)
		return false;
	for (int i = 0; i < m_log_size; i++)
		temp[i] = m_cart[i];
	delete[]m_cart;
	m_cart = temp;
	return true;
}
void Cart::emptyCart()
{
	for (int i = 0; i < m_log_size; i++)
	{
		m_cart[i] = nullptr;
	}
	m_log_size = 0;
	m_cost = 0;
}


const Product * Cart::operator[](int i) const
{
	if(i<0||i>m_log_size)
		return nullptr;
	return m_cart[i];
}

const Cart & Cart::operator=(const Cart & other)
{
	if (this != &other)
	{
		this->m_log_size = other.m_log_size;
		this->m_phy_size = other.m_phy_size;
		this->m_cost = other.m_cost;
		this->m_cart_owner = other.m_cart_owner;
		delete[] this->m_cart;
		this->m_cart = new const Product*[m_phy_size]; // # allocation check

		for (int i = 0; i < m_log_size; i++)
		{
			this->m_cart[i] = other.m_cart[i];
		}
	}
	return *this;
}
ostream& operator<<(ostream& os, const Cart& cart)
{
	if (cart.m_log_size == 0)
	{
		os << "Cart is empty. Nothing to print. Begone!\n";
		return os;
	}
	for (int i = 0; i < cart.m_log_size; i++)
		os << *(cart[i]) << endl;
	
	os << "Total cost: " << cart.m_cost << endl;
	return os;
}