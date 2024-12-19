#include "expression_evaluator.h"
#include <iostream>
#include <string>

int main() {
    std::string expression;
    std::cout << "Enter an expression:" << std::endl;
    std::getline(std::cin, expression);
    try {
        double result = ExpressionEvaluator::eval(expression);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::runtime_error &e) {
        std::cout << "Error" << std::endl;
    }
    return 0;
}
