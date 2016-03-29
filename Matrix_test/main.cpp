//
//  main.cpp
//
//  Created by ForceBru on 03.10.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//


#include "Matrix.hpp"
#include "Tests.hpp"

using namespace std;

int main(void) {
    
    Matrix::Init();
    
    Tests::Test(); //perform some tests
    
    return 0;
}