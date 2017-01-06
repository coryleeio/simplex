#ifndef SIMPLEX_MESH_H
#define SIMPLEX_MESH_H
#include <common.h>

namespace Simplex
{
	class Mesh 
	{
		public:
			Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
			void render();
		private:
			GLuint vao = 0;
			GLuint vbo = 0;
			GLuint ibo = 0;
			int numVertices = 0;
	};
}
#endif