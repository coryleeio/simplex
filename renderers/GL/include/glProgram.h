#ifndef SIMPLEX_PROGRAM_H
#define SIMPLEX_PROGRAM_H
#include <glShader.h>
#include <iLoggingService.h>
#include <math3d.h>

namespace Simplex
{
	class GLProgram 
	{
		public:
			GLProgram(GLShader& vertexShader, GLShader& fragmentShader);
			GLuint getProgramId();
			GLuint getVertexShaderId();
			GLuint getFragmentShaderId();
			void setVector4f(const char* inputName, float x, float y, float z, float w);
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