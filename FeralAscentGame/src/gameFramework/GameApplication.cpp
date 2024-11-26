// GameApplication.cpp
#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Platform.h"
#include "framework/Player.h"
#include "framework/Core.h"
#include <SFML/Graphics.hpp>

// Factory method to create a game application derived from the application class
fa::Application* GetApplication() {
    return new fa::GameApplication();
}

using namespace std;

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
        m_World(nullptr),  // Initialize m_World to nullptr
        m_GroundPlatform(nullptr)  // Initialize the ground platform pointer
    {


        // Initialize Box2D world and gravity
        b2Vec2 gravity(0.0f, -9.8f);  // Gravity vector
        m_World = new World(this, gravity);  // Pass gravity to World constructor

        // Enable debug draw flags
        uint32 debugFlags = 0;
        debugFlags |= b2Draw::e_shapeBit;           // Draw shapes
        debugFlags |= b2Draw::e_jointBit;           // Draw joints
        debugFlags |= b2Draw::e_centerOfMassBit;    // Draw centers of mass
        m_DebugDraw.SetFlags(debugFlags);

        // Initialize debug draw for Box2D
        m_World->GetB2World().SetDebugDraw(&m_DebugDraw);

        // Initialize boundaries to keep player inside the screen
        InitBoundaries();


        // Initialize the player at a starting position, use shared_ptr instead of unique_ptr
        m_Player = make_unique<Player>(m_World, sf::Vector2f(m_Window.getSize().x / 2.f, 100.f));  // Center of the screen

        // Create ground platform in the world
        m_GroundPlatform = new fa::Platform(
            m_World,
            sf::Vector2f(m_Window.getSize().x / 2.f, m_Window.getSize().y - 100.f),
            sf::Vector2f(m_Window.getSize().x, 20.0f),
            "assets/PNG/terrain/land_sprites/tile000.png"
        );

        // Add player to the world, cast Player to Actor
        m_World->AddActor(m_Player.get());  // Player is now a make_unique<Actor>

        m_World->AddActor(m_BoundaryTop);
        m_World->AddActor(m_BoundaryLeft);
        m_World->AddActor(m_BoundaryRight);
        m_World->AddActor(m_BoundaryBottom);

    }

    void GameApplication::InitBoundaries() {
        float windowWidth = 1024.0f;
        float windowHeight = 768.0f;
        float boundaryThickness = 10.0f;

        m_BoundaryLeft = new Platform(
            m_World, // world ptr
            sf::Vector2f(0, windowHeight / 2), // pos
            sf::Vector2f(boundaryThickness, windowHeight), // location
            "assets/PNG/terrain/land_sprites/tile000.png" // texture
        );

        m_BoundaryRight = new Platform(
            m_World,
            sf::Vector2f(windowWidth - boundaryThickness, windowHeight / 2),
            sf::Vector2f(boundaryThickness, windowHeight),
            "assets/PNG/terrain/land_sprites/tile000.png"
        );

        m_BoundaryTop = new Platform(
            m_World,
            sf::Vector2f(windowWidth / 2, 0),
            sf::Vector2f(windowWidth, boundaryThickness),
            "assets/PNG/terrain/land_sprites/tile000.png"
        );
        m_BoundaryBottom = new Platform(
            m_World,
            sf::Vector2f(windowWidth / 2, windowHeight - boundaryThickness),
            sf::Vector2f(windowWidth, boundaryThickness),
            "assets/PNG/terrain/land_sprites/tile000.png"
        );
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

        }
    }

    void GameApplication::Update(float deltaTime) {
        m_Counter += deltaTime;

        //LOG("Game Application is updating");

        m_World->Update(deltaTime);  // Update Box2D world (e.g., physics)



        // Update player movement (e.g., simple left/right movement)
        if (m_Player) {
            m_Player->Update(deltaTime);
        }


    }

    void GameApplication::Render() {

        // make screen background white
        m_Window.clear(sf::Color::White);

        m_World->Render(m_Window);  // Render the world and all its actors

        if (m_Player) {
            m_Player->Render(m_Window);  // Render the player
        }

        if (m_GroundPlatform) {
            m_GroundPlatform->Render(m_Window);  // Render the ground platform
        }

        m_Window.display();
    }

    GameApplication::~GameApplication() {
        // Cleanup resources
        delete m_BoundaryLeft;
        delete m_BoundaryRight;
        delete m_BoundaryTop;
        delete m_BoundaryBottom;
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
