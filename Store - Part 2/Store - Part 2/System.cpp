#include "System.h"
#include "BuyerSeller.h"
#include <typeinfo.h>
#include <iostream>
#include <string.h>
using namespace std;

// ----------------- C'TORS AND D'TOR ----------------- //
System::System(const char* name)
{
	strcpy(m_systemName, name);
	
	m_users_phy_size = 20;
	m_users_log_size = 0;
	m_users = new User*[m_users_phy_size];
	if (!m_users)
		exit(1);
	m_users[0] = nullptr;

}
System::~System()
{
	for (int i = 0; i < m_users_log_size; i++)
		delete m_users[i];
	delete[]m_users;
}


// ----------------- MENU ----------------- //
void System::runMenu()
/*
This runs the menu of the system.
Through this menu the user navigates to all possible functions in the program.
*/
{
	bool exit = false;
	while (!exit)
	{
		unsigned short int optionAnswer = printMainMenuOptions();

		switch (optionAnswer)
		{
		case 1:
			createNewAccount();
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
		case 6:	// Exit.
			exit = true;
			break;
		}
	}//while
	cout << endl;
}
void System::createNewAccount() // Create a new user.
{
	int accountType = readAccountType(); // Read what kind of account user wants to create.
	if (accountType == 4)	//	User chose to stop the process.
		return;

	char name[NAME_LEN];
	int password;
	if (!ReadNewUserDetails(name, password))	//	User chooses name for his account. Returns false if name is taken and user gives up.
		return;

	if (AddAccountToSystem(name, password, accountType) == false)
		cout << "Failed to add account. Account deleted. :D\n";
	cout << endl;
}
bool System::AddAccountToSystem(const char* name, int password, int accountType)
{
	switch (accountType)
	{
	case BUYER_OPTION:
	{
		User* buyer = new Buyer(name, password, createAddress());
		if (buyer == nullptr)
		{
			cout << "Failed to create new buyer.\n";
			return false;
		}
		if (!AddUser(buyer))
		{
			delete buyer;
			return false;
		}
		break;
	}
	case SELLER_OPTION:
	{
		User* seller = new Seller(name, password, createAddress());
		if (seller == nullptr)
		{
			cout << "Failed to create new seller.\n";
			return false;
		}
		if (!(AddUser(seller)))
		{
			delete seller;
			return false;
		}
		break;
	}
	case BUYERSELLER_OPTION:
	{
		User* buyer_seller = new BuyerSeller(name, password, createAddress());
		if (buyer_seller == nullptr)
		{
			cout << "Failed to create new seller.\n";
			return false;
		}
		if (!(AddUser(buyer_seller)))
		{
			delete buyer_seller;
			return false;
		}
		m_buyerseller_count++;
		break;
	}
	}
	return true;
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
	cout << "\t1) Buyer\n\t2) Seller\n\t3) BuyerSeller\n";
	int user_type;
	cin >> user_type;

	switch (user_type)
	{
	case 1:
	{
		Buyer* buyer = dynamic_cast<Buyer*>(GetAccount(typeid(Buyer).name())); 
		if (!buyer)
			return;
		cout << "Buyer log in successful.\n\n";
		runBuyerMenu(buyer);
		break;
	}
	case 2:
	{
		Seller* seller = dynamic_cast<Seller*>(GetAccount(typeid(Seller).name())); 
		if (!seller)
			return;
		cout << "Seller log in successful.\n\n";
		runSellerMenu(seller);
		break;
	}
	case 3:
	{
		BuyerSeller* buyer_seller= dynamic_cast<BuyerSeller*>(GetAccount(typeid(BuyerSeller).name()));
		if (!buyer_seller)
			return;
		cout << "Buyer-Seller log in successful.\n\n";
		RunBuyerSellerMenu(buyer_seller);
		break;
	}
	default:
		return;
	}
}
void System::ShowUsersMenu() const
{
	cout << "Choose which type of user to show:\n";
	cout << "\t1) Buyers\n";
	cout << "\t2) Sellers\n";
	cout << "\t3) Buyer-Sellers\n";
	cout << "\t4) All\n";
	cout << "\t5) Back\n";
	int choice;
	cin >> choice;

	switch (choice)
	{
	case 1:
		ShowTypeUsers(typeid(Buyer).name());
		break;
	case 2:
		ShowTypeUsers(typeid(Seller).name());
		break;
	case 3:
		ShowTypeUsers(typeid(BuyerSeller).name());
		break;
	case 4:
		ShowAllUsers();
		break;
	default:
		cout << "Invalid choice.\n";
		break;
	}
}
void System::ShowTypeUsers(const char* user_type) const
{
	if (m_users_log_size == 0)
	{
		cout << "No users in the system yet. This store is crap :D\n\n";
		return;
	}
	cout << endl;

	int count = 0; // A count to see how many users of the type we've found.
	for (int i = 0; i < m_users_log_size; i++) // Go over all the users.
	{
		if (typeid(*(m_users[i])).name() == user_type) // Check if the user is of the requested type.
		{
			cout << user_type + 6 << count << endl;
			cout << *(m_users[i]);
			cout << endl;
			++count;
		}
	}
}
void System::ShowAllUsers() const
{
	if (m_users_log_size == 0)
	{
		cout << "No users in the store. It's trash.\n";
	}
	for (int i = 0; i < m_users_log_size; i++)
	{
		cout << "User number " << i + 1 << endl;
		cout << *(m_users[i]);
		cout << endl;
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
	cin >> option;

	if (option == 1)
		showSpecificProduct();
	else if (option == 2)
		showAllProducts();
	else
		return;
}
void System::showSpecificProduct() const
/*
User chooses a product name to show, and the system goes over all its products,
searching for products with the same name.
*/
{
	char prodName[NAME_LEN];
	readProductName(prodName);
	int count = 0; // Count how many items in system.
	for (int i = 0; i < m_users_log_size; i++)	//	 Go over all users, check sellers and buyers-sellers, and check their products.
	{
		if (typeid(*(m_users[i])).name() != typeid(Buyer).name())
		{
			const Product* prod = dynamic_cast<Seller*>(m_users[i])->getProduct(prodName); // Search within seller (or buyer-seller) i for the product.
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


// ----------------- CONST METHODS ----------------- //
const Buyer* System::GetBuyer(int index) const
/*
This function receives an index for the array and returns the element in that array.
*/
{
	if (index < 0 || index > m_users_log_size)
		return nullptr;
	if(typeid(*(m_users[index])).name()==typeid(Buyer).name())
		return dynamic_cast<Buyer*>(m_users[index]);
	return nullptr;
}
const Buyer* System::GetBuyer(const char* name) const
{
	for (int i = 0; i < m_users_log_size; i++)
	{
		if(strcmp(m_users[i]->getUsername(), name)==0) // Found matching username
			if (typeid(*(m_users[i])).name() == typeid(Buyer).name()) // Check that the user is actually a buyer
				return dynamic_cast<Buyer*>(m_users[i]);
	}
	return nullptr;
}
const Seller* System::getSeller(int index) const
{
	if (index < 0 || index > m_users_log_size)
		return nullptr;
	if (typeid(*(m_users[index])).name() == typeid(Seller).name())
		return dynamic_cast<Seller*>(m_users[index]);
	return nullptr;
}
const BuyerSeller* System::getBuyerSeller(int index) const
{
	if (index < 0 || index > m_users_log_size)
		return nullptr;
	if (typeid(*(m_users[index])).name() == typeid(BuyerSeller).name())
		return dynamic_cast<BuyerSeller*>(m_users[index]);
	return nullptr;
}
bool System::isAvailableUsername(const char* name)		const
/*
This function receives a username, and checks if it already exists in the system.
*/
{
	for (int i = 0; i < m_users_log_size; i++)
	{
		if (strcmp(m_users[i]->getUsername(), name) == 0) // Found identical existing username.
			return false;
	}	
	return true;
}
void System::showAllProducts()	const //	A bit of a "brutish" method that just shows all the products
{
	int productCount = 0;

	for (int i = 0; i < m_users_log_size; i++)
	{
		if (typeid(*(m_users[i])) != typeid(Buyer)) // If a Seller or BuyerSeller // # see if we can get the type outside the if check, to save function calls
		{
			Seller* temp = dynamic_cast<Seller*>(m_users[i]);
			if (temp->m_catLogSize > 0) // If seller i has at least 1 product.
			{
				cout << "Products of " << temp->m_username << ": ";
				cout << endl;
				temp->showAllMerchandise();
				cout << endl;
				productCount += temp->m_catLogSize;
			}
		}
	}
	cout << "Total number of available products: " << productCount << endl << endl;
}


// ----------------- NON-CONST METHODS ----------------- //
User* System::AccessAccount(const char* name, int password, const char* type)
/*
This function provides access to a Buyer Account for the user.
This allows the user to take actions with his account, such as adding to wishlist, checking out, etc.
*/
{
	for (int i = 0; i < m_users_log_size; i++)
	{
		if (strcmp(m_users[i]->getUsername(), name) == 0)	//	Found the username
		{
			if (typeid(*(m_users[i])).name() == type) // Check that the account is of the right type
			{
				bool validAccess = m_users[i]->passwordCheck(password);
				if (validAccess)
					return (m_users[i]);
				else
					return nullptr;
			}
		}
	}
	return nullptr;
}
bool System::AddUser(User* new_user)
{
	if (new_user == nullptr)
		return false;

	if ((CheckAndIncreaseArrayIfNeeded()) == false) // Check the array size. Check if failed to increase the array for some reason.
	{
		cout << "Array is full, and failed to increase size.\n";
		return false;
	}
	m_users[m_users_log_size] = new_user;
	++m_users_log_size;
	return true;
}
bool System::addFeedbackToSeller(const char* sellerUsername, const Feedback* buyerFeedback)
{
	for (int i = 0; i < m_users_log_size; i++)
	{
		if (typeid(*(m_users[i])).name() != typeid(Buyer).name()) // Check if seller or buyer-seller
		{
			if (strcmp(m_users[i]->m_username, sellerUsername) == 0) // Found the seller.
			{
				Seller* temp = dynamic_cast<Seller*>(m_users[i]); // Just for readability.
				if (!temp->addFeedback(buyerFeedback)) // If failed to add feedback.
					return false;
				else
					return true;
			}
		}
	}//for
	return false;
}


// ========= BUYER FUNCTIONS ========= //
void System::runBuyerMenu(Buyer*& buyer)
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
		cout << "\t7) Log out\n";
		cout << "Choose an option:   ";
		cin >> optionAnswer;
		while (optionAnswer < 1 || optionAnswer > 7)
		{
			cout << "Please enter a number within the range (1-7): ";
			cin >> optionAnswer;
		}
		cout << endl;
		switch (optionAnswer)
		{
		case 1:		//	add feedback to Seller; we check that feedback giver actually purchased from Seller
			addFeedbackToSeller(buyer);
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
		case 7:	//	exit
			fContinue = false;
			break;
		}
	}//while
	cout << endl;
}//runBuyerMenu
void System::addFeedbackToSeller(Buyer*& buyer)
{
	if (buyer->getPurchaseHistory().getLogSize() == 0) // Check that buyer has even made any purchases, to even leave feedback about.
	{
		cout << "You've made no purchases. Nothing to leave feedback for you crook. Leaving a false review for something is just being a dick.\n\n";
		return;
	}
	
	PurchaseHistory& history = buyer->getPurchaseHistory();
	int receipts_count = history.getLogSize(); // Num of receipts. Placed in a variable just for comfort and readability.
	Receipt**& all_receipts = history.getReceipts();

	char prodName[NAME_LEN], sellerName[NAME_LEN];
	if (!ReadDataAheadOfFeedback(prodName, sellerName, buyer)) // Fill in the data for product name and seller name.
		return;

	bool found = false;
	int i = 0;
	while (!found && i < receipts_count)	 // Loop until we've found the product, or until we've run out of receipts.
	{
		int receiptSize = all_receipts[i]->getNumOfProducts();	//	Get the 'i' receipt out of all the buyer's receipt.
		const Product** receiptProducts = all_receipts[i]->getProducts();	//	Get all products in the receipt.
		const Product* prod = all_receipts[i]->GetProduct(prodName, sellerName);	//	Search for the product in receipt 'i'
		if (prod == nullptr) // Couldn't find a match within receipt 'i'.
			i++;
		else if (all_receipts[i]->LeftFeedbackForProduct(prod)) // Check if already left feedback
		{
			cout << "You've already given feedback for this product.\n";
			return;
		}
		else // Found the product and confirmed feedback hasn't been made in the past
		{
			Feedback* buyerFeedback = createFeedback(prod, buyer);
			const Seller* seller = prod->getSeller();
			if (!addFeedbackToSeller(sellerName, buyerFeedback))
			{
				cout << "Failure adding the feedback.\n";
				delete buyerFeedback;
				return;
			}
			if (!all_receipts[i]->addFeedbackToProd(prodName, sellerName, buyerFeedback))
			{
				cout << "Failure adding the feedback.\n";
				delete buyerFeedback;
				return;
			}

			found = true;
		}
	}

	if (!found)
		cout << "\nCouldn't find the product or seller in your history.\n\n";
}
void System::addToWishlist(Buyer*& buyer)
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
	//if (m_seller_count + m_buyerseller_count == 0)
	{
		cout << "No sellers in system. It is a time of great depression.\n\n";
		return;
	}

	const Product** availProducts = nullptr;	//	Avoid allocating just yet - we allocate only if user searches by name, because in that case there could be several products.
	int choice;

	do
	{
		choice = wishlistMenuOptions();

		// # CHANGE TO SWITCH CASE AND EXPORT TO DIFFERENT FUNCTIONS
		if (choice == 1) // Search by name of product
		{
			char prodName[NAME_LEN];
			readProductName(prodName);

			int availProductsCount = 0;	//	A counter for how many products of the chosen name we've found.
			for (int i = 0; i < m_users_log_size; i++) //	Go over all users and search for existence of product at sellers or buyers-sellers.
			{
				if (typeid(*(m_users[i])).name() != typeid(Buyer).name()) // Check if the user is either a seller or buyer-seller
				{
					Seller* temp = dynamic_cast<Seller*>(m_users[i]);
					const Product* product = temp->getProduct(prodName);	//	In array of sellers, search seller i for the product.
					if (product != nullptr)	//	Seller returned something not-nullptr, meaning seller does have the item.
					{
						if (!availProducts) // If haven't allocated yet
						{
							//availProducts = new const Product*[m_seller_count+m_buyerseller_count];
							availProducts = new const Product*[Seller::seller_count]; // Allocate based on amount of sellers in store

							if (!availProducts) // Allocation check
							{
								cout << "Failure retrieving to wishlist.\n";
								return;
							}
						}
						availProducts[availProductsCount++] = product;	//	Add this product to the array of available products of this name.
					}
				}
			}//for

			if (availProductsCount > 0)
			{
				int userChoice = chooseFromAvailableProducts(availProducts, availProductsCount); // Print all options and read user choice.
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
			cout << "Enter serial to search for: ";
			cin >> serial;
			cout << endl;

			const Product* product = nullptr;
			int i = 0;
			while (!product && i < m_users_log_size)	//	Go over all sellers until found the product by serial.
			{
				// # change to outer function because this code repeats itself and is unclear
				if (typeid(*(m_users[i])).name() != typeid(Buyer).name()) // Account is not a buyer - meaning it's either seller or buyerseller
					product = dynamic_cast<Seller*>(m_users[i])->getProduct(serial); // Within seller i out of all sellers, search for the product.
				i++;
			}

			if (!product) // Couldn't find product.
				cout << "Product does not exist in the store. It's weird and suspicious.\n\n";
			else if (buyer->getWishlist().isWishlistedProduct(product->getSerial()) == true)
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
			showAllProducts();	//	This makes it easier for the Buyer to choose the product names to search for, if he's unsure.
	} while (choice != WISH_EXIT);	//	For any other input we stop the loop.

	if (availProducts)
		delete[]availProducts;
	return;
}//addToWishlist
void System::addToCart(Buyer*& buyer)
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
			cout << "Enter a valid number: ";
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
				if (cart.addToCart(productAddress) == false)
					cout << "Failed to add to checkout queue.\n";
				wishlist.changeProductCartStatus(prodNum);
			}
		}
		cout << "Choose a product: ";
		cin >> prodNum;
	}
	cin.ignore();
	cout << "Items added to your cart. You're one step closer to spending your hard-earned shekels.\n\n";
}
void System::checkout(Buyer*& buyer)
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
	if (continueCheck() == false)
		return;

	// Passed all the checks - Buyer definitely wants to buy. Proceed with checkout.
	Receipt* receipt = new Receipt(buyerCart);
	if (!receipt)
	{
		cout << "Problem checking out Process cancelled, no payment made.\n\n";
		return;
	}
	if (!buyer->proceedToCheckout(receipt))
	{
		cout << "Failed to proceed to checkout. Process cancelled, no payment made.\n\n";
		delete receipt;
		return;
	}
}


