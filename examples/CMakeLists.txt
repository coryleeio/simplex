add_executable( simplex_example_gl_render glRender.cpp )
target_link_libraries(
	simplex_example_gl_render
	simplex_engine
)

add_executable( simplex_example_core_init coreInit.cpp )
target_link_libraries(
	simplex_example_core_init
	simplex_engine
)