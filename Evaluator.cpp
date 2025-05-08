

#include "Evaluator.h"
#include <iostream>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <stack>
#include <map>
#include <stdexcept>

Evaluator::Evaluator() {
    // Initialize operator precedence according to requirements
    // Higher number = higher precedence
    precedence["!"] = 8;
    precedence["++"] = 8;
    precedence["--"] = 8;
    precedence["u-"] = 8;  // Unary minus
    precedence["^"] = 7;
    precedence["*"] = 6;
    precedence["/"] = 6;
    precedence["%"] = 6;
    precedence["+"] = 5;
    precedence["b-"] = 5;  // Binary minus
    precedence[">"] = 4;
    precedence[">="] = 4;
    precedence["<"] = 4;
    precedence["<="] = 4;
    precedence["=="] = 3;
    precedence["!="] = 3;
    precedence["&&"] = 2;
    precedence["||"] = 1;

    // Initialize binary operator flags
    isBinary["^"] = true;
    isBinary["*"] = true;
    isBinary["/"] = true;
    isBinary["%"] = true;
    isBinary["+"] = true;
    isBinary["b-"] = true;
    isBinary[">"] = true;
    isBinary[">="] = true;
    isBinary["<"] = true;
    isBinary["<="] = true;
    isBinary["=="] = true;
    isBinary["!="] = true;
    isBinary["&&"] = true;
    isBinary["||"] = true;

    // Unary operators
    isBinary["!"] = false;
    isBinary["++"] = false;
    isBinary["--"] = false;
    isBinary["u-"] = false;
}

std::string Evaluator::tokenize(const std::string& expression) {
    std::string result;

    // Remove all spaces
    for (char c : expression) {
        if (!std::isspace(c)) {
            result += c;
        }
    }

    return result;
}

bool Evaluator::isOperator(char c) const {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
            c == '^' || c == '!' || c == '>' || c == '<' || c == '=' ||
            c == '&' || c == '|');
}

int Evaluator::performOperation(const std::string& op, int b, int a) {
    // For binary operators
    if (op == "+") return a + b;
    if (op == "b-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) throw std::runtime_error("Division by zero @ char " + std::to_string(op.length()));
        return a / b;
    }
    if (op == "%") {
        if (b == 0) throw std::runtime_error("Modulo by zero @ char " + std::to_string(op.length()));
        return a % b;
    }
    if (op == "^") return static_cast<int>(pow(a, b));
    if (op == ">") return a > b;
    if (op == ">=") return a >= b;
    if (op == "<") return a < b;
    if (op == "<=") return a <= b;
    if (op == "==") return a == b;
    if (op == "!=") return a != b;
    if (op == "&&") return a && b;
    if (op == "||") return a || b;

    // For unary operators
    if (op == "!") return !b;
    if (op == "++") return b + 1;
    if (op == "--") return b - 1;
    if (op == "u-") return -b;

    throw std::runtime_error("Unsupported operator: " + op);
}

