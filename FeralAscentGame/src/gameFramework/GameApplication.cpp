// GameApplication.cpp
#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Platform.h"
#include "framework/Player.h"
#include <SFML/Graphics.hpp>

// Factory method to create a game application derived from the application class
fa::Application* GetApplication() {
    return new fa::GameApplication();
}

namespace fa {

    GameApplication::GameApplication()
        : m_Window(sf::VideoMode(1024, 768), "Feral Ascent"),  // Initialize SFML window
        m_DebugDraw(m_Window),
        m_Counter(0.0f),
        m_BoundaryLeft(nullptr),
        m_BoundaryRight(nullptr),
        m_BoundaryTop(nullptr),
        m_BoundaryBottom(nullptr),
        m_Player(nullptr),
        m_World(nullptr)  // Initialize m_World to nullptr
    {
        // Initialize Box2D world and gravity
        b2Vec2 gravity(0.0f, -9.8f);  // Gravity vector
        m_World = new World(this, gravity);  // Pass gravity to World constructor

        // Initialize debug draw for Box2D
        m_World->GetB2World().SetDebugDraw(&m_DebugDraw);

        // Initialize boundaries to keep player inside the screen
        InitBoundaries();

        // Initialize the player at a starting position
        m_Player = new Player(m_World->GetB2World(), sf::Vector2f(512.0f, 384.0f));  // Center of the screen
    }

    void GameApplication::InitBoundaries() {
        float windowWidth = 1024.0f;
        float windowHeight = 768.0f;
        float boundaryThickness = 10.0f;

        m_BoundaryLeft = new Platform(m_World->GetB2World(), sf::Vector2f(0, windowHeight / 2), sf::Vector2f(boundaryThickness, windowHeight));
        m_BoundaryRight = new Platform(m_World->GetB2World(), sf::Vector2f(windowWidth - boundaryThickness, windowHeight / 2), sf::Vector2f(boundaryThickness, windowHeight));
        m_BoundaryTop = new Platform(m_World->GetB2World(), sf::Vector2f(windowWidth / 2, 0), sf::Vector2f(windowWidth, boundaryThickness));
        m_BoundaryBottom = new Platform(m_World->GetB2World(), sf::Vector2f(windowWidth / 2, windowHeight - boundaryThickness), sf::Vector2f(windowWidth, boundaryThickness));
    }

    void GameApplication::HandleEvents() {
        sf::Event event;
        while (m_Window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_Window.close();  // Close the window if the close event is triggered
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    m_Window.close();  // Close the window if Escape key is pressed
                }
            }
            else if (event.type == sf::Event::Resized) {
                // Handle window resizing
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                m_Window.setView(sf::View(visibleArea));
            }
        }
    }

    void GameApplication::Update(float deltaTime) {
        m_Counter += deltaTime;
        m_World->Update(deltaTime);  // Update Box2D world (e.g., physics)

        // Update player movement (e.g., simple left/right movement)
        if (m_Player) {
            m_Player->Update(deltaTime);
        }
    }

    void GameApplication::Render() {
        m_Window.clear();
        m_World->Render(m_Window);  // Render the world and all its actors

        if (m_Player) {
            m_Player->Render(m_Window);  // Render the player
        }

        m_Window.display();
    }

    GameApplication::~GameApplication() {
        // Cleanup resources
        delete m_BoundaryLeft;
        delete m_BoundaryRight;
        delete m_BoundaryTop;
        delete m_BoundaryBottom;
        delete m_Player;
        delete m_World;
    }

    void GameApplication::Run() {
        sf::Clock clock;
        while (m_Window.isOpen()) {
            sf::Time deltaTime = clock.restart();

            // Handle events (e.g., window close event)
            sf::Event event;
            while (m_Window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    m_Window.close();
                }
            }

            Update(deltaTime.asSeconds());
            Render();
        }
    }

    void GameApplication::Initialize() {
        // Any additional initialization steps can be placed here
    }

}
