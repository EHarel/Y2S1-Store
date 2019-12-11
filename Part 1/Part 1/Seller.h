#pragma warning(disable:4996)
#ifndef __Seller_H
#define __Seller_H

#include "Product.h"
#include "Address.h"

class Feedback;
class Buyer;
class Receipt;

//const int NOT_FOUND = -1;

class Seller
{
private:
	char*					username;
	int						password;
	Address					address;

	const Feedback**		feedbacks;							//	dynamically allocated array of feedbacks received
	int						feedLogSize, feedPhySize;			//	sizes for the feedback array
	Product**				catalog;							//	dynamically allocated array of products
	int						catLogSize, catPhySize;

public:
// Constructors and Destructor
	Seller() = delete;	//	 Delete default constructor.
	Seller(char* name, int password, const Address& address);
	Seller(const Seller&) = delete;	//	Delete copy constructor.
	~Seller();

//	Const methods
	const char*				getUsername()							const;
	const Address&			getAddress()							const;
	const Product*			getProduct(const char* name)			const;	
	int						getCatalogLogSize()						const;
	
	void					showSeller()							const;
	void					showAllMerchandise()					const;
	bool					passwordCheck(int password)				const;
	void					showAllFeedbacks()						const;

//	Non-const methods
	bool					changeUsername(const char* username);
	bool					resetPassword(int newPassword, int currentPasswordVerification);
	bool					setAddress(const Address& other);		

	bool					addFeedback(const Feedback* feedback);
	bool					increaseFeedbackSize();
	bool					addProductToMerch(Product* product);
	bool					increaseMerchandiseSize();

	friend class System;
};
#endif