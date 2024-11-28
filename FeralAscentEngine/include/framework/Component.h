
#include <SFML/Graphics.hpp>
#pragma once

using namespace sf;

namespace fa {
    class Component {
    public:
        virtual ~Component() = default;
        virtual void Update(float dt) = 0;
        virtual void Render(RenderWindow& window) = 0;
    };
}
