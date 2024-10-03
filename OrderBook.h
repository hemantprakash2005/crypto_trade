#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include<string>
#include<vector>

class OrderBook
{
    public:
        OrderBook(std::string filename);    //constructor,reading a csv file
        std::vector<std::string> getKnownProducts();
        // vector of all known products in the data set
        std::vector<OrderBookEntry> getOrders(OrderBookType type,   //returns vector of Orders according to the sent filters    
                                               std::string products,
                                               std::string timestamp);

        std::string getEarliestTime();  //returns the first order done in the data set
        std::string getNextTime(std::string timestamp); //returns the next time after the sent time in the orderBook


        void insertOrder(OrderBookEntry& order); //to insert an order in the orderBook. 
        /* For doing this, we will first insert the order at the end of the orderBook then we sort the order accordingly */

        std::vector<OrderBookEntry> matchAsksToBids(std::string product,std::string timestamp);

        static double getHighPrice(std::vector<OrderBookEntry>& orders);    // finds the highest price in the orders.Its is static because it does not need to look for data stored in the class.
        static double getLowPrice(std::vector<OrderBookEntry>& orders); // return the lowest price in the orders.

    private:
        std::vector<OrderBookEntry> orders;
};  