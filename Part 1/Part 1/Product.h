#pragma warning(disable:4996)
#ifndef __PROD_H
#define __PROD_H

const int LEN = 31;

class Seller;

class Product
{
public:
	const char* eCategoryNames[4] = { "Children", "Electricity", "Office", "Clothing" };
	enum eCategory { CHILDREN, ELECTRICITY, OFFICE, CLOTHING };

public:
	Product() = delete;
	Product(char* name, double price, int serial, eCategory category, Seller* seller, int indAtSeller, bool& check);	//	constructor; receives initial values
	Product(const Product* other);

// Getters
	const char* getName()			const;
	double getPrice()				const;
	int getSerial()					const;
	eCategory getCategory()			const;
	void showProduct()				const;
	const Seller*	getSeller()		const;

// Setters
	bool setName(const char* name);
	bool setPrice(const double price);
	bool setSerial(int serial);
	bool setCategory(eCategory category);

	~Product();
private:
	char				name[LEN];
	double				price;
	int					serial;
	eCategory			category;
	const Seller*		sellerOfProduct;
	int					indAtSeller;
};
#endif