#include "System.h"
#include "ValidationHelper.h"
#include <typeinfo.h>
#include <string>

// ----------------- MAIN MENU ----------------- //
void System::RunMainMenu()
/*
This runs the menu of the system.
Through this menu the user navigates to all possible functions in the program.
*/
{
	unsigned short int optionAnswer;
	bool exit = false;

	while (!exit)
	{
		cout << "Main Menu\n";
		cout << "\t1) Create new account\n"; // Leads to a mini-menu.
		cout << "\t2) Sign in\n"; // Leads to a mini-menu.
		cout << "\t3) Show users\n"; // Leads to a mini-menu.
		cout << "\t4) Show products\n";
		cout << "\t5) Test Operators\n";
		cout << "\t6) Load\\Save file\n";
		cout << "\t7) Exit\n";
		
		cout << "\n\tChoose an option: ";
		cin >> optionAnswer;
		cout << endl;

		switch (optionAnswer)
		{
		case 1:
			CreateAndAddUser(readAccountType());
			break;
		case 2:
			accessAccountMenu();
			break;
		case 3:
			ShowUsersMenu();
			break;
		case 4:
			showProductsMenu();
			break;
		case 5:
			OperatorsTestMenu();
			break;
		case 6:
			FilesMenu();
			break;
		default:	// Exit.
			exit = true;
			break;
		}
	}//while
	cout << endl;
}
User* System::CreateAndAddUser(int account_type)
{
	if (account_type != BUYER_OPTION && account_type != SELLER_OPTION && account_type != BUYERSELLER_OPTION)	//	User chose a type which doesn't exist.
		return nullptr;

	string			username;
	int				password;

	if (!ReadNewUserDetails(username, password))
		return nullptr;

	User* new_user;

	switch (account_type)
	{
	case (BUYER_OPTION):
		new_user = new Buyer(username, password, createAddress());
		break;
	case(SELLER_OPTION):
		new_user = new Seller(username, password, createAddress());
		break;
	case(BUYERSELLER_OPTION):
		new_user = new BuyerSeller(username, password, createAddress());
		break;
	default:
		return nullptr;
	}
	ValidationHelper::AllocationCheck<User*>(new_user);

	*this += *new_user;

	cout << "\nSuccessfully added " << typeid(*(new_user)).name() + 6 << "." << endl << endl;
	return new_user;
}
int System::readAccountType()
{
	int accountType;

	cout << "What sort of account would you like to create?\n";
	cout << "\t1) Buyer\n";
	cout << "\t2) Seller\n";
	cout << "\t3) Buyer and Seller\n";
	cout << "\t4) Back\n";
	cout << "\n\tChoose an option: ";
	cin >> accountType;
	cout << endl;
	while (accountType < 1 || accountType > 4)
	{
		cout << "\tPlease enter an option within the range: ";
		cin >> accountType;
	}

	return accountType;
}
bool System::ReadNewUserDetails(string& name, int& password)
/*
This method receives two parameters and handles the reading of data into them.
If the user decides to stop trying, the method returns false to indicate that no data was read.
*/
{
	bool uContinue = true;
	while (uContinue)
	{
		cin.ignore();
		cout << "\tChoose username: ";
		getline(cin, name);
		// cin.getline(name, NAME_LEN);
		if (!IsAvailableUsername(name)) // Check if name exists.
		{
			cout << "Username is already taken. Would you like to try another one? ";
			if (!ValidationHelper::continueCheck())
				return false;
		}
		else
		{
			cout << "\tChoose password: ";
			cin >> password;
			uContinue = false;
			cout << endl;
		}
	}
	return true;
}
bool System::IsAvailableUsername(const string& name)		const
/*
This function receives a username, and checks if it already exists in the system.
*/
{
	for (auto u : m_users)
		if (u->m_username == name)
			return false;

	return true;
}
Address System::createAddress()
{
	string		street;
	int			houseNumber;
	string		city;
	string		country;

	cin.ignore(); // Clean the buffer.

	cout << "Please enter the following details for a new address.\n";
	cout << "\tStreet: ";
	getline(cin, street);

	cout << "\tHouse number: ";
	cin >> houseNumber;

	cin.ignore();

	cout << "\tCity: ";
	getline(cin, city);

	cout << "\tCountry: ";
	getline(cin, country);

	return Address(street, houseNumber, city, country); // Move Constructor
}
void System::accessAccountMenu()
/*
The sign in option allows a user to sign into his account - a Buyer or a Seller.
It asks for the username as well as the password and checks that they're correct.
Once the user is signed in, he's given menu options exclusive to his account type.
Meaning Buyers have their own menu with buyer options, and like so with Sellers.
This allows a user to perform a sequence of actions related to his account,
without always needing to provide his username and password.
So he can move from adding items to his wishlist, to his cart, to checkout,
without always going through the main menu.
*/
{
	cout << "Which account type would you like to sign in as?\n";
	cout << "\t1) Buyer\n";
	cout << "\t2) Seller\n";
	cout << "\t3) BuyerSeller\n";
	cout << "\n\tChoose an option: ";
	int user_type;
	cin >> user_type;
	cout << endl;

	switch (user_type)
	{
	case 1:
	{
		Buyer* buyer = dynamic_cast<Buyer*>(GetAccount(typeid(Buyer).name())); 
		if (!buyer)
			return;
		cout << "\nBuyer log in successful.\n\n";
		runBuyerMenu(buyer);
		break;
	}
	case 2:
	{
		Seller* seller = dynamic_cast<Seller*>(GetAccount(typeid(Seller).name())); 
		if (!seller)
			return;
		cout << "\nSeller log in successful.\n\n";
		runSellerMenu(seller);
		break;
	}
	case 3:
	{
		BuyerSeller* buyer_seller= dynamic_cast<BuyerSeller*>(GetAccount(typeid(BuyerSeller).name()));
		if (!buyer_seller)
			return;
		cout << "\nBuyer-Seller log in successful.\n\n";
		RunBuyerSellerMenu(buyer_seller);
		break;
	}
	default:
		return;
	}
}
User* System::AccessAccount(const string& name, int password, const string& type)
/*
This function provides access to a Buyer Account for the user.
This allows the user to take actions with his account, such as adding to wishlist, checking out, etc.
*/
{
	for(auto u:m_users) // Go over all users
	{

		if (u->m_username == name)	//	Found the username
		{
			if (typeid(*(u)).name() == type) // Check that the account is of the right type
			{
				bool validAccess = u->passwordCheck(password);
				if (validAccess)
					return (u);
				else
					return nullptr;
			}
		}
	}
	return nullptr;
}
User* System::GetAccount(const string& type)
{
	string name;
	int password;

	User* user = nullptr;
	bool uContinue = true;
	while (uContinue)
	{
		// Read the data from the user (name and password)
		cin.ignore();
		cout << "Enter username:\t";
		getline(cin, name);
		cout << "Enter password:\t";
		cin >> password;

		// Try to retrieve account based on name and password given
		user = AccessAccount(name, password, type); // Send to function that goes over the array with the parameters and searches for the user based on the type
		if (!user) // If didn't find the user
		{
			cout << "Username or password are incorrect. Would you like to try again? ";
			if (!ValidationHelper::continueCheck()) //	User doesn't want to continue. Unwritten Else - he wants to continue.
			{
				cout << endl;
				return nullptr;
			}
		}
		else
			uContinue = false;
	}
	return user;
}


