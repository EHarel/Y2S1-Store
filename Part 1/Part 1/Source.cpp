#include "Source.h"
#include "Address.h"
#include "Buyer.h"
#include "Seller.h"
#include "Product.h"
#include "System.h"
#include "Receipt.h"
#include "Date.h"
#include "Feedback.h"

#include "PurchaseHistory.h"

#include <iostream>
using namespace std;

// -----------------------	STATIC FUNCTION DECLARATIONS ----------------------- //
static Buyer* buyerAccountEntry(System& system);
static Seller* sellerAccountEntry(System& system);
static Address createAddress();
static Feedback* createFeedback(const Product* prod, const Buyer* feedbackGiver);
static Date createDate();
static void cleanBuffer();
static bool continueCheck();


// -----------------------	FUNCTION IMPLEMENTATION ----------------------- //

// ========= GENERAL FUNCTIONS ========= //
void runMenu(System& system)
{
	bool fContinue = true;
	unsigned short int optionAnswer;
	while (fContinue)
	{
		cout << "Main Menu\n";
		cout << "\t1) Create new user\n";
		cout << "\t2) Sign in\n";
		cout << "\t3) Show all buyers\n";
		cout << "\t4) Show all sellers\n";
		cout << "\t5) Show product\n";
		cout << "\t6) Exit\n";
		cout << "Choose an option:   "; 
		cin >> optionAnswer;
		while (optionAnswer < 1 || optionAnswer > 6)
		{
			cout << "Please enter a number within the range (1-6): ";
			cin >> optionAnswer;
		}
		cout << endl;
		switch (optionAnswer)
		{
		case 1:
			addUser(system);
			break;
		case 2:
			signIn(system);
			break;
		case 3:		
			showAllBuyers(system);
			break;
		case 4:		
			showAllSellers(system);
			break;
		case 5:	
			showSpecificProduct(system);
			break;
		case 6:	// Exit.
			fContinue = false;
			break;
		}
	}//while
	cout << endl;
}//addOrRemoveSurvivors
void addUser(System& system) // Create a new user.
{
	cout << "What sort of account would you like to create?\n";
	cout << "\t1) Buyer\n\t2) Seller\n";
	int userType;
	cin >> userType;
	if (userType != BUYER_OPTION && userType != SELLER_OPTION)
		return;
	char name[LEN];
	bool uContinue = true;
	while (uContinue)
	{
		cin.ignore();
		cout << "Choose username: ";
		cin.getline(name, LEN);
		bool availableUsername = system.isAvailableUsername(name); // Check if name exists.
		if (!availableUsername)
		{
			cout << "Username is already taken. Would you like to try another one? ";
			if (!continueCheck())
				return;
		}
		else
			uContinue = false;
	}

// Username isn't taken, collect rest of data.
	int password;
	cout << "Please enter a password (numbers only): ";
	cin >> password;

	if (userType == BUYER_OPTION) // Create buyer.
	{
		Buyer* buyer = new Buyer(name, password, createAddress());	//	IMPROVE: move/copy/whatever with address
		if (buyer == nullptr)
			cout << "Failed to create new buyer.\n";
		system.addBuyer(buyer);
	}
	else	//	Create seller.
	{
		Seller* seller = new Seller(name, password, createAddress());	//	IMPROVE: move/copy/whatever with address
		if (seller == nullptr)
			cout << "Failed to create new seller.\n";
		system.addSeller(seller);
	}
	cout << endl;
}
void signIn(System& system)
{
	cout << "Which account type would you like to sing in as?\n";
	cout << "\t1) Buyer\n\t2) Seller\n";
	int userType;
	cin >> userType;

	if (userType == BUYER_OPTION)
	{
		Buyer* buyer = buyerAccountEntry(system);

		if (!buyer)
			return;
		runBuyerMenu(system, buyer);
	}
	else if (userType == SELLER_OPTION)
	{
		Seller* seller = sellerAccountEntry(system);
		if (!seller)
			return;
		runSellerMenu(system, seller);
	}
}
void showAllBuyers(System& system)
{
	int size = system.getBuyerLogSize();
	if (size == 0)
	{
		cout << "No buyers in the system yet. Maybe we should first attract sellers?\n\n";
		return;
	}
	const Buyer** buyers = system.getAllBuyers();
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "Buyer " << i + 1;
		cout << endl;
		buyers[i]->showBuyer();
		cout << endl;
	}
	cout << endl;
}
void showAllSellers(System& system)
{
	int size = system.getSellerLogSize();
	if (size == 0)
	{
		cout << "No sellers in system yet. We need better marketing, damn it.\n\n";
		return;
	}
	const Seller** sellers = system.getAllSellers();
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "Seller " << i + 1;
		cout << endl;
		sellers[i]->showSeller();
		cout << endl;
	}
	cout << endl;
}
void showSpecificProduct(System& system)	
{
	char prodName[LEN];
	cout << "Enter name of product to show: ";
	cin >> prodName;
	cout << endl;
	const Seller** sellers = system.getAllSellers();
	int numOfSellers = system.getSellerLogSize();	//	Receive size for efficiency (avoid calling the getSize function all the time in the loop)
	bool found = false;
	for (int i = 0; i < numOfSellers; i++)
	{
		const Product* prod = sellers[i]->getProduct(prodName);
		if (prod)
		{
			prod->showProduct();
			cout << endl;
			if (found == false)
				found = true;
		}

	}
	if (found == false)	//	Didn't find product at all.
		cout << "Item isn't sold by anyone. No one wants it.\n";
	cout << endl;
}


