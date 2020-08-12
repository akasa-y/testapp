cmake_minimum_required(VERSION 3.10)

find_package(GTest REQUIRED)
include(GoogleTest)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

add_executable(GoogleTest Test_main.cpp linux/test_os_api.cpp)
target_link_libraries(GoogleTest GTest::GTest)
include_directories(${PROJECT_SOURCE_DIR}/src/linux ${PROJECT_SOURCE_DIR}/src/include ${PROJECT_SOURCE_DIR}/test/include ${GTEST_INCLUDE_DIRS})

#add_subdirectory(linux)
#target_link_libraries(GoogleTest Test_linux GTest::GTest GTest::Main)
#include_directories(${PROJECT_SOURCE_DIR}/src/linux ${PROJECT_SOURCE_DIR}/src/include ${PROJECT_SOURCE_DIR}/test/include ${GTEST_INCLUDE_DIRS})

# Google Testの各テストケースごとにCTestのテストを作成する
gtest_add_tests(TARGET GoogleTest)
#gtest_discover_tests(GoogleTest TEST_PREFIX new:)

# CTestのテストをひとつだけ作成する
#add_test(NAME AllTests COMMAND TestSample1)

#add_test(NAME GoogleTest COMMAND GoogleTest)
