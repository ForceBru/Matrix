//
//  Exceptions.cpp
//
//  Created by ForceBru on 13.10.15.
//  Copyright © 2015 ForceBru. All rights reserved.
//

#include "Exceptions.hpp"

SizeException::SizeException() {
    this->m="Size mismatch";
}

SizeException::SizeException(const char * msg) {
    this->m=msg;
}