cmake_minimum_required(VERSION 3.21)
project(brainfuck C)

set(CMAKE_C_STANDARD 23)

add_executable(brainfuck main.c Interpreter.h Interpreter.c)
