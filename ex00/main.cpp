#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./btc <input_file>" << std::endl;
        return 1;
    }

    try {
        BitcoinExchange btc;
        btc.parseDatabase("data.csv");
        btc.processInput(argv[1]);
    } 
    catch (const std::exception &e) {
        std::cerr << "Error initializing BitcoinExchange: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;

}