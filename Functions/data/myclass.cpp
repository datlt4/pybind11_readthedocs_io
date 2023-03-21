#include "myclass.h"

MyClass::MyClass(int size, std::string s) : m_data{(int *)malloc(size * sizeof(int))}, m_size(size), text{s}
{
    std::cout << "[ " << __LINE__ << " ] " << __FUNCTION__ << " - " << text << std::endl;
    for (int i = 0; i < m_size; ++i)
        m_data[i] = i;
}

MyClass::MyClass(const MyClass &other) : text{other.text + std::string(" - copy")}, m_size{other.size()}
{
    std::cout << "[ " << __LINE__ << " ] " << __FUNCTION__ << " - " << text << std::endl;
    m_data = (int *)malloc(m_size * sizeof(int));
    memcpy((void *)m_data, (void *)(other.m_data), m_size * sizeof(int));
}

MyClass::~MyClass()
{
    std::cout << "[ " << __LINE__ << " ] " << __FUNCTION__ << " - " << text << std::endl;
    delete[] m_data;
}

void MyClass::print() const
{
    std::cout << str() << std::endl;
}

int *MyClass::data()
{
    return m_data;
}

int MyClass::size() const
{
    return m_size;
}

std::string MyClass::str() const
{
    std::ostringstream oss;
    for (int i = 0; i < m_size; ++i)
        oss << m_data[i] << " ";
    return oss.str();
}

int &MyClass::operator[](std::size_t index) const
{
    return m_data[index];
}

MyClass MyClass::operator+(const MyClass &other) const
{
    std::cout << "[ " << __LINE__ << " ] " << __FUNCTION__ << "  m_size: " << m_size << "other.size: " << other.size()
              << std::endl;
    if (this->m_size <= other.size())
    {
        MyClass sum(other.size());
        for (int i = 0; i < other.size(); ++i)
        {
            if (i < this->m_size)
                sum[i] = this->m_data[i] + other[i];
            else
                sum[i] = other[i];
        }
        return sum;
    }
    else
    {
        MyClass sum(this->m_size);
        for (int i = 0; i < this->m_size; ++i)
        {
            if (i < other.size())
                sum[i] = this->m_data[i] + other[i];
            else
                sum[i] = this->m_data[i];
        }
        return sum;
    }
}

void MyClass::delitem(int index)
{
    if (index < m_size)
    {
        int c = index;
        while (c + 1 < m_size)
        {
            m_data[c] = m_data[c + 1];
            ++c;
        }
        --m_size;
        m_data = (int *)realloc(m_data, m_size * sizeof(int));
    }
}
