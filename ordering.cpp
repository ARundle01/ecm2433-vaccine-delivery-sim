#include <ordering.hpp>

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
            throw new InvalidArgsException;

        string filename = argv[1];

        if (isTxt(filename) != true)
            throw new InvalidFileTypeException;

        start(filename);
        return 0;
    }
    catch (InvalidArgsException *e)
    {
        cout << "Usage: " << argv[0] << " FIlENAME" << endl;
        cerr << e->what() << endl;
        exit(-1);
    }
    catch (InvalidFileTypeException *e)
    {
        cout << "Must supply a '.txt' file" << endl;
        cerr << e->what() << endl;
        exit(-1);
    }
    catch (exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

// initiliazes and runs the vaccine ordering system
void start(string filename)
{
    char* buffer = getFileContents(filename);
    int length = numberOfLines(buffer);
    string* lines = new string[length];

    splitFileContents(lines, buffer);

    // Configure Customer storage
    int noCustomerRecords = numberOfCustomerEntries(lines, length);
    vector<Customer> customers;
    // reserve memory for all customers in file.
    customers.reserve(noCustomerRecords);
    int invoiceNum = 1000;

    try
    {
        int invoiceNum = 1000;
        int prevDate = 0;
        int currDate = 0;
        // start handling loop
        for (int index = 0; index < length; index++)
        {
            // check if entry is customer creation
            if (isCustomerRecord(lines[index]))
            {
                // check length of customer record
                if (lines[index].length() > 45)
                    throw new CustomerTooLongException;
                
                // check that cust num is only numbers
                if (!isValidCustomerNumber(lines[index].substr(1, 4)))
                    throw new InvalidCustomerNumberException;

                // This entry is valid, add to customer vector
                string name = retrieveCustomerName(lines[index]);
                int custNum = retrieveCustomerNumber(lines[index]);

                // if vector is empty, add new customer
                if (customers.size() == 0)
                {
                    customers.push_back(Customer(custNum, name));
                    customerAdded(custNum);
                }
                // if vector is not full, check that customer doesn't exist and add
                else if (customers.size() != customers.capacity())
                {
                    for (int cust = 0; cust < customers.size(); cust++)
                    {
                        if (customers[cust].getCustomerNumber() == custNum)
                            throw new CustomerExistsException;
                    }
                    customers.push_back(Customer(custNum, name));
                    customerAdded(custNum);
                }
            }
            // check if entry is an order
            else if (isOrderRecord(lines[index]))
            {
                // check length of order record
                if (lines[index].length() > 17)
                    throw new OrderTooLongException;
                
                if (!isValidOrderType(lines[index]))
                    throw new InvalidOrderTypeException;

                if (!isValidCustomerNumber(lines[index].substr(10, 4)))
                    throw new InvalidCustomerNumberException;

                if (!isValidQuantity(lines[index].substr(14, 3)))
                    throw new InvalidQuantityException;

                if (!isValidDate(lines[index].substr(1, 8)))
                    throw new InvalidDateException;

                int date = retrieveDate(lines[index]);

                // Next if ensures that an order is not made for a prev/future day                

                // if the prev and curr date are not set, set them
                if (prevDate == 0 && currDate == 0)
                {
                    prevDate = date;
                    currDate = date;
                }
                // if they are set and the same
                else if (prevDate == currDate)
                {
                    currDate = date; // set curr date to date of order
                }
                // if date is not current date, throw exception
                else if (date != currDate)
                    throw new InvalidDateException;

                int custNum = retrieveOrderNumber(lines[index]);
                int quantity = retrieveOrderQuantity(lines[index]);
                bool exists = false;

                if (customers.size() == 0)
                {
                    throw new EmptyCustomersException;
                }
                else
                {
                    // search for customer to order for
                    for (int cust = 0; cust < customers.size(); cust++)
                    {
                        int customerNumber = customers[cust].getCustomerNumber();
                        if (customerNumber == custNum)
                        {
                            // for normal order, add quantity but do not ship
                            if (isNormalOrder(lines[index]))
                            {
                                // add items to customer order
                                customers[cust].addQuantity(quantity);
                                normalOrder(custNum, quantity);
                                exists = true;
                                break;
                            }
                            // for express order, add quantity and ship
                            else if (isExpressOrder(lines[index]))
                            {
                                // add items to customer order
                                customers[cust].addQuantity(quantity);
                                expressOrder(custNum, quantity);
                                int total = customers[cust].getQuantity();
                                // show invoice
                                orderShipped(custNum, total);
                                invoice(custNum, invoiceNum, date, total);
                                customers[cust].shipOrder();
                                invoiceNum++;
                                exists = true;
                                break;
                            }
                        }
                    }
                    
                    // if customer is not found, throw exception
                    if (!exists)
                        throw new CustomerNotExistsException;    
                }
            }
            // check if entry is end of day record
            else if (isEndRecord(lines[index]))
            {
                // check length of end-of-day record
                if (lines[index].length() > 9)
                    throw new EndDayTooLongException;
                
                // check that date is only nums
                if (!isValidDate(lines[index].substr(1, 8)))
                    throw new InvalidDateException;
                // display end-of-day message
                dayEnd(currDate);
                // for each customer, check if they have outstanding orders
                for (int cust = 0; cust < customers.size(); cust++)
                {
                    int custNum = customers[cust].getCustomerNumber();
                    int quantity = customers[cust].getQuantity();
                    // if they have outstanding orders, deliever them
                    if (customers[cust].getQuantity() != 0)
                    {
                        orderShipped(custNum, quantity);
                        invoice(custNum, invoiceNum, currDate, quantity);
                        invoiceNum++;
                        customers[cust].shipOrder();
                    }
                }
                prevDate = currDate;
            }
            else
                // entry is not valid as it is none of the three above
                throw new InvalidEntryException;
        }
        delete[] lines; // free memory for lines
        vector<Customer>().swap(customers); // free memory for customer vector
    }
    catch (InvalidEntryException *e)
    {
        delete[] lines;
        vector<Customer>().swap(customers); // free memory for customer vector
        cout << "Entries must start with 'C', 'S' or 'E'" << endl;
        cerr << e->what() << endl;
        exit(-1);
    }
    catch (CustomerTooLongException *e)
    {
        delete[] lines;
        vector<Customer>().swap(customers); // free memory for customer vector
        cout << "Customer entries cannot be longer than 45 characters" << endl;
        cerr << e->what() << endl;
        exit(-1);
    }
    catch (OrderTooLongException *e)
    {
        delete[] lines;
        vector<Customer>().swap(customers); // free memory for customer vector
        cout << "Order entries cannot be longer than 17 characters" << endl;
        cerr << e->what() << endl;
        exit(-1);
    }
    catch (EndDayTooLongException *e)
    {
        delete[] lines;
        vector<Customer>().swap(customers); // free memory for customer vector
        cout << "End-of-day entries cannot be longer than 9 characters" << endl;
        cerr << e->what() << endl;
        exit(-1);
    }
    catch (InvalidCustomerNumberException *e)
    {
        delete[] lines;
        vector<Customer>().swap(customers); // free memory for customer vector
        cout << "Customer numbers must be 4 digits and zero-padded" << endl;
        cerr << e->what() << endl;
        exit(-1);
    }
    catch (InvalidQuantityException *e)
    {
        delete[] lines;
        vector<Customer>().swap(customers); // free memory for customer vector
        cout << "Order quantities must be 3 digits and zero-padded" << endl;
        cerr << e->what() << endl;
        exit(-1);
    }
    catch (InvalidOrderTypeException *e)
    {
        delete[] lines;
        vector<Customer>().swap(customers); // free memory for customer vector
        cout << "Order types must be 'N' or 'X'" << endl;
        cerr << e->what() << endl;
        exit(-1);
    }
    catch (InvalidDateException *e)
    {
        delete[] lines;
        vector<Customer>().swap(customers); // free memory for customer vector
        cout << "Dates must be in the format 'YYYYMMDD'" << endl;
        cerr << e->what() << endl;
        exit(-1);
    }
    catch (CustomerExistsException *e)
    {
        delete[] lines;
        vector<Customer>().swap(customers);
        cout << "A customer with that ID already exists" << endl;
        cerr << e->what() << endl;
        exit(-1);
    }
    catch (EmptyCustomersException *e)
    {
        delete[] lines;
        vector<Customer>().swap(customers);
        cout << "There are no customers to make orders for" << endl;
        cerr << e->what() << endl;
        exit(-1);
    }
    catch (CustomerNotExistsException *e)
    {
        delete[] lines;
        vector<Customer>().swap(customers);
        cout << "A customer with that ID does not exist" << endl;
        cerr << e->what() << endl;
        exit(-1);
    }
    catch (EmptyQuantityException *e)
    {
        delete[] lines;
        vector<Customer>().swap(customers);
        cout << "This customer does not have anything ordered" << endl;
        cerr << e->what() << endl;
        exit(-1);
    }
    catch (bad_alloc &b)
    {
        vector<Customer>().swap(customers); // free memory for customer vector
        cout << "Cannot allocate memory" << endl;
        cerr << "Error: " << b.what() << endl;
        exit(-1);
    }
    catch (...)
    {
        delete[] lines;
        vector<Customer>().swap(customers); // free memory for customer vector
        throw;
    }
}

// Checks that given string ends with .txt
bool isTxt(string filename)
{
    int len = filename.length();
    size_t found = filename.find(".txt");
    if (found != string::npos)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// outputs all customers in the vector
void showCustomers(vector<Customer> &customers)
{
    for (int index = 0; index < customers.size(); index++)
    {
        cout << "Customer Name: " << customers[index].getCustomerName() << endl;
        cout << "Customer Number: " << customers[index].getCustomerNumber() << endl;
    }
}

// converts given number into a 4-digit, zero-padded string
string stringifyNum(int num)
{
    if (num < 10)
    {
        string strNum = "000" + to_string(num);
        return strNum;
    }
    else if (num < 100)
    {
        string strNum = "00" + to_string(num);
        return strNum;
    }
    else if (num < 1000)
    {
        string strNum = "0" + to_string(num);
        return strNum;
    }
    else if (num < 9999)
    {
        string strNum = to_string(num);
        return strNum;
    }
}

// outputs message about adding of customer
void customerAdded(int custNum)
{
    cout << "OP: customer " << stringifyNum(custNum) << " added" << endl;
}

// outputs message about a normal order
void normalOrder(int custNum, int quantity)
{
    cout << "OP: customer " << stringifyNum(custNum) << ": normal order: quantity " << quantity << endl;
}

// outputs message about an express order
void expressOrder(int custNum, int quantity)
{
    cout << "OP: customer " << stringifyNum(custNum) << ": EXPRESS order: quantity " << quantity << endl;
}

// outputs message about shipping an order
void orderShipped(int custNum, int quantity)
{
    cout << "OP: customer " << stringifyNum(custNum) << ": shipped quantity " << quantity << endl;
}

// outputs message about an invoice
void invoice(int custNum, int invoiceNum, int date, int quantity)
{
    cout << "SC: customer " << stringifyNum(custNum) << ": invoice " << invoiceNum << ": date " << date << ": quantity " << quantity << endl;
}

// outputs message about a day ending
void dayEnd(int date)
{
    cout << "OP: end of day " << date << endl;
}
