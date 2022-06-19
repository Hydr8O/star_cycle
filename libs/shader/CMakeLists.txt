add_library(shader src/shader_program.cpp)
target_include_directories(shader PRIVATE include ${CMAKE_SOURCE_DIR}/vendor/glad/include)