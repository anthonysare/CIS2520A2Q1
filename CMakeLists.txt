cmake_minimum_required(VERSION 3.12)
project(2520A2 C)

set(CMAKE_C_STANDARD 99)

add_executable(2520A2fw  fileWriter.c helper.c helper.h)
add_executable(2520A2  main.c helper.c helper.h)