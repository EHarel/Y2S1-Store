/*  The Wishlist is where a Buyer keeps products he considers buying.

The Wishlist class was created to be an integral part of the Buyer type user.
Each Buyer makes use of a Wishlist and a Cart.
Originally all these methods and variables were within Buyer, but because they became so numerous,
we figured it was better to split them into their own classes.
*/
#ifndef __WISHLIST_H
#define __WISHLIST_H

class Product;
class Buyer;

class Wishlist
{
private:
	const Product**		products;	//	this is an array of products that the buyer considers purchasing. Dynamically allocated
	bool*				cartIndication;
	int					logSize, phySize;		//	Variables to manage the dynamic cart array.
	const Buyer*		wishlistOwner;

public:
// Constructors and destructor
	Wishlist();
	Wishlist(const Wishlist&) = delete;
	~Wishlist();

// Const methods
	const Buyer*		getOwner()						const;
	bool				showWishlist()					const;
	int					getLogSize()					const;
	const Product*		getProduct(int index)			const;
	bool				isWishlistedProduct(int serial)	const;
	bool				getCartIndication(int idex)		const;



// Non-const methods
	bool				increaseWishlistSize(); // We want to make this an internal helper function just for the wishlist
	bool				addToWishlist(const Product* product);

	void				changeProductCartStatus(int index); // NOTE 3: CAHAAAANNGGEEE
	void				cleanNullptrs();	//	This method cleans the array of nullptrs. Important for the checkout stage.

	friend class Buyer;
};
#endif // !__WISHLIST_H
