#include "System.h"
#include "Seller.h"
#include <iostream>
#include <string.h>
using namespace std;

// ----------------- C'TORS AND D'TOR ----------------- //
System::System(const char* name)
{
	strcpy(m_name, name);
	
	m_buyPhySize = 10;
	m_buyLogSize = 0;
	m_buyers = new Buyer*[m_buyPhySize];
	if (!m_buyers)
		exit(1);
	m_buyers[0] = nullptr;

	m_sellPhySize = 5;		//	Expect less Sellers than buyers.
	m_sellLogSize = 0;
	m_sellers = new Seller*[m_sellPhySize];
	if (!m_sellers)
		exit(1);
	m_sellers[0] = nullptr;	
}
System::~System()
{
	int i = 0;
	for (i = 0; i < m_buyLogSize; i++)
		delete m_buyers[i];
	delete[]m_buyers;

	for (i = 0; i < m_sellLogSize; i++)
		delete m_sellers[i];
	delete[]m_sellers;
}


// ----------------- CONST METHODS----------------- //
const Buyer* System::getBuyer(int index) const
/*
This function receives an index for the array and returns the element in that array.
*/
{
	if (index < 0 || index > m_buyLogSize)
		return nullptr;
	return(m_buyers[index]);
}
const Seller* System::getSeller(int index) const
{
	if (index < 0 || index > m_sellLogSize)
		return nullptr;
	return(m_sellers[index]);
}
bool System::isAvailableUsername(const char* name)		const
/*
This function receives a username, and checks if it already exists in the system.
It goes over one array, then the other, stopping if it has found it.
*/
{
	int i = 0;
// Go over buyers array.
	for (i = 0; i < m_buyLogSize; i++)
		if (strcmp(m_buyers[i]->getUsername(), name) == 0)		//	Found similar username.
			return false;

// Go over sellers array.
	for (i = 0; i < m_sellLogSize; i++)
		if (strcmp(m_sellers[i]->getUsername(), name) == 0)
			return false;
	
	return true;
}
void System::showAllProducts()	const //	A bit of a "brutish" method that just shows all the products
{
	int productCount = 0;

	for (int i = 0; i < m_sellLogSize; i++)
	{
		if (m_sellers[i]->m_catLogSize > 0)	//	If seller i has items.
		{
			cout << "Products of " << m_sellers[i]->m_username << ": ";
			cout << endl;
			m_sellers[i]->showAllMerchandise();
			cout << endl;
			productCount += m_sellers[i]->m_catLogSize;
		}
	}
	cout << "Total number of available products: " << productCount << endl << endl;
}


// ----------------- NON-CONST METHODS----------------- //
Buyer* System::accessBuyerAccount(char* name, int password)
/*
This function provides access to a Buyer Account for the user.
This allows the user to take actions with his account, such as adding to wishlist, checking out, etc.
*/
{
	for (int i = 0; i < m_buyLogSize; i++)
	{
		if (strcmp(m_buyers[i]->getUsername(), name) == 0)	//	Found the username
		{
			bool validAccess = m_buyers[i]->passwordCheck(password);
			if (validAccess)
				return m_buyers[i];
			else
				return nullptr;
		}
	}
	return nullptr;
}
Seller* System::accessSellerAccount(char* name, int password)
/*
This function provides a Seller Account for the user.
This allows the user to take actions regarding his account.
*/
{
	for (int i = 0; i < m_sellLogSize; i++)
	{
		if (strcmp(m_sellers[i]->getUsername(), name) == 0)	//	Found the username
		{
			bool validAccess = m_sellers[i]->passwordCheck(password);
			if (validAccess)
				return m_sellers[i];
			else
				return nullptr;
		}
	}
	return nullptr;
}
bool System::addBuyer(Buyer* newBuyer)
{
	if (newBuyer == nullptr)
		return false;
	if (m_buyLogSize == m_buyPhySize)	//	No room in the array; need to increase its physical size.
		if (increaseBuyerArray() == false)
		{
			cout << "Array is full, and failed to increase size.\n";
			return false;
		}
	m_buyers[m_buyLogSize++] = newBuyer;
	return true;
}
bool System::addSeller(Seller* newSeller)
{
	if (newSeller == nullptr)
		return false;
	if (m_sellLogSize == m_sellPhySize)	//	No room in the array; need to increase its physical size.
		if (increaseSellerArray() == false)
		{
			cout << "Array is full, and failed to increase size.\n";
			return false;
		}
	m_sellers[m_sellLogSize++] = newSeller;
	return true;
}
bool System::addFeedbackToSeller(const char* sellerUsername, const Feedback* buyerFeedback)
{
	for (int i = 0; i < m_sellLogSize; i++)
	{
		if (strcmp(m_sellers[i]->m_username, sellerUsername) == 0) // Found the seller.
			if (!m_sellers[i]->addFeedback(buyerFeedback))
				return false;
			else
				return true;
	}//for
	return false;
}


// ----------------- MENU ----------------- //
// ========= MAIN MENU========= //
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
			showAllBuyers();
			break;
		case 4:
			showAllSellers();
			break;
		case 5:
			showProductsMenu();
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
	if (accountType != BUYER_OPTION && accountType != SELLER_OPTION) // If neither Buyer nor Seller, leave this menu.
		return;
	char name[NAME_LEN];
	if (!chooseNewUsername(name))	//	User chooses name for his account. Returns false if name is taken and user gives up.
		return;
	int password; // Username isn't taken, collect final data which is password.
	cout << "Please enter a password (numbers only): ";
	cin >> password;

	addAccountToSystem(name, password, accountType);
	cout << endl;
}
bool System::addAccountToSystem(char* name, int password, int accountType)
{
	if (accountType == BUYER_OPTION) // Create buyer.
	{
		Buyer* buyer = new Buyer(name, password, createAddress());
		if (buyer == nullptr)
		{
			cout << "Failed to create new buyer.\n";
			return false;
		}
		addBuyer(buyer);
	}
	else	//	Create seller.
	{
		Seller* seller = new Seller(name, password, createAddress());
		if (seller == nullptr)
		{
			cout << "Failed to create new seller.\n";
			return false;
		}
		addSeller(seller);
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
	cout << "Which account type would you like to sing in as?\n";
	cout << "\t1) Buyer\n\t2) Seller\n";
	int userType;
	cin >> userType;

	if (userType == BUYER_OPTION)
	{
		Buyer* buyer = signInBuyer();
		if (!buyer)
			return;
		cout << "Buyer log in successful.\n\n";
		runBuyerMenu(buyer);
	}
	else if (userType == SELLER_OPTION)
	{
		Seller* seller = signInSeller();
		cout << "Seller log in successful.\n\n";
		if (!seller)
			return;
		runSellerMenu(seller);
	}
	else
		return;
}
void System::showAllBuyers() const
{
	if (m_buyLogSize == 0)
	{
		cout << "No buyers in the system yet. This store is crap :D\n\n";
		return;
	}
	cout << endl;
	for (int i = 0; i < m_buyLogSize; i++)
	{
		cout << "Buyer " << i + 1;
		cout << endl;
		m_buyers[i]->showBuyer();
		cout << endl;
	}
	cout << endl;
}
void System::showAllSellers() const
{
	if (m_sellLogSize == 0)
	{
		cout << "No sellers in system yet. How about a marketing team?\n\n";
		return;
	}
	cout << endl;
	for (int i = 0; i < m_sellLogSize; i++)
	{
		cout << "Seller " << i + 1;
		cout << endl;
		m_sellers[i]->showSeller();
		cout << endl;
	}
	cout << endl;
}
void System::showProductsMenu() const
/*
This function allows the user to show either a specific product, or all products.
*/
{
	int option;
	cout << "Show Products\n";
	cout << "\t1) Show specific product\n";
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
	for (int i = 0; i < m_sellLogSize; i++)	//	 Go over all sellers, and check their products.
	{
		const Product* prod = m_sellers[i]->getProduct(prodName); // Search within seller i for the product.
		if (prod) // Returned value isn't nullptr, meaning seller i has the product.
		{
			prod->showProduct();
			cout << endl;
			count++;
		}
	}
	if (count == 0)	//	Didn't find product at all.
		cout << "Item isn't sold by anyone. No one wants it.\n";
	else
		cout << count << " options in the store of " << prodName << endl; // State how many products overall (count)
	cout << endl;
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
	char prodName[NAME_LEN];
	char sellerName[NAME_LEN];
	cout << "Enter the following details for the feedback.\n";
	cout << "Product name: ";
	cin >> prodName;
	cout << "Seller name: ";
	cin >> sellerName;

	PurchaseHistory& history = buyer->getPurchaseHistory();

	int historySize = history.getLogSize(); // Num of receipts.
	if (historySize == 0)
	{
		cout << "You've made no purchases. Nothing to leave feedback for you crook. Leaving a false review for something is just being a dick.\n\n";
		return;
	}
	bool found = false;
	int i = 0, j = 0;
	Receipt**& receipts = history.getReceipts();

	while (!found && i < historySize)	 // Loop until we've found the product, or until we've run out of receipts.
	{
		int receiptSize = receipts[i]->getNumOfProducts();	//	Get the 'i' receipt out of all the buyer's receipt.
		j = 0;
		const Product** receiptProducts = receipts[i]->getProducts();	//	Get all products in the receipt.
		while (!found && j < receiptSize)	//	Go over all products in the receipt.
		{
			if (strcmp(receiptProducts[j]->getName(), prodName) != 0)	//	In receipt 'i', check product 'j' name
				j++;
			else	//	Found product name, now check that actually purchased from this seller
			{
				if (strcmp(sellerName, receiptProducts[j]->getSeller()->getUsername()) != 0)	//	Check seller of product 'j' in receipt 'i'
					j++;
				else	//	Found the correct product and the correct seller. Send the feedback to system.
				{
					if (receipts[i]->getFeedbacks()[i])
					{
						cout << "You've already given feedback for this product.\n";
						return;
					}
					Feedback* buyerFeedback = createFeedback(receiptProducts[j], buyer);
					const Seller* seller = receiptProducts[j]->getSeller();
					if (!addFeedbackToSeller(sellerName, buyerFeedback))
					{
						cout << "Failure adding the feedback.\n";
						delete buyerFeedback;
						return;
					}
					if (!receipts[i]->addFeedbackToProd(prodName, sellerName, buyerFeedback))
					{
						cout << "Failure adding the feedback.\n";
						// Delete?
						return;
					}

					found = true;
				}
			}
		}
		i++;
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

	if (m_sellLogSize == 0) // Number of sellers in system.
	{
		cout << "No sellers in system. It is a time of great depression.\n\n";
		return;
	}
	const Product** availProducts = nullptr;	//	Avoid allocating just yet - we allocate only if user searches by name, because in that case there could be several products.
	int choice;

	do
	{
		choice = wishlistMenuOptions();

		if (choice == 1) // Search by name
		{
			char prodName[NAME_LEN];
			readProductName(prodName);

			int availProductsCount = 0;	//	A counter for how many products of the chosen name we've found.
			for (int i = 0; i < m_sellLogSize; i++) //	Go over all sellers and search for existence of product at their store.
			{
				const Product* product = m_sellers[i]->getProduct(prodName);	//	In array of sellers, search seller i for the product.
				if (product != nullptr)	//	Seller returned something not-nullptr, meaning seller does have the item.
				{
					if (!availProducts) // If haven't allocated yet
					{
						availProducts = new const Product*[m_sellLogSize];
						if (!availProducts) // Allocation check
						{
							cout << "Failure retrieving to wishlist.\n";
							return;
						}
					}
					availProducts[availProductsCount++] = product;	//	Add this product to the array of available products of this name.
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
			while (!product && i < m_sellLogSize)	//	Go over all sellers until found the product by serial.
			{
				product = m_sellers[i]->getProduct(serial); // Within seller i out of all sellers, search for the product.
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


// ----------------- PRIVATE METHODS----------------- //
int System::printMainMenuOptions()
{
	unsigned short int optionAnswer;

	cout << "Main Menu\n";
	cout << "\t1) Create new account\n";
	cout << "\t2) Sign in\n";
	cout << "\t3) Show all buyers\n";
	cout << "\t4) Show all sellers\n";
	cout << "\t5) Show products\n";
	cout << "\t6) Exit\n";
	cout << "Choose an option:   ";
	cin >> optionAnswer;
	while (optionAnswer < 1 || optionAnswer > 6)
	{
		cout << "Please enter a number within the range (1-6): ";
		cin >> optionAnswer;
	}
	cout << endl;
	return optionAnswer;
}
int System::readAccountType()
{
	int accountType;

	cout << "What sort of account would you like to create?\n";
	cout << "\t1) Buyer\n\t2) Seller\n\t3) Back\n";
	cin >> accountType;
	while (accountType < 1 || accountType > 3)
	{
		cout << "Please enter an option within the range.";
		cin >> accountType;
	}

	return accountType;
}
bool System::chooseNewUsername(char* name)
{
	bool uContinue = true;
	while (uContinue)
	{
		cin.ignore();
		cout << "Choose username: ";
		cin.getline(name, NAME_LEN);
		bool availableUsername = isAvailableUsername(name); // Check if name exists.
		if (!availableUsername)
		{
			cout << "Username is already taken. Would you like to try another one? ";
			if (!continueCheck())
				return false;
		}
		else
			uContinue = false;
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
Buyer* System::signInBuyer()
{
	char name[NAME_LEN];
	int password;
	Buyer* buyer = nullptr;
	bool uContinue = true;
	while (uContinue)
	{
		cout << "Enter username of buyer: ";
		cin >> name;
		cout << "Enter password: ";
		cin >> password;

		buyer = accessBuyerAccount(name, password);
		if (!buyer)
		{
			cout << "Username or password are incorrect. Would you like to try again? ";
			if (!continueCheck()) //	User doesn't want to continue. Unwritten Else - he wants to continue.
				return nullptr;
		}
		else
			uContinue = false;
	}
	return buyer;
}
Seller* System::signInSeller()
{
	char name[NAME_LEN];
	int password;
	Seller* seller = nullptr;
	bool uContinue = true;
	while (uContinue)
	{
		cout << "Enter username of seller: ";
		cin >> name;
		cout << "Enter password: ";
		cin >> password;

		seller = accessSellerAccount(name, password);
		if (!seller)
		{
			cout << "Username or password are incorrect. Would you like to try again? ";
			if (!continueCheck()) //	User doesn't want to continue. Unwritten Else - he wants to continue.
				return nullptr;
		}
		else
			uContinue = false;
	}
	return seller;
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
bool System::increaseBuyerArray()
{
	m_buyPhySize *= 2;
	Buyer** temp = new Buyer*[m_buyPhySize];
	if (!temp)		//	Failed to allocate.
		return false;
	for (int i = 0; i < m_buyLogSize; i++)
		temp[i] = m_buyers[i];
	delete[]m_buyers;
	m_buyers = temp;
	return true;
}
bool System::increaseSellerArray()
{
	m_sellPhySize *= 2;
	Seller** temp = new Seller*[m_sellPhySize];
	if (!temp)		//	Failed to allocate.
		return false;
	for (int i = 0; i < m_sellLogSize; i++)
		temp[i] = m_sellers[i];
	delete[]m_sellers;
	m_sellers = temp;
	return true;
}