// ----------------- SHOW METHODS ----------------- //
void System::ShowUsersMenu() const
{
	cout << "Who do you want to see?\n";
	cout << "\t1) Buyers\n";
	cout << "\t2) Sellers\n";
	cout << "\t3) Buyer-Sellers\n";
	cout << "\t4) garyoldmaneveryone.gif\n";
	cout << "\t5) Back\n";
	cout << "\n\tChoose an option: ";
	int choice;
	cin >> choice;
	cout << endl;

	switch (choice)
	{
	case 1:
		ShowUsersOfType(typeid(Buyer).name());
		break;
	case 2:
		ShowUsersOfType(typeid(Seller).name());
		break;
	case 3:
		ShowUsersOfType(typeid(BuyerSeller).name());
		break;
	case 4:
		ShowAllUsers();
		break;
	default:
		cout << "Invalid choice.\n";
		break;
	}
}
void System::ShowAllUsers() const
{
	if(m_users.empty())
	{
		cout << "No users in the store. It's trash.\n\n";
	}
	int i = 1;
	for (auto u : m_users)
	{
		cout << "User " << i++ << ":\n";
		cout << *u;
	}
}
void System::ShowUsersOfType(const string& user_type) const 
{
	if (m_users.empty())
	{
		cout << "No users in the system yet. This store is crap :D\n\n";
		return;
	}
	cout << endl;

	int count = 1; // A count to see how many users of the type we've found.
	for(auto u:m_users) // Go over all uers.
	{
		if (typeid(*(u)).name() == user_type) // Check if the user is of the requested type.
		{
			cout << user_type.substr(6) << " " << count++ << endl;
			cout << *(u);
			cout << endl;
		}
	}
}
void System::PrintAllBuyers()
{
	if (Buyer::buyer_count == 0)
	{
		cout << "No buyers in the system. Create one:\n";
		User* temp = CreateAndAddUser(BUYER_OPTION);

		if (temp != nullptr)
		{
			cout << "\nDone creating the user. Now - drumroll - printing him!\n\n";
			cout << *temp << endl;
		}
		else
			cout << "No user was created. Nothing to print using operator<<.\n";
		return;
	}

	for(auto u:m_users)
	{
		if (typeid((*u)).name() == typeid(Buyer).name())
		{
			cout << *(u);
			return;
		}
	}
}
void System::PrintAllSellers()
{
	if (Seller::seller_count == 0)
	{
		cout << "No sellers in the system. Create one:\n";
		User* temp = CreateAndAddUser(SELLER_OPTION);

		if (temp != nullptr)
		{
			cout << "\nDone creating the user. Now - drumroll - printing him!\n\n";
			cout << *temp << endl;
		}
		else
			cout << "No user was created. Nothing to print using operator<<.\n";
		return;
	}

	for(auto u:m_users)
	{
		if (typeid(*(u)).name() == typeid(Seller).name())
		{
			cout << *(u);
			return;
		}
	}
}
void System::PrintAllBuyerSellers()
{
	if (BuyerSeller::buyer_seller_count == 0)
	{
		cout << "No buyers-sellers in the system. Create one:\n";
		User* temp = CreateAndAddUser(BUYERSELLER_OPTION);

		if (temp != nullptr)
		{
			cout << "\nDone creating the user. Now - drumroll - printing him!\n\n";
			cout << *temp << endl;
		}
		else
			cout << "No user was created. Nothing to print using operator<<.\n";
		return;
	}

	for(auto u:m_users)
	{
		if (typeid(*(u)).name() == typeid(BuyerSeller).name())
		{
			cout << *(u);
			return;
		}
	}
}
void System::showProductsMenu() const
/*
This function allows the user to show either a specific product, or all products.
*/
{
	int option;
	cout << "Show Products\n";
	cout << "\t1) Show specific product (search by name)\n";
	cout << "\t2) Show all products\n";
	cout << "\n\t Choose an option: ";
	cin >> option;
	cout << endl;

	if (option == 1)
		showSpecificProduct();
	else if (option == 2)
		ShowAllProducts();
	else
		return;
}
void System::showSpecificProduct() const
/*
User chooses a product name to show, and the system goes over all its products,
searching for products with the same name.
*/
{
	string prodName;
	readProductName(prodName);
	int count = 0; // Count how many items in system.
	for(auto u:m_users)	//	 Go over all users, check sellers and buyers-sellers, and check their products.
	{
		if (typeid(*(u)).name() != typeid(Buyer).name())
		{
			const Product* prod = dynamic_cast<const Seller*>(u)->getProduct(prodName); // Search within seller (or buyer-seller) i for the product.
			if (prod) // Returned value isn't nullptr, meaning seller (or buyer-seller) i has the product.
			{
				prod->showProduct();
				cout << endl;
				count++;
			}
		}
	}
	if (count == 0)	//	Didn't find product at all.
		cout << "Item isn't sold by anyone. No one wants it.\n";
	else
		cout << count << " options in the store of " << prodName << endl; // State how many products overall (count)
	cout << endl;
}
void System::ShowAllProducts()	const //	A bit of a "brutish" method that just shows all the products
{
	int productCount = 0;

	for(auto u:m_users)
	{
		if (typeid(*(u)) != typeid(Buyer)) // If a Seller or BuyerSeller 
		{
			const Seller* temp = dynamic_cast<const Seller*>(u);
			if (temp->m_catalog.empty()==false) // If seller i has at least 1 product.
			{
				cout << "Products of " << temp->m_username << ": ";
				cout << endl;
				temp->showAllMerchandise();
				cout << endl;
				productCount += temp->m_catalog.size();
			}
		}
	}
	cout << "Total number of available products: " << productCount << endl << endl;
}


