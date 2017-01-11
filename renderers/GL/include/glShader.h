#ifndef SHADER_H
#define SHADER_H
#include <common.h>
namespace Simplex
{
	class GLShader 
	{
		public:
			GLShader(const char *filename, GLenum shaderType);
			GLuint getShaderId();
		private:
			GLuint shaderId;
	};
}

#endif