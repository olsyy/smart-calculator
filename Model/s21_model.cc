/**
 * @file s21_creditmodel.cc
 * @brief Implementation file for the s21_model.h.
 */

#include "s21_model.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <map>
#include <stack>
#include <stdexcept>
#include <string>

s21::Model::Model() noexcept
    : expression_(),
      x_(),
      dot_count_(0),
      postfix_(),
      operators_(),
      calculation_(),
      result_(),
      priorities_{{")", 6},    {"(", 6},    {"cos", 5},  {"sin", 5}, {"tan", 5},
                  {"acos", 5}, {"asin", 5}, {"atan", 5}, {"ln", 5},  {"log", 5},
                  {"~", 4},    {"sqrt", 3}, {"^", 3},    {"%", 2},   {"*", 2},
                  {"/", 2},    {"-", 1},    {"+", 1}} {}

void s21::Model::SetInput(const std::string& input) {
  ValidateInput(input);
  expression_ = input;
}

void s21::Model::SetX(const double x) noexcept { x_ = x; }

void s21::Model::ValidateInput(const std::string& input) {
  bool is_valid_size = !input.empty() && input.size() < 256;
  bool is_valid_parenthesis = std::count(input.begin(), input.end(), '(') ==
                              std::count(input.begin(), input.end(), ')');
  bool is_valid_first_unary = !input.empty() && input[0] != '*' &&
                              input[0] != '/' && input[0] != '^' &&
                              input[0] != '%';
  bool is_math_expression = std::any_of(input.begin(), input.end(), [](char c) {
    return std::isdigit(c) || c == 'x';
  });

  if (!(is_valid_size && is_valid_parenthesis && is_math_expression &&
        is_valid_first_unary)) {
    throw std::invalid_argument("Invalid input");
  }
}

double s21::Model::CalculateMathExpression() {
  ReplaceScientificNotation();
  ToPostfix();
  Calculate();
  return result_;
}

void s21::Model::ReplaceScientificNotation() {
  size_t pos = expression_.find('e');
  while (pos != std::string::npos) {
    bool is_valid_prev = (pos > 1) && std::isdigit(expression_[pos - 1]);
    bool is_valid_nxt =
        (pos + 1 < expression_.size()) &&
        (std::isdigit(expression_[pos + 1]) || expression_[pos + 1] == '+' ||
         expression_[pos + 1] == '-');
    if (!is_valid_nxt || !is_valid_prev) {
      throw std::invalid_argument("Invalid input");
    }
    expression_.replace(pos, 1, "*10^");
    pos = expression_.find('e', pos + 4);
  }
}

void s21::Model::ToPostfix() {
  std::string number;
  std::string operation;
  for (auto it = expression_.begin(); it != expression_.end(); ++it) {
    char c = *it;  /// Lexeme
    bool is_exp = (c == 'e');

    // Incrementing counter for validating a double
    if (c == '.' && !number.empty()) ++dot_count_;

    // Write number
    if (isdigit(c) || c == '.' || is_exp)
      number += c;
    else if (!number.empty())
      PushNumberToPostfix(number);

    // Replace x to number
    if (c == 'x') postfix_.push({DoubleToString(x_), 0});

    // Write trigonometry or functions
    if (isalpha(c) && c != 'x')
      operation += c;
    else if (!operation.empty())
      PushOperationToOperators(operators_, operation);

    // Write arithmetic operators
    if (IsOperator(c)) {
      if (c == '+' && IsUnary(it)) continue;
      if (c == '-' && IsUnary(it)) c = '~';
      while (!operators_.empty() &&
             GetTokenPriority(operators_) >=
                 SetTokenPriority(std::string(1, c)) &&
             GetTokenValue(operators_) != "(") {
        postfix_.push(operators_.top());
        operators_.pop();
      }
      PushOperationToOperators(operators_, c);
    }

    // Write parenthesis
    if (c == '(') PushOperationToOperators(operators_, c);

    if (c == ')') {
      while (!operators_.empty() && GetTokenValue(operators_) != "(") {
        postfix_.push(
            {GetTokenValue(operators_), GetTokenPriority(operators_)});
        operators_.pop();
      }
      if (!operators_.empty()) {
        operators_.pop();  // Pop '('
      }
    }
  }

  if (!number.empty()) PushNumberToPostfix(number);
  if (!operation.empty()) PushOperationToOperators(operators_, operation);

  while (!operators_.empty()) {
    postfix_.push({GetTokenValue(operators_), GetTokenPriority(operators_)});
    operators_.pop();
  }

  ReverseStack();
}

