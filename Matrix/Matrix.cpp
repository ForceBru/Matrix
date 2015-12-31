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
    this->M.resize(1);
    this->M.reserve(4);
    this->prettified=false;
}

    //construct a matrix of size rows x cols
Matrix::Matrix(long rows, long cols) {
    this->rows = rows, this->cols = cols;
    this->M.resize(rows*cols);
    this->prettified=false;
}

Matrix::Matrix(const std::vector<double>& data) {
    this->FromData(data);
}

Matrix::Matrix(const std::vector< std::vector<double> >& data) {
    this->FromData(data);
}

Matrix::Matrix(const std::string fname) {
    if (!this->FromFile(fname)) {
        this->rows = this->cols = 1;
        this->M.resize(1);
        this->M.reserve(4);
        this->prettified=false;
    }
}

    //transpose a matrix
Matrix Matrix::T() {
    
    if (this->IsNum())
        return *this;
    
    Matrix tmp(cols, rows);
    
    for (size_t a = 0; a < cols; ++a)
        for (size_t b = 0; b < rows; ++b)
            tmp.M[a * rows + b] = this->M[b * cols + a];
    
    return tmp;
}

    //return identity matrix
Matrix Matrix::Identity() {
    
    if (this->IsNum()) {
        Matrix k(1,1);
        k.Ones();
        return k;
    }
    
    if (rows != cols)
        throw SizeException("Matrix must be square to have an identity matrix");

    Matrix k(rows,rows);

    for (size_t a = 0; a < rows; a++)
        for (size_t b = 0; b < cols; b++)
            k.M[a * cols + b] = (a==b);
    
    return k;
}

    //exponential of a matrix (element-wise)
Matrix exp(const Matrix& A){

    Matrix E(A.Rows(), A.Cols());
    
    for (size_t a = 0; a < A.Rows(); a++)
        for (size_t b = 0; b < A.Cols(); b++)
            E.M[a * (A.Cols()) + b] = exp(A.M[a * (A.Cols()) + b]);
    
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

    // fill a matrix with a constant number
void Matrix::FillWith(double num) {
    if (num == 0) {
        this->Zeros();
        return;
    } else if (num == 1.0) {
        this->Ones();
        return;
    }
    
    for (size_t a = 0; a < rows; ++a)
        for (size_t b = 0; b < cols; ++b)
            M[a * cols + b] = num;
}

    // fill a matrix with random numbers
void Matrix::Random(long min, long max) {
    for (size_t a = 0; a < rows; ++a)
        for (size_t b = 0; b < cols; ++b)
            M[a * cols + b] = _Random(min, max);
}

void Matrix::Zeros() {
    for (size_t a = 0; a < rows; ++a)
        for (size_t b = 0; b < cols; ++b)
            M[a * cols + b]=0.0;
}

void Matrix::Ones() {
    for (size_t a = 0; a < rows; ++a)
        for (size_t b = 0; b < cols; ++b)
            this->M[a * cols + b] = 1.0;
}

void Matrix::FromData(const std::vector< std::vector<double> >& data) {
    this->rows=data.size();
    this->cols=data[0].size();
    this->M.resize((this->rows)*(this->cols));
    for (size_t a = 0; a < this->rows; ++a)
        for (size_t b = 0; b < this->cols; ++b)
            this->M[a * (this->cols) + b]=data[a][b];

    this->prettified=false;
}

void Matrix::FromData(const std::vector<double>& data) {
    this->rows=1;
    this->cols=data.size();
    this->M.assign(data.begin(), data.end());
    this->prettified=false;
}

    //fill a matrix with data from a file
int Matrix::FromFile(const std::string fname) {
    std::ifstream f;
    f.open(fname.c_str());
    prettified=false;
    if (!f.is_open())
        throw FileException();
    std::string line;
    cols=rows=0;
    M.clear();

    size_t columns;
    while (std::getline(f, line)) {
        columns=0;
        line=rtrim(line);
        if (! line.length())
            break;
        
        double value;
        std::istringstream ss(line);

        while (ss >> value) {
            M.push_back(value);
            ++columns;
        }
        
        ++rows, cols=columns;
    }
    f.close();
    return 1;
}


void Matrix::Reshape(size_t rows, size_t cols) {
    if (!rows || !cols)
        throw SizeException("Invalid shape");
    
    if (this->rows==rows && this->cols==cols) return; //nothing to do here
    
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
    
    this->rows=rows;
    
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
    
    this->cols=cols;
    
done:
    this->rows = rows, this->cols = cols;
    return;
}