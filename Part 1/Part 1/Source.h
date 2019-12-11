#pragma warning(disable:4996)
#ifndef __SOURCE_H
#define __SOURCE_H

#include "System.h"
#include <iostream>
using namespace std;

const int BUYER_OPTION = 1;
const int SELLER_OPTION = 2;
const unsigned int EXIT_OPTION = 11;
const int STOP = -10;

void runMenu(System& system);

// General
void addUser(System& system);
void signIn(System& system);
void showAllBuyers(System& system);
void showAllSellers(System& system);
void showSpecificProduct(System& system);

// Buyer related functions
void runBuyerMenu(System& system, Buyer*& buyer);
void addFeedbackToSeller(System& system, Buyer*&);
void addToWishlist(System& system, Buyer*& buyer);
void addToCart(System& system, Buyer*& buyer);
void checkout(System& system, Buyer*& buyer);

// Seller related functions
void runSellerMenu(System& system, Seller*& seller);
void addItemToSeller(System& system, Seller*& seller);

#endif
