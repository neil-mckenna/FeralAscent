#pragma once

#include "framework/Actor.h"
#include "framework/World.h"

using namespace std;

namespace fa
{
	class Enemy : public Actor
	{
	public:
		Enemy(World* owningWorld, Vector2f position, const string& texturePath = "");
		virtual void Update(float dt);

		float GetSpeed() const { return m_speed; }
		void SetSpeed(float newSpeed) { m_speed = newSpeed; }

	private:
		void HandleInput(float dt);
		void NormalizeInput();
		void ClampInputOnEdge();

		void ConsumeInput(float dt);
		void BeginPlay();
		Vector2f m_MoveInput;
		float m_speed;
	};

}