// ----------------- GETTERS METHODS ----------------- //
const Buyer* System::GetBuyer(int index) const
/*
This function receives an index for the array and returns the element in that array.
*/
{
	if (index < 0 || index > (int)m_users.size())
		return nullptr;
	if(typeid(*(m_users[index])).name()==typeid(Buyer).name())
		return dynamic_cast<Buyer*>(m_users[index]);
	return nullptr;
}
const Buyer* System::GetBuyer(const string& name) const
{
	for(auto u:m_users)
	{
		if(u->m_username==name) // Found matching username
			if (typeid(*(u)).name() == typeid(Buyer).name()) // Check that the user is actually a buyer
				return dynamic_cast<const Buyer*>(u);
	}
	return nullptr;
}
const Seller* System::GetSeller(int index) const
{
	if (index < 0 || index > (int)m_users.size())
		return nullptr;
	if (typeid(*(m_users[index])).name() == typeid(Seller).name())
		return dynamic_cast<Seller*>(m_users[index]);
	return nullptr;
}
const BuyerSeller* System::GetBuyerSeller(int index) const
{
	if (index < 0 || index > (int)m_users.size())
		return nullptr;
	if (typeid(*(m_users[index])).name() == typeid(BuyerSeller).name())
		return dynamic_cast<BuyerSeller*>(m_users[index]);
	return nullptr;
}


