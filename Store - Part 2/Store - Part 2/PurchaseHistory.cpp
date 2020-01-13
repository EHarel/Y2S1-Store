#include "PurchaseHistory.h"

// ----------------- C'TORS AND D'TOR ----------------- //
PurchaseHistory::PurchaseHistory()
{
	phySize = 10;
	logSize = 0;

	receipts = new Receipt*[phySize];
	if (!receipts)
		return;
}
PurchaseHistory::PurchaseHistory(const PurchaseHistory& other) : receipts(NULL)
{
	*this = other;
}
PurchaseHistory::PurchaseHistory(PurchaseHistory && other) : receipts(NULL)
{
	*this = other;
	other.receipts = nullptr;
}
PurchaseHistory::~PurchaseHistory()
{
	for (int i = 0; i < logSize; i++)
		delete receipts[i];
	delete []receipts;
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

const PurchaseHistory & PurchaseHistory::operator=(const PurchaseHistory & other)
{
	if (this != &other)
	{
		for (int i = 0; i < logSize; i++)
			delete receipts[i];
		delete[]receipts;
		logSize = other.logSize;
		phySize = other.phySize;
		receipts = new Receipt*[phySize];
		if (!receipts) // Allocation check
			exit(1);

		for (int i = 0; i < logSize; i++)
			receipts[i] = new Receipt(*(other.receipts[i]));

	}
	return *this;
}
