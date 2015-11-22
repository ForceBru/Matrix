//
//  Tests.cpp
//  Matrix
//
//  Created by ForceBru on 21.11.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//

#include "Tests.hpp"

namespace Tests {
    Matrix sigmoid(Matrix& z){ return 1.0 / (1.0 + exp(-z)); }
    
    string S(int num) {
        ++tests.success;
        return string("[+] Success: ").append(to_string(tests.success)).append(" out of ").append(to_string(number_of_tests)).append("\n\n");
    }
    string F(int num) {
        ++tests.failed;
        return string("[!] Failed: ").append(to_string(tests.failed)).append(" out of ").append(to_string(number_of_tests)).append("\n\n");
    }
    
void Test(void) {
    
    Tests::tests.names[0]="Filling and assigning";
    Tests::tests.names[1]="Outputting";
    Tests::tests.names[2]="Matrix multiplication";
    Tests::tests.names[3]="Adding and substracting";
    Tests::tests.names[4]="Reshaping";
    Tests::tests.names[5]="Transposing";
    Tests::tests.names[6]="Calculating identity matrix";
    Tests::tests.names[7]="Squaring matrix";
    Tests::tests.names[8]="Exponentiation";
    Tests::tests.names[9]="Accessing data";
    Tests::tests.names[10]=Tests::tests.names[9];
    Tests::tests.names[11]="Vectorization";
    Tests::tests.names[12]="Filling from file";
    
        //create some matrices of size (rows, columns)
    Matrix a(3, 4), aHat, b(4, 2), c(3, 2);
    
    cout << "\n\t\tRUNNING " << number_of_tests << " TESTS...\n" << endl;
    
    cout << "\tTest " << Tests::tests.N+1 << ": " << Tests::tests.names[Tests::tests.N] << '\n' << endl;
    try {
            //fill matrices with random values
        a.Random(0, 1);
        b.Random(0, 1);
        cout << Tests::S(Tests::tests.N++) << endl;
    } catch (exception& e) {
        cout << Tests::F(Tests::tests.N++) << e.what() << endl;
    }
    
    cout << "\tTest " << Tests::tests.N+1 << ": " << Tests::tests.names[Tests::tests.N] << '\n' << endl;
    try {
            //outputting is easy
        cout << "Matrix A:\n" << a << endl;
        cout << "Matrix B:\n" << b.Prettify() << endl;
        cout << Tests::S(Tests::tests.N++) << endl;
    } catch (exception& e) {
        cout << Tests::F(Tests::tests.N++) << e.what() << endl;
    }
    
    cout << "\tTest " << Tests::tests.N+1 << ": " << Tests::tests.names[Tests::tests.N] << '\n' << endl;
    try {
            //multiply two matrices (of appropriate size!)
        cout << "Multiplying matrices (A*B)..." << endl;
        c = a * b;
        cout << c << endl;
        cout << Tests::S(Tests::tests.N++) << endl;
    } catch (const SizeException& e){
            //exception is thrown if the matrices are not of the appropriate size
        cout << Tests::F(Tests::tests.N++) << e.what() << endl;
    }
    
    cout << "\tTest " << Tests::tests.N+1 << ": " << Tests::tests.names[Tests::tests.N] << '\n' << endl;
    try {
            //add two matrices easily
        cout << " Adding matrices..." << endl;
        aHat = a;
        aHat += a;
            //and then substract
        aHat -= a;
        
        cout << aHat << endl << "must be equal to\n\n" << a << endl;
            //now aHat should be equal to a
        if (aHat != a) cout << Tests::F(Tests::tests.N++) << endl;
        else cout << Tests::S(Tests::tests.N++) << endl;
    } catch (const SizeException& e) {
        cout << Tests::F(Tests::tests.N++) << e.what() << endl;
    }
    
    cout << "\tTest " << Tests::tests.N+1 << ": " << Tests::tests.names[Tests::tests.N] << '\n' << endl;
    try {
            //'c' was 3x2, now make it 2x2 by removing the last row (other rows are kept)
        c.Reshape(2, 2);
        cout << Tests::S(Tests::tests.N++) << endl;
    } catch(...) {
        cout << Tests::F(Tests::tests.N++) << endl;
    }
    
    cout << "\tTest " << Tests::tests.N+1 << ": " << Tests::tests.names[Tests::tests.N] << '\n' << endl;
    try {
            //transpose a matrix
        cout << " Transposing matrix A:" << endl;
        cout << a.T() << endl; //or a.Transpose()
        cout << Tests::S(Tests::tests.N++) << endl;
    } catch (const SizeException& e) {
        cout << Tests::F(Tests::tests.N++) << e.what() << endl;
    }
    
        //change shape of matrix (3 rows, 3 columns)
    a.Reshape(3, 3);
    
    cout << "\tTest " << Tests::tests.N+1 << ": " << Tests::tests.names[Tests::tests.N] << '\n' << endl;
    try {
        cout << " Identity matrix of A after reshaping to (3, 3) is" << endl;
        cout << a.Identity() << endl;
        cout << Tests::S(Tests::tests.N++) << endl;
    } catch (const SizeException& e) {
        cout << Tests::F(Tests::tests.N++) << e.what() << endl;
    }
    
    cout << "\tTest " << Tests::tests.N+1 << ": " << Tests::tests.names[Tests::tests.N] << '\n' << endl;;
    try {
            //square a matrix
        cout << " Raising matrix A to power of 2:" << endl;
        cout << a.sqr() << endl;
        cout << Tests::S(Tests::tests.N++) << endl;
    } catch (const SizeException& e) {
        cout << Tests::F(Tests::tests.N++) << e.what() << endl;
    }
    
    cout << "\tTest " << Tests::tests.N+1 << ": " << Tests::tests.names[Tests::tests.N] << '\n' << endl;
    try {
        a.Random(0,1);
        cout << " Matrix A:"<< endl;
        cout << a << endl;
        cout << " exp(A) is" << endl;
        cout << exp(a) << endl;
        cout << Tests::S(Tests::tests.N++) << endl;
    } catch (const SizeException& e) {
        cout << Tests::F(Tests::tests.N++) << e.what() << endl;
    }
    
    cout << "\tTest " << Tests::tests.N+1 << ": " << Tests::tests.names[Tests::tests.N] << '\n' << endl;
    try {
        cout << " First row of matrix A:" << endl;
        cout << a[0] << endl;
        cout << Tests::S(Tests::tests.N++) << endl;
    } catch (const SizeException& e) {
        cout << Tests::F(Tests::tests.N++) << e.what() << endl;
    }
    
    cout << "\tTest " << Tests::tests.N+1 << ": " << Tests::tests.names[Tests::tests.N] << '\n' << endl;
    try {
        cout << " First element of the first row of matrix A:" << endl;
        cout << a[0][0] << endl;
        cout << Tests::S(Tests::tests.N++) << endl;
    } catch (const SizeException& e) {
        cout << Tests::F(Tests::tests.N++) << e.what() << endl;
    }
    
    cout << "\tTest " << Tests::tests.N+1 << ": " << Tests::tests.names[Tests::tests.N] << '\n' << endl;
    try {
        cout << " Applying sigmoid function to A:" << endl;
        cout << Tests::sigmoid(a) << endl;
        cout << Tests::S(Tests::tests.N++) << endl;
    } catch (const SizeException& e) {
        cout << Tests::F(Tests::tests.N++) << e.what() << endl;
    }
    
    
        // --- Testing filling from file
    cout << "\tTest " << Tests::tests.N+1 << ": " << Tests::tests.names[Tests::tests.N] << '\n' << endl;
    {
        Matrix a(2, 3), b(5, 3);
        a.Random(0, 1), b.Random(1, 2);
        
        ofstream f("matrix_a.txt"), g("matrix_b.txt");
        
        f << a; g << b;
        
        f.close(), g.close();
        
        Matrix C, D;
        C.FromFile("matrix_a.txt"), D.FromFile("matrix_b.txt");
        
        if ((C==a) && (D==b))
            cout << Tests::S(Tests::tests.N++) << endl;
        else {
            cout << Tests::F(Tests::tests.N++) << endl;
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
    cout << "Succeeded: " << Tests::tests.success << " out of " << Tests::tests.N;
    if (Tests::tests.success == Tests::tests.N) cout << "\t(Great!)" << endl;
    else cout << endl;
    cout << "Failed: " << Tests::tests.failed << " out of " << Tests::tests.N;
    if (Tests::tests.failed)
        cout << "Please see which tests exactly have failed and contact the developer" << endl;
    else cout << endl;
    cout << "\nTests finished\n\n";
}
}