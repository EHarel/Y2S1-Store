#include "Buyer.h"
#include "Product.h"

int Buyer::buyer_count = 0;

bool Buyer::Checkout(Receipt& receipt)
{
	m_history.push_back(receipt);
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
void Buyer::ShowPurchasedItems() const
{
	if(m_history.empty())
	{
		cout << "No purchases made.\n";
		return;
	}

	cout << m_history;
}
void Buyer::toOs(ostream& os) const
{
	os << "Wishlist: \n" << m_wishlist << endl; 
}