#pragma warning(disable:4996)
#ifndef __PROD_H
#define __PROD_H

const int LEN = 31;

class Seller;
class Feedback;

class Product
{
public:
	const char* eCategoryNames[4] = { "Children", "Electricity", "Office", "Clothing" };
	enum eCategory { CHILDREN, ELECTRICITY, OFFICE, CLOTHING };

private:
	static int latestSerialNum;

	char*				name;	//	 Dynamically allocated.
	double				price;
	int					serial;
	eCategory			category;
	const Seller*		sellerOfProduct;
	int					indAtSeller;

public:
// Constructors and Destructor
	Product() = delete;
	Product(char* name, double price, eCategory category, Seller* seller, int indAtSeller, bool& check);	//	constructor; receives initial values
	~Product();
	// We rely on a regular copy constructor. We want copies of the product to be pointing to the same seller.

// Const methods
	const char* getName()			const;
	double getPrice()				const;
	int getSerial()					const;
	eCategory getCategory()			const;
	void showProduct()				const;
	const Seller*	getSeller()		const;

// Non-const methods
	bool setName(const char* name);
	bool setPrice(const double price);
	bool setCategory(eCategory category);
};
#endif