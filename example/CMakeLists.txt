cmake_minimum_required(VERSION 3.0.0)
project(confmaster_example VERSION 0.1.0)

add_executable(confmaster_example example.cpp)
target_link_libraries(confmaster_example PRIVATE confmaster)