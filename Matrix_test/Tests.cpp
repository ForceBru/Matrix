//
//  Tests.cpp
//  Matrix
//
//  Created by ForceBru on 21.11.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//

#include "Tests.hpp"

namespace Tests {
    
        //create some matrices of size (rows, columns)
    Matrix a(3, 4), aHat, b(4, 2), c(3, 2);
    
#define Stats cout << "\tTest " << Tests::tests.N+1 << ": " << Tests::tests.names[Tests::tests.N] << "\n\n";
    
    Matrix sigmoid(Matrix& z){ return 1.0 / (1.0 + exp(-z)); }
    
    string S(int num) {
        ++tests.success;
        return string("[+] Success: ").append(to_string(tests.success)).append(" out of ").append(to_string(number_of_tests)).append("\n\n");
    }
    string F(int num) {
        ++tests.failed;
        return string("[!] Failed: ").append(to_string(tests.failed)).append(" out of ").append(to_string(number_of_tests)).append("\n\n");
    }
    
    double Time() {
#if __cplusplus > 199711L
        using namespace std::chrono;
        
        high_resolution_clock::time_point _time;
        _time=high_resolution_clock::now();
        
        return duration_cast<milliseconds>(_time.time_since_epoch()).count()/1000.0;
#else
        time_t _time;
        _time=time(NULL);
        
        return static_cast<double>(_time);
#endif
    }
    
    void _FillRandom() {
        try {
                //fill matrices with random values
            a.Random();
            b.Random();
            cout << Tests::S(Tests::tests.N++) << endl;
        } catch (exception& e) {
            cout << Tests::F(Tests::tests.N++) << e.what() << endl;
        }
    }
    
    void _Output() {
        try {
                //outputting is easy
            cout << "Matrix A:\n" << a << endl;
            cout << "Matrix B:\n" << b.Prettify() << endl;
            cout << Tests::S(Tests::tests.N++) << endl;
        } catch (exception& e) {
            cout << Tests::F(Tests::tests.N++) << e.what() << endl;
        }
    }
    
    void _Multiply() {
        try {
                //multiply two matrices (of appropriate size!)
            cout << "Multiplying matrices ( A * B ) " << TIMES << " times, please wait...\n" << endl;
            unsigned long r;
            
            double start=Time();
            
            for (r=0; r<TIMES; ++r) {
                c = a * b;
            }
            
            
            cout << c << endl;
            
            cout << "Multiplied two matrices " << TIMES << " times in " << Time() - start << " seconds." << endl;
            cout << Tests::S(Tests::tests.N++) << endl;
        } catch (const SizeException& e){
                //exception is thrown if the matrices are not of the appropriate size
            cout << Tests::F(Tests::tests.N++) << e.what() << endl;
        }
    }
    
    void _AddSubstract() {
        try {
                //add two matrices easily
            cout << " Adding matrices..." << endl;
            aHat = a;
            aHat += a;
                //and then substract
            aHat -= a;
            
                //now aHat should be equal to a
            if (aHat != a) cout << Tests::F(Tests::tests.N++) << endl;
            else cout << Tests::S(Tests::tests.N++) << endl;
        } catch (const SizeException& e) {
            cout << Tests::F(Tests::tests.N++) << e.what() << endl;
        }
    }
    
    void _Reshape() {
        try {
                //'c' was 3x2, now make it 2x2 by removing the last row (other rows are kept)
            c.Reshape(2, 2);
            cout << Tests::S(Tests::tests.N++) << endl;
        } catch(...) {
            cout << Tests::F(Tests::tests.N++) << endl;
        }
    }
    
    void _Transpose() {
        try {
                //transpose a matrix
            cout << " Transposing matrix A:" << endl;
            cout << a.T() << endl; //or a.Transpose()
            cout << Tests::S(Tests::tests.N++) << endl;
        } catch (const SizeException& e) {
            cout << Tests::F(Tests::tests.N++) << e.what() << endl;
        }
    }
    
    void _Identity() {
            //change shape of matrix (3 rows, 3 columns)
        a.Reshape(3, 3);
        
        try {
            cout << " Identity matrix of A after reshaping to (3, 3) is" << endl;
            cout << a.Identity() << endl;
            cout << Tests::S(Tests::tests.N++) << endl;
        } catch (const SizeException& e) {
            cout << Tests::F(Tests::tests.N++) << e.what() << endl;
        }
    }
    
    void _Square() {
        try {
                //square a matrix
            cout << " Raising matrix A to power of 2:" << endl;
            cout << sqr(a) << endl;
            cout << Tests::S(Tests::tests.N++) << endl;
        } catch (const SizeException& e) {
            cout << Tests::F(Tests::tests.N++) << e.what() << endl;
        }
    }
    
    void _exp() {
        try {
            a.Random();
            cout << " Matrix A:"<< endl;
            cout << a << endl;
            cout << " exp(A) is" << endl;
            cout << exp(a) << endl;
            cout << Tests::S(Tests::tests.N++) << endl;
        } catch (const SizeException& e) {
            cout << Tests::F(Tests::tests.N++) << e.what() << endl;
        }
    }
    
    void _GetRow() {
        try {
            cout << " First row of matrix A:" << endl;
            cout << a[0] << endl;
            cout << Tests::S(Tests::tests.N++) << endl;
        } catch (const SizeException& e) {
            cout << Tests::F(Tests::tests.N++) << e.what() << endl;
        }
    }
    
