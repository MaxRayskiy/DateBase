cmake_minimum_required(VERSION 3.15)
project(qs)

set(CMAKE_CXX_STANDARD 17)

add_executable(qs main.cpp condition_parser.cpp condition_parser.h token.cpp token.h date.cpp date.h database.cpp database.h node.cpp node.h condition_parser_tests.cpp)