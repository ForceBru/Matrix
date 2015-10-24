//
//  Matrix.hpp
//
//  Created by ForceBru on 11.10.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <random>

#include "Exceptions.hpp"


class Matrix {
public:
    Matrix();
    Matrix(long rows, long cols);
    ~Matrix();
    
    void FillRandom(long min=0, long max=RAND_MAX);
    void FillZero();
    void Reshape(long rows, long cols);
    Matrix T();
    long Rows() {return this->rows;}
    long Cols() {return this->cols;}
    Matrix Transpose() {return this->T();}
    Matrix Identity();

    friend Matrix exp(Matrix);
    friend Matrix operator/(int left, Matrix right);
    friend Matrix operator/(Matrix& left, Matrix& right);
    
    Matrix& operator=(const Matrix& m);
    Matrix operator+(const Matrix& right) const;
    Matrix operator+(const int& right) const;
    Matrix operator+=(const Matrix& right);
    Matrix operator-() const;
    Matrix operator-(const Matrix& right) const;
    Matrix operator-=(const Matrix& right);
    Matrix operator*(const Matrix& right);
    Matrix operator*(const int& right) const;
    Matrix operator/(const int& right) const;
    Matrix operator/(const Matrix& right) const;
    bool operator==(const Matrix& m) {
        long a,b;
        if (this->rows!=m.rows || this->cols != m.cols) return false;
        for (a=0;a<rows;++a)
            for (b=0;b<cols;++b)
                if (this->M[a][b]!=m.M[a][b]) return false;
        return true;
    }
    
    inline bool operator!=(const Matrix& m) {
        return !(*this==m);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Matrix& obj){
        os << "\n\tRows: " << obj.rows<<" cols: "<<obj.cols<<"\n";
        long a,b;
        os << std::fixed << std::setprecision(3);
        for (a=0; a<obj.rows; ++a) {
            for (b=0; b<obj.cols; ++b) os << (obj.M)[a][b] << " ";
            os << "\n";
        }
        os << std::endl;
        return os;
    }
private:
    double Random(long min=0, long max=RAND_MAX);
    double Mult_Row_by_Column(std::vector<double>row, std::vector<double> col, long size);
    long rows, cols;
        //'M' is a vector of vectors that holds all the values
    std::vector< std::vector<double> > M, _Transposed, _Identity;
    std::vector<double> _t;
};

inline Matrix operator+(int left, Matrix& right) {
    return right+left;
}

inline Matrix operator+(int left, Matrix right) {
    return right+left;
}

inline Matrix operator*(int left, Matrix& right) {
    return left*right;
}

inline Matrix operator/(int left, Matrix right) {
    if (right.rows != right.cols)
        throw SizeException("Size mismatch while substracting matrices!");
    
    Matrix ret=right;
    long a, b;
    for (a=0; a<right.rows; ++a)
        for (b=0; b<right.cols; ++b)
            ret.M[a][b]=(double)left/right.M[a][b];
    return ret;
}

inline Matrix operator/(Matrix& left, Matrix& right) {
    if (left.cols!=right.cols || left.rows!=right.rows)
        throw SizeException("Size mismatch while dividing matrices");
    
    long a,b;
    Matrix res=left;
    for (a=0; a<left.rows; ++a)
        for (b=0; b<left.cols; ++b) {
            res.M[a][b]=left.M[a][b]/right.M[a][b];
        }
    return res;
}

Matrix exp(Matrix);

#endif /* Matrix_hpp */
