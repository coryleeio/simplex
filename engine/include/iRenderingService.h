#ifndef SIMPLEX_INTERFACE_RENDERER_SERVICE_H
#define SIMPLEX_INTERFACE_RENDERER_SERVICE_H
#include <common.h>
#include <mesh.h>
namespace Simplex
{
	class IRenderingService 
	{
		public:
			virtual void drawMesh(Mesh* mesh) = 0;
			virtual Mesh* loadMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) = 0;
	};
}
#endif