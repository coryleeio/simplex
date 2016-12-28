
#include <core.h>
#define GL_LOG_FILE "gl.log"

int main() {

  Simplex::Window window;
  float points[] = {
     0.0f,  0.5f,  0.0f,
     0.5f, -0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f
  };
  
  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  Simplex::Shader vertexShader("../res/shaders/test.vert", GL_VERTEX_SHADER);
  Simplex::Shader fragmentShader("../res/shaders/test.frag", GL_FRAGMENT_SHADER);
  Simplex::Programme programme(vertexShader, fragmentShader);
  programme.activate();
  programme.setVector4f("inputColour", 0.5f, 0.0f, 0.5f, 1.0f);

  while(!window.shouldClose()) {
    window.clear();
    glBindVertexArray(vao);
    // draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // update other events like input handling  
    window.draw();
  }

  // close GL context and any other GLFW resources
  glfwTerminate();
  return 0;
}