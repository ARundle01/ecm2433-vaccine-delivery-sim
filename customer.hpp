#ifndef CUSTOMER_H
#define CUSTOMER_H
/*--------------------------- Includes --------------------------------------*/
#include <string>
#include <orderingExceptions.hpp>
/*--------------------------- Namespace -------------------------------------*/
using namespace std;
/*--------------------------- Class Definition ------------------------------*/
class Customer
{
    private:
        unsigned int quantity = 0;
        unsigned int customerNumber;
        string customerName;
    public:
        Customer(unsigned int, string);
                
        void addQuantity(int);
        void emptyQuantity();
        void shipOrder();
        
        int getQuantity();
        int getCustomerNumber();
        string getCustomerName();
};
/*---------------------------------------------------------------------------*/
#endif
