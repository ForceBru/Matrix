//
//  Exceptions.hpp
//
//  Created by ForceBru on 13.10.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//

#ifndef Exceptions_hpp
#define Exceptions_hpp

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
