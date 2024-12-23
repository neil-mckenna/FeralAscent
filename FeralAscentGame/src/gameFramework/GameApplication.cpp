#include "gameFramework/GameApplication.h"
#include "framework/AssetManager.h"
#include "framework/World.h"
#include "framework/Platform.h"
#include "framework/Player.h"
#include "framework/Core.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <config.h>


// Factory method to create a game application derived from the application class
fa::Application* GetApplication() {
    LOG("Factory Method to Call Game Application");
    return new fa::GameApplication();
}

namespace fa {

    GameApplication::GameApplication()
        : Application(1024, 768, "Feral Ascent", sf::Style::Resize | sf::Style::Close),  // Initialize SFML window
        m_DebugDraw{ m_DebugDraw },
        m_Counter{ 0.0f },
        m_BoundaryLeft{ nullptr },
        m_BoundaryRight{ nullptr },
        m_BoundaryTop{ nullptr },
        m_BoundaryBottom{ nullptr },
        m_BoundaryCenter{ nullptr },
        m_World{ std::make_unique<World>(this, b2Vec2(0.0f, 9.8f)) }, // initialize world with gravity
        m_Player{ nullptr },

        m_GroundPlatform{ nullptr }  // Initialize the ground platform pointer

    {
        LOG("Game Application Constructor Started");

        AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
        LOG("Asset root directory set to: %s", GetResourceDir().c_str());

        LOG("Window Size: %d %d", GetWindowSize().x, GetWindowSize().y);

        // create player
        m_Player = std::make_unique<Player>(  // Initialize with make_unique
          m_World.get(),  // Pass m_World or nullptr if needed
          sf::Vector2f(GetWindowSize().x / 2.f, 100.f),  // Center of the screen
          "PNG/player/walking_sprites/right_walk_1.png"  // Path to texture
        );

        // add player to actors list
        m_World->AddActor(m_Player.get());



        LOG("Game Application Constructor Completed");

    }

    void GameApplication::InitBoundaries()
    {
        LOG("Initialize Boundaries");


        float windowWidth = 1024.0f;
        float windowHeight = 768.0f;
        float boundaryThickness = 30.0f;

        m_BoundaryLeft = std::make_unique<Boundary>(
            m_World.get(),
            sf::Vector2f(0, windowHeight / 2),  // Position
            sf::Vector2f(boundaryThickness, windowHeight),  // Size
            "PNG/terrain/land_sprites/tile000.png"  // Texture
        );


        m_BoundaryRight = std::make_unique<Boundary>(
            m_World.get(),
            sf::Vector2f(windowWidth - boundaryThickness, windowHeight / 2),
            sf::Vector2f(boundaryThickness, windowHeight),
            "PNG/terrain/land_sprites/tile000.png"
        );

        m_BoundaryTop = std::make_unique<Boundary>(
            m_World.get(),
            sf::Vector2f(windowWidth / 2, 0),
            sf::Vector2f(windowWidth, boundaryThickness),
            "PNG/terrain/land_sprites/tile000.png"
        );

        m_BoundaryBottom = std::make_unique<Boundary>(
            m_World.get(),
            sf::Vector2f(windowWidth / 2, windowHeight - boundaryThickness),
            sf::Vector2f(windowWidth, boundaryThickness),
            "PNG/terrain/land_sprites/tile000.png"
        );

        m_BoundaryCenter = std::make_unique<Boundary>(
            m_World.get(),
            sf::Vector2f(windowWidth / 2.f, windowHeight  / 2.f),
            sf::Vector2f(60.f, 60.f),
            "PNG/terrain/land_sprites/tile000.png"
        );

        m_World.get()->AddActor(m_BoundaryLeft.get());
        m_World.get()->AddActor(m_BoundaryRight.get());
        m_World.get()->AddActor(m_BoundaryTop.get());
        m_World.get()->AddActor(m_BoundaryBottom.get());

        m_World.get()->AddActor(m_BoundaryCenter.get());
    }



