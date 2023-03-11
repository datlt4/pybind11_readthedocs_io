#include "div.h"

template <typename T>
T div_op(T x, T y)
{
    return x / y;
}

// Explicitly instantiate the template function for the types you want to tells the compiler to generate the code for
// the function with the specified template arguments
template int div_op(int, int);
template float div_op(float, float);
template double div_op(double, double);
