#include "Seller.h"
#include "Product.h"
#include "Address.h"
#include "Feedback.h"

int Seller::seller_count = 0;


// ----------------- C'TORS AND D'TOR ----------------- //
Seller::Seller(const char* username, int password, const Address& address) : User(username, password, address)
{
	++seller_count;

	m_feedPhySize = 10;
	m_feedLogSize = 0;
	m_feedbacks = new const Feedback*[m_feedPhySize];
	for (int i = 0; i < m_feedPhySize; i++)
		m_feedbacks[i] = nullptr;
	if (!m_feedbacks)
		exit(1);

	m_catPhySize = 10;
	m_catLogSize = 0;
	m_catalog = new Product*[m_catPhySize];
	if (!m_catalog)
		exit(1);
}
Seller::Seller(const Seller& other) : User(other)
{
	++seller_count;

}
Seller::Seller(Seller&& other) : User(other) // # check move operator - research
{
	++seller_count;

}
//constructor
Seller::~Seller()
{
	--seller_count;
	int i = 0;
	for (i = 0; i < m_feedLogSize; i++)
		delete m_feedbacks[i];
	delete[]m_feedbacks;

	for (i = 0; i < m_catLogSize; i++)
		delete m_catalog[i];
	delete[]m_catalog;
}


// ----------------- GETTERS ----------------- //
const Product* Seller::getProduct(const char* name) const
{
	for (int i = 0; i < m_catLogSize; i++)
	{
		if (strcmp(m_catalog[i]->getName(), name) == 0) // Compare names.
			return m_catalog[i];
	}
	return nullptr;	//	Didn't find the product.
}
const Product* Seller::getProduct(int serial) const
{
	for (int i = 0; i < m_catLogSize; i++)
	{
		if (m_catalog[i]->getSerial() == serial) // Compare serial numbers.
			return m_catalog[i];
	}
	return nullptr; // Didn't find the product.
}



// ----------------- MISC ----------------- //
void Seller::showSeller() const
{
	cout << "Username: " << m_username << endl;
	m_address.showAddress();
}
void Seller::showAllMerchandise() const
{
	if (m_catLogSize == 0)
	{
		cout << "No products in the catalog. Nothing to show.\n";
		return;
	}

	for (int i = 0; i < m_catLogSize; i++)
	{
		cout << "Item " << i + 1 << endl;
		m_catalog[i]->showProduct();
		cout << endl;
	}
}
void Seller::showAllFeedbacks()	const
{
	if (m_feedLogSize == 0)
	{
		cout << "No feedbacks to show.\n";
		return;
	}

	for (int i = 0; i < m_feedLogSize; i++)
	{
		cout << i + 1 << ") ";
		m_feedbacks[i]->showFeedback();
	}
}
bool Seller::addFeedback(const Feedback* feedback)
{
	if (!feedback)
		return false;

	if (m_feedLogSize == m_feedPhySize)
		if (!increaseFeedbackSize())	//	failed to increase size
			return false;

	m_feedbacks[m_feedLogSize++] = feedback;
	return true;
}
bool Seller::addProductToMerch(Product* product)
{
	if (!product)
		return false;

	if (m_catLogSize == m_catPhySize)
		if (!increaseMerchandiseSize())
			return false;

	m_catalog[m_catLogSize++] = product;
	return true;
}


// ----------------- PRIVATE ----------------- //
bool Seller::increaseFeedbackSize()
{
	m_feedPhySize *= 2;
	const Feedback** temp = new const Feedback*[m_feedPhySize];
	if (!temp)		//	Failed to allocate.
		return false;
	int i = 0;
	for (i = 0; i < m_feedLogSize; i++)
		temp[i] = m_feedbacks[i];
	int j;
	for (j = i; j < m_feedPhySize; j++)
		temp[i] = nullptr;
	delete[]m_feedbacks;
	m_feedbacks = temp;
	return true;
}
bool Seller::increaseMerchandiseSize()
{
	m_catPhySize *= 2;
	Product** temp = new Product*[m_catPhySize];
	if (!temp)		//	Failed to allocate.
		return false;
	for (int i = 0; i < m_feedLogSize; i++)
		temp[i] = m_catalog[i];
	delete[]m_catalog;
	m_catalog = temp;
	return true;
}







void Seller::toOs(ostream& os) const
{
	os << "Seller's catalog: \n";
	for (int i = 0; i < m_catLogSize; i++)
	{
		os << *(m_catalog[i]) << endl;
	}
}