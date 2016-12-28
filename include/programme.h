#ifndef PROGRAMME_H
#define PROGRAMME_H
#include <common.h>
#include <shader.h>
#include <logger.h>

namespace Simplex
{
	extern Logger logger;
	class Programme 
	{
		public:
			Programme(Shader& vertexShader, Shader& fragmentShader);
			GLuint getProgrammeId();
			GLuint getVertexShaderId();
			GLuint getFragmentShaderId();
			void setVector4f(const char* inputName, float x,float y,float z,float w);
			void setFloat(const char* inputName, float x);
			void activate();
		private:
			GLuint vertexShaderId;
			GLuint fragmentShaderId;
			GLuint programmeId;
	};
}
#endif