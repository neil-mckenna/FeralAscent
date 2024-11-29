#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "framework/World.h"
#include "framework/Player.h"
#include "framework/Platform.h"
#include "framework/Boundary.h"
#include "framework/DebugDraw.h"
#include "framework/Core.h"

namespace fa {

    class GameApplication : public Application {
    public:
        // Constructor & Destructor
        GameApplication();
        virtual ~GameApplication() override;

        // Main game loop functions
        void Run();
        void Initialize();
        void SetupDebug();

        void Update(float deltaTime);
        void Render();

    private:
        // Initialize boundaries (e.g., walls of the game world)
        void InitBoundaries();

        // Handle input events (key press, mouse click, etc.)
        void HandleEvents();

        // Game world instance
        unique<World> m_World;

        // Debug draw for Box2D
        DebugDraw m_DebugDraw;

        // Timed counter for game logic updates
        float m_Counter;

        // Player actor (using smart pointer for automatic memory management)
        unique<Player> m_Player;

        // Add this declaration inside the class
        unique<Platform> m_GroundPlatform;

        // Boundaries (platforms acting as walls)
        unique<Boundary> m_BoundaryLeft;
        unique<Boundary> m_BoundaryRight;
        unique<Boundary> m_BoundaryTop;
        unique<Boundary> m_BoundaryBottom;
        unique<Boundary> m_BoundaryCenter;



        // Quit button (if adding custom buttons)
        sf::RectangleShape m_QuitButton;
    };

}

#endif // GAME_H
