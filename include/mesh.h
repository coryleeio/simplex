#ifndef MESH_H
#define MESH_H
#include <prerequisites.h>

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