//
//  operators.cpp
//
//  Created by ForceBru on 02.11.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//

#include <stdio.h>

#include "Matrix.hpp"

    // multiply a row of one matrix by a column of another matrix
double Matrix::Mult_Row_by_Column(std::vector<double> row, std::vector<double> col, long size) {
    double res; long a;
    for (a = 0, res = 0; a < size; ++a)
        res += row[a] * col[a];
    return res;
}

    //append double to a matrix (element-wise)
Matrix Matrix::operator+(const double& right) const {
    Matrix ret = *this;
    
    long a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            ret.M[a][b] += right;
    return ret;
}

    //append matrix to another matrix
Matrix Matrix::operator+(const Matrix& right) const{
    if (rows != right.rows || cols != right.cols)
        throw SizeException("Size mismatch while adding matrices!");
    
    Matrix ret = *this;
    long a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            ret.M[a][b] += right.M[a][b];
    return ret;
}

Matrix Matrix::operator+=(const Matrix& right) {
    if (rows != right.rows || cols != right.cols)
        throw SizeException("Size mismatch while adding matrices!");
    
    long a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            this->M[a][b] += right.M[a][b];
    return *this;
}

    //invert sign of elements of given matrix (element-wise)
Matrix Matrix::operator-() const{
    return (*this) * (-1);
}

    //substract a matrix from another matrix
Matrix Matrix::operator-(const Matrix& right) const{
    if (rows != right.rows || cols != right.cols)
        throw SizeException("Size mismatch while substracting matrices!");
    
    Matrix ret = *this;
    long a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            ret.M[a][b] -= right.M[a][b];
    return ret;
}

Matrix Matrix::operator-=(const Matrix& right) {
    if (rows != right.rows || cols != right.cols)
        throw SizeException("Size mismatch while substracting matrices!");
    
    long a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            this->M[a][b] -= right.M[a][b];
    return *this;
}

    //divide a number by a matrix (element-wise)
Matrix operator/(const double a, const Matrix& b) {
    Matrix ret(b.rows, b.cols);
    long i, j;
    
    for (i = 0; i < b.rows; ++i)
        for (j = 0; j < b.cols; ++j)
            ret.M[i][j] = a / b.M[i][j];
    
    return ret;
}


    // multiply a matrix by another matrix
Matrix Matrix::operator*(const Matrix& right) {
    if (cols != right.rows)
        throw SizeException("Size mismatch while multiplying matrices");
    
    long a, b, c, d;
    Matrix res(rows, right.cols);
    if (_t.size() != cols) _t.resize(cols);
    for (a=0; a<rows; ++a)
        for (b = 0, d = 0; b < cols && d < right.cols; ++b, ++d) {
            for (c = 0; c < cols; ++c) _t[c] = right.M[c][d];
            res.M[a][b] = Mult_Row_by_Column(this->M[a], _t, cols);
        }
    return res;
}


    // multiply a matrix by a double
Matrix Matrix::operator*(const double& right) const{
    Matrix res(rows, cols);
    
    long a,b;
    for (a = 0; a < res.rows; ++a)
        for (b = 0; b < res.cols; ++b)
            res.M[a][b] = (this->M[a][b])*right;
    return res;
}


    // assign a matrix to another matrix
Matrix& Matrix::operator=(Matrix const& m) {
    if (this != &m) {
        this->rows = m.rows;
        this->cols = m.cols;
        this->M = m.M;
        this->Reshape(this->rows, this->cols);
    }
    return *this;
}

    //get a row of a matrix or its element
Matrix Matrix::operator[](const int i) {
    if (rows != 1) {
        if (i < 0 || i == rows)
            throw SizeException("Index out of range");
        
        Matrix ret(1, cols);
        long a;
        
        for (a = 0; a < cols; ++a) ret.M[0][a] = this->M[i][a];
        
        return ret;
    } else {
        if (i < 0 || i == cols)
            throw SizeException("Index out of range");
        
        Matrix ret(1,1);
        ret.M[0][0] = this->M[0][i];
        
        return ret;
    }
}