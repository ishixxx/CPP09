#include "RPN.hpp"

//--------------------------Constructors & Destructors--------------------------//

RPN::RPN() {}

RPN::RPN(RPN const & src) {
    *this = src;
}

RPN & RPN::operator=(RPN const & rhs) {
    if (this != &rhs) {
        this->_stack = rhs._stack;
    }
    return *this;
}

RPN::~RPN() {}

//--------------------------Private Methods--------------------------//

bool RPN::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int RPN::performOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw std::runtime_error("Error: Division by zero");
            return a / b;
        default: throw std::runtime_error("Error: Unknown operator");
    }
}

void RPN::processToken(const std::string & token) {
    // Check if there is at least 2 number for 1 operator
    if (token.length() == 1 && isOperator(token[0])) {
        if (_stack.size() < 2) {
            clearStack();
            throw std::runtime_error("Error: Insufficient values in expression");
        }
        int b = _stack.top(); _stack.pop();
        int a = _stack.top(); _stack.pop();
        int result = performOperation(a, b, token[0]);
        _stack.push(result);
    } else {
        char *end;
        long value = std::strtol(token.c_str(), &end, 10);
        if (*end != '\0' || value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max()) {
            clearStack();
            throw std::runtime_error("Error: Invalid token '" + token + "'");
        }
        _stack.push(static_cast<int>(value));
    }
}

void RPN::clearStack() {
    while (!_stack.empty()) {
        _stack.pop();
    }
}

//--------------------------Public Methods--------------------------//

void RPN::evaluate(std::string expression) {
    std::istringstream iss(expression);
    std::string token;

    bool hasOperations = false;
    
    // Process each token in the expression, so each number has a space between them and a according number of operators
    while (iss >> token) {
        // Check if there's at least one operator in the expression
        if (token.length() == 1 && isOperator(token[0])) {
            hasOperations = true;
        }
        processToken(token);
    }
    
    if (_stack.empty()) {
        throw std::runtime_error("Error: The user input is empty");
    }
    
    if (!hasOperations) {
        clearStack();
        throw std::runtime_error("Error: You need at least one operator");
    }
    
    if (_stack.size() != 1) {
        clearStack();
        throw std::runtime_error("Error: The user input has too many values");
    }

    std::cout << "Result: " << _stack.top() << std::endl;
    _stack.pop();
}