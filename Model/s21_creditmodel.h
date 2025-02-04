/**
 * @file s21_creditmodel.h
 * @brief Header file containing the declaration of the CreditModel abstraction
 * in the MVC pattern.
 */

#ifndef CREDITMODEL_H
#define CREDITMODEL_H

#include <cmath>
#include <tuple>

namespace s21 {

class CreditModel {
 public:
  CreditModel() noexcept = default;
  ~CreditModel() = default;

  /**
   * @brief Calculates the result based on specified parameters.
   *
   * @param k The coefficient value.
   * @param amount The principal amount.
   * @param term The term of the deposit.
   * @param rate The interest rate.
   * @param month The month of interest calculation.
   * @param type The type of calculation.
   * @return A tuple containing the calculated result values.
   */
  std::tuple<double, double, double> CalculateResult(int k, double amount,
                                                     int term, double rate,
                                                     int month, char type);

 private:
  /**
   * @brief Calculates the annuity payment, interest, and total amount for a
   * loan.
   *
   * This function calculates the annuity payment, interest, and total amount
   * for a loan based on the number of months, loan amount, loan term, interest
   * rate, and the specific month for which the calculations are required.
   *
   * @param[in] k The coefficient value.
   * @param[in] amount The loan amount.
   * @param[in] term The loan term in years.
   * @param[in] rate The annual interest rate.
   * @param[in] month The specific month for which the calculations are
   * required.
   * @return A tuple containing the annuity payment, interest, and total amount.
   */
  std::tuple<double, double, double> CalculateAnnuityCredit(int k,
                                                            double amount,
                                                            int term,
                                                            double rate);

  /**
   * @brief Calculates the differential payment, interest, and total amount for
   * a loan.
   *
   * This function calculates the differential payment, interest, and total
   * amount for a loan based on the number of months, loan amount, loan term,
   * interest rate, and the specific month for which the calculations are
   * required.
   *
   * @param[in] k The coefficient value.
   * @param[in] amount The loan amount.
   * @param[in] term The loan term in years.
   * @param[in] rate The annual interest rate.
   * @param[in] month The specific month for which the calculations are
   * required.
   * @return A tuple containing the differential payment, interest, and total
   * amount.
   */
  std::tuple<double, double, double> CalculateDifferentialCredit(
      int k, double amount, int term, double rate, int month);
};

}  // namespace s21

#endif  // CREDITMODEL_H
