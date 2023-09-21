cmake_minimum_required(VERSION 3.27)

project(coords_test)

find_package(GTest CONFIG REQUIRED)

enable_testing()

add_executable(
  coords_test
  coords_test.cpp
)
target_link_libraries(
  coords_test
  GTest::gtest
  coords
)

include(GoogleTest)
gtest_discover_tests(coords_test)
