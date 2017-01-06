#include <mesh.h>

namespace Simplex
{
	Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
	{
		numVertices = vertices.size();

		// Create vao
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Create vbo to put in VAO
		glGenBuffers(1, &vbo); // generate 1 buffer at location of vbo
		glBindBuffer(GL_ARRAY_BUFFER, vbo); // set global variable 'GL_ARRAY_BUFFER' to vbo
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(float), &vertices[0], GL_STATIC_DRAW); // write data into GL_ARRAY_BUFFER, that we just set
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);/* Copy into VAO: Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex  */
		glEnableVertexAttribArray(0); /* enables attribute 0 (see location 0) in the vertex shader.  If this wasn't called, attribute 0 can't be used for rendering.  It doesnt have to be done here, but it must be done before render*/

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numVertices * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		
		glBindVertexArray(0); // unbind so this isnt modified by anyone
	}

	void Mesh::render()
	{
		glBindVertexArray(vao); // bind the vao we are going to draw
		glDrawElements(GL_TRIANGLES, numVertices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0); // unbind so this isnt modified by anyone
	}
}