# cs-303--Extra-Credit

# Infix Expression Evaluator

This project provides a C++ class, `Evaluator`, that can parse and evaluate infix expressions. It supports a variety of operators, including arithmetic, logical, and comparison operators, and handles operator precedence and parentheses.

## Files Included

* **Evaluator.h:** This header file contains the declaration of the `Evaluator` class.
* **Evaluator.cpp:** This source file contains the implementation of the `Evaluator` class.
* **main.cpp:** This file contains the `main` function that demonstrates the usage of the `Evaluator` class with test cases and an interactive mode.


## Features

* **Supports Infix Notation:** Evaluates expressions written in the standard infix notation (e.g., `1 + 2 * 3`).
* **Operator Precedence:** Correctly handles different operator precedences (e.g., multiplication before addition).
* **Parentheses:** Supports the use of parentheses to override operator precedence (e.g., `(1 + 2) * 3`).
* **Arithmetic Operators:** `+` (addition), `-` (subtraction - both binary and unary), `*` (multiplication), `/` (division), `%` (modulo), `^` (exponentiation).
* **Comparison Operators:** `>` (greater than), `>=` (greater than or equal to), `<` (less than), `<=` (less than or equal to), `==` (equal to), `!=` (not equal to).
* **Logical Operators:** `&&` (logical AND), `||` (logical OR), `!` (logical NOT).
* **Increment/Decrement Operators:** `++` (pre-increment), `--` (pre-decrement). Note that these operators modify the operand directly in a typical programming context. In this evaluator, they are treated as unary operators that return the incremented/decremented value.
* **Error Handling:** Includes basic error checking for invalid expressions, such as mismatched parentheses, division by zero, consecutive operators or operands, and invalid characters.
* **Interactive Mode:** Allows users to enter and evaluate expressions directly from the command line.



