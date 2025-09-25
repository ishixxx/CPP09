#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
    parseDatabase("data.csv");
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other) {
    database = other.database;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other) {
    if (this != &other) {
        database = other.database;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::parseDatabase(std::string const &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open database file");
    }

    std::string line;
    while (std::getline(file, line)) {
        parseLine(line);
    }
    file.close();
}

void BitcoinExchange::parseInput(std::string const &filename) {}

void BitcoinExchange::parseLine(std::string line) {
    trim(line);
    if (line.empty()) {
        return; // Skip empty lines
    }
    size_t sep = line.find('|');
    if (sep == std::string::npos) {
        std::cerr << "Error: bad input => " << line << std::endl;
        return;
    }

    std::string date = line.substr(0, sep);
    trim(date);
    std::string valueStr = line.substr(sep + 1);
    trim(valueStr);

    if (!isDateValid(date)) {
        std::cerr << "Error: bad input => " << line << std::endl;
        return;
    }

    if(!isValueValid(std::atof(valueStr.c_str()))) {
        std::cerr << "Error: bad input => " << line << std::endl;
        return;
    }

    float value = std::atof(valueStr.c_str());
    float rate = getExchangeRate(date);
    std::cout << date << " => " << value << " = " << value * rate << std::endl;
}

bool BitcoinExchange::isDateValid(std::string const &date) {
    
}

bool BitcoinExchange::isValueValid(float value) {
}

float BitcoinExchange::getExchangeRate(std::string const &date) {
    // Implement logic to get exchange rate for a specific date
    return 0.0f;
}