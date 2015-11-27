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
    this->modified=true, this->prettified=false;
}

    //construct a matrix of size rows x cols
Matrix::Matrix(long rows, long cols) {
    long a;
    this->rows = rows, this->cols = cols;
    this->M.resize(rows);
    for (a = 0;a < rows; ++a) this->M[a].resize(cols);
    this->modified=true, this->prettified=false;
}

    //transpose a matrix
Matrix Matrix::T() {
    Matrix tmp(cols, rows);
    if (modified) {
        long a, b;
        _Transposed.resize(cols);
        for (a = 0; a < cols; ++a) {
            _Transposed[a].resize(rows);
            for (b = 0; b < rows; ++b)
                _Transposed[a][b]=this->M[b][a];
        }
    }
    tmp.M=_Transposed;
    modified=false;
    return tmp;
}

    //return identity matrix
Matrix Matrix::Identity() {
    if (rows != cols)
        throw SizeException("Matrix must be square to have an identity matrix");

    Matrix k(rows,rows);
    if (modified) {
        long a, b, c;
        _Identity.resize(rows);
        for (a = 0, c = 0; a < rows; a++, c++) {
            _Identity[a].resize(cols);
            for (b = 0; b < cols; b++)
                _Identity[a][b] = (b==c)?1:0;
        }
    }
    k.M=_Identity;
    modified=false;
    return k;
}

    //exponential of a matrix (element-wise)
Matrix exp(Matrix A){
    long k, i;
    Matrix E(A.Rows(), A.Cols());
    
    for (k = 0; k < A.Rows(); k++)
        for (i = 0; i < A.Cols(); i++)
            E.M[k][i] = exp(A.M[k][i]);
    return E;
}


    //raise a matrix to power of 2
Matrix Matrix::sqr() {
    if (rows!=cols)
        throw SizeException("Matrix must be square to be raised to power of 2");
    else
        return (*this) * (*this);
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
    modified=true;
}

void Matrix::Zeroes() {
    long a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            M[a][b]=0.0;
    modified=true;
}

void Matrix::Ones() {
    long a, b;
    for (a = 0; a < rows; ++a)
        for (b = 0; b < cols; ++b)
            this->M[a][b] = 1.0;
    modified=true;
}

    //fill a matrix with data from a file
int Matrix::FromFile(std::string fname) {
    std::ifstream f;
    f.open(fname.c_str());
    modified=prettified=false;
    if (!f.is_open())
        return -1;
    std::string line;
    cols=rows=0;
    M.clear();
    char *end;
    while (std::getline(f, line)) {
        std::vector<double> tmp;

        while (line.size()) {
            tmp.push_back(std::strtod(line.c_str(), &end));
            line.assign(std::string(end));
        }
        
        if (rows!=0 && tmp.size()!=cols) {
            modified=true;
            f.close();
            return 0;
        }
        M.push_back(tmp);
        ++rows, cols=tmp.size();
    }
    rows=M.size(), cols=M[0].size();
    f.close();
    modified=true;
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
    modified=true;
}