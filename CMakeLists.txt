cmake_minimum_required(VERSION 3.7.1)
project (simplex)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(dependencies)

set (DEPENDENCIES 
	engine/include
	renderers/GL/include
	dependencies/glfw/include
 	dependencies/glew/include
 	dependencies/assimp/include
)

include_directories(${DEPENDENCIES})

add_subdirectory(renderers)
add_subdirectory(engine)
add_subdirectory(examples)
