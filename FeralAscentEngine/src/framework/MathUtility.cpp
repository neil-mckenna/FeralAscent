#include "framework/MathUtility.h"

namespace fa
{
	const float PI = 3.1415926535;

	Vector2f RotationToVector(float rotation)
	{
		float radians = DegreesToRadians(rotation);
		return Vector2f(cos(radians), sin(radians));
	}

	float DegreesToRadians(float degrees)
	{
		return degrees * (PI / 180.f);
	}

	float RadiansToDegrees(float radians)
	{
		return radians * (180.f / PI);
	}
}