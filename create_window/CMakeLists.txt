cmake_minimum_required(VERSION 3.5)
project(create_window)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(create_window ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)

target_include_directories(create_window PUBLIC ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})
target_link_libraries(create_window ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES} ${GLFW_STATIC_LIBRARIES})

