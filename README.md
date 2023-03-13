# Installation

## Docker

- Dockerfile

https://hub.docker.com/r/hienanh/pybind11

- Run

```bash
docker run --name pybind11 -it -d -v $(pwd):/root/pybind hienanh/pybind11:latest
```

## Format C++ code

```bash
apt install clang-format -y
clang-format -style=microsoft -dump-config > .clang-format
sed -i 's/AlwaysBreakTemplateDeclarations: MultiLine/AlwaysBreakTemplateDeclarations: Yes/g' .clang-format

# To use
find . -regex '.*\.\(c\|cc\|cpp\|cxx\|cu\|h\|hh\|hpp\|hxx\|inl\|inc\|ipp\|m\|mm\)$' -exec clang-format -style=file -i {} \;
```


## Pre-commit

```
python3 -m pip install pre-commit
pre-commit install      # runs every time you commit in git
pre-commit run -a       # To use
pre-commit autoupdate   # To update this file
```

# [First steps](First-steps)

# [Object-oriented code](Object-oriented-code)

# [Functions](Functions)
