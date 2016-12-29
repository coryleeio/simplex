
#include <core.h>
#include <math.h>
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

  Simplex::Shader vertexShader("../tests/9interpolation/shader.vert", GL_VERTEX_SHADER);
  Simplex::Shader fragmentShader("../tests/9interpolation/shader.frag", GL_FRAGMENT_SHADER);
  Simplex::Program program(vertexShader, fragmentShader);
  program.activate();
   
  /* World translation matrix row-major */
  float input = 0.001f;
  Matrix4f gworld;


  while(!window.shouldClose()) {
    input += 0.0001f;
    gworld.m[0][0] = sinf(input); gworld.m[0][1] = 0.0f; gworld.m[0][2] = 0.0f; gworld.m[0][3] = 0.0f;
    gworld.m[1][0] = 0.0f; gworld.m[1][1] = sinf(input); gworld.m[1][2] = 0.0f; gworld.m[1][3] = 0.0f;
    gworld.m[2][0] = 0.0f; gworld.m[2][1] = 0.0f; gworld.m[2][2] = sinf(input); gworld.m[2][3] = 0.0f;
    gworld.m[3][0] = 0.0f; gworld.m[3][1] = 0.0f; gworld.m[3][2] = 0.0f; gworld.m[3][3] = 1.0f;
    program.setMatrix4f("gWorld", gworld);
    input += 0.001f;
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