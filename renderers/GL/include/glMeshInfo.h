#ifndef SIMPLEX_GL_MESH_INFO_H
#define SIMPLEX_GL_MESH_INFO_H
#include <mesh.h>

namespace Simplex
{
	struct GLMeshInfo 
	{	
		GLMeshInfo(GLuint vao, int numVertices);
		GLuint vao;
		int numVertices;
	};
}
#endif