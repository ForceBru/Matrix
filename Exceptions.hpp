//
//  Exceptions.hpp
//
//  Created by ForceBru on 13.10.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//

#ifndef Exceptions_hpp
#define Exceptions_hpp

/* This exception is thrown when something
 is wrong with the sze of a matrix.
 For example, if two matrices are not of the
 appropriate sizes (PxN and NxK) or if
 one tries to substract or add matrices of different shapes,
 e.g. PxN + PxK instead of PxN + PxN.
*/

class SizeException
{
public:
    SizeException();
    SizeException(const char * msg);
    virtual const char* what() const throw()
    {
        return this->m;
    }
private:
    const char *m;
};

#endif /* Exceptions_hpp */
