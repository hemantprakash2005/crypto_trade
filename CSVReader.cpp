#pragma once
#include "CSVReader.h"
#include<vector>
#include "OrderBookEntry.h"
#include<string>
#include<iostream>
#include<fstream>   //for opening a file


CSVReader::CSVReader()  //constructor of the class:CSVReader
{

}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFile) //reades the CSV file and tokenises them
{
    std::vector<OrderBookEntry> entries;

    std::ifstream csvFile{csvFile}; //open the file paassed to it
    std::string line;
    if(csvFile.is_open())   //checks of the file is open
    {
        while(std::getline(csvFile,line))   //iterate over the kines in the file
        {
            try{
            OrderBookEntry obe=stringToOBE(tokenise(line,',')); //converts into the tokens of strings
            entries.push_back(obe); //stores in the vector
            }
            catch(const std::exception& e)
            {
                std::cout<<"CSVReader::readCSV bad data"<<std::endl;
            }
        }
    }
    std::cout<<"CSVReader::readCSV read"<<entries.size()<<"enteries"<<std::endl;    //printing thr number of tokens read
    return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine,char seperator)    //for tokenising the CSV file into tokens
{
   std::vector<std::string> tokens;    //vector of tokens of CSV file
    signed int start, end;
    std::string token;
    start=csvLine.find_first_not_of(seperator,0);
    do
    {
        end=csvLine.find_first_of(seperator,start); //end=next "seperator" after start
        if(start==csvLine.length() ||start==end) break;
        if(end>=0)
            token =csvLine.substr(start,end-start);
        else
            token=csvLine.substr(start,csvLine.length()-start);
        tokens.push_back(token);
        start=end+1;
    }while(end>0);
    return tokens;
}

OrderBookEntry CSVReader::stringToOBE(std::vector<std::string> tokens)
{
    double price, amount;
    if(tokens.size()!=5)
    {
        std::cout<<"Basd line"<<std::endl;
        throw std::exception{}; //if the number of tokens is less than 5 then it will throw an exception
    }
    try
    {
        price=std::stod(tokens[3]);
        amount=std::stod(tokens[4]);
    }
    catch(const std::exception& e)
    {
        std::cout<<"Bad FLoat !"<<std::endl;
        throw;
    }
    

    OrderBookEntry obe{price,       //creating the object of the OrderBookEntry class
                        amount,
                        tokens[0],
                        tokens[1], 
                        OrderBookEntry::stringToOrderBookType(tokens[2])};
    return obe;
}

OrderBookEntry CSVReader::stringToOBE(std::string priceString,std::string amountString,std::string timestamp,std::string product,OrderBookType orderType)
{
    double price,amount;
    try
    {
        price=std::stod(priceString);
        amount=std::stod(amountString);
    }
    catch(const std::exception& e)
    {
        std::cout<<"CSVReader::stringToOBE Bad Float !"<<std::endl;
        throw;
    }
    OrderBookEntry obe{price,       //creating the object of the OrderBookEntry class
                        amount,
                        timestamp,
                        product, 
                        orderType};
    
    return obe;
}
