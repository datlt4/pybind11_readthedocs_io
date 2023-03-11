#include "sub.h"

template <typename T>
T sub_op(T x, T y)
{
    return x - y;
}

// Explicitly instantiate the template function for the types you want to tells the compiler to generate the code for
// the function with the specified template arguments
template int sub_op(int, int);
template float sub_op(float, float);
template double sub_op(double, double);
