#pragma warning(disable:4996)
#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "Buyer.h"

// Consts
const int BUYER_OPTION = 1;
const int SELLER_OPTION = 2;
const int STOP = -10;
const int WISH_EXIT = 4;
const int NAME_LEN = 31;
const int FEED_LEN = 150;

// Forward Declaration
class Seller;
class Buyer;
class Feedback;
class Date;



class System
{
private:
	char					m_name[NAME_LEN];			
	Buyer**					m_buyers;
	int						m_buyLogSize, m_buyPhySize;
	Seller**				m_sellers;		
	int						m_sellLogSize, m_sellPhySize;

public:
// C'tors and D'tor
	System() = delete;
	System(const char* name);
	System(const System&) = delete;
	~System();
	
// Const methods
	inline const Buyer**	getAllBuyers()							const	{ return (const Buyer**)m_buyers; }
	inline const Seller**	getAllSellers()							const	{ return (const Seller**)m_sellers; }
	inline int				getBuyerLogSize()						const	{ return m_buyLogSize; }
	inline int				getBuyerPhySize()						const	{ return m_buyPhySize; }
	inline int				getSellerLogSize()						const	{ return m_sellLogSize; }
	inline int				getSellerPhySize()						const	{ return m_sellPhySize; }
	const Buyer*			getBuyer(int index)						const;
	const Seller*			getSeller(int index)					const;
	bool					isAvailableUsername(const char* name)	const;
	void					showAllProducts()						const;
	
// Non-const methods
	Buyer*					accessBuyerAccount(char* name, int password);
	Seller*					accessSellerAccount(char* name, int password);
	bool					addBuyer(Buyer* newBuyer);
	bool					addSeller(Seller* newSeller);
	bool					addFeedbackToSeller(const char* sellerUsername, const Feedback* buyerFeedback);

// Menu Options
	void					runMenu();
	void					createNewAccount();
	bool					addAccountToSystem(char* name, int password, int accountType);
	void					accessAccountMenu();
	void					showAllBuyers()							const;
	void					showAllSellers()						const;
	void					showProductsMenu()						const;
	void					showSpecificProduct()					const;

// Buyer related functions
	void					runBuyerMenu(Buyer*& buyer);
	void					addFeedbackToSeller(Buyer*&);
	void					addToWishlist(Buyer*& buyer);
	void					addToCart(Buyer*& buyer);
	void					checkout(Buyer*& buyer);

// Seller related functions
	void					runSellerMenu(Seller*& seller);
	void					addItemToSeller(Seller*& seller);

private:
// Private methods
	int						printMainMenuOptions();
	int						readAccountType();
	bool					chooseNewUsername(char* name);
	bool					continueCheck();
	Feedback*				createFeedback(const Product* prod, const Buyer* feedbackGiver);
	Address					createAddress();
	Date					createDate();
	Buyer*					signInBuyer();
	Seller*					signInSeller();
	void					cleanBuffer();
	void					readProductName(char* name) const;
	int						wishlistMenuOptions();
	int						chooseFromAvailableProducts(const Product** availProducts, int availProductsCount);
	bool					increaseBuyerArray();
	bool					increaseSellerArray();
};
#endif 