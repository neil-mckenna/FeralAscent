#include "framework/PhysicsComponent.h"
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

namespace fa {

    // Constructor initializes the body and the physics environment
    PhysicsComponent::PhysicsComponent(b2World* b2world, const sf::Vector2f& position)
        : m_B2World(b2world)
    {
        // Set up the body for the physics component
        InitializeBody(position);

        // Initialize the debug shape (optional for visualizing the physics body)
        m_DebugShape.setRadius(10.f);  // Size of the shape for debugging
        m_DebugShape.setFillColor(sf::Color::Green);  // Color for the debug shape
    }

    // Destructor cleans up Box2D body
    PhysicsComponent::~PhysicsComponent() {
        if (m_Body) {
            m_B2World->DestroyBody(m_Body);  // Destroy Box2D body to avoid memory leaks
        }
    }

    // Initialize the physics body in Box2D (we assume a dynamic body here)
    void PhysicsComponent::InitializeBody(const sf::Vector2f& position) {
        // Define the body’s properties
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;  // Set the body type to dynamic (affected by physics)
        bodyDef.position.Set(position.x, position.y);  // Set the initial position in the world

        // Create the body in the Box2D world
        m_Body = m_B2World->CreateBody(&bodyDef);

        // Define the shape of the body (e.g., a circle shape)
        b2CircleShape circleShape;
        circleShape.m_radius = 10.0f;  // Set the radius of the circle for the body

        // Define the fixture (physical properties like density and friction)
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circleShape;
        fixtureDef.density = 1.0f;  // Set density (mass-related)
        fixtureDef.friction = 0.3f;  // Friction between the body and other surfaces

        // Attach the fixture to the body (connects shape and physics properties)
        m_Body->CreateFixture(&fixtureDef);
    }

    // Apply velocity to the physics body (to move the actor)
    void PhysicsComponent::ApplyVelocity(const sf::Vector2f& velocity, float dt) {
        // Box2D uses b2Vec2, so convert SFML vector to Box2D vector
        b2Vec2 b2Velocity(velocity.x, velocity.y);
        m_Body->SetLinearVelocity(b2Velocity);  // Set the linear velocity (movement)
    }

    // Update the physics component (called once per frame)
    void PhysicsComponent::Update(float dt) {
        // Box2D's simulation step typically happens in the main game loop
        // You could step the world manually here if needed, but it's often done outside
        // Here, we step the world using Box2D's `Step` function to simulate physics
        m_B2World->Step(dt, 8, 3);  // Step the simulation with a time step, velocity iterations, and position iterations
    }

    // Get the Box2D body for external interaction
    b2Body* PhysicsComponent::GetBody() const {
        return m_Body;
    }

    sf::Vector2f PhysicsComponent::GetPosition() const
    {
        if (m_Body) {
            b2Vec2 pos = m_Body->GetPosition();
            return sf::Vector2f(pos.x, pos.y);
        }
        return sf::Vector2f(0.0f, 0.0f); // Default if body is not initialized
    }

    // For debugging purposes, draw the physics body's shape (useful during development)
    void PhysicsComponent::Render(sf::RenderWindow& window) {
        // Update the debug shape position based on the body’s position in Box2D
        b2Vec2 position = m_Body->GetPosition();
        m_DebugShape.setPosition(position.x - m_DebugShape.getRadius(), position.y - m_DebugShape.getRadius());

        // Draw the debug shape to the window for visualizing the physics body
        window.draw(m_DebugShape);
    }

    // Handle movement: Apply velocity to the physics body based on direction and speed
    void PhysicsComponent::HandleMovement(const sf::Vector2f& direction, float dt) {
        // Apply velocity to the physics body based on direction and speed
        float speed = 55.0f; // Speed of movement in meters per second
        b2Vec2 velocity(direction.x * speed, direction.y * speed);
        m_Body->SetLinearVelocity(velocity);  // Set the linear velocity of the body
    }



}  // namespace fa

