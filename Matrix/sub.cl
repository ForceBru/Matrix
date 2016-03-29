#pragma OPENCL EXTENSION cl_khr_fp64 : enable

__kernel void Matrix_sub(constant double *left, constant double *right, __global double *out, const size_t rows, const size_t cols) {
#ifdef SLOW
    for (size_t a = 0; a < rows; ++a)
        for (size_t b = 0; b < cols; ++b)
            out[a * cols + b] = left[a * cols + b] - right[a * cols + b];
#else
    int i = get_global_id(0),
        j = get_global_id(1);
    
    out[i * cols + j] = left[i * cols + j] - right[i * cols + j];
#endif
}