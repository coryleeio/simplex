project (simplex)
cmake_minimum_required(VERSION 3.7.1)

add_subdirectory(deps)

set (INCLUDE_DIRS 
	include
	deps/glfw/include
 	deps/glew/include
)

include_directories(${INCLUDE_DIRS})

add_executable( shader_test tests/shader_test.cpp src/shader.cpp)
target_link_libraries(shader_test libglew_static glfw ${GLFW_LIBRARIES})

ADD_DEFINITIONS(-DGLEW_STATIC)
