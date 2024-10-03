/*
    This particular program tokenises the lines of CSV files into distinct tokens.
*/
#include<iostream>
#include<vector>
#include<string>
#include<fstream>   //fstream stands for "file stream"

std::vector<std::string> tokenise(std::string csvLine,char seperator)
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
int main()
{
    // std::vector<std::string> tokens;
    // std::string s="thing1,thing2,thing3";

    // tokens=tokenise(s,','); //passing the string to be tokenised and the seperator by which the values are seperated
    // for(std::string& token:tokens)
    //     std::cout<<token<<std::endl;

    std::ifstream csvFile{"CryptoTrade.csv"};    //std::ifstream(input file stream) is a class
    // The above line opens the file passed in the argument
    std:: string line;
    std::vector<std::string> tokens;
    if(csvFile.is_open()) //checks whether the CSV file is open or not
    {
        std::cout<<"File Opened"<<std::endl;
        while(std::getline(csvFile,line))
        {
            /* getline() is used to read a line from the file.When the getline() function reaches the end of the file then it returns false. Then the loop gets stopped.*/
            //std::getline(csvFile,line); /*where you are getting line from and where you writing the line to. This line reads only one line form the CSV file. If we want to have more lines then, we can keep calling it or use a loop for this purpose.*/
            std::cout<<"Read line: "<<line<<std::endl;
            tokens=tokenise(line,',');  //tokenises the line into values seperated by ','(comma))
            if(tokens.size()!=5)// incorrect tokeninsation
            {
                std::cout<<"Incorrect Tokenisation"<<std::endl;
                continue;
            }

            //we have 5 tokens in all: string, string ,string, double, double
            // all these are zero-based index

            //exception handling
            try
            {
                /* At first this part of try-catch will be executed, if this contains some errors then, the catch block will be executed */
                double price=std::stod(tokens[3]);  //std::stod() converts string to double
                //the program will stop if the stod() is unable to converet the string to a double
                double amount=std::stod(tokens[4]);
            }
            catch(const std::exception& e)  //gets executed when there is an exception in the try block
            {
                std::cout<<"Bad float !!"<<std::endl;
                continue;   //goes to the next iteration
            }
            
            
            for(std::string& t:tokens)  //printing out the tokens
                std::cout<<t<<std::endl;
        }
        csvFile.close();    //though the file gets automatically closed still we should close the opened file as a precaution
    }
    else    
        std::cout<<"Could not open file"<<std::endl;
    
    return 0;
}