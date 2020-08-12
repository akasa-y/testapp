cmake_minimum_required(VERSION 3.10)

find_package(GTest REQUIRED)
include(GoogleTest)

#target_link_libraries(GTest::GTest)
include_directories(${PROJECT_SOURCE_DIR}/src/linux ${PROJECT_SOURCE_DIR}/src/include ${PROJECT_SOURCE_DIR}/test/include ${GTEST_INCLUDE_DIRS})

add_library(Test_linux STATIC
    test_os_api.cpp
)

# Google Testの各テストケースごとにCTestのテストを作成する
gtest_add_tests(TARGET Test_linux)
#gtest_discover_tests(Test_linux)

# CTestのテストをひとつだけ作成する
#add_test(NAME AllTests COMMAND TestSample1)
#add_test(NAME Test_linux COMMAND GoogleTest)