//
//  Tests.h
//  ANN
//
//  Created by Mia on 03.11.15.
//  Copyright © 2015 Mia. All rights reserved.
//

#ifndef Tests_h
#define Tests_h

#include <exception>
#include "Matrix.hpp"

#define number_of_tests 13
using namespace std;

struct {
    unsigned tests[number_of_tests], N, failed, success;
    string names[number_of_tests];
} tests={0,0,0,0,};

Matrix sigmoid(Matrix& z){
    return 1.0 / (1.0 + exp(-z));
}

string S(int num) {
    ++tests.success;
    return string("[+] Success: ").append(to_string(tests.success)).append(" out of ").append(to_string(number_of_tests)).append("\n\n");
}

string F(int num) {
    ++tests.failed;
    return string("[!] Failed: ").append(to_string(tests.failed)).append(" out of ").append(to_string(number_of_tests)).append("\n\n");
}

void Test(void) {
    
    tests.names[0]="Filling and assigning";
    tests.names[1]="Outputting";
    tests.names[2]="Matrix multiplication";
    tests.names[3]="Adding and substracting";
    tests.names[4]="Reshaping";
    tests.names[5]="Transposing";
    tests.names[6]="Calculating identity matrix";
    tests.names[7]="Squaring matrix";
    tests.names[8]="Exponentiation";
    tests.names[9]="Accessing data";
    tests.names[10]=tests.names[9];
    tests.names[11]="Vectorization";
    tests.names[12]="Filling from file";
    
        //create some matrices of size (rows, columns)
    Matrix a(3, 4), aHat, b(4, 2), c(3, 2);
    
    cout << "\n\t\tRUNNING " << number_of_tests << " TESTS...\n" << endl;
    
    cout << "\tTest " << tests.N+1 << ": " << tests.names[tests.N] << '\n' << endl;
    try {
            //fill matrices with random values
        a.Random(0, 1);
        b.Random(0, 1);
        cout << S(tests.N++) << endl;
    } catch (exception& e) {
        cout << F(tests.N++) << e.what() << endl;
    }
    
    cout << "\tTest " << tests.N+1 << ": " << tests.names[tests.N] << '\n' << endl;
    try {
            //outputting is easy
        cout << "Matrix A:\n" << a << endl;
        cout << "Matrix B:\n" << b << endl;
        cout << S(tests.N++) << endl;
    } catch (exception& e) {
        cout << F(tests.N++) << e.what() << endl;
    }
    
    cout << "\tTest " << tests.N+1 << ": " << tests.names[tests.N] << '\n' << endl;
    try {
            //multiply two matrices (of appropriate size!)
        cout << "Multiplying matrices (A*B)..." << endl;
        c = a * b;
        cout << c << endl;
        cout << S(tests.N++) << endl;
    } catch (const SizeException& e){
            //exception is thrown if the matrices are not of the appropriate size
        cout << F(tests.N++) << e.what() << endl;
    }
    
    cout << "\tTest " << tests.N+1 << ": " << tests.names[tests.N] << '\n' << endl;
    try {
            //add two matrices easily
        cout << " Adding matrices..." << endl;
        aHat = a;
        aHat += a;
            //and then substract
        aHat -= a;
        
        cout << aHat << endl << "must be equal to\n\n" << a << endl;
            //now aHat should be equal to a
        if (aHat != a) cout << F(tests.N++) << endl;
        else cout << S(tests.N++) << endl;
    } catch (const SizeException& e) {
        cout << F(tests.N++) << e.what() << endl;
    }
    
    cout << "\tTest " << tests.N+1 << ": " << tests.names[tests.N] << '\n' << endl;
    try {
            //'c' was 3x2, now make it 2x2 by removing the last row (other rows are kept)
        c.Reshape(2, 3);
        cout << S(tests.N++) << endl;
    } catch(...) {
        cout << F(tests.N++) << endl;
    }
    
    cout << "\tTest " << tests.N+1 << ": " << tests.names[tests.N] << '\n' << endl;
    try {
            //transpose a matrix
        cout << " Transposing matrix A:" << endl;
        cout << a.T() << endl; //or a.Transpose()
        cout << S(tests.N++) << endl;
    } catch (const SizeException& e) {
        cout << F(tests.N++) << e.what() << endl;
    }
    
        //change shape of matrix (3 rows, 3 columns)
    a.Reshape(3, 3);
    
    cout << "\tTest " << tests.N+1 << ": " << tests.names[tests.N] << '\n' << endl;
    try {
        cout << " Identity matrix of A after reshaping to (3, 3) is" << endl;
        cout << a.Identity() << endl;
        cout << S(tests.N++) << endl;
    } catch (const SizeException& e) {
        cout << F(tests.N++) << e.what() << endl;
    }
    
    cout << "\tTest " << tests.N+1 << ": " << tests.names[tests.N] << '\n' << endl;;
    try {
            //square a matrix
        cout << " Raising matrix A to power of 2:" << endl;
        cout << a.sqr() << endl;
        cout << S(tests.N++) << endl;
    } catch (const SizeException& e) {
        cout << F(tests.N++) << e.what() << endl;
    }
    
    cout << "\tTest " << tests.N+1 << ": " << tests.names[tests.N] << '\n' << endl;
    try {
        a.Random(0,1);
        cout << " Matrix A:"<< endl;
        cout << a << endl;
        cout << " exp(A) is" << endl;
        cout << exp(a) << endl;
        cout << S(tests.N++) << endl;
    } catch (const SizeException& e) {
        cout << F(tests.N++) << e.what() << endl;
    }
    
    cout << "\tTest " << tests.N+1 << ": " << tests.names[tests.N] << '\n' << endl;
    try {
        cout << " First row of matrix A:" << endl;
        cout << a[0] << endl;
        cout << S(tests.N++) << endl;
    } catch (const SizeException& e) {
        cout << F(tests.N++) << e.what() << endl;
    }
    
    cout << "\tTest " << tests.N+1 << ": " << tests.names[tests.N] << '\n' << endl;
    try {
        cout << " First element of the first row of matrix A:" << endl;
        cout << a[0][0] << endl;
        cout << S(tests.N++) << endl;
    } catch (const SizeException& e) {
        cout << F(tests.N++) << e.what() << endl;
    }
    
    cout << "\tTest " << tests.N+1 << ": " << tests.names[tests.N] << '\n' << endl;
    try {
        cout << " Applying sigmoid function to A:" << endl;
        cout << sigmoid(a) << endl;
        cout << S(tests.N++) << endl;
    } catch (const SizeException& e) {
        cout << F(tests.N++) << e.what() << endl;
    }
    
    
        // --- Testing filling from file
    cout << "\tTest " << tests.N+1 << ": " << tests.names[tests.N] << '\n' << endl;
    {
    Matrix a(2, 3), b(5, 3);
    a.Random(), b.Random();
    
    ofstream f("matrix_a.txt"), g("matrix_b.txt");
    
    f << a; g << b;
    
    f.close(), g.close();
    
    Matrix C, D;
    C.FromFile("matrix_a.txt"), D.FromFile("matrix_b.txt");
    
    if ((C==a) && (D==b))
        cout << S(tests.N++) << endl;
    else {
        cout << F(tests.N++) << endl;
        cout << a << "\n" << C << "\n" << b << "\n" << D << "\n";
        cout << "\n\n" << a.Rows() << ' ' << a.Cols() << " vs " << C.Rows() << ' ' << C.Cols() << endl;
        cout << b.Rows() << ' ' << b.Cols() << " vs " << D.Rows() << ' ' << D.Cols() << endl;
        long i,j;
        for (i = 0; i < a.Rows();++i)
            for (j = 0; j < a.Cols();++j)
                if (a[i][j] != C[i][j]) cout << "\nDifference: " << a[i][j] << " != " << C[i][j] << endl;
    }
    }
        // --- Testing filling from file
    
    cout << "\n\n\tSUMMARY:" << endl;
    cout << "Succeeded: " << tests.success << " out of " << tests.N << endl;
    cout << "Failed: " << tests.failed << " out of " << tests.N << endl;
    cout << "\nTests finished\n\n";
}

#endif /* Tests_h */
