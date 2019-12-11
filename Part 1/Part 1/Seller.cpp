#include "Seller.h"
#include "Product.h"
#include "Address.h"
#include "Feedback.h"

#include <iostream>
using namespace std;


Seller::Seller(char* name, int password, const Address& address) : address(address)
{
	this->username = strdup(name);
	this->password = password;

	feedPhySize = 10;
	feedLogSize = 0;
	feedbacks = new const Feedback*[feedPhySize];
	for (int i = 0; i < feedPhySize; i++)
		feedbacks[i] = nullptr;
	if (!feedbacks)
		exit(1);

	catPhySize = 10;
	catLogSize = 0;
	catalog = new Product*[catPhySize];
	if (!catalog)
		exit(1);
}//constructor

Seller::~Seller()
{
	delete[]username;

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
const Address& Seller::getAddress() const
{
	return address;
}

const Product* Seller::getProduct(const char* name) const
{
	for (int i = 0; i < catLogSize; i++)
	{
		if (strcmp(catalog[i]->getName(), name) == 0)
			return catalog[i];
	}
	return nullptr;	//	Didn't find the product.
}

int Seller::getCatalogLogSize() const
{
	return catLogSize;
}


void Seller::showSeller() const
{
	cout << "Username: " << username << endl;
	address.showAddress();
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

void Seller::showAllFeedbacks()	const
{
	for (int i = 0; i < feedLogSize; i++)
	{
		cout << i+1 << ") "; 
		feedbacks[i]->showFeedback();
	}
	cout << endl;
}




// ------------------------------- NON-CONST METHODS ------------------------------- //

bool Seller::changeUsername(const char* username)
{
	strcpy(this->username, username);
	return true;
}

bool Seller::resetPassword(int newPassword, int currentPasswordVerification)
{
	if (currentPasswordVerification != password)
		return false;
	if (newPassword < 0)	//	Cannot enter negative number.
		return false;
	if (password < 0)
		return false;		//	cannot enter negative number
	this->password = password;
	return true;
}

bool Seller::setAddress(const Address& other)
{
	address = other;
	return true;
}

bool Seller::addFeedback(const Feedback* feedback)
{
	if (!feedback)
		return false;

	if (feedLogSize == feedPhySize)
		if (!increaseFeedbackSize())	//	failed to increase size
			return false;

	feedbacks[feedLogSize++] = feedback;
	return true;
}
bool Seller::increaseFeedbackSize()
{
	feedPhySize *= 2;
	const Feedback** temp = new const Feedback*[feedPhySize];
	if (!temp)		//	Failed to allocate.
		return false;
	int i = 0;
	for (i = 0; i < feedLogSize; i++)
		temp[i] = feedbacks[i];
	int j;
	for (j = i; j < feedPhySize; j++)
		temp[i] = nullptr;
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
