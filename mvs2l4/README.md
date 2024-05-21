# Lab 4

This repository contains an implementation of the first lab work, namely `Numerical methods of solving the Cauchy problem`

# Overview
This program performs the numerical approximation of the solution of the differential equation using 3 methods:
1. Implicit trapezoidal method
2. Explicit Midpoint Method
3. Adams-Bashforth method
The results of the approximation and the associated errors are written to the output files, which can be turned into the Word table and the graph using Python.
The primary objective is to compare the approximation accuracy between the three methods.

# Usage

The program approximates the function `u' = F(x,u)` numerically using the `implicitTrapezoidalMethod()`, `midpointMethod()` and `adamsBashforthMethod()` functions.
To use this program to interpolate your function:
1. Change the `a` and `b` variables to the bounds of the approximation domain.
2. Change the `u0` variable to your initial value.
3. Change the `f` function to yours, as well as `fprime` function to the first derivative with respect to u.
4. Run the programm using
   ```
   g++ main.cpp -o main.exe
   ```
   ```
   main.cpp
   ```
   Graph the functions using the pyton script in `graph` folder
   ```
   python main.py
   ```
   
# Notes
All the theoretical stuff and further explanation of the code is located in the `mvs2l4.docx` file.