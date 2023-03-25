#include "animals.h"
#include "myclass.h"

#include <memory>
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

    py::class_<MyClass>(m, "MyClass")
        .def(py::init<int, std::string>(), "size"_a, "string"_a)
        .def("print", &MyClass::print)
        .def_property_readonly("data", &MyClass::data)
        .def_property_readonly("size", &MyClass::size)
        .def("__sizeof__", [](MyClass &m) { return sizeof(int) * (1 + m.size()); })
        .def("get_size", &MyClass::size, py::return_value_policy::reference_internal)
        .def("__delitem__", &MyClass::delitem, "index"_a)
        .def("__getitem__", &MyClass::operator[], "index"_a)
        .def("__setitem__", [](MyClass &m, std::size_t index, int value) { m[index] = value; })
        .def("__add__", &MyClass::operator+, py::return_value_policy::take_ownership)
        .def("__str__", &MyClass::str);

    /**
     * @brief return_value_policy::take_ownership
     * In this example, we define a MyData class that holds a pointer to a dynamically allocated array of integers. We
     * then define a Python module called `MyClass` that exposes this class and a function `policy_take_ownership` that
     * returns a std::unique_ptr<MyData>.
     *
     * In order to properly transfer ownership of the MyData object to Python, we use the
     * `py::return_value_policy::take_ownership` policy when defining the policy_take_ownership function. This tells
     * Pybind11 to take ownership of the `MyData` object and delete it when it is no longer needed by Python.
     *
     * Note that this policy only works for objects that are dynamically allocated using new and wrapped in a
     * `std::unique_ptr`. For other types of objects, you may need to use a different return value policy.
     */

    m.def(
        "copy_mydata", [](MyClass &d) -> std::unique_ptr<MyClass> { return std::make_unique<MyClass>(d); },
        py::return_value_policy::take_ownership);

    m.def(
        "policy_take_ownership",
        [](int n, std::string s) -> std::unique_ptr<MyClass> { return std::make_unique<MyClass>(n, s); },
        py::return_value_policy::take_ownership);

    /**
     * @brief return_value_policy::copy
     * Create a new copy of the returned object, which will be owned by Python. This policy is comparably safe because
     * the lifetimes of the two instances are decoupled.
     */

    m.def(
        "policy_copy", [](int n, std::string s) -> MyClass { return MyClass(n, s); }, py::return_value_policy::copy);

    /**
     * @brief return_value_policy::copy
     * Use std::move to move the return value contents into a new instance that will be owned by Python. This policy is
     * comparably safe because the lifetimes of the two instances (move source and destination) are decoupled.
     */

    m.def(
        "policy_move", [](int n, std::string s) -> MyClass { return MyClass(n, s); }, py::return_value_policy::move);

    /**
     * @brief return_value_policy::reference
     * Reference an existing object, but do not take ownership. The C++ side is responsible for managing the object’s
     * lifetime and deallocating it when it is no longer used. Warning: undefined behavior will ensue when the C++ side
     * deletes an object that is still referenced and used by Python
     */
    m.def(
        "policy_reference", [](MyClass &m) -> MyClass & { return m; }, py::return_value_policy::reference);

    /**
     * @brief return_value_policy::reference_internal
     * Indicates that the lifetime of the return value is tied to the lifetime of a parent object, namely the implicit
     * this, or self argument of the called method or property. Internally, this policy works just like
     * return_value_policy::reference but additionally applies a keep_alive<0, 1> call policy (described in the next
     * section) that prevents the parent object from being garbage collected as long as the return value is referenced
     * by Python. This is the default policy for property getters created via def_property, def_readwrite, etc.
     *
     * In particular, we use py::return_value_policy::reference_internal as the return value policy for the
     * MyClass::size() function. This tells pybind11 to return a reference to the int data member of MyClass rather than
     * a copy. By default, pybind11 returns copies of C++ objects to Python, but using reference_internal allows us to
     * avoid unnecessary copying and improve performance.
     */
    // py::class_<MyClass>(m, "MyClass")
    //     .def("get_size", &MyClass::size, py::return_value_policy::reference_internal);

    /**
     * @brief return_value_policy::automatic
     * This policy falls back to the policy return_value_policy::take_ownership when the return value is a pointer.
     * Otherwise, it uses return_value_policy::move or return_value_policy::copy for rvalue and lvalue references,
     * respectively. See above for a description of what all of these different policies do. This is the default policy
     * for py::class_-wrapped types.
     *
     * The py::return_value_policy::automatic argument tells Pybind11 to automatically determine the appropriate return
     * value policy for the function. This is useful when the function returns a C++ object that has a corresponding
     * Python type. In this case, since std::string maps to a Python string, Pybind11 will automatically use the copy
     * return value policy, which creates a copy of the returned object and returns it to Python.
     *
     * Note that return_value_policy::automatic may not always be the appropriate choice, especially if the function
     * returns a C++ object that does not have a corresponding Python type or requires some special handling. In such
     * cases, it may be necessary to explicitly specify a return value policy.
     */

    m.def(
        "greet", []() -> std::string { return "Hello World!"; }, py::return_value_policy::automatic);

    /**
     * @brief Python objects as arguments
     * pybind11 exposes all major Python types using thin C++ wrapper classes. These wrapper classes can also be used as
     * parameters of functions in bindings, which makes it possible to directly work with native Python types on the C++
     * side.
     */
    m.def("print_dict", [](const py::dict &dict) {
        /* Easily interact with Python types */
        for (auto item : dict)
            std::cout << "key=" << std::string(py::str(item.first)) << ", "
                      << "value=" << std::string(py::str(item.second)) << std::endl;
    });

    m.def("print_list", [](const py::list &list) {
        /* Easily interact with Python types */
        for (auto item : list)
            std::cout << std::string(py::str(item)) << "  ";
        std::cout << "\n";
    });

    m.def("print_tuple", [](const py::tuple &tuple) {
        /* Easily interact with Python types */
        for (auto item : tuple)
            std::cout << std::string(py::str(item)) << "   ";
        std::cout << "\n";
    });

    m.def("print_set", [](const py::set &set) {
        /* Easily interact with Python types */
        for (auto item : set)
            std::cout << std::string(py::str(item)) << "    ";
        std::cout << "\n";
    });

    /**
     * @brief Accepting *args and **kwargs
     * We define a new function called `calculate` that takes any number of positional and keyword arguments, and
     * calculates the sum of all of them.
     *
     * The `py::args` object represents all of the positional arguments passed to the function, and the `py::kwargs`
     * object represents all of the keyword arguments passed to the function. We iterate over both of these objects and
     * add up their values, casting them to integers using `py::cast<int>`.
     *
     */
    m.def(
        "calculate",
        [](py::args args, py::kwargs kwargs) {
            int sum = 0;
            for (auto item : args)
            {
                sum += py::cast<int>(item);
            }
            for (auto item : kwargs)
            {
                sum += py::cast<int>(item.second);
            }
            return sum;
        },
        "Calculate the sum of all arguments");

    /**
     * @brief Allow/Prohibiting None arguments
     * pybind allows None to be passed from Python which results in calling the C++ function with nullptr (or an empty
     * holder) for the argument.
     */
    py::class_<Dog>(m, "Dog").def(py::init<>());
    py::class_<Cat>(m, "Cat").def(py::init<>());
    m.def(
        "bark",
        [](Dog *dog) -> std::string {
            if (dog)
                return "woof!";    /* Called with a Dog instance */
            else
                return "(no dog)"; /* Called with None, dog == nullptr */
        },
        py::arg("dog").none(true));
    m.def(
        "meow",
        [](Cat *cat) -> std::string {
            // Can't be called with None argument
            return "meow";
        },
        py::arg("cat").none(false));
}
