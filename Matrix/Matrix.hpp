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
#   include <random>
#else
#   include <stdlib.h>
#endif
#include <fstream>
#include <limits>
#include <exception>
#include <string>
#include <functional>
#include <cctype>
#include <locale>

#ifdef HAVE_OPENCL
#include "cl.hpp"
#endif


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

enum {UNDEFINED, NONZERO, ZERO};

static inline void CheckZero(size_t* zeros, double num) {
    if (num == 0) {
        if (*zeros == UNDEFINED)
            *zeros = ZERO;
    } else {
        if (*zeros != NONZERO)
            *zeros = NONZERO;
    }
}

#if __cplusplus < 199711L
#   define to_string std::to_string
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
#ifdef HAVE_OPENCL
    static bool initOpenCL(std::string add_src, std::string sub_src, std::string mult_src);
#else
    static constexpr bool initOpenCL(std::string a="", std::string b="", std::string c="");
#endif
    
    Matrix();
    Matrix(const std::string fname);
    Matrix(const size_t rows, const size_t cols);

    Matrix(const std::vector<double>&);
    Matrix(const std::vector< std::vector<double> >&);
    
        // Fill matrix with data
    Matrix& Random(const size_t min = 0, const size_t max = 1);
    Matrix& Zeros();
    Matrix& Ones();
    Matrix& FillWith(const double);
    Matrix& FromFile(const std::string fname);
    Matrix& FromData(const std::vector<double>& data);
    Matrix& FromData(const std::vector< std::vector<double> >& data);
    
    void Reshape(size_t rows, size_t cols);
    
        // Get properties of a Matrix
    size_t Rows() const { return this->rows; }
    size_t Cols() const { return this->cols; }
    bool IsVect() const {  return (rows==1); }
    bool IsCol()  const { return (cols==1); }
    bool IsNum()  const { return ((rows==1) && (cols==1)); }
    bool IsSquare(unsigned n) const { return (rows == n && cols ==n); }
    bool IsZero() const { return this->_isZero; }
    
        // Apply mathematical operations to a Matrix
    Matrix  T();
    Matrix  Transpose() { return this->T(); }
    Matrix  Identity();
    Matrix  Hadamard(const Matrix& right) const;
    Matrix& clear();
    
    Matrix& Prettify();

    friend Matrix exp (const Matrix&);
    friend Matrix sqr (const Matrix&);
    friend Matrix operator/ (const double, const Matrix& );
    
    Matrix& operator= (const Matrix&);
    
    friend Matrix operator+ (const Matrix& left, const Matrix& right);
    
    Matrix  operator+ (const double& right) const;
    Matrix& operator+=(const Matrix& right);
    Matrix  operator- ()                    const;
    
    
    friend Matrix  operator- (const Matrix& left, const Matrix& right);
    
    Matrix  operator- (const double& right) const;
    Matrix& operator-=(const Matrix& right);
    Matrix  operator* (const Matrix& right) const;
    Matrix  operator* (const double& right) const;
    Matrix  operator/ (const double& right) const;
    Matrix& operator/=(const double& right);
    
    Matrix& operator[](const size_t) const;
    
    bool operator! () {
        return this->IsZero();
    }
    
    explicit operator double() const {
        if (rows == 1 && cols == 1) return (double)M[0];
        return 0;
    }
    
    explicit operator int() const {
        return (int)((double)(*this));
    }
    
    explicit operator long() const {
        return (long)((double)(*this));
    }
    
    bool operator==(const Matrix& mat) {
        
        if (rows != mat.rows || cols != mat.cols)
            return false;
        
        
        for (size_t a = 0; a < rows; ++a)
            for (size_t b = 0; b < cols; ++b)
                if (std::fabs(M[a * cols + b] - mat.M[a * cols + b]) > std::numeric_limits<double>::epsilon()*10)
                    return false;
            
        return true;
    }
    
    inline bool operator!=(const Matrix& m) {
        return !(*this == m);
    }
    
    static inline void Init() {
        srand((unsigned int)time(NULL));
    }
    
    
    friend std::ostream& operator<<(std::ostream& os, Matrix obj){
        std::ios_base::fmtflags t=os.flags();
        if (obj.prettified)
            os << std::fixed << std::setprecision(3);
        else
            os << std::fixed << std::setprecision(std::numeric_limits<double>::digits10);
        
        for (size_t a = 0; a < obj.rows; ++a) {
            for (size_t b = 0; b < obj.cols; ++b) {
                os << obj.M[a * (obj.cols) + b];
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
    double _Random(long min, long max);
    size_t rows, cols;
    bool prettified, _isZero;
        //'M' is a vector that holds all the values
    std::vector<double> M;
    
#ifdef HAVE_OPENCL
    static bool                      oclEnabled;
    static cl::Context               context;
    static cl::CommandQueue          queue;
    static cl::Program               add, sub, mult;
#endif
};


    //number + matrix
inline Matrix operator+(double left, const Matrix& right) {
    return right + left;
}

    //number - matrix
inline Matrix operator-(double left, const Matrix& right) {
    return (-right) + left;
}

    //number * matrix
inline Matrix operator*(double left, const Matrix& right) {
    return right * left;
}


    // -------------- EXCEPTIONS --------------

/* This exception is thrown when something
 is wrong with the size of a matrix.
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
