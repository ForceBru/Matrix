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
#include "Matrix.hpp"

using namespace std;

namespace Tests {
#define number_of_tests 13

    struct {
        unsigned tests[number_of_tests], N, failed, success;
        string names[number_of_tests];
    } tests={0,0,0,0,};

    Matrix sigmoid(Matrix& z);
    string S(int num);
    string F(int num);
    void Test(void);
    
}

#endif /* Tests_h */
