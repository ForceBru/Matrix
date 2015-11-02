[![Build Status](https://travis-ci.org/ForceBru/Matrix.svg?branch=master)](https://travis-ci.org/ForceBru/Matrix)

# Matrix
User-friendly way to perform operations with matrices.

> ###Warning!

> This project is now in active development, so it may contain bugs and unstable code. If you find any, please let me know.

##What is it for?
_Matrix_ is written to help programmers work with matrices easily and with as little efforts as possible. It also aims for code readability and simple logic. There's no need to work with vectors or arrays in your code (while that's what is used under the hood). You work with objects that implement some basic operations (like multiplication, addition, etc).

##How to use
It's planned to distribute _Matrix_ as a library, but as for now, it's distributed simply as some source files. To use _Matrix_ you need to `#include "Matrix.hpp"` and then compile your project _with the files that belong to Matrix_.

###Compilation
First of all, you need to clone this repo to your computer (or just download and unpack the `.zip` file). Then enter the directory with source you've downloaded and run:

    g++ *.cpp -o some_file

Then run `./some_file` to see how _Matrix_ works. 

##Any examples, please?
The most complete example is `main.cpp` itself. Here is a list of all methods currently available and examples of usage.

 - addition and substraction
  - matrix + matrix and matrix - matrix
   ```
   Matrix a(2, 3), b=a, c=a;
   
   a.FillRandom();
   b.FillZero();
   
   c = a + b;
   
   if (c != a) std::cout << "Something went wrong, please raise an issue!";
   else std::cout << "Test passed";
   
   c -= a;
   
   if (c != b) std::cout << "Something went wrong, please raise an issue!";
   else std::cout << "Test passed";
   ```
  - matrix + number and matrix - number (element-wise and interchangeable)
   ```
   Matrix a(2, 3);
   
   a.FillZero();
   
   a += 6.2;
   
   if (a[0][0] != 6.2) std::cout << "Something went wrong, please raise an issue!";
   else std::cout << "Test passed";
   ```
 - multiplication
  - matrix * matrix and matrix * number
   ```
   Matrix a(2, 3), b(3, 4), c(2, 4);
   
   a.FillRandom();
   b.FillRandom();
   
   c = a * b;
   
   cout << c * 3.1 << endl;
   ```
 - division
  - number / matrix and matrix / number only (element-wise)

##Dependencies and requirements
Absolutely _no dependencies_ except for a C/C++ runtime. Requires a C++ compiler to be built. 

