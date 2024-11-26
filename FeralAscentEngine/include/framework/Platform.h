#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>
#include "framework/Actor.h"
#include "framework/World.h"
#include <Box2D/Box2D.h>
#include <iostream>

using namespace std;

namespace fa {

    class Platform : public Actor {
    public:
        Platform(World* world, const sf::Vector2f& position, const sf::Vector2f& size, const string texturePath);
        void Render(sf::RenderWindow& window);

    private:
        b2Body* m_Body;             ///< Box2D body
        sf::RectangleShape m_Rect;  ///< SFML rectangle for visual representation
    };

} // namespace fa

#endif // PLATFORM_H
