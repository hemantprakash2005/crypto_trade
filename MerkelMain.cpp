#pragma once
#include "MerkelMain.h"
#include<iostream>
#include<vector>
#include "OrderBookEntry.h"//implementing the bodies of the functions specifind in the Merkelmain.h file
#include "CSVReader.h"
#include<string>

MerkelMain::MerkelMain()
{

}
void MerkelMain::init() //this function is used for making the objects do the work
{
    //loadOrderBook(); /*We dont need it anymore as it will be used form the csv file*/
    int input;
    currentTime=orderBook.getEarliestTime();
    wallet.insertCurrency("BTC",10);
    while(true)
    {
        /* We are able to direclty usie the functions of the MerkelMain class because we have already mentioned the namespace we are using which is MerkelMain*/
        printMenu();
        input=getUserOption();
        processUserOption(input);
    }
} 
// void MerkelMain::loadOrderBook()
// {
//     orders=CSVReader::readCSV("CryptoTrade.csv");
//     //std::vector <OrderBookEntry> orders; //vector of objects
//     // the vector "orders" here, is in local scope of loadOrderBook() function only
//     // OrderBookEntry order1{1000,
//     //                 0.02,
//     //                 "2024/09/09 17:01:24.884492",
//     //                 "BTC/USDT",
//     //                 OrderBookType::bid};
//     // orders.push_back(order1);  //adding the order1 object to the vector

//     // OrderBookEntry order2{3000,
//     //                 0.02,
//     //                 "2024/09/09 17:01:24.884492",
//     //                 "BTC/USDT",
//     //                 OrderBookType::ask};
//     // orders.push_back(order2);  //adding the order2 object to the vector

// }

void MerkelMain::printMenu()
{
    std::cout<<"1:Print Help"<<std::endl;
    std::cout<<"2:Print exchcange stats"<<std::endl;
    std::cout<<"3:Make an Ask"<<std::endl;
    std::cout<<"4:Make a bid"<<std::endl;
    std::cout<<"5:Print wallet"<<std::endl;
    std::cout<<"6:Continue"<<std::endl;
    std::cout<<"Current Time"<<currentTime<<std::endl;
}
void MerkelMain::printHelp()
{
    std::cout<<"Help- your aim is make money. Analyse the market and make money accordingly "<<std::endl;
}
void MerkelMain::printMarketStats()
{
    // std::cout<<"OrderBook contains : "<<orders.size()<<" entries"<<std::endl;
    // unsigned int bids=0;
    // unsigned int asks=0;
    // for(OrderBookEntry& entry:orders)
    // {
    //     if(entry.orderType==OrderBookType::ask) //counting the number of asks in the CSV file
    //         asks++;
    //     if(entry.orderType==OrderBookType::bid) //counts the number of bids in the CSV file
    //         bids++;
    // }
    // std::cout<<"Number of asks: "<<asks<<std::endl;
    // std::cout<<"Number of bids: "<<bids<<std::endl;

    for(std::string const& s:orderBook.getKnownProducts())
    {
        std::cout<<"Product:"<< s <<std::endl;
        std::vector<OrderBookEntry> entries=orderBook.getOrders(OrderBookType::ask,s,currentTime);  //it will down orders from the current time frame 
        std::cout<<"Asks seen: "<<entries.size()<<std::endl;
        std::cout<<"Max Ask: "<<OrderBook::getHighPrice(entries)<<std::endl;
        std::cout<<"Min Ask: "<<OrderBook::getLowPrice(entries)<<std::endl;
    }
}
void MerkelMain::enterAsk()
{
    std::cout<<"Mark an Ask- enter the amount:product,price,amount "<<std::endl;
    std::cout<<"eg:ETH/BTC,200,0.5"<<std::endl;
    std::string input;
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');    // we don't need this line anymore as we are now entering all the string input using the getline() method
    std::getline(std::cin,input);
    std::vector<std::string> tokens=CSVReader::tokenise(input,',');
    if(tokens.size()!=3)
        std::cout<<"Bad input: "<<input<<std::endl;
    else    
    {
        try
        {
            OrderBookEntry obe=CSVReader::stringToOBE(tokens[1], tokens[2],currentTime,tokens[0],OrderBookType::ask);
            obe.username="simuser";

            if(wallet.canFulfillOrder(obe))
            {
                std::cout<<"Wallet Looks good"<<std::endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout<<"Wallet has insufficient insufficient fund"<<std::endl;
            }
        }
        catch(const std::exception& e)
        {
            std::cout<<"MerkelMain:: enterAsk Bad Input"<<std::endl;
        }
    }

    std::cout<<"You typed: "<<input<<std::endl;
}
void MerkelMain::enterBid()
{
    std::cout<<"Make a bid - enter the amount "<<std::endl;
    std::string input;
    std::getline(std::cin,input);
    std::vector<std::string> tokens=CSVReader::tokenise(input,','); //tokeinsing the inputs
    if(tokens.size()!=3)
        std::cout<<"Bad input: "<<input<<std::endl;
    else    
    {
        try
        {
            OrderBookEntry obe=CSVReader::stringToOBE(tokens[1], tokens[2],currentTime,tokens[0],OrderBookType::bid);
            obe.username="simuser";

            if(wallet.canFulfillOrder(obe))
            {
                std::cout<<"Wallet Looks good"<<std::endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout<<"Wallet has insufficient insufficient fund"<<std::endl;
            }
        }
        catch(const std::exception& e)
        {
            std::cout<<"MerkelMain:: enterBid Bad Input"<<std::endl;
        }
    }

    std::cout<<"You typed: "<<input<<std::endl;
}
void MerkelMain::printWallet()
{
    std::cout<<"Your Wallet looks empty"<<std::endl;
    std::cout<<wallet.toString()<<std::endl;
}
void MerkelMain::gotoNextTimeframe()    //here the matching between the asks and the bids takes place
{
    std::cout<<"Going to the next time frame"<<std::endl;
    std::vector<OrderBookEntry> sales=orderBook.matchAsksToBids("ETH/BTC",currentTime);
    std::cout<<"Sales: "<<sales.size()<<std::endl;
    for(OrderBookEntry& sale:sales)
    {
        std::cout<<"Sale price: "<<sale.price<<"Amount: "<<sale.amount<<std::endl;
        if(sale.username=="simuser")
        {
            //update the wallet of the user
            wallet.processSale(sale);
        }
    }

    currentTime=orderBook.getNextTime(currentTime);
}
int MerkelMain::getUserOption()
{
    int userOption=0;

    std::cout<<"Type in 1 to 6"<<std::endl;
    std::string line;
    std::getline(std::cin,line);
    try 
    {
        userOption=std::stoi(line); //converts string to integer
    }
    catch(const std::exception& e)
    {
        //empty catch block
    }

    //std::cin>>userOption;   //this particular way of string input is lean but it is not roboust. Foe making it more robiust, we need to use getline() function for string input.
    std::cout<<"Your choice: "<<userOption<<std::endl;
    return userOption;
}
void MerkelMain::processUserOption(int userOption)
{
    if(userOption==1)
       printHelp();
    else if(userOption==2)
        printMarketStats();
    else if(userOption==3)
        enterAsk();
    else if(userOption==4)
        enterBid();
    else if(userOption==5)
        printWallet();
    else if(userOption==6)
        gotoNextTimeframe();
    else
        std::cout<<"Invalid Input"<<std::endl;
}