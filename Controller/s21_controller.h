/**
 * @file s21_controller.h
 * @brief Header file with the Controller class responsible for connecting the
 * View with the Model.
 */

#ifndef SMARTCALC_CONTROLLER_S21_CONTROLLER_H_
#define SMARTCALC_CONTROLLER_S21_CONTROLLER_H_

#include <QString>
#include <tuple>
#include <utility>

#include "../Model/s21_creditmodel.h"
#include "../Model/s21_model.h"

namespace s21 {

/**
 * @class Controller
 *
 * @brief Accepts an expression and send to the model for processing.
 *
 * The Controller acts as a glue layer between the View and the Model.
 * It separates business logic and interface, where the Controller knows about
 * the Model, but the View does not.
 */
class Controller {
 public:
  /**
   * @brief Constructor for the Controller class.
   */
  Controller() noexcept = default;

  /**
   * @brief Destructor for the Controller class.
   */
  ~Controller() = default;

  /**
   * @brief Accepts a mathematical expression and x value, redirecting them to
   * the Model for processing.
   *
   * @param[in] expression The matematical expression.
   * @param[in] x The value of x.
   * @return The result of expression.
   */
  QString ProcessMathExpression(const QString &expression, double x) noexcept;

  /**
   * @brief Process a credit expression and calculate annuity or differential
   * payments.
   *
   * This function takes input parameters for a credit calculation and returns a
   * tuple containing annuity or differential payment details.
   *
   * @param[in] months The number of months in the credit term.
   * @param[in] amount The loan amount.
   * @param[in] term The loan term in years.
   * @param[in] rate The annual interest rate.
   * @param[in] month The specific month for which to calculate the payment (for
   * differential payment).
   * @param[in] type The type of calculation: 'a' for annuity, 'd' for
   * differential.
   *
   * @return A tuple containing annuity or differential payment details:
   *         - Element 1: Monthly payment.
   *         - Element 2: Total interest payment.
   *         - Element 3: Total payment (including the loan amount and
   * interest).
   *
   * @note For annuity calculation, set `type` to 'a'. For differential
   * calculation, set `type` to 'd'.
   */
  std::tuple<double, double, double> ProcessCreditExpression(
      int months, double amount, double term, double rate, int month,
      char type) noexcept;

 private:
  s21::Model model_;  //<< The associated Model instance for processing
                      // mathematical expressions.
  s21::CreditModel
      credit_model_;  //<< The associated CreditModel instance for processing
                      // credit expressions.
};
}  // namespace s21

#endif  // SMARTCALC_CONTROLLER_S21_CONTROLLER_H_
