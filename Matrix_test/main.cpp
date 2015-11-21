//
//  main.cpp
//
//  Created by ForceBru on 03.10.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//


#include <iostream>
#include <algorithm>

#include "Matrix.hpp"

#include "Tests.hpp"

using namespace std;


int main(int argc, const char * argv[]) {
    
    srand((unsigned int)time(NULL));
    
    Tests::Test(); //perform some tests
    
    return 0;
}