// ========= USER SETTINGS FUNCTIONS ========= //
void System::RunUserSettingsMenu(User* user)
{

	bool fContinue = true;
	unsigned short int optionAnswer;
	while (fContinue)
	{
		cout << "User Menu:\n";
		cout << "\t1) Change username\n";
		cout << "\t2) Change password\n";
		cout << "\t3) Change address\n";
		cout << "\t4) Back\n";
		cout << "\n\t Choose an option: ";
		cin >> optionAnswer;
		cout << endl;
		switch (optionAnswer)
		{
		case 1:
			ChangeUsername(user);
			break;
		case 2:
			ChangePassword(user);
			break;
		case 3:
			ChangeAddress(user);
			break;
		default: // exit
			fContinue = false;
			break;
		}
	}//while
}
bool System::ChangeUsername(User* user)
{
	cin.ignore();
	cout << "Current username: " << user->m_username << endl;
	
	string new_username;
	cout << "Pick a new username: ";
	getline(cin, new_username);
	cout << endl;

	if (user->m_username == new_username) // Check that user didn't choose same username
	{
		cout << "You cannot pick the same username.\n\n";
		return false;
	}

	if (!IsAvailableUsername(new_username))
	{
		cout << "Username is already taken.\n\n";
		return false;
	}

	if (!user->setUsername(new_username))
	{
		cout << "Username has invalid characters.\n";
		return false;
	}
	cout << "Username updated.\n\n";
	return true;
}
bool System::ChangePassword(User * user)
{
	int new_password;
	int new_password_verification;
	int current_password_verification;

	cout << "Enter new password:\t";
	cin >> new_password;
	cout << "Enter it again:\t";
	cin >> new_password_verification;

	if (new_password != new_password_verification)
	{
		cout << "Passwords do not match.\n";
		return false;
	}

	cout << "Confirm current password:\t";
	cin >> current_password_verification;

	if (!user->setPassword(new_password, current_password_verification))
	{
		cout << "Failed resetting password. Either invalid characters or current password is incorrect.\n\n";
		return false;
	}
	cout << "Password updated.\n\n";
	return true;
}
bool System::ChangeAddress(User * user)
{
	Address& address = user->getAddress();
	cout << "Current Address:\n" << address << endl;

	string		street;
	int			houseNumber;
	string		city;
	string		country;

	cin.ignore(); // Clean the buffer.

	cout << "Please enter the following details for a new address.\n\n";

	cout << "\tStreet: ";
	getline(cin, street);
	while (address.setStreet(street) == false)
	{
		cout << "Invalid street name. Please choose again: ";
		getline(cin, street);
	}

	cout << "\tHouse number: ";
	cin >> houseNumber;
	while (address.setHouse(houseNumber) == false)
	{
		cout << "Invalid house number. Please choose again: ";
		cin >> houseNumber;
	}

	cin.ignore();	//	Clear the enter

	cout << "\tCity: ";
	getline(cin, city);
	while (address.setCity(city) == false)
	{
		cout << "Invalid city name. Please choose again: ";
		getline(cin, city);
	}

	cout << "\tCountry: ";
	getline(cin, country);
	while (address.setCountry(country) == false)
	{
		cout << "Invalid country name. Please choose again: ";
		getline(cin, country);
	}

	cout << "\nAddress updated.\n\n";
	return true;
}


