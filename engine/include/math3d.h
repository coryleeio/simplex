#ifndef SIMPLEX_MATH3D_H
#define SIMPLEX_MATH3D_H
#include <common.h>

namespace Simplex
{
	struct Vector3f
	{
		float x;
		float y;
		float z;
		Vector3f();
		Vector3f(float x, float y, float z);
		Vector3f(float input);
	};

	struct Vector4f
	{
		float x;
		float y;
		float z;
		float w;
		Vector4f();
		Vector4f(float x, float y, float z, float w);
		Vector4f(const Vector3f& input, float w);
		Vector4f(float input);
	};

	struct Matrix4f
	{
		float m[4][4];
		Matrix4f();
		Matrix4f(float a00, float a01, float a02, float a03,
		         float a10, float a11, float a12, float a13,
		         float a20, float a21, float a22, float a23,
		         float a30, float a31, float a32, float a33);
		Matrix4f(float input);
		Matrix4f operator*(const Matrix4f & right) const;
	};
}

#endif