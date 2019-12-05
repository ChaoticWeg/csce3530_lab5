cmake_minimum_required(VERSION 3.10)
project(3530_Lab5 C)

set(CMAKE_C_STANDARD 99)
set(LIBS graph common dijkstra)

add_subdirectory(lib)
add_executable(sml0262 main.c)

target_link_libraries(sml0262 LINK_PUBLIC ${LIBS})
