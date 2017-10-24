cmake_minimum_required(VERSION 2.6)
project(test_parti)

add_executable(test_parti main.cpp)

install(TARGETS test_parti RUNTIME DESTINATION bin)
