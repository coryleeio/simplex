#ifndef SIMPLEX_PERSPECTIVE_PROJECTION_H
#define SIMPLEX_PERSPECTIVE_PROJECTION_H
#include <common.h>

namespace Simplex
{
	struct PerspectiveProjection 
	{
		float viewportWidth; 
		float viewportHeight;
		float zNear;           // Distance from near clip plane
		float zFar;            // Distance from far clip plane
		float fieldOfView;     // Degrees
	};
}
#endif