// ========= BUYER FUNCTIONS ========= //
void System::runBuyerMenu(Buyer* buyer)
{
	bool fContinue = true;
	unsigned short int optionAnswer;
	while (fContinue)
	{
		cout << "\nBuyer Menu\n";
		cout << "\t1) Add feedback to seller\n";
		cout << "\t2) Add to wishlist\n";
		cout << "\t3) Add to cart\n";
		cout << "\t4) Checkout\n";
		cout << "\t5) Show wishlist\n";
		cout << "\t6) Show cart\n";
		cout << "\t7) Show purchased items\n";
		cout << "\t8) Edit account\n";
		cout << "\t9) Log out\n";
		cout << "\n\tChoose an option: ";	
		cin >> optionAnswer;
		cout << endl;
		switch (optionAnswer)
		{
		case 1:		//	add feedback to Seller; we check that feedback giver actually purchased from Seller
			CreateAndAddFeedback(buyer);
			break;
		case 2:		//	add product to cart of buyer
			addToWishlist(buyer);
			break;
		case 3:		//	perform order for buyer
			addToCart(buyer);
			break;
		case 4:		//	order payment for buyer
			checkout(buyer);
			break;
		case 5:
			buyer->getWishlist().showWishlist();
			break;
		case 6:
			buyer->getCart().showCart();
			break;
		case 7:
			buyer->ShowPurchasedItems();
			break;
		case 8:	
			RunUserSettingsMenu(buyer);
			break;
		default: // Exit.
			fContinue = false;
			break;
		}
	}//while
	cout << endl;
}//runBuyerMenu
void System::CreateAndAddFeedback(Buyer* buyer)
{
	if (buyer->getPurchaseHistory().empty()) // Check that buyer has even made any purchases, to even leave feedback about.
	{
		cout << "You've made no purchases. Nothing to leave feedback for you crook. Leaving a false review for something is just being a dick.\n\n";
		return;
	}
	
	PointerArray<Receipt>& history = buyer->getPurchaseHistory();
	int receipts_count = history.size(); // Num of receipts. Placed in a variable just for comfort and readability.

	string prodName, sellerName;

	if (!ReadDataAheadOfFeedback(prodName, sellerName, buyer)) // Fill in the data for product name and seller name.
		return;

	bool found = false;
	unsigned int size = history.size();
	for(unsigned int i=0;i<size;++i) // Go over all receipt.
	{		

		const Product* prod = history[i]->GetProduct(prodName, sellerName);	//	Search for the product in current receipt
		if (prod != nullptr) // Found the product within the receipt.
		{
			if (history[i]->LeftFeedbackForProduct(prod)) // Check if already left feedback for this product
			{
				cout << "You've already given feedback for this product.\n";
				return;
			}
			else // Found the product and confirmed feedback hasn't been made in the past
			{
				Feedback* buyerFeedback = createFeedback(prod, buyer);
				const Seller* seller = prod->getSeller();
				if (!addFeedbackToSeller(sellerName, *buyerFeedback))
				{
					cout << "Failure adding the feedback.\n";
					delete buyerFeedback;
					return;
				}
				if (!(history[i]->AddFeedbackToProd(prodName, sellerName, buyerFeedback)))
				{
					cout << "Failure adding the feedback.\n";
					delete buyerFeedback;
					return;
				}

				found = true;
			}
		}
	}
	if (!found)
		cout << "\nCouldn't find the product or seller in your history.\n\n";
}
bool System::addFeedbackToSeller(const string& sellerUsername, const Feedback& buyerFeedback)
{
	for(auto u:m_users)
	{
		if (typeid(*(u)).name() != typeid(Buyer).name()) // Check if seller or buyer-seller
		{
			if (u->m_username == sellerUsername) // Found the seller.
			{
				Seller* temp = dynamic_cast<Seller*>(u); // Just for readability.
				temp->addFeedback(buyerFeedback);
				return true;
			}
		}
	}//for
	return false;
}
bool System::ReadDataAheadOfFeedback(string& product_name, string& seller_name, const Buyer * buyer)
{
	while (true)
	{
		cin.ignore();
		cout << "Enter the following details for the feedback.\n";
		cout << "\tProduct name: ";
		cin >> product_name;
		cout << "\tSeller name: ";
		cin >> seller_name;

		if (buyer->m_username == seller_name) // Check that a BuyerSeller isn't trying to leave feedback for himself
		{
			cout << "Cannot leave feedback for yourself you hack.\n";
			cout << "Would you like to try again? ";
			if (!ValidationHelper::continueCheck())
				return false;
		}
		return true;
	}
	return true;

}
Feedback* System::createFeedback(const Product* prod, const Buyer* feedbackGiver) // Read the buyer's feedback.
{
	string content;
	cin.ignore();
	cout << "Enter your feedback:\t";
	getline(cin, content);
	cout << endl;
	Feedback* feedback = new Feedback(createDate(), *feedbackGiver, content, *prod);
	ValidationHelper::AllocationCheck(feedback);
	return feedback;
}
Date System::createDate()
{
	unsigned int day, month, year;
	cout << "Enter the following details for the date.\n";
	cout << "\tDay: ";
	cin >> day;
	cout << "\tMonth: ";
	cin >> month;
	cout << "\tYear: ";
	cin >> year;

	return Date(day, month, year);
}
void System::addToWishlist(Buyer* buyer)  
/*
In this function the user choose products to add to his wishlist.
He chooses by searching by product name, or by serial.
This function runs a menu loop where he can choose to search for items (by name or serial), choose to show all items, or choose to exit.
Choosing by name is more of a "broad search" to see all available options of a certain product (such as TV).
Choosing by serial is much more focused and efficient for the code; possible when the user knows what item he wants.
*/
{
	if (!buyer)
		return;

	if(Seller::seller_count==0)
	{
		cout << "No sellers in system. It is a time of great depression.\n\n";
		return;
	}

	vector<const Product*> availProducts;
	availProducts.reserve(Seller::GetSellerCount());
	int choice;

	do
	{
		choice = wishlistMenuOptions();

		if (choice == 1) // Search by name of product
		{
			availProducts.clear();
			string prodName;
			readProductName(prodName);

			for(auto u:m_users)//	Go over all users and search for existence of product at sellers or buyers-sellers.
			//for (int i = 0; i < (int)m_users.size(); i++) 
			{
				if (typeid(*(u)).name() != typeid(Buyer).name()) // Check if the user is either a seller or buyer-seller
				{
					Seller* temp = dynamic_cast<Seller*>(u);
					const Product* product = temp->getProduct(prodName);	//	In array of sellers, search seller i for the product.
					if (product != nullptr)	//	Seller returned something not-nullptr, meaning seller does have the item.
					{
						// Check if the user isn't trying to buy from himself (in the case of a BuyerSeller type user)
						if(product->m_seller->m_username==buyer->m_username) // Check that a BuyerSeller isn't trying to leave feedback for himself
							cout << "Cannot add products from your own store you weirdo.\n\n";
						else
						{
							availProducts.push_back(product);//	Add this product to the array of available products of this name.
						}
					}
				}
			}//for

			if(!availProducts.empty())
			{
				int userChoice = chooseFromAvailableProducts(availProducts); // Print all options and read user choice.
				const Product* chosenProduct = availProducts[userChoice];
				if (buyer->getWishlist().isWishlistedProduct(chosenProduct->getSerial()) == true)// Search for product in wishlist to see if it's already added
					cout << "Product is already in wishlist.\n\n";
				else
				{
					buyer->getWishlist().addToWishlist(chosenProduct);
					cout << "Product added to wishlist.\n\n";
				}
			}
		}
		else if (choice == 2) // Search by serial
		{
			int serial;
			cout << "\tEnter serial to search for: ";
			cin >> serial;
			cout << endl;

			const Product* product = nullptr;

			vector<User*>::iterator itr = m_users.begin();
			vector<User*>::iterator itr_end = m_users.end();

			for(;!product && itr!=itr_end;++itr)//	Go over all sellers until found the product by serial.
			{
				if (typeid(*(*itr)).name() != typeid(Buyer).name()) // Account is not a buyer - meaning it's either seller or buyerseller
					product = dynamic_cast<Seller*>(*itr)->getProduct(serial); // Within seller i out of all sellers, search for the product.
			}

			if (!product) // Couldn't find product.
				cout << "Product does not exist in the store. It's weird and suspicious.\n\n";
			else if (product->m_seller->m_username==buyer->m_username)  // Check if the user isn't trying to buy from himself (in the case of a BuyerSeller type user)
				cout << "Cannot add products from your own store you weirdo.\n\n";
			else if (buyer->getWishlist().isWishlistedProduct(product->getSerial()) == true) // Check if product is already in wishlist
				cout << "Product is already in wishlist.\n";
			else // Product exists and isn't yet in wishlist.
			{
				char choice;
				cout << "Do you want to add this product to your wishlist? (y\\n) \n\n";
				product->showProduct();
				cout << endl;
				cin >> choice;
				if (choice == 'y')
				{
					buyer->getWishlist().addToWishlist(product);
					cout << "Product added to your wishlist.\n\n";
				}

			}
		}
		else if (choice == 3) // Show all
			ShowAllProducts();	//	This makes it easier for the Buyer to choose the product names to search for, if he's unsure.
	} while (choice != WISH_EXIT);	//	For any other input we stop the loop.

	return;
}//addToWishlist
int System::wishlistMenuOptions()
{
	int choice;

	cout << "Wishlist Menu:\n";
	cout << "\t1) Search by name\n";
	cout << "\t2) Search by serial\n";
	cout << "\t3) Show all products\n";
	cout << "\t4) Back\n";
	cout << "\n\tChoose an option: ";

	cin >> choice;
	while (choice < 1 || choice > 4)
	{
		cout << "Invalid choice. Please pick a number within the range.\n";
		cin >> choice;
	}
	cout << endl;
	return choice;
}
int System::chooseFromAvailableProducts(vector<const Product*>& availProducts)
{
	int userChoice;

	cout << "The product is available at " << availProducts.size() << " sellers.\n\n";

	vector<const Product*>::iterator itr = availProducts.begin();
	vector<const Product*>::iterator itr_end = availProducts.end();

	for (int i = 1; itr!=itr_end; ++i, ++itr)
	{
		cout << "Option " << i << endl;
		cout << **itr << endl;
	}
	cout << endl;

	cout << "Choose an option number from the list above to add to your wishlist:   ";
	cin >> userChoice;
	while (userChoice<1 || userChoice>(int)availProducts.size())
	{
		cout << "Chosen option is not within range. Try again.\n";
		cin >> userChoice;
	}
	userChoice = userChoice - 1; // Minus 1 to fit the array's starting count from 0, whereas we displayed options starting from 1.
	return userChoice;
}
void System::addToCart(Buyer* buyer)
{
	if (!buyer)
		return;

	Wishlist& wishlist = buyer->getWishlist();
	Cart& cart = buyer->getCart();
	int wishLogSize = wishlist.getLogSize();
	if (wishLogSize == 0)	//	Check if wishlist is empty.
	{
		cout << "Wishlist is empty. Nothing to show.\n\n";
		return;
	}

	cout << "These are your options. Enter the ones you want, or " << STOP << " to stop.\n\n";	//	IMPROVE: find a better way to stop than an ugly negative const number
	wishlist.showWishlist();
	int prodNum;
	cout << "Choose a product: ";
	cin >> prodNum;
	cin.ignore();
	while (prodNum != STOP)
	{
		prodNum = prodNum - 1; //	Minus 1, because the options displayed to the user start from 1, not 0 like the array 
		if (prodNum<0 || prodNum>wishLogSize)
		{
			cout << "Enter a valid number:\t";
			cin >> prodNum;
			prodNum -= 1;
			getchar();
		}
		else
		{
			const Product* productAddress = wishlist.getProduct(prodNum);
			if (!productAddress)
				cout << "Failed to fetch product from wishlist.\n";
			else if (wishlist.getCartIndication(prodNum) == true)
				cout << "Product is already in cart.\n";
			else
			{
				if (cart.addToCart(*productAddress) == false)
					cout << "Failed to add to checkout queue.\n";
				wishlist.changeProductCartStatus(prodNum);
			}
		}
		cout << "Choose a product:\t";
		cin >> prodNum;
	}
	cin.ignore();
	cout << "\nItems added to your cart. You're one step closer to spending your hard-earned shekels.\n\n";
}
void System::checkout(Buyer* buyer)
{
	if (!buyer)
		return;

	Cart& buyerCart = buyer->getCart();
	buyerCart.showCart();
	if (buyerCart.getLogSize() == 0)
	{
		cout << "This cart is as empty as my bank account.\n\n";
		return;
	}

	cout << "Cost of all products is: " << buyerCart.getCost() << endl;
	if (!ValidationHelper::continueCheck())
		return;

	// Passed all the checks - Buyer definitely wants to buy. Proceed with checkout.
	Receipt* receipt = new Receipt(buyerCart);
	if (!receipt) // Allocation check.
	{
		cout << "Problem checking out Process cancelled, no payment made.\n\n";
		return;
	}
	if (!buyer->Checkout(*receipt))
	{
		cout << "Failed to proceed to checkout. Process cancelled, no payment made.\n\n";
		delete receipt;
		return;
	}
	cout << "Checkout successful. Congratulations on your materialism.\n\n";
}


