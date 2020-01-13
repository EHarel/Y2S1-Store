#include "Receipt.h"
#include "Seller.h"

// ----------------- C'TORS AND D'TOR ----------------- //
Receipt::Receipt(const Cart& cart)
/*
The constructor of Receipt receives the buyer's cart, and copies from it all the products.
*/
{
	numOfProducts = cart.getLogSize();
	totalCost = cart.getCost();
	buyer = cart.getOwner();

	products = new const Product*[numOfProducts];
	feedbacks = new const Feedback*[numOfProducts];
	const Product** cartProducts = cart.getProducts();
	for (int i = 0; i < numOfProducts; i++)
	{
		products[i] = new const Product((*cartProducts[i]));
		if (!products[i]) // Alocation check
			exit(1);
		feedbacks[i] = nullptr;
	}

}
Receipt::Receipt(const Receipt & other) : products(NULL), feedbacks(NULL), numOfProducts(0)
{
	*this = other;
}
Receipt::Receipt(Receipt && other) : products(NULL), feedbacks(NULL), numOfProducts(0)
{
	*this = other;

	other.numOfProducts = 0;
	other.products = nullptr;
	other.feedbacks = nullptr;
	
}
Receipt::~Receipt()
{
	for (int i = 0; i < numOfProducts; i++)
	{
		delete products[i];
		delete feedbacks[i];
	}
	delete[]products;
	delete[]feedbacks;
}


const Product* Receipt::GetProduct(int i)		const
{
	if (i<0 || i>numOfProducts)	//	Index out of range.
		return nullptr;
	return products[i];
}
const Product * Receipt::GetProduct(const char * product_name, const char * seller_name) const
/*
We check by product name and seller name too because some sellers could be selling products of identical names.
*/
{
	for (int i = 0; i < numOfProducts; i++)
	{
		const Product* prod = products[i];
		if (strcmp(prod->getName(), product_name) == 0) // Correct product name
			if (strcmp(prod->getSeller()->getUsername(), seller_name) == 0) // Correct seller too
				return prod;
	}
	return nullptr;
}
bool Receipt::LeftFeedbackForProduct(int index) const
{
	if (index<0 || index>numOfProducts)
		return false;
	return feedbacks[index] != nullptr;
}
bool Receipt::LeftFeedbackForProduct(const Product * prod) const
{
	for (int i = 0; i < numOfProducts; i++)
	{
		const Product* curr_prod = products[i];
		if (strcmp(curr_prod->getName(), prod->getName()) == 0) // Correct product name
			if (strcmp(curr_prod->getSeller()->getUsername(), prod->getSeller()->getUsername()) == 0) // Correct seller too
				return feedbacks[i] != nullptr; // Return the value stored in the feedbacks array for this product - if it's not nullptr, we left feedback.
	}
	return false;
}
const Receipt & Receipt::operator=(const Receipt & other)
{
	if (this != &other)
	{
		for (int i = 0; i < numOfProducts; i++)
		{
			delete products[i];
			delete feedbacks[i];
		}
		delete[]products;
		delete[]feedbacks;

		numOfProducts = other.numOfProducts;
		totalCost = other.totalCost;
		buyer = other.buyer;

		for (int i = 0; i < numOfProducts; i++)
		{
			products[i] = new Product(*(other.products[i]));
			feedbacks[i] = new Feedback(*(other.feedbacks[i]));
			if (!products[i] || !feedbacks[i]) // Allocation check;
				exit(1);
		}

	}
	return *this;
}
bool Receipt::addFeedbackToProd(const char* prodName, const char* sellerName, const Feedback* feedback)
{
	for(int i = 0; i < numOfProducts; i++)
	{
		if (strcmp(products[i]->getName(), prodName) == 0) // Check product name match.
		{
			if (strcmp(products[i]->getSeller()->getUsername(), sellerName) == 0) // Check seller name match (could have several sellers selling similar products).
			{
				if (feedbacks[i] != nullptr) // Feedback was already given.
					return false;
				feedbacks[i] = new Feedback(*feedback);
				return true;
			}
		}
	}
	return false;
}

ostream & operator<<(ostream & os, const Receipt & rec)
{
	// const User* temp = dynamic_cast<const User*>(rec.buyer); // # how to do this?!?!?!?!
	// os << "Receipt of " << *(rec.buyer) << endl;
	os << "Number of products pruchased: " << rec.numOfProducts << endl;
	os << "Purchased products:\n";
	for (int i = 0; i < rec.numOfProducts; i++)
	{
		os << *(rec.products[i]) << endl;
	}
	return os;
}