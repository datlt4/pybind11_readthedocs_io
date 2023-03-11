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

# Import

```python
import mymodule
mymodule.add_op(1, 2)
mymodule.sub_op(1, 2)
mymodule.mul_op(1, 2)
mymodule.div_op(1, 2)
mymodule.fourty_two
mymodule.get_started
```
