#ifndef PROGRAM_H
#define PROGRAM_H
#include <common.h>
#include <shader.h>
#include <logger.h>

namespace Simplex
{
	extern Logger logger;
	class Program 
	{
		public:
			Program(Shader& vertexShader, Shader& fragmentShader);
			GLuint getProgramId();
			GLuint getVertexShaderId();
			GLuint getFragmentShaderId();
			void setVector4f(const char* inputName, float x,float y,float z,float w);
			void setMatrix4f(const char* inputName, Matrix4f inputMatrix);
			void setFloat(const char* inputName, float x);
			void use();
		private:
			GLuint vertexShaderId;
			GLuint fragmentShaderId;
			GLuint programId;
	};
}
#endif