
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
  Simplex::Transform transform1;
  Simplex::Transform transform2;
  Simplex::Transform transform3;
  Simplex::Transform transform4;
  Simplex::PerspectiveProjection* perspectiveProjection = new Simplex::PerspectiveProjection();
  perspectiveProjection->fieldOfView = 30.0f;
  perspectiveProjection->zNear = 1.0f;
  perspectiveProjection->zFar  = 1000.0f;
  perspectiveProjection->viewportWidth = 640.0f;
  perspectiveProjection->viewportHeight = 480.0f;
  Simplex::Camera camera(perspectiveProjection);
  while(!renderer->shouldCloseWindow()) {

    // this will later be moved into the components update() method.
    transform1.setPosition(sinf(input) * 5.0f, cosf(input) * 5.0f * sinf(input), 30.0f);
    transform1.setRotation(0.0f, 100.0f * sinf(input), 100.0f * sinf(input));
    transform1.setScale(1.0f, 1.0f, 1.0f);

    transform2.setPosition(-1.0f * cosf(input), sinf(input), sinf(input)* 15.0f + 15.0f);
    transform2.setRotation(100.0f * sinf(input), 0.0f, 0.0f);
    transform2.setScale(1.0f, 1.0f, 1.0f);

    transform3.setPosition(1.0f, 0.0f, cosf(input) * 15.0f + 15.0f);
    transform3.setRotation(40.0f, 0.0f, 200.0f * cosf(input));
    transform3.setScale(1.0f, 1.0f, 1.0f);

    transform4.setPosition(cosf(input) * 5.0f, sinf(input) * 5.0f * sinf(input), 30.0f);
    transform4.setRotation(0.0f, 100.0f * cosf(input), 100.0f * cosf(input));
    transform4.setScale(1.0f, 1.0f, 1.0f);

    input += 0.001f;

    // this will later be moved all into the renderer, when the transform information
    // for the actor is available elsewhere.
    renderer->clearWindow();
    renderer->drawMesh(&camera, &transform1, mesh);
    renderer->drawMesh(&camera, &transform2, mesh);
    renderer->drawMesh(&camera, &transform3, mesh);
    renderer->drawMesh(&camera, &transform4, mesh);
    renderer->drawWindow();

    // once these are done, the main loop can be extracted into core start method
  }
  return 0;
}