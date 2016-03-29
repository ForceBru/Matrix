#pragma OPENCL EXTENSION cl_khr_fp64 : enable


__kernel void Matrix_mult(constant double *left, constant double *right, __global double *out, const size_t right_rows, const size_t left_rows, const size_t right_cols, const size_t left_cols) {
    
#ifdef SLOW
    size_t a,b,c;
    
    for (a = 0; a < left_rows; ++a) {
        for (b = 0; b < right_cols; ++b) {
            double tmp;
            for (c = 0, tmp = 0.0; c < left_cols; ++c)
                tmp += left[a * left_cols + c] * right[c * right_cols + b];
            out[a * right_cols + b] = tmp;
        }
    }
#else
    int i = get_global_id(0),
        j = get_global_id(1);
    
    double value = 0;
    
    for (size_t c = 0; c < left_cols; ++c)
        value += left[i * left_cols + c] * right[c * right_cols + j];
    
    out[i * right_cols + j] = value;
#endif
}