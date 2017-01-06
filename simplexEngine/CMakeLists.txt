
set (HEADER_FILES
	include/common.h
	include/math3d.h
	include/program.h
	include/shader.h
	include/simplex.h
	include/transform.h
	include/window.h
	include/mesh.h
	include/core.h
	include/iLoggingService.h
	include/iServiceLocatorService.h
	include/defaultLoggingService.h
	include/defaultServiceLocatorService.h
)

set (SOURCE_FILES
	src/shader.cpp
	src/program.cpp
	src/window.cpp
	src/math3d.cpp
	src/transform.cpp
	src/mesh.cpp
	src/core.cpp
	src/defaultLoggingService.cpp
	src/defaultServiceLocatorService.cpp
)

ADD_DEFINITIONS(-DGLEW_STATIC)
add_library( simplexEngine STATIC ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(
	simplexEngine
	libglew_static
	glfw
	${GLFW_LIBRARIES}
)




