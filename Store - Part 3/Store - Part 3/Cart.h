/* From a Wishlist, a Buyer adds products to his Cart.
These are the final products he proceeds to checkout with.

The Cart class was created to be an integral part of the Buyer type user.
Each Buyer makes use of a Wishlist and a Cart.
Originally all these methods and variables were within Buyer, but because they became so numerous,
we figured it was better to split them into their own classes.
*/
#ifndef __CART_H
#define __CART_H

#include <vector>
#include <iostream>
using namespace std;

class Product;
class Buyer;

class Cart
{
private:
	vector<const Product*>					m_cart;				//	Items to be purchased - the cart elements point to products in the wishlist.
	double									m_cost;				//	Total cost of all products.
	const Buyer*							m_cart_owner;

public: // C'tors and D'tor
	Cart(const Buyer* owner) : m_cart_owner(owner), m_cost(0) {}
	Cart(const Cart& other);
	Cart(Cart&& other);

// Const methods
	inline const vector<const Product*>&	getProducts()		const	{ return m_cart; }
	inline int								getLogSize()		const	{ return m_cart.size(); }
	inline double							getCost()			const	{ return m_cost; }
	inline const Buyer*						getOwner()			const	{ return m_cart_owner; }
	void									showCart()			const;

// Non-const methods
	bool									addToCart(const Product& product);
	void									emptyCart();

// Operators
private:
	const Cart&								operator=(const Cart& other);
public:
	const Product*							operator[](int i) const;
	friend ostream&							operator<<(ostream& os, const Cart& cart);

	friend class Buyer;
};
#endif // !__CART_H
