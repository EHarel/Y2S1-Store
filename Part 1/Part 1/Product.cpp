#include "Product.h"
#include "Seller.h"


int Product::latestSerialNum = 1000;

// ----------------- C'TORS AND D'TOR ----------------- //
Product::Product(char* name, double price, eCategory category, Seller* seller, int indAtSeller, bool& check)	//	Constructor
{
	this->m_name = strdup(name);
	bool nameCheck=setName(name);
	bool priceCheck=setPrice(price);
	bool catCheck=setCategory(category);

	this->m_seller = seller;
	this->m_indAtSeller = indAtSeller;

	m_serial = ++latestSerialNum;

	if (!nameCheck || !priceCheck || !catCheck || m_seller==nullptr || indAtSeller <0)
		check = false;
	else
		check = true;
}//Product constructor
Product::Product(const Product& other)
{
	m_name = strdup(other.m_name);
	m_price = other.m_price;
	m_serial = other.m_serial;
	m_category = other.m_category;
	m_seller = other.m_seller;
	m_indAtSeller = other.m_indAtSeller;
}
Product::Product(Product&& other)
{
	m_name = other.m_name;
	m_price = other.m_price;
	m_serial = other.m_serial;
	m_category = other.m_category;
	m_seller = other.m_seller;
	m_indAtSeller = other.m_indAtSeller;

	other.m_name = nullptr;
	other.m_seller = nullptr;
}
Product::~Product()	

{
	delete []m_name;
}


// ----------------- SETTERS ----------------- //
bool Product::setName(const char* name)
{
	// Product names can include numbers and other symbols. No need to check for invalid chars. We believe in freedom of branding expression.
	delete[]m_name;
	m_name = strdup(name);
	return true;
}
bool Product::setPrice(const double price)
{
	if (price < 0)
		return false;
	this->m_price = price;
	return true;
}
bool Product::setCategory(Product::eCategory category)
{
	if (category < 0 || category>3)
		return false;

	this->m_category = category;
	return true;
}


// ----------------- MISC ----------------- //
void Product::showProduct() const
{
	cout << "Product: " << m_name << endl;
	cout << "Price: " << m_price << endl;
	cout << "Serial Number: " << m_serial << endl;
	cout << "Category: " << eCategoryNames[m_category] << endl;
	cout << "Seller: " << m_seller->getUsername() << endl;
}