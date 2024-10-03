//Using the header file created
#include "OrderBookEntry.h" //calling the self-created header file

//the first OrderBookEntry below is the namespace we are using
// in that particular namespace the constructor OrderBookEntry has been defined
OrderBookEntry::OrderBookEntry(double _price,
                double _amount,
                std::string _timestamp,
                std::string _product,
                OrderBookType _orderType,
                std::string _username)://initilaising the values in the constructor
                        price(_price),
                        amount(_amount),
                        timestamp(_timestamp),
                        product(_product), 
                        orderType(_orderType),
                        username(_username)     //we dont need to write the defult specifier in the header file only, no in the .cpp file
{
}
OrderBookType OrderBookEntry::stringToOrderBookType(std::string s)
{
        if(s=="ask") 
        return OrderBookType::ask;
        if(s=="bid")
        return OrderBookType::bid;
        
        return OrderBookType::unkown;
}