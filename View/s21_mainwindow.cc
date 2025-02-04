/**
 * @file s21_mainwindow.cc
 * @brief Implementation file for the s21_mainwindow.h.
 */

#include "s21_mainwindow.h"

#include <QString>
#include <QVector>
#include <cmath>

#include "./ui_s21_mainwindow.h"
#include "Controller/s21_controller.h"
#include "s21_creditcalc.h"

namespace s21 {

/**
 *  @details This constructor sets up the UI and connects various buttons to the
 * SymbClicked slot. It simplifies the process of managing multiple buttons by
 * combining them into an array and connecting each button to the common slot,
 * SymbClicked.
 *
 */

s21_MainWindow::s21_MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::s21_MainWindow) {
  ui->setupUi(this);
  ui->Graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  setFixedSize(795, 445);

  QPushButton *buttons[] = {
      ui->Zero_Button,  ui->One_Button,  ui->Two_Button,  ui->Three_Button,
      ui->Four_Button,  ui->Five_Button, ui->Six_Button,  ui->Seven_Button,
      ui->Eight_Button, ui->Nine_Button, ui->X_Button,    ui->Div_Button,
      ui->Mult_Button,  ui->Sub_Button,  ui->Add_Button,  ui->Pow_Button,
      ui->Mod_Button,   ui->Sin_Button,  ui->Cos_Button,  ui->Tan_Button,
      ui->Asin_Button,  ui->Acos_Button, ui->Atan_Button, ui->Ln_Button,
      ui->Log_Button,   ui->Sqrt_Button, ui->LP_Button,   ui->LR_Button,
      ui->E_Button};

  for (QPushButton *button : buttons) {
    connect(button, SIGNAL(clicked()), this, SLOT(SymbClicked()));
  }
  connect(ui->Xmax, SIGNAL(valueChanged(double)), this,
          SLOT(Xmax_valueChanged(double)));
  connect(ui->Xmin, SIGNAL(valueChanged(double)), this,
          SLOT(Xmin_valueChanged(double)));
  connect(ui->Ymax, SIGNAL(valueChanged(double)), this,
          SLOT(Ymax_valueChanged(double)));
  connect(ui->Ymin, SIGNAL(valueChanged(double)), this,
          SLOT(Ymin_valueChanged(double)));
}

s21_MainWindow::~s21_MainWindow() { delete ui; }

void s21_MainWindow::SymbClicked() {
  ///@var current_input The expression at the moment the button is clicked.
  QString current_input = ui->Calculation_label->text();

  ///@var new_value The text of the button that was clicked.
  QString new_value = qobject_cast<QPushButton *>(sender())->text();

  // Check for consecutive arithmetic symbols
  if (!current_input.isEmpty()) CheckArithmetic(current_input, new_value);

  // Place a paranthesis for trigonometric operations
  if (new_value.size() > 1) {
    is_trigonometry_ = true;
    new_value += "(";
  }

  // Clear initial zero if present
  if (current_input == "0") current_input.clear();

  // Update the expression
  ui->Calculation_label->setText(current_input + new_value);
}

void s21_MainWindow::CheckArithmetic(QString &cur_str,
                                     const QString &new_value) {
  if (QString("+-*/").contains(cur_str.back()) &&
      QString("+-*/").contains(new_value))
    cur_str.chop(1);
}

void s21_MainWindow::on_Del_Button_clicked() {
  if (!ui->Calculation_label->text().isEmpty()) {
    ui->Calculation_label->setText(ui->Calculation_label->text().chopped(1));
  }
}

void s21_MainWindow::on_AC_Button_clicked() { ui->Calculation_label->clear(); }

void s21_MainWindow::on_Dot_Button_clicked() {
  ui->Calculation_label->setText(ui->Calculation_label->text() + ".");
}

void s21_MainWindow::Xmin_valueChanged(double value) {
  ui->Xmax->setMinimum(value + 1);
}

void s21_MainWindow::Xmax_valueChanged(double value) {
  ui->Xmin->setMaximum(value - 1);
}

void s21_MainWindow::Ymin_valueChanged(double value) {
  ui->Ymax->setMinimum(value + 1);
}

void s21_MainWindow::Ymax_valueChanged(double value) {
  ui->Ymin->setMaximum(value - 1);
}

void s21_MainWindow::on_Eq_Button_clicked() {
  ///@var result The processed result or an error message.
  QString result = controller_.ProcessMathExpression(
      ui->Calculation_label->text(), ui->Double_Spin_Box->value());
  ui->Calculation_label->setText(result);
}

void s21_MainWindow::on_Graph_Button_clicked() {
  ui->Graph->clearGraphs();
  double h = 0.01;
  QVector<double> x;
  QVector<double> y;
  double xmin = ui->Xmin->value();
  double xmax = ui->Xmax->value();
  double ymin = ui->Ymin->value();
  double ymax = ui->Ymax->value();
  double delta = ymax - ymin;

  for (double i = xmin; i <= xmax; i += h) {
    QString str_result =
        controller_.ProcessMathExpression(ui->Calculation_label->text(), i);
    double result = str_result.toDouble();

    if (str_result == "calc_error") {
      ui->Calculation_label->setText("plot error");
      return;
    }

    if (std::isnan(result) || std::isinf(result) ||
        (!y.empty() && std::abs(y.last() - result) > delta)) {
      if (!x.empty()) {
        ui->Graph->addGraph()->setData(x, y);
        x.clear();
        y.clear();
      }
      continue;
    }

    y.push_back(result);
    x.push_back(i);
  }

  if (!x.empty()) ui->Graph->addGraph()->setData(x, y);
  ui->Graph->xAxis->setRange(xmin, xmax);
  ui->Graph->yAxis->setRange(ymin, ymax);
  ui->Graph->replot();
}



void s21_MainWindow::on_Credit_Button_clicked() { credit_calc_.show(); }

}  // namespace s21
