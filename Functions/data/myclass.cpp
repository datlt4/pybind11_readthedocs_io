#include "myclass.h"

MyClass::MyClass(int size) : m_data(new int[size]), m_size(size)
{
    std::cout << "[ " << __LINE__ << " ] " << __FUNCTION__ << std::endl;
}

MyClass::~MyClass()
{
    std::cout << "[ " << __LINE__ << " ] " << __FUNCTION__ << std::endl;
    delete[] m_data;
}

void MyClass::print() const
{
    for (int i = 0; i < m_size; ++i)
        std::cout << m_data[i] << " ";
}
