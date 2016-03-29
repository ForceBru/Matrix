//
//  Tests.h
//  ANN
//
//  Created by ForceBru on 03.11.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//

#ifndef Tests_h
#define Tests_h

#include <exception>
#include <string>
#include "Matrix.hpp"

#if __cplusplus > 199711L
#include <chrono>
#else
#include <ctime>
#endif

using namespace std;

#define TIMES 2000000UL
#define OCL_TIMES 10000

namespace Tests {
#ifdef HAVE_OPENCL
#define number_of_tests 15
#else
#define number_of_tests 13
#endif
    
    double Time();

    struct {
        unsigned tests[number_of_tests], N, failed, success;
        string names[number_of_tests];
    } tests={{0}, 0, 0, 0, {""}};

    Matrix sigmoid(Matrix& z);
    string S(int num);
    string F(int num);
    void Test(void);
    
}

#endif /* Tests_h */
