//
//  operators.cpp
//
//  Created by ForceBru on 02.11.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//

#include <stdio.h>

//#include "Matrix.hpp"


    // append number to a matrix (element-wise)
template <typename datatype>
Matrix<datatype> Matrix<datatype>::operator+(const double& right) const {
    
    if (right == 0.0) return *this;
    
    Matrix ret = *this;
    
    size_t a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            ret.M[a * cols + b] += right;
    
    return ret;
}

    // append matrix to another matrix
template <typename argtype1, typename argtype2>
Matrix<argtype1> operator+ (const Matrix<argtype1>& left, const Matrix<argtype2>& right){
    if (left.rows != right.rows || left.cols != right.cols)
        throw SizeException("Size mismatch while adding matrices!");
    
    Matrix<argtype1> ret = left;
    size_t a, b;
    for (a = 0; a < left.rows; ++a)
        for (b = 0; b < left.cols; ++b)
            ret.M[a * left.cols + b] += right.M[a * left.cols + b];
    return ret;
}

template <typename datatype>
Matrix<datatype>& Matrix<datatype>::operator+=(const Matrix<datatype>& right) {
    if (rows != right.rows || cols != right.cols)
	throw SizeException("Size mismatch while adding matrices!");
    
    size_t a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            this->M[a * cols + b] += right.M[a * cols + b];
    return *this;
}

    //invert sign of elements of given matrix (element-wise)
template <typename datatype>
Matrix<datatype> Matrix<datatype>::operator-() const{
    return (*this) * (-1);
}

template <typename datatype>
Matrix<datatype>  Matrix<datatype>::operator- (const double& right) const {
    if (right == 0.0) return *this;
    
    Matrix ret = *this;
    
    size_t a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            ret.M[a * cols + b] -= right;
    
    return ret;
}

    //substract a matrix from another matrix
template <typename argtype1, typename argtype2>
Matrix<argtype1>  operator- (const Matrix<argtype1>& left, const Matrix<argtype2>& right){
    if (left.rows != right.rows || left.cols != right.cols)
        throw SizeException("Size mismatch while substracting matrices!");
    
    Matrix<argtype1> ret;
    
    size_t a, b;
    for (a = 0; a < left.rows; ++a)
        for (b = 0; b < left.cols; ++b)
            ret.M[a * left.cols + b] -= right.M[a * left.cols + b];
    return ret;
}

template <typename datatype>
Matrix<datatype>& Matrix<datatype>::operator-=(const Matrix<datatype>& right) {
    if (rows != right.rows || cols != right.cols)
	throw SizeException("Size mismatch while substracting matrices!");
    
    size_t a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            this->M[a * cols + b] -= right.M[a * cols + b];
    return *this;
}

    //divide a number by a matrix (element-wise)
template <typename datatype>
Matrix<datatype> operator/(const datatype d, const Matrix<datatype>& mat) {
    Matrix<datatype> ret(mat.rows, mat.cols);
    size_t a, b;
    
    for (a = 0; a < mat.rows; ++a)
        for (b = 0; b < mat.cols; ++b)
            ret.M[a * (mat.cols) + b] = d / mat.M[a * (mat.cols) + b];
    
    return ret;
}

    //divide a matrix by a number (element-wise)
template <typename datatype>
Matrix<datatype> Matrix<datatype>::operator/(const datatype& right) const{
    Matrix<datatype> res(rows, cols);
    
    size_t a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            res.M[a * cols + b] = (this->M[a * cols + b]) / right;
    
    return res;
}

    //divide a matrix by a number (element-wise)
template <typename datatype>
Matrix<datatype>& Matrix<datatype>::operator/=(const datatype& right) {
    size_t a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            (this->M[a * cols + b]) /= right;
    
    return *this;
}


    //calculate Hadamard product: this (*) right -> element-wise multiplication
template <typename datatype>
Matrix<datatype> Matrix<datatype>::Hadamard(const Matrix<datatype>& right) const {
    if (cols != right.cols || rows != right.rows)
	throw SizeException("Size mismatch while caclulating Hadamard product");

    Matrix<datatype> res(rows, cols);
    
    size_t a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            res.M[a * cols + b] = (this->M[a * cols + b]) * right.M[a * cols + b];

    return res;
}


    // multiply a matrix by another matrix
template <typename datatype>
Matrix<datatype> Matrix<datatype>::operator*(const Matrix<datatype>& right) const {
    if (cols != right.rows) {
        std::string msg=std::string("Size mismatch while multiplying matrices: ")
            .append(to_string(rows))
            .append("X")
            .append(to_string(cols)
        );
        
        msg.append(" vs ")
            .append(to_string(right.rows))
            .append("X")
            .append(to_string(right.cols)
        );
        
        throw SizeException(msg);
    }
    
    if (right.IsNum())
        return this->operator*(right.M[0]);
    
    
    size_t a;

    Matrix<datatype> res(rows, right.cols);
    
    
    if (right.IsCol()) {
        for (a = 0; a < cols; ++a)
            res.M[0] += M[a] * right.M[a];
        return res;
    } else if (this->IsSquare(2) && right.IsSquare(2)) {
            // loop unrolling for 2x2 matrices
        res.M[0] = M[0] * right.M[0] + M[1] * right.M[2],
        res.M[1] = M[0] * right.M[1] + M[1] * right.M[3],
        res.M[2] = M[2] * right.M[0] + M[3] * right.M[2],
        res.M[3] = M[2] * right.M[1] + M[3] * right.M[3];
        
        return res;
    }
    
    size_t b, c;

    for (a = 0; a < rows; ++a) {
        for (b = 0; b < right.cols; ++b) {
            datatype tmp;
            for (c = 0, tmp = static_cast<datatype>(0); c < cols; ++c)
                tmp += M[a * cols + c] * right.M[c * right.cols + b];
            res.M[a * right.cols + b] = tmp;
        }
    }

    return res;
}


    // multiply a matrix by a number
template <typename datatype>
Matrix<datatype> Matrix<datatype>::operator*(const datatype& right) const{
    Matrix<datatype> res(rows, cols);
    
    for (size_t a = 0; a < res.rows; ++a)
        for (size_t b = 0; b < res.cols; ++b)
            res.M[a * cols + b] = (this->M[a * cols + b])*right;
    return res;
}


    // assign a matrix to another matrix
template <typename datatype>
Matrix<datatype>& Matrix<datatype>::operator=(const Matrix<datatype>& mat) {
    if (this != &mat) {
        this->rows = mat.rows;
        this->cols = mat.cols;
        (this->M).assign(mat.M.begin(), mat.M.end());
            //this->Reshape(this->rows, this->cols);
        this->prettified=false;
    }

    return *this;
}

    //get a row of a matrix or its element
template <typename datatype>
Matrix<datatype>& Matrix<datatype>::operator[](const size_t i) const {
    
    static Matrix<datatype> ret;
    
    if (rows != 1) {
        if (i == rows)
            throw SizeException("Index out of range");
        
        ret.Reshape(1, cols);
	
        for (size_t a = 0; a < cols; ++a) ret.M[a] = this->M[i * cols + a];
    } else {
        if (i == cols)
            throw SizeException("Index out of range");
        
        ret.Reshape(1, 1);
        ret.M[0] = this->M[i];
    }
    
	return ret;
}