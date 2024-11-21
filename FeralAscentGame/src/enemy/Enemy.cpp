#include "enemy/Enemy.h"
#include "framework/PhysicsSystem.h"

namespace fa
{
	Enemy::Enemy(World* owningWorld, const string& texturePath) :
		Actor{ owningWorld, texturePath },
		m_speed{ 100.0f },
		m_MoveInput{ 0.0f, 0.0f },
		// Defines the direction an enemy is travelling, which changes randomly in small increments
		randomDirection{ 0.f, 0.f }
	{
		m_ActorName = "Enemy One";
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);
		HandleInput(dt); // Process input to update movement
		MoveRandom(dt); // Move in a random direction
		ClampInputOnEdge();
		NormalizeInput(); // Optional: Normalize movement direction
		AddActorLocationOffset(m_MoveInput * m_speed * dt); // Apply movement
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
		Vector2f actorLocation = GetActorLocation();
		float actorWidth = GetActorGlobalBounds().width / 2;
		float actorHeight = GetActorGlobalBounds().height / 2;

		if (actorLocation.x - actorWidth <= 0.f && m_MoveInput.x < 0.f
			|| actorLocation.x + actorWidth >= GetWindowSize().x && m_MoveInput.x > 0.f) {
			m_MoveInput.x = 0;
		}

		if (actorLocation.y - actorHeight <= 0.f && m_MoveInput.y < 0.f
			|| actorLocation.y + actorHeight >= GetWindowSize().y && m_MoveInput.y > 0.f) {
			m_MoveInput.y = 0;
		}
	}

	void Enemy::ConsumeInput(float dt)
	{
	}

	void Enemy::BeginPlay()
	{
		Actor::BeginPlay();

		SetEnablePhysics(true);
	}

	void Enemy::MoveRandom(float dt)
	{
		// Randomize movement
		// 
		// Get random minor change in x/y coordinates and move in that direction
		// Direction changes by small amounts each run

		// Get a number between -50 and 50, then scale down (a lot!)
		float cx = ((rand() % 100) - 50) / 1000000.f;
		randomDirection.x += cx;
		// Cap each direction between -1 and 1
		randomDirection.x = max(min(randomDirection.x, 1.0f), -1.0f);

		// Same with y
		float cy = ((rand() % 100) - 50) / 1000000.f;
		randomDirection.y += cy;
		randomDirection.y = max(min(randomDirection.y, 1.0f), -1.0f);


		// If touches edge of screen, reverse direction (and slow down a little)
		// Copy this code for other collisions
		Vector2f loc = GetActorLocation();
		float awidth = GetActorGlobalBounds().width / 2;
		float aheight = GetActorGlobalBounds().height / 2;

		if (loc.x - awidth < 0 && randomDirection.x < 0.f
			|| loc.x + awidth > GetWindowSize().x && randomDirection.x > 0.f)
		{
			randomDirection.x *= -0.2f;
		}

		if (loc.y - aheight < 0 && randomDirection.y < 0.f
			|| loc.y + aheight > GetWindowSize().y && randomDirection.y > 0.f)
		{
			randomDirection.y *= -0.2f;
		}



		m_MoveInput.x += randomDirection.x;
		m_MoveInput.y += randomDirection.y;
	}
}