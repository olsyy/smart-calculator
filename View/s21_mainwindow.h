/**
 * @file s21_mainwindow.h
 * @brief Header file containing the declaration of the s21_MainWindow for the
 * View abstraction in the MVC pattern.
 * @note  When including dependencies, the "IWYU" (Include What You Use) rule is
 * applied to avoid transitive inclusions.
 */

#ifndef SMARTCALC_VIEW_S21_MAINWINDOW_H
#define SMARTCALC_VIEW_S21_MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "../Controller/s21_controller.h"
#include "s21_creditcalc.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class s21_MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

/**
 * @class s21_MainWindow
 * @brief The View class responsible for presenting data to the user
 * and receiving user input.
 *
 * In the context of the Model-View-Controller (MVC) pattern,
 * the View is responsible for the visual representation of the application's
 * data.
 */
class s21_MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Constructor for the s21_MainWindow class, establishing connections
   * between UI elements and slots.
   *
   * @param parent The parent widget (if any) of the main window.
   */
  s21_MainWindow(QWidget *parent = nullptr);

  /**
   * @brief Destructor for the s21_MainWindow class
   */
  ~s21_MainWindow();

 private slots:

  /**
   * @brief Process user input for the calculator.
   *
   * The function combines the values of the calculator buttons into a
   * mathematical expression. It prevents consecutive arithmetic symbols and
   * ensures correct placement of parentheses for trigonometric operations.
   */
  void SymbClicked();

  /**
   * @brief Checks if the last character in the expression and the new one are
   * both arithmetic, and removes the last character if they are.
   *
   * @param[in, out] cur_str The current input expression.
   * @param[in] new_value The new value to be added to the expression.
   */
  void CheckArithmetic(QString &cur_str, const QString &new_value);

  /**
   * @brief Removes the last character from the calculation label until the
   * string is empty.
   */
  void on_Del_Button_clicked();

  /**
   * @brief Clears the content of the calculation label.
   */
  void on_AC_Button_clicked();

  /**
   * @brief Adds a dot to the calculation label.
   *
   * This function adds a dot to the current expression in the calculation
   * label. The dot is typically used to represent decimal points in
   * floating-point numbers.
   */
  void on_Dot_Button_clicked();

  /**
   * @brief Slot for handling changes in the Xmin value.
   * @param value The new value of Xmin.
   */
  void Xmin_valueChanged(double value);

  /**
   * @brief Slot for handling changes in the Xmax value.
   * @param value The new value of Xmax.
   */
  void Xmax_valueChanged(double value);

  /**
   * @brief Slot for handling changes in the Ymin value.
   * @param value The new value of Ymin.
   */
  void Ymin_valueChanged(double value);

  /**
   * @brief Slot for handling changes in the Ymax value.
   * @param value The new value of Ymax.
   */
  void Ymax_valueChanged(double value);

  /**
   * @brief Sends the current expression to the controller for processing.
   */
  void on_Eq_Button_clicked();

  /**
   * @brief Slot for handling the click event of the Credit Button.
   * Shows the credit calculator dialog.
   */
  void on_Credit_Button_clicked();

  /**
   * @brief Slot for handling the click event of the Graph Button.
   * Clears existing graphs, generates x and y values, and plots the graph.
   */
  void on_Graph_Button_clicked();

 private:
  Ui::s21_MainWindow *ui;  ///< A pointer to an interface object.
  s21::Controller
      controller_;  ///< The associated Controller handling credit calculations.
  s21::CreditCalc credit_calc_;  ///< The View of Credit Calculator.
  bool is_trigonometry_ = false;
};

}  // namespace s21

#endif  // SMARTCALC_VIEW_S21_MAINWINDOW_H
