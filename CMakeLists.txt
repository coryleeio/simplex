project (hello)
cmake_minimum_required(VERSION 3.7.1)

add_subdirectory(deps)

find_package(OpenGL REQUIRED)

set (
      INCLUDE_DIRS
      include
      ${OPENGL_INCLUDE_DIRS}
    )

include_directories( ${INCLUDE_DIRS} )

add_executable(hello src/helloworld.cpp)
target_link_libraries(hello ${OPENGL_INCLUDE_DIRS})