#ifndef SIMPLEX_INTERFACE_RENDERER_SERVICE_H
#define SIMPLEX_INTERFACE_RENDERER_SERVICE_H
#include <common.h>
#include <mesh.h>
#include <camera.h>
#include <transform.h>
namespace Simplex
{
	class IRenderingService 
	{
		public:
			virtual void drawMesh(Mesh* mesh) = 0;
			virtual void drawMesh(Mesh* mesh, Transform* transform) = 0;
			virtual void drawMesh(Camera* camera, Transform* transform, Mesh* mesh) = 0;
			virtual void drawWindow() = 0;
			virtual void clearWindow() = 0;
			virtual bool shouldCloseWindow() = 0;
			virtual Mesh* loadMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) = 0;
	};
}
#endif