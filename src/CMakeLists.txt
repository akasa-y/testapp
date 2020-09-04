cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -Wall -O0 -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -Wall -O0 -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

include_directories(include)
add_subdirectory(main_task)
add_subdirectory(sub1)
add_subdirectory(sub2)
add_subdirectory(linux)
add_executable(testapp main.c)
target_link_libraries(testapp Main_task Linux  Sub1 Sub2 -lpthread)
