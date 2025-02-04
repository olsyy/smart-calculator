/**
 * @file s21_controller.cc
 * @brief Implementation file for the s21_controller.h.
 */

#include "s21_controller.h"

#include <QString>
#include <string>
#include <tuple>

#include "Model/s21_model.h"

/**
 * @details The mathematical expression is a QString type and requires
 * pre-processing to convert it to std::string. If the model throws any
 * exception, the controller will return "calc_error" instead of the result to
 * the View.
 */
QString s21::Controller::ProcessMathExpression(const QString &expression,
                                               double x) noexcept {
  try {
    model_.SetInput(expression.toStdString());
    model_.SetX(x);
    double result = model_.CalculateMathExpression();
    return QString::number(result, 'g', 8);
  } catch (...) {
    return "calc_error";
  }
}

std::tuple<double, double, double> s21::Controller::ProcessCreditExpression(
    int months, double amount, double term, double rate, int month,
    char type) noexcept {
  return credit_model_.CalculateResult(months, amount, term, rate, month, type);
}
