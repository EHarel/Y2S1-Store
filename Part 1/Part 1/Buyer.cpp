#include "Buyer.h"
#include "Product.h"
#include "Address.h"
#include <string.h>
#include <iostream>
using namespace std;



Buyer::Buyer(char* name, int password, Address* address)
{
	changeUsername(name);
	resetPassword(password);
	setAddress(address);

	wishPhySize = 10;
	wishLogSize = 0;
	wishlist = new const Product*[wishPhySize];
	if (!wishlist)
		cout << "Failed to create a cart for the buyer.\n";

	cartPhySize = wishPhySize;
	cartLogSize = 0;
	cart = new const Product**[cartPhySize];
	if (!cart)
		cout << "Failed to create checkout array.\n";

	currCheckoutCost = 0;

	historyLogSize = 0;
	historyPhySize = 0;
}

Buyer::~Buyer()		//	Destructor
{
	delete address;
	delete[]wishlist;
	delete[]cart;
	delete[]purchaseHistory;
}



// ------------------------------- GETTERS ------------------------------- //

const char*		Buyer::getUsername()								const
{
	return username;
}
const			Address* Buyer::getAddress()						const
{
	return address;
}
const			Product** Buyer::getWishlist()							const
{
	return wishlist;
}
int				Buyer::getCartLogSize()								const
{
	return wishLogSize;
}


void Buyer::showBuyer() const
{
	cout << "Username: " << username << endl;
	address->showAddress();
	cout << endl;
}
bool Buyer::showAllWishlistProducts() const
{
	if (wishLogSize == 0)	//	No items in wishlist.
		return false;
	for (int i = 0; i < wishLogSize; i++)
	{
		cout << "Wishlisted product " << i + 1 << endl;
		wishlist[i]->showProduct();
		cout << endl;
	}
	return true;
}
const Product**	Buyer::getWishlistProductAddress(int index) const
{
	if (index<0 || index>wishLogSize)
		return nullptr;
	return &(wishlist[index]);
}
double Buyer::getCurrentCheckoutCost() const
{
	return currCheckoutCost;
}
int Buyer::getWishLogSize() const
{
	return wishLogSize;
}
const Product*** Buyer::getCart() const	//	Items for check-out.
{
	return cart;
}
int Buyer::getCheckoutLogSize() const
{
	return cartLogSize;
}

bool Buyer::passwordCheck(int password)					const
// This function receives a password and compares it with the user's password, to see if it is the same.
{
	if (this->password == password)
		return true;
	else
		return false;
}



// ------------------------------- SETTERS ------------------------------- //

bool Buyer::changeUsername(const char* username)
{
	strcpy(this->username, username);
	return true;
}

bool Buyer::resetPassword(const int password)
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
bool Buyer::setAddress(Address* address)
{
	this->address = address;
	return true;
}

bool Buyer::addToWishlist(const Product* product)		//	This function receives a chosen product and adds it to the cart.
{
	if (product == nullptr)
		return false;
	if (wishLogSize == wishPhySize)
		if (increaseWishlistSize() == false)
			return false;
	wishlist[wishLogSize++] = product;
	return true;
}
bool Buyer::increaseWishlistSize()
{
	wishPhySize *= 2;
	const Product** temp = new const Product*[wishPhySize];		//	Const because the cart is not able to change the product.
	if (!temp)		//	Failed to allocate.
		return false;
	for (int i = 0; i < wishLogSize; i++)
		temp[i] = wishlist[i];
	delete[]wishlist;
	wishlist = temp;
	return true;
}

bool Buyer::addToCart(const Product** productAddress)
{
	if (!productAddress)
		return false;
	if (cartLogSize == cartPhySize)
		if (increaseCartSize() == false)
			return false;
	cart[cartLogSize] = productAddress;
	cartLogSize++;
	currCheckoutCost = currCheckoutCost + (*productAddress)->getPrice();
	return true;
}
bool Buyer::increaseCartSize()
{
	cartPhySize *= 2;
	const Product*** temp = new const Product**[cartPhySize];
	if (!temp)
		return false;
	for (int i = 0; i < cartLogSize; i++)
		temp[i] = cart[i];
	delete[]cart;
	cart = temp;
	return true;
}

bool Buyer::proceedToCheckout(ReceiptBuyer* receipt)
{
	if (!receipt)
		return false;
	if (historyPhySize == 0)
	{
		historyPhySize = 2;
		purchaseHistory = new ReceiptBuyer*[historyPhySize];
		if (!purchaseHistory)	//	Allocation check.
			return false;
	}
	if (historyLogSize == historyPhySize)	//	No more space.
		if (!increasePurchaseHistorySize())	//	If failed to increase.
			return false;
	purchaseHistory[historyLogSize++] = receipt;
	
	// Now we remove from the wishlist the items we have paid for.
	for (int i = 0; i < cartLogSize; i++)
	{
		const Product** location = cart[i];	//	Receive address of the product at the wishlist (cart is ***)
		(*location) = nullptr;	//	Place nullptrs where there are products that were purchased
	}
	int i = 0;
	while (i < wishLogSize)
	{
		if (wishlist[i] == nullptr)	//	Location of a purchased item - need to "clear" it from the array
		{
			wishlist[i] = wishlist[wishLogSize - 1];
			wishlist[wishLogSize - 1] = nullptr;
			wishLogSize--;
			//	We don't advance the index because we must check the item we took from the end
		}
		else
			i++;	//	Advance only if the product at the location is valid (that is, not nullptr)
	}
//	if (wishlist[i] == nullptr)	//	Check for the final advancement after the loop
//		wishLogSize--;	//	BAD CODE. DOESN'T WORK.
	return true;
}
bool Buyer::increasePurchaseHistorySize()
{
	historyPhySize *= 2;
	ReceiptBuyer** temp = new ReceiptBuyer*[cartPhySize];
	if (!temp)
		return false;
	for (int i = 0; i < historyLogSize; i++)
		temp[i] = purchaseHistory[i];
	delete[]purchaseHistory;
	purchaseHistory = temp;
	return true;
}

