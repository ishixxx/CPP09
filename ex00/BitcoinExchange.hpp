#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <stdexcept>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cctype>

class BitcoinExchange {
    public:
        BitcoinExchange();
        BitcoinExchange(BitcoinExchange const &other);
        BitcoinExchange &operator=(BitcoinExchange const &other);
        ~BitcoinExchange();

    private:
        void trim(std::string &s);
        void parseDatabase(std::string const &filename);
        void parseInput(std::string const &filename);
        void parseLine(std::string line); //on modifie la ligne si il y a des espaces par exemples et si on veut la traiter malgré le séparateur 
};

#endif // BITCOINEXCHANGE_HPP