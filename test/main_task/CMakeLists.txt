cmake_minimum_required(VERSION 3.10)

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(TestMainTask test_main_task.cpp)
target_link_libraries(TestMainTask GTest::GTest GTest::Main)
include_directories(${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/src/include ${PROJECT_SOURCE_DIR}/test/include ${GTEST_INCLUDE_DIRS})

# Google Testの各テストケースごとにCTestのテストを作成する
gtest_add_tests(TARGET TestMainTask)
