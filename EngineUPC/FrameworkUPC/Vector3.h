#pragma once

#include <math.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

class Vector3
{
public:
	Vector3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	~Vector3() {}

	float x, y, z;

	float Magnitude()
	{
		return sqrtf(x*x + y*y + z*z);
	}

	Vector3 Direction(Vector3 other)
	{
		float magnitude = Magnitude();
		Vector3* result = new Vector3(0, 0, 0);
		result->x = (other.x - x) / magnitude;
		result->y = (other.y - y) / magnitude;
		result->z = (other.z - z) / magnitude;
		return *result;
	}

	Vector3 Normalize()
	{
		float magnitude = Magnitude();
		return Vector3(x / magnitude, y / magnitude, z / magnitude);
	}

	static Vector3 Transform(Vector3 position, glm::mat4 matrix)
	{
		float* mtxPtr = glm::value_ptr(matrix);

		return Vector3(
			(position.x * *(mtxPtr + 0)) + (position.y * *(mtxPtr + 4)) + (position.z * *(mtxPtr + 8))  + *(mtxPtr + 12),
			(position.x * *(mtxPtr + 1)) + (position.y * *(mtxPtr + 5)) + (position.z * *(mtxPtr + 9))  + *(mtxPtr + 13),
			(position.x * *(mtxPtr + 2)) + (position.y * *(mtxPtr + 6)) + (position.z * *(mtxPtr + 10)) + *(mtxPtr + 14));
	}

	Vector3 Normalize(float magnitude) {}

	Vector3 operator+(const Vector3& b) {
		Vector3 vector;
		vector.x = this->x + b.x;
		vector.y = this->y + b.y;
		vector.z = this->z + b.z;
		return vector;
	}

	Vector3 operator-(const Vector3& b) {
		Vector3 vector;
		vector.x = this->x - b.x;
		vector.y = this->y - b.y;
		vector.z = this->z - b.z;
		return vector;
	}

	Vector3 operator/(const Vector3& b) {
		Vector3 vector;
		vector.x = this->x / b.x;
		vector.y = this->y / b.y;
		vector.z = this->z / b.z;
		return vector;
	}

	Vector3 operator*(const Vector3& b) {
		Vector3 vector;
		vector.x = this->x * b.x;
		vector.y = this->y * b.y;
		vector.z = this->z * b.z;
		return vector;
	}

	static const Vector3 Zero;
	static const Vector3 One;
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 Up;
	static const Vector3 Down;
	static const Vector3 Right;
	static const Vector3 Left;
	static const Vector3 Forward;
	static const Vector3 Backward;
};