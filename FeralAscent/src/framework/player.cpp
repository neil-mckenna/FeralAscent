//player.cpp
#include "framework/player.h"

using namespace sf;
using namespace std;

void Player::Update(double dt) {
    //Move in four directions based on keys

    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        // move left
         move(Vector2f(-5.0f * _speed * dt, 0.0f));
    }
    else if (Keyboard::isKeyPressed(Keyboard::D))
    {
        // move right
        move(Vector2f(5.0f * _speed * dt, 0.0f));
    }
    else if (Keyboard::isKeyPressed(Keyboard::W))
    {
        // move up
        move(Vector2f(0.0f ,-5.0f * _speed * dt));
    }
    else if (Keyboard::isKeyPressed(Keyboard::S))
    {
        // move down
        move(Vector2f(0.0f, 5.0f * _speed * dt));
    }

    Entity::Update(dt);
}

Player::Player()
    : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
    _shape->setFillColor(Color::Magenta);
    _shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::Render(sf::RenderWindow& window) const {
    window.draw(*_shape);
}