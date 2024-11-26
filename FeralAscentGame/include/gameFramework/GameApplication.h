#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "framework/World.h"
#include "framework/Player.h"
#include "framework/Platform.h"
#include "framework/DebugDraw.h"

namespace fa {

    class GameApplication : public Application {
    public:
        // Constructor & Destructor
        GameApplication();
        virtual ~GameApplication() override;

        // Main game loop functions
        void Run();
        void Initialize();
        void Update(float deltaTime);
        void Render();

    private:
        // Initialize boundaries (e.g., walls of the game world)
        void InitBoundaries();

        // Handle input events (key press, mouse click, etc.)
        void HandleEvents();

        // SFML window to render the game
        sf::RenderWindow m_Window;

        // Game world instance
        World* m_World;

        // Debug draw for Box2D
        DebugDraw m_DebugDraw;

        // Player actor (using smart pointer for automatic memory management)
        std::unique_ptr<Player> m_Player;

        // Add this declaration inside the class
        fa::Platform* m_GroundPlatform;


        // Timed counter for game logic updates
        float m_Counter;

        // Boundaries (platforms acting as walls)
        Platform* m_BoundaryLeft;
        Platform* m_BoundaryRight;
        Platform* m_BoundaryTop;
        Platform* m_BoundaryBottom;



        // Quit button (if adding custom buttons)
        sf::RectangleShape m_QuitButton;
    };

}

#endif // GAME_H
