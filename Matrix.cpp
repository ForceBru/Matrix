//
//  Matrix.cpp
//
//  Created by ForceBru on 11.10.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//


#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "Matrix.hpp"

Matrix::Matrix() {
    this->rows=this->cols=0;
}

Matrix::Matrix(long rows, long cols) {
    long a;
    this->rows=rows, this->cols=cols;
    this->M.resize(rows);
    for (a=0;a<rows;++a) this->M[a].resize(cols);
    if (this->rows==this->cols) {
        this->_Identity.resize(rows);
        for (a=0;a<rows;++a) this->_Identity[a].resize(cols);
    }
}

Matrix::~Matrix() {
    long a;
    for (a=0; a<rows; a++) std::vector<double>(M[a]).swap(M[a]);
    std::vector< std::vector<double> >(M).swap(M);
    std::vector<double>(_t).swap(_t);
}

Matrix Matrix::T() {
    Matrix tmp(this->cols, this->rows);
    long a,b;
    for (a=0; a<cols; ++a)
        for (b=0; b<rows; ++b)
            tmp.M[a][b]=this->M[b][a];
    return tmp;
}

Matrix Matrix::Identity() {
    if (this->rows != this-> cols) {
        throw SizeException("Matrix must be square to have an identity matrix");
        return Matrix();
    }
    long a, b, c;
    this->_Identity.resize(rows);
    for (a=0;a<rows;++a) this->_Identity[a].resize(cols);
    for (a=0, c=0; a< this->rows; a++, c++) {
        for (b=0; b<this->cols; b++) {
            if (b==c) this->_Identity[a][b]=1.0;
            else this->_Identity[a][b]=0.0;
        }
    }
    Matrix k(rows,rows);
    k.M=this->_Identity;
    
    return k;
}

    // multiply a row of one matrix by a column of another matrix
double Matrix::Mult_Row_by_Column(std::vector<double> row, std::vector<double> col, long size) {
    double res; long a;
    for (a=0, res=0; a<size; ++a)
        res+=row[a]*col[a];
    return res;
}

Matrix Matrix::operator+(const Matrix& right) {
    if (this->rows != right.rows || this->cols != right.cols)
        throw SizeException("Size mismatch while adding matrices!");
    
    Matrix ret=*this;
    long a, b;
    for (a=0; a<rows; ++a)
        for (b=0; b<cols; ++b)
            ret.M[a][b]+=right.M[a][b];
    return ret;
}

Matrix Matrix::operator+=(const Matrix& right) {
    if (this->rows != right.rows || this->cols != right.cols)
        throw SizeException("Size mismatch while adding matrices!");
    
    long a, b;
    for (a=0; a<rows; ++a)
        for (b=0; b<cols; ++b)
            this->M[a][b]+=right.M[a][b];
    return *this;
}

Matrix Matrix::operator-(const Matrix& right) {
    if (this->rows != right.rows || this->cols != right.cols)
        throw SizeException("Size mismatch while substracting matrices!");
    
    Matrix ret=*this;
    long a, b;
    for (a=0; a<rows; ++a)
        for (b=0; b<cols; ++b)
            ret.M[a][b]-=right.M[a][b];
    return ret;
}

Matrix Matrix::operator-=(const Matrix& right) {
    if (this->rows != right.rows || this->cols != right.cols)
        throw SizeException("Size mismatch while substracting matrices!");
    
    long a, b;
    for (a=0; a<rows; ++a)
        for (b=0; b<cols; ++b)
            this->M[a][b]-=right.M[a][b];
    return *this;
}


    // multiply a matrix by another matrix
Matrix Matrix::operator*(const Matrix& right) {
    if (cols!=right.rows)
        throw SizeException("Size mismatch while multiplying matrices");
    
    long a,b,c,d;
    Matrix res(rows,right.cols);
    if (_t.size()!=cols) _t.resize(cols);
    for (a=0; a<rows; ++a)
        for (b=0,d=0; b<cols && d<right.cols; ++b, ++d) {
            for (c=0; c<cols; ++c) _t[c]=right.M[c][d];
            res.M[a][b]=Mult_Row_by_Column(this->M[a],_t,cols);
        }
    return res;
}


    // multiply a matrix by an integer
Matrix Matrix::operator*(const int& right) {
    Matrix res(rows,cols);
    
    long a,b;
    for (a=0; a<res.rows; a++)
        for (b=0; b<res.cols; b++)
            res.M[a][b]=(this->M[a][b])*right;
    return res;
}

Matrix Matrix::operator/(const int& right) {
    return (*this)*(1.0/(double)right);
}


    // assign a matrix to another matrix
Matrix& Matrix::operator=(Matrix const& m) {
    if (this!=&m) {
        this->rows=m.rows;
        this->cols=m.cols;
        this->M=m.M;
        this->Reshape(this->rows, this->cols);
    }
    return *this;
}


    // generate a random number
double Matrix::Random() {
    return (double)rand()/(double)10000000;//RAND_MAX;
}

void Matrix::FillRandom(){
    long a,b;
    for (a=0;a<rows;++a)
        for (b=0;b<cols;++b)
            M[a][b]=Random();
}

void Matrix::FillZero(){
    long a,b;
    for (a=0;a<rows;++a)
        for (b=0;b<cols;++b)
            M[a][b]=0;
}

void Matrix::Reshape(long rows, long cols) {
    if (this->rows==rows && this->cols==cols) return; //no need to do anything here
    if (this->rows > rows) {
        M.resize(rows);
        this->rows=rows;
    } else if (this->rows<rows) {
        this->M.resize(rows);
        for (; this->rows<rows; this->rows++) {
            this->M[this->rows].resize(cols);
        }
    }
    if (this->cols > cols) {
        long a;
        for (a=0; a<this->rows; ++a) {
            M[a].resize(cols);
        }
        this->cols=cols;
    } else if (this->cols<cols) {
        long a;
        for (a=0; a<this->rows; a++) {
            this->M[a].resize(cols);
        }
        this->cols=cols;
    }
}