#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include <sstream>
#include <string>

#include <box2d/b2_body.h>

using namespace std;

namespace fa
{
	Actor::Actor(World* owningWorld, const string& texturePath) :
		m_owningWorld(owningWorld),
		m_hasBeganPlay(false),
		m_Sprite{},
		m_Texture{},
		m_body{nullptr},
		m_dynamic{true},
		m_position{0,0}
		m_PhysicsBody{nullptr},
		m_PhysicsEnabled{false}

	{
		SetTexture(texturePath);

		// Define the Box2D body
		b2BodyDef bodyDef;
		bodyDef.type = m_dynamic ? b2_dynamicBody : b2_staticBody;
		bodyDef.position.Set(m_position.x, m_position.y);

		// Create the body in the Box2D world
		m_body = m_owningWorld->GetB2World().CreateBody(&bodyDef);

		// Define a shape for the body (rectangle for simplicity)
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(m_Sprite.getGlobalBounds().width / 2.0f, m_Sprite.getGlobalBounds().height / 2.0f);

		// Create the fixture (add the shape to the body)
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		m_body->CreateFixture(&fixtureDef);


	}

	void Actor::SetTexture(const string texturePath)
	{
		// call singleton
		m_Texture = AssetManager::Get().LoadTexture(texturePath);

		if (!m_Texture)
		{
			return;
		}

		m_Sprite.setTexture(*m_Texture);

		int textureWidth = m_Texture->getSize().x;
		int textureHeight = m_Texture->getSize().y;

		m_Sprite.setTextureRect(IntRect(Vector2i{ 0,0 }, Vector2i{ textureWidth, textureHeight }));

		// center origin
		CenterPivot();
	}


	void Actor::BeginPlayInternal()
	{
		if (!m_hasBeganPlay)
		{
			m_hasBeganPlay = true;
			BeginPlay();
		}

	}

	void Actor::BeginPlay()
	{
		LOG("Actor	: %s :	Created!", m_ActorName.c_str());

	}

	void Actor::Update(float dt)
	{
		//LOG("Actor updating");

		LogActorDetails();

	}

	void Actor::LogActorDetails()
	{
		stringstream logMessage;

		// Append each variable to the log message
		//logMessage << "Actor Name: " << m_ActorName << "\n";
		//logMessage << "Body: " << m_body << "\n";  // Log the body pointer or position depending on your needs

		logMessage << "Dynamic: " << (m_dynamic ? "true" : "false") << "\n";
		//logMessage << "Position: (" << m_position.x << ", " << m_position.y << ")\n";

		// If m_owningWorld is a pointer, log its validity or more details
		//logMessage << "Owning World: " << (m_owningWorld ? "Valid" : "Null") << "\n";  // Adjust this line as needed

		// Check if the texture is loaded
		//logMessage << "Texture: " << (m_Texture && m_Texture->getSize().x > 0 ? "Loaded" : "Not Loaded") << "\n";

		// Pass the log message to the LOG function
		LOG("", logMessage.str());
	}


	void Actor::UpdateInternal(float dt)
	{
		if (!IsPendingDestroy())
		{
			Update(dt);
		}
	}

	void Actor::Render(RenderWindow& window)
	{
		if (m_dynamic) {
			m_Sprite.setColor(sf::Color::Green); // Green for dynamic
		}
		else {
			m_Sprite.setColor(sf::Color::Red); // Red for static
		}

		window.draw(m_Sprite);
	}

	void Actor::SetActorLocation(const Vector2f& newLocation)
	{
		m_Sprite.setPosition(newLocation);

	}

	void Actor::SetActorRotation(const float newRot)
	{
		m_ActorRotation = newRot;

	}

	Vector2f Actor::GetActorLocation() const
	{
		return m_Sprite.getPosition();
	}

	float Actor::GetActorRotation() const
	{
		return m_ActorRotation;
	}

	void Actor::AddActorLocationOffset(const Vector2f& offsetAmt)
	{
		SetActorLocation(GetActorLocation() + offsetAmt);
	}

	void Actor::AddActorLocationOffset(float rotOffsetAmt)
	{
		SetActorRotation(GetActorRotation() + rotOffsetAmt);
	}

	Vector2f Actor::GetActorForwardDirection() const
	{
		return RotationToVector(GetActorRotation());
	}

	Vector2f Actor::GetActorRightDirection() const
	{
		// from the actor ^ to >
		return RotationToVector(GetActorRotation() + 90);
	}

	void Actor::RescaleActor(float scaleXAmt, float scaleYAmt)
	{
		m_Sprite.setScale(scaleXAmt, scaleYAmt);
	}

	void Actor::FaceLeft()
	{
		m_Sprite.setScale(-1.f, 1.f);
		m_facingLeft = true;
	}

	void Actor::FaceRight()
	{
		m_Sprite.setScale(1.f, 1.f);
		m_facingLeft = false;
	}

	Vector2u Actor::GetWindowSize() const
	{
		return m_owningWorld->GetWindowSize();
	}

	FloatRect Actor::GetActorGlobalBounds() const
	{
		return m_Sprite.getGlobalBounds();
	}

	void Actor::SetSpriteRotation(float newRot) {
		m_Sprite.setRotation(newRot); // Rotate the sprite independently
	}

	float Actor::GetSpriteRotation() const {
		return m_Sprite.getRotation(); // Get the current sprite rotation
	}



	void Actor::CenterPivot()
	{
		FloatRect bounds = m_Sprite.getGlobalBounds();
		m_Sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	}



	bool Actor::IsActorOutOfWindowBounds() const
	{
		float windowWidth = GetWorld()->GetWindowSize().x;
		float windowHeight = GetWorld()->GetWindowSize().y;

		float actorWidth = GetActorGlobalBounds().width;
		float actorHeight = GetActorGlobalBounds().height;

		Vector2f actorPos = GetActorLocation();

		//LOG("Current Actor Pos x=%f y=%f", GetActorLocation().x, GetActorLocation().y);

		// outside the x axises
		if (actorPos.x < -actorWidth || actorPos.x > (windowWidth + actorWidth))
		{
			return true;
		}

		// outside the y axises
		if (actorPos.y < -actorHeight || actorPos.y >(windowHeight + actorHeight))
		{
			return true;
		}

		return false;
	}


	void Actor::Destroy()
	{

		Object::Destroy();
	}

	Actor::~Actor()
	{
		LOG("Ahhhhhh!!!! ------------ Actor %s Destroyed", m_ActorName.c_str());
	}
}

