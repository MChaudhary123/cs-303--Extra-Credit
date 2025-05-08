#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <string>
#include <stack>
#include <map>
#include <stdexcept>

/**
 * The Evaluator class provides functionality to parse and evaluate infix expressions.
 * It supports various operators with different precedences, handles parentheses,
 * and provides error checking for invalid expressions.
 */
class Evaluator {
public:
    /**
     * Constructor for the Evaluator class.
     * Initializes operator precedence and sets up the evaluator.
     * Time Complexity: O(1) - Constant time for initializing maps.
     */
    Evaluator();

    /**
     * Evaluates the given infix expression and returns the result.
     *
     * @param expression The infix expression to evaluate.
     * @return The result of the expression evaluation.
     * @throws std::runtime_error if the expression is invalid.
     *
     * Time Complexity: O(n) where n is the length of the expression.
     * Each character is processed once.
     */
    int eval(const std::string& expression);

private:
    // Maps to store operator precedence and information
    std::map<std::string, int> precedence;         // Stores operator precedence
    std::map<std::string, bool> isBinary; // Indicates if an operator is binary

    /**
     * Tokenizes the expression string, removing spaces and handling multi-character operators.
     *
     * @param expression The original expression string.
     * @return A cleaned expression string ready for parsing.
     *
     * Time Complexity: O(n) where n is the length of the expression.
     */
    std::string tokenize(const std::string& expression);

    /**
     * Checks if a character is a valid operator.
     *
     * @param c The character to check.
     * @return True if the character is an operator, false otherwise.
     *
     * Time Complexity: O(1) - Constant time check.
     */
    bool isOperator(char c) const;

    /**
     * Performs the operation between two operands based on the operator.
     *
     * @param op The operator to apply.
     * @param b The right operand.
     * @param a The left operand (not used for unary operators).
     * @return The result of the operation.
     * @throws std::runtime_error if an unsupported operator is provided.
     *
     * Time Complexity: O(1) - Constant time operations.
     */
    int performOperation(const std::string& op, int b, int a = 0);

    /**
     * Validates the expression for common syntax errors.
     *
     * @param expression The expression to validate.
     * @throws std::runtime_error with a descriptive error message if the expression is invalid.
     *
     * Time Complexity: O(n) where n is the length of the expression.
     */
    void validateExpression(const std::string& expression);
};

#endif // EVALUATOR_H
