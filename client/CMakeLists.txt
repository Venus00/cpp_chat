cmake_minimum_required(VERSION 3.10)
project(Main)
add_executable(Main src/main.cpp)
target_link_libraries(Main PRIVATE ws2_32)