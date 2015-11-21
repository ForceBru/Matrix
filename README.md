[![Build Status](https://travis-ci.org/ForceBru/Matrix.svg?branch=master)](https://travis-ci.org/ForceBru/Matrix)

# Matrix
User-friendly way to perform operations with matrices.

> ###Warning!

> This project is now in active development, so it may contain bugs and unstable code. If you find any, please let me know.

##What is it for?
_Matrix_ is written to help programmers work with matrices easily and with as little efforts as possible. It also aims for code readability and simple logic. There's no need to work with vectors or arrays in your code (while that's what is used under the hood). You work with objects that implement some basic operations (like multiplication, addition, etc).

##How to use
Now Matrix should be used as a static library. First you should compile it. 

1. Clone this repo or download the zipfile
    1. Unzip the downloaded file if any
2. Open console and change directory to where you've got a copy of _Matrix_
3. Change directory to `Matrix`
    `cd Matrix`
4. Generate object files and create a library
    `$CXX` is your C++ compiler. You can do `export CXX=clang #or gcc` and then copy and paste these commands.
    ###Linux
    ```sh
    libtool --tag=CXX --mode=compile $CXX -std=c++0x -g -O -c Matrix.cpp
    libtool --tag=CXX --mode=compile $CXX -std=c++0x -g -O -c operators.cpp
    libtool --tag=CXX --mode=link $CXX -std=c++0x -g -O -o libMatrix.a Matrix.lo operators.lo
    ```
    
    ###Mac OS
    ```sh
    $CXX -c Matrix.cpp -o Matrix.o
    $CXX -c operators.cpp -o operators.o
    libtool -static operators.o Matrix.o -o libMatrix.a
    ```
5. Run tests (optional)
    ```sh
    cd ../Matrix_test
    $CXX -std=c++0x -L ../Matrix -I ../Matrix main.cpp Tests.cpp -o Test -lMatrix
    ```

6. Use _Matrix_ in your project
    All you need is `libMatrix.a` file and a header called `Matrix.hpp`.
    ```sh
    # if you're still in Matrix/Matrix_tests
    cd ..
    $CXX -I Matrix your_files -lMatrix
    ```
7. If you still have questions about how to compile _Matrix_ or link with the library, have a look at `.travis.yml` file.

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

