cmake_minimum_required(VERSION 2.6)
project(test_part1)
find_package(OpenCV REQUIRED)
 
include_directories(include/)

add_executable(test_part1 main.cpp src/handler.cpp)
target_link_libraries(test_part1 ${OpenCV_LIBS})
install(TARGETS test_part1 RUNTIME DESTINATION bin)
