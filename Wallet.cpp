#include <string>
#include "Wallet.h"
#include<iostream>
#include "CSVReader.h"


Wallet::Wallet()
{

}

void Wallet::insertCurrency(std::string type,double amount)
{
    double balance;
    if(amount<0)
        throw std::exception{};
    if(currencies.count(type)==0)   //checking if the wallet is emopty
        balance=0;
    else    //the wallet is not empty
        balance=currencies[type];
    balance+=amount;

    currencies[type]=balance;
}
bool Wallet::removeCurrency(std::string type,double amount)
{
    double balance;
    if(amount<0)    //checking it the wallet is empty 
        return false;   //hence the removal can't take place
    if(currencies.count(type)==0)   //checking if the wallet is having the type of currency asked for
    {
        std::cout<<"No currency for "<<type<<std::endl;
        return false;   //if required currency is not there then false is returned
    }
    else    //the wallet is not empty; we have enough money to remove from the wallet
    {
        if(containsCurrency(type,amount))
        {
            std::cout<<"Removing "<<type<<":"<<amount<<std::endl;
            currencies[type]-=amount;
            return true;
        }
        else    //the reuired type of currency is present but not in enough quantity
            return false;
    }
    

    currencies[type]=balance;
    return false;
}

bool Wallet::containsCurrency(std::string type, double amount)
{
    if(currencies.count(type)==0)
        return false;
    else
        return currencies[type]>=amount;    //returning on testing of the condition passed
    return false;
}

std::string Wallet::toString()
{
    std::string s;
    for(std::pair<std::string,double> pair:currencies) 
    {
        std::string currency=pair.first;    //pair.first access the first part of the pair
        double amount=pair.second;
        s+=currency+" : "+std::to_string(amount)+"\n";  //std::to_string() function converts the passed argument to string
    }
    return s;
}

/*
    ETH/BTC,0.01, 0.5, ask
    This means:  I have 0.5 ERTH, I will sell them at 0.01 BTC each

    ETH/BTC,0.001,0.5,bid
    This means: I have 0.01 BTC,I will buy 0.5 ETH at 0.01 BTC each
*/
bool Wallet::canFulfillOrder(OrderBookEntry order)
{
    std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');
    
    // for ask condition
    if (order.orderType == OrderBookType::ask)
    {
        double amount = order.amount;
        std::string currency = currs[0];  // first currency in the product
        std::cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;
        return containsCurrency(currency, amount);
    }

    // for bid condition
    if (order.orderType == OrderBookType::bid)
    {
        double amount = order.amount * order.price;  // total value of the bid
        std::string currency = currs[1];  // second currency in the product
        std::cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;
        return containsCurrency(currency, amount);
    }

    return false;  // fallback in case neither ask nor bid condition is fulfilled
}

void Wallet::processSale(OrderBookEntry& sale)
{
    std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');
    
    // for ask condition
    if (sale.orderType == OrderBookType::asksale)
    {
        double outgoingAmount = order.amount;  
        std::string outgoingCurrency = currs[0];  // first currency in the product
        double incomingAmount=order.amount*order.price;
        std::string incomingCurrency=surrs[1];

        currencies[incomingCurrency]+=incomingAmount;
        currencies[outgoingCurrency]-=outgoingAmount;
    }

    // for bid condition
    if (sale.orderType == OrderBookType::bidsale)
    {
        double incomingAmount = order.amount;  
        std::string incomingCurrency = currs[0];  // first currency in the product
        double outgoingAmount=order.amount*order.price;
        std::string outgoingCurrency=surrs[1];

        currencies[incomingCurrency]+=incomingAmount;
        currencies[outgoingCurrency]-=outgoingAmount;
    }
}