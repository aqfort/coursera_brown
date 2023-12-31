cmake_minimum_required(VERSION 3.25)
project(test_runner_lib)
set(CMAKE_CXX_STANDARD 26)

add_library(${PROJECT_NAME} test_runner.h test_runner.cpp)
