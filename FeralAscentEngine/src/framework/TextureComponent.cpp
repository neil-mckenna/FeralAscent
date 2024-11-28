// framework/TextureComponent.cpp
#include "framework/TextureComponent.h"
#include "framework/AssetManager.h"
#include "framework/Core.h"

namespace fa {


    TextureComponent::TextureComponent(const std::string& texturePath) {
        SetTexture(texturePath);
    }

    void TextureComponent::Update(float dt) {
        // Here you could update animation or other logic if needed
    }

    void TextureComponent::Render(sf::RenderWindow& window) {
        if (m_Texture) {
            LOG("Textcomponet Rendering");
            window.draw(m_Sprite);
        }
        else {
            LOG("No texture to render.");
        }
    }

    void TextureComponent::SetTexture(const std::string& texturePath) {
        m_Texture = AssetManager::Get().LoadTexture(texturePath);
        if (m_Texture) {
            m_Sprite.setTexture(*m_Texture);
        }
        else {
            LOG("Failed to load texture: %s", texturePath.c_str());
        }
    }

    sf::Sprite& TextureComponent::GetSprite() {
        return m_Sprite;
    }
}
