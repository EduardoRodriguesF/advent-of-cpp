cmake_minimum_required(VERSION 3.27)

project(RopePhysics)

set(SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(SOURCES "${SRC_DIR}/main.cpp")

include_directories(lib)
add_subdirectory(lib/coords)
add_subdirectory(lib/split)
add_subdirectory(lib/rope)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE coords split rope)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
	CMAKE_EXPORT_COMPILE_COMMANDS ON
)
