#pragma once
#include "OrderBook.h"
#include "CSVReader.h"
#include<map>
#include<algorithm>


OrderBook::OrderBook(std::string filename)    //constructor,reading a csv file
{
    orders=CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts()
// vector of all known products in the data set
{
    std::vector<std::string> products;

    std::map<std::string,bool>  prodMap;    //Mapping between string and boolean
    for(OrderBookEntry& e:orders)
        prodMap[e.product]=true;

    for(auto const& e:prodMap)
        products.push_back(e.first);    //this code will iterate over prodMap annd pull out each element in prodMap to iterate. e.first is key and e.last will be the value
    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,   //returns vector of Orders according to the sent filters    
                                               std::string products,
                                               std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;
    for(OrderBookEntry& e:orders)
    {
        if(e.orderType==type && e.product==products && e.timestamp==timestamp)
        {
            orders_sub.push_back(e);
        }
    }
    return orders_sub;
}

std::string OrderBook::getEarliestTime()
{
    // for getting the earliest time,we assume that  the orders are sorted, and we need to return the first order.
    return orders[0].timestamp; //returning the timestamp for the first order
}

std::string OrderBook::getNextTime(std::string timestamp)
{
    // orders are sorted by time
    std::string next_timestamp="";
    for(OrderBookEntry& e:orders)
    {
        if(e.timestamp>timestamp)   //if the timestamp is later in time
        {
            next_timestamp=e.timestamp;
            break;
        }
    }

    //for the case when there is no next timestamp then, we consider the first timestamp itself
    if(next_timestamp =="")
        next_timestamp=orders[0].timestamp;
    return next_timestamp;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
    double max=orders[0].price;
    for(OrderBookEntry& e:orders)
    {
        if(e.price>max)
            max=e.price;
    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders)
{
    double min=orders[0].price;
    for(OrderBookEntry& e:orders)
    {
        if(e.price<min)
            min=e.price;
    }
    return min;
} 
    
void OrderBook::insertOrder(OrderBookEntry& order)
{
    orders.push_back(order);    //inserting the order to the vector "orders" at the end of the vector

    //now we use the sorting algorithm to sort the order entered in the vector
    std::sort(orders.begin(),orders.end(),OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product,std::string timestamp)
{
    //asks=orderBook.asks
    std::vector<OrderBookEntry> asks=getOrders(OrderBookType::ask,product,timestamp);

    //bids=orderBook.bids
    std::vector<OrderBookEntry> bids=getOrders(OrderBookType::bid,product,timestamp);

    //sales=[]
    std::vector<OrderBookEntry> sales;

    //sorting asks lowest first, i.e., ascending order
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);

    //sort asks highest first
    std::sort(bids.begin(),bids.end(),OrderBookEntry::compareByPriceDesc);

    //for ask in asks
    for(OrderBookEntry& ask:asks)
    {
        //for bid in bids
        for(OrderBookEntry& bid:bids)
        {
            //if bid.price>=ask.price; we have a match
            if(bid.price>=ask.price)
            {
                /*sale =new order()
                sale.price= ask.price */
                OrderBookEntry sale{ask.price, 0,timestamp,product,
                OrderBookType::asksale};    //creating an order and defaulting it to the asksale type of order

                if(bid.username=="simuser")
                {
                    sale.username="simuser";
                    sale.orderType=OrderBookType::bidsale;
                }
                if(ask.username=="simuser")
                {
                    sale.username="simuser";
                    sale.orderType=OrderBookType::asksale;
                }

                // now work out how much was sold and create new bids and asks covering anything that was not sold
                // if bid.amount== ask.amount; bid completely clears ask
                if(bid.amount == ask.amount)
                {
                    /* sale.amount =ask.amount
                    sales.append(sale)
                    bid.amount=0; make sure the bid is not processed again
                    can do no more with this ask
                    go onto the next ask
                    break */
                    sale.amount=ask.amount;
                    sales.push_back(sale);
                    bid.amount=0;
                    break;
                }

                // if bid.amount >ask.amount; ask is completely gone slice the bid
                if(bid.amount >ask.amount)
                {
                    /* sales.amount=ask.amount
                    sales.append(sale)
                    # we adjust the bid in place, so it can be used to process the next ask
                    bid.amount =bid.amount-ask.amount
                    #ask is completely gone, so go to next ask
                    break */
                    sale.amount=ask.amount;
                    sales.push_back(sale);
                    bid.amount=bid.amount-ask.amount;
                    break;
                }

                //if bid.amount<ask.amount; bid is completely gone slice the ask
                if(bid.amount<ask.amount && bid.amount>0)
                {
                    /* sale.amount =bid.amount
                    sales.append(sale)
                    # update the ask and allow further bid to process the reamining amount
                    ask.amount=ask.amount-bid.amount
                    bid.amount=0; make sure the bid not processed again
                    # some ask remain so go to the next bid
                    continue */
                    sale.amount=bid.amount;
                    sales.push_back(sale);
                    ask.amount=ask.amount-bid.amount;
                    bid.amount=0;
                    continue;
                }
            }
        }
    }
    return sales;
}
