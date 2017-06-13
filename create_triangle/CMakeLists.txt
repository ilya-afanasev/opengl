cmake_minimum_required(VERSION 3.7)
project(create_triangle)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp shader.h shader.cpp)
add_executable(create_triangle ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)

target_include_directories(create_triangle PUBLIC ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})
target_link_libraries(create_triangle ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES} ${GLFW_STATIC_LIBRARIES})
