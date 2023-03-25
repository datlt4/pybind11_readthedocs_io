cmake_minimum_required(VERSION 3.0)
project(mymodule)

find_package(pybind11 REQUIRED)

add_subdirectory(operator)
set(LIB ${LIB} operator)

message(STATUS "sources: ${SRC}")
message(STATUS "includes: ${INC}")

pybind11_add_module(${PROJECT_NAME} mymodule.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${INC})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB} Python::Python)

find_package(Python REQUIRED COMPONENTS Interpreter Development)

# Get the dist-packages or site-packages directory
execute_process(
  COMMAND
    ${Python_EXECUTABLE} -c
    "from distutils.sysconfig import get_python_lib; print(get_python_lib())"
  OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
  OUTPUT_STRIP_TRAILING_WHITESPACE)
message(STATUS "python_site_packages: ${PYTHON_SITE_PACKAGES}")
# Install the pybind11 project and its subdirectory to the Python site-packages
# directory
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION LIBRARY
                                        ${PYTHON_SITE_PACKAGES})
install(DIRECTORY operator DESTINATION ${PYTHON_SITE_PACKAGES})
