add_executable( simplex_gl_render renderGL.cpp )
target_link_libraries(
	simplex_gl_render
	simplex_engine
)

add_executable( simplex_core_init coreInit.cpp )
target_link_libraries(
	simplex_core_init
	simplex_engine
)