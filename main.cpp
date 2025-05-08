
#include "Evaluator.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

/**
 * Main function to demonstrate the Evaluator class.
 *
 * Time Complexity: O(n*m) where n is the number of test expressions
 * and m is the average length of each expression.
 */
int main() {
    Evaluator eval;

    // Test expressions from the requirements
    std::vector<std::string> testExpressions = {
        "1+2*3",             // 7
        "2+2^2*3",           // 14
        "1==2",              // 0 (false)
        "1+3 > 2",           // 1 (true)
        "(4>=4) && 0",       // 0 (false)
        "(1+2)*3",           // 9
        "+++2-5*(3^2)"       // -41
    };

    std::cout << "=== Testing expressions from requirements ===" << std::endl << std::endl;
    std::cout << std::left << std::setw(20) << "Expression" << "Result" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    for (const auto& expr : testExpressions) {
        try {
            int result = eval.eval(expr);
            std::cout << std::left << std::setw(20) << expr << result;

            // Show boolean interpretation for comparison results
            if (expr.find("==") != std::string::npos ||
                expr.find("!=") != std::string::npos ||
                expr.find(">") != std::string::npos ||
                expr.find("<") != std::string::npos ||
                expr.find("&&") != std::string::npos ||
                expr.find("||") != std::string::npos) {
                std::cout << " // " << (result ? "true" : "false") << " if the type is bool";
            }

            std::cout << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << std::left << std::setw(20) << expr << "Error: " << e.what() << std::endl;
        }
    }

    std::cout << std::endl << "=== Testing error cases ===" << std::endl << std::endl;
    std::cout << std::left << std::setw(20) << "Expression" << "Error Message" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    // Test error cases from the requirements
    std::vector<std::string> errorExpressions = {
        ")+2",                 // Expression can't start with a closing parenthesis
        "<3+2",                 // Expression can't start with a binary operator
        "3&&&&5",               // Two binary operators in a row
        "15+3 2",               // Two operands in a row
        "10+ ++<3",             // A unary operand can't be followed by a binary operator
        "1/0"                    // Division by zero
    };

    for (const auto& expr : errorExpressions) {
        try {
            int result = eval.eval(expr);
            std::cout << std::left << std::setw(20) << expr << result << " (No error detected)" << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << std::left << std::setw(20) << expr << e.what() << std::endl;
        }
    }

    std::cout << std::endl << "=== Interactive Mode ===" << std::endl;
    std::cout << "Enter expressions to evaluate (type 'exit' to quit)" << std::endl;

    std::string userExpr;
    while (true) {
        std::cout << std::endl << "Expression: ";
        std::getline(std::cin, userExpr);

        if (userExpr == "exit") {
            break;
        }

        try {
            int result = eval.eval(userExpr);
            std::cout << "Result: " << result;

            // Show boolean interpretation if result is 0 or 1
            if (result == 0 || result == 1) {
                std::cout << " (" << (result ? "true" : "false") << " if the type is bool)";
            }

            std::cout << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
