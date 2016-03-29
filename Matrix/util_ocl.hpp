//
//  util_ocl.hpp
//  Matrix
//
//  Created by Mia on 27.03.16.
//  Copyright © 2016 ForceBru. All rights reserved.
//

#ifndef util_ocl_hpp
#define util_ocl_hpp


#ifdef HAVE_OPENCL
#include <iostream>
#include "cl.hpp"

bool check_cl_err(cl_int);
#endif

#endif /* util_ocl_hpp */
