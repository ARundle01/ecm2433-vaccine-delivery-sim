#ifndef ORDERING_H
#define ORDERING_H
/*--------------------------- Includes --------------------------------------*/
#include <iostream>
#include <customer.hpp>
#include <fileManip.hpp>
#include <lineManip.hpp>
#include <orderingExceptions.hpp>
#include <string>
#include <vector>
/*--------------------------- Namespace -------------------------------------*/
using namespace std;
/*--------------------------- Function Prototype ----------------------------*/
void start(string);
bool isTxt(string);
void showCustomers(vector<Customer> &);
string stringifyNum(int);
void customerAdded(int);
void normalOrder(int, int);
void expressOrder(int, int);
void orderShipped(int, int);
void invoice(int, int, int, int);
void dayEnd(int);
/*---------------------------------------------------------------------------*/
#endif