    void GameApplication::Run() {

        //LOG("Game Application Running");

        Initialize();

        //LOG("Window Size: %u x %u", m_Window.getSize().x, m_Window.getSize().y);


        sf::Clock clock;
        while (m_Window.isOpen()) {
            sf::Time deltaTime = clock.restart();

            // Handle events
            HandleEvents();

            Update(deltaTime.asSeconds());
            Render();
        }
    }

    void GameApplication::Initialize()
    {
        LOG("Game Application: Initilaizing");

        // Initialize Box2D world and gravity
        //b2Vec2 gravity(0.0f, -9.8f);  // Gravity vector
        //m_World = std::make_unique<World>(this, gravity);  // Pass gravity to World constructor

        SetupDebug();

        // Initialize boundaries to keep player inside the screen
        InitBoundaries();

        //InitializePlayer();



        // Create ground platform in the world
        /*m_GroundPlatform = std::make_unique<Platform>(
            m_World.get(),
            sf::Vector2f(m_Window.getSize().x / 2.f, m_Window.getSize().y - 100.f),
            sf::Vector2f(m_Window.getSize().x, 20.0f),
            "assets/PNG/terrain/land_sprites/tile000.png"
        );*/


    }

    void GameApplication::SetupDebug()
    {
        LOG("Setup Debug Settings");

        // Enable debug draw flags
        uint32 debugFlags = 0;
        debugFlags |= b2Draw::e_shapeBit;           // Draw shapes
        debugFlags |= b2Draw::e_jointBit;           // Draw joints
        debugFlags |= b2Draw::e_centerOfMassBit;    // Draw centers of mass
        m_DebugDraw.SetFlags(debugFlags);

        // Initialize debug draw for Box2D
        m_World->GetB2World()->SetDebugDraw(&m_DebugDraw);
    }


    void GameApplication::Update(float deltaTime)
    {
        //LOG("Game Application: Updating");

        m_Counter += deltaTime;

        m_World->Update(deltaTime);  // Update Box2D world (e.g., physics)


        // Update player movement
        //LOG("Player  %p", m_Player.get());
        if (m_Player.get()) {
            m_Player.get()->Update(deltaTime);
        }

        if (m_BoundaryLeft.get())
        {
            //LOG("Boundary Left %p ", m_BoundaryLeft.get());
            m_BoundaryLeft.get()->Update(deltaTime);
            m_BoundaryLeft.get()->Render(m_Window);
        }

        if (m_BoundaryRight.get())
        {
            //LOG("Boundary Right %p ", m_BoundaryRight.get());
            m_BoundaryRight.get()->Update(deltaTime);

        }

        if (m_BoundaryTop.get())
        {
            //LOG("Boundary Top %p ", m_BoundaryTop.get());
            m_BoundaryTop.get()->Update(deltaTime);

        }


        if (m_BoundaryBottom.get())
        {
            //LOG("Boundary Bottom %p ", m_BoundaryBottom.get());
            m_BoundaryBottom.get()->Update(deltaTime);

        }

        if (m_BoundaryCenter.get())
        {
            //LOG("Boundary Center %p ", m_BoundaryCenter.get());
            m_BoundaryCenter.get()->Update(deltaTime);

        }
    }

    void GameApplication::Render()
    {
        //LOG("Game Application: Rendering");

        m_Window.clear(sf::Color::White);  // Clear the screen with white background

        // call world, then actors, then texture component render
        m_World->Render(m_Window);  // Render the world and all its actors


        //if (m_GroundPlatform) {
        //    m_GroundPlatform->Render(m_Window);  // Render the ground platform
        //}

        m_Window.display();
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


    // In the GameApplication destructor:
    GameApplication::~GameApplication() {

        LOG("Game Application: Deconstructor");

        if (m_World.get()) {
            LOG("m_World exists before destruction: %p", m_World.get());
        }
        else {
            LOG("m_World is nullptr");
        }

        if (m_World.get()) {
            m_World.get()->ClearAllActors();  // Manually clear any remaining actors
            m_World.reset();        // Optionally clear Box2D and other resources
        }


        if (m_Player)
        {
            m_Player.reset();
        }
    }
}
