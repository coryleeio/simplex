#ifndef SIMPLEX_GL_RENDERING_SERVICE_H
#define SIMPLEX_GL_RENDERING_SERVICE_H
#include <glShader.h>
#include <iLoggingService.h>
#include <iRenderingService.h>
#include <math3d.h>
#include <mesh.h>
#include <glMeshInfo.h>
#include <glRenderingService.h>
#include <glShader.h>
#include <glProgram.h>
#include <glWindow.h>


namespace Simplex
{
	class GLRenderingService  : public IRenderingService 
	{
		public:
			GLRenderingService();
			~GLRenderingService();
			void drawMesh(Mesh* mesh);
			void drawMesh(Mesh* mesh, Transform* transform);
			void drawMesh(Camera* camera, Transform* transform, Mesh* mesh);
			void drawWindow();
			void clearWindow();
			bool shouldCloseWindow();
			Mesh* loadMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
			GLWindow* window = NULL;
		private:
			std::vector<Mesh*> meshCollection;
			std::map<int, GLMeshInfo*> meshIdToInfoMap;
			int nextId = 0;
			GLShader* vertexShader = NULL;
			GLShader* fragmentShader = NULL;
			GLProgram* program = NULL;
	};
}
#endif