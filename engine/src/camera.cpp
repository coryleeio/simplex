#include <camera.h>

namespace Simplex
{
	Camera::Camera(PerspectiveProjection* p)
	{
		perspectiveProjection = p;
	}

	Camera::~Camera()
	{
		delete perspectiveProjection;
	}

	static float degreesToRadians(float degrees)
	{
		return degrees * 3.141592653589793 / 180.0f;
	}

	static void updatePerspectiveProjectionMatrix(PerspectiveProjection* perspectiveProjection, Matrix4f& output)
	{
		const float aspectRatio = perspectiveProjection->viewportWidth / perspectiveProjection->viewportHeight;
		const float zRange = perspectiveProjection->zNear - perspectiveProjection->zFar;
		const float tanHalfFOV = tanf(degreesToRadians(perspectiveProjection->fieldOfView / 2.0));

		output.m[0][0] = 1.0f / (tanHalfFOV * aspectRatio); 
		output.m[0][1] = 0.0f;
		output.m[0][2] = 0.0f;
		output.m[0][3] = 0.0f;

		output.m[1][0] = 0.0f;
		output.m[1][1] = 1.0f / tanHalfFOV; 
		output.m[1][2] = 0.0f; 
		output.m[1][3] = 0.0f;

		output.m[2][0] = 0.0f; 
		output.m[2][1] = 0.0f; 
		output.m[2][2] = (-perspectiveProjection->zNear - perspectiveProjection->zFar) / zRange; 
		output.m[2][3] = 2.0f * perspectiveProjection->zFar * perspectiveProjection->zNear / zRange;

		output.m[3][0] = 0.0f;
		output.m[3][1] = 0.0f; 
		output.m[3][2] = 1.0f; 
		output.m[3][3] = 0.0f;
	}

	const Matrix4f* Camera::getCameraTransformMatrix()
	{
		updatePerspectiveProjectionMatrix(perspectiveProjection, perspectiveProjectionMatrix);
		cameraTransformMatrix = perspectiveProjectionMatrix;
		return &cameraTransformMatrix;
	}
}