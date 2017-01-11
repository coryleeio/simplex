
set (HEADER_FILES
	include/common.h
	include/math3d.h
	include/simplex.h
	include/transform.h
	include/mesh.h
	include/core.h
	include/iLoggingService.h
	include/iServiceLocatorService.h
	include/iRenderingService.h
	include/defaultLoggingService.h
	include/defaultServiceLocatorService.h
)

set (SOURCE_FILES
	src/math3d.cpp
	src/transform.cpp
	src/mesh.cpp
	src/core.cpp
	src/defaultLoggingService.cpp
	src/defaultServiceLocatorService.cpp
)

add_library( simplex_engine STATIC ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(
	simplex_engine
	simplex_gl
)




