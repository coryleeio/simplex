#ifndef SIMPLEX_CAMERA_H
#define SIMPLEX_CAMERA_H
#include <common.h>
#include <perspectiveProjection.h>
#include <math3d.h>
namespace Simplex
{
	class Camera
	{
		public:
			Camera(PerspectiveProjection* p);
			~Camera();
			const Matrix4f* getCameraTransformMatrix();
		private:
			Vector3f position;
			Vector3f target;
			Vector3f up;
			Matrix4f perspectiveProjectionMatrix;
			PerspectiveProjection* perspectiveProjection;
			Matrix4f cameraTransformMatrix;
	};
}
#endif