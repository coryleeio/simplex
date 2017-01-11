
set (HEADER_FILES
	include/glProgram.h
	include/glShader.h
	include/glWindow.h
	include/glRenderingService.h
	include/glMeshInfo.h
)

set (SOURCE_FILES
	src/glProgram.cpp
	src/glShader.cpp
	src/glWindow.cpp
	src/glRenderingService.cpp
	src/glMeshInfo.cpp
)

include_directories(include)

ADD_DEFINITIONS(-DGLEW_STATIC)
add_library( simplex_gl STATIC ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(
	simplex_gl
	libglew_static
	glfw
	${GLFW_LIBRARIES}
)




