/* From a Wishlist, a Buyer adds products to his Cart.
These are the final products he proceeds to checkout with.

The Cart class was created to be an integral part of the Buyer type user.
Each Buyer makes use of a Wishlist and a Cart.
Originally all these methods and variables were within Buyer, but because they became so numerous,
we figured it was better to split them into their own classes.
*/
#ifndef __CART_H
#define __CART_H

class Product;
class Buyer;

class Cart
{
private:
	const Product**				cart;				//	Items to be purchased - the cart elements point to products in the wishlist.
	int							logSize, phySize;	//	To manage the array.
	double						cost;				//	Total cost of all products.
	const Buyer*				cartOwner;

// Private Methods
	bool						increaseCartSize();	//	The method allocates, copies and deletes. It's very costly, so we want it done only within the class, and not be called from outside.

public:
// C'tors and D'tor
	Cart();
	Cart(const Cart&) = delete;	//	No copy constructor. Just as we don't copy Buyers, there's no reason to copy a Cart as of now.
	~Cart();

// Const methods
	inline const Product**		getProducts()		const	{ return cart; }
	inline int					getLogSize()		const	{ return logSize; }
	inline double				getCost()			const	{ return cost; }
	inline const Buyer*			getOwner()			const	{ return cartOwner; }
	void						showCart()			const;

// Non-const methods
	bool						addToCart(const Product* product);
	void						emptyCart();

	friend class Buyer;
};
#endif // !__CART_H
