#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

namespace fa {

    class Platform {
    public:
        Platform(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size);
        void Render(sf::RenderWindow& window);

    private:
        b2Body* m_Body;             ///< Box2D body
        sf::RectangleShape m_Rect;  ///< SFML rectangle for visual representation
    };

} // namespace fa

#endif // PLATFORM_H
