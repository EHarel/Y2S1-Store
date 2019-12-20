#include "Buyer.h"
#include "Product.h"
#include "Address.h"

// ----------------- C'TORS AND D'TOR ----------------- //
Buyer::Buyer(const char* name, int password, const Address& address) : address(address)
{
	this->username = strdup(name);
	this->password = password;
}
Buyer::~Buyer()
{
	delete[]username;
}


// ----------------- SETTERS ----------------- //
bool Buyer::changeUsername(const char* username)
{
	strcpy(this->username, username);
	return true;
}
bool Buyer::resetPassword(int newPassword, int currentPasswordVerification)
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
bool Buyer::setAddress(const Address& other)
{
	address = other;
	return true;
}


// ----------------- MISC ----------------- //
bool Buyer::proceedToCheckout(Receipt* receipt)
{
	if (!receipt)
		return false;
	if (history.logSize == history.phySize)	//	No more space.
		if (!history.increasePurchaseHistorySize())	//	If failed to increase.
			return false;
	history.receipts[history.logSize++] = receipt;	//	Add receipt to history.

	wishlist.clearChosenProducts();
	cart.emptyCart();
	return true;
}
void Buyer::showBuyer() const
{
	cout << "Username: " << username << endl;
	address.showAddress();
	cout << endl;
}