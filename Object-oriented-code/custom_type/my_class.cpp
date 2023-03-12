#include "my_class.h"

int Shape::reference_count = 0;
int Shape::public_static_var = 2210;

Cat::Cat(const std::string &name) : name{name}, only_read{10}, public_var{2210}, readonly_public_var(2210)
{
}

Cat::Cat(const Cat &other) : name{other.name}, only_read{other.only_read}
{
}

void Cat::setName(const std::string &name_)
{
    name = name_;
}

const std::string &Cat::getName() const
{
    return name;
}

std::ostream &operator<<(std::ostream &os, const Cat &cat)
{
    os << "cat's name:" << cat.name;
    return os;
}

const int Cat::getOnlyRead() const
{
    return this->only_read;
}

void Cat::setOnlyWrite(float ow)
{
    only_write = ow;
}

Shape::Shape(const std::string &Id_) : Id{Id_}
{
    std::cout << "[ " << __LINE__ << " ] " << __FUNCTION__ << std::endl;
    ++reference_count;
}

Shape::Shape(const Shape &other) : Id{other.Id}
{
    std::cout << "[ " << __LINE__ << " ] " << __FUNCTION__ << std::endl;
    ++reference_count;
}

Shape::~Shape()
{
    std::cout << "[ " << __LINE__ << " ] " << __FUNCTION__ << std::endl;
    --reference_count;
}

const std::string &Shape::getId()
{
    return this->Id;
}

void Shape::setId(const std::string &Id_)
{
    this->Id = Id_;
}

int Shape::getCount()
{
    return reference_count;
}

Circle::Circle(float radius_, const std::string &id) : Shape(id), radius{radius_}
{
    std::cout << "[ " << __LINE__ << " ] " << __FUNCTION__ << std::endl;
}

Circle::~Circle()
{
    std::cout << "[ " << __LINE__ << " ] " << __FUNCTION__ << std::endl;
}

float Circle::area() const
{
    return M_PI * radius * radius;
}

float Circle::perimeter() const
{
    return 2 * M_PI * radius;
}

Rectangle::Rectangle(float width_, float height_, const std::string &id) : Shape(id), width{width_}, height{height_}
{
    std::cout << "[ " << __LINE__ << " ] " << __FUNCTION__ << std::endl;
}

Rectangle::~Rectangle()
{
    std::cout << "[ " << __LINE__ << " ] " << __FUNCTION__ << std::endl;
}

float Rectangle::area() const
{
    return width * height;
}

float Rectangle::perimeter() const
{
    return 2 * (width + height);
}