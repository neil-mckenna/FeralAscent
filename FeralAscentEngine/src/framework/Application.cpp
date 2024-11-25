#include "framework/Application.h"
#include <SFML/Graphics.hpp>
#include <Box2d/box2d.h>
#include <iostream>

namespace fa {

    // Default constructor initializing members with default values
    Application::Application()
        : m_Window(sf::VideoMode(800, 600), "Default Title", sf::Style::Default),  // Default window size and title
        m_TargetFrameRate(60.0f),  // Default target frame rate
        m_CleanCycleInterval(1.0f),  // Default clean cycle interval
        m_currentWorld(nullptr)  // Initially no world loaded
    {
        std::cout << "Application created with default constructor." << std::endl;
    }

    // Parameterized constructor that initializes the window with given parameters
    Application::Application(unsigned int windowWidth, unsigned int windowHeight,
        const std::string& title, sf::Uint32 style)
        : m_Window(sf::VideoMode(windowWidth, windowHeight), title, style),
        m_TargetFrameRate(60.0f),  // Default target frame rate
        m_CleanCycleInterval(1.0f),  // Default clean cycle interval
        m_currentWorld(nullptr)  // Initially no world loaded
    {
        std::cout << "Application created with custom window size and title." << std::endl;
    }

    // Method to run the application
    void Application::Run()
    {
        sf::Clock clock;

        // Game loop
        while (m_Window.isOpen()) {
            sf::Time deltaTime = clock.restart();
            Update(deltaTime.asSeconds());
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
        std::cout << "Updating with deltaTime: " << dt << std::endl;
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
        std::cout << "Application destroyed." << std::endl;
    }

} // namespace fa
