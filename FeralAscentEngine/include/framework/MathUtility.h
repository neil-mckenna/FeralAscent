#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

namespace fa
{
	Vector2f RotationToVector(float rotation);
	float DegreesToRadians(float degrees);
	float RadiansToDegrees(float radians);

	template<typename T>
	float GetVectorLength(const Vector2<T>& vector)
	{
		return sqrt(vector.x * vector.x + vector.y * vector.y);
	}

	template<typename T>
	Vector2<T>& ScaleVector(Vector2<T>& vectorToScale, float amt)
	{
		vectorToScale.x *= amt;
		vectorToScale.y *= amt;
		return vectorToScale;
	}

	template<typename T>
	Vector2<T>& Normalize(Vector2<T>& vector)
	{
		float vectorLength = GetVectorLength<T>(vector);
		if (vectorLength == 0.0f) { return Vector2<T>{}; }

		ScaleVector(vector, 1.0 / vectorLength);

		return vector;
	}
}