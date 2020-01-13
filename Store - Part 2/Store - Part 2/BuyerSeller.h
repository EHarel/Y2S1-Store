#ifndef __BUYSELL_H
#define __BUYSELL_H

#include "Seller.h"
#include "Buyer.h"

class BuyerSeller : public Seller, public Buyer
{
private:
	static int		buyer_seller_count;

public:
	BuyerSeller(const char* username, int password, const Address& address);
	~BuyerSeller();

	inline int		GetBuyerSellerCount() const { return buyer_seller_count; }

	virtual void	toOs(ostream& os) const override;

	friend class System;
};

#endif // !__BUYSELL_H



