#ifndef __MY_CLASS_H__
#define __MY_CLASS_H__

#include <iostream>

class MyClass
{
  public:
    MyClass(int size);
    ~MyClass();

    void print() const;

  private:
    int *m_data;
    int m_size;
};

#endif // __MY_CLASS_H__