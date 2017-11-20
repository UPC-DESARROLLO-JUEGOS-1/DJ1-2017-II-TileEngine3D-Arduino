#pragma once

#include <math.h>

class Vector2
{
public:
	Vector2() {
		this->x = 0;
		this->y = 0;
	}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	~Vector2() {}

	float x, y;
	float Magnitude()
	{
		return sqrtf(x*x + y*y);
	}

	Vector2 Direction(Vector2 other)
	{
		float magnitude = Magnitude();
		Vector2* result = new Vector2(0, 0);
		result->x = (other.x - x) / magnitude;
		result->y = (other.y - y) / magnitude;
		return *result;
	}

	Vector2 Normalize()
	{
		float magnitude = Magnitude();
		return Vector2(x / magnitude, y / magnitude);
	}

	Vector2 Normalize(float magnitude) {}

	Vector2 operator+(const Vector2& b) {
		Vector2 vector;
		vector.x = this->x + b.x;
		vector.y = this->y + b.y;
		return vector;
	}

	Vector2 operator-(const Vector2& b) {
		Vector2 vector;
		vector.x = this->x - b.x;
		vector.y = this->y - b.y;
		return vector;
	}

	Vector2 operator/(const Vector2& b) {
		Vector2 vector;
		vector.x = this->x / b.x;
		vector.y = this->y / b.y;
		return vector;
	}

	Vector2 operator*(const Vector2& b) {
		Vector2 vector;
		vector.x = this->x * b.x;
		vector.y = this->y * b.y;
		return vector;
	}

	Vector2 operator*(const float& val) {
		Vector2 vector;
		vector.x = this->x * val;
		vector.y = this->y * val;
		return vector;
	}

	static const Vector2 Zero;
	static const Vector2 One;
	static const Vector2 UnitX;
	static const Vector2 UnitY;
};