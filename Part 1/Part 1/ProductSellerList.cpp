#include "ProductSellerList.h"
#include "Seller.h"
#include "Product.h"
#include <iostream>
using namespace std;

ProductSellerList::ProductSellerList(int phySize, const char* name)
{
	if (phySize <= 0)
		this->availPhySize = 1;
	else
		this->availPhySize = phySize;
	this->availLogSize = 0;

	availableSellers = new const Seller*[phySize];
	if (!availableSellers)
		cout << "Problem creating the sellers array.\n";

	indexArray = new int[phySize];
	if (!indexArray)
		cout << "Problem creating the index array.\n";

	// LEN CHECK?
	strcpy(prodName, name);
}

ProductSellerList::~ProductSellerList()
{
	delete[]availableSellers;
	delete[]indexArray;
}



bool ProductSellerList::showAvailableSellers() const
{
	if (availLogSize == 0)
		return false;
	for (int i = 0; i < availLogSize; i++)
	{
		int index = indexArray[i];
		const Product* prod = availableSellers[i]->getProduct(prodName, index);
		cout << "Option " << i + 1 << endl;
		prod->showProduct();
		cout << endl;
	}
	cout << endl;
	return true;
}

int ProductSellerList::getLogSize() const
{
	return availLogSize;
}

const Product* ProductSellerList::getProduct(int index)	const
{
	if (index<0 || index>availLogSize)	//	Chosen index is not in proper range.
		return nullptr;
	int indexAtSeller = indexArray[index];
	return availableSellers[index]->getProduct(prodName, indexAtSeller);
}


bool ProductSellerList::addAvailableSeller(const Seller* seller, int index)
{
	if (!seller)
		return false;
	if(availLogSize==availPhySize)
	if (!increaseAvailSellersArray())
		return false;

	availableSellers[availLogSize] = seller;
	indexArray[availLogSize] = index;
	availLogSize++;
	return true;
}

bool ProductSellerList::increaseAvailSellersArray()
/* This function is called upon when we wish to add an element to the array; 
We check that there's enough space. If not, we call the increase size function.
*/
{
	availPhySize *= 2;
	const Seller** temp = new const Seller*[availPhySize];
	if (!temp)	//	Failed to allocate.
		return false;
	for (int i = 0; i < availLogSize; i++)
		temp[i] = availableSellers[i];
	delete[]availableSellers;
	availableSellers = temp;
	return true;
}