void s21::Model::PushNumberToPostfix(std::string& number) {
  if (dot_count_ > 1) throw std::invalid_argument("Invalid input");
  dot_count_ = 0;
  postfix_.push({number, 0});  // Assuming 0 as the priority for numbers
  number.clear();
}

void s21::Model::PushOperationToOperators(std::stack<Token>& stack,
                                          std::string& operation) {
  stack.push({operation, SetTokenPriority(operation)});
  operation.clear();
}

void s21::Model::PushOperationToOperators(std::stack<Token>& stack,
                                          char operation) {
  stack.push(
      {std::string(1, operation), SetTokenPriority(std::string(1, operation))});
}

std::string s21::Model::GetTokenValue(const std::stack<Token>& token) {
  return token.top().value;
}

int s21::Model::GetTokenPriority(const std::stack<Token>& token) {
  return token.top().priority;
}

void s21::Model::ThrowInvalidDouble() {
  if (dot_count_ > 1) throw std::invalid_argument("Invalid input");
  dot_count_ = 0;
}

bool s21::Model::IsOperator(char c) noexcept {
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%');
}

int s21::Model::SetTokenPriority(const std::string& operation) {
  try {
    return priorities_.at(operation);
  } catch (...) {
    throw std::invalid_argument("Invalid input");
  }
}

bool s21::Model::IsUnary(std::string::iterator it) {
  return it == expression_.begin() || *(it - 1) == '(' ||
         IsOperator(*(it - 1)) || IsOperator(*(it + 1));
}

void s21::Model::ReverseStack() {
  std::stack<Token> reversed_stack;
  while (!postfix_.empty()) {
    reversed_stack.push(postfix_.top());
    postfix_.pop();
  }
  postfix_ = std::move(reversed_stack);
}

void s21::Model::Calculate() {
  while (!postfix_.empty()) {
    double num = 0.0;
    std::string token = GetTokenValue(postfix_);
    bool is_number = GetTokenPriority(postfix_) == 0;
    if (is_number) {
      calculation_.push(postfix_.top());
    } else if (IsOperator(token[0])) {
      num = std::stod(GetTokenValue(calculation_));
      calculation_.pop();
      double num2 = std::stod(GetTokenValue(calculation_));
      calculation_.pop();
      CalculateArithmetic(num2, num, token[0]);
    } else {
      num = std::stod(GetTokenValue(calculation_));
      calculation_.pop();
      CalculateTrigonometry(num, token);
    }
    postfix_.pop();
  }
  result_ = std::stod(GetTokenValue(calculation_));

  calculation_.pop();
  if (!calculation_.empty()) throw std::invalid_argument("Invalid input");
}

void s21::Model::CalculateArithmetic(double num1, double num2,
                                     char operation) noexcept {
  double result = 0.0;
  switch (operation) {
    case '+':
      result = num1 + num2;
      break;
    case '-':
      result = num1 - num2;
      break;
    case '*':
      result = num1 * num2;
      break;
    case '/':
      result = num1 / num2;
      break;
    case '^':
      result = pow(num1, num2);
      break;
    case '%':
      result = fmod(num1, num2);
      break;
    default:
      break;
  }
  calculation_.push({DoubleToString(result), 0});
}

void s21::Model::CalculateTrigonometry(double num,
                                       std::string operation) noexcept {
  double result = 0.0;
  if (operation == "cos") result = cos(num);
  if (operation == "sin") result = sin(num);
  if (operation == "tan") result = tan(num);
  if (operation == "acos") result = acos(num);
  if (operation == "asin") result = asin(num);
  if (operation == "atan") result = atan(num);
  if (operation == "sqrt") result = sqrt(num);
  if (operation == "log") result = log10(num);
  if (operation == "ln") result = log(num);
  if (operation == "~") result = -num;
  calculation_.push({DoubleToString(result), 0});
}

std::string s21::Model::DoubleToString(double num) {
  char buff[255];
  sprintf(buff, "%.7lf", num);
  return std::string(buff);
}
