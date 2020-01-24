/*  The Wishlist is where a Buyer keeps products he considers buying.

The Wishlist class was created to be an integral part of the Buyer type user.
Each Buyer makes use of a Wishlist and a Cart.
Originally all these methods and variables were within Buyer, but because they became so numerous,
we figured it was better to split them into their own classes.
*/
#ifndef __WISHLIST_H
#define __WISHLIST_H

#include <vector>
#include <iostream>
using namespace std;

class Product;
class Buyer;

class Wishlist
{
private: 
	vector<const Product*>	m_products;					//	List of products that the buyer considers purchasing. 
	vector<bool>			m_cartIndication;			//	Array corresponding to the above array of products, indicating whether a product is in the cart (i.e. about to be purchased). Important for removal from Wishlist upon checkout.
	double					m_cost;
	const Buyer*			m_buyer; 

public:
// C'tors and D'tor
	Wishlist();
	Wishlist(const Wishlist&); 
	Wishlist(Wishlist&&);

// Const methods
	inline const Buyer*		getOwner()						const	{ return m_buyer; }
	inline int				getLogSize()					const	{ return m_products.size(); }
	inline double			GetWishlistTotalCost()			const	{ return m_cost; }
	bool					getCartIndication(int index)	const;
	bool					showWishlist()					const;
	const Product*			getProduct(int index)			const;
	bool					isWishlistedProduct(int serial)	const;

// Non-const methods
	bool					addToWishlist(const Product* product);
	void					changeProductCartStatus(int index); 
	void					clearChosenProducts();	//	This method cleans the array from products added to the cart. Important for the checkout stage.

// Operators
public:
	friend ostream&			operator<<(ostream& os, const Wishlist& wl);
private:
	const Wishlist&			operator=(const Wishlist&);

public:
	friend class Buyer;
};
#endif // !__WISHLIST_H
