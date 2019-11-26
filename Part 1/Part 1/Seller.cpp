#include "Seller.h"
#include "Product.h"
#include "Address.h"

#include <iostream>
using namespace std;


Seller::Seller(char* name, int password, Address* address)
{
	changeUsername(name);
	resetPassword(password);
	setAddress(address);

	feedPhySize = 10;
	feedLogSize = 0;
	feedbacks = new Feedback*[feedPhySize];
	if (!feedbacks)
		cout << "Error: Failed to allocate space for feedbacks for Seller.\n";

	catPhySize = 10;
	catLogSize = 0;
	catalog = new Product*[catPhySize];
	if (!catalog)
		cout << "Error: Failed to allocate space for merchandise for Seller.\n";
}//constructor

Seller::~Seller()
{
	int i = 0;
	for (i = 0; i < feedLogSize; i++)
		delete feedbacks[i];
	delete[]feedbacks;

	for (i = 0; i < catLogSize; i++)
		delete catalog[i];
	delete[]catalog;
}



// ------------------------------- GETTERS ------------------------------- //

const char* Seller::getUsername() const
{
	return username;
}
const Address* Seller::getAddress() const
{
	return address;
}
const Product* Seller::getProduct(const char* name, int& indexAtSeller)	const
/*
A seller offers two options of retrieving a product of his;
Either searching by product name, or by index at his store.

IDEA: change index to something better. Perhaps private serial?
*/
{
	if (indexAtSeller != UNKNOWN_INDEX)
	{
		return catalog[indexAtSeller];
	}
	for (int i = 0; i < catLogSize; i++)
	{
		if (strcmp(catalog[i]->getName(), name) == 0)
		{
			indexAtSeller = i;
			return catalog[i];
		}
	}
	indexAtSeller = NOT_FOUND;
	return nullptr;	//	Didn't find the product.
}
int Seller::getCatalogLogSize() const
{
	return catLogSize;
}


void Seller::showSeller() const
{
	cout << "Username: " << username << endl;
	address->showAddress();
	cout << endl;
}

void Seller::showAllMerchandise() const
{
	for (int i = 0; i < catLogSize; i++)
	{
		cout << "Item " << i + 1 << endl;
		catalog[i]->showProduct();
		cout << endl;
	}
}

bool Seller::passwordCheck(int password) const
// This function receives a password and compares it with the user's password, to see if it is the same.
{
	if(this->password==password)
		return true;
	else
		return false;
}


// ------------------------------- SETTERS ------------------------------- //

bool Seller::changeUsername(const char* username)
{
	strcpy(this->username, username);
	return true;
}

bool Seller::resetPassword(const int password)
{
	//int verification;
	//cout << "Please enter current passowrd:\n";
	//cin >> verification;
	//if (verification != this->password)
	//{
	//	cout << "Passwords do not match.\n";
	//	return false;
	//}
	if (password < 0)
		return false;		//	cannot enter negative number
	this->password = password;
	return true;
}
bool Seller::setAddress(Address* address)
{
	this->address = address;
	return true;
}

bool Seller::addFeedback(Feedback* feedback)
{
	if (!feedback)
		return false;

	if (feedLogSize == feedPhySize)
		if (!increaseFeedbackSize())	//	failed to increase size
			return false;

	feedbacks[feedLogSize++] = feedback;
}
bool Seller::increaseFeedbackSize()
{
	feedPhySize *= 2;
	Feedback** temp = new Feedback*[feedPhySize];
	if (!temp)		//	Failed to allocate.
		return false;
	for (int i = 0; i < feedLogSize; i++)
		temp[i] = feedbacks[i];
	delete[]feedbacks;
	feedbacks = temp;
	return true;
}

bool Seller::addProductToMerch(Product* product)
{
	if (!product)
		return false;
	
	if (catLogSize == catPhySize)
		if (!increaseMerchandiseSize())
			return false;

	catalog[catLogSize++] = product;
	return true;
}
bool Seller::increaseMerchandiseSize()
{
	catPhySize *= 2;
	Product** temp = new Product*[catPhySize];
	if (!temp)		//	Failed to allocate.
		return false;
	for (int i = 0; i < feedLogSize; i++)
		temp[i] = catalog[i];
	delete[]catalog;
	catalog = temp;
	return true;
}