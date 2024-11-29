#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "framework/Component.h"
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

namespace fa {

    class PhysicsComponent : public Component {
    public:
        // Constructor initializes the body and physics environment
        PhysicsComponent(b2World* b2world, const sf::Vector2f& position);

        // Destructor cleans up Box2D body
        ~PhysicsComponent();

        // Update the physics component (called once per frame)
        void Update(float dt);

        // Apply velocity to the physics body
        void ApplyVelocity(const sf::Vector2f& velocity, float dt);

        // Get the Box2D body for external interaction
        b2Body* GetBody() const;

        sf::Vector2f GetPosition() const;

        // Render the physics body for debugging purposes
        void Render(sf::RenderWindow& window);

        // Handle movement: Apply velocity to the physics body based on direction and speed
        void HandleMovement(const sf::Vector2f& direction, float dt);

    private:
        // Initialize the physics body in Box2D
        void InitializeBody(const sf::Vector2f& position);

        b2World* m_B2World;  // Box2D world instance
        b2Body* m_Body;      // Box2D body for the actor
        sf::CircleShape m_DebugShape;  // Shape used for debugging purposes (visualize physics body)
    };

}  // namespace fa

#endif  // PHYSICSCOMPONENT_H
