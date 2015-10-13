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
    unsigned long D;
    
        //create some matrices of size (rows, columns)
    Matrix a(3,4);
    Matrix b(4,2);
    Matrix c(3,2);
    Matrix OK=c; //no need to initialize, just assign a value
    
        //fill matrices with random values
    a.FillRandom();
    b.FillRandom();
    
        //outputting is easy
    cout << "A:\n" << a << endl;
    cout << "B:\n" << b << endl;
    
    try{
            //multiply two matrices (of appropriate size!)
        OK=a*b;
        cout << "Multiplying matrices..." << endl;
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
            //exception is thrown if the matrices are not of the appropriate size
        cout << "Caught exception: " << e.what() << endl;
    }
    
        //'c' was 3x2, now make it 2x2 by removing the last row (other rows are kept)
    c.Reshape(2, 3);
    
    cout << c << endl;
    
    return 0;
}
