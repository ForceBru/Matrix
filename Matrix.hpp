//
//  Matrix.hpp
//  ANN
//
//  Created by ForceBru on 11.10.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>

#include "Exceptions.hpp"


class Matrix {
public:
    Matrix(long rows, long cols);
    ~Matrix();
    
    void FillRandom();
    void FillZero();
    void Reshape(long rows, long cols);
    Matrix& operator=(const Matrix& m);
    Matrix operator*(const Matrix& right);
    Matrix operator*(const int& right);
    bool operator==(const Matrix& m) {
        long a,b;
        if (this->rows!=m.rows || this->cols != m.cols) return false;
        for (a=0;a<rows;++a)
            for (b=0;b<cols;++b)
                if (this->M[a][b]!=m.M[a][b]) return false;
        return true;
    }
    bool operator!=(const Matrix& m) {
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
    double Random();
    double Mult_Row_by_Column(std::vector<double>row, std::vector<double> col, long size);
    long rows, cols;
    std::vector< std::vector<double> > M, _tmp;
    std::vector<double> _t;
};

inline Matrix operator*(int left, Matrix& right) {
    return left*right;
}

#endif /* Matrix_hpp */
