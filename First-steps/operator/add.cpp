#include "add.h"

int fourty_two = 42;

template <typename T>
T add_op(T x, T y)
{
    return x + y;
}

// Explicitly instantiate the template function for the types you want to tells the compiler to generate the code for
// the function with the specified template arguments
template int add_op(int, int);
template float add_op(float, float);
template double add_op(double, double);
