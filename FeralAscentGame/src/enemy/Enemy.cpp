#include "enemy/Enemy.h"
#include "framework/PhysicsSystem.h"

namespace fa
{
	Enemy::Enemy(World* owningWorld, const string& texturePath) :
		Actor{ owningWorld, texturePath },
		m_speed{ 125.0f },
		m_MoveInput{ 0.0f, 0.0f }
	{
		m_ActorName = "Enemy One";
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);
		HandleInput(dt); // Process input to update movement
		NormalizeInput(); // Optional: Normalize movement direction
		AddActorLocationOffset(m_MoveInput * m_speed * dt * 100.0f); // Apply movement
		m_MoveInput = Vector2f{ 0.0f, 0.0f }; // Reset input after applying



	}

	void Enemy::HandleInput(float dt)
	{
	}

	void Enemy::NormalizeInput()
	{
		// Normalize movement to prevent faster diagonal movement
		float magnitude = std::sqrt(m_MoveInput.x * m_MoveInput.x + m_MoveInput.y * m_MoveInput.y);
		if (magnitude > 0.0f)
		{
			m_MoveInput /= magnitude;
		}
	}

	void Enemy::ClampInputOnEdge()
	{
	}

	void Enemy::ConsumeInput(float dt)
	{
	}

	void Enemy::BeginPlay()
	{
		Actor::BeginPlay();

		SetEnablePhysics(true);
	}
}