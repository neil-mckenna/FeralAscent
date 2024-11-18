#include "player/Player.h"
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include <cmath>

using namespace sf;
using namespace std;

namespace fa
{
	Player::Player(World* owningWorld, const string& texturePath) :
		Actor{owningWorld, texturePath},
		m_speed{5.0f},
		m_MoveInput{0.0f, 0.0f}

	{
		LOG("Texture Path : %s", texturePath.c_str());

		m_ActorName = "Player One";
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);
		HandleInput(dt); // Process input to update movement
		NormalizeInput(); // Optional: Normalize movement direction
		AddActorLocationOffset(m_MoveInput * m_speed * dt); // Apply movement
		m_MoveInput = Vector2f{ 0.0f, 0.0f }; // Reset input after applying
	}

	void Player::HandleInput(float dt)
	{
		// Accumulate movement based on key presses
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			m_MoveInput.x -= 1.0f; // Move left
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			m_MoveInput.x += 1.0f; // Move right
		}
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			m_MoveInput.y -= 1.0f; // Move up
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			m_MoveInput.y += 1.0f; // Move down
		}
	}

	void Player::NormalizeInput()
	{
		// Normalize movement to prevent faster diagonal movement
		float magnitude = std::sqrt(m_MoveInput.x * m_MoveInput.x + m_MoveInput.y * m_MoveInput.y);
		if (magnitude > 0.0f)
		{
			m_MoveInput /= magnitude;
		}
	}

	void Player::ClampInputOnEdge()
	{

	}

	void Player::ConsumeInput(float dt)
	{

	}

	void Player::BeginPlay()
	{
		Actor::BeginPlay();

		SetEnablePhysics(true);
	}
}