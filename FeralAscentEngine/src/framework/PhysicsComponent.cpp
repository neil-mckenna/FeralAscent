#include "framework/PhysicsComponent.h"
#include "framework/World.h"  // Assuming you have a world that holds the Box2D world

namespace fa {

    // Constructor: Initialize the Box2D body using the body definition passed in
    PhysicsComponent::PhysicsComponent(b2BodyDef bodyDef) {
        // Assuming you have access to the world to retrieve the Box2D world instance
        m_World = nullptr;  // Set this to your actual Box2D world if needed

        // Create the Box2D body using the world and body definition
        if (m_World) {
            m_Body = m_World->CreateBody(&bodyDef);
        }
        else {
            m_Body = nullptr; // Handle case where the world is not initialized
        }
    }

    // Destructor: Remove the Box2D body from the world if it exists
    PhysicsComponent::~PhysicsComponent() {
        if (m_World && m_Body) {
            m_World->DestroyBody(m_Body);
        }
    }

    // Update method: You can apply physics updates here if needed
    void PhysicsComponent::Update(float dt) {
        // This is where you might apply physics-related changes each frame (e.g., velocity or forces)
        // For now, it's left empty, but could be extended for custom physics behavior.
    }

    // Accessor for the Box2D body
    b2Body* PhysicsComponent::GetBody() const {
        return m_Body;
    }

    // Set the position of the Box2D body
    void PhysicsComponent::SetPosition(const b2Vec2& position) {
        if (m_Body) {
            m_Body->SetTransform(position, m_Body->GetAngle());
        }
    }

    // Apply force to the body
    void PhysicsComponent::ApplyForce(const b2Vec2& force) {
        if (m_Body) {
            m_Body->ApplyForceToCenter(force, true);
        }
    }

    // Set the Box2D body to a new definition (e.g., after changing velocity)
    void PhysicsComponent::SetBodyDefinition(b2BodyDef newDef) {
        if (m_Body) {
            m_World->DestroyBody(m_Body);
            m_Body = m_World->CreateBody(&newDef);
        }
    }

}