// ========= SELLER FUNCTIONS ========= //
void System::runSellerMenu(Seller*& seller)
{
	bool fContinue = true;
	unsigned short int optionAnswer;
	while (fContinue)
	{
		cout << "\nSeller Menu\n";
		cout << "\t1) Add item to catalog\n";
		cout << "\t2) Show catalog\n";
		cout << "\t3) Show all feedbacks\n";
		cout << "\t4) Log out\n";
		cout << "Choose an option:   ";
		cin >> optionAnswer;
		while (optionAnswer < 1 || optionAnswer > 4)
		{
			cout << "Please enter a number within the range: ";
			cin >> optionAnswer;
		}
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
			fContinue = false;
			break;
		}
	}//while
	cout << endl;
}
void System::addItemToSeller(Seller*& seller)
{
	if (!seller)
		return;

	bool uContinue = true;
	char prodName[NAME_LEN];
	while (uContinue)
	{
		cout << "Enter product name: ";
		cin >> prodName;
		getchar();
		if (seller->getProduct(prodName) != nullptr)		//	Product exists
		{
			cout << "A product by that name already exists. Would you like trying a different name? ";
			if (!continueCheck())
				return;
		}
		else	//	Product doesn't exist.
			uContinue = false;
	}

	double price;
	cout << "Set price: ";
	cin >> price;
	int cat;
	Product::eCategory category;
	cout << "Categories:\n\t1) Children\n\t2) Electricity\n\t3) Office\n\t4) Clothing\nChoose a category:   ";
	cin >> cat;
	category = (Product::eCategory)(cat - 1);
	cout << endl << endl;
	bool check;
	int index = seller->getCatalogLogSize();
	Product* newProd = new Product(prodName, price, category, seller, index, check);
	if (!check)
	{
		cout << "Error with adding the product to the system.\n\n";
		delete newProd;
	}
	else if (!seller->addProductToMerch(newProd))	//	 Failed to add to seller's array.
	{
		cout << "Failed to add the product to " << seller->getUsername() << "'s store.\n\n";
		delete newProd;
	}
}


