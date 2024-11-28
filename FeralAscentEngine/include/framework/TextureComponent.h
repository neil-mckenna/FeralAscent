#pragma once

#include <SFML/Graphics.hpp>
#include "framework/Component.h"

namespace fa {

    class TextureComponent : public Component {
    public:


        // Constructor: Initialize with a texture path
        TextureComponent(const std::string& texturePath);

        // Override Update method (empty for now, could be extended for animations, etc.)
        void Update(float dt) override;

        // Override Render method to draw the sprite on the window
        void Render(sf::RenderWindow& window) override;

        // Set the texture to be used by the component
        void SetTexture(const std::string& texturePath);

        // Getter for the texture
        sf::Texture* GetTexture() { return m_Texture.get(); }

        sf::Sprite& GetSprite();

    private:
        // SFML Sprite to hold and render the texture
        sf::Sprite m_Sprite;

        // The texture to be used by the sprite
        std::shared_ptr<sf::Texture> m_Texture;
    };

}
