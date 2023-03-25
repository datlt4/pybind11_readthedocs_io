#ifndef __MY_CLASS_H__
#define __MY_CLASS_H__

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>

class MyClass
{
  public:
    MyClass(int size, std::string s = "default");
    MyClass(const MyClass &other);
    ~MyClass();

    void print() const;

    int *data();
    int size() const;
    void delitem(int index);
    std::string str() const;

    int &operator[](std::size_t index) const;
    MyClass operator+(const MyClass &other) const;
    std::string text;
    int *m_data;

  private:
    int m_size;
};

#endif // __MY_CLASS_H__
