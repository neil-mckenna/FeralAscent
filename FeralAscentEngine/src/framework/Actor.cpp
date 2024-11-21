#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"
#include <box2d/b2_body.h>

namespace fa
{
	Actor::Actor(World* owningWorld, const string& texturePath) :
		m_owningWorld(owningWorld),
		m_hasBeganPlay(false),
		m_Sprite{},
		m_Texture{},
		m_PhysicsBody{nullptr},
		m_PhysicsEnabled{false}
	{
		SetTexture(texturePath);

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

		PhysicsSystem::Get().Step(dt);

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
		window.draw(m_Sprite);
	}

	void Actor::SetActorLocation(const Vector2f& newLocation)
	{
		m_Sprite.setPosition(newLocation);
		UpdatePhysicsBodyTransform();
	}

	void Actor::SetActorRotation(const float newRot)
	{
		m_ActorRotation = newRot;
		UpdatePhysicsBodyTransform();
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

	bool Actor::SetEnablePhysics(bool enable)
	{
		m_PhysicsEnabled = enable;
		if (m_PhysicsEnabled)
		{
			InitializePhysics();
		}
		else
		{
			UninitializePhysics();
		}

		return false;
	}



	void Actor::InitializePhysics()
	{


		if (!m_PhysicsBody)
		{
			m_PhysicsBody = PhysicsSystem::Get().AddListener(this);

			if (m_PhysicsBody)
			{
				LOG("Physics initialized for actor: %p", m_PhysicsBody);
			}
			else
			{
				LOG("Failed to initialize physics for actor.");
			}
		}
		else
		{
			LOG("Physics already initialized for actor: %p", m_PhysicsBody);
		}
	}

	void Actor::UninitializePhysics()
	{
		if (m_PhysicsBody)
		{
			PhysicsSystem::Get().RemoveListener(m_PhysicsBody);
			m_PhysicsBody = nullptr;
		}
	}

	void Actor::UpdatePhysicsBodyTransform()
	{
		if (m_PhysicsBody)
		{
			float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
			b2Vec2 pos{
				GetActorLocation().x * physicsScale,
				GetActorLocation().y * physicsScale
			};

			float rotation = DegreesToRadians(GetActorRotation());

			m_PhysicsBody->SetTransform(pos, rotation);

		}
	}

	void Actor::OnActorBeginOverlap(Actor* other)
	{
		LOG("Overlapped");
	}

	void Actor::OnActorEndOverlap(Actor* other)
	{
		LOG("Overlap Ended");

	}

	void Actor::Destroy()
	{
		UninitializePhysics();
		Object::Destroy();
	}

	Actor::~Actor()
	{
		LOG("Ahhhhhh!!!! ------------ Actor %s Destroyed", m_ActorName.c_str());
	}
}

