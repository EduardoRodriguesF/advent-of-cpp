cmake_minimum_required(VERSION 3.27)

project(coords_test)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(GTest CONFIG REQUIRED)

enable_testing()

add_executable(coords_test coords_test.cpp)
target_link_libraries(coords_test coords gtest_main)
add_test(NAME coords_test COMMAND coords)
