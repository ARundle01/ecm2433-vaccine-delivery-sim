#include <lineManip.hpp>
// checks that given line is a customer record
bool isCustomerRecord(string line)
{
    if (line[0] == 'C')
        return true;
    else
        return false;
}

// checks that given line is an order record
bool isOrderRecord(string line)
{
    if (line[0] == 'S')
        return true;
    else
        return false;
}

// checks that given line is end-of-day record
bool isEndRecord(string line)
{
    if (line[0] == 'E')
        return true;
    else
        return false;
}

// checks that given line is a normal order
bool isNormalOrder(string line)
{
    if (line[9] == 'N')
        return true;
    else
        return false;
}

// checks that given line is an express order
bool isExpressOrder(string line)
{
    if (line[9] == 'X')
        return true;
    else
        return false;
}

// retrieves customer number from a given customer record
int retrieveCustomerNumber(string line)
{
    string strNum = line.substr(1, 4);
    int customerNumber = stoi(strNum);
    
    return customerNumber;
}

// retrieves customer name from given customer record
string retrieveCustomerName(string line)
{
    int endIndex = line.length() - 1;
    string name = line.substr(5, endIndex);

    return name;
}

// retrieves date from given order or end record
int retrieveDate(string line)
{
    string strDate = line.substr(1, 8);
    int date = stoi(strDate);
    
    return date;
}

// retrieves customer number from given order record
int retrieveOrderNumber(string line)
{
    string strNum = line.substr(10, 4);
    int customerNumber = stoi(strNum);
    
    return customerNumber;
}

// retrieves quantity from given order record
int retrieveOrderQuantity(string line)
{
    string strQuant = line.substr(14, 3);
    int quantity = stoi(strQuant);

    return quantity;
}

// checks that a given line is a valid record type
bool isValidEntry(string line)
{
    if (isCustomerRecord(line) || isOrderRecord(line) || isEndRecord(line))
        return true;
    else
        return false;
}

// checks that given customer number is valid
bool isValidCustomerNumber(string customerNumber)
{
    for (char &c : customerNumber)
    {
        if (isalpha(c))
            return false;
    }
    return true;
}

// checks that given quantity is valid
bool isValidQuantity(string quantity)
{
    for (char &c : quantity)
    {
        if (isalpha(c))
            return false;
    }
    return true;
}

// checks that given order is a valid order type
bool isValidOrderType(string order)
{
    if (isNormalOrder(order))
        return true;
    else if (isExpressOrder(order))
        return true;
    else
        return false;
}

// checks that a given date is valid
bool isValidDate(string date)
{
    for (char &c : date)
    {
        if (isalpha(c))
            return false;
    }
    return true;
}

// returns the number of customer records in given file
int numberOfCustomerEntries(string lines[], int length)
{
    int num = 0;
    
    for (int index = 0; index < length; index++)
    {
        if (isCustomerRecord(lines[index]))
            num++;
    } 
    return num;
}
