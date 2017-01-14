#include <glRenderingService.h>

namespace Simplex
{
	GLRenderingService::GLRenderingService()
	{
		window = new GLWindow();
		vertexShader = new GLShader("../../renderers/GL/resources/default.vert", GL_VERTEX_SHADER);
		fragmentShader = new GLShader("../../renderers/GL/resources/default.frag", GL_FRAGMENT_SHADER);
		program = new GLProgram(vertexShader, fragmentShader);
		program->use();
	}

	GLRenderingService::~GLRenderingService()
	{
		std::vector<Mesh*>::iterator itr, end;
	    for(itr = meshCollection.begin(), end = meshCollection.end() ; itr != end; ++itr) 
	    {
			delete (*itr);
	    }
	    meshCollection.clear();

	    for(std::map<int, GLMeshInfo*>::iterator itr = meshIdToInfoMap.begin(); itr != meshIdToInfoMap.end(); itr++)
	    {
	        delete itr->second;
	    }
	    meshIdToInfoMap.clear();

	    if(window)
	    {
	    	delete window;
	    }
	    if(vertexShader)
	    {
	    	delete vertexShader;
	    }
	    if(fragmentShader)
	    {
	    	delete fragmentShader;
	    }
	    if(program)
	    {
	    	delete program;
	    }
		glfwTerminate();
	}

	Mesh* GLRenderingService::loadMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
	{
		int numVertices = vertices.size();
		GLuint vao;

		// Create vao
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		GLuint vbo;
		// Create vbo to put in VAO
		glGenBuffers(1, &vbo); // generate 1 buffer at location of vbo
		glBindBuffer(GL_ARRAY_BUFFER, vbo); // set global variable 'GL_ARRAY_BUFFER' to vbo
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(float), &vertices[0], GL_STATIC_DRAW); // write data into GL_ARRAY_BUFFER, that we just set
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Copy into VAO: Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex 
		glEnableVertexAttribArray(0);  // enables attribute 0 (see location 0) in the vertex shader.  If this wasn't called, attribute 0 can't be used for rendering.  It doesnt have to be done here, but it must be done before render

		GLuint ibo;
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numVertices * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		
		glBindVertexArray(0); // unbind so this isnt modified by anyone

		GLMeshInfo* info = new GLMeshInfo(vao, numVertices);
		Mesh* mesh = new Mesh(nextId);
		meshIdToInfoMap[mesh->id] = info;
		meshCollection.push_back(mesh);
		nextId++;
		return mesh;
	}

	void GLRenderingService::drawMesh(Camera* camera, Transform* transform, Mesh* mesh)
	{
		const Matrix4f cameraTransformationMatrix = *(camera->getCameraTransformMatrix());
		const Matrix4f gWorld = *(transform->getTransformMatrix());
		Matrix4f globalWorldViewProjectionMatrix = cameraTransformationMatrix * gWorld;
		program->setMatrix4f("globalWorldViewProjectionMatrix", globalWorldViewProjectionMatrix);
		GLMeshInfo* info = meshIdToInfoMap[mesh->id];
		glBindVertexArray(info->vao); // bind the vao we are going to draw
		glDrawElements(GL_TRIANGLES, info->numVertices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0); // unbind so this isnt modified by anyone
	}

	void GLRenderingService::drawMesh(Mesh* mesh, Transform* transform)
	{
		program->setMatrix4f("globalWorldViewProjectionMatrix", *(transform->getTransformMatrix()));
		GLMeshInfo* info = meshIdToInfoMap[mesh->id];
		glBindVertexArray(info->vao); // bind the vao we are going to draw
		glDrawElements(GL_TRIANGLES, info->numVertices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0); // unbind so this isnt modified by anyone
	}

	void GLRenderingService::drawMesh(Mesh* mesh)
	{
		Transform transform;
		transform.setPosition(0.0f, 0.0f, 0.0f);
		transform.setRotation(0.0f, 0.0f, 0.0f);
		transform.setScale(1.0f, 1.0f, 1.0f);
		drawMesh(mesh, &transform);
	}

	// Temporary pass through to touch renderer window until renderer can stand on its own
	// These methods should definitely go away
	void GLRenderingService::drawWindow()
	{
		window->draw();
	}

	void GLRenderingService::clearWindow()
	{
		window->clear();
	}

	bool GLRenderingService::shouldCloseWindow()
	{
		return window->shouldClose();
	}
}