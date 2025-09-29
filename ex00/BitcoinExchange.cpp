#include "BitcoinExchange.hpp"

//-------------------------------Constructors - Destructors--------------------------------
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

//-------------------------------------utils-------------------------------------------

void BitcoinExchange::trim(std::string &s) {
     // trim gauche
    std::string::iterator it = s.begin();
    while (it != s.end() && isspace(*it)) ++it;
    s.erase(s.begin(), it);

    // trim droite
    if (!s.empty()) {
        std::string::reverse_iterator rit = s.rbegin();
        while (rit != s.rend() && isspace(*rit)) ++rit;
        s.erase(rit.base(), s.end());
    }
}

//-------------------------------Members functions--------------------------------

void BitcoinExchange::parseDatabase(std::string const &filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Could not open database file");
    }

    std::string line;
    if (std::getline(file, line)) {
        // Skip header line
    }
    while (std::getline(file, line)) {
        size_t sep = line.find(',');
        if (sep == std::string::npos) {
            continue; // Skip malformed lines
        }
        std::string date = line.substr(0, sep);
        std::string rateStr = line.substr(sep + 1);
        trim(date);
        trim(rateStr);
        float rate = std::atof(rateStr.c_str());
        database[date] = rate;
    }
    file.close();
}

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
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }
    std::string year = date.substr(0, 4);
    std::string month = date.substr(5, 2);
    std::string day = date.substr(8, 2);
    
    for (size_t i = 0; i < year.length(); ++i) {
        if (!isdigit(year[i])) 
        return false;
    }
    for (size_t i = 0; i < month.length(); ++i) {
        if (!isdigit(month[i])) 
        return false;
    }
    for (size_t i = 0; i < day.length(); ++i) {
        if (!isdigit(day[i]))
        return false;
    }
    
    int y = std::atoi(year.c_str());
    int m = std::atoi(month.c_str());
    int d = std::atoi(day.c_str());
    
    if (m < 1 || m > 12 || d < 1 || d > 31) {
        return false;
    }
    return true;
    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) {
        return false;
    }
    if (m == 2) {
        bool isLeap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        if (d > 29 || (d == 29 && !isLeap)) {
            return false;
        }
    }
    return true;
}

bool BitcoinExchange::isValueValid(float value) {
    if (value < 0) {
        std::cerr << "Error: not a positive number." << std::endl;
        return false;
    }
    if (value > 1000) {
        std::cerr << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
}

float BitcoinExchange::getExchangeRate(std::string const &date) {
    std::map<std::string, float>::iterator it = database.lower_bound(date);
    if (it != database.end() && it->first == date) {
        return it->second;
    }
    if (it == database.begin()) {
        std::cerr << "Error: no exchange rate available for date " << date << std::endl;
        return 0.0f;
    }
    --it; // Prendre la date la plus proche avant la date donnée
    return it->second;
}

void BitcoinExchange::processInput(std::string const &filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Could not open input file");
    }
    std::string line;
    while (std::getline(file, line)) {
        parseLine(line);
    }
    file.close();
}