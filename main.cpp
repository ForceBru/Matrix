//
//  main.cpp
//
//  Created by ForceBru on 03.10.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//


#include <iostream>

#include "Matrix.hpp"

using namespace std;

Matrix sigmoid(Matrix& z){
    return 1.0 / (1.0 + exp(-z));
}

int main(int argc, const char * argv[]) {
    
    srand((unsigned int)time(NULL));
    
        //create some matrices of size (rows, columns)
    Matrix a(3,4);
    Matrix aHat;
    Matrix b(4,2);
    Matrix c(3,2);
    
        //fill matrices with random values
    a.FillRandom(0,1);
    aHat = a;
    b.FillRandom(0,1);
    
        //outputting is easy
    cout << "A:\n" << a << endl;
    cout << "B:\n" << b << endl;
    
    try {
            //multiply two matrices (of appropriate size!)
        cout << "Multiplying matrices (A*B)..." << endl;
        c = a * b;
        cout << c << endl;
        
    } catch (const SizeException& e){
            //exception is thrown if the matrices are not of the appropriate size
        cout << "Caught exception: " << e.what() << endl;
    }
    
    try {
            //add two matrices easily
        cout << " Adding matrices..." << endl;
        aHat += a;
            //and then substract
        aHat -= a;
        
            //now aHat should be equal to a
        if (aHat != a) cout << "That's an error!" << endl;
        else cout << "Test passed" << endl;
    } catch (const SizeException& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    
        //'c' was 3x2, now make it 2x2 by removing the last row (other rows are kept)
    c.Reshape(2, 3);
    
    
    try {
            //transpose a matrix
        cout << " Transposing matrix A:" << endl;
        cout << a.T() << endl; //or a.Transpose()
    } catch (const SizeException& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    
        //change shape of matrix (3 rows, 3 columns)
    a.Reshape(3, 3);
    
    try {
        cout << " Identity matrix of A after reshaping to (3, 3) is" << endl;
        cout << a.Identity() << endl;
    } catch (const SizeException& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    
    try {
            //square a matrix
        cout << " Raising matrix A to power of 2:" << endl;
        cout << a.sqr() << endl;
    } catch (const SizeException& e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    try {
        a.FillRandom(0,1);
        cout << " Matrix A:"<< endl;
        cout << a << endl;
        cout << " Matrix -A:"<< endl;
        cout << -a << endl;
        cout << " exp(A) is" << endl;
        cout << exp(a) << endl;
    } catch (const SizeException& e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    
    try {
        cout << " First row of matrix A:" << endl;
        cout << a[0] << endl;
    } catch (const SizeException& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    
    try {
        cout << " First element of the first row of matrix A:" << endl;
        cout << a[0][0] << endl;
    } catch (const SizeException& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    
    try {
        cout << " Applying sigmoid function to A:" << endl;
        cout << sigmoid(a) << endl;
    } catch (const SizeException& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    
    return 0;
}
