set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++") 
set(CMAKE_EXE_LINKER_FLAGS "-stdlib=libc++")
cmake_minimum_required(VERSION 3.7.1)
project (simplex)


add_subdirectory(deps)

set (INCLUDE_DIRS 
	include
	deps/glfw/include
 	deps/glew/include
 	deps/assimp/include/assimp
)

set (SOURCE_FILES
	src/shader.cpp
	src/program.cpp
	src/window.cpp
	src/logger.cpp
	src/math3d.cpp
	src/transform.cpp
	src/mesh.cpp
)

include_directories(${INCLUDE_DIRS})

add_library( SimplexRenderer ${SOURCE_FILES})
target_link_libraries( SimplexRenderer libglew_static glfw ${GLFW_LIBRARIES})

add_executable( renderingTest tests/renderingTest.cpp)
target_link_libraries(renderingTest SimplexRenderer)

ADD_DEFINITIONS(-DGLEW_STATIC)
