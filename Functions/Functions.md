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

## Return value policies

- Python and C++ use fundamentally different ways of managing the memory and lifetime of objects managed by them. This can lead to issues when creating bindings for functions that return a non-trivial type. Just by looking at the type information, it is not clear whether Python should take charge of the returned value and eventually free its resources, or if this is handled on the C++ side. For this reason, pybind11 provides a several return value policy annotations that can be passed to the `module_::def()` and `class_::def()` functions. The default policy is `return_value_policy::automatic`.

- When Python’s garbage collector eventually deletes the Python wrapper, pybind11 will also attempt to delete the C++ instance (via `operator delete()`) due to the implied ownership. At this point, the entire application will come crashing down, though errors could also be more subtle and involve silent data corruption.

- On the other hand, this is not the right policy for many other situations, where ignoring ownership could lead to resource leaks. As a developer using pybind11, it’s important to be familiar with the different return value policies, including which situation calls for which one of them. The following table provides an overview of available policies:

|Return value policy|Description|
|:---:|---|
|`return_value_policy::take_ownership`|Reference an existing object (i.e. do not create a new copy) and take ownership. Python will call the destructor and delete operator when the object’s reference count reaches zero. Undefined behavior ensues when the C++ side does the same, or when the data was not dynamically allocated.|
|`return_value_policy::copy`|Create a new copy of the returned object, which will be owned by Python. This policy is comparably safe because the lifetimes of the two instances are decoupled.|
|`return_value_policy::move`|Use `std::move` to move the return value contents into a new instance that will be owned by Python. This policy is comparably safe because the lifetimes of the two instances (move source and destination) are decoupled.|
|`return_value_policy::reference`|Reference an existing object, but do not take ownership. The C++ side is responsible for managing the object’s lifetime and deallocating it when it is no longer used. Warning: undefined behavior will ensue when the C++ side deletes an object that is still referenced and used by Python.|
|`return_value_policy::reference_internal`|Indicates that the lifetime of the return value is tied to the lifetime of a parent object, namely the implicit `this`, or `self` argument of the called method or property. Internally, this policy works just like `return_value_policy::reference` but additionally applies a `keep_alive<0, 1>` call policy (described in the next section) that prevents the parent object from being garbage collected as long as the return value is referenced by Python. This is the default policy for property getters created via `def_property`, `def_readwrite`, etc.|
|`return_value_policy::automatic`|This policy falls back to the policy `return_value_policy::take_ownership` when the return value is a pointer. Otherwise, it uses `return_value_policy::move` or `return_value_policy::copy` for rvalue and lvalue references, respectively. See above for a description of what all of these different policies do. This is the default policy for `py::class_`-wrapped types.|
|`return_value_policy::automatic_reference`|As above, but use policy `return_value_policy::reference` when the return value is a pointer. This is the default conversion policy for function arguments when calling Python functions manually from C++ code (i.e. via `handle::operator()`) and the casters in `pybind11/stl.h`. You probably won’t need to use this explicitly.|

```python
from mymodule import *

m1 = MyClass(5, "m1")
print(m1)
m1[3]
m1[4] = 10
del(m1[0])
print(m1)
m2 = MyClass(7, "m2")
print(m2)
m3 = policy_take_ownership(8, "m3")
m4 = copy_mydata(m3)
print(m3, m4)
del(m4[3])
m5 = m1+m2
m6 = m2+m1
print(m3, m4, m5, m6)
del(m1)
del(m2)
del(m3)
del(m4)
del(m5)
m6 = 0 

m7 = policy_copy(4, "m7")

m8 = policy_move(8, "m8")

m9 = policy_reference(m8)
```

## Additional call policies

## Python objects as arguments

- pybind11 exposes all major Python types using thin C++ wrapper classes. These wrapper classes can also be used as parameters of functions in bindings, which makes it possible to directly work with native Python types on the C++ side.

```python
from mymodule import *

print_dict({"foo": 123, "bar": "hello"})
print_list([1,2,3,4,5,6,7,8,8,8,8])
print_tuple((1,2,3,4,5,6,7,8,8,8,8))
print_set({1,2,3,4,5,6,7,8,8,8,8})
```

## Accepting *args and **kwargs

- We define a new function called `calculate` that takes any number of positional and keyword arguments, and calculates the sum of all of them.

- The `py::args` object represents all of the positional arguments passed to the function, and the `py::kwargs` object represents all of the keyword arguments passed to the function. We iterate over both of these objects and add up their values, casting them to integers using `py::cast<int>`.

```python
from mymodule import *

calculate(1, 2, 3, a=4, b=5)
```

## Allow/Prohibiting None arguments

- pybind allows None to be passed from Python which results in calling the C++ function with nullptr (or an empty holder) for the argument.

```python
from mymodule import *

bark(Dog())
meow(Cat())
bark(None)
meow(None)
```

