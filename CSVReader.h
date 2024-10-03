#pragma once    //to include the header only once
#include "OrderBookEntry.h"
#include<vector>
#include<string>

// Being a header we will only put the function specification/decalration only, the rest of the implementation will be put int the cpp file.
class CSVReader
{
    public:
        CSVReader();
        static std::vector<OrderBookEntry> readCSV(std::string csvFile);    //reading each line in the file
        /* This function will be a stateless fiunction i.e, it doesn't rely on creating anything beforehand
        static function are those functions which can be created without even creation of an object */
        static std::vector<std::string> tokenise(std::string csvLine,char seperator);
        static OrderBookEntry stringToOBE(std::string price,std::string amount,std::string timestamp,std::string product,OrderBookType orderType);
        
    private:
        static OrderBookEntry stringToOBE(std::vector<std::string> strings);
};