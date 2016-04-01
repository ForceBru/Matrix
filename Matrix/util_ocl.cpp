//
//  util_ocl.cpp
//  Matrix
//
//  Created by Mia on 27.03.16.
//  Copyright © 2016 ForceBru. All rights reserved.
//

#include "util_ocl.hpp"

#ifdef HAVE_OPENCL

bool check_cl_err(cl_int err) {
    switch (err) {
        case CL_INVALID_PROGRAM_EXECUTABLE:
            std::cerr << "Invalid executable after creating kernel!" << std::endl;
            return 1;
        case CL_INVALID_PROGRAM:
            std::cerr << "Invalid program!" << std::endl;
            return 1;
        case CL_INVALID_KERNEL_DEFINITION:
            std::cerr << "Invalid kernel definition!" << std::endl;
            return 1;
        case CL_INVALID_KERNEL_NAME:
            std::cerr << "Invalid kernel name!" << std::endl;
            return 1;
        case CL_INVALID_WORK_GROUP_SIZE:
            std::cerr << "Invalid work group size!" << std::endl;
            return 1;
        case CL_MISALIGNED_SUB_BUFFER_OFFSET:
            std::cerr << "Problems with offset!" << std::endl;
            return 1;
        case CL_MEM_OBJECT_ALLOCATION_FAILURE:
            std::cerr << "Failed to allocate!" << std::endl;
            return 1;
        case CL_OUT_OF_RESOURCES:
            std::cerr << "Out of resources!" << std::endl;
            return 1;
        case CL_INVALID_EVENT_WAIT_LIST:
            std::cerr << "Invalid event wait list!" << std::endl;
            return 1;
        case CL_INVALID_KERNEL:
            std::cerr << "Invalid kernel!" << std::endl;
            return 1;
        case CL_INVALID_CONTEXT:
            std::cerr << "Invalid context!" << std::endl;
            return 1;
        case CL_INVALID_KERNEL_ARGS:
            std::cerr << "Invalid args!" << std::endl;
            return 1;
        case CL_INVALID_COMMAND_QUEUE:
            std::cerr << "Invalid command queue!" << std::endl;
            return 1;
        case CL_INVALID_VALUE:
            std::cerr << "Invalid value!" << std::endl;
            return 1;
        case CL_OUT_OF_HOST_MEMORY:
            std::cerr << "Out of host memory!" << std::endl;
            return 1;
        case CL_INVALID_BUFFER_SIZE:
            std::cerr << "Invalid buffer size!" << std::endl;
            return 1;
        case CL_INVALID_HOST_PTR:
            std::cerr << "Invalid host pointer!" << std::endl;
            return 1;
        
        case CL_SUCCESS: return 0;
        
        default:
            std::cerr << "Got an error!" << std::endl;
            return 1;
    }
}
#endif