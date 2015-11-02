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

    //default constructor constructs an ordinary number
Matrix::Matrix() {
    this->rows=this->cols=1;
    this->M.resize(rows);
    this->M[0].resize(cols);
    this->_Identity.resize(rows);
    this->_Identity[0].resize(cols);
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

    //transpose a matrix
Matrix Matrix::T() {
    Matrix tmp(this->cols, this->rows);
    long a,b;
    for (a=0; a<cols; ++a)
        for (b=0; b<rows; ++b)
            tmp.M[a][b]=this->M[b][a];
    return tmp;
}

    //return identity matrix
Matrix Matrix::Identity() {
    if (this->rows != this->cols)
        throw SizeException("Matrix must be square to have an identity matrix");

    long a, b, c;
    this->_Identity.resize(rows);
    for (a=0;a<rows;++a) this->_Identity[a].resize(cols);
    for (a=0, c=0; a< this->rows; a++, c++)
        for (b=0; b<this->cols; b++)
            this->_Identity[a][b]=(b==c)?1:0;
    
    Matrix k(rows,rows);
    k.M=this->_Identity;
    
    return k;
}

    //exponential of a matrix (element-wise)
Matrix exp(Matrix A){
    long k, i;
    Matrix E(A.Rows(), A.Cols());
    
    for (k=0; k<A.Rows(); k++)
        for (i = 0; i < A.Cols(); i++)
            E.M[k][i]=exp(A.M[k][i]);
    return E;
}


    //raise a matrix to power of 2
Matrix Matrix::sqr() {
    if (rows!=cols)
        throw SizeException("Matrix must be square to be raised to power of 2");
    else
        return (*this)*(*this);
}


    // generate a random number
double Matrix::Random(long min, long max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    
    return dis(gen);
}

void Matrix::FillRandom(long min, long max){
    long a,b;
    for (a=0;a<rows;++a)
        for (b=0;b<cols;++b)
            M[a][b]=Random(min, max);
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
        for (; this->rows<rows; this->rows++)
            this->M[this->rows].resize(cols);
    }
    if (this->cols > cols) {
        long a;
        for (a=0; a<this->rows; ++a)
            M[a].resize(cols);
        this->cols=cols;
    } else if (this->cols<cols) {
        long a;
        for (a=0; a<this->rows; a++)
            this->M[a].resize(cols);
        this->cols=cols;
    }
}