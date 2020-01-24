#pragma warning(disable:4996)
#ifndef __PROD_H
#define __PROD_H

#include <iostream>
using namespace std;

class Seller;
class Feedback;

class Product
{
public:
	enum eCategory { CHILDREN, ELECTRICITY, OFFICE, CLOTHING };

private:
	static int latestSerialNum;

	string					m_name;	
	double					m_price;
	int						m_serial;
	eCategory				m_category;
	const Seller*			m_seller;
	int						m_indAtSeller;

public:
// Constructors and Destructor
	Product() = delete;
	Product(const string& name, double price, eCategory category, const Seller* seller, int indAtSeller);	
	Product(const Product& other);
	Product(Product&& other);

// Getters
	inline const string&	getName()			const	{ return m_name; }
	inline double			getPrice()			const	{ return m_price; }
	inline int				getSerial()			const	{ return m_serial; }
	inline 	eCategory		getCategory()		const	{ return m_category; }
	inline const Seller*	getSeller()			const	{ return m_seller; }
	void					showProduct()		const;

// Setters
	bool					setName(const string& name);
	bool					setPrice(const double price);
	bool					setCategory(eCategory category);

	friend class System;
	friend ostream&			operator<<(ostream& os, const Product& p);
};
#endif