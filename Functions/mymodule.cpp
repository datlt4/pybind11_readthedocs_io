#include "myclass.h"

#include <pybind11/pybind11.h>
namespace py = pybind11;
using namespace pybind11::literals;

MyClass *createMyClass(int size)
{
    return new MyClass(size);
}

PYBIND11_MODULE(mymodule, m)
{
    /**
     * # Return value policies
     * Python and C++ use fundamentally different ways of managing the memory and lifetime of objects managed by them.
     * This can lead to issues when creating bindings for functions that return a non-trivial type. Just by looking at
     * the type information, it is not clear whether Python should take charge of the returned value and eventually free
     * its resources, or if this is handled on the C++ side.
     */
    py::class_<MyClass>(m, "MyClass").def(py::init<int>(), "size"_a).def("print", &MyClass::print);

    m.def("createMyClass", &createMyClass, py::return_value_policy::take_ownership);
}
