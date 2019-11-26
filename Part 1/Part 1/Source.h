#pragma warning(disable:4996)
#ifndef __SOURCE_H
#define __SOURCE_H

#include "System.h"
#include <iostream>
using namespace std;

const unsigned int MAX_OPTION = 11;
const unsigned int EXIT_OPTION = 11;
const int STOP = -10;

void runMenu(System& system);
void addBuyer(System& system);
void addSeller(System& system);
void addItemToSeller(System& system);
void addFeedbackToSeller();
void addToWishlist(System& system);
void addToCart(System& system);
void checkout(System& system);
void showAllBuyers(System& system);
void showAllSellers(System& system);
void showSpecificProduct(System& system);
#endif
