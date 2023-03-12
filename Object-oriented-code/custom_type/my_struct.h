#ifndef __MY_STRUCT_H__
#define __MY_STRUCT_H__

#include <iostream>
#include <string>

struct Dog
{
    Dog(const std::string &name);
    Dog();
    void setName(const std::string &name_);
    const std::string &getName() const;
    friend std::ostream &operator<<(std::ostream &os, const Dog &dog);

    std::string name;
};

struct Widget
{
    Widget(int x, float y);
    int foo(int x, float y);
    int foo(int x, float y) const;
    int x_;
    float y_;
};

enum class Color
{
    RED = 0,
    GREEN,
    BLUE
};

enum Body
{
    TALL = 0,
    SHORT,
    LONG,
    THIN

};

struct Pet
{
    enum Kind
    {
        Dog = 0,
        Cat
    };
    struct Attributes
    {
        float age = 0;
    };
    Pet(const std::string &name, Kind type) : name(name), type(type)
    {
    }

    std::string name;
    Kind type;
    Attributes attr;
    Color color;
    Body body_desc;
};

#endif // __MY_STRUCT_H__