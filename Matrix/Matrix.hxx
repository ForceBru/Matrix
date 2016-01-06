//
//  Matrix.cpp
//
//  Created by ForceBru on 11.10.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//


#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//#include "Matrix.hpp"

    //default constructor constructs an ordinary number
template <typename datatype>
Matrix<datatype>::Matrix(): rows(1), cols(1), _isZero(true), prettified(false) {
    this->M.resize(1);
    this->M.reserve(4);
}

    //construct a matrix of size rows x cols
template <typename datatype>
Matrix<datatype>::Matrix(size_t rows, size_t cols): rows(rows), cols(cols), _isZero(true), prettified(false) {
    this->M.resize(rows * cols);
}

template <typename datatype>
Matrix<datatype>::Matrix(const std::vector<datatype>& data) {
    this->FromData(data);
}

template <typename datatype>
Matrix<datatype>::Matrix(const std::vector< std::vector<datatype> >& data) {
    this->FromData(data);
}

template <typename datatype>
Matrix<datatype>::Matrix(const std::string fname) {
    if (! this->FromFile(fname)) {
        this->rows = this->cols = 1;
        this->M.resize(1);
        this->M.reserve(4);
        this->_isZero = 0;
        this->prettified=false;
    }
}

    //transpose a matrix
template <typename datatype>
Matrix<datatype> Matrix<datatype>::T() {
    
    if (this->IsNum())
        return *this;
    
    Matrix<datatype> tmp(cols, rows);
    
    for (size_t a = 0; a < cols; ++a)
        for (size_t b = 0; b < rows; ++b)
            tmp.M[a * rows + b] = this->M[b * cols + a];
    
    return tmp;
}

    //return identity matrix
template <typename datatype>
Matrix<datatype> Matrix<datatype>::Identity() {
    
    if (this->IsNum()) {
        Matrix<datatype> k(1,1);
        k.Ones();
        return k;
    }
    
    if (rows != cols)
        throw SizeException("Matrix must be square to have an identity matrix");

    Matrix<datatype> k(rows,rows);

    for (size_t a = 0; a < rows; a++)
        for (size_t b = 0; b < cols; b++)
            k.M[a * cols + b] = (a==b);
    
    k._isZero = false;
    
    return k;
}

    //exponential of a matrix (element-wise)
template <typename datatype>
Matrix<datatype> exp(const Matrix<datatype>& A){

    size_t zeros = UNDEFINED;
    Matrix<datatype> E(A.Rows(), A.Cols());
    
    for (size_t a = 0; a < A.Rows(); a++)
        for (size_t b = 0; b < A.Cols(); b++) {
            E.M[a * (A.Cols()) + b] = exp(A.M[a * (A.Cols()) + b]);
            CheckZero(&zeros, E.M[a * (A.Cols()) + b]);
        }
    
    if (zeros == ZERO)
        E._isZero = true;
    
    return E;
}


    //raise a matrix to power of 2
template <typename datatype>
Matrix<datatype> sqr(const Matrix<datatype>& A) {
    
    if (A.rows != A.cols)
        throw SizeException("Matrix must be square to be raised to power of 2");
    else
        return A * A;
}

template <typename datatype>
Matrix<datatype>& Matrix<datatype>::Prettify() {
    this->prettified=true;
    return (*this);
}


    // generate a random number
template <typename datatype>
double Matrix<datatype>::_Random(long min, long max) {
    
#if __cplusplus > 199711L
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    
    return dis(gen);
#else
    return static_cast<double>(min) + static_cast<double>(rand()) / static_cast<double>(RAND_MAX/(max - min));
#endif
}

    // fill a matrix with a constant number
template <typename datatype>
Matrix<datatype>& Matrix<datatype>::FillWith(datatype num) {
    if (num == 0) {
        this->Zeros();
        return *this;
    } else if (num == 1) {
        this->Ones();
        return *this;
    }
    
    for (size_t a = 0; a < rows; ++a)
        for (size_t b = 0; b < cols; ++b)
            M[a * cols + b] = num;
    
    this->_isZero = false;
    
    return *this;
}


    // fill a matrix with random numbers
template <typename datatype>
Matrix<datatype>& Matrix<datatype>::Random(long min, long max) {
    size_t zeros = UNDEFINED;
    this->_isZero = false;
    for (size_t a = 0; a < rows; ++a)
        for (size_t b = 0; b < cols; ++b) {
            M[a * cols + b] = static_cast<datatype>(_Random(min, max));
            CheckZero(&zeros, M[a * cols + b]);
        }
    
    if (zeros == ZERO)
        this->_isZero = true;
    
    return *this;
}

