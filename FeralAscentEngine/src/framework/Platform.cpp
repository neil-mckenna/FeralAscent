#include "framework/Platform.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "framework/Utilities.h"

namespace fa {

    Platform::Platform(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size) {
        // Initialize Box2D body
        b2BodyDef bodyDef;
        bodyDef.position.Set(PixelsToMeters(position.x), PixelsToMeters(position.y));
        bodyDef.type = b2_staticBody;
        m_Body = world.CreateBody(&bodyDef);

        b2PolygonShape boxShape;
        boxShape.SetAsBox(PixelsToMeters(size.x / 2.0f), PixelsToMeters(size.y / 2.0f)); // Half-size for Box2D

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &boxShape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        m_Body->CreateFixture(&fixtureDef);

        // Initialize SFML rectangle shape
        m_Rect.setSize(size);
        m_Rect.setOrigin(size.x / 2.0f, size.y / 2.0f);
        m_Rect.setPosition(position);
        m_Rect.setFillColor(sf::Color::Red); // Example color
    }


    void Platform::Render(sf::RenderWindow& window) {
        // Update the SFML rectangle's position based on the Box2D body's position
        b2Vec2 bodyPosition = m_Body->GetPosition();
        m_Rect.setPosition(bodyPosition.x * 30.0f, bodyPosition.y * 30.0f); // Convert back to pixels

        // Draw the rectangle on the window
        window.draw(m_Rect);
    }

}
