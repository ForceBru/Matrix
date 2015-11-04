[![Build Status](https://travis-ci.org/ForceBru/Matrix.svg?branch=master)](https://travis-ci.org/ForceBru/Matrix)

# Matrix
User-friendly way to perform operations with matrices.

> ###Warning!

> This project is now in active development, so it may contain bugs and unstable code. If you find any, please let me know.

##What is it for?
_Matrix_ is written to help programmers work with matrices easily and with as little efforts as possible. It also aims for code readability and simple logic. There's no need to work with vectors or arrays in your code (while that's what is used under the hood). You work with objects that implement some basic operations (like multiplication, addition, etc).

##How to use
It's planned to distribute _Matrix_ as a library, but as for now, it's distributed simply as some source files. To use _Matrix_ you need to `#include "Matrix.hpp"` and then compile your project _with the files that belong to Matrix_: 
```sh
g++ your_file.cpp Matrix.cpp operators.cpp Exceptions.cpp -o some_file
```

###Compilation
First of all, you need to clone this repo to your computer (or just download and unpack the `.zip` file). Then enter the directory with source you've downloaded and run:

    g++ *.cpp -o some_file

Then run `./some_file` to see how _Matrix_ works. 

##Any examples, please?
The most complete example is `main.cpp` itself. Here is a list of all mathematical operations currently available and examples of usage.

 - addition and substraction
  - `matrix + matrix` and `matrix - matrix`
   ```cpp
   Matrix a(2, 3), b=a, c=a;
   
   a.Random(0, 1); // random values in range [0, 1]
   b.Zeroes();
   
   c = a + b;
   
   if (c != a) std::cout << "Something went wrong, please raise an issue!";
   else std::cout << "Test passed";
   
   c -= a;
   
   if (c != b) std::cout << "Something went wrong, please raise an issue!";
   else std::cout << "Test passed";
   ```
  - `matrix + number` and `matrix - number` (element-wise and interchangeable)
   ```cpp
   Matrix a(2, 3);
   
   a.Zeroes();
   
   a += 6.2;
   
   if (a[0][0] != 6.2) std::cout << "Something went wrong, please raise an issue!";
   else std::cout << "Test passed";
   ```
 - multiplication
  - `matrix * matrix` and `matrix * number` (last case interchangeable)
   ```cpp
   Matrix a(2, 3), b(3, 4), c(2, 4);
   
   a.Random();
   b.Random();
   
   c = a * b;
   
   cout << c * 3.1 << endl;
   ```
 - division
  - `number / matrix` and `matrix / number` only (element-wise)
 - raising to power of two
  ```cpp
  Matrix a(2, 2); // square matrices only
  
  cout << a.sqr() << endl;
  ```
 - matrix exponentiation (element-wise)
  ```cpp
  Matrix a(3, 5);
  
  cout << exp(a) << endl;
  ```
 - negation
  ```cpp
  Matrix a(2, 4);
  
  a.Random();
  
    //too easy
  cout << -a << endl;
  ```
  
##Vectorizing functions
It's very easy to vectorize a function with _Matrix_:
```cpp
Matrix sigmoid(Matrix& z) {
    return 1.0 / (1.0 + exp(-z));
}

int main (void) {
    Matrix N(3, 5);
    
    N.Random(0, 1);
    
    Matrix result = sigmoid(N);
    
    // do some stuff...
    
    return 0;
}
```

##Ways to populate matrices with data
 - with random values, ones or zeroes
  ```cpp
  Matrix a(2, 3), b(3, 4), c(4, 5);
  
  a.Random(0, 1);
  b.Ones();
  c.Zeroes();
  ```
 - with values from a file
  ```cpp
  Matrix a; // shape will be calculated automatically
            // according to data in the file
  a.FromFile("matrix_a.txt");
  ```
  
 ###Matrix file format
 Input data row by row and column by column. Separate numbers with a whitespace, rows with new lines.
 
 Example:
 
 ```
 0.234 0.456 0.678
 0.123 0.345 0.567
 ```
 
 This will be converted into a 2X3 matrix.
 

##Dependencies and requirements
Absolutely _no dependencies_ except for a C/C++ runtime. Requires a C++ compiler to be built. 

