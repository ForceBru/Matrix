//
//  operators.cpp
//
//  Created by ForceBru on 02.11.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//

#include <iostream>
#include "Matrix.hpp"
#include "util_ocl.hpp"


    // append number to a matrix (element-wise)
Matrix Matrix::operator+(const double& right) const {
    
    if (right == 0.0) return *this;
    
    Matrix ret = *this;
    
    for (size_t a = 0; a < rows; ++a)
        for (size_t b = 0; b < cols; ++b)
            ret.M[a * cols + b] += right;
    
    return ret;
}

    // add matrix to another matrix
Matrix operator+ (const Matrix& left, const Matrix& right) {
    if (left.rows != right.rows || left.cols != right.cols)
        throw SizeException("Size mismatch while adding matrices!");
    
    Matrix ret = left;
    
#ifdef HAVE_OPENCL
    if (Matrix::oclEnabled && (left.rows < 10) && (left.cols < 10)) {
#endif
        
    for (size_t a = 0; a < left.rows; ++a)
        for (size_t b = 0; b < left.cols; ++b)
            ret.M[a * left.cols + b] += right.M[a * left.cols + b];
        
#ifdef HAVE_OPENCL
    } else {
        double *data = new double[left.M.size()]();
        cl_int write_err = CL_SUCCESS, err = CL_SUCCESS;
        
        cl::Buffer _left = cl::Buffer::Buffer(Matrix::context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, left.M.size() * sizeof(double), (void *)left.M.data(), &write_err);
        
        if (check_cl_err(write_err)) {
            std::cerr << "[!] Failed to allocate buffer, computation failed!" << std::endl;
            return ret;
        } write_err = CL_SUCCESS;
        
        cl::Buffer _right = cl::Buffer::Buffer(Matrix::context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, left.M.size() * sizeof(double), (void *)right.M.data(), &write_err);
        
        if (check_cl_err(write_err)) {
            std::cerr << "[!] Failed to allocate buffer, computation failed!" << std::endl;
            return ret;
        } write_err = CL_SUCCESS;
        
        cl::Buffer _out = cl::Buffer::Buffer(Matrix::context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, left.M.size() * sizeof(double), (void *)data, &write_err);
        
        if (check_cl_err(write_err)) {
            std::cerr << "[!] Failed to allocate buffer, computation failed!" << std::endl;
            return ret;
        } write_err = CL_SUCCESS;
        
        
        cl::Kernel kernel(Matrix::add, "Matrix_add", &err);
        
        if (check_cl_err(err)) {
            std::cerr << "[!] Failed to init kernel, computation failed!" << std::endl;
            return ret;
        } err = CL_SUCCESS;
        
        kernel.setArg(0, _left), kernel.setArg(1, _right), kernel.setArg(2, _out), kernel.setArg(3, left.rows), kernel.setArg(4, left.cols);
        
        cl::Event add_done;
        
#ifdef SLOW
        err = Matrix::queue.enqueueTask(kernel, NULL, &add_done);
#else
        err = Matrix::queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(left.rows, left.cols), cl::NullRange, NULL, &add_done);
#endif
        
        if (check_cl_err(err)) {
            std::cerr << "[!] Failed to run task, computation failed!" << std::endl;
            return ret;
        } err = CL_SUCCESS;
        
        add_done.wait();
        
        err = Matrix::queue.enqueueReadBuffer(_out, CL_TRUE, 0, left.M.size() * sizeof(double), data);
        
        if (check_cl_err(err)) {
            std::cerr << "[!] Failed to read result, computation failed!" << std::endl;
            return ret;
        } err = CL_SUCCESS;
        
        Matrix::queue.finish();
        
        
            //ret.M.assign(data, data + left.M.size());
        ret.M = std::vector<double>(data, data + left.M.size());
        
        delete[] data;
    }
#endif
    return ret;
}


Matrix& Matrix::operator+=(const Matrix& right) {
    if (rows != right.rows || cols != right.cols)
	throw SizeException("Size mismatch while adding matrices!");
    
#ifdef HAVE_OPENCL
    if (Matrix::oclEnabled && ((rows < 10) || (cols < 10))) {
#endif
    
    for (size_t a = 0; a < rows; ++a)
        for (size_t b = 0; b < cols; ++b)
            this->M[a * cols + b] += right.M[a * cols + b];
        
#ifdef HAVE_OPENCL
    } else {
        *this = *this + right;
    }
#endif
    return *this;
}

    //invert sign of elements of given matrix (element-wise)
Matrix Matrix::operator-() const{
    return (*this) * (-1);
}


    // substract a number from a matrix
Matrix Matrix::operator- (const double& right) const {
    if (right == 0.0) return *this;
    
    Matrix ret = *this;
    
        
    for (size_t a = 0; a < rows; ++a)
        for (size_t b = 0; b < cols; ++b)
            ret.M[a * cols + b] -= right;
        
    
    return ret;
}

    //substract a matrix from another matrix
