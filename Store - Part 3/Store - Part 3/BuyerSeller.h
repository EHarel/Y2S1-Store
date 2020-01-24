#ifndef __BUYSELL_H
#define __BUYSELL_H

#include "Seller.h"
#include "Buyer.h"

class BuyerSeller : public Seller, public Buyer
{
private:
	static int			buyer_seller_count;

public:
						BuyerSeller(const string& username, int password, const Address& address);
						BuyerSeller(const BuyerSeller& other) = delete; // No copying of users.
						BuyerSeller(BuyerSeller&& other) = delete;
						BuyerSeller(ifstream& in) : User(in), Buyer(in), Seller(in) { ++buyer_seller_count; }
						~BuyerSeller() { --buyer_seller_count; }

	inline static int	GetBuyerSellerCount()	{ return buyer_seller_count; }

	virtual void		toOs(ostream& os) const override;

	const BuyerSeller&	operator=(const BuyerSeller& other) = delete;

	friend class System;
};
#endif // !__BUYSELL_H



