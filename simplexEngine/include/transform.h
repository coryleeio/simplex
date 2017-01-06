#ifndef SIMPLEX_TRANSFORM_H
#define SIMPLEX_TRANSFORM_H
#include <common.h>
#include <math3d.h>

namespace Simplex
{
	class Transform 
	{
		public:
			Transform();
			void setPosition(float x, float y, float z);
			void setRotation(float yaw, float pitch, float roll);
			void setScale(float scaleX, float scaleY, float scaleZ);
			const Matrix4f* getTransformMatrix();
		private:
			Vector3f position;
			Vector3f rotation;
			Vector3f scale;

			Matrix4f translationMatrix;
			Matrix4f rotationMatrix;
			Matrix4f scaleMatrix;
			
			Matrix4f transformMatrix;
	};
}
#endif