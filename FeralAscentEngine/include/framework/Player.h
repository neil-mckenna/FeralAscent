#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include <string>

namespace fa {

    class Player {
    public:
        // Constructor and destructor
        Player(b2World& world, const sf::Vector2f& position);
        ~Player();

        // Update the player (movement and animation)
        void Update(float deltaTime);

        // Render the player
        void Render(sf::RenderWindow& window);

    private:
        // Initialize Box2D physics for the player
        void InitPhysics(b2World& world, const sf::Vector2f& position);

        // Load animation textures
        void LoadTextures(const std::string& prefix, int frameCount, std::vector<sf::Texture>& textures);

        // Animation properties
        std::vector<sf::Texture> m_RightWalkTextures;  // Textures for right walking animation
        std::vector<sf::Texture> m_LeftWalkTextures;   // Textures for left walking animation
        int m_CurrentFrame;                            // Current frame index
        float m_AnimationTimer;                        // Timer to control frame changes
        float m_FrameDuration;                         // Duration of each frame

        // Movement direction flags
        bool m_IsMovingRight;
        bool m_IsMovingLeft;

        // SFML sprite and texture
        sf::Sprite m_Sprite;

        // Box2D physics body
        b2Body* m_Body;
    };

} // namespace fa

#endif // PLAYER_H
