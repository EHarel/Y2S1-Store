#include "System.h"
#include "Buyer.h"
#include "Seller.h"

#include <iostream>
#include <string.h>
using namespace std;


static bool allocationCheck(void* ptr);


System::System(const char* name)
{
	setSystemName(name);
	
	buyPhySize = 10;
	buyLogSize = 0;
	buyers = new Buyer*[buyPhySize];
	if (!allocationCheck(buyers))
		cout << "Failed to allocate room for Buyer array.\n";

	sellPhySize = 5;		//	Expect less Sellers than buyers.
	sellLogSize = 0;
	sellers = new Seller*[sellPhySize];
	if (!allocationCheck(sellers))
		cout << "Failed to allocate room for Seller array.\n";

	latestSerialNum = 1000000;	
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
	for (i = 0; i < buyLogSize; i++)
		if (strcmp(buyers[i]->getUsername(), name) == 0)		//	Found similar username.
			return false;

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
int System::getLatestSerial()							const
{
	return latestSerialNum;
}

Buyer* System::accessBuyerAccount(char* name, int password)
/*
This function provides access to a Buyer Account for the user.
This allows the user to change this account.
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
bool System::advanceSerial()	
{
	latestSerialNum += 1;
	return true;
}




static bool allocationCheck(void* ptr)
{
	if (!ptr)
		return false;
	return true;
}