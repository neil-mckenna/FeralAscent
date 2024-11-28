#include "framework/Application.h"
#include "framework/Core.h"
#include <SFML/Graphics.hpp>
#include <Box2d/box2d.h>
#include <iostream>

namespace fa {


    // Parameterized constructor that initializes the window with given parameters
    Application::Application(unsigned int windowWidth, unsigned int windowHeight,
        const std::string& title, sf::Uint32 style)
        : m_Window(sf::VideoMode(windowWidth, windowHeight), title, style),
        m_TargetFrameRate(60.0f),  // Default target frame rate
        m_CleanCycleInterval(1.0f),  // Default clean cycle interval
        m_currentWorld(nullptr)  // Initially no world loaded
    {
        LOG("Application created with custom window size and title.");

        // Check if window is open and log its size
        if (!m_Window.isOpen()) {
            LOG("Failed to create window.");
        }
        else {
            LOG("Window created successfully: %u x %u", m_Window.getSize().x, m_Window.getSize().y);
        }

    }

    // running applicqtion
    void Application::Run()
    {
        LOG("Application Running!");
        sf::Clock clock;



        LOG("Window Size: %u x %u", m_Window.getSize().x, m_Window.getSize().y);

        while (m_Window.isOpen()) {
            sf::Time deltaTime = clock.restart();

            // Event handling
            sf::Event event;
            while (m_Window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    LOG("Window closed event received.");
                    m_Window.close();  // Close window on close event
                }
            }

            LOG("Updating game state with deltaTime: %f", deltaTime.asSeconds());
            Update(deltaTime.asSeconds());

            LOG("Rendering...");
            Render();
        }
    }


    sf::Vector2u Application::GetWindowSize() const
    {
        return m_Window.getSize();
    }

    // Update function, typically used to update the game's state
    void Application::Update(float dt)
    {
        // Update internal game logic and world
        UpdateInternal(dt);
    }

    // Internal update method (this method can be called from other game logic)
    void Application::UpdateInternal(float dt)
    {
        // Logic for updating the application per frame (e.g., physics updates)
        LOG("Updating with deltaTime: %f", dt);
    }

    // Render method, draws everything to the window
    void Application::Render()
    {
        RenderInternal();  // Calls internal render method, which can be overridden
    }

    // Internal render method
    void Application::RenderInternal()
    {
        m_Window.clear();  // Clear the window
        // You would usually call render for different game objects or world here
        m_Window.display();  // Display the window contents
    }

    // Destructor
    Application::~Application()
    {

        LOG("Application destroyed.");
    }

} // namespace fa
