#include<string>
#include<map>
#include "OrderBook.h"
#include "OrderBookEntry.h"

class Wallet
{
    public:
        Wallet();   //class constructor
        void insertCurrency(std::string type,double amount);  //function to insert currency in the wallet
        bool removeCurrency(std::string type,double amount); //function to remove currency
        bool containsCurrency(std::string type, double amount); //function to check whether the wallet contains this much currency or not
        std::string toString(); //function torepresent the string representation of the wallet
        bool canFulfillOrder(OrderBookEntry order); //function to check if the wallet can cope with this ask or bid
        void processSale(OrderBookEntry order); //function to update the wallet of the username assuming that the order was made by the owner of the wallet
    private:
        std::map<std::string, double> currencies;   //we are storing the currencies in the wallet using the map
};