Matrix  operator- (const Matrix& left, const Matrix& right){
    if (left.rows != right.rows || left.cols != right.cols)
        throw SizeException("Size mismatch while substracting matrices!");
    
    Matrix ret(left.rows, left.cols);
    
#ifdef HAVE_OPENCL
    if (Matrix::oclEnabled && ((left.rows < 10) || (left.cols < 10))) {
#endif
    
    for (size_t a = 0; a < left.rows; ++a)
        for (size_t b = 0; b < left.cols; ++b)
            ret.M[a * left.cols + b] -= right.M[a * left.cols + b];
        
#ifdef HAVE_OPENCL
    } else {
        double *data = new double[left.M.size()]();
        cl_int write_err = CL_SUCCESS, err = CL_SUCCESS;
        
        cl::Buffer _left = cl::Buffer::Buffer(Matrix::context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, left.M.size() * sizeof(double), (void *)left.M.data(), &write_err);
        
        if (check_cl_err(write_err)) {
            std::cerr << "[!] Failed to allocate buffer, computation failed!" << std::endl;
            return ret;
        } write_err = CL_SUCCESS;
        
        cl::Buffer _right = cl::Buffer::Buffer(Matrix::context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, left.M.size() * sizeof(double), (void *)right.M.data(), &write_err);
        
        if (check_cl_err(write_err)) {
            std::cerr << "[!] Failed to allocate buffer, computation failed!" << std::endl;
            return ret;
        } write_err = CL_SUCCESS;
        
        cl::Buffer _out = cl::Buffer::Buffer(Matrix::context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, left.M.size() * sizeof(double), (void *)data, &write_err);
        
        if (check_cl_err(write_err)) {
            std::cerr << "[!] Failed to allocate buffer, computation failed!" << std::endl;
            return ret;
        } write_err = CL_SUCCESS;
        
        
        cl::Kernel kernel(Matrix::sub, "Matrix_sub", &err);
        
        if (check_cl_err(err)) {
            std::cerr << "[!] Failed to init kernel, computation failed!" << std::endl;
            return ret;
        } err = CL_SUCCESS;
        
        kernel.setArg(0, _left), kernel.setArg(1, _right), kernel.setArg(2, _out), kernel.setArg(3, left.rows), kernel.setArg(4, left.cols);
        
        cl::Event sub_done;
        
#ifdef SLOW
        err = Matrix::queue.enqueueTask(kernel, NULL, &sub_done);
#else
        err = Matrix::queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(left.rows, left.cols), cl::NullRange, NULL, &sub_done);
#endif
        
        if (check_cl_err(err)) {
            std::cerr << "[!] Failed to run task, computation failed!" << std::endl;
            return ret;
        } err = CL_SUCCESS;
        
        sub_done.wait();
        
        err = Matrix::queue.enqueueReadBuffer(_out, CL_TRUE, 0, left.M.size() * sizeof(double), data);
        
        if (check_cl_err(err)) {
            std::cerr << "[!] Failed to read result, computation failed!" << std::endl;
            return ret;
        } err = CL_SUCCESS;
        
        Matrix::queue.finish();
        
        
            //ret.M.assign(data, data + left.M.size());
        ret.M = std::vector<double>(data, data + left.M.size());
        
        delete[] data;
    }
#endif
    return ret;
}

Matrix& Matrix::operator-=(const Matrix& right) {
    if (rows != right.rows || cols != right.cols)
        throw SizeException("Size mismatch while substracting matrices!");
    
#ifdef HAVE_OPENCL
    if (Matrix::oclEnabled && ((right.rows < 10) || (right.cols < 10))) {
#endif
        
    for (size_t a = 0; a < rows; ++a)
        for (size_t b = 0; b < cols; ++b)
            this->M[a * cols + b] -= right.M[a * cols + b];
        
#ifdef HAVE_OPENCL
    } else {
        *this = *this - right;
    }
#endif
    
    return *this;
}

    //divide a number by a matrix (element-wise)

Matrix operator/(const double d, const Matrix& mat) {
    Matrix ret(mat.rows, mat.cols);
    
    for (size_t a = 0; a < mat.rows; ++a)
        for (size_t b = 0; b < mat.cols; ++b)
            ret.M[a * (mat.cols) + b] = d / mat.M[a * (mat.cols) + b];
    
    return ret;
}

    //divide a matrix by a number (element-wise)

Matrix Matrix::operator/(const double& right) const{
    Matrix res(rows, cols);
    
    for (size_t a = 0; a < rows; ++a)
        for (size_t b = 0; b < cols; ++b)
            res.M[a * cols + b] = (this->M[a * cols + b]) / right;
    
    return res;
}

    //divide a matrix by a number (element-wise)
