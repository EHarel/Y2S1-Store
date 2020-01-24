#include "Product.h"
#include "Seller.h"


int Product::latestSerialNum = 1000;

const string eCategoryNames[] = { "Children", "Electricity", "Office", "Clothing" }; 

// ----------------- C'TORS AND D'TOR ----------------- //
Product::Product(const string& name, double price, eCategory category, const Seller* seller, int indAtSeller) : m_seller(seller) //	Constructor
{
	setName(name);
	setPrice(price);
	setCategory(category);

	m_indAtSeller = indAtSeller;

	m_serial = ++latestSerialNum;
}// Product C'tor
Product::Product(const Product& other) : m_seller(other.m_seller)
{
	m_name = other.m_name;
	m_price = other.m_price;
	m_serial = other.m_serial;
	m_category = other.m_category;
	m_seller = other.m_seller;
	m_indAtSeller = other.m_indAtSeller;
}// Product Copy C'tor
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


// ----------------- SETTERS ----------------- //
bool Product::setName(const string& name)
{
	// Product names can include numbers and other symbols. No need to check for invalid chars. We believe in freedom of branding expression.
	m_name = name;
	return true;
}
bool Product::setPrice(const double price)
{
	if (price < 0)
		return false;

	m_price = price;
	return true;
}
bool Product::setCategory(Product::eCategory category)
{
	if (category < 0 || category>3)
		return false;

	m_category = category;
	return true;
}


// ----------------- MISC ----------------- //
void Product::showProduct() const
{
	cout << "Product: "			<< m_name << endl;
	cout << "\tPrice: "			<< m_price << endl;
	cout << "\tSerial Number: "	<< m_serial << endl;
	cout << "\tCategory: "		<< eCategoryNames[m_category] << endl;
	cout << "\tSeller: "		<< m_seller->getUsername() << endl;
}
ostream& operator<<(ostream& os, const Product& p)
{
	os << "Product: "			<< p.m_name << endl;
	os << "\tPrice: "			<< p.m_price << endl;
	os << "\tSerial Number: "	<< p.m_serial << endl;
	os << "\tCategory: "		<< eCategoryNames[p.m_category] << endl;
	os << "\tSeller: "			<< p.m_seller->getUsername() << endl;

	return os;
}