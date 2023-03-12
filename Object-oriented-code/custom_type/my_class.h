#ifndef __MY_CLASS_H__
#define __MY_CLASS_H__

#include <cmath>
#include <iostream>
#include <string>

class Cat
{

  public:
    Cat(const std::string &name);
    Cat(const Cat &other);

    void setName(const std::string &name_);
    const std::string &getName() const;
    friend std::ostream &operator<<(std::ostream &os, const Cat &cat);

    const int getOnlyRead() const;
    void setOnlyWrite(float);
    // static int count; // count time getName called

    double public_var;
    double readonly_public_var;

  private:
    std::string name;
    int only_read;
    float only_write;
};

class Shape
{
  public:
    Shape(const std::string &Id_);
    Shape(const Shape &other);
    virtual ~Shape();
    const std::string &getId();
    void setId(const std::string &Id_);
    static int getCount();
    static int public_static_var;

    virtual float area() const = 0;
    virtual float perimeter() const = 0;

  protected:
    static int reference_count;

  private:
    std::string Id;
};

class Rectangle : public Shape
{
  public:
    Rectangle(float witdh, float height, const std::string &id = "0");
    ~Rectangle() override;
    float area() const override;
    float perimeter() const override;

  private:
    float width;
    float height;
};

class Circle : public Shape
{
  public:
    Circle(float radius_, const std::string &id = "0");
    ~Circle() override;
    float area() const override;
    float perimeter() const override;

  private:
    float radius;
};

class Shape2
{
  public:
    virtual ~Shape2()
    {
    }
    virtual double area() const = 0; // pure virtual function

    int miscellaneous()
    {
        return 2210;
    }

    std::string miscellaneous(const std::string &s)
    {
        return "Hello " + s + ", you are in miscellaneous\n";
    }
};

class Rectangle2 : public Shape2
{
  public:
    Rectangle2(double width, double height) : width_(width), height_(height)
    {
    }

    double area() const override
    {
        return width_ * height_;
    }

  private:
    double width_;
    double height_;
};

#endif // __MY_CLASS_H__