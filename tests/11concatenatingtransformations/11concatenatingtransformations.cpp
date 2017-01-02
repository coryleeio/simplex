
#include <core.h>
#include <math.h>
#define GL_LOG_FILE "gl.log"

int main() {
  Simplex::Window window;

  float vertices[] = {
   -1.0f, -1.0f, 0.0f,    // 0
    0.0f, -1.0f, 1.0f,    // 1
    1.0f, -1.0f, 0.0f,    // 2
    0.0f,  1.0f, 0.0f     // 3
  };

  unsigned int indices[] = {
	  0, 3, 1,         // triangle consisting of vertexes with indices 0,3, and 1 from above....
	  1, 3, 2,
	  2, 3, 0,
	  0, 1, 2 
  };

  // Create vao
  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Create vbo to put in VAO
  GLuint vbo = 0;
  glGenBuffers(1, &vbo); // generate 1 buffer at location of vbo
  glBindBuffer(GL_ARRAY_BUFFER, vbo); // set global variable 'GL_ARRAY_BUFFER' to vbo
  glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW); // write data into GL_ARRAY_BUFFER, that we just set
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);/* Copy into VAO: Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex  */
  glEnableVertexAttribArray(0); /* enables attribute 0 (see location 0) in the vertex shader.  If this wasn't called, attribute 0 can't be used for rendering.  It doesnt have to be done here, but it must be done before render*/

  GLuint ibo = 0;
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

  Simplex::Shader vertexShader("../tests/11concatenatingtransformations/shader.vert", GL_VERTEX_SHADER);
  Simplex::Shader fragmentShader("../tests/11concatenatingtransformations/shader.frag", GL_FRAGMENT_SHADER);
  Simplex::Program program(vertexShader, fragmentShader);
  program.use();
   
  /* World translation matrix row-major */
  float input = 0.001f;
  float scale = 0.001f;
  Simplex::Transform transform;

  while(!window.shouldClose()) {
    transform.setPosition(0.0f, 0.0f, 0.0f);
    transform.setRotation(572.958 * sinf(input), 0.0f, 0.0f);
    transform.setScale(1.0f, 1.0f, 1.0f);
    program.setMatrix4f("gWorld", *(transform.getTransformMatrix()));
    input += 0.001f;
    window.clear();

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0); // Type, num indices, type of indices, byte offset
    // update other events like input handling  
    window.draw();
  }

  // close GL context and any other GLFW resources
  glfwTerminate();
  return 0;
}