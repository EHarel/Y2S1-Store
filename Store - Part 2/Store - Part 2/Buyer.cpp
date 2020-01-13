#include "Buyer.h"
#include "Product.h"
#include "Address.h"

int Buyer::buyer_count = 0;

// ----------------- CONSTRUCTORS ----------------- //
Buyer::Buyer(const Buyer& other) : User(other), m_wishlist(other.m_wishlist),  m_cart(other.m_cart), m_history(other.m_history)
{
	++buyer_count;
}

Buyer::~Buyer()
{
	--buyer_count;
}

// ----------------- MISC ----------------- //
bool Buyer::proceedToCheckout(Receipt* receipt)
{
	if (!receipt)
		return false;
	if (m_history.logSize == m_history.phySize)	//	No more space.
		if (!m_history.increasePurchaseHistorySize())	//	If failed to increase.
			return false;
	m_history.receipts[m_history.logSize++] = receipt;	//	Add receipt to history.

	m_wishlist.clearChosenProducts();
	m_cart.emptyCart();
	return true;
}
void Buyer::showBuyer() const
{
	cout << "Username: " << m_username << endl;
	m_address.showAddress();
	cout << endl;
}



void Buyer::toOs(ostream& os) const	
{
	os << "Wishlist: \n" << m_wishlist << endl; // # change to purchase history?
}