// ========= BUYER FUNCTIONS ========= //
void runBuyerMenu(System& system, Buyer*& buyer)
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
			addFeedbackToSeller(system, buyer);
			break;
		case 2:		//	add product to cart of buyer
			addToWishlist(system, buyer);
			break;
		case 3:		//	perform order for buyer
			addToCart(system, buyer);
			break;
		case 4:		//	order payment for buyer
			checkout(system, buyer);
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
void addFeedbackToSeller(System& system, Buyer*& buyer)
{
	char prodName[LEN];
	char sellerName[LEN];
	cout << "Enter the following details for the feedback.\n";
	cout << "Product name: ";
	cin >> prodName;
	cout << "Seller name: ";
	cin >> sellerName;

	PurchaseHistory& history = buyer->getPurchaseHistory();
	
// PROBLEM: ugly code, change later
	int historySize = history.getLogSize(); // Num of receipts.
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
					const Seller* seller=receiptProducts[j]->getSeller();
					if (!system.addFeedbackToSeller(sellerName, buyerFeedback))
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
		cout << "Couldn't find the product or seller.\n\n";
}

void addToWishlist(System& system, Buyer*& buyer)
/*
In this function the user choose products to add to his wishlist.
He chooses by searching by product name.
This function runs a menu loop where he can choose to search for items, choose to show all items, or choose to exit.
*/
{
	if (!buyer)
		return;

	const Seller** allSellers = system.getAllSellers();
	if (allSellers[0] == nullptr)
	{
		cout << "No sellers in system. It is a time of great depression.\n\n";
		return;
	}

	int numOfSellers = system.getSellerLogSize();	//	Number of sellers in system.
	const Product** availProducts = new const Product*[numOfSellers];	//	 Prepare array for the products. Since the same product name could exist at different sellers, we could have more than one option.
	if (!availProducts)
		exit(1);
	cin.ignore();
	int choice;

	do
	{
		cout << "Choose an option:\n";
		cout << "\t1) Search by name\n";
		cout << "\t2) Show all products\n";
		cout << "\t3) Back\n";
		cin >> choice;
		cout << endl;
		if (choice == 1)
		{
			char prodName[LEN];
			cout << "Enter product to search: ";
			cin >> prodName;
			cout << endl;

			int availProductsCount = 0;	//	A counter for how many products of the chosen name we've found.
			for (int i = 0; i < numOfSellers; i++) //	Go over all sellers and search for existence of product at their store.
			{
				const Product* product = allSellers[i]->getProduct(prodName);	//	In array of sellers, search seller i for the product.
				// cout << "Checkeckeckeckeckeckkeckec\n";
				if (product != nullptr)	//	Seller returned something not-nullptr, meaning seller does have the item.
					availProducts[availProductsCount++] = product;	//	Add this product to the array of available products of this name.
			}//for

			cout << "The product " << prodName << " is available at " << availProductsCount << " sellers.\n\n";
			for (int i = 0; i < availProductsCount; i++)
			{
				cout << "Option " << i + 1 << endl;
				availProducts[i]->showProduct();
				cout << endl;
			}
			cout << endl;

			if (availProductsCount > 0)	//	If there are some products to choose from.
			{
				int userChoice;
				cout << "Choose an option:   ";
				cin >> userChoice;
				while (userChoice<1 || userChoice>availProductsCount)
				{
					cout << "Chosen option is not within range. Would you like to try again? ";
					if (!continueCheck())
						return;
					cin >> userChoice;
				}
				userChoice = userChoice - 1; // Minus 1 to fit the array's starting count from 0, whereas we displayed options starting from 1.

				const Product* chosenProduct = availProducts[userChoice];

				// Search for product in wishlist to see if it's already added
				if(buyer->getWishlist().isWishlistedProduct(chosenProduct->getSerial())==true)
					cout << "Product is already in wishlist.\n\n";
				else
					buyer->getWishlist().addToWishlist(chosenProduct);
			}
		}
		else if (choice == 2)
			system.showAllProducts();	//	This makes it easier for the Buyer to choose the product names to search for, if he's unsure.
	} while (choice == 1 || choice == 2);	//	For any other input we stop the loop.

	delete[]availProducts;
	return;
}//addToWishlist
void addToCart(System& system, Buyer*& buyer)
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
void checkout(System& system, Buyer*& buyer)
{
	//Buyer* buyer = buyerAccountEntry(system);
	//cout << endl;
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
void runSellerMenu(System& system, Seller*& seller)
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
			addItemToSeller(system, seller);
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
void addItemToSeller(System& system, Seller*& seller)
{
	//Seller* seller = sellerAccountEntry(system);
	//cout << endl;
	if (!seller)
		return;

	bool uContinue = true;
	char prodName[LEN];
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
	Product* newProd = new Product(prodName, price,  category, seller, index, check);
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


// ========= STATIC FUNCTIONS ========= //
static Buyer* buyerAccountEntry(System& system)
{
	char name[LEN];
	int password;
	Buyer* buyer = nullptr;
	bool uContinue = true;
	while (uContinue)
	{
		cout << "Enter username of buyer: ";
		cin >> name;
		cout << "Enter password: ";
		cin >> password;

		buyer = system.accessBuyerAccount(name, password);
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
static Seller* sellerAccountEntry(System& system)
{
	char name[LEN];
	int password;
	Seller* seller = nullptr;
	bool uContinue = true;
	while (uContinue)
	{
		cout << "Enter username of seller: ";
		cin >> name;
		cout << "Enter password: ";
		cin >> password;

		seller = system.accessSellerAccount(name, password);
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
static Feedback* createFeedback(const Product* prod, const Buyer* feedbackGiver) // Read the buyer's feedback.
{
	char content[FEED_LEN];
	cin.ignore();
	cout << "Enter your feedback: ";
	cin.getline(content, FEED_LEN);
	cout << endl;
	Feedback* feedback = new Feedback(createDate(), feedbackGiver, content, prod);
	return feedback;
}
static Address createAddress()
{
	char		street[LEN];
	int			houseNumber;
	char		city[LEN];
	char		country[LEN];

	cin.ignore(); // Clean the buffer.

	cout << "Please enter the following details for a new address.\n";
	cout << "Street: ";
	cin.getline(street, LEN);
	//cleanBuffer();
	//cin.ignore();

	cout << "House number: ";
	cin >> houseNumber;
	cin.ignore();

	cout << "City: ";
	cin.getline(city, LEN);
	//cleanBuffer();

	cout << "Country: ";
	cin.getline(country, LEN);
	//cleanBuffer();

	return Address(street, houseNumber, city, country);
}
static Date createDate()
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

static bool continueCheck()
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

static void cleanBuffer()
{
	int c;
	do 
	{
		c = getchar();
	} while (c != '\n' && c != EOF);
}


