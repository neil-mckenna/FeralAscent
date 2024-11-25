#include "framework/Boundary.h"

namespace fa {

    // Constructor implementation
    Boundary::Boundary(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size)
        : position(position), size(size) { // Initialize position and size
        b2BodyDef bodyDef;
        bodyDef.position.Set(position.x / SCALE, position.y / SCALE); // Convert position to Box2D scale
        bodyDef.type = b2_staticBody;  // Static body for walls
        body = world.CreateBody(&bodyDef);

        b2PolygonShape boxShape;
        boxShape.SetAsBox((size.x / 2.0f) / SCALE, (size.y / 2.0f) / SCALE);  // Convert size to Box2D scale

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &boxShape;
        fixtureDef.friction = 0.5f; // Adjust friction as necessary
        body->CreateFixture(&fixtureDef);
    }

    // Render implementation
    void Boundary::render(sf::RenderWindow& window) {
        sf::RectangleShape boundaryShape(size);  // Use size directly
        boundaryShape.setFillColor(sf::Color::Transparent);  // Transparent fill
        boundaryShape.setOutlineThickness(2);
        boundaryShape.setOutlineColor(sf::Color::Red);       // Red outline for debugging
        boundaryShape.setPosition(position);                // Use position
        window.draw(boundaryShape);
    }

} // namespace Platty
