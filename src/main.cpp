#include <SFML/Graphics.hpp>
#include "../lib/box2d/include/box2d/b2_world.h"



b2World* world;

int main() {
    // Create a render window with specified size and title
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");

    // Create a circle shape with a radius of 100 pixels
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green); // Set the color to green

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close the window when the close event is received
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the window
        window.clear();
        // Draw the circle shape
        window.draw(shape);
        // Display the content of the window
        window.display();
    }

    return 0;
}
