add_library(graphics STATIC src/drawable.cpp src/circle.cpp src/graphics_engine.cpp)

target_include_directories(graphics PRIVATE 
 include 
 ${CMAKE_SOURCE_DIR}/libs/shader/include 
 ${CMAKE_SOURCE_DIR}/vendor/glad/include
 ${CMAKE_SOURCE_DIR}
)