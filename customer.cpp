#include <customer.hpp>
// constructor definition
Customer::Customer(unsigned int customerNum, string name)
{
    this->customerNumber = customerNum;
    this->customerName = name;
}
// adds given int to quantity
void Customer::addQuantity(int num)
{
    this->quantity += num;
}
// resets quantity to zero
void Customer::emptyQuantity()
{
    this->quantity = 0;
}
// resets quantity but throws exception if already zero
void Customer::shipOrder()
{
    if (this->quantity == 0)
    {
        throw new EmptyQuantityException;
    } 
    else
    {
        this->emptyQuantity();
    }
}
// returns quantity
int Customer::getQuantity()
{
    return this->quantity;
}
// returns customer number
int Customer::getCustomerNumber()
{
    return this->customerNumber;
}
// returns customer name
string Customer::getCustomerName()
{
    return this->customerName;
}
