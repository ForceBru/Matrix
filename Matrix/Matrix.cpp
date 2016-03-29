//
//  Matrix.cpp
//
//  Created by ForceBru on 11.10.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>

#include "Matrix.hpp"
#include "util_ocl.hpp"

#ifdef HAVE_OPENCL
bool   Matrix::oclEnabled = false;
cl::CommandQueue Matrix::queue;
cl::Context Matrix::context;
cl::Program Matrix::add, Matrix::sub, Matrix::mult;
#endif

    //default constructor constructs an ordinary number
Matrix::Matrix(): rows(1), cols(1), _isZero(1), prettified(0) {
    this->M.resize(1);
    this->M.reserve(4);
}

    //construct a matrix of size rows x cols
Matrix::Matrix(size_t rows, size_t cols): rows(rows), cols(cols), _isZero(1), prettified(0) {
    this->M.resize(rows * cols);
}

Matrix::Matrix(const std::vector<double>& data) {
    this->FromData(data);
}


Matrix::Matrix(const std::vector< std::vector<double> >& data) {
    this->FromData(data);
}


Matrix::Matrix(const std::string fname) {
    if (! this->FromFile(fname)) {
        this->rows = this->cols = 1;
        this->M.resize(1);
        this->M.reserve(4);
        this->_isZero = 0;
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
    
    k._isZero = false;
    
    return k;
}

    //exponential of a matrix (element-wise)
Matrix exp(const Matrix& A){

    size_t zeros = UNDEFINED;
    Matrix E(A.Rows(), A.Cols());
    
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
Matrix& Matrix::FillWith(double num) {
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
Matrix& Matrix::Random(const size_t min, const size_t max) {
    size_t zeros = UNDEFINED;
    this->_isZero = false;
    for (size_t a = 0; a < rows; ++a)
        for (size_t b = 0; b < cols; ++b) {
            M[a * cols + b] = double(_Random(min, max));
            CheckZero(&zeros, M[a * cols + b]);
        }
    
    if (zeros == ZERO)
        this->_isZero = true;
    
    return *this;
}

Matrix& Matrix::Zeros() {
    for (size_t a = 0; a < rows; ++a)
        for (size_t b = 0; b < cols; ++b)
            M[a * cols + b] = double(0.0);
    
    this->_isZero = true;
    return *this;
}


Matrix& Matrix::Ones() {
    for (size_t a = 0; a < rows; ++a)
        for (size_t b = 0; b < cols; ++b)
            this->M[a * cols + b] = double(1.0);
    
    this->_isZero = false;
    return *this;
}


Matrix& Matrix::FromData(const std::vector< std::vector<double> >& data) {
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


Matrix& Matrix::FromData(const std::vector<double>& data) {
    this->rows = 1;
    this->cols = data.size();
    this->_isZero = false;
    this->M.assign(data.begin(), data.end());
    
    if ((data.size() == 1) && (!data[0])) this->_isZero = true;
    
    this->prettified = false;
    
    return *this;
}

    //fill a matrix with data from a file
Matrix& Matrix::FromFile(const std::string fname) {
    std::ifstream f;
    f.open(fname.c_str());

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


void Matrix::Reshape(size_t rows, size_t cols) {
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

#ifdef HAVE_OPENCL
bool Matrix::initOpenCL(std::string add_src, std::string sub_src, std::string mult_src) {
    cl_int err = CL_SUCCESS;
    std::vector<cl::Platform> platforms;
    std::vector<cl::Device>   devices;
    
    cl::Platform::get(&platforms);
    
    if (platforms.empty()) return 0;
    
    for (auto plat: platforms) {
        std::vector<cl::Device> GPUS;
        plat.getDevices(CL_DEVICE_TYPE_GPU, &GPUS);
        devices.insert(devices.end(), GPUS.begin(), GPUS.end());
    }
    
    if (devices.empty()) return 0;
    
    Matrix::context = cl::Context(devices, NULL, NULL, NULL, &err);
    if (check_cl_err(err)) return 0;
    
    Matrix::queue   = cl::CommandQueue(Matrix::context, 0, &err);
    if (check_cl_err(err)) return 0;
    
    std::ifstream add_file, sub_file, mult_file;
    
    add_file.open(add_src);
    sub_file.open(sub_src);
    mult_file.open(mult_src);
    
    if ((! add_file.good()) || (! mult_file.good()) || (! sub_file.good())) {
        std::cerr << "[!] Error opening source files!" << std::endl;
       return 0;
    }
    
    std::string   add_source(std::istreambuf_iterator<char>(add_file),(std::istreambuf_iterator<char>()));
    std::string   sub_source(std::istreambuf_iterator<char>(sub_file),(std::istreambuf_iterator<char>()));
    std::string   mult_source(std::istreambuf_iterator<char>(mult_file),(std::istreambuf_iterator<char>()));
    
    add_file.close(), sub_file.close(), mult_file.close();
    
    
    cl::Program::Sources _add = cl::Program::Sources(1, std::make_pair(add_source.c_str(), add_source.length()+1));
    cl::Program::Sources _sub = cl::Program::Sources(1, std::make_pair(sub_source.c_str(), sub_source.length()+1));
    cl::Program::Sources _mult = cl::Program::Sources(1, std::make_pair(mult_source.c_str(), mult_source.length()+1));
    
    
    Matrix::add = cl::Program(Matrix::context, _add);
    Matrix::sub = cl::Program(Matrix::context, _sub);
    Matrix::mult = cl::Program(Matrix::context, _mult);
    
    
    err = Matrix::add.build();
    
    if (check_cl_err(err)) {
        std::cerr << "[!] Error compiling kernel for addition!" << std::endl;
        return 0;
    }
    
    err = Matrix::sub.build();
    
    if (check_cl_err(err)) {
        std::cerr << "[!] Error compiling kernel for substraction!" << std::endl;
        return 0;
    }
    
    err = Matrix::mult.build();
    
    if (check_cl_err(err)) {
        std::cerr << "[!] Error compiling kernel for multiplication!" << std::endl;
        return 0;
    }
    
    Matrix::oclEnabled = true;
    
    return 1;
}
#else
constexpr bool Matrix::initOpenCL(std::string a, std::string b, std::string c) {
    return 0;
}
#endif


Matrix& Matrix::clear() {
    this->M.clear();
    this->M.push_back((double)0);
    this->rows = this->cols = 1;
    
    this->_isZero = true;
    
    return *this;
}