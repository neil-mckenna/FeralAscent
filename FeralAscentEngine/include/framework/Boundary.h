#ifndef BOUNDARY_HPP
#define BOUNDARY_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

namespace fa {

    // Boundary class to create static boundaries (walls) for the game world
    class Boundary {
    public:
        // Constructor to initialize a boundary wall
        Boundary(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size);

        // Render the boundary wall
        void render(sf::RenderWindow& window);

    private:
        b2Body* body;                  // Box2D body for the wall
        sf::RectangleShape shape;     // SFML shape for rendering the wall
        sf::Vector2f position;        // Position of the boundary
        sf::Vector2f size;            // Size of the boundary (added this member)

        const sf::Vector2u screenSize = sf::Vector2u(1024, 768); // Adjust this value based on your needs
        static constexpr float SCALE = 30.0f; // Conversion scale between Box2D and SFML
    };

} // namespace Platty

#endif // BOUNDARY_HPP
