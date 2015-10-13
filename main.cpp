//
//  main.cpp
//
//  Created by ForceBru on 03.10.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//


#include <iostream>

#include "Matrix.hpp"

#define MAX_TIMES 1000000

using namespace std;

int main(int argc, const char * argv[]) {
    
    srand((unsigned int)time(NULL));
    
    Matrix a(3,4);
    Matrix b(4,2);
    Matrix c(3,2);
    Matrix OK=c;
    a.FillRandom();
    b.FillRandom();
    
    cout << "A:\n" << a << endl;
    cout << "B:\n" << b << endl;
    
    try{
        OK=a*b;
        cout << "Multiplying matrices..." << endl;
        unsigned long D;
        cout << "Started multiplying this " << MAX_TIMES << " times..." << endl;
        
        time_t st=time(NULL);
        for (D=0; D<MAX_TIMES; ++D) {
            c=a*b;
            if (c!=OK) {
                cout << "That's an error!" << endl;
            }
        }
        cout << c;
        cout << "Done in " << difftime(time(NULL), st) << " seconds" << endl;
    } catch (SizeException const& e){
        cout << "Caught exception: " << e.what() << endl;
    }
    
    c.Reshape(2, 3);
    
    cout << c << endl;
    
    return 0;
}
