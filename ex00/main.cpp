#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./btc <input_file>" << std::endl;
        return 1;
    }

    try {
        BitcoinExchange btc(argv[1]);
        btc.processInput();
    } 
    catch (const std::exception &e) {
        std::cerr << "Error initializing BitcoinExchange: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;

}