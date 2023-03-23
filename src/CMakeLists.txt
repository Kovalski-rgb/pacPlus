cmake_minimum_required(VERSION 3.26)
project(PacPlus)
add_executable(PacMan main.cpp)

target_link_libraries(PacMan PRIVATE -lncurses)
