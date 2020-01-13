#include "BuyerSeller.h"

int BuyerSeller::buyer_seller_count = 0;

BuyerSeller::BuyerSeller(const char* username, int password, const Address& address) : User(username, password, address), Buyer(username, password, address), Seller(username, password, address)
{
}


BuyerSeller::~BuyerSeller()
{
}


void BuyerSeller::toOs(ostream& os) const
{
	Buyer::toOs(os);
	Seller::toOs(os);
}