#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Component.h"  // Include the header file for Component class

namespace fa {

    class TextureComponent : public Component {  // Inherit from Component
    public:
        // Constructor with a single texture path
        explicit TextureComponent(const std::string& texturePath);

        // Update the animation
        void Update(float deltaTime) override;

        // Render the sprite to the window
        void Render(sf::RenderWindow& window) override;

        // Set the texture (for a single texture)
        void SetTexture(const std::string& texturePath);

        // Get the texture (for accessing it directly)
        std::shared_ptr<sf::Texture> GetTexture() const;

        // Get the sprite (for rendering)
        sf::Sprite& GetSprite();

        // Load the walking animation textures
        void LoadPlayerWalkingTextures();

        // single file load
        void TextureComponent::LoadTexture(const std::string& texturePath);

    private:


        // Load multiple textures into a vector
        void LoadTextures(const std::string& basePath, int numFrames, std::vector<sf::Texture>& textureVector);

        // Texture for the sprite
        std::shared_ptr<sf::Texture> m_Texture;

        // Sprite to display the texture
        sf::Sprite m_Sprite;

        // Animation-related variables
        float m_AnimationTimer = 0.0f;
        int m_CurrentFrame = 0;
        float m_FrameDuration = 0.1f;  // Duration between frames
        std::vector<sf::Texture> m_RightWalkTextures;  // Right walking animation textures
        std::vector<sf::Texture> m_LeftWalkTextures;   // Left walking animation textures
    };

} // namespace fa
