cmake_minimum_required(VERSION 3.10)
project(crcalculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra)

file(GLOB SOURCES "*.cpp")

add_executable(crcalculator ${SOURCES})

target_link_libraries(crcalculator gcc_s gcc)
