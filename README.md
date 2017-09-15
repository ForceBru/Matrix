[![Build Status](https://travis-ci.org/ForceBru/Matrix.svg?branch=master)](https://travis-ci.org/ForceBru/Matrix)

# Matrix

User-friendly way to perform operations with matrices. _Supports OpenCL for calculations on GPU._


##What is it for?

_Matrix_ is written to help programmers work with matrices easily and with as little efforts as possible. It also aims for code readability and simple logic. There's no need to work with vectors or arrays in your code (while that's what is used under the hood). You work with objects that implement some basic operations (like multiplication, addition, etc).

##Dependencies and requirements

Absolutely _no dependencies_ except for a C/C++ runtime (and OpenCL if needed). Requires a C++ compiler to be built. 

To use OpenCL, define `HAVE_OPENCL` like this:

```sh
$CXX -DHAVE_OPENCL #other options
```


###Documentation

Documentation and examples of usage are available in the [Matrix Wiki](https://github.com/ForceBru/Matrix/wiki)
