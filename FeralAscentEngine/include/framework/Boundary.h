#ifndef BOUNDARY_HPP
#define BOUNDARY_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "framework/TextureComponent.h"
#include "framework/Actor.h"

namespace fa {

    // Boundary class to create static boundaries (walls) for the game world
    class Boundary : public Actor {
    public:
        // Constructor to initialize a boundary with texture
        Boundary(World* world, const sf::Vector2f& position, const sf::Vector2f& size, const std::string& texturePath);

        // Render the boundary
        void Render(sf::RenderWindow& window);

        // Update the boundary (e.g., for animations)
        void Update(float deltaTime);

    private:
        b2Body* m_body;                       // Box2D body for the wall
        sf::Vector2f m_Position;              // Position of the boundary
        sf::Vector2f m_Size;                  // Size of the boundary
        TextureComponent m_TextureComponent;  // Texture component for rendering
        // SFML sprite and texture
        sf::Sprite m_Sprite;

        static constexpr float SCALE = 30.0f; // Conversion scale between Box2D and SFML

    public:

        Boundary() = default;
    };

} // namespace fa

#endif // BOUNDARY_HPP
