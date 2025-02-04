#include "../Model/s21_model.h"
#include "../Model/s21_creditmodel.h"


#include <gtest/gtest.h>

#include <cmath>
#include <string>
#include <tuple>
#include <iostream>

TEST(Calc, Sum) {
  s21::Model m;
  m.SetInput("134.5675673+456.8946571");
  ASSERT_NEAR(m.CalculateMathExpression(), 591.4622244, 1e-6);
}

TEST(Calc, Sub) {
  s21::Model m;
  m.SetInput("134.5675673-456.8946571");
  ASSERT_NEAR(m.CalculateMathExpression(), -322.3270898, 1e-6);
}

TEST(Calc, Mul) {
  s21::Model m;
  m.SetInput("134.5675673*456.8946571");
  ASSERT_NEAR(m.CalculateMathExpression(), 6'1483.2025183, 1e-6);
}

TEST(Calc, Div) {
  s21::Model m;
  m.SetInput("134.5675673/456.8946571");
  ASSERT_NEAR(m.CalculateMathExpression(), 0.2945265, 1e-6);
}

TEST(Calc, Mod) {
  s21::Model m;
  m.SetInput("101%10");
  ASSERT_NEAR(m.CalculateMathExpression(), 1, 1e-6);
}

TEST(Calc, Pow_1) {
  s21::Model m;
  m.SetInput("8.11^2.12");
  ASSERT_NEAR(m.CalculateMathExpression(), 84.5520635, 1e-6);
}

TEST(Calc, Pow_2) {
  s21::Model m;
  m.SetInput("3.96e+3");
  ASSERT_EQ(m.CalculateMathExpression(), 3'960);
}

TEST(Calc, Pow_3) {
  s21::Model m;
  m.SetInput("3.96e3");
  ASSERT_NEAR(m.CalculateMathExpression(), 3'960, 1e-6);
}

TEST(Calc, Pow_4) {
  s21::Model m;
  m.SetInput("17.356e-4");
  ASSERT_NEAR(m.CalculateMathExpression(), 0.0017356, 1e-6);
}

TEST(Calc, UnaryPlus) {
  s21::Model m;
  m.SetInput("+156+344");
  ASSERT_NEAR(m.CalculateMathExpression(), 500, 1e-6);
}

TEST(Calc, Cos) {
  s21::Model m;
  m.SetInput("cos(2.6)");
  ASSERT_NEAR(m.CalculateMathExpression(), -0.8568889, 1e-6);
}

TEST(Calc, Sin) {
  s21::Model m;
  m.SetInput("sin(2.6)");
  ASSERT_NEAR(m.CalculateMathExpression(), 0.5155014, 1e-6);
}

TEST(Calc, Tan) {
  s21::Model m;
  m.SetInput("tan(2.6)");
  ASSERT_NEAR(m.CalculateMathExpression(), -0.6015966, 1e-6);
}

TEST(Calc, Ln) {
  s21::Model m;
  m.SetInput("ln(2.6)");
  ASSERT_NEAR(m.CalculateMathExpression(), 0.9555114, 1e-6);
}

TEST(Calc, Log) {
  s21::Model m;
  m.SetInput("log(2.6)");
  ASSERT_NEAR(m.CalculateMathExpression(), 0.4149733, 1e-6);
}

TEST(Calc, Asin) {
  s21::Model m;
  m.SetInput("asin(0.5)");
  ASSERT_NEAR(m.CalculateMathExpression(), 0.5235987, 1e-6);
}

TEST(Calc, Acos) {
  s21::Model m;
  m.SetInput("acos(0.5)");
  ASSERT_NEAR(m.CalculateMathExpression(), 1.0471975, 1e-6);
}

TEST(Calc, Atan) {
  s21::Model m;
  m.SetInput("atan(0.5)");
  ASSERT_NEAR(m.CalculateMathExpression(), 0.4636476, 1e-6);
}

TEST(Calc, Sqrt) {
  s21::Model m;
  m.SetInput("sqrt(115.6)");
  ASSERT_NEAR(m.CalculateMathExpression(), 10.7517440, 1e-6);
}

TEST(Calc, X) {
  s21::Model m;
  m.SetInput("x^x");
  m.SetX(8);
  ASSERT_NEAR(m.CalculateMathExpression(), 16'777'216, 1e-6);
}

TEST(Calc, Calculation_1) {
  s21::Model m;
  m.SetInput("58-(-5)/2^3-12");
  ASSERT_NEAR(m.CalculateMathExpression(), 46.625, 1e-6);
}

TEST(Calc, Calculation_2) {
  s21::Model m;
  m.SetInput("3*sin(cos(tan(10)))");
  ASSERT_NEAR(m.CalculateMathExpression(), 2.1459451, 1e-6);
}

TEST(Calc, Calculation_3) {
  s21::Model m;
  m.SetInput("5*(28-(9-(5-(1+1))))");
  ASSERT_NEAR(m.CalculateMathExpression(), 110, 1e-6);
}

TEST(Calc, Calculation_4) {
  s21::Model m;
  m.SetInput("sin(5)^2+cos(5)^2");
  ASSERT_NEAR(m.CalculateMathExpression(), 1, 1e-6);
}

TEST(Calc, Calculation_5) {
  s21::Model m;
  m.SetInput("78-(-86.23)+9*tan(4)");
  ASSERT_NEAR(m.CalculateMathExpression(), 174.6503915, 1e-6);
}

TEST(Calc, Calculation_6) {
  s21::Model m;
  m.SetInput("cos(x)-sin(x)");
  m.SetX(4);
  ASSERT_NEAR(m.CalculateMathExpression(), 0.1031588, 1e-6);
}

TEST(Calc, Calculation_7) {
  s21::Model m;
  m.SetInput("58*5^8/6+sqrt(45*sin(0.66))");
  ASSERT_NEAR(m.CalculateMathExpression(), 3'776'046.91931, 1e-6);
}

TEST(Calc, Calculation_8) {
  s21::Model m;
  m.SetInput("ln(x)*cos(x)");
  m.SetX(6);
  ASSERT_NEAR(m.CalculateMathExpression(), 1.7203942, 1e-6);
}

TEST(Calc, Calculation_9) {
  s21::Model m;
  m.SetInput("(-(-(-10)))-(-(-10))");
  m.SetX(6);
  ASSERT_NEAR(m.CalculateMathExpression(), -20, 1e-6);
}

TEST(Calc, Calculation_10) {
  s21::Model m;
  m.SetInput("(-(-(-10)))-(-(-10))");
  m.SetX(6);
  ASSERT_NEAR(m.CalculateMathExpression(), -20, 1e-6);
}

TEST(Calc, PosInf) {
  s21::Model m;
  m.SetInput("1/0");
  ASSERT_TRUE(std::isinf(m.CalculateMathExpression()));
}

TEST(Calc, NegInf) {
  s21::Model m;
  m.SetInput("-1/0");
  ASSERT_TRUE(std::isinf(m.CalculateMathExpression()));
}

TEST(Calc, Nan) {
  s21::Model m;
  m.SetInput("sqrt(-1.0)");
  ASSERT_TRUE(std::isnan(m.CalculateMathExpression()));
}

TEST(Calc, ErrorCalculation_1) {
  s21::Model m;
  EXPECT_THROW({
    m.SetInput("");
  }, std::invalid_argument);
}

TEST(Calc, ErrorCalculation_2) {
  s21::Model m;
  std::string str(260, '0');
  EXPECT_THROW({
    m.SetInput("2+(4-5))");
  }, std::invalid_argument);
}

TEST(Calc, ErrorCalculation_3) {
  s21::Model m;
  EXPECT_THROW({
  m.SetInput(")");
  }, std::invalid_argument);
}

TEST(Calc, ErrorCalculation_4) {
  s21::Model m;
  EXPECT_THROW({
  m.SetInput("()");
  }, std::invalid_argument);
}

TEST(Calc, ErrorCalculation_5) {
  s21::Model m;
  EXPECT_THROW({
  m.SetInput("cos");
  }, std::invalid_argument);
}

TEST(Calc, ErrorCalculation_6) {
  s21::Model m;
  EXPECT_THROW({
  m.SetInput("coss(6)");
  m.CalculateMathExpression();
  }, std::invalid_argument);
}

TEST(Calc, ErrorCalculation_7) {
  s21::Model m;
  EXPECT_THROW({
  m.SetInput("6.7.0-6");
  m.CalculateMathExpression();
  }, std::invalid_argument);
}

TEST(Calc, ErrorCalculation_8) {
  s21::Model m;
  EXPECT_THROW({
  m.SetInput("6e*5");
  m.CalculateMathExpression();
  }, std::invalid_argument);
}

TEST(Calc, ErrorCalculation_9) {
  s21::Model m;
  EXPECT_THROW({
  m.SetInput("e+5-6");
  m.CalculateMathExpression();
  }, std::invalid_argument);
}

TEST(Calc, ErrorCalculation_10) {
  s21::Model m;
  EXPECT_THROW({
  m.SetInput("cos(5)e5-6");
  m.CalculateMathExpression();
  }, std::invalid_argument);
}

TEST(CreditCalc, Annuity_1) {
  std::stringstream stream;
  s21::CreditModel m;
  int k = 12;
  double amount = 300000;
  double term = 5;
  double rate = 16.0;
  int month = 1;
  char type = 'a';
  auto [payment, precentage, total] = m.CalculateResult(k, amount, term, rate, month, type);
  ASSERT_EQ(std::floor(payment), 7295);
  ASSERT_EQ(std::floor(precentage), 137725);
  ASSERT_EQ(std::floor(total), 437725);
}

TEST(CreditCalc, Annuity_2) {
  s21::CreditModel m;
  int k = 12;
  double amount = 10'000'000;
  double term = 2;
  double rate = 5.0;
  int month = 1;
  char type = 'a';
  auto [payment, precentage, total] = m.CalculateResult(k, amount, term, rate, month, type);
  ASSERT_EQ(std::floor(payment), 438'713);
  ASSERT_EQ(std::floor(precentage), 529'133);
  ASSERT_EQ(std::floor(total), 10'529'133);
}

TEST(CreditCalc, Diff_1) {
  std::stringstream stream;
  s21::CreditModel m;
  int k = 12;
  double amount = 300000;
  double term = 5;
  double rate = 16.0;
  int month = 1;
  char type = 'd';
  auto [payment, precentage, total] = m.CalculateResult(k, amount, term, rate, month, type);
  ASSERT_EQ(std::floor(payment), 9'000);
  ASSERT_EQ(std::floor(precentage), 122'000);
  ASSERT_EQ(std::floor(total), 422'000);
}

TEST(CreditCalc, Diff_2) {
  s21::CreditModel m;
  int k = 12;
  double amount = 10'000'000;
  double term = 2;
  double rate = 5.0;
  int month = 1;
  char type = 'd';
  auto [payment, precentage, total] = m.CalculateResult(k, amount, term, rate, month, type);
  ASSERT_EQ(std::floor(payment), 458'333);
  ASSERT_EQ(std::floor(precentage), 520'833);
  ASSERT_EQ(std::floor(total), 10'520'833);
}
