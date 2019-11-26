#include "Source.h"
#include "Address.h"
#include "Buyer.h"
#include "Seller.h"
#include "Product.h"
#include "System.h"
#include "ProductSellerList.h"
#include "ReceiptBuyer.h"
#include "ReceiptSeller.h"

// -----------------------	STATIC FUNCTION DECLARATIONS ----------------------- //
static void printMenu();
static Buyer* buyerAccountEntry(System& system);
static Seller* sellerAccountEntry(System& system);
static Address* createAddress();



// -----------------------	FUNCTION IMPLEMENTATION ----------------------- //
void runMenu(System& system)
//This function runs the menu of the program.
//It continues until the user decides to stop.
{
	bool fContinue = true;
	unsigned short int optionAnswer;
	while (fContinue)
	{
		cout << "Choose an option:\n"; 
		printMenu();
		cin >> optionAnswer;
		while (optionAnswer < 1 || optionAnswer > MAX_OPTION)
		{
			cout << "Please enter a number within the range (1-" << MAX_OPTION << "): ";
			cin >> optionAnswer;
		}
		switch (optionAnswer)
		{
		case 1:	
			addBuyer(system);
			break;
		case 2:	
			addSeller(system);
			break;
		case 3:		//	add item to Seller
			addItemToSeller(system);
			break;
		case 4:		//	add feedback to Seller; we check that feedback giver actually purchased from Seller
			addFeedbackToSeller();
			break;
		case 5:		//	add product to cart of buyer
			addToWishlist(system);
			break;
		case 6:		//	perform order for buyer
			addToCart(system);
			break;
		case 7:		//	order payment for buyer
			checkout(system);
			break;
		case 8:		//	show all buyer details
			showAllBuyers(system);
			break;
		case 9:		//	show all Seller details
			showAllSellers(system);
			break;
		case 10:	//	show details of all products of certain name
			showSpecificProduct(system);
			break;
		case 11:	//	exit
			fContinue = false;
			break;
		}
	}//while
	cout << endl;
}//addOrRemoveSurvivors

static void printMenu()
// This function prints all the options in the menu.
{
	cout << "\t1) Add buyer\n";
	cout << "\t2) Add seller\n";
	cout << "\t3) Add item to seller\n";
	cout << "\t4) Add feedback to seller\n";
	cout << "\t5) Add product to wishlist\n";
	cout << "\t6) Choose items from wishlsit\n";
	cout << "\t7) Checkout\n";
	cout << "\t8) Show details of all buyers\n";
	cout << "\t9) Show details of all sellers\n";
	cout << "\t10) Show details of all products of certain name\n";
	cout << "\t11) Exit\n";
}


void addBuyer(System& system)
{
	char name[LEN];
	cout << "Choose username: ";
	cin >> name;
	bool availableUsername = system.isAvailableUsername(name);
	if (!availableUsername)
	{
		cout << "Username is already taken.\n\n";
		return;
	}

	// At this point, we've established the entered name is new. Now we collect the rest of the data to create a user.
	int password;
	cout << "Please enter a password (numbers only): ";
	cin >> password;
	Address* address = createAddress();
	Buyer* buyer = new Buyer(name, password, address);
	if (buyer == nullptr)
		cout << "Failed to create new buyer.\n";
	system.addBuyer(buyer);
	cout << endl;
}

void addSeller(System& system)
{
	char name[LEN];
	cout << "Choose username: ";
	cin >> name;
	bool availableUsername = system.isAvailableUsername(name);
	if (!availableUsername)
	{
		cout << "Username is already taken.\n\n";
		return;
	}

	// At this point, we've established the entered name is new. Now we collect the rest of the data to create a user.
	int password;
	cout << "Please enter a password (numbers only): ";
	cin >> password;
	Address* address = createAddress();
	Seller* seller = new Seller(name, password, address);
	if (!seller)
		cout << "Failed to create new seller.\n";
	system.addSeller(seller);
	cout << endl;
}

bool readNewUsername(char* name, System& system)
/*
This function asks for a new username, and checks if it exists in the system.
If it does, it asks the user if he wishes to try a different name.
If he rejects, the loop ends.
*/
{
	bool uContinue=true;		//	user continue
	while (uContinue)
	{
		cout << "Please enter a new username, up to " << LEN - 1 << " letters: ";
		cin >> name;
		if(system.isAvailableUsername(name)==false)		//	Found an existing user of that username.
		{
			cout << "That username already. Would you like to try a new username? (y\\n)\n ";
			char ch;
			cin >> ch;
			getchar();
			while (ch != 'n' || ch != 'y')
			{
				cout << "Please enter a valid option (y\\n)\n";
				cin >> ch;
				getchar();
			}
			if (ch == 'n')			//	User wishes to stop and not try a new username.
				return false;
		}
		else
			uContinue = false;
	}//while
	return true;
}


