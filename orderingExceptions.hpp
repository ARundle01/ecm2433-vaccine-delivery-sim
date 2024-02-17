#ifndef __ORDERINGEXCEPTIONS_HPP
#define __ORDERINGEXCEPTIONS_HPP
/*--------------------------- Includes --------------------------------------*/
#include <exception>
/*--------------------------- Namespace -------------------------------------*/
using namespace std;
/*--------------------------- Exception Class Definitions -------------------*/
class CustomerTooLongException: public exception
{
    public:
        virtual const char *what() const throw()
        {
            return "Error: Customer entry too long";
        }
};

class InvalidCustomerNumberException: public exception
{
    public:
        virtual const char *what() const throw()
        {
           return "Error: Invalid customer number";
        }
};

class InvalidEntryException: public exception
{
    public:
        virtual const char *what() const throw()
        {
            return "Error: Invalid line entry";
        }
};

class OrderTooLongException: public exception
{
    public:
        virtual const char *what() const throw()
        {
            return "Error: Order entry too long";
        }
};

class InvalidOrderTypeException: public exception
{
    public:
        virtual const char *what() const throw()
        {
            return "Error: Invalid order type";
        }
};
 
class InvalidDateException: public exception
{
    public:
        virtual const char *what() const throw()
        {
            return "Error: Invalid date format";
        }
};

class InvalidQuantityException: public exception
{
    public:
        virtual const char *what() const throw()
        {
            return "Error: Invalid quantity";
        }
};

class EndDayTooLongException: public exception
{
    public:
        virtual const char *what() const throw()
        {
            return "Error: End-of-day entry too long";
        }
};

class InvalidArgsException: public exception
{
    public:
        virtual const char *what() const throw()
        {
            return "Error: Invalid number of arguments supplied";
        }
};

class InvalidFileTypeException: public exception
{
    public:
        virtual const char *what() const throw()
        {
            return "Error: Incorrect filetype supplied";
        }
};

class CustomerExistsException: public exception
{
    public:
        virtual const char *what() const throw()
        {
            return "Error: Customer already exists";
        }
};

class EmptyCustomersException: public exception
{
    public:
        virtual const char *what() const throw()
        {
            return "Error: No customers";
        }
};

class CustomerNotExistsException: public exception
{
    public:
        virtual const char *what() const throw()
        {
            return "Error: Customer does not exist";
        }
};

class EmptyQuantityException: public exception
{
    public:
        virtual const char *what() const throw()
        {
            return "Error: Attempting to deliver quantity of zero";
        }
};
/*---------------------------------------------------------------------------*/
#endif
