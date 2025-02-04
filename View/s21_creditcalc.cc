/**
 * @file s21_creditcalc.cc
 * @brief Implementation file for the s21_creditcalc.h.
 */

#include "s21_creditcalc.h"

#include <QString>
#include <tuple>

#include "Controller/s21_controller.h"
#include "ui_s21_creditcalc.h"

namespace s21 {

CreditCalc::CreditCalc(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CreditCalc) {
  ui->setupUi(this);
  setFixedSize(550, 370);
  ToggleVisibility(false);
}

CreditCalc::~CreditCalc() { delete ui; }

void CreditCalc::on_Ann_button_clicked() { ToggleVisibility(false); }

void CreditCalc::on_Diff_button_clicked() { ToggleVisibility(true); }

void CreditCalc::ToggleVisibility(bool visible) {
  ui->Month_label->setVisible(visible);
  ui->Month_spinBox->setVisible(visible);
}

/**
 * @details Uses a tuple with value binding for return values: current payment,
 * percentage and total payment.
 */
void CreditCalc::on_Eq_button_clicked() {
  int k = ui->Months_button->isChecked() ? 1 : 12;
  double amount = ui->Amount_spinBox->value();
  int term = ui->Term_spinBox->value();
  double rate = ui->Rate_doubleSpinBox->value();
  int month = ui->Month_spinBox->value();
  char type = ui->Ann_button->isChecked() ? 'a' : 'd';

  auto [payment, precentage, total] =
      controller_.ProcessCreditExpression(k, amount, term, rate, month, type);

  ui->Payment->setText(QString::number(payment, 'f', 2));
  ui->Percentage->setText(QString::number(precentage, 'f', 2));
  ui->All->setText(QString::number(total, 'f', 2));
}

}  // namespace s21
