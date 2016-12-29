project (simplex)
cmake_minimum_required(VERSION 3.7.1)

add_subdirectory(deps)

set (INCLUDE_DIRS 
	include
	deps/glfw/include
 	deps/glew/include
)

set (SOURCE_FILES
	src/shader.cpp
	src/program.cpp
	src/window.cpp
	src/logger.cpp
)

include_directories(${INCLUDE_DIRS})

add_library( SimplexRenderer ${SOURCE_FILES})
target_link_libraries( SimplexRenderer libglew_static glfw ${GLFW_LIBRARIES})


add_executable( 4shaders tests/4shaders/4shaders.cpp)
target_link_libraries(4shaders SimplexRenderer)

add_executable( 5uniforms tests/5uniforms/5uniforms.cpp)
target_link_libraries(5uniforms SimplexRenderer)

add_executable( 6translation tests/6translation/6translation.cpp)
target_link_libraries(6translation SimplexRenderer)

add_executable( 7_2drotation tests/7_2drotation/7_2drotation.cpp)
target_link_libraries(7_2drotation SimplexRenderer)

add_executable( 8scale tests/8scale/8scale.cpp)
target_link_libraries(8scale SimplexRenderer)

add_executable( 9interpolation tests/9interpolation/9interpolation.cpp)
target_link_libraries(9interpolation SimplexRenderer)

ADD_DEFINITIONS(-DGLEW_STATIC)
