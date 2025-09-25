#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {

}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other) {
    *this = other;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other) {
    if (this != &other) {
        // Copy member variables here if there are any
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {

}

void BitcoinExchange::parseDatabase(std::string const &filename) {}

void BitcoinExchange::parseInput(std::string const &filename) {}

void BitcoinExchange::parseLine(std::string line) {
    trim(line);
    if (line.empty()) {
        return; // Skip empty lines
    }