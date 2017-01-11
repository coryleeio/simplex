#ifndef SIMPLEX_GL_RENDERING_SERVICE_H
#define SIMPLEX_GL_RENDERING_SERVICE_H
#include <glShader.h>
#include <iLoggingService.h>
#include <iRenderingService.h>
#include <math3d.h>
#include <mesh.h>
#include <glMeshInfo.h>
#include <glRenderingService.h>


namespace Simplex
{
	class GLRenderingService  : public IRenderingService 
	{
		public:
			~GLRenderingService();
			void drawMesh(Mesh* mesh);
			Mesh* loadMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
		private:
			std::vector<Mesh*> meshCollection;
			std::map<int, GLMeshInfo*> meshIdToInfoMap;
			int nextId = 0;
	};
}
#endif