void Evaluator::validateExpression(const std::string& expression) {
    if (expression.empty()) {
        throw std::runtime_error("Expression is empty");
    }

    // Check if expression starts with a closing parenthesis or binary operator
    if (expression[0] == ')') {
        throw std::runtime_error("Expression can't start with a closing parenthesis @ char: 0");
    }

    if (expression[0] == '*' || expression[0] == '/' || expression[0] == '%' ||
        expression[0] == '^' || expression[0] == '>' || expression[0] == '<' ||
        expression[0] == '=' || expression[0] == '&' || expression[0] == '|') {
        throw std::runtime_error("Expression can't start with a binary operator @ char: 0");
    }

    // Check for consecutive binary operators, operands, or mismatched parentheses
    int openParenCount = 0;
    bool lastWasOperand = false;
    bool lastWasOperator = false;
    char prevChar = '\0';

    for (size_t i = 0; i < expression.length(); i++) {
        char c = expression[i];

        // Check for opening and closing parentheses
        if (c == '(') {
            openParenCount++;
            lastWasOperand = false;
            lastWasOperator = false;
            prevChar = c;
        }
        else if (c == ')') {
            openParenCount--;
            if (openParenCount < 0) {
                throw std::runtime_error("Mismatched parentheses - too many closing @ char: " + std::to_string(i));
            }
            lastWasOperand = true;
            lastWasOperator = false;
            prevChar = c;
        }
        // Check for operands (digits)
        else if (std::isdigit(c)) {
            if (lastWasOperand && prevChar != '(' && !std::isdigit(prevChar)) {
                throw std::runtime_error("Two operands in a row @ char " + std::to_string(i));
            }
            lastWasOperand = true;
            lastWasOperator = false;
            prevChar = c;
        }
        // Check for operators
        else if (isOperator(c)) {
            // Handle multi-char operators
            if (c == '&' && i + 1 < expression.length() && expression[i + 1] == '&') {
                // Skip the next '&'
                i++;
            }
            else if (c == '|' && i + 1 < expression.length() && expression[i + 1] == '|') {
                // Skip the next '|'
                i++;
            }
            else if (c == '=' && i + 1 < expression.length() && expression[i + 1] == '=') {
                // Skip the next '='
                i++;
            }
            else if (c == '!' && i + 1 < expression.length() && expression[i + 1] == '=') {
                // Skip the next '='
                i++;
            }
            else if (c == '>' && i + 1 < expression.length() && expression[i + 1] == '=') {
                // Skip the next '='
                i++;
            }
            else if (c == '<' && i + 1 < expression.length() && expression[i + 1] == '=') {
                // Skip the next '='
                i++;
            }
            else if (c == '+' && i + 1 < expression.length() && expression[i + 1] == '+') {
                // Skip the next '+'
                i++;
            }
            else if (c == '-' && i + 1 < expression.length() && expression[i + 1] == '-') {
                // Skip the next '-'
                i++;
            }

            // Check for consecutive binary operators
            if (lastWasOperator && c != '+' && c != '-' && c != '!') {
                throw std::runtime_error("Two binary operators in a row @ char " + std::to_string(i));
            }

            // Check for unary operator followed by binary operator
            if ((prevChar == '+' && c == '<') || (prevChar == '+' && c == '*') ||
                (prevChar == '-' && c == '<') || (prevChar == '-' && c == '*')) {
                throw std::runtime_error("A unary operand can't be followed by a binary operator @ char " + std::to_string(i));
            }

            lastWasOperator = true;
            lastWasOperand = false;
            prevChar = c;
        }
        else {
            throw std::runtime_error("Invalid character in expression: " + std::string(1, c) + " @ char " + std::to_string(i));
        }
    }

    // Check for unclosed parentheses
    if (openParenCount > 0) {
        throw std::runtime_error("Mismatched parentheses - unclosed parentheses");
    }
}

