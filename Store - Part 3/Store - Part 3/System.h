#pragma warning(disable:4996)
#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "BuyerSeller.h"

// Consts
const int BUYER_OPTION = 1;
const int SELLER_OPTION = 2;
const int BUYERSELLER_OPTION = 3;
const int STOP = -10;
const int WISH_EXIT = 4;

// Forward Declaration
class Seller;
class Feedback;
class Date;
class BuyerSeller;
class User;


class System
{
private:
	string						m_system_name;
	vector<User*>				m_users;

public:
// C'tors and D'tor
	System() = delete;
	System(const string& name) : m_system_name(name) {}
	System(const System&) = delete;


// Main Menu Options
	void						RunMainMenu();
	User*						CreateAndAddUser(int account_type);
	int							readAccountType();
	bool						ReadNewUserDetails(string& username, int& password);
	Address						createAddress();
	bool						IsAvailableUsername(const string& name)	const;
	void						accessAccountMenu();
	User*						AccessAccount(const string& name, int password, const string& type);
	User*						GetAccount(const string& type);


// Show Methods
	void						ShowUsersMenu()							const;
	void						ShowUsersOfType(const string& user_type)const;
	void						ShowAllUsers()							const;
	void						showProductsMenu()						const;
	void						showSpecificProduct()					const;
	void						ShowAllProducts()						const;
	void						PrintAllBuyers();
	void						PrintAllSellers();
	void						PrintAllBuyerSellers();

	
// Const methods
	inline const vector<User*>	GetUsersArray()							const	{ return m_users; } 
	inline int					GetUsersArrayLogSize()					const	{ return (int)m_users.size(); }
	const Buyer*				GetBuyer(int index)						const;
	const Buyer*				GetBuyer(const string& username)		const;
	const Seller*				GetSeller(int index)					const;
	const BuyerSeller*			GetBuyerSeller(int index)				const;
	void						readProductName(string& name)			const;
	

// User Settings related functions
	void						RunUserSettingsMenu(User* user);
	bool						ChangeUsername(User* user);
	bool						ChangePassword(User* user);
	bool						ChangeAddress(User* user);


// Buyer related functions
	void						runBuyerMenu(Buyer* buyer);
	void						CreateAndAddFeedback(Buyer* buyer);
	bool						addFeedbackToSeller(const string& sellerUsername, const Feedback& buyerFeedback);
	Feedback*					createFeedback(const Product* prod, const Buyer* feedbackGiver);
	bool						ReadDataAheadOfFeedback(string& product_name, string& seller_name, const Buyer* buyer);
	Date						createDate();
	void						addToWishlist(Buyer* buyer);
	int							chooseFromAvailableProducts(vector<const Product*>& availProducts);
	int							wishlistMenuOptions();
	void						addToCart(Buyer* buyer);
	void						checkout(Buyer* buyer);


// Seller related functions
	void						runSellerMenu(Seller* seller);
	void						addItemToSeller(Seller* seller);


// Buyer-Seller related functions
	void						RunBuyerSellerMenu(BuyerSeller* buyer_seller);


// Operators And Operations Menu
	void						OperatorsTestMenu();
	void						AddUserThroughOperator();
	void						CompareUsers()							const;
	void						OstreamOperatorTest();					// Not const for the option of adding a user if needed.
	System&						operator+=(User& user);


public: // Files
	void						FilesMenu();
	void						LoadUsers();
	void						SaveUsers()	const;
};

#endif 