void addItemToSeller(System& system)
{
	Seller* seller = sellerAccountEntry(system);
	if (!seller)
	{
		cout << "Username or password are incorrect.\n\n";
		return;
	}

	char prodName[LEN];
	cout << "Enter product name: ";
	cin >> prodName;
	getchar();
	int temp=UNKNOWN_INDEX;			//	Necessary just for the following function call:
	if (seller->getProduct(prodName, temp) != nullptr)		//	Product exists
	{
		cout << "The product already exists.\n\n";
		return;
	}
	else												//	Product doesn't exist
	{
		double price;
		cout << "Set price: ";
		cin >> price;
		int cat;
		Product::eCategory category;
		cout << "Choose a category:\n\t1) Children\n\t2) Electricity\n\t3) Office\n\t4) Clothing\n";
		cin >> cat;
		category = (Product::eCategory)(cat - 1);
		int serial;
		serial = 1 + system.getLatestSerial();
		bool check;
		int index = seller->getCatalogLogSize();
		Product* newProd = new Product(prodName, price, serial, category, seller, index, check);
		if (!check)
		{
			cout << "Error with adding the product to the system.\n\n";
			delete newProd;
		}
		else		//	Product was created - passed all Product checks.
		{
			if (!seller->addProductToMerch(newProd))	//	 Failed to add to seller's array.
			{
				cout << "Failed to add the product to " << seller->getUsername() << "'s store.\n\n";
				delete newProd;
			}
			else	//	Succeeded in adding to seller's array.
				system.advanceSerial();	//	 Advance only once we're sure the product is okay.
		}
	}	
}

void addFeedbackToSeller()
{
	/*
	1. Account access for buyer
	2. Choose seller name
	3. Check within seller's past buyers that this buyer exists in the array
		We don't go over all the array - only until we've found the name once
		If so - create feedback
		Add feedback to array of feedbacks
	*/
}

void addToWishlist(System& system)
{
	Buyer* buyer = buyerAccountEntry(system);
	if (!buyer)
	{
		cout << "Username or password are incorrect.\n\n";
		return;
	}
	cout << endl;
	
	const Seller** allSellers = system.getAllSellers();
	if (!allSellers)
	{
		cout << "No sellers in system. It is a time of great depression.\n\n";
		return;
	}

	char prodName[LEN];
	cout << "Enter product to search: ";
	cin >> prodName;
	cout << endl;

	ProductSellerList* prodList = nullptr;
	bool createdList = false;	//	A bool check, so that we can avoid allocating the class if the product doesn't even exist.

	//	Go over all sellers and search for existence of product at their store.
	int size = system.getSellerLogSize();
	for (int i = 0; i < size; i++)		
	{
		int indexAtSeller = UNKNOWN_INDEX;
		const Product* product = allSellers[i]->getProduct(prodName, indexAtSeller);	//	Search seller i for the product.
		if (product!=nullptr)	//	Seller didn't return nullptr, meaning seller does have the item.
		{
			if (!createdList)	//	If haven't created the list yet (meaning, haven't found an item yet), create now.
			{
				prodList = new ProductSellerList(system.getSellerLogSize(), prodName);	//	We send the logical size of the sellers array - so that we can already work within our auxiliary class with an allocated array to the maximum size, just in case.
				if (!prodList)
				{
					cout << "Error during creation of product list.\n";
					return;
				}
				createdList = true;
			}
			prodList->addAvailableSeller(allSellers[i], indexAtSeller);
		}
	}

	if (!prodList)
	{
		cout << "Product " << prodName << " isn't sold by anyone. It's disgusting.\n";
		return;
	}

	cout << "The product " << prodName << " is available at the following Sellers. Choose an option.\n";
	if (prodList->showAvailableSellers() == false)
	{
		cout << "The product isn't sold by anyone. Tough luck.\n";
		return;
	}
	int userChoice;
	cin >> userChoice;
	if (userChoice <1 || userChoice > prodList->getLogSize())	//	PROBLEM: how can we be sure how the class presents the options?
	{
		cout << "Chosen option is not within range.\n";
		
		//	 IDEA: Create loop here that allows user to keep trying a proper answer.
		
		return;
	}

	userChoice = userChoice - 1;
	const Product* chosenProduct = prodList->getProduct(userChoice);
	buyer->addToWishlist(chosenProduct);
}

