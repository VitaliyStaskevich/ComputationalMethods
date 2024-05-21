# Lab 3

This repository contains an implementation of the first lab work, namely `Numerical integral approximation`

# Overview
This program performs the numerical integral approximation using the midpoint method and the Simpsons` method.
The results of the integration and the associated errors are written to the output file, which can be turned into the Word table easily.
The primary objective is to compare the integration accuracy between the two methods.

# Usage

The program integrates the function `F` numerically using the `middleRectangles(int)` and `Simpson(int)` functions.
To use this program to interpolate your function:
1. Change the `a` and `b` variables to the bounds of the integration domain.
2. (Optionally) Change the `I` variable to the exact result to check the accuracy of the integration.
3. Change the `F` function to yours.
4. Run the programm using
   ```
   g++ main.cpp -o main.exe
   ```
   ```
   main.cpp
   ```
   
# Notes
All the theoretical stuff and further explanation of the code is located in the `mvs2l3.docx` file.
