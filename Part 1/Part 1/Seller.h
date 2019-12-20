#pragma warning(disable:4996)
#ifndef __Seller_H
#define __Seller_H

#include "Address.h"
#include "Feedback.h"

class Buyer;
class Receipt;


class Seller
{
private:
	char*					m_username;
	int						m_password;
	Address					m_address;

	const Feedback**		m_feedbacks;							//	dynamically allocated array of feedbacks received
	int						m_feedLogSize, m_feedPhySize;			//	sizes for the feedback array
	Product**				m_catalog;								//	dynamically allocated array of products
	int						m_catLogSize, m_catPhySize;

// Private Methods
	bool					increaseFeedbackSize();
	bool					increaseMerchandiseSize();

public:
// C'tors and D'tor
	Seller() = delete;	
	Seller(char* name, int password, const Address& address);
	Seller(const Seller&) = delete;	
	~Seller();

//	Const methods
	inline const char*		getUsername()						const	{ return m_username; }
	inline const Address&	getAddress()						const	{ return m_address; }
	inline int				getCatalogLogSize()					const	{ return m_catLogSize; }
	inline bool				passwordCheck(int password)			const	{ return m_password == password; }
	const Product*			getProduct(const char* name)		const;	
	const Product*			getProduct(int serial)				const;
	void					showSeller()						const;
	void					showAllMerchandise()				const;
	void					showAllFeedbacks()					const;

//	Non-const methods
	bool					changeUsername(const char* username);
	bool					resetPassword(int newPassword, int currentPasswordVerification);
	bool					setAddress(const Address& other);		
	bool					addFeedback(const Feedback* feedback);
	bool					addProductToMerch(Product* product);

	friend class System;
};
#endif