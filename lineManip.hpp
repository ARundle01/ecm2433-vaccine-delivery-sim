#ifndef __LINEMANIP_HPP
#define __LINEMANIP_HPP
/*--------------------------- Includes --------------------------------------*/
#include <iostream>
#include <sstream>
#include <string>
#include <orderingExceptions.hpp>
#include <cctype>
/*--------------------------- Namespace -------------------------------------*/
using namespace std;
/*--------------------------- Function Prototypes ---------------------------*/
bool isCustomerRecord(string);
bool isOrderRecord(string);
bool isEndRecord(string);
bool isNormalOrder(string);
bool isExpressOrder(string);
int retrieveCustomerNumber(string);
string retrieveCustomerName(string);
int retrieveDate(string);
int retrieveOrderNumber(string);
int retrieveOrderQuantity(string);
bool isValidEntry(string);
bool isValidCustomerNumber(string);
bool isValidQuantity(string);
bool isValidOrderType(string);
bool isValidDate(string);
int numberOfCustomerEntries(string[], int);
/*---------------------------------------------------------------------------*/
#endif
