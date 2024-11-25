#pragma once
#include <SFML/Graphics.hpp>
#include <Box2d/box2d.h>
#include "framework/Core.h"
#include <memory>

namespace fa
{
    class World;

    class Application
    {
    public:
        // Default constructor initializing members with default values
        Application();

        // Parameterized constructor that initializes the window with given parameters
        Application(unsigned int windowWidth, unsigned int windowHeight,
            const std::string& title, sf::Uint32 style);

        // Function to run the application
        virtual void Run();

        // Template function to load different types of worlds
        template<typename WorldType>
        std::weak_ptr<WorldType> LoadWorld();

        // Get the window size
        sf::Vector2u GetWindowSize() const;

        virtual ~Application();

    protected:
        virtual void Update(float dt);
        sf::RenderWindow m_Window;

    private:
        float m_TargetFrameRate;  // Target frame rate
        sf::Clock m_TickClock;    // Clock for updating the game
        std::shared_ptr<World> m_currentWorld;  // Current world loaded

        sf::Clock m_CleanCycleClock;  // Clock for cleaning up resources periodically
        float m_CleanCycleInterval;   // Interval for cleanup

        void UpdateInternal(float dt);  // Internal update method
        void RenderInternal();          // Internal render method
        virtual void Render();          // Custom render method for derived classes
    };

    // Template function definition
    template<typename WorldType>
    std::weak_ptr<WorldType> Application::LoadWorld()
    {
        // Logging world load attempt
        LOG("Attempting to load world of type WorldType");

        // Create new world instance of type WorldType
        std::shared_ptr<WorldType> newWorld{ new WorldType{this} };
        LOG("WorldType instance created");

        // Set the current world
        m_currentWorld = newWorld;
        LOG("m_currentWorld set");

        // Call BeginPlay after world creation
        m_currentWorld->BeginPlayInternal();

        return newWorld;
    }
}
