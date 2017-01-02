
#include <core.h>
#include <math.h>
#define GL_LOG_FILE "gl.log"

int main() {
  Simplex::Window window;

  std::vector<float> vertices = {
    -1.0f, -1.0f, 0.0f,    // 0
     0.0f, -1.0f, 1.0f,    // 1
     1.0f, -1.0f, 0.0f,    // 2
     0.0f,  1.0f, 0.0f     // 3
  };

  std::vector<unsigned int> indices = {
	  0, 3, 1,         // triangle consisting of vertexes with indices 0,3, and 1 from above....
	  1, 3, 2,
	  2, 3, 0,
	  0, 1, 2 
  };

  Simplex::Mesh mesh(vertices, indices);
  Simplex::Shader vertexShader("../res/shaders/simple.vert", GL_VERTEX_SHADER);
  Simplex::Shader fragmentShader("../res/shaders/simple.frag", GL_FRAGMENT_SHADER);
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

    mesh.render();
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0); // Type, num indices, type of indices, byte offset
    // update other events like input handling  
    window.draw();
  }

  // close GL context and any other GLFW resources
  glfwTerminate();
  return 0;
}