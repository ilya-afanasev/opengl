cmake_minimum_required(VERSION 3.15)
project(create_triangle)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp shader.h shader.cpp)
add_executable(create_triangle ${SOURCE_FILES})

find_package(OpenGL REQUIRED)

if(WIN32)
  set(GLFW_INCLUDE_DIRS "$ENV{GLFW_ROOT}/include")
  find_library(GLFW_STATIC_LIBRARIES NAMES glfw3 PATHS ENV GLFW_ROOT PATH_SUFFIXES lib)
elseif(UNIX)
  pkg_search_module(GLFW REQUIRED glfw3)
endif()

set(GLEW_USE_STATIC_LIBS true)
find_package(GLEW REQUIRED)

target_include_directories(create_triangle PUBLIC ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})
target_link_libraries(create_triangle ${OPENGL_gl_LIBRARY} ${GLFW_STATIC_LIBRARIES} ${GLEW_STATIC_LIBRARY})
