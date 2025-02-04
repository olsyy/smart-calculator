/**
 * @file s21_creditcalc.h
 * @brief Header file containing the declaration of the CreditCalc for the View
 * abstraction in the MVC pattern.
 */

#ifndef SMARTCALC_VIEW_S21_CREDITCALC_H
#define SMARTCALC_VIEW_S21_CREDITCALC_H

#include <QDebug>
#include <QMainWindow>

#include "../Controller/s21_controller.h"

namespace Ui {
class CreditCalc;
}

namespace s21 {

/**
 * @class CreditCalc
 * @brief The View class responsible for presenting data to the user
 * and receiving user input for credit calculation.
 */
class CreditCalc : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Constructor for the CreditCalc class.
   * @param parent The parent widget (default is nullptr).
   */
  explicit CreditCalc(QWidget *parent = nullptr);

  /**
   * @brief Destructor for the CreditCalc class.
   */
  ~CreditCalc();

 private slots:
  /**
   * @brief Slot triggered when the annuity button is clicked.
   */
  void on_Ann_button_clicked();

  /**
   * @brief Slot triggered when the differential button is clicked.
   */
  void on_Diff_button_clicked();

  /**
   * @brief Toggles the visibility of specific UI elements based on user
   * selection.
   * @param[in] visible Boolean indicating whether to make the elements visible
   * or not.
   */
  void ToggleVisibility(bool visible);

  /**
   * @brief Slot triggered when the equal button is clicked to initiate credit
   * calculation.
   */
  void on_Eq_button_clicked();

 private:
  Ui::CreditCalc *ui;  ///< A pointer to an interface object.
  s21::Controller
      controller_;  ///< The associated Controller handling credit calculations.
};

}  // namespace s21

#endif  // SMARTCALC_VIEW_S21_CREDITCALC_H
