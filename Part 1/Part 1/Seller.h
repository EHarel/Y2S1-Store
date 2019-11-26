#pragma warning(disable:4996)
#ifndef __Seller_H
#define __Seller_H

#include "Product.h"
//class Product;
//const int LEN = 21;

class Address;
class Feedback;
class Buyer;
class ReceiptBuyer;

const int UNKNOWN_INDEX = -10;
const int NOT_FOUND = -1;

class Seller
{
public:
	Seller() = delete;
	Seller(char* name, int password, Address* address);

//	Getters
	const char* getUsername()											const;
	const Address* getAddress()											const;
	const Product* getProduct(const char* name, int& indexAtSeller)		const;	//	Explanation for index at bottom of page.
	int getCatalogLogSize()												const;
	
	void showSeller()													const;
	void showAllMerchandise()											const;
	bool passwordCheck(int password)									const;

//	Setters
	bool changeUsername(const char* username);
	bool resetPassword(const int password);
	bool setAddress(Address* address);		//	QUESTION: can it be const address?

	bool addReceipt(const ReceiptBuyer* receipt);
	bool increaseRecordsSize();

	bool addFeedback(Feedback* feedback);
	bool increaseFeedbackSize();
	bool addProductToMerch(Product* product);
	bool increaseMerchandiseSize();

	~Seller();
private:
	char			username[LEN];
	int				password;
	Address*		address;

	Feedback**		feedbacks;							//	dynamically allocated array of feedbacks received
	int				feedLogSize, feedPhySize;			//	sizes for the feedback array
	Product**		catalog;							//	dynamically allocated array of products
	int				catLogSize, catPhySize;
	ReceiptBuyer**	saleRecords;
	int				recordsLogSize, recordsPhySize;
};
#endif

/*
getProduct index parameter
	...


*/
