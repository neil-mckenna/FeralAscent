#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "box2d/box2d.h"

using namespace std;
using namespace sf;

namespace fa
{
	class UniPhysics
	{
	public:
		b2World* m_world;

		explicit UniPhysics(b2World& world, float physicsScale);

		// Create physics box using position and size as Vector2f
		b2Body* CreatePhysicsBox(b2World& world, const bool dynamic, const Vector2f& position, const Vector2f& size);

		// Create physics box using SFML RectangleShape
		b2Body* CreatePhysicsBox(b2World& world, const bool dynamic, const RectangleShape& rs);

		Vector2f BV2_TO_SV2(const b2Vec2& in);

		b2Vec2 SV2_TO_BV2(const Vector2f& in);

		Vector2f Invert_Height(const Vector2f& in);

		void Step(float dt);

		~UniPhysics();

	protected:

	private:
		const float physicsScale = 30.0f;
		float gameHeight;
		float physics_scale_inv;


	};
}