// ========= SELLER FUNCTIONS ========= //
void System::runSellerMenu(Seller* seller)
{
	bool fContinue = true;
	unsigned short int optionAnswer;
	while (fContinue)
	{
		cout << "\nSeller Menu\n";
		cout << "\t1) Add item to catalog\n";
		cout << "\t2) Show catalog\n";
		cout << "\t3) Show all feedbacks\n";
		cout << "\t4) Edit account\n";
		cout << "\t5) Log out\n";
		cout << "\n\tChoose an option: ";
		cin >> optionAnswer;
		cout << endl;
		switch (optionAnswer)
		{
		case 1:
			addItemToSeller(seller);
			break;
		case 2:
			seller->showAllMerchandise();
			break;
		case 3:
			seller->showAllFeedbacks();
			break;
		case 4:	//	exit
			RunUserSettingsMenu(seller);
			break;
		default: // exit
			fContinue = false;
			break;
		}
	}//while
	cout << endl;
}
void System::addItemToSeller(Seller* seller)
{
	if (!seller)
		return;

	bool uContinue = true;
	string prodName;
	while (uContinue)
	{
		cout << "\tEnter product name: ";
		cin >> prodName;
		getchar(); 
		if (seller->getProduct(prodName) != nullptr)		//	Product exists
		{
			cout << "A product by that name already exists. Would you like trying a different name? ";
			if (!ValidationHelper::continueCheck())
				return;
		}
		else	//	Product doesn't exist.
			uContinue = false;
	}

	double price;
	cout << "\tSet price: ";
	cin >> price;
	if (price <= 0)
	{
		cout << "Unable to add a product with 0 or negative cost. We're here to make money.\n\n";
		return;
	}

	int cat;
	Product::eCategory category;
	cout << "Categories:\n\t1) Children\n\t2) Electricity\n\t3) Office\n\t4) Clothing\nChoose a category:\t ";
	cin >> cat;
	category = (Product::eCategory)(cat - 1);
	cout << endl << endl;
	int index = seller->getCatalogLogSize();
	Product* newProd = new Product(prodName, price, category, seller, index);
	ValidationHelper::AllocationCheck<Product*>(newProd);
	seller->addProductToMerch(*newProd);
}


