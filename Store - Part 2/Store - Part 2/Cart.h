/* From a Wishlist, a Buyer adds products to his Cart.
These are the final products he proceeds to checkout with.

The Cart class was created to be an integral part of the Buyer type user.
Each Buyer makes use of a Wishlist and a Cart.
Originally all these methods and variables were within Buyer, but because they became so numerous,
we figured it was better to split them into their own classes.
*/
#ifndef __CART_H
#define __CART_H

#include <iostream>
using namespace std;

class Product;
class Buyer;

class Cart
{
private:
	const Product**				m_cart;				//	Items to be purchased - the cart elements point to products in the wishlist.
	int							m_log_size, m_phy_size;	//	To manage the array.
	double						m_cost;				//	Total cost of all products.
	const Buyer*				m_cart_owner;

// Private Methods
	bool						increaseCartSize();	//	The method allocates, copies and deletes. It's very costly, so we want it done only within the class, and not be called from outside.

public:
// C'tors and D'tor
	Cart();
	Cart(const Cart&);
	Cart(Cart&&);
	~Cart();

// Const methods
	inline const Product**		getProducts()		const	{ return m_cart; }
	inline int					getLogSize()		const	{ return m_log_size; }
	inline double				getCost()			const	{ return m_cost; }
	inline const Buyer*			getOwner()			const	{ return m_cart_owner; }
	void						showCart()			const;

// Non-const methods
	bool						addToCart(const Product* product);
	void						emptyCart();


// Operators
	const Product*				operator[](int i) const;
	const Cart&					operator=(const Cart& other);
	friend ostream&				operator<<(ostream& os, const Cart& cart);


	friend class Buyer;
};
#endif // !__CART_H
