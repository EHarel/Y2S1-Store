/* The purpose of this class is to manage the dynamic array of all of the buyer's receipts,
meaning all his past purchases.
Within here you can find records of all the items he bought.
*/
#ifndef __PURCHASEHISTORY_H
#define __PURCHASEHISTORY_H

class Receipt;

class PurchaseHistory
{
private:
	Receipt**		receipts;			//	Dynamic array of all receipts.
	int				logSize, phySize;	//	variables to manage the dynamic array.

public:
// Constructors and Destructor
	PurchaseHistory();
	~PurchaseHistory();

	int getLogSize()	const;

	Receipt**& getReceipts();

	bool increasePurchaseHistorySize();

	friend class Buyer;
};
#endif