// ========= BUYERSELLER FUNCTIONS ========= //
void System::RunBuyerSellerMenu(BuyerSeller* buyerseller)
{
	bool fContinue = true;
	unsigned short int optionAnswer;
	while (fContinue)
	{
		cout << "\nBuyer-Seller Menu\n";
		cout << "\t1) Add feedback to seller\n";
		cout << "\t2) Add to wishlist\n";
		cout << "\t3) Add to cart\n";
		cout << "\t4) Checkout\n";
		cout << "\t5) Show wishlist\n";
		cout << "\t6) Show cart\n";
		cout << "\t7) Add item to catalog\n";
		cout << "\t8) Show catalog\n";
		cout << "\t9) Show all feedbacks\n";
		cout << "\t10) Edit user\n";
		cout << "\t11) Log out\n";
		cout << "\n\tChoose an option: ";
		cin >> optionAnswer;
		cout << endl;
		
		// Use temp variables here because the functions expect pointers to either Buyers or Sellers
		Buyer* buyer = dynamic_cast<Buyer*>(buyerseller); 
		Seller* seller = dynamic_cast<Seller*>(buyerseller);

		switch (optionAnswer)
		{
		case 1:		//	add feedback to Seller; we check that feedback giver actually purchased from Seller
			CreateAndAddFeedback(buyer);
			break;
		case 2:		//	add product to cart of buyer
			addToWishlist(buyer);
			break;
		case 3:		//	perform order for buyer
			addToCart(buyer);
			break;
		case 4:		//	order payment for buyer
			checkout(buyer);
			break;
		case 5:
			buyer->getWishlist().showWishlist();
			break;
		case 6:
			buyer->getCart().showCart();
			break;
		case 7:
			addItemToSeller(seller);
			break;
		case 8:
			seller->showAllMerchandise();
			break;
		case 9:
			seller->showAllFeedbacks();
			break;
		case 10:
			RunUserSettingsMenu(buyerseller);
			break;
		default: // Exit
			fContinue = false;
			break;
		}
	}//while
	cout << endl;
}


