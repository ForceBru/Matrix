//
//  Matrix.hpp
//
//  Created by ForceBru on 11.10.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#pragma once

#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <sstream>
#if __cplusplus > 199711L
#include <random>
#else
#include <stdlib.h>
#endif
#include <fstream>
#include <limits>
#include <exception>
#include <string>
#include <functional>
#include <cctype>
#include <locale>

    // trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

    // trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

    // trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}


template<typename T>
std::string to_string(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

#if __cplusplus < 199711L
#define to_string std::to_string
#endif


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
    Matrix(std::string fname);
    Matrix(long rows, long cols);
    Matrix(std::vector<double>);
    Matrix(std::vector< std::vector<double> >);
    
    void Random(long min = 0, long max = 1);
    void Zeros();
    void Ones();
    int FromFile(std::string fname);
    void FromData(std::vector<double> data);
    void FromData(std::vector< std::vector<double> > data);
    void Reshape(long rows, long cols);
    Matrix T();
    long Rows() const { return this->rows; }
    long Cols() const { return this->cols; }
    bool IsVect() const { if (rows==1) return true; return false; }
    bool IsCol() const { if (cols==1) return true; return false; }
    bool IsNum() const { if ((rows==1) && (cols==1)) return true; return false; }
    bool IsSquare(unsigned n) const { if (rows==cols==n) return true; return false; }
    Matrix Transpose() { return this->T(); }
    Matrix Identity();
    Matrix Hadamard(const Matrix& right) const;
    Matrix sqr();
    Matrix& Prettify();

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
    Matrix operator/(const double right) const;
    Matrix operator/=(const double right);
    
    Matrix& operator[](const long);
    
    explicit operator double() const {
        if (rows == 1 && cols == 1) return M[0][0];
        return 0;
    }
    
    explicit operator int() const {
        return (int)((double)(*this));
    }
    
    explicit operator long() const {
        return (long)((double)(*this));
    }
    
    bool operator==(const Matrix& mat) {
        size_t a, b;

        if (rows != mat.rows || cols != mat.cols)
            return false;
        
        for (a = 0; a < rows; ++a)
            for (b = 0; b < cols; ++b)
                if (std::fabs(M[a][b] - mat.M[a][b]) > std::numeric_limits<double>::epsilon()*10)
                    return false;
            
        return true;
    }
    
    inline bool operator!=(const Matrix& m) {
        return !(*this == m);
    }
    
    static void Init() {
        srand((unsigned int)time(NULL));
    }
    
    
    friend std::ostream& operator<<(std::ostream& os, Matrix obj){
        size_t a,b;
        std::ios_base::fmtflags t=os.flags();
        if (obj.prettified)
            os << std::fixed << std::setprecision(3);
        else
            os << std::fixed << std::setprecision(std::numeric_limits<double>::digits10);
        
        for (a = 0; a < obj.rows; ++a) {
            for (b = 0; b < obj.cols; ++b) {
                os << (obj.M)[a][b];
                if (b != obj.cols-1) os << ' ';
            }
            if (obj.rows > 1)
                os << std::endl;
        }
        
        os.flags(t);
        obj.prettified=false;
        return os;
    }
private:
    double _Random(long min = 0, long max = RAND_MAX);
    //inline double Mult_Row_by_Column(Matrix row, Matrix col);
    size_t rows, cols;
    bool modified, prettified;
        //'M' is a vector of vectors that holds all the values
    std::vector< std::vector<double> > M, _Transposed, _Identity;
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
    return right * left;
}

    // -------------- EXCEPTIONS --------------

/* This exception is thrown when something
 is wrong with the sze of a matrix.
 For example, if two matrices are not of the
 appropriate sizes (PxN and NxK) or if
 one tries to substract or add matrices of different shapes,
 e.g. PxN + PxK instead of PxN + PxN.
 */

class SizeException : public std::exception {
public:
    SizeException() : msg("Size mismatch") { }
    explicit SizeException(const char * msg) : msg(msg) { }
    explicit SizeException(const std::string msg) : msg(msg.c_str()) { }
    virtual ~SizeException() throw() {}
    virtual const char* what() const throw() { return msg.c_str(); }
private:
    std::string msg;
};

class FileException : public std::exception {
public:
    FileException() : msg("Failed to open a file") { }
    explicit FileException(const char * msg) : msg(msg) { }
    explicit FileException(const std::string msg) : msg(msg.c_str()) { }
    virtual ~FileException() throw() {}
    virtual const char* what() const throw() { return msg.c_str(); }
private:
    std::string msg;
};

#endif /* Matrix_hpp */
