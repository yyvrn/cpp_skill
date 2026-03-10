cmake_minimum_required(VERSION 3.10)
project(CarProject VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Единственный исходный файл
add_executable(${PROJECT_NAME} main.cpp)