// ========= OPERATORS FUNCTIONS ========= //
void System::OperatorsTestMenu()
{
	bool fContinue = true;
	unsigned short int optionAnswer;
	while (fContinue)
	{
		cout << "Operators Test Menu\n";
		cout << "\t1) += operator\n";
		cout << "\t2) Buyer comparison (> or <) operator\n";
		cout << "\t3) operator<<\n";
		cout << "\t4) Back\n";
		cout << "\n\tChoose an option: ";
		cin >> optionAnswer;
		cout << endl;
		switch (optionAnswer)
		{
		case 1:
			AddUserThroughOperator();
			break;
		case 2:
			CompareUsers();
			break;
		case 3:
			OstreamOperatorTest();
			break;
		default:
			fContinue = false;
			break;
		}
	}
	cout << endl;
}
void System::CompareUsers() const
{
	string name1, name2;
	cin.ignore();
	cout << "Enter name of Buyer 1:\t";
	getline(cin, name1);
	cin.ignore();
	cout << "Enter name of Buyer 2:\t";
	getline(cin, name2);
	const Buyer* b1 = GetBuyer(name1);
	const Buyer* b2 = GetBuyer(name2);

	if (!b1 || !b2)
	{
		cout << "Couldn't find buyers by those names.\n\n";
		return;
	}

	cout << "Costs:\n\n\t";
	cout << b1->getWishlist().GetWishlistTotalCost() << " compared against " << b2->getWishlist().GetWishlistTotalCost() << endl;

	cout << "Which operator would you like to check?\n";
	cout << "\t1) >\n";
	cout << "\t2) >=\n";
	cout << "\t3) ==\n";
	cout << "\t4) <=\n";
	cout << "\t5) <\n";
	cout << "\t6) Back\n";
	cout << "\n\tChoose an option: ";
	int option;
	bool uContinue = true;
	while (uContinue)
	{
		cout << endl;
		cin >> option;
		switch (option)
		{
		case 1:
			if (*b1 > *b2)
				cout << "Result: TRUE\n\n";
			else
				cout << "Result: FALSE\n\n";
			break;
		case 2:
			if (*b1 >= *b2)
				cout << "Result: TRUE\n\n";
			else
				cout << "Result: FALSE\n\n";
			break;
		case 3:
			if (*b1 == *b2)
				cout << "Result: TRUE\n\n";
			else
				cout << "Result: FALSE\n\n";
			break;
		case 4:
			if (*b1 <= *b2)
				cout << "Result: TRUE\n\n";
			else
				cout << "Result: FALSE\n\n";
			break;
		case 5:
			if (*b1 < *b2)
				cout << "Result: TRUE\n\n";
			else
				cout << "Result: FALSE\n\n";
			break;
		default:
			uContinue = false;
			break;
		}
	}
}
void System::AddUserThroughOperator()
{
	unsigned short type;
	cout << "Which type of user would you like to add?\n";
	cout << "\t1) Buyer\n";
	cout << "\t2) Seller\n";
	cout << "\t3) BuyerSeller\n";
	cout << "\t4) Back\n";
	cout << "\n\tChoose an option: ";

	cin >> type;

	switch (type)
	{
	case 1: // Buyer
		CreateAndAddUser(BUYER_OPTION);
		break;
	case 2: // Seller
		CreateAndAddUser(SELLER_OPTION);
		break;
	case 3: // BuyerSeller
		CreateAndAddUser(BUYERSELLER_OPTION);
		break;
	default:
		return;
	}
}
void System::OstreamOperatorTest()
{
	cout << "What would you like to print through operator<< ?\n";
	cout << "Note: the program will print the first user of the specified type it finds.\n";
	cout << "If one doesn't exist, you'll be asked to make one to add to the system.\n\n";
	bool fContinue = true;
	unsigned short int optionAnswer;
	while (fContinue)
	{
		cout << "\t1) Buyer\n";
		cout << "\t2) Seller\n";
		cout << "\t3) BuyerSeller\n";
		cout << "\t4) Back\n";

		cout << "\n\tChoose an option: ";
		cin >> optionAnswer;
		cout << endl;

		switch (optionAnswer)
		{
		case 1:
			PrintAllBuyers();
			break;
		case 2:
			PrintAllSellers();
			break;
		case 3:
			PrintAllBuyerSellers();
			break;
		default: // Exit.
			fContinue = false;
			break;
		}
	}
}
System & System::operator+=(User & user)
{
	m_users.push_back(&user);
	return *this;
}


// ----------------- FILES ----------------- //
void System::FilesMenu() 
{
	int option;
	cout << "Files Menu:\n";
	cout << "\t1) Load users\n";
	cout << "\t2) Save users\n";
	cout << "\t3) Back\n";
	cout << "\n\tChoose an option: ";
	cin >> option;
	cout << endl;

	switch (option)
	{
	case 1:
		LoadUsers();
		break;
	case 2:
		SaveUsers();
		break;
	default:
		return;
	}
}
void System::LoadUsers()
{
	cout << "Warning: loading new users will delete all the current users. Would you like to continue? ";
	if (!ValidationHelper::continueCheck())
		return;

	string file_name;
	cout << "\n\tEnter file name to load: ";
	cin >> file_name;
	cout << endl;


	for (auto u : m_users)
		delete u;
	m_users.clear();

	ifstream in_file(file_name, ios::in);

	int num_of_users;
	in_file >> num_of_users;

	for (int i = 0; i < num_of_users; i++)
	{
		string type;
		in_file >> type;

		if (type == typeid(Buyer).name() + 6)
			m_users.push_back(new Buyer(in_file));
		else if(type== typeid(Seller).name() + 6)
			m_users.push_back(new Seller(in_file));
		else
			m_users.push_back(new BuyerSeller(in_file));
	}

	in_file.close();
	cout << "\tDone loading from file.\n\n";
}
void System::SaveUsers() const
{
	string file_name;
	cin.ignore();
	cout << "\tEnter name of file: ";
	cin >> file_name;
	cout << endl;

	ofstream out_file(file_name, ios::trunc);

	out_file << (int)m_users.size() << endl; // Save num of users
	for (auto u:m_users)
	{
		const User* user = u; // Temp just for readability
		out_file << typeid(*user).name() + 6 << " " << *user<< endl;
	}
	out_file.close();

	cout << "File saved.\n\n";
}


// ----------------- PRIVATE METHODS ----------------- //

void System::readProductName(string& name) const
{
	cin.ignore();
	cout << "\tEnter name of product: ";
	getline(cin, name);
	cout << endl;
}
