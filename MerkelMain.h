#pragma once
#include<vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
class MerkelMain
{
    public:
        MerkelMain();   // constructor

        void init();    //call this function to start the program
        //specifications of the functions
    private:    //this will not let the main.cpp access these functions directly
        //void loadOrderBook(); //load the some data in some vector
        void printMenu();
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeframe();
        int getUserOption();
        void processUserOption(int userOption);

        std::string currentTime;
        OrderBook orderBook{"CryptoTrader.csv"}; 
        Wallet wallet;
};