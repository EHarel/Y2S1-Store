#include "PurchaseHistory.h"

PurchaseHistory::PurchaseHistory()
{
	phySize = 10;
	logSize = 0;

	receipts = new Receipt*[phySize];
	if (!receipts)
		return;
}

PurchaseHistory::~PurchaseHistory()
{
	for (int i = 0; i < logSize; i++)
		delete receipts[i];
	delete []receipts;
}



int PurchaseHistory::getLogSize()	const
{
	return logSize;
}

Receipt**& PurchaseHistory::getReceipts()
{
	return receipts;
}



bool PurchaseHistory::increasePurchaseHistorySize()
{
	phySize *= 2;
	Receipt** temp = new Receipt*[phySize];
	if (!temp)
		return false;
	for (int i = 0; i < logSize; i++)
		temp[i] = receipts[i];
	delete[]receipts;
	receipts = temp;
	return true;
}