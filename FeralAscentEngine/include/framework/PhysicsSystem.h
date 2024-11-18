#pragma once
#include "framework/Core.h"
#include "framework/Actor.h"
#include <box2d/b2_world.h>

namespace fa
{
	class Actor;
	class PhysicsContactListener : public b2ContactListener
	{
		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override;

	};

	class PhysicsSystem
	{
	public:
		static PhysicsSystem& Get();
		void Step(float dt);

		b2Body* AddListener(Actor* listener);
		void RemoveListener(b2Body* bodyToRemove);

		float GetPhysicsScale() const { return m_PhysicsScale; }

		static void Cleanup();

	protected:
		PhysicsSystem();

	private:
		static unique<PhysicsSystem> physicsSystem;
		b2World m_PhysicsWorld;
		float m_PhysicsScale;
		int m_VelocityIterations;
		int m_PositionIterations;

		PhysicsContactListener m_ContactListener;

		Set<b2Body*> m_PendingRemovalListeners;

		void ProcessPendingRemovalListeners();
	};


}