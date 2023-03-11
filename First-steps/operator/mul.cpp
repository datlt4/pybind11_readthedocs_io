#include "mul.h"

template <typename T>
T mul_op(T x, T y)
{
    return x * y;
}

// Explicitly instantiate the template function for the types you want to tells the compiler to generate the code for
// the function with the specified template arguments
template int mul_op(int, int);
template float mul_op(float, float);
template double mul_op(double, double);
