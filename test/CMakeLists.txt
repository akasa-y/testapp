cmake_minimum_required(VERSION 3.10)

find_package(GTest REQUIRED)
include(GoogleTest)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -Wall -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -Wall -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

add_subdirectory(linux)
add_subdirectory(main_task)
