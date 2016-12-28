#ifndef SHADER_H
#define SHADER_H
#include <common.h>

namespace Simplex
{
	class Shader 
	{
		public:
			Shader(const char *filename, GLenum shaderType);
			GLuint getShaderId();
		private:
			GLuint shaderId;
	};
}

#endif