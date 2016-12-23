#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <fstream>
#include <streambuf>
#include <string>
#include <cerrno>
#include <time.h>
#include <stdarg.h>
#include <assert.h>

namespace SIMPLEX
{
	class Shader {
	public:
		Shader(const char *filename, GLenum shaderType);
		GLuint getShaderId();
	private:
		GLuint shaderId;
	};
}

#endif