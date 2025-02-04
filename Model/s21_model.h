/**
 * @file s21_model.h
 * @brief Header file containing the declaration of the Model abstraction in the
 * MVC pattern.
 */

#ifndef SMARTCALC_MODEL_S21_MODEL_H
#define SMARTCALC_MODEL_S21_MODEL_H

#include <map>
#include <stack>
#include <string>

namespace s21 {

/**
 * @class Model
 *
 * @brief Represents the Model in the MVC pattern for mathematical calculations.
 *
 * The Model class is responsible for processing mathematical expressions using
 * Reverse Polish Notation (RPN). It accepts an expression, validates it, and
 * performs the calculation. If an error occurs during processing, the model
 * sets an error state.
 */
class Model {
 public:
  Model() noexcept;
  ~Model() = default;

 public:
  /**
   * @brief Sets the input mathematical expression after validating and
   * processing it.
   *
   * @param[in] input The mathematical expression to be set.
   * @throws std::invalid_argument if the input is invalid.
   */
  void SetInput(const std::string& input);

  /**
   * @brief Sets the value of 'x_'.
   *
   * @param[in] x The value to set for the variable 'x'.
   */
  void SetX(const double x) noexcept;

  /**
   * @brief GetResult function performs the main steps for processing the
   * mathematical expression.
   *
   * This method calls ToRpn to convert the infix expression to postfix notation
   * and then Calculate to evaluate the expression. If any errors occur during
   * the process, an exception is thrown.
   *
   * @return The result of the evaluated expression.
   * @throws std::exception if an error occurs during the processing of the
   * expression.
   */
  double CalculateMathExpression();

 private:
  /**
   * @struct Token
   * @brief Represents a token in the mathematical expression.
   *
   * It holds the token as a string and an priority value.
   */
  struct Token {
    std::string value;
    int priority;
  };

  /**
   * @brief Validates the input mathematical expression.
   *
   * This function checks the validity of the input mathematical expression
   * based on the following criteria:
   *
   * - The input should not be empty and its size should be less than 256
   * characters.
   * - The number of opening '(' and closing ')' parentheses should be equal.
   * - The first character should not be '*' or '/'.
   * - The expression should contain at least one digit or the variable 'x'.
   *
   * @param input The input mathematical expression to be validated.
   *
   * @throw std::invalid_argument if the input expression is invalid.
   */
  void ValidateInput(const std::string& input);

  /**
   * @brief Replaces 'E' notation in the input string with '*10^' and validates
   * its form.
   *
   * This function is used to replace 'E' notation with a format suitable for
   * mathematical expressions.
   *
   * @throw std::invalid_argument if the scientific notation is not valid.
   */
  void ReplaceScientificNotation();

  /**
   * @brief Converts the infix expression to postfix (Reverse Polish Notation).
   *
   * This function processes the infix expression stored in the 'expression_'
   * member variable and converts it to postfix notation, storing the result in
   * the 'postfix_' member variable. It uses the Shunting Yard algorithm for
   * this conversion.
   */
  void ToPostfix();

  /**
   * @brief Gets the value of the top token in the stack.
   *
   * @param[in] token The stack containing tokens.
   * @return The value of the top token.
   */
  std::string GetTokenValue(const std::stack<Token>& token);

  /**
   * @brief Gets the priority of the top token in the stack.
   *
   * @param[in] token The stack containing tokens.
   * @return The priority of the top token.
   */
  int GetTokenPriority(const std::stack<Token>& token);

  /**
   * @brief Pushes a number to the postfix expression stack.
   *
   * Validates the input and pushes the number along with a priority of 0
   * to the postfix expression stack.
   *
   * @param number The number to push to the postfix expression.
   * @throws std::invalid_argument if the input is invalid.
   */
  void PushNumberToPostfix(std::string& number);

  /**
   * @brief Pushes an operation to the operators stack.
   *
   * Clears the input operation string and pushes it along with its priority
   * to the provided stack.
   *
   * @param[in] stack The stack to push the operation onto.
   * @param[in] operation The operation to push onto the stack.
   *                  Accepts a string representation of the operation.
   */
  void PushOperationToOperators(std::stack<Token>& stack,
                                std::string& operation);

  /**
   * @brief Pushes a character operation to the operators stack.
   *
   * Pushes a character operation along with its priority to the provided stack.
   *
   * @param[in] stack The stack to push the operation onto.
   * @param[in] operation The character operation to push onto the stack.
   */
  void PushOperationToOperators(std::stack<Token>& stack, char operation);

  /**
   * @brief Throws an exception if the count of dots in the current number is
   * greater than 1.
   *
   * This function checks the dot count in the 'cur_num' variable and throws an
   * exception if the count is greater than 1, indicating an invalid double
   * value.
   */
  void ThrowInvalidDouble();

  /**
   * @brief Checks if the given character is an arithmetic operator.
   *
   * @param c The character to check.
   * @return True if the character is an operator, otherwise false.
   */
  bool IsOperator(char c) noexcept;

  /**
   * @brief Returns the priority of the given arithmetic operation.
   *
   * @param operation The arithmetic operation to determine priority.
   * @return The priority of the operation.
   */
  int SetTokenPriority(const std::string& operation);

  /**
   * @brief Checks if the current operator is a unary operator and operates
   * accordingly.
   *
   * This function checks if the current operator is a unary operator and
   * operates accordingly, modifying the operator 'c' to '~' for the unary
   * minus. It also handles the special case where a unary plus is encountered.
   *
   * @param[in] it Iterator pointing to the current character in the input
   * expression.
   * @param[in, out] c Reference to the current operator character.
   * @return True if the current operator is a unary plus, otherwise false.
   */
  bool IsUnary(std::string::iterator it);

  /**
   * @brief Reverses the order of tokens in the postfix stack.
   *
   * This function reverses the order of tokens in the postfix stack by using an
   * auxiliary stack.
   */
  void ReverseStack();

  /**
   * @brief Calculates the result of the expression using the postfix notation.
   *
   * This function iterates through the postfix stack, performs calculations
   * based on the operators and operands encountered, and updates the result_
   * variable.
   */
  void Calculate();

  /**
   * @brief Calculates the result of arithmetic operations and updates the
   * calculation stack.
   *
   * This function takes two operands and an operator, performs the
   * corresponding arithmetic operation, and pushes the result onto the
   * calculation stack.
   *
   * @param[in] num1 The first operand.
   * @param[in] num2 The second operand.
   * @param[in] operation The arithmetic operator.
   */
  void CalculateArithmetic(double num1, double num2, char operation) noexcept;

  /**
   * @brief Calculates the result of trigonometric and other mathematical
   * operations and updates the calculation stack.
   *
   * This function takes a single operand and a string representing the
   * mathematical operation, performs the corresponding operation, and pushes
   * the result onto the calculation stack.
   *
   * @param[in] num The operand for the mathematical operation.
   * @param[in] operation The string representing the mathematical operation.
   */
  void CalculateTrigonometry(double num, std::string operation) noexcept;

  /**
   * @brief Converts a double value to a string with a fixed precision of 7
   * decimal places.
   *
   * This function converts a double value to a string with a fixed precision of
   * 7 decimal places and returns the resulting string.
   *
   * @param[in] num The double value to be converted to a string.
   * @return The string representation of the double value.
   */
  std::string DoubleToString(double num);

 private:
  std::string expression_;  ///< Stores the original string value containing the
                            ///< mathematical expression.
  double x_;                ///< Specific X value for expression calculation.
  int dot_count_;  ///< Counter for tracking the number of decimal points in the
                   ///< input.
  std::stack<Token> postfix_;  ///< Stack for holding tokens in postfix notation
                               ///< during expression processing.
  std::stack<Token> operators_;  ///< Temp stack for holding operators.
  std::stack<Token>
      calculation_;  ///< Stack for holding intermediate calculation results
                     ///< during expression evaluation.
  double result_;    ///< Stores the solution to the mathematical expression.
  const std::map<std::string, int>
      priorities_;  ///< Map to store operator priorities.
};
}  // namespace s21

#endif  // SMARTCALC_MODEL_S21_MODEL_H
