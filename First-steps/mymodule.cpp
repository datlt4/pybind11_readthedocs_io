#include "add.h"
#include "div.h"
#include "mul.h"
#include "sub.h"

#include <math.h>
#include <pybind11/pybind11.h>
namespace py = pybind11;
using namespace pybind11::literals;

template <typename T>
T max_value(T x, T y)
{
    return x > y ? x : y;
}

double hat(double x, double h)
{
    return pow(x, h);
}

PYBIND11_MODULE(mymodule, m)
{
    m.doc() = "pybind11 example plugin"; // optional module docstring

    // In pybind11, py::arg(x) and "x"_a are both used to specify function arguments in Python.

    // py::arg(x) is a class that represents a function argument, which can be used to specify the name, default value,
    //  and type of the argument. It is used by passing it as an argument to the def method in a pybind11 module.

    // "x"_a is a user-defined literal that creates a py::arg object with the specified name x. It can be used as a
    // shorthand for creating py::arg objects, making it easier and more concise to specify function arguments.

    m.def("add_int", &(add_op<int>), "A function that adds two integer numbers", py::arg("i"), py::arg("j"));
    m.def("add_op", py::overload_cast<int, int>(&add_op<int>), "A function that add two int numbers", "x"_a, "y"_a);
    m.def("add_op", py::overload_cast<float, float>(&add_op<float>), "A function that add two float numbers",
          py::arg("x") = 0, py::arg("y") = 0);
    m.def("add_op", py::overload_cast<double, double>(&add_op<double>), "A function that add two double numbers",
          "x"_a = 0, "y"_a = 0);

    m.def("sub_op", py::overload_cast<int, int>(&sub_op<int>), "A function that sub two int numbers", py::arg("x"),
          py::arg("y"));
    m.def("sub_op", py::overload_cast<float, float>(&sub_op<float>), "A function that sub two float numbers",
          py::arg("x"), py::arg("y"));
    m.def("sub_op", py::overload_cast<double, double>(&sub_op<double>), "A function that sub two double numbers",
          py::arg("x"), py::arg("y"));

    m.def("mul_op", py::overload_cast<int, int>(&mul_op<int>), "A function that mul two int numbers", py::arg("x"),
          py::arg("y"));
    m.def("mul_op", py::overload_cast<float, float>(&mul_op<float>), "A function that mul two float numbers",
          py::arg("x"), py::arg("y"));
    m.def("mul_op", py::overload_cast<double, double>(&mul_op<double>), "A function that mul two double numbers",
          py::arg("x"), py::arg("y"));

    m.def("div_op", py::overload_cast<int, int>(&div_op<int>), "A function that div two int numbers", py::arg("x"),
          py::arg("y"));
    m.def("div_op", py::overload_cast<float, float>(&div_op<float>), "A function that div two float numbers",
          py::arg("x"), py::arg("y"));
    m.def("div_op", py::overload_cast<double, double>(&div_op<double>), "A function that div two double numbers",
          py::arg("x"), py::arg("y"));

    m.def("max_value_int", &max_value<int>, "max_value<int>", py::arg("x"), py::arg("y"));
    m.def("max_value", py::overload_cast<int, int>(&max_value<int>), "max_value<int>", py::arg("x"), py::arg("y"));
    m.def("max_value", py::overload_cast<float, float>(&max_value<float>), "max_value<float>", py::arg("x"),
          py::arg("y"));
    m.def("max_value", py::overload_cast<double, double>(&max_value<double>), "max_value<double>", py::arg("x"),
          py::arg("y"));

    m.def("hat", &hat, "power function", "x"_a, "y"_a);

    m.attr("fourty_two") = fourty_two;
    py::object hw = py::cast("hello word");
    m.attr("get_started") = hw;
}
