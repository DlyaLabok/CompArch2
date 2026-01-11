cmake_minimum_required(VERSION 3.10)
project(CalculatorProject)

set(CMAKE_CXX_STANDARD 17)

add_library(calculator STATIC calculator.cpp)
add_executable(app main.cpp)
target_link_libraries(app calculator)
