#include <shader.h>

namespace Simplex
{
	Vector3f::Vector3f() : x(0.0f), y(0.0f),z(0.0f) {}
	Vector3f::Vector3f(float x, float y, float z) : x(x), y(y),z(z) {}
	Vector3f::Vector3f(float input) : x(input), y(input), z(input) {}

	Vector4f::Vector4f() : x(0.0f), y(0.0f),z(0.0f), w(0.0f) {}
	Vector4f::Vector4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	Vector4f::Vector4f(const Vector3f& input, float w) : x(input.x), y(input.y), z(input.z), w(w) {}
	Vector4f::Vector4f(float input) : x(0.0f), y(0.0f),z(0.0f), w(0.0f) {}
	
	Matrix4f::Matrix4f()
	{
		m[0][0] = 0.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 0.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 0.0f; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 0.0f;  
	}

	Matrix4f::Matrix4f(float a00, float a01, float a02, float a03,
				       float a10, float a11, float a12, float a13,
				       float a20, float a21, float a22, float a23,
				       float a30, float a31, float a32, float a33)
	{
		m[0][0] = a00; m[0][1] = a01; m[0][2] = a02; m[0][3] = a03;
		m[1][0] = a10; m[1][1] = a11; m[1][2] = a12; m[1][3] = a13;
		m[2][0] = a20; m[2][1] = a21; m[2][2] = a22; m[2][3] = a23;
		m[3][0] = a30; m[3][1] = a31; m[3][2] = a32; m[3][3] = a33;  
	}
	
	Matrix4f::Matrix4f(float input)
	{
		m[0][0] = input; m[0][1] = input; m[0][2] = input; m[0][3] = input;
		m[1][0] = input; m[1][1] = input; m[1][2] = input; m[1][3] = input;
		m[2][0] = input; m[2][1] = input; m[2][2] = input; m[2][3] = input;
		m[3][0] = input; m[3][1] = input; m[3][2] = input; m[3][3] = input; 
	}
}