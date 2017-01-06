#ifndef SHADER_H
#define SHADER_H
#include <prerequisites.h>
#include <logger.h>
namespace Simplex
{
	extern Logger logger;
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