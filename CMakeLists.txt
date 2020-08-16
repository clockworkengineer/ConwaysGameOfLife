cmake_minimum_required(VERSION 3.0.0)
project(ConwaysGameOfLife VERSION 0.1.0)

add_executable(ConwaysGameOfLife ConwaysGameOfLife.cpp CLife.cpp)
target_link_libraries(ConwaysGameOfLife ncurses)

