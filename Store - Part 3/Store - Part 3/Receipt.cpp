#include "Receipt.h"
#include "Seller.h"
#include "ValidationHelper.h"


// ----------------- C'TORS AND D'TOR ----------------- //
Receipt::Receipt(const Cart& cart) 
/*
The constructor of Receipt receives the buyer's cart, and copies from it all the products.
*/
{
	int size = cart.getLogSize();
	m_products.reserve(size);
	m_feedbacks.reserve(size);
	m_total_cost = cart.getCost();
	m_buyer = cart.getOwner();

	const vector<const Product*>& cartProducts = cart.getProducts();

	vector<const Product*>::const_iterator itr = cartProducts.begin();
	vector<const Product*>::const_iterator itr_end = cartProducts.end();

	for (; itr != itr_end; ++itr)
	{
		m_products.push_back(new Product(**itr));
		m_feedbacks.push_back(nullptr);
	}
}
Receipt::Receipt(const Receipt & other) 
{
	*this = other;
}
Receipt::Receipt(Receipt && other) 
{
	m_products = move(other.m_products);
	m_feedbacks = move(other.m_feedbacks);
	m_total_cost = other.m_total_cost;
	m_buyer = other.m_buyer;
	other.m_buyer = nullptr;
	
}
Receipt::~Receipt()
{
	vector<const Product*>::const_iterator itr = m_products.begin();
	vector<const Product*>::const_iterator itr_end = m_products.end();
	vector<const Feedback*>::const_iterator feed_itr = m_feedbacks.begin();
	// No need for end feedback iterator because they're the same size

	for (; itr != itr_end; ++itr, ++feed_itr)
	{
		delete *itr;
		delete *feed_itr; // feed eater. Haha.
	}

	m_products.clear();
	m_feedbacks.clear();
}

const Product* Receipt::GetProduct(int i)		const
{
	if (i<0 || i>(int)m_products.size())	//	Index out of range.
		return nullptr;
	return m_products[i];
}
const Product * Receipt::GetProduct(const string& product_name, const string& seller_name) const
/*
We check by product name and seller name too because some sellers could be selling products of identical names.
*/
{
	for (auto prod : m_products)
	{
		if (prod->getName() == product_name)  // Correct product name
			if (prod->getSeller()->getUsername() == seller_name)  // Correct seller too
				return prod;
	}

	return nullptr;
}
bool Receipt::LeftFeedbackForProduct(int index) const
{
	if (index<0 || index>(int)m_products.size())
		return false;
	return m_feedbacks[index] != nullptr;
}
bool Receipt::LeftFeedbackForProduct(const Product * prod) const
{
	vector<const Product*>::const_iterator curr_prod = m_products.begin();
	vector<const Product*>::const_iterator itr_end = m_products.end();
	vector<const Feedback*>::const_iterator feed_itr = m_feedbacks.begin();

	for (; curr_prod!=itr_end; ++curr_prod, ++feed_itr)
	{
		if ((*curr_prod)->getName()==prod->getName()) // Correct product name
			if ((*curr_prod)->getSeller()->getUsername()== prod->getSeller()->getUsername()) // Correct seller too
				return (*feed_itr) != nullptr; // Return the value stored in the feedbacks array for this product - if it's not nullptr, we left feedback.
	}
	return false;
}
void Receipt::ShowProducts() const
{
	vector<const Product*>::const_iterator curr_prod = m_products.begin();
	vector<const Product*>::const_iterator itr_end = m_products.end();

	int m_num_of_products = m_products.size();

	for (int i=1; curr_prod != itr_end; ++curr_prod, ++i)
	{
		cout << "Product " << i << " out of " << m_num_of_products << ":\n";
		cout << **curr_prod << endl;
	}
	cout << "Total cost: " << m_total_cost << endl;
}
const Receipt & Receipt::operator=(const Receipt & other)
{
	if (this != &other)
	{
		vector<const Product*>::const_iterator itr = m_products.begin();
		vector<const Product*>::const_iterator itr_end = m_products.end();
		vector<const Feedback*>::const_iterator feed_itr = m_feedbacks.begin();
		// No need for end feedback iterator because they're the same size

		for (; itr != itr_end; ++itr, ++feed_itr)
		{
			delete *itr;
			delete *feed_itr; // feed eater. Haha.
		}
		m_products.clear();
		m_feedbacks.clear();

		m_products.reserve(other.m_products.size());
		m_total_cost = other.m_total_cost;
		m_buyer = other.m_buyer;

		itr = other.m_products.begin();
		feed_itr = other.m_feedbacks.begin();
		for (; itr != itr_end; ++itr, ++feed_itr)
		{
			m_products.push_back(new Product(**itr));
			m_feedbacks.push_back(new Feedback(**feed_itr));
		}
	}
	return *this;
}
bool Receipt::AddFeedbackToProd(const string& prodName, const string& sellerName, const Feedback* feedback) 
{
	vector<const Product*>::const_iterator itr = m_products.begin();
	vector<const Product*>::const_iterator itr_end = m_products.end();
	vector<const Feedback*>::iterator feed_itr = m_feedbacks.begin(); 
	// No need for end feedback iterator because they're the same size

	for (int i=0; itr != itr_end; ++itr, ++feed_itr, ++i)
	{
		if ((*itr)->getName() == prodName)  // Check product name match.
		{
			if ((*itr)->getSeller()->getUsername() == sellerName)  // Check seller name match (could have several sellers selling similar products).
			{
				if ((*feed_itr) != nullptr) // Feedback was already given.
					return false;
				*(feed_itr) = new Feedback(*feedback);
				ValidationHelper::AllocationCheck<const Feedback*>(*feed_itr);
				return true;
			}
		}
	}

	return false;
}

ostream & operator<<(ostream & os, const Receipt & rec)
{
	os << rec.m_products.size()<< " purchased products:" << endl << endl;

	int i = 1;
	for (auto prod : rec.m_products)
	{
		os << i << ") " << *prod << endl;
		i++;
	}
	cout << "End of receipt.\n";
	return os;
}