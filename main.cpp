#include<iostream>
#include<string>    
#include<vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVReader.h"
#include "Wallet.h"

int main()
{
    MerkelMain app{};   //creating an object of the MerkelMain class
    app.init();
    //CSVReader::readCSV("CryptoTrade.csv");
    // Wallet wallet;
    // wallet.insertCurrency("BTC",10);
    // wallet.insertCurrency("USDT",10000);
    // std::cout<<wallet.toString()<<std::endl;
    // wallet.removeCurrency("USDT",1000);
    // std::cout<<wallet.toString()<<std::endl;
    return 0;
}
    
//     //iterating over the vector of objects
//     for(int i=0;i<orders.size();i++)
//     {
//         std::cout<<"\nDetails of order no.:"<<i+1<<endl;
//         std::cout<<"Price: "<<orders.at(i).price<<endl;
//         std::cout<<"Amount: "<<orders.at(i).amount<<endl;
//         std::cout<<"Timestamp: "<<orders.at(i).timestamp<<endl;
//         std::cout<<"Product: "<<orders.at(i).product<<endl;
//         std::cout<<"Order Type: ";
//         if(orders.at(i).orderType == OrderBookType::bid)
//             std::cout<<"Bid"<<endl;
//         else if(orders.at(i).orderType == OrderBookType::ask)
//             std::cout<<"Ask"<<endl;
//     } 

//     std::cout<<"\n\nPress 1:For Average Price"<<endl;
//     std::cout<<"Press 2:For Lowest Price"<<endl;
//     std::cout<<"Press 3:For Highest Price"<<endl;
//     std::cout<<"Press 4:To exit"<<endl;
//     std::cout<<"Enter your choice: ";
//     int choice;
//     cin>>choice;
//     switch(choice)
//     {
//         case 1:
//             computeAveragePrice(orders);
//             break;
//         case 2:
//             computeLowPrice(orders);
//             break;
//         case 3:
//             computeHighPrice(orders);
//             break;
//         case 4:
//             break;
//         default:
//             std::cout<<"Invalid choice!"<<endl;
//             break;
//     }

//     return 0;
// }