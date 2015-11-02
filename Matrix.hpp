//
//  Matrix.hpp
//
//  Created by ForceBru on 11.10.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <random>

#include "Exceptions.hpp"

/* This class represents a matrix object and implements all
 mathematical operations that can be done to a matrix:
    addition and substraction
    multiplication
    division (only number / matrix and element-wise)
    raising to power of 2
    exponentiation (element-wise)
 It's easy to transpose a matrix or to get an identity matrix 
 using appropriate methods.
 A matrix can currently be filled either with random numbers
 either with zeroes.
*/

class Matrix {
public:
    Matrix();
    Matrix(long rows, long cols);
    
    void FillRandom(long min = 0, long max = RAND_MAX);
    void FillZero();
    void Reshape(long rows, long cols);
    Matrix T();
    long Rows() { return this->rows; }
    long Cols() { return this->cols; }
    Matrix Transpose() { return this->T(); }
    Matrix Identity();
    Matrix sqr();

    friend Matrix exp(Matrix);
    friend Matrix operator/(const double, const Matrix& );
    
    Matrix& operator=(const Matrix&);
    Matrix operator+(const Matrix& right) const;
    Matrix operator+(const double& right) const;
    Matrix operator+=(const Matrix& right);
    Matrix operator-() const;
    Matrix operator-(const Matrix& right) const;
    Matrix operator-=(const Matrix& right);
    Matrix operator*(const Matrix& right);
    Matrix operator*(const double& right) const;
    
    Matrix operator[](const int);
    
    bool operator==(const Matrix& m) {
        long a, b;
        if (rows!=m.rows || cols != m.cols) return false;
        for (a = 0; a < rows;++a)
            for (b = 0; b < cols;++b)
                if (this->M[a][b] != m.M[a][b]) return false;
        return true;
    }
    
    inline bool operator!=(const Matrix& m) {
        return !(*this == m);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Matrix& obj){
        os << "\n\tRows: " << obj.rows<<" cols: "<<obj.cols<<"\n";
        long a,b;
        os << std::fixed << std::setprecision(3);
        for (a = 0; a < obj.rows; ++a) {
            for (b = 0; b < obj.cols; ++b) os << (obj.M)[a][b] << " ";
            os << "\n";
        }
        os << std::endl;
        return os;
    }
private:
    double Random(long min = 0, long max = RAND_MAX);
    double Mult_Row_by_Column(std::vector<double>row, std::vector<double> col, long size);
    long rows, cols;
        //'M' is a vector of vectors that holds all the values
    std::vector< std::vector<double> > M, _Transposed, _Identity;
    std::vector<double> _t;
};

    //number + matrix
inline Matrix operator+(double left, Matrix& right) {
    return right + left;
}
    //number + matrix
inline Matrix operator+(double left, Matrix right) {
    return right + left;
}

    //number - matrix
inline Matrix operator-(double left, Matrix& right) {
    return (-right) + left;
}

    //number - matrix
inline Matrix operator-(double left, Matrix right) {
    return (-right) + left;
}

    //number * matrix
inline Matrix operator*(double left, Matrix& right) {
    return left * right;
}

#endif /* Matrix_hpp */
