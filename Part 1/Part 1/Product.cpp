#include "Product.h"
#include "Seller.h"

#include <iostream>
using namespace std;

Product::Product(char* name, double price, int serial, eCategory category, Seller* seller, int indAtSeller, bool& check)	//	Constructor
{
	bool nameCheck=setName(name);
	bool priceCheck=setPrice(price);
	setSerial(serial);
	bool catCheck=setCategory(category);

	this->sellerOfProduct = seller;
	this->indAtSeller = indAtSeller;

	if (!nameCheck || !priceCheck || !catCheck || sellerOfProduct==nullptr || indAtSeller <0)
		check = false;
	else
		check = true;
}//Product constructor

Product::~Product()		//	Destructor
{
	delete name;
}
 // ----------------- GETTERS ----------------- //
const char* Product::getName() const
{
	return name;
}
double Product::getPrice() const
{
	return price;
}
int Product::getSerial() const
{
	return serial;
}
Product::eCategory Product::getCategory() const
{
	return category;
}
const Seller*	Product::getSeller()		const
{
	return sellerOfProduct;
}

void Product::showProduct() const
{
	cout << "Product: " << name << endl;
	cout << "Price: " << price << endl;
	cout << "Serial Number: " << serial << endl;
	cout << "Category: " << eCategoryNames[category] << endl;
	cout << "Seller: " << sellerOfProduct->getUsername() << endl;
	cout << endl;
}



// ----------------- SETTTERS ----------------- //
bool Product::setName(const char* name)
{
	// length validity check? \0?
	strcpy(this->name, name);
	return true;
}

bool Product::setPrice(const double price)
{
	if (price < 0)
		return false;
	this->price = price;
	return true;
}

bool Product::setSerial(int serial)
{
	this->serial = serial;
	return true;
}

bool Product::setCategory(Product::eCategory category)
{
	if (category < 0 || category>3)
		return false;

	this->category = category;
	return true;
}