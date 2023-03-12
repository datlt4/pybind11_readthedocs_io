#include "my_struct.h"

Dog::Dog(const std::string &name) : name{name}
{
}

Dog::Dog() : name{"Cho'"}
{
}

void Dog::setName(const std::string &name_)
{
    name = name_;
}

const std::string &Dog::getName() const
{
    return name;
}

std::ostream &operator<<(std::ostream &os, const Dog &dog)
{
    os << "dog's name:" << dog.name;
    return os;
}

Widget::Widget(int x, float y)
{
    x_ = x;
    y_ = y;
}

int Widget::foo(int x, float y)
{
    return x_ + y_ - x - y;
}
int Widget::foo(int x, float y) const
{
    return x + y - x_ - y_;
}