Matrix& Matrix::operator/=(const double& right) {
    
    for (size_t a = 0; a < rows; ++a)
        for (size_t b = 0; b < cols; ++b)
            (this->M[a * cols + b]) /= right;
    
    return *this;
}


    //calculate Hadamard product: this (*) right -> element-wise multiplication
Matrix Matrix::Hadamard(const Matrix& right) const {
    if (cols != right.cols || rows != right.rows)
	throw SizeException("Size mismatch while caclulating Hadamard product");

    Matrix res(rows, cols);
    
    for (size_t a = 0; a < rows; ++a)
        for (size_t b = 0; b < cols; ++b)
            res.M[a * cols + b] = (this->M[a * cols + b]) * right.M[a * cols + b];

    return res;
}


    // multiply a matrix by another matrix
Matrix Matrix::operator*(const Matrix& right) const {
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

    Matrix res(rows, right.cols);
    
    
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
    
#ifdef HAVE_OPENCL
    if (Matrix::oclEnabled && ((rows < 10) || (right.cols < 10))) {
#endif
        
    size_t b,c;
    for (a = 0; a < rows; ++a) {
        for (b = 0; b < right.cols; ++b) {
            double tmp;
            for (c = 0, tmp = 0.0; c < cols; ++c)
                tmp += M[a * cols + c] * right.M[c * right.cols + b];
            res.M[a * right.cols + b] = tmp;
        }
    }
        
#ifdef HAVE_OPENCL
    } else {
        cl_int write_err = CL_SUCCESS;
        double *data = new double[rows * right.cols]();
            // CL_MEM_COPY_HOST_PTR
        cl::Buffer _left = cl::Buffer(Matrix::context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, this->M.size() * sizeof(double), (void *)this->M.data(), &write_err);
        
        if (check_cl_err(write_err)) {
            std::cerr << "[!] Failed to create buffer, computation failed!" << std::endl;
            return res;
        }
        write_err = CL_SUCCESS;
        
        cl::Buffer _right = cl::Buffer(Matrix::context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, right.M.size() * sizeof(double), (void *)right.M.data(), &write_err);
        
        if (check_cl_err(write_err)) {
            std::cerr << "[!] Failed to create buffer, computation failed!" << std::endl;
            return res;
        }
        write_err = CL_SUCCESS;
        
        cl::Buffer _out = cl::Buffer(Matrix::context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, rows * right.cols * sizeof(double), data, &write_err);
        
        if (check_cl_err(write_err)) {
            std::cerr << "[!] Failed to create buffer, computation failed!" << std::endl;
            return res;
        }
        write_err = CL_SUCCESS;
        
        cl_int err = CL_SUCCESS;
        cl::Kernel kernel(Matrix::mult, "Matrix_mult", &err);
        
        if (check_cl_err(err)) {
            std::cerr << "\n[!] Failed to create kernel, computation failed!" << std::endl;
            return res;
        } err = CL_SUCCESS;
        
        kernel.setArg(0, _left), kernel.setArg(1, _right), kernel.setArg(2, _out), kernel.setArg(3, right.rows), kernel.setArg(4, rows), kernel.setArg(5, right.cols), kernel.setArg(6, cols);
        
        cl::Event mult_done;
        
#ifdef SLOW
        err = Matrix::queue.enqueueTask(kernel, NULL, &mult_done);
#else
        err = Matrix::queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(rows, right.cols), cl::NullRange, NULL, &mult_done);
#endif
        
        if (check_cl_err(err)) {
            std::cerr << "[!] Failed to run kernel, computation failed!" << std::endl;
            return res;
        } err = CL_SUCCESS;
        
        mult_done.wait();
        
        
        err = Matrix::queue.enqueueReadBuffer(_out, CL_TRUE, 0, rows * right.cols * sizeof(double), data);
        
        if (check_cl_err(err)) {
            std::cerr << "[!] Failed to read data from GPU, computation failed!" << std::endl;
            return res;
        } err = CL_SUCCESS;
        
        Matrix::queue.finish();
        
        
            //res.M.assign(data, data + rows * right.cols);
        res.M = std::vector<double>(data, data + rows * right.cols);
        
        delete[] data;
    }
#endif

    return res;
}


    // multiply a matrix by a number
Matrix Matrix::operator*(const double& right) const{
    Matrix res(rows, cols);
    
    for (size_t a = 0; a < res.rows; ++a)
        for (size_t b = 0; b < res.cols; ++b)
            res.M[a * cols + b] = (this->M[a * cols + b])*right;
    
    return res;
}


    // assign a matrix to another matrix
Matrix& Matrix::operator=(const Matrix& mat) {
    if (this != &mat) {
        this->rows = mat.rows;
        this->cols = mat.cols;
        (this->M).assign(mat.M.begin(), mat.M.end());
        this->Reshape(this->rows, this->cols);
        this->prettified=false;
    }

    return *this;
}

    //get a row of a matrix or its element
Matrix& Matrix::operator[](const size_t i) const {
    
    static Matrix ret;
    
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