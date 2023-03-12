# Note

- https://github.com/datlt4/WLINUX/blob/master/my-chatgpt-QA.md#-what-is-the-different-between-pyarg-and-x_a-in-pybind11-project
- https://github.com/datlt4/WLINUX/blob/master/my-chatgpt-QA.md#-pybind11-undefined-symbol-cannot-link-to-a-template-function
- https://github.com/datlt4/WLINUX/blob/master/my-chatgpt-QA.md#-why-do-we-need-to--explicitly-instantiate-the-template-function-in-a-source-file

# Build

```bash
cd build
cmake ..
make -j$(nproc)
```

# Usage

## Creating bindings for a custom type

```python
from mymodule import *
dog = Dog("Morri")
dog.setName("Conan")
dog.getName()
dog.name = "Haibara_Ai"
print(dog)
```

## Class

```python
from mymodule import *
cat = Cat("Morri")
cat.public_var = 1405
cat.public_var
cat.readonly_public_var

cat.name
cat.name = "Conan"
cat.name
cat.name = "Haibara_Ai"

cat.read_only
cat.write_only = 10
```

## Dynamic attributes

```python
from mymodule import *
dog_dy = Dog()
dog_dy.name = "Conan"
dog_dy.name
dog_dy.age = 10
dog_dy.__dict__
```

## Inheritance

```python
from mymodule import *
from uuid import uuid4

s2 = Rectangle2(3, 2)
s2.area()

rect1 = Rectangle(4, 3, uuid4().hex)
rect1.getCount()
rect1.Id
rect1.area()
rect1.perimeter()
Rectangle.getCount()

cir1 = Circle(3, uuid4().hex)
cir1.Id
cir1.area()
cir1.perimeter()
Rectangle.getCount()

Shape.public_static_var
cir1.public_static_var = 0
rect1.public_static_var

rect2 = shape_store_rect(4, 3, uuid4().hex)
cir2 = shape_store_circle(3, uuid4().hex)

type(rect1)
type(cir1)
type(rect2)
type(cir2)
```

## Enumerations and internal types

```python
from mymodule import *

Color.RED
Color.GREEN
Color.BLUE

to_int(Color.RED)
to_int(Color.GREEN)
to_int(Color.BLUE)

Body.TALL
Body.SHORT
Body.LONG
Body.THIN

pet = Pet("Lucy", Pet.Cat)
pet.name
pet.type
pet.attr.age=10
pet.color=Color.RED
pet.body_desc=Body.SHORT
```
