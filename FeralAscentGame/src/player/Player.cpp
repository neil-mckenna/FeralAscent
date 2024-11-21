#include "player/Player.h"
#include "framework/PhysicsSystem.h"
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include <cmath>

using namespace sf;
using namespace std;

namespace fa
{
	Player::Player(World* owningWorld, const string& texturePath) :
		Actor{owningWorld, texturePath},
		m_speed{200.0f},
		m_MoveInput{0.0f, 0.0f}
	{
		//LOG("Texture Path : %s", texturePath.c_str());

		m_ActorName = "Player One";
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);
		HandleInput(dt); // Process input to update movement
		ClampInputOnEdge();
		NormalizeInput(); // Optional: Normalize movement direction
		AddActorLocationOffset(m_MoveInput * m_speed * dt); // Apply movement

		if (m_PhysicsBody)
		{
			b2Vec2 velocity = m_PhysicsBody->GetLinearVelocity();
			velocity.x = m_MoveInput.x * m_speed; // Apply horizontal input velocity
			velocity.y = m_MoveInput.y * m_speed; // Apply vertical input velocity

			m_PhysicsBody->SetLinearVelocity(velocity); // Set new velocity
		}

		m_MoveInput = Vector2f{ 0.0f, 0.0f }; // Reset input after applying

		// apply graviyt?

		PhysicsSystem::Get().Step(dt);
	}

	void Player::HandleInput(float dt)
	{
		// Accumulate movement based on key presses
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			// Edit sprite to face left
			FaceLeft();
			m_MoveInput.x -= m_speed * dt; // Move left
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			// Edit sprite to face right
			FaceRight();
			m_MoveInput.x += m_speed * dt; // Move right
		}

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			m_MoveInput.y -= m_speed * dt; // Move up
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			m_MoveInput.y += m_speed * dt; // Move down
		}

		//LOG("MOve Vector: x=%f y=%f", m_MoveInput.x, m_MoveInput.y);
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
		LOG(
			"PlayerX: %f PlayerY %f : Window Size player_width=%f player_height=%f width=%u height=%u",
			GetActorLocation().x,
			GetActorLocation().y,
			GetActorGlobalBounds().width,
			GetActorGlobalBounds().height,
			GetWindowSize().x,
			GetWindowSize().y
		);

		Vector2f actorLocation = GetActorLocation();
		float actorWidth = GetActorGlobalBounds().width / 2;
		float actorHeight = GetActorGlobalBounds().height / 2;

		// left side
		if (actorLocation.x < 0 + (actorWidth) && m_MoveInput.x < 0.f
			|| actorLocation.x > GetWindowSize().x - (actorWidth) && m_MoveInput.x > 0.f)
		{
			m_MoveInput.x = 0.f;
		}

		// top
		if (actorLocation.y < 0 + (actorHeight) && m_MoveInput.y < 0.f
			|| actorLocation.y > GetWindowSize().y - (actorHeight) && m_MoveInput.y > 0.f)
		{
			m_MoveInput.y = 0.f;
		}
	}

	void Player::ConsumeInput(float dt)
	{

		SetSpeed(m_speed);
		m_MoveInput.x = 0.f;
		m_MoveInput.y = 0.f;
	}

	void Player::BeginPlay()
	{
		Actor::BeginPlay();

		SetEnablePhysics(true);
	}
}