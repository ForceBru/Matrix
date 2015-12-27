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
    this->rows = this->cols = 1;
    this->M.resize(rows);
    this->M[0].resize(cols);
    this->prettified=false;
}

    //construct a matrix of size rows x cols
Matrix::Matrix(long rows, long cols) {
    long a;
    this->rows = rows, this->cols = cols;
    this->M.resize(rows);
    for (a = 0; a < rows; ++a) this->M[a].resize(cols);
    this->prettified=false;
}

Matrix::Matrix(const std::vector<double>& data) {
    this->FromData(data);
}

Matrix::Matrix(const std::vector< std::vector<double> >& data) {
    this->FromData(data);
}

Matrix::Matrix(std::string fname) {
    if (!this->FromFile(fname)) {
        this->rows = this->cols = 1;
        this->M.resize(rows);
        this->M[0].resize(cols);
        this->prettified=false;
    }
}

    //transpose a matrix
Matrix Matrix::T() {
    Matrix tmp(cols, rows);
    long a, b;
    for (a = 0; a < cols; ++a) {
        for (b = 0; b < rows; ++b)
            tmp.M[a][b] = this->M[b][a];
    }
    return tmp;
}

    //return identity matrix
Matrix Matrix::Identity() {
    if (rows != cols)
        throw SizeException("Matrix must be square to have an identity matrix");

    Matrix k(rows,rows);
    size_t a, b;
    for (a = 0; a < rows; a++) {
        for (b = 0; b < cols; b++)
            k.M[a][b] = (a==b)?1:0;
    }
    return k;
}

    //exponential of a matrix (element-wise)
Matrix exp(const Matrix& A){
    long k, i;
    Matrix E(A.Rows(), A.Cols());
    
    for (k = 0; k < A.Rows(); k++)
        for (i = 0; i < A.Cols(); i++)
            E.M[k][i] = exp(A.M[k][i]);
    return E;
}


    //raise a matrix to power of 2
Matrix sqr(const Matrix& A) {
    if (A.rows != A.cols)
        throw SizeException("Matrix must be square to be raised to power of 2");
    else
        return A * A;
}

Matrix& Matrix::Prettify() {
    this->prettified=true;
    return (*this);
}


    // generate a random number
double Matrix::_Random(long min, long max) {
#if __cplusplus > 199711L
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    
    return dis(gen);
#else
    return static_cast<double>(min) + static_cast<double>(rand()) / static_cast<double>(RAND_MAX/(max - min));
#endif
}

    //fill a matrix with random numbers
void Matrix::Random(long min, long max) {
    long a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            M[a][b] = _Random(min, max);
}

void Matrix::Zeros() {
    long a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            M[a][b]=0.0;
}

void Matrix::Ones() {
    long a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            this->M[a][b] = 1.0;
}

void Matrix::FromData(const std::vector< std::vector<double> >& data) {
    this->rows=data.size();
    this->cols=data[0].size();
    this->M.assign(data.begin(), data.end());
    this->prettified=false;
}

void Matrix::FromData(const std::vector<double>& data) {
    this->rows=1;
    this->cols=data.size();
    this->M.resize(1);
    this->M[0].assign(data.begin(), data.end());
    this->prettified=false;
}

    //fill a matrix with data from a file
int Matrix::FromFile(std::string fname) {
    std::ifstream f;
    f.open(fname.c_str());
    prettified=false;
    if (!f.is_open())
        throw FileException();
    std::string line;
    cols=rows=0;
    M.clear();

    while (std::getline(f, line)) {
        line=rtrim(line);
        if (! line.length())
            break;
        
        double value;
        std::istringstream ss(line);
        M.push_back(std::vector<double>());
        while (ss >> value) {
            (M.back()).push_back(value);
        }
        ++rows, cols=M.end()->size();
    }
    rows=M.size(), cols=M[0].size();
    f.close();
    return 1;
}


void Matrix::Reshape(long rows, long cols) {
    if (this->rows==rows && this->cols==cols) return; //no need to do anything here
    if (this->rows > rows) {
        M.resize(rows);
    } else if (this->rows<rows) {
        this->M.resize(rows);
        for (; this->rows<rows; this->rows++)
            this->M[this->rows].resize(cols);
    }
    if (this->cols > cols) {
        long a;
        for (a=0; a<this->rows; ++a)
            M[a].resize(cols);
    } else if (this->cols<cols) {
        long a;
        for (a=0; a<this->rows; a++)
            this->M[a].resize(cols);
    }
    this->rows=this->M.size(), this->cols=this->M[0].size();
}