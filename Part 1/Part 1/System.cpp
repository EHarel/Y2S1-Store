#include "System.h"
#include "Buyer.h"
#include "Seller.h"

#include <iostream>
#include <string.h>
using namespace std;

System::System(const char* name)
{
	setSystemName(name);
	
	buyPhySize = 10;
	buyLogSize = 0;
	buyers = new Buyer*[buyPhySize];
	if (!buyers)
		exit(1);
	buyers[0] = nullptr;

	sellPhySize = 5;		//	Expect less Sellers than buyers.
	sellLogSize = 0;
	sellers = new Seller*[sellPhySize];
	if (!sellers)
		exit(1);
	sellers[0] = nullptr;	
}

System::~System()
{
	int i = 0;
	for (i = 0; i < buyLogSize; i++)
		delete buyers[i];
	delete[]buyers;

	for (i = 0; i < sellLogSize; i++)
		delete sellers[i];
	delete[]sellers;
}



// ------------------------------- GETTERS ------------------------------- //

const Buyer** System::getAllBuyers()					const
{
	return (const Buyer**)buyers;
}
const Seller** System::getAllSellers()					const
{
	return (const Seller**)sellers;
}

const Buyer* System::getBuyer(int index) const
/*
This function receives an index for the array and returns the element in that array.
*/
{
	if (index < 0 || index > buyLogSize)
		return nullptr;
	return(buyers[index]);
}
const Seller* System::getSeller(int index) const
{
	if (index < 0 || index > sellLogSize)
		return nullptr;
	return(sellers[index]);
}

bool System::isAvailableUsername(const char* name)		const
/*
This function receives a username, and checks if it already exists in the system.
It goes over one array, then the other, stopping if it has found it.
*/
{
	int i = 0;
// Go over buyers array.
	for (i = 0; i < buyLogSize; i++)
		if (strcmp(buyers[i]->getUsername(), name) == 0)		//	Found similar username.
			return false;

// Go over sellers array.
	for (i = 0; i < sellLogSize; i++)
		if (strcmp(sellers[i]->getUsername(), name) == 0)
			return false;
	
	return true;
}

int System::getBuyerLogSize()							const
{
	return buyLogSize;
}
int System::getBuyerPhySize()							const
{
	return buyPhySize;
}
int System::getSellerLogSize()							const
{
	return sellLogSize;
}
int System::getSellerPhySize()							const
{
	return sellPhySize;
}

void System::showAllProducts()	const //	A bit of a "brutish" method that just shows all the products
{
	int productCount = 0;

	for (int i = 0; i < sellLogSize; i++)
	{
		if (sellers[i]->catLogSize > 0)	//	If seller i has items.
		{
			cout << "Products of " << sellers[i]->username << ": ";
			cout << endl;
			sellers[i]->showAllMerchandise();
			cout << endl;
			productCount += sellers[i]->catLogSize;
		}
	}
	cout << "Total number of available products: " << productCount << endl << endl;
}

Buyer* System::accessBuyerAccount(char* name, int password)
/*
This function provides access to a Buyer Account for the user.
This allows the user to take actions with his account, such as adding to wishlist, checking out, etc.
*/
{
	for (int i = 0; i < buyLogSize; i++)
	{
		if (strcmp(buyers[i]->getUsername(), name) == 0)	//	Found the username
		{
			bool validAccess = buyers[i]->passwordCheck(password);
			if (validAccess)
				return buyers[i];
			else
				return nullptr;
		}
	}
	return nullptr;
}
Seller* System::accessSellerAccount(char* name, int password)
/*
This function provides a Seller Account for the user.
This allows the user to change his account.
*/
{
	for (int i = 0; i < sellLogSize; i++)
	{
		if (strcmp(sellers[i]->getUsername(), name) == 0)	//	Found the username
		{
			bool validAccess = sellers[i]->passwordCheck(password);
			if (validAccess)
				return sellers[i];
			else
				return nullptr;
		}
	}
	return nullptr;
}



// ------------------------------- SETTERS ------------------------------- //
bool System::setSystemName(const char* name)
{
	// CHECK NAME LENGTH?
	strcpy(this->name, name);
	return true;
}

bool System::addBuyer(Buyer* newBuyer)
{
	if (newBuyer == nullptr)
		return false;
	if (buyLogSize == buyPhySize)	//	No room in the array; need to increase its physical size.
		if (increaseBuyerArray() == false)
		{
			cout << "Array is full, and failed to increase size.\n";
			return false;
		}
	buyers[buyLogSize++] = newBuyer;
	return true;
}

bool System::addSeller(Seller* newSeller)
{
	if (newSeller == nullptr)
		return false;
	if (sellLogSize == sellPhySize)	//	No room in the array; need to increase its physical size.
		if (increaseSellerArray() == false)
		{
			cout << "Array is full, and failed to increase size.\n";
			return false;
		}
	sellers[sellLogSize++] = newSeller;
	return true;
}

bool System::increaseBuyerArray()
{
	buyPhySize *= 2;
	Buyer** temp = new Buyer*[buyPhySize];
	if (!temp)		//	Failed to allocate.
		return false;
	for (int i = 0; i < buyLogSize; i++)
		temp[i] = buyers[i];
	delete[]buyers;
	buyers = temp;
	return true;
}
bool System::increaseSellerArray()
{
	sellPhySize *= 2;
	Seller** temp = new Seller*[sellPhySize];
	if (!temp)		//	Failed to allocate.
		return false;
	for (int i = 0; i < sellLogSize; i++)
		temp[i] = sellers[i];
	delete[]sellers;
	sellers = temp;
	return true;
}



bool System::addFeedbackToSeller(const char* sellerUsername, const Feedback* buyerFeedback)
{
	for (int i = 0; i < sellLogSize; i++)
	{
		if (strcmp(sellers[i]->username, sellerUsername) == 0) // Found the seller.
			if (!sellers[i]->addFeedback(buyerFeedback))
				return false;
			else
				return true;
	}//for
	return false;
}