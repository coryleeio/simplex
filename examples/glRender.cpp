
#include <simplex.h>
#include <math.h>

int main() {
  Simplex::Core core;
  core.initialize();
  Simplex::IServiceLocatorService* services = core.getServiceLocatorService();
  Simplex::IRenderingService* renderer = services->getRenderingService();

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

  Simplex::Mesh* mesh = renderer->loadMesh(vertices, indices);
  float input = 0.001f;
  Simplex::Transform transform;

  while(!renderer->shouldCloseWindow()) {

    // this will later be moved into the components update() method.
    transform.setPosition(0.0f, 0.0f, 0.0f);
    transform.setRotation(572.958 * sinf(input), 0.0f, 0.0f);
    transform.setScale(1.0f, 1.0f, 1.0f);
    input += 0.001f;

    // this will later be moved all into the renderer, when the transform information
    // for the actor is available elsewhere.
    renderer->clearWindow();
    renderer->drawMesh(mesh, &transform);
    renderer->drawWindow();

    // once these are done, the main loop can be extracted into core start method
  }
  return 0;
}