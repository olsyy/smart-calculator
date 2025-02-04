/**
 * @brief Entry point
 *
 * Execution of the program
 * starts here.
 */

#include <QApplication>

#include "s21_mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::s21_MainWindow w;
  w.show();
  return a.exec();
}
