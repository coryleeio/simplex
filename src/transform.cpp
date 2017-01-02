#include <transform.h>

namespace Simplex
{
	static float degreesToRadians(float degrees)
	{
		return degrees * 3.141592653589793 / 180.0f;
	}

	static void updateScaleTransform(const Vector3f& input, Matrix4f& output)
	{
	    output.m[0][0] = input.x; output.m[0][1] = 0.0f;   output.m[0][2] = 0.0f;   output.m[0][3] = 0.0f;
	    output.m[1][0] = 0.0f;   output.m[1][1] = input.y; output.m[1][2] = 0.0f;   output.m[1][3] = 0.0f;
	    output.m[2][0] = 0.0f;   output.m[2][1] = 0.0f;   output.m[2][2] = input.z; output.m[2][3] = 0.0f;
	    output.m[3][0] = 0.0f;   output.m[3][1] = 0.0f;   output.m[3][2] = 0.0f;   output.m[3][3] = 1.0f;
	}

	static void updateRotationTransform(const Vector3f& input, Matrix4f& output)
	{
	    Matrix4f rx, ry, rz, ret;

	    const float x = degreesToRadians(input.x);
	    const float y = degreesToRadians(input.y);
	    const float z = degreesToRadians(input.z);

	    rx.m[0][0] = 1.0f; rx.m[0][1] = 0.0f   ; rx.m[0][2] = 0.0f    ; rx.m[0][3] = 0.0f;
	    rx.m[1][0] = 0.0f; rx.m[1][1] = cosf(x); rx.m[1][2] = -sinf(x); rx.m[1][3] = 0.0f;
	    rx.m[2][0] = 0.0f; rx.m[2][1] = sinf(x); rx.m[2][2] = cosf(x) ; rx.m[2][3] = 0.0f;
	    rx.m[3][0] = 0.0f; rx.m[3][1] = 0.0f   ; rx.m[3][2] = 0.0f    ; rx.m[3][3] = 1.0f;

	    ry.m[0][0] = cosf(y); ry.m[0][1] = 0.0f; ry.m[0][2] = -sinf(y); ry.m[0][3] = 0.0f;
	    ry.m[1][0] = 0.0f   ; ry.m[1][1] = 1.0f; ry.m[1][2] = 0.0f    ; ry.m[1][3] = 0.0f;
	    ry.m[2][0] = sinf(y); ry.m[2][1] = 0.0f; ry.m[2][2] = cosf(y) ; ry.m[2][3] = 0.0f;
	    ry.m[3][0] = 0.0f   ; ry.m[3][1] = 0.0f; ry.m[3][2] = 0.0f    ; ry.m[3][3] = 1.0f;

	    rz.m[0][0] = cosf(z); rz.m[0][1] = -sinf(z); rz.m[0][2] = 0.0f; rz.m[0][3] = 0.0f;
	    rz.m[1][0] = sinf(z); rz.m[1][1] = cosf(z) ; rz.m[1][2] = 0.0f; rz.m[1][3] = 0.0f;
	    rz.m[2][0] = 0.0f   ; rz.m[2][1] = 0.0f    ; rz.m[2][2] = 1.0f; rz.m[2][3] = 0.0f;
	    rz.m[3][0] = 0.0f   ; rz.m[3][1] = 0.0f    ; rz.m[3][2] = 0.0f; rz.m[3][3] = 1.0f;
	    ret = rz * ry * rx;

	    // Copy.  this is inefficient, could shore it up later
	    output.m[0][0] = ret.m[0][0]; output.m[0][1] = ret.m[0][1]; output.m[0][2] = ret.m[0][2]; output.m[0][3] = ret.m[0][3];
	    output.m[1][0] = ret.m[1][0]; output.m[1][1] = ret.m[1][1]; output.m[1][2] = ret.m[1][2]; output.m[1][3] = ret.m[1][3];
	    output.m[2][0] = ret.m[2][0]; output.m[2][1] = ret.m[2][1]; output.m[2][2] = ret.m[2][2]; output.m[2][3] = ret.m[2][3];
	    output.m[3][0] = ret.m[3][0]; output.m[3][1] = ret.m[3][1]; output.m[3][2] = ret.m[3][2]; output.m[3][3] = ret.m[3][3];
	}

	static void updateTranslationTransform(const Vector3f& input, Matrix4f& output)
	{
		output.m[0][0] = 1.0f; output.m[0][1] = 0.0f; output.m[0][2] = 0.0f; output.m[0][3] = input.x;
		output.m[1][0] = 0.0f; output.m[1][1] = 1.0f; output.m[1][2] = 0.0f; output.m[1][3] = input.y;
		output.m[2][0] = 0.0f; output.m[2][1] = 0.0f; output.m[2][2] = 1.0f; output.m[2][3] = input.z;
		output.m[3][0] = 0.0f; output.m[3][1] = 0.0f; output.m[3][2] = 0.0f; output.m[3][3] = 1.0f;
	}

	Transform::Transform()
	{
		setPosition(0.0f, 0.0f, 0.0f);
		setRotation(0.0f, 0.0f, 0.0f);
		setScale(1.0f, 1.0f, 1.0f);
	}

	void Transform::setPosition(float x, float y, float z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
	}

	void Transform::setRotation(float x, float y, float z)
	{
		rotation.x = x;
		rotation.y = y;
		rotation.z = z;
	}

	void Transform::setScale(float scaleX, float scaleY, float scaleZ)
	{
		scale.x = scaleX;
		scale.y = scaleY;
		scale.z = scaleZ;
	}
	
	const Matrix4f* Transform::getTransformMatrix()
	{
		updateTranslationTransform(position, translationMatrix);
		updateRotationTransform(rotation, rotationMatrix);
		updateScaleTransform(scale, scaleMatrix);
		transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;
		return &transformMatrix;
	}
}