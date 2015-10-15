//
//  main.cpp
//
//  Created by ForceBru on 03.10.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//


#include <iostream>

#include "Matrix.hpp"


using namespace std;

int main(int argc, const char * argv[]) {
    
    srand((unsigned int)time(NULL));
    
        //create some matrices of size (rows, columns)
    Matrix a(3,4);
    Matrix aHat(3,4);
    Matrix b(4,2);
    Matrix c(3,2);
    
        //fill matrices with random values
    a.FillRandom();
    aHat=a;
    b.FillRandom();
    
        //outputting is easy
    cout << "A:\n" << a << endl;
    cout << "B:\n" << b << endl;
    
    try {
            //multiply two matrices (of appropriate size!)
        cout << "Multiplying matrices..." << endl;
        c=a*b;
        cout << c << endl;
        
    } catch (const SizeException& e){
            //exception is thrown if the matrices are not of the appropriate size
        cout << "Caught exception: " << e.what() << endl;
    }
    
    try {
            //add to matrices easily
        cout << "Adding matrices..." << endl;
        aHat+=a;
            //and then substract
        aHat-=a;
        
            //now aHat should be equal to a
        if (aHat != a) cout << "That's an error!" << endl;
        else cout << "Test passed" << endl;
    } catch (const SizeException& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    
        //'c' was 3x2, now make it 2x2 by removing the last row (other rows are kept)
    c.Reshape(2, 3);
    
    cout << c << endl;
    
        //transpose a matrix
    cout << a.T() << endl; //or a.Transpose()
    
    return 0;
}
