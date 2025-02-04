# SmartCalc v2.0

## Overview
SmartCalc v2.0 is a powerful and flexible calculator application developed in C++17. It supports complex arithmetic operations, function plotting, and advanced financial calculations, including credit and deposit calculators.

## Features

Arithmetic Expression Evaluation: Supports infix notation with nested brackets, integer and real numbers (including exponential notation).
Graph Plotting: Visualizes functions with adaptive grids and scalable coordinate axes.
Credit Calculator: Calculates monthly payments, overpayment, and total payment for annuity and differentiated credit types.
Deposit Calculator: Evaluates profitability with support for interest capitalization, tax rates, replenishments, and partial withdrawals.

## Technologies Used
- Language: C++17
- GUI Libraries: Qt
- Testing Framework: Google Test (GTest)
- Build System: Makefile with targets: all, install, uninstall, clean, dvi, dist, tests
- Implemented using the Model-View-Controller (MVC) pattern:

## Supported Operations
- Arithmetic Operators: Addition (+), Subtraction (-), Multiplication (*), Division (/), Power (^), Modulus (mod), Unary Plus (+), Unary Minus (-)
- Mathematical Functions: Trigonometric: sin(x), cos(x), tan(x)
- Inverse Trigonometric: asin(x), acos(x), atan(x)
- Logarithmic: ln(x), log(x)
- Others: sqrt(x)
- Financial Calculator

## Build & Run
```bash
 make all ./SmartCalc
```

## Testing
```bash
make tests
./tests
```

## Installation
```bash
make install
```

## Uninstallation
```bash
make uninstall
```

## License
This project is licensed under the MIT License.
