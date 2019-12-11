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
private:
	char					name[LEN];			// name of the system
	Buyer**					buyers;
	int						buyLogSize, buyPhySize;
	Seller**				sellers;			//	Dynamically allocated array of Sellers.
	int						sellLogSize, sellPhySize;
	// products array

public:
// Constructors and Destructor
	System() = delete;
	System(const char* name);
	System(const System&) = delete;
	~System();
	
// Const methods
	const Buyer**			getAllBuyers()					const;
	const Seller**			getAllSellers()					const;
	const Buyer*			getBuyer(int index)				const;
	const Seller*			getSeller(int index)				const;
	bool					isAvailableUsername(const char* name)		const;
	
	int						getBuyerLogSize()							const;
	int						getBuyerPhySize()							const;
	int						getSellerLogSize()							const;
	int						getSellerPhySize()							const;

	void					showAllProducts()							const;
	
	
	Buyer*					accessBuyerAccount(char* name, int password);		//	Currently it returns a pointer rather than Buyer&, because a pointer allows an indication that the password isn't correct.
	Seller*					accessSellerAccount(char* name, int password);		//	IDEA: find a way to return Class& instead of pointer, with some sort of password validation?

// Non-const methods
	bool					setSystemName(const char* name);

	bool					addBuyer(Buyer* newBuyer);
	bool					addSeller(Seller* newSeller);


	bool					addFeedbackToSeller(const char* sellerUsername, const Feedback* buyerFeedback);


	bool					increaseBuyerArray();			//	IDEA: Maybe concentrate them both into a single function? The downside is possibly increasing an array we don't want to, if it happens that the log size is equal to the physical (because it will run both checks)
	bool					increaseSellerArray();
};
#endif 