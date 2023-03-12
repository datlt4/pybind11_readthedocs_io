#include "my_class.h"
#include "my_struct.h"

#include <memory>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(mymodule, m)
{
    /**
     * Creating bindings for a custom type
     * class_ creates bindings for a C++ class or struct-style data structure.
     * init() is a convenience function that takes the types of a constructor’s parameters as template arguments and
     * wraps the corresponding constructor
     * We can also directly expose the name field using the class_::def_readwrite() method.
     * A similar class_::def_readonly() method also exists for const fields.
     */
    // py::class_<Dog>(m, "Dog")
    py::class_<Dog>(m, "Dog", py::dynamic_attr())
        .def(py::init<>())
        .def(py::init<const std::string &>(), py::arg("name"))
        .def("setName", &Dog::setName, py::arg("name"))
        .def("getName", &Dog::getName)
        .def("__str__", [](const Dog &a) { return "<mymodule.Dog named '" + a.getName() + "'>"; })
        .def_readwrite("name", &Dog::name); // expose fields

    /**
     * Class and Dynamic attributes
     * We can also directly expose the name field using the class_::def_readwrite() method.
     * A similar class_::def_readonly() method also exists for const fields.
     * Suppose that Pet::name was a private internal variable that can only be accessed via setters and getters. In this
     *   case, the method class_::def_property() (class_::def_property_readonly() for read-only data) can be used to
     *   provide a field-like interface within Python that will transparently call the setter and getter functions.
     * Write only properties can be defined by passing nullptr as the input for the read function.
     * To enable dynamic attributes for C++ classes, the py::dynamic_attr tag must be added to the py::class_
     * constructor.
     */
    // py::class_<Cat>(m, "Cat", py::dynamic_attr())
    py::class_<Cat>(m, "Cat")
        .def(py::init<const std::string &>(), py::arg("name"))
        .def(py::init<const Cat &>(), py::arg("other"))
        .def_readwrite("public_var", &Cat::public_var)                  // expose public attributes
        .def_readonly("readonly_public_var", &Cat::readonly_public_var) // expose read-only public attributes
        .def("__str__", [](const Dog &a) { return "<mymodule.Dog named '" + a.getName() + "'>"; })
        .def_property("name", &Cat::getName,
                      &Cat::setName) // expose private internal attributes can be accessed via setters getters
        .def_property_readonly("read_only", &Cat::getOnlyRead)   // read-only
        .def_property("write_only", nullptr, &Cat::setOnlyWrite) // write-only
        ;

    /**
     * Inheritance and automatic downcasting
     * There are two different ways of indicating a hierarchical relationship to pybind11
     * 1. the first specifies the C++ base class as an extra template parameter of the class_
     * 2. Alternatively, we can also assign a name to the previously bound Cat class_ object and reference it when
     * binding the ConMeo class:
     */

#define INHERITANCE_METHOD_1

#ifdef INHERITANCE_METHOD_1
    // Method 1 : template parameter:

    // [ WARNING ] If in your class have pure virtual method, you can encounter issue: invalid new-expression of
    // abstract class type. There are 3 ways to resolve it:
    // 1. define pure virtual method.
    py::class_<Shape2>(m, "Shape2")
        .def("miscellaneous", py::overload_cast<>(&Shape2::miscellaneous))
        .def("miscellaneous", py::overload_cast<const std::string &>(&Shape2::miscellaneous), "s"_a);
    py::class_<Rectangle2, Shape2>(m, "Rectangle2").def(py::init<double, double>()).def("area", &Rectangle2::area);

    // 2. don't bind constructors
    py::class_<Shape>(m, "Shape")
        //.def(py::init<const Shape &>(), py::arg("other"))
        //.def(py::init<const std::string &>(), "id"_a)
        .def_property("Id", &Shape::getId, &Shape::setId)
        .def_static("getCount", &Shape::getCount)
        .def_readwrite_static("public_static_var", &Shape::public_static_var);
    py::class_<Circle, Shape /* <- specify C++ parent type */>(m, "Circle")
        .def(py::init<float, const std::string &>(), "radius"_a, "id"_a)
        .def("area", &Circle::area)
        .def("perimeter", &Circle::perimeter);
    py::class_<Rectangle, Shape>(m, "Rectangle")
        .def(py::init<float, float, const std::string &>())
        .def("area", &Rectangle::area)
        .def("perimeter", &Rectangle::perimeter);

#else  // !INHERITANCE_METHOD_1
    // Method 2: pass parent class_ object:
    py::class_<Shape2> shape2(m, "Shape2");
    shape2 //
        .def("miscellaneous", py::overload_cast<>(&Shape2::miscellaneous))
        .def("miscellaneous", py::overload_cast<const std::string &>(&Shape2::miscellaneous), "s"_a);
    py::class_<Rectangle2>(m, "Rectangle2", shape2 /* <- specify Python parent type */)
        .def(py::init<double, double>())
        .def("area", &Rectangle2::area);

    py::class_<Shape> shape1(m, "Shape");
    shape1
        //.def(py::init<const Shape &>(), py::arg("other"))
        //.def(py::init<const std::string &>(), "id"_a)
        .def_property("Id", &Shape::getId, &Shape::setId)
        .def_static("getCount", &Shape::getCount)
        .def_readwrite_static("public_static_var", &Shape::public_static_var);
    py::class_<Circle>(m, "Circle", shape1) /* <- specify Python parent type */
        .def(py::init<float, const std::string &>(), "radius"_a, "id"_a)
        .def("area", &Circle::area)
        .def("perimeter", &Circle::perimeter);
    py::class_<Rectangle>(m, "Rectangle", shape1) /* <- specify Python parent type */
        .def(py::init<float, float, const std::string &>())
        .def("area", &Rectangle::area)
        .def("perimeter", &Rectangle::perimeter);
#endif // INHERITANCE_METHOD_1
    /**
     * Downcasting
     * Given a pointer to a polymorphic base, pybind11 performs automatic downcasting to the actual derived type.
     */
    m.def(
        "shape_store_rect",
        [](float width, float height, std::string id) {
            return std::unique_ptr<Shape>(new Rectangle(width, height, id));
        },
        "witdh"_a, "height"_a, "id"_a);
    m.def(
        "shape_store_circle",
        [](float radius, std::string id) { return std::unique_ptr<Shape>(new Circle(radius, id)); }, "radius"_a,
        "id"_a);

    /**
     * py::overload_cast only requires the parameter types to be specified. The return type and class are deduced.
     * If a function is overloaded based on constness, the py::const_ tag should be used:
     */
    py::class_<Widget>(m, "Widget")
        .def(py::init<int, float>(), "x"_a, "y"_a)
        .def("foo_mutable", py::overload_cast<int, float>(&Widget::foo), "x"_a, "y"_a)
        .def("foo_const", py::overload_cast<int, float>(&Widget::foo, py::const_), "x"_a, "y"_a);

    /**
     * Enumerations and internal types
     */
    py::class_<Pet> pet(m, "Pet");

    pet.def(py::init<const std::string &, Pet::Kind>())
        .def_readwrite("name", &Pet::name)
        .def_readwrite("type", &Pet::type)
        .def_readwrite("attr", &Pet::attr)
        .def_readwrite("color", &Pet::color)
        .def_readwrite("body_desc", &Pet::body_desc);

    // Kind is internal type
    py::enum_<Pet::Kind>(pet, "Kind").value("Dog", Pet::Kind::Dog).value("Cat", Pet::Kind::Cat).export_values();

    py::enum_<Color>(m, "Color")
        .value("RED", Color::RED)
        .value("GREEN", Color::GREEN)
        .value("BLUE", Color::BLUE)
        .export_values();
    m.def("to_int", [](Color c) { return static_cast<std::underlying_type_t<Color>>(c); });

    py::enum_<Body>(m, "Body")
        .value("TALL", TALL)
        .value("SHORT", SHORT)
        .value("LONG", LONG)
        .value("THIN", THIN)
        .export_values();

    // Attribute is internal type
    py::class_<Pet::Attributes>(pet, "Attributes").def_readwrite("age", &Pet::Attributes::age);
}
