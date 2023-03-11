cmake_minimum_required(VERSION 3.0)
project(mymodule)

find_package(pybind11 REQUIRED)

add_subdirectory(operator)
set(LIB ${LIB} operator)

message(STATUS "sources: ${SRC}")
message(STATUS "includes: ${INC}")

pybind11_add_module(${PROJECT_NAME} mymodule.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${INC})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB})
