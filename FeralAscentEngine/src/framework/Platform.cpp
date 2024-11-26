#include "framework/Platform.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "framework/Utilities.h"

namespace fa {

    /**
     * @brief Constructs a Platform object in the Box2D world and initializes its SFML graphical representation.
     *
     * This constructor creates a static Box2D body representing a platform in the game world,
     * along with a corresponding SFML rectangle shape that visually represents the platform in the game window.
     * The platform is defined by its position and size, which are provided as arguments.
     *
     * @param world The Box2D world where the platform will be created.
     * @param position The position of the platform in the game world (in pixels).
     * @param size The size of the platform (in pixels), where the width and height are divided by 2 to account for Box2D's center origin.
     */
    Platform::Platform(World* world, const sf::Vector2f& position, const sf::Vector2f& size, const string texturePath = "assets/PNG/terrain/land_sprites/tile000.png") :
        Actor(world, position, texturePath),
        m_Body{nullptr}
    {
        if (world == nullptr)
        {
            LOG_ERROR("World is NULL in Platform constructor.");
            return;
        }

        // Access Box2D world directly
        b2World& b2w = world->GetB2World();

        // Initialize Box2D body
        b2BodyDef bodyDef;
        bodyDef.position.Set(PixelsToMeters(position.x), PixelsToMeters(position.y));
        bodyDef.type = b2_staticBody;
        m_Body = b2w.CreateBody(&bodyDef);

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
