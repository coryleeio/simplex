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
	src/programme.cpp
	src/window.cpp
	src/logger.cpp
)

include_directories(${INCLUDE_DIRS})

add_library( SimplexRenderer ${SOURCE_FILES})
target_link_libraries( SimplexRenderer libglew_static glfw ${GLFW_LIBRARIES})


add_executable( demo1 tests/demo1/demo1.cpp)
add_executable( demo2 tests/demo2/demo2.cpp)
target_link_libraries(demo1 SimplexRenderer)
target_link_libraries(demo2 SimplexRenderer)

ADD_DEFINITIONS(-DGLEW_STATIC)