// ========= BUYERSELLER FUNCTIONS ========= //
void System::RunBuyerSellerMenu(BuyerSeller* buyerseller) // # fix this if we have time
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
		cout << "\t10) Log out\n";
		cout << "Choose an option:   ";
		cin >> optionAnswer;
		while (optionAnswer < 1 || optionAnswer > 10)
		{
			cout << "Please enter a number within the range: ";
			cin >> optionAnswer;
		}
		cout << endl;
		
		Buyer* buyer = dynamic_cast<Buyer*>(buyerseller); // # does temp point to the same object within buyerseller?
		Seller* seller = dynamic_cast<Seller*>(buyerseller);

		switch (optionAnswer)
		{
		case 1:		//	add feedback to Seller; we check that feedback giver actually purchased from Seller
			addFeedbackToSeller(buyer);
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
		cout << "Choose an option:   ";
		cin >> optionAnswer;
		while (optionAnswer < 1 || optionAnswer > 10)
		{
			cout << "Please enter a number within the range: ";
			cin >> optionAnswer;
		}
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
		case 4:
			fContinue = false;
			break;
		}
	}
	cout << endl;
}
void System::CompareUsers() const
{
	char name1[NAME_LEN], name2[NAME_LEN];
	cin.ignore();
	cout << "Enter name of Buyer 1: ";
	cin >> name1;
	cin.ignore();
	cout << "Enter name of Buyer 2: ";
	cin >> name2;
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
	cout << "\t6) Back\n\n";
	int option;
	bool uContinue = true;
	while (uContinue)
	{
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
	cout << "Which type of user do you want to add?\n";
	cout << "\t1) Buyer\n";
	cout << "\t2) Seller\n";
	cout << "\t3) BuyerSeller\n";
	cout << "\t4) I regret everything, take me back :(\n";

	cin >> type;

	switch (type)
	{
	case 1: // Buyer
		CreateAndSendBuyer();
		break;
	case 2: // Seller
		CreateAndSendSeller();
		break;
	case 3:
		CreateAndSendBuyerSeller();
		break;
	default:
		return;
	}
}
Buyer* System::CreateAndSendBuyer()
{
	char			username[NAME_LEN];
	int				password;

	if (!ReadNewUserDetails(username, password))
		return nullptr;

	Buyer* newbuyer=new Buyer(username, password, createAddress()); // # Maybe allocate here instead of forcing system to copy?
	*this += newbuyer;
	return newbuyer;
}
Seller* System::CreateAndSendSeller()
{
	char			username[NAME_LEN];
	int				password;

	if (!ReadNewUserDetails(username, password))
		return nullptr;

	Seller* newseller = new Seller(username, password, createAddress()); // # Maybe allocate here instead of forcing system to copy?
	*this += newseller;
	return newseller;
}
BuyerSeller* System::CreateAndSendBuyerSeller()
{
	char			username[NAME_LEN];
	int				password;

	if (!ReadNewUserDetails(username, password))
		return nullptr;

	BuyerSeller* newbuyerseller = new BuyerSeller(username, password, createAddress()); // # Maybe allocate here instead of forcing system to copy?
	*this += newbuyerseller;
	return newbuyerseller;
}
void System::OstreamOperatorTest()
{
	bool fContinue = true;
	unsigned short int optionAnswer;
	while (fContinue)
	{
		cout << "What would you like to print through operator<< ?\n";
		cout << "\t1) Buyer\n";
		cout << "\t2) Seller\n";
		cout << "\t3) BuyerSeller\n";
		cout << "\t4) Back\n";
		cout << "\t5) How many buyers?\n";
		cout << "Note: the program will print the first user of the specified type it finds.";
		cout << "If one doesn't exist, you'll be asked to make one to add to the system.\n";
		cout << "Choose an option:   ";
		cin >> optionAnswer;

		while (optionAnswer < 1 || optionAnswer > 10)
		{
			cout << "Please enter a number within the range: ";
			cin >> optionAnswer;
		}
		cout << endl;

		switch (optionAnswer)
		{
		case 1:
			PrintBuyer();
			break;
		case 2:
			PrintSeller();
			break;
		case 3:
			PrintBuyerSeller();
			break;
		case 4:
			fContinue = false;
			break;
		case 5:
			cout << "Amount of buyers: " << Buyer::buyer_count << endl << endl;
			break;
		}


	}
}
void System::PrintBuyer()
{
	if (Buyer::buyer_count==0)
	{
		cout << "No buyers in the system. Create one:\n";
		User* temp=CreateAndSendBuyer();

		if (temp != nullptr)
		{
			cout << "\nDone creating the user. Now - drumroll - printing him!\n\n";
			cout << *temp << endl;
		}
		else
			cout << "No user was created. Nothing to print using operator<<.\n";
		return;
	}

	for(int i=0;i<m_users_log_size;i++)
	{	
		if (typeid(*(m_users[i])).name() == typeid(Buyer).name())
		{
			cout << *(m_users[i]);
			return;
		}
	}
}
void System::PrintSeller()
{
	if (Seller::seller_count == 0)
	{
		cout << "No sellers in the system. Create one:\n";
		User* temp = CreateAndSendSeller();

		if (temp != nullptr)
		{
			cout << "\nDone creating the user. Now - drumroll - printing him!\n\n";
			cout << *temp << endl;
		}
		else
			cout << "No user was created. Nothing to print using operator<<.\n";
		return;
	}

	for (int i = 0; i < m_users_log_size; i++)
	{
		if (typeid(*(m_users[i])).name() == typeid(Seller).name())
		{
			cout << *(m_users[i]);
			return;
		}
	}
}
void System::PrintBuyerSeller()
{
	if (BuyerSeller::buyer_seller_count == 0)
	{
		cout << "No buyers-sellers in the system. Create one:\n";
		User* temp = CreateAndSendBuyerSeller();

		if (temp != nullptr)
		{
			cout << "\nDone creating the user. Now - drumroll - printing him!\n\n";
			cout << *temp << endl;
		}
		else
			cout << "No user was created. Nothing to print using operator<<.\n";
		return;
	}

	for (int i = 0; i < m_users_log_size; i++)
	{
		if (typeid(*(m_users[i])).name() == typeid(BuyerSeller).name())
		{
			cout << *(m_users[i]);
			return;
		}
	}
}

// ----------------- OPERATORS ----------------- //
System& System::operator+=(Buyer* buyer)
{
	CheckAndIncreaseArrayIfNeeded();
	m_users[m_users_log_size++] = buyer;
	return *this;
}
System& System::operator+=(const Buyer& buyer)
{
	CheckAndIncreaseArrayIfNeeded();
	m_users[m_users_log_size++] = new Buyer(buyer);
	return *this;
}
System& System::operator+=(Seller* seller)
{
	CheckAndIncreaseArrayIfNeeded();
	m_users[m_users_log_size++] = seller;
	return *this;
}
System& System::operator+=(const Seller& seller)
{
	CheckAndIncreaseArrayIfNeeded();
	m_users[m_users_log_size++] = new Seller(seller);
	return *this;
}
System& System::operator+=(BuyerSeller* buyerseller)
{
	CheckAndIncreaseArrayIfNeeded();
	m_users[m_users_log_size++] = buyerseller;
	return *this;
}
System& System::operator+=(const BuyerSeller& buyerseller)
{
	CheckAndIncreaseArrayIfNeeded();
	m_users[m_users_log_size++] = new BuyerSeller(buyerseller);
	return *this;
}


// ----------------- PRIVATE METHODS ----------------- //
int System::printMainMenuOptions()
{
	unsigned short int optionAnswer;

	cout << "Main Menu\n";
	cout << "\t1) Create new account\n"; // Leads to a mini-menu.
	cout << "\t2) Sign in\n"; // Leads to a mini-menu.
	cout << "\t3) Show users of certain type\n"; // Leads to a mini-menu.
	cout << "\t4) Show products\n";
	cout << "\t5) Test Operators\n";
	cout << "\t6) Exit\n";
	cout << "Choose an option:   ";
	cin >> optionAnswer;
	while (optionAnswer < 1 || optionAnswer > 6)
	{
		cout << "Please enter a number within the range: ";
		cin >> optionAnswer;
	}
	cout << endl;
	return optionAnswer;
}
int System::readAccountType()
{
	int accountType;

	cout << "What sort of account would you like to create?\n";
	cout << "\t1) Buyer\n\t2) Seller\n\t3) Buyer and Seller\n\t4) Back\n";
	cin >> accountType;
	while (accountType < 1 || accountType > 4)
	{
		cout << "Please enter an option within the range.";
		cin >> accountType;
	}

	return accountType;
}
bool System::ReadNewUserDetails(char* name, int& password)
/*
This method receives two parameters and handles the reading of data into them.
If the user decides to stop trying, the method returns false to indicate that no data was read.
*/
{
	bool uContinue = true;
	while (uContinue)
	{
		cin.ignore();
		cout << "Choose username: ";
		cin >> name;
		if(! isAvailableUsername(name)) // Check if name exists.
		{
			cout << "Username is already taken. Would you like to try another one? ";
			if (!continueCheck())
				return false;
		}
		else
		{
			cin.ignore();
			cout << "Choose password: ";
			cin >> password;
			uContinue = false;
		}
	}
	return true;
}
bool System::ReadDataAheadOfFeedback(char * product_name, char * seller_name, const Buyer * buyer)
{
	while (true)
	{
		cin.ignore();
		cout << "Enter the following details for the feedback.\n";
		cout << "Product name: ";
		cin >> product_name;
		cout << "Seller name: ";
		cin >> seller_name;

		if (strcmp(seller_name, buyer->m_username) == 0) // Check that a BuyerSeller isn't trying to leave feedback for himself
		{
			cout << "Cannot leave feedback for yourself you hack.\n";
			cout << "Would you like to try again? ";
			if (continueCheck() == false)
				return false;
		}
		return true;
	}
	return true;

}
bool System::continueCheck()
{
	char ch;
	cout << "Choose 'y' to continue, 'n' to stop (y\\n)\n";
	cin >> ch;
	while (ch != 'y' && ch != 'n')
	{
		cout << "Please enter a valid response, smarty pants.\n";
		cin >> ch;
	}
	if (ch == 'n')
		return false;
	else
		return true;
}
Feedback* System::createFeedback(const Product* prod, const Buyer* feedbackGiver) // Read the buyer's feedback.
{
	char content[FEED_LEN];
	cin.ignore();
	cout << "Enter your feedback: ";
	cin.getline(content, FEED_LEN);
	cout << endl;
	Feedback* feedback = new Feedback(createDate(), feedbackGiver, content, prod);
	return feedback;
}
Address System::createAddress()
{
	char		street[NAME_LEN];
	int			houseNumber;
	char		city[NAME_LEN];
	char		country[NAME_LEN];

	cin.ignore(); // Clean the buffer.

	cout << "Please enter the following details for a new address.\n";
	cout << "Street: ";
	cin.getline(street, NAME_LEN, '\n');
	//cleanBuffer();

	cout << "House number: ";
	cin >> houseNumber;
	cin.ignore();	//	Clear the enter

	cout << "City: ";
	cin.getline(city, NAME_LEN);
	//cleanBuffer();

	cout << "Country: ";
	cin.getline(country, NAME_LEN);
	//cleanBuffer();

	return Address(street, houseNumber, city, country); // Move Constructor
}
Date System::createDate()
{
	unsigned int day, month, year;
	cout << "Enter the following details for the date.\n";
	cout << "Day: ";
	cin >> day;
	cout << "Month: ";
	cin >> month;
	cout << "Year: ";
	cin >> year;

	return Date(day, month, year);
}
User* System::GetAccount(const char* type)
{
	char name[NAME_LEN];
	int password;

	User* user = nullptr;
	bool uContinue = true;
	while (uContinue)
	{
		// Read the data from the user (name and password)
		cout << "Enter username: ";
		cin >> name;
		cout << "Enter password: ";
		cin >> password;

		// Try to retrieve account based on name and password given
		user = AccessAccount(name, password, type); // Send to function that goes over the array with the parameters and searches for the user based on the type
		if (!user) // If didn't find the user
		{
			cout << "Username or password are incorrect. Would you like to try again? ";
			if (!continueCheck()) //	User doesn't want to continue. Unwritten Else - he wants to continue.
				return nullptr;
		}
		else
			uContinue = false;
	}
	return user;
}
void System::cleanBuffer()
{
	int c;
	do
	{
		c = getchar();
	} while (c != '\n' && c != EOF);
}
void System::readProductName(char* name) const
{
	cin.ignore();
	cout << "Enter name of product: ";
	cin >> name;
	cout << endl;
}
int System::wishlistMenuOptions()
{
	int choice;

	cout << "Choose an option:\n";
	cout << "\t1) Search by name\n";
	cout << "\t2) Search by serial\n";
	cout << "\t3) Show all products\n";
	cout << "\t4) Back\n";

	cin >> choice;
	while (choice < 1 || choice > 4)
	{
		cout << "Invalid choice. Please pick a number within the range.\n";
		cin >> choice;
	}
	cout << endl;
	return choice;
}
int System::chooseFromAvailableProducts(const Product** availProducts, int availProductsCount)
{
	int userChoice;

	cout << "The product is available at " << availProductsCount << " sellers.\n\n";
	for (int i = 0; i < availProductsCount; i++)
	{
		cout << "Option " << i + 1 << endl;
		availProducts[i]->showProduct();
		cout << endl;
	}
	cout << endl;

	cout << "Choose an option number from the list above to add to your wishlist:   ";
	cin >> userChoice;
	while (userChoice<1 || userChoice>availProductsCount)
	{
		cout << "Chosen option is not within range. Try again.\n";
		cin >> userChoice;
	}
	userChoice = userChoice - 1; // Minus 1 to fit the array's starting count from 0, whereas we displayed options starting from 1.
	return userChoice;
}
bool System::CheckAndIncreaseArrayIfNeeded() 
{
	if (m_users_log_size == m_users_phy_size) // Check if we even need to update the size
	{
		m_users_phy_size *= 2;

		User** temp = new User*[m_users_phy_size];
		if (!temp)		//	Failed to allocate.
			return false;
		for (int i = 0; i < m_users_log_size; i++)
			temp[i] = m_users[i];
		delete[]m_users;
		m_users = temp;
		return true;
	}
	return true;
}