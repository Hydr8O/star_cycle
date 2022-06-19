cmake_minimum_required(VERSION 3.0.0)
project(star_cycle VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(star_cycle main.cpp)
add_subdirectory(vendor)
add_subdirectory(libs)
find_package(glfw3 3.3 REQUIRED)
include(CPack)

target_include_directories(star_cycle PRIVATE
    ${CMAKE_SOURCE_DIR}/vendor/glad/include
    ${CMAKE_SOURCE_DIR}/libs/shader/include
    ${CMAKE_SOURCE_DIR}/libs/graphics/include
)

target_link_libraries(star_cycle graphics shader glfw glad)