void addToCart(System& system)			// purchase?
{
	Buyer* buyer = buyerAccountEntry(system);
	if (!buyer)
	{
		cout << "Wrong username or password.\n\n";
		return;
	}
	cout << endl;

	if (!buyer->showAllWishlistProducts()) //	Display all the products considered for purchasing
	{
		cout << "Wishlist is empty. Nothing to show.\n\n";
		return;
	}
	cout << endl;

	int prodNum;
	cout << "Choose product numbers to add to checkout. Enter " << STOP << " to stop.\n";	//	IMPROVE: find a better way to stop than an ugly negative const number
	cin >> prodNum;
	getchar();
	while (prodNum != STOP)
	{
		prodNum = prodNum - 1; //	Minus 1, because the options displayed to the user start from 1, not 0 like the array 
		if (prodNum<0 || prodNum>buyer->getWishLogSize())
		{
			cout << "Enter a valid number: ";
			cin >> prodNum;
			getchar();
		}
		else
		{
			const Product** productAddress = buyer->getWishlistProductAddress(prodNum);
			if (!productAddress)
				cout << "Failed to fetch product from wishlist.\n";
			else
			{
				if (buyer->addToCart(productAddress) == false)
					cout << "Failed to add to checkout queue.\n";
			}
			cout << "Choose another product: ";
			cin >> prodNum;
			cout << endl;
		}
	}
}

void checkout(System& system)
{
	Buyer* buyer = buyerAccountEntry(system);
	if (!buyer)
	{
		cout << "Failed to access account. Goodbye, fool.\n\n";
		return;
	}
	
	double price = buyer->getCurrentCheckoutCost();
	cout << "Cost of all products is: " << price << endl;

	char ch;
	cout << "Do you wish to continue? (y\\n)\n";
	cin >> ch;
	while (ch != 'y' && ch != 'n')
	{
		cout << "Please enter a valid response, smarty pants.\n";
		cin >> ch;
	}
	if (ch == 'n')
		return;

	int receiptSize = buyer->getCheckoutLogSize();
	ReceiptBuyer* receiptBuyer = new ReceiptBuyer(buyer->getCart(), receiptSize, price, buyer);
	if (!receiptBuyer)
	{
		cout << "Problem checking out Process cancelled, no payment made.\n\n";
		return;
	}
	if (!buyer->proceedToCheckout(receiptBuyer))
	{
		cout << "Failed to proceed to checkout. Process cancelled, no payment made.\n\n";
		delete receiptBuyer;
		return;
	}

// Now we add a receipt to the seller.
	for (int i = 0; i < receiptSize; i++)
	{
		const Product* product = receiptBuyer->getProductByIndex(i);
		ReceiptSeller* receiptSeller = new ReceiptSeller(product, buyer);
		const Seller* seller = product->getSeller();
		seller->addReceipt(receiptSeller);
	}
}

void showAllBuyers(System& system)
{
	const Buyer** buyers = system.getAllBuyers();
	int size = system.getBuyerLogSize();
	for (int i = 0; i < size; i++)
	{
		buyers[i]->showBuyer();
		cout << endl;
	}
}

void showAllSellers(System& system)
{
	const Seller** sellers = system.getAllSellers();
	int size = system.getSellerLogSize();
	for (int i = 0; i < size; i++)
	{
		sellers[i]->showSeller();
		cout << endl;
	}
}

void showSpecificProduct(System& system)	//	IMPROVEMENT: mis function is very inefficient, and will greatly benefit from ProductWeb
{
	char prodName[LEN];
	cout << "Enter name of product to show: ";
	cin >> prodName;

	const Seller** sellers = system.getAllSellers();
	int size = system.getSellerLogSize();	//	Receive size for efficiency (avoid calling the getSize function all the time in the loop)
	for (int i = 0; i < size; i++)
	{
		int index = UNKNOWN_INDEX;
		const Product* prod = sellers[i]->getProduct(prodName, index);
		if (prod)
			prod->showProduct();
	}
}






// ------------------------------- STATIC FUNCTIONS------------------------------- //

static Buyer* buyerAccountEntry(System& system)
{
	char name[LEN];
	int password;
	cout << "Enter username of buyer: ";
	cin >> name;
	cout << "Enter password: ";
	cin >> password;

	Buyer* buyer = system.accessBuyerAccount(name, password);
	return buyer;
}
static Seller* sellerAccountEntry(System& system)
{
	char name[LEN];
	int password;
	cout << "Enter username of seller: ";
	cin >> name;
	cout << "Enter password: ";
	cin >> password;

	Seller* seller = system.accessSellerAccount(name, password);
	return seller;
}

static Address* createAddress()
{
	char		street[LEN];
	int			houseNumber;
	char		city[LEN];
	char		country[LEN];

	getchar();
	cout << "Please enter the following details for a new address.\n";
	cout << "Street: ";
	cin >> street;
	getchar();
	cout << "House number: ";
	cin >> houseNumber;
	getchar();
	cout << "City: ";
	cin >> city;
	getchar();
	cout << "Country: ";
	cin >> country;
	getchar();

	Address* address = new Address(street, houseNumber, city, country);
	if(!address)
		cout << "Failed to allocate space for address.\n";
	return address;
}


