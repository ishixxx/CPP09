#include "RPN.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " \"<RPN expression>\"" << std::endl;
        return 1;
    }

    RPN rpn;
    try {
        rpn.evaluate(argv[1]);
    } catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

//Example usage:
// ./RPN "3 4 + 2 * 7 /" must output 2
// ./RPN "5 1 2 + 4 * + 3 -" must output 14
// ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +" must output 42
// ./RPN  "7 7 * 7 -" must output 42
// ./RPN "1 2 * 2 / 2 * 2 4 - +" must output 0
// ./RPN "1 2 + 3 4 + *" must output 21
// ./RPN "42" must output 42
// ./RPN "1 2 +" must output 3

// ./RPN "1 2" must output Error: The RPN expression is invalid
// ./RPN "(1 + 1)" must output Error: Invalid token