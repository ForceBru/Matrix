//
//  operators.cpp
//
//  Created by ForceBru on 02.11.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//

#include <stdio.h>

#include "Matrix.hpp"



    // multiply a row of one matrix by a column of another matrix
double Matrix::Mult_Row_by_Column(Matrix row, Matrix col) {
    double res; long a;
    for (a = 0, res = 0; a < row.Cols(); ++a) {
        res += static_cast<double>(row[a]) * static_cast<double>(col[a]);
    }
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
    modified=true;
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
    modified=true;
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

    //divide a matrix by a number (element-wise)
Matrix Matrix::operator/(const double right) const{
    Matrix res(rows, cols);
    
    long a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            res.M[a][b] = (this->M[a][b]) / right;
    
    return res;
}

    //divide a matrix by a number (element-wise)
Matrix Matrix::operator/=(const double right) {
    long a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            (this->M[a][b]) /= right;
    
    return *this;
}


    //calculate Hadamard product: this (*) right -> element-wise multiplication
Matrix Matrix::Hadamard(const Matrix& right) const {
    if (cols != right.cols || rows != right.rows)
        throw SizeException("Size mismatch while caclulating Hadamard product");

    Matrix res(rows, cols);
    long a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            res.M[a][b] = (this->M[a][b]) * right.M[a][b];

    return res;
}


    // multiply a matrix by another matrix
Matrix Matrix::operator*(const Matrix& right) {
    if (cols != right.rows) {
        std::string msg=std::string("Size mismatch while multiplying matrices: ").append(to_string(rows).append(std::string("X")).append(to_string(cols)));
        msg.append(std::string(" vs ").append(to_string(right.rows)).append(std::string("X")).append(to_string(right.cols)));
        throw SizeException(msg);
    }
    
    long a, b, c, d;
    Matrix res(rows, right.cols), k(cols, 1);;
    for (a=0; a<rows; ++a)
        for (b = 0, d = 0; b < right.cols && d < right.cols; ++b, ++d) {
            for (c = 0; c < cols; ++c) k.M[c][0]=right.M[c][d];
            res.M[a][b] = Mult_Row_by_Column((*this)[a], k);
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
Matrix& Matrix::operator=(const Matrix& m) {
    if (this != &m) {
        this->rows = m.rows;
        this->cols = m.cols;
        (this->M).assign(m.M.begin(), m.M.end());
        this->Reshape(this->rows, this->cols);
        this->modified=true, this->prettified=false;
    }

    return *this;
}

    //get a row of a matrix or its element
Matrix& Matrix::operator[](const long i) {
    static Matrix ret;
    
    if (rows != 1) {
        if (i < 0 || i == rows)
            throw SizeException("Index out of range");
        
        ret.Reshape(1, cols);
        long a;
        
        for (a = 0; a < cols; ++a) ret.M[0][a] = this->M[i][a];
    } else {
        if (i < 0 || i == cols)
            throw SizeException("Index out of range");
        
        ret.Reshape(1, 1);
        ret.M[0][0] = this->M[0][i];
    }
    
    return ret;
}