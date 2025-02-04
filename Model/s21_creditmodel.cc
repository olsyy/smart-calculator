/**
 * @file s21_creditmodel.cc
 * @brief Implementation file for the s21_credit_model.h.
 */

#include "s21_creditmodel.h"

namespace s21 {

std::tuple<double, double, double> CreditModel::CalculateResult(
    int k, double amount, int term, double rate, int month, char type) {
  if (type == 'a')
    return CalculateAnnuityCredit(k, amount, term, rate);
  else
    return CalculateDifferentialCredit(k, amount, term, rate, month);
}

std::tuple<double, double, double> CreditModel::CalculateAnnuityCredit(
    int k, double amount, int term, double rate) {
  int time = term * k;
  double r = rate / 12.0 / 100;
  double pay = amount * (r * pow(1 + r, time)) / (pow(1 + r, time) - 1);
  double perc = (pay * time) - amount;
  double total = amount + perc;

  return std::make_tuple(pay, perc, total);
}

std::tuple<double, double, double> CreditModel::CalculateDifferentialCredit(
    int k, double amount, int term, double rate, int month) {
  int time = term * k;
  double m_rate = rate / 12.0 / 100.0;
  double tmp = amount / time;
  double pay = 0.0, perc = 0.0, total = 0.0;
  for (int i = 0; i < time; ++i) {
    double interest_payment = amount * m_rate;
    if (month == i + 1) pay = interest_payment + tmp;
    total += tmp + interest_payment;
    perc += interest_payment;
    amount -= tmp;
  }
  return std::make_tuple(pay, perc, total);
}

}  // namespace s21
