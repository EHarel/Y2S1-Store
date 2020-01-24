#include "Seller.h"

int Seller::seller_count = 0;

// ----------------- GETTERS ----------------- //
const Product* Seller::getProduct(const string& name) const
{
	for (auto p : m_catalog)
		if (p->getName() == name)
			return p;

	return nullptr; // Didn't find the product.


}
const Product* Seller::getProduct(int serial) const
{
	int size = m_catalog.size();

	for (int i = 0; i < size; i++)
	{
		if (m_catalog[i]->getSerial() == serial) // Compare serial numbers.
			return m_catalog[i];
	}
	return nullptr; // Didn't find the product.
}


// ----------------- SHOW ----------------- //
void Seller::showSeller() const
{
	cout << "Username: " << m_username << endl;
	m_address.showAddress();
}
void Seller::showAllMerchandise() const
{
	if (m_catalog.empty())
	{
		cout << "No products in the catalog. Nothing to show.\n";
		return;
	}

	vector<Product*>::const_iterator itr = m_catalog.begin();
	vector<Product*>::const_iterator itr_end = m_catalog.end();

	for (; itr != itr_end; ++itr)
	{
		cout << **itr << endl << endl;
	}
}
void Seller::showAllFeedbacks()	const
{
	if (m_feedbacks.empty())
	{
		cout << "No feedbacks given.\n";
		return;
	}

	vector<const Feedback*>::const_iterator itr = m_feedbacks.begin();
	vector<const Feedback*>::const_iterator itr_end = m_feedbacks.end();

	for (; itr != itr_end; ++itr)
	{
		cout << **itr << endl;;
	}
	cout << endl;
}

// ----------------- MISC ----------------- //
void Seller::addFeedback(const Feedback& feedback)
{
	ValidationHelper::ManageSize<const Feedback*>(m_feedbacks);
	m_feedbacks.push_back(&feedback); // Send address because it's an array of pointers.
}
void Seller::addProductToMerch(Product& product)
{
	ValidationHelper::ManageSize<Product*>(m_catalog);
	
	m_catalog.push_back(&product);
}
void Seller::toOs(ostream& os) const
{
	os << "Seller's catalog: \n";
	if (m_catalog.empty())
	{
		os << "Seller has no items on sale.\n";
		os << endl;
	}
	else
	{
		os << endl;

		vector<Product*>::const_iterator itr		= m_catalog.begin();
		vector<Product*>::const_iterator itr_end	= m_catalog.end();

		for (; itr != itr_end; ++itr)
		{
			cout << **itr << endl << endl;
		}
	}
}