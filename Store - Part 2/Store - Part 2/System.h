#pragma warning(disable:4996)
#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "Buyer.h"

// Consts
const int BUYER_OPTION = 1;
const int SELLER_OPTION = 2;
const int BUYERSELLER_OPTION = 3;
const int STOP = -10;
const int WISH_EXIT = 4;
const int NAME_LEN = 31;
const int FEED_LEN = 150;

// Forward Declaration
class Seller;
class Buyer;
class Feedback;
class Date;
class BuyerSeller;
class User;



class System
{
private:
	char		m_systemName[NAME_LEN];			
	User**		m_users;
	int			m_users_log_size, m_users_phy_size;
	int			m_buyerseller_count;


public:
// C'tors and D'tor
	System() = delete;
	System(const char* name);
	System(const System&) = delete;
	~System();
	
// Const methods
	inline const User**		getUsers()			const { return (const User**)m_users; } // # WHY CAN'T REMOVE CONST?
	inline int				getUsersLogSize()	const { return m_users_log_size; }
	inline int				getUsersPhySize()	const { return m_users_phy_size; }


	const Buyer*			GetBuyer(int index)						const;
	const Buyer*			GetBuyer(const char* username)			const;
	const Seller*			getSeller(int index)					const;
	const BuyerSeller*		getBuyerSeller(int index)				const;
	bool					isAvailableUsername(const char* name)	const;
	void					showAllProducts()						const;
	
// Non-const methods
	User*					AccessAccount(const char* name, int password, const char* type);
	bool					AddUser(User* new_user);
	bool					addFeedbackToSeller(const char* sellerUsername, const Feedback* buyerFeedback);

// Menu Options
	void					runMenu();
	void					createNewAccount();
	bool					AddAccountToSystem(const char* name, int password, int accountType);
	void					accessAccountMenu();
	void					ShowUsersMenu()							const;
	void					ShowTypeUsers(const char* user_type)	const;
	void					ShowAllUsers()							const;
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

// Buyer-Seller related functions
	void					RunBuyerSellerMenu(BuyerSeller* buyer_seller);

// Operations Menu
	void					OperatorsTestMenu();
	void					AddUserThroughOperator();
	Buyer*					CreateAndSendBuyer();
	Seller*					CreateAndSendSeller();
	BuyerSeller*			CreateAndSendBuyerSeller();
	void					CompareUsers()							const;
	void					OstreamOperatorTest();					// Not const for the option of adding a user if needed.
	void					PrintBuyer();
	void					PrintSeller();
	void					PrintBuyerSeller();


// Operators
	System&					operator+=(Buyer* buyer);
	System&					operator+=(const Buyer& buyer);
	System&					operator+=(Seller* seller);
	System&					operator+=(const Seller& buyer); // #
	System&					operator+=(BuyerSeller* buyerseller);
	System&					operator+=(const BuyerSeller& buyer);





private:
// Private methods
	int						printMainMenuOptions();
	int						readAccountType();
	bool					ReadNewUserDetails(char* username, int& password);
	bool					ReadDataAheadOfFeedback(char* product_name, char* seller_name, const Buyer* buyer);
	bool					continueCheck();
	Feedback*				createFeedback(const Product* prod, const Buyer* feedbackGiver);
	Address					createAddress();
	Date					createDate();
	User*					GetAccount(const char* type);
	void					cleanBuffer(); // # LIAR
	void					readProductName(char* name) const;
	int						wishlistMenuOptions();
	int						chooseFromAvailableProducts(const Product** availProducts, int availProductsCount);
	bool					CheckAndIncreaseArrayIfNeeded();
};
#endif 