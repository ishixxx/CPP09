#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cctype>
#include <cstdlib>
#include <limits>
#include <cmath>

//The RPN stack works the same as a normal stack, in other words, the first number which is pushed onto the stack will be the first one to be popped off (LIFO).
//So we add numbers to the stack until we encounter an operator, at which point we pop the top two numbers off the stack, apply the operator to them, and push the result back onto the stack.
//The final result will be the only number left on the stack after the entire expression has been processed.
//Here RPN only accepts integers and the operators +, -, *, /. 
//evaluate() method takes a string expression as input, processes it token by token, and performs the necessary calculations using a stack to store intermediate results.
//processToken() method handles each token, determining if it's a number or an operator and acting accordingly.
//clearStack() method is used to reset the stack in case of an error during evaluation.

class RPN {
    public:
        RPN();
        RPN(RPN const & src);
        RPN & operator=(RPN const & rhs);
        ~RPN();

        void evaluate(std::string expression);
    private:
        std::stack<int> _stack;

        bool isOperator(char c);
        int performOperation(int a, int b, char op);
        void processToken(const std::string & token);
        void clearStack();
};

#endif // RPN_HPP