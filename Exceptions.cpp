//
//  Exceptions.cpp
//  ANN
//
//  Created by Mia on 13.10.15.
//  Copyright © 2015 Mia. All rights reserved.
//

#include "Exceptions.hpp"

SizeException::SizeException() {
    this->m="Size mismatch";
}

SizeException::SizeException(const char * msg) {
    this->m=msg;
}