#include<string>    
#pragma once    //to include it only once
enum class OrderBookType{bid,ask, unkown,bidsale,asksale};  //specifies the only  values it can hold
// unknown is any other string another than bid and ask

class OrderBookEntry
{
    public:
        //list of the data members
        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;
        std::string username;

        //constructor without any implementations parts
        // initiliasation doesn't take place here
        OrderBookEntry(
                        double _price,
                        double _amount,
                        std::string _timestamp,
                        std::string _product,
                        OrderBookType _orderType,
                        std::string username="dataset");    //if no other name is input by the user then, the default name is "dataset"
        
        static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2) 
        {
            return e1.timestamp<e2.timestamp;
        }

        static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)    //sorting the orders by prices in ascending order
        {
            return e1.price<e2.price;
        }

        static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)  //sorting the orders by price in descending orders
        {
            return e1.price>e2.price;
        }

        static OrderBookType stringToOrderBookType(std::string s);
};