template <typename datatype>
Matrix<datatype>& Matrix<datatype>::Zeros() {
    for (size_t a = 0; a < rows; ++a)
        for (size_t b = 0; b < cols; ++b)
            M[a * cols + b] = static_cast<datatype>(0.0);
    
    this->_isZero = true;
    return *this;
}

template <typename datatype>
Matrix<datatype>& Matrix<datatype>::Ones() {
    for (size_t a = 0; a < rows; ++a)
        for (size_t b = 0; b < cols; ++b)
            this->M[a * cols + b] = static_cast<datatype>(1.0);
    
    this->_isZero = false;
    return *this;
}

template <typename datatype>
Matrix<datatype>& Matrix<datatype>::FromData(const std::vector< std::vector<datatype> >& data) {
    this->_isZero = false;
    this->rows = data.size();
    this->cols = data[0].size();
    this->M.resize((this->rows) * (this->cols));
    
    size_t zeros = UNDEFINED;
    
    if ((data.size() == 1) && (data[0].size() == 1) && (!data[0][0]))
        this->_isZero = true;
    
    for (size_t a = 0; a < this->rows; ++a)
        for (size_t b = 0; b < this->cols; ++b) {
            this->M[a * (this->cols) + b] = data[a][b];
            CheckZero(&zeros, this->M[a * (this->cols) + b]);
        }
    
    this->prettified = false;
    
    if (zeros == ZERO)
        this->_isZero = true;
    
    return *this;
}

template <typename datatype>
Matrix<datatype>& Matrix<datatype>::FromData(const std::vector<datatype>& data) {
    this->rows = 1;
    this->cols = data.size();
    this->_isZero = false;
    this->M.assign(data.begin(), data.end());
    
    if ((data.size() == 1) && (!data[0])) this->_isZero = true;
    
    this->prettified = false;
    
    return *this;
}

    //fill a matrix with data from a file
template <typename datatype>
Matrix<datatype>& Matrix<datatype>::FromFile(const std::string fname) {
    std::ifstream f;
    f.open(fname.c_str());
//    prettified = false, _isZero = true;
    if (! f.is_open())
        throw FileException();
    std::string line;
    cols = rows = 0;
    prettified = false, _isZero = false;
    M.clear();

    size_t columns, zeros = UNDEFINED;
    this->_isZero = false;
    while (std::getline(f, line)) {
        columns = 0;
        line = rtrim(line);
        if (! line.length())
            break;
        
        double value;
        std::istringstream ss(line);

        while (ss >> value) {
            M.push_back(value);
            CheckZero(&zeros, value);
            ++columns;
        }
        
        ++rows, cols = columns;
    }
    
    if (zeros == ZERO)
        this->_isZero = true;
    
    f.close();
    return *this;
}

template <typename datatype>
void Matrix<datatype>::Reshape(size_t rows, size_t cols) {
    if (!rows || !cols)
        throw SizeException("Invalid shape");
    
    if (this->rows == rows && this->cols == cols) return; //nothing to do here
    
    std::vector<double>::iterator it;
    
    if (rows == 1 && cols == 1) {
        this->M.resize(1);
        goto done;
    } else if (rows == 2 && cols == 2) {
        this->M.resize(4);
        goto done;
    } else if (rows == 3 && cols == 3) {
        this->M.resize(9);
        goto done;
    }
    
        // The simplest case: just resize the array
        // (either losing data either inserting zeros)
    if (this->rows != rows)
        this->M.resize(rows * (this->cols));
    
    this->rows = rows;
    
    it = this->M.begin();
    
        // Now a bit trickier: it's time to deal with
        // data that is located elsewhere in the array
    if (this->cols > cols) {
        for (size_t r = 0; r < this->rows; ++r) {
            this->M.erase(it + cols, it + this->cols);
            it += cols;
        }
    } else if (this->cols < cols) {
        for (size_t r = 0; r < this->rows; ++r) {
            this->M.insert(it + this->cols, cols - this->cols, 0);
            it += cols;
        }
    }
    
    this->cols = cols;
    
done:
    this->rows = rows, this->cols = cols;
    return;
}

template <typename datatype>
Matrix<datatype>& Matrix<datatype>::clear() {
    this->M.clear();
    this->M.push_back((datatype)0);
    this->rows = this->cols = 1;
    
    this->_isZero = true;
    
    return *this;
}