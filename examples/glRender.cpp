
#include <simplex.h>
#include <glRenderingService.h>
#include <math.h>

int main() {
  Simplex::GLWindow window;

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

  Simplex::GLRenderingService renderer;
  Simplex::Mesh* mesh = renderer.loadMesh(vertices, indices);
  // TODO: fix relative path
  Simplex::GLShader vertexShader("../../renderers/GL/resources/default.vert", GL_VERTEX_SHADER);
  Simplex::GLShader fragmentShader("../../renderers/GL/resources/default.frag", GL_FRAGMENT_SHADER);
  Simplex::GLProgram program(vertexShader, fragmentShader);
  program.use();
   
  /* World translation matrix row-major */
  float input = 0.001f;
  float scale = 0.001f;
  Simplex::Transform transform;

  while(!window.shouldClose()) {
    transform.setPosition(0.0f, 0.0f, 0.0f);
    transform.setRotation(572.958 * sinf(input), 0.0f, 0.0f);
    transform.setScale(1.0f, 1.0f, 1.0f);
   
    input += 0.001f;

    program.setMatrix4f("gWorld", *(transform.getTransformMatrix()));
    window.clear();
    renderer.drawMesh(mesh);
    // update other events like input handling  
    window.draw();
  }

  // close GL context and any other GLFW resources
  glfwTerminate();
  return 0;
}