    void _GetNum() {
        try {
            cout << " First element of the first row of matrix A:" << endl;
            cout << a[0][0] << endl;
            cout << Tests::S(Tests::tests.N++) << endl;
        } catch (const SizeException& e) {
            cout << Tests::F(Tests::tests.N++) << e.what() << endl;
        }
    }
    
    void _sigmoid() {
        try {
            cout << " Applying sigmoid function to A:" << endl;
            cout << Tests::sigmoid(a) << endl;
            cout << Tests::S(Tests::tests.N++) << endl;
        } catch (const SizeException& e) {
            cout << Tests::F(Tests::tests.N++) << e.what() << endl;
        }
    }
    
    void _FromFile() {
        
        Matrix a(2, 3), b(5, 3);
        a.Random(), b.Random(1, 2);
        
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
            cout << "\n\n";
            
            for (i = 0; i < b.Rows();++i)
                for (j = 0; j < b.Cols();++j)
                    if (b[i][j] != D[i][j]) cout << "\nDifference: " << b[i][j] << " != " << D[i][j] << endl;
            
            cout << "If this fails, it's OK as comparing doubles is pretty difficult" << endl;
        }
        
    }
    
#ifdef HAVE_OPENCL
    void _TestOpenCLMult() {
        try {
            Matrix _a(80, 90), _b(90, 60), _c(80, 60);
                //multiply two matrices (of appropriate size!)
            cout << "Multiplying big matrices ( (80x90) X (90x60) ) " << OCL_TIMES << " times with OpenCL, please wait...\n" << endl;
            size_t r;
            
            _a.Random(), _b.Random();
            
                //cout << "\nA:\n" << _a << "\nB:\n" << _b << endl;
            
            double start = Time();
            
            for (r = 0; r < OCL_TIMES; ++r) {
                _c = _a * _b;
            }
            
            _c.Reshape(7, 6);
            cout << _c.Prettify() << endl;
            
            cout << "Multiplied two big matrices " << OCL_TIMES << " times in " << Time() - start << " seconds." << endl;
            cout << Tests::S(Tests::tests.N++) << endl;
        } catch (const SizeException& e){
                //exception is thrown if the matrices are not of the appropriate size
            cout << Tests::F(Tests::tests.N++) << e.what() << endl;
        }
    }
    
    void _TestOpenCLAddSub() {
        try {
            Matrix _a(80, 90), _b(80, 90), _c(80, 90);
                //add two matrices (of appropriate size!)
            cout << "Adding and substracting big matrices ( (80x90) + (80x90) ) " << OCL_TIMES << " times with OpenCL, please wait...\n" << endl;
            size_t r;
            
            _a.Random(), _b.Random();
            
            double start = Time();
            
            for (r = 0; r < OCL_TIMES; ++r) {
                _c = _a + _b;
                if ((_c -= _b) != _a) {
                    cout << Tests::F(Tests::tests.N++) << endl;
                    return;
                }
            }
            
            _c.Reshape(7, 6);
            cout << _c.Prettify() << endl;
            
            cout << "Added two big matrices " << OCL_TIMES << " times in " << Time() - start << " seconds." << endl;
            cout << Tests::S(Tests::tests.N++) << endl;
        } catch (const SizeException& e){
                //exception is thrown if the matrices are not of the appropriate size
            cout << Tests::F(Tests::tests.N++) << e.what() << endl;
        }
    }
    
#endif
    
    
void Test(void) {
    
#ifdef HAVE_OPENCL
    std::string path = "/Users/ForceBru/Desktop/Matrix/";
    bool ret = Matrix::initOpenCL(path + "add.cl", path + "sub.cl", path + "mult.cl");
    
    if (! ret) cout << "Failed to initialize OpenCL!" << endl;
    else cout << "OpenCL initialized successfully!" << endl;
#endif
    
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
#ifdef HAVE_OPENCL
    Tests::tests.names[13]="Testing OpenCL multiplication";
    Tests::tests.names[14]="Testing OpenCL addition";
#endif
    
    
    cout << "\n\t\tRUNNING " << number_of_tests << " TESTS...\n" << endl;
    
    Stats; _FillRandom();
    Stats; _Output();
    Stats; _Multiply();
    Stats; _AddSubstract();
    Stats; _Reshape();
    Stats; _Transpose();
    Stats; _Identity();
    Stats; _Square();
    Stats; _exp();
    Stats; _GetRow();
    Stats; _GetNum();
    Stats; _sigmoid();
    Stats; _FromFile();
#ifdef HAVE_OPENCL
    Stats; _TestOpenCLMult();
    Stats; _TestOpenCLAddSub();
#endif
    
    
    
    cout << "\n\n\tSUMMARY:" << endl;
    cout << "Succeeded: " << Tests::tests.success << " out of " << Tests::tests.N;
    if (Tests::tests.success == Tests::tests.N) cout << "\t(Great!)" << endl;
    else cout << endl;
    cout << "Failed: " << Tests::tests.failed << " out of " << Tests::tests.N << endl;
    if (Tests::tests.failed)
        cout << "Please see which tests exactly have failed and contact the developer" << endl;
    cout << "\nTests finished\n\n";
}
}