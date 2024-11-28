// framework/Component.cpp
#include "framework/Component.h"

// The base Component class doesn't have any specific implementation
namespace fa {

    // Abstract class, no need for implementation here
    void Component::Update(float dt) {
        // This is an abstract method, to be overridden by derived classes
    }

    void Component::Render(sf::RenderWindow& window) {
        // This is an abstract method, to be overridden by derived classes
    }

}
