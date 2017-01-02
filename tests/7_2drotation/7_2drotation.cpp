
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
  
  // Create vao
  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Create vbo to put in VAO
  GLuint vbo = 0;
  glGenBuffers(1, &vbo); // generate 1 buffer at location of vbo
  glBindBuffer(GL_ARRAY_BUFFER, vbo); // set global variable 'GL_ARRAY_BUFFER' to vbo
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW); // write data into GL_ARRAY_BUFFER, that we just set
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);/* Copy into VAO: Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex  */
  glEnableVertexAttribArray(0); /* enables attribute 0 (see location 0) in the vertex shader.  If this wasn't called, attribute 0 can't be used for rendering.  It doesnt have to be done here, but it must be done before render */

  Simplex::Shader vertexShader("../tests/7_2drotation/shader.vert", GL_VERTEX_SHADER);
  Simplex::Shader fragmentShader("../tests/7_2drotation/shader.frag", GL_FRAGMENT_SHADER);
  Simplex::Program program(vertexShader, fragmentShader);
  program.use();
   
  /* World translation matrix row-major */
  float input = 0.001f;
  Simplex::Matrix4f gworld;


  while(!window.shouldClose()) {
    input += 0.02f;
    gworld.m[0][0] = cosf(input); gworld.m[0][1] = -sinf(input); gworld.m[0][2] = 0.0f; gworld.m[0][3] = 0.0f;
    gworld.m[1][0] = sinf(input); gworld.m[1][1] = cosf(input); gworld.m[1][2] = 0.0f; gworld.m[1][3] = 0.0f;
    gworld.m[2][0] = 0.0f; gworld.m[2][1] = 0.0f; gworld.m[2][2] = 1.0f; gworld.m[2][3] = 0.0f;
    gworld.m[3][0] = 0.0f; gworld.m[3][1] = 0.0f; gworld.m[3][2] = 0.0f; gworld.m[3][3] = 1.0f;
    program.setMatrix4f("gWorld", gworld);
    input += 0.001f;
    window.clear();
    // draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // update other events like input handling  
    window.draw();
  }

  // close GL context and any other GLFW resources
  glfwTerminate();
  return 0;
}