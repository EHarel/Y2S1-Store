/* The purpose of this class is to manage the dynamic array of all of the buyer's receipts,
meaning all his past purchases.
Within here you can find records of all the items he bought.
*/
#ifndef __PURCHASEHISTORY_H
#define __PURCHASEHISTORY_H

#include "Receipt.h"

class PurchaseHistory
{
private:
	Receipt**				receipts;			//	Dynamic array of all receipts.
	int						logSize, phySize;	//	variables to manage the dynamic array.

public:
// C'tors and D'tor
	PurchaseHistory();
	PurchaseHistory(const PurchaseHistory& other);
	PurchaseHistory(PurchaseHistory&& other);
	~PurchaseHistory();

	inline int				getLogSize()	const	{ return logSize; }
	inline Receipt**&		getReceipts()			{ return receipts; }
	bool					increasePurchaseHistorySize();

	const PurchaseHistory&	operator=(const PurchaseHistory& other);

	friend class Buyer;
};
#endif
