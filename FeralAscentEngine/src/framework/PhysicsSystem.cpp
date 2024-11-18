#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_contact.h>


using namespace std;

namespace fa
{
	unique<PhysicsSystem> PhysicsSystem::physicsSystem{ nullptr };

	PhysicsSystem& PhysicsSystem::Get()
	{
		if (!physicsSystem)
		{
			physicsSystem = move(unique<PhysicsSystem>{new PhysicsSystem});
		}

		return *physicsSystem;
	}

	void PhysicsSystem::Cleanup()
	{
		physicsSystem = move(unique<PhysicsSystem>{new PhysicsSystem});
	}

	// constructor no gravity with cm scale
	PhysicsSystem::PhysicsSystem() :
		m_PhysicsWorld{ b2Vec2{0.f, 0.f} },
		m_PhysicsScale{ 0.01f },
		m_VelocityIterations{ 8 },
		m_PositionIterations{ 3 },
		m_ContactListener{},
		m_PendingRemovalListeners{}
	{
		m_PhysicsWorld.SetContactListener(&m_ContactListener);
		m_PhysicsWorld.SetAllowSleeping(false);
	}

	void PhysicsSystem::ProcessPendingRemovalListeners()
	{
		for (auto listener : m_PendingRemovalListeners)
		{
			m_PhysicsWorld.DestroyBody(listener);
		}

		m_PendingRemovalListeners.clear();
	}

	void PhysicsSystem::Step(float dt)
	{
		ProcessPendingRemovalListeners();

		m_PhysicsWorld.Step(
			dt,
			m_VelocityIterations,
			m_PositionIterations
		);

	}

	b2Body* PhysicsSystem::AddListener(Actor* listener)
	{
		if (listener->IsPendingDestroy())
		{
			return nullptr;
		}

		b2BodyDef bodyDef{};
		bodyDef.type = b2_dynamicBody;

		bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);
		bodyDef.position.Set(
			listener->GetActorLocation().x * GetPhysicsScale(),
			listener->GetActorLocation().y * GetPhysicsScale()
			);

		bodyDef.angle = DegreesToRadians(listener->GetActorRotation());

		b2Body* body = m_PhysicsWorld.CreateBody(&bodyDef);

		b2PolygonShape shape;
		auto bounds = listener->GetActorGlobalBounds();

		shape.SetAsBox(
			(bounds.width / 2.f) * GetPhysicsScale(),
			(bounds.width / 2.f) * GetPhysicsScale()
		);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.isSensor = true;

		body->CreateFixture(&fixtureDef);

		return body;
	}

	void PhysicsSystem::RemoveListener(b2Body* bodyToRemove)
	{
		m_PendingRemovalListeners.insert(bodyToRemove);
	}


	void PhysicsContactListener::BeginContact(b2Contact* contact)
	{
		LOG("Contact");
		Actor* ActorA =
			reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		Actor* ActorB =
			reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

		if (ActorA && !ActorA->IsPendingDestroy())
		{
			ActorA->OnActorBeginOverlap(ActorB);
		}

		if (ActorB && !ActorB->IsPendingDestroy())
		{
			ActorB->OnActorBeginOverlap(ActorA);
		}

	}

	void PhysicsContactListener::EndContact(b2Contact* contact)
	{
		LOG("End Contact");
		Actor* ActorA = nullptr;
		Actor* ActorB = nullptr;

		if (contact->GetFixtureA() && contact->GetFixtureB()->GetBody())
		{
			ActorA =
				reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		}

		if (contact->GetFixtureB() && contact->GetFixtureA()->GetBody())
		{
			ActorB =
				reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
		}

		if (ActorA && !ActorA->IsPendingDestroy())
		{
			ActorA->OnActorEndOverlap(ActorB);
		}

		if (ActorB && !ActorB->IsPendingDestroy())
		{
			ActorB->OnActorEndOverlap(ActorA);
		}


	}

}