int Evaluator::eval(const std::string& expression) {
    // Tokenize and clean the expression
    std::string tokenized = tokenize(expression);

    // Validate the expression
    validateExpression(tokenized);

    std::stack<int> values;         // Stack to store operand values
    std::stack<std::string> ops; // Stack to store operators

    for (size_t i = 0; i < tokenized.length(); i++) {
        // Skip spaces (though they should have been removed by tokenize)
        if (tokenized[i] == ' ') {
            continue;
        }

        // If current character is an opening bracket, push it to 'ops'
        else if (tokenized[i] == '(') {
            ops.push("(");
        }

        // If current character is a digit, extract the full number
        else if (isdigit(tokenized[i])) {
            int val = 0;
            while (i < tokenized.length() && isdigit(tokenized[i])) {
                val = (val * 10) + (tokenized[i] - '0');
                i++;
            }
            i--; // Move back one position since for loop will increment
            values.push(val);
        }

        // If current character is a closing bracket, solve the entire bracket
        else if (tokenized[i] == ')') {
            while (!ops.empty() && ops.top() != "(") {
                std::string op = ops.top();
                ops.pop();

                if (isBinary[op]) {
                    // Binary operation needs two operands
                    if (values.size() < 2) {
                        throw std::runtime_error("Invalid expression: Not enough operands for binary operator " + op);
                    }

                    int val2 = values.top();
                    values.pop();

                    int val1 = values.top();
                    values.pop();

                    values.push(performOperation(op, val2, val1));
                }
                else {
                    // Unary operation needs one operand
                    if (values.empty()) {
                        throw std::runtime_error("Invalid expression: Not enough operands for unary operator " + op);
                    }

                    int val = values.top();
                    values.pop();

                    values.push(performOperation(op, val));
                }
            }

            // Remove the opening bracket
            if (!ops.empty()) {
                ops.pop();
            }
        }

        // If current character is an operator
        else if (isOperator(tokenized[i])) {
            std::string currentOp;

            // Handle multi-character operators
            if (tokenized[i] == '+') {
                if (i + 1 < tokenized.length() && tokenized[i + 1] == '+') {
                    currentOp = "++";
                    i++;
                }
                else {
                    currentOp = "+";
                }
            }
            else if (tokenized[i] == '-') {
                if (i + 1 < tokenized.length() && tokenized[i + 1] == '-') {
                    currentOp = "--";
                    i++;
                }
                else {
                    // Check if this is a unary minus (negation) or binary minus
                    if (i == 0 || tokenized[i - 1] == '(' || isOperator(tokenized[i - 1])) {
                        currentOp = "u-";  // unary minus
                    }
                    else {
                        currentOp = "b-";  // binary minus
                    }
                }
            }
            else if (tokenized[i] == '=') {
                if (i + 1 < tokenized.length() && tokenized[i + 1] == '=') {
                    currentOp = "==";
                    i++;
                }
                else {
                    throw std::runtime_error("Invalid operator: single '=' is not supported @ char " + std::to_string(i));
                }
            }
            else if (tokenized[i] == '!') {
                if (i + 1 < tokenized.length() && tokenized[i + 1] == '=') {
                    currentOp = "!=";
                    i++;
                }
                else {
                    currentOp = "!";
                }
            }
            else if (tokenized[i] == '>') {
                if (i + 1 < tokenized.length() && tokenized[i + 1] == '=') {
                    currentOp = ">=";
                    i++;
                }
                else {
                    currentOp = ">";
                    }
                                }
                                else if (tokenized[i] == '<') {
                                    if (i + 1 < tokenized.length() && tokenized[i + 1] == '=') {
                                        currentOp = "<=";
                                        i++;
                                    }
                                    else {
                                        currentOp = "<";
                                    }
                                }
                                else if (tokenized[i] == '&') {
                                    if (i + 1 < tokenized.length() && tokenized[i + 1] == '&') {
                                        currentOp = "&&";
                                        i++;
                                    }
                                    else {
                                        throw std::runtime_error("Invalid operator: single '&' is not supported @ char " + std::to_string(i));
                                    }
                                }
                                else if (tokenized[i] == '|') {
                                    if (i + 1 < tokenized.length() && tokenized[i + 1] == '|') {
                                        currentOp = "||";
                                        i++;
                                    }
                                    else {
                                        throw std::runtime_error("Invalid operator: single '|' is not supported @ char " + std::to_string(i));
                                    }
                                }
                                else {
                                    // Single character operators
                                    currentOp = std::string(1, tokenized[i]);
                                }

                                // Process operators according to precedence
                                while (!ops.empty() && ops.top() != "(" &&
                                       precedence[ops.top()] >= precedence[currentOp]) {
                                    std::string op = ops.top();
                                    ops.pop();

                                    if (isBinary[op]) {
                                        if (values.size() < 2) {
                                            throw std::runtime_error("Not enough operands for binary operator: " + op);
                                        }
                                        int val2 = values.top();
                                        values.pop();

                                        int val1 = values.top();
                                        values.pop();

                                        values.push(performOperation(op, val2, val1));
                                    }
                                    else {
                                        if (values.empty()) {
                                            throw std::runtime_error("Not enough operands for unary operator: " + op);
                                        }
                                        int val = values.top();
                                        values.pop();

                                        values.push(performOperation(op, val));
                                    }
                                }

                                // Push current operator to stack
                                ops.push(currentOp);
                            }
                        }

                        // Process all remaining operators in the stack
                        while (!ops.empty()) {
                            std::string op = ops.top();
                            ops.pop();

                            if (op == "(") {
                                throw std::runtime_error("Mismatched parentheses - unclosed parenthesis");
                            }

                            if (isBinary[op]) {
                                if (values.size() < 2) {
                                    throw std::runtime_error("Not enough operands for binary operator: " + op);
                                }
                                int val2 = values.top();
                                values.pop();

                                int val1 = values.top();
                                values.pop();

                                values.push(performOperation(op, val2, val1));
                            }
                            else {
                                if (values.empty()) {
                                    throw std::runtime_error("Not enough operands for unary operator: " + op);
                                }
                                int val = values.top();
                                values.pop();

                                values.push(performOperation(op, val));
                            }
                        }

                        // Final result should be on top of the values stack
                        if (values.size() != 1) {
                            throw std::runtime_error("Invalid expression - too many values");
                        }

                        return values.top();
                    }
