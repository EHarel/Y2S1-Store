#pragma warning(disable:4996)
#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "Product.h"

// const int LEN = 31;	//	PROBLEM: there needs to be one LEN for all. Where do we define it? What do we include? Or maybe we just make the name dynamically allocated?
// Right now, LEN is located at Product and all include it
class Seller;
class Buyer;

class System
{
public:	//	Constructors
	System() = delete;
	System(const char* name);
	
public:	//	Getters
	const Buyer** getAllBuyers()					const;
	const Seller** getAllSellers()					const;
	const Buyer* getBuyer(int index)				const;
	const Seller* getSeller(int index)				const;
	bool isAvailableUsername(const char* name)		const;
	
	int getBuyerLogSize()							const;
	int getBuyerPhySize()							const;
	int getSellerLogSize()							const;
	int getSellerPhySize()							const;
	int getLatestSerial()							const;
	Buyer* accessBuyerAccount(char* name, int password);
	Seller* accessSellerAccount(char* name, int password);

public:	//	Setters
	bool setSystemName(const char* name);

	bool addBuyer(Buyer* newBuyer);
	bool addSeller(Seller* newSeller);

	bool increaseBuyerArray();			//	IDEA: Maybe concentrate them both into a single function? The downside is possibly increasing an array we don't want to, if it happens that the log size is equal to the physical (because it will run both checks)
	bool increaseSellerArray();
	bool advanceSerial();				//	Is there some way to control this?

	~System();
private:
	char			name[LEN];		// name of the system
	Buyer**			buyers;
	int				buyLogSize, buyPhySize;
	Seller**		sellers;			//	Dynamically allocated array of Sellers.
	int				sellLogSize, sellPhySize;
	// class ProductsArr
	// products array
	int				latestSerialNum;
};
#endif 

/*
Note:	
	No Move or Copy constructor for System. We can add, but right now we don't see any potential use, because System occurs only once.
*/