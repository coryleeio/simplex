cmake_minimum_required(VERSION 3.7.1)
project (simplex)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(deps)

set (DEPENDENCIES 
	simplexEngine/include
	deps/glfw/include
 	deps/glew/include
 	deps/assimp/include
)

include_directories(${DEPENDENCIES})

add_subdirectory(simplexEngine)

add_executable( renderingTest tests/renderingTest.cpp)
target_link_libraries(
	renderingTest
	simplexEngine
)


add_executable( coreTest tests/coreTest.cpp)
target_link_libraries(
	coreTest
	simplexEngine
)
