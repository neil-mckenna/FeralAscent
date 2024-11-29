#include "framework/TextureComponent.h"
#include "framework/AssetManager.h"
#include "framework/Core.h"

namespace fa {

    TextureComponent::TextureComponent(const std::string& texturePath) {
        LOG("Texture Component ctor: texturePath: %s", texturePath.c_str());
        SetTexture(texturePath);
    }

    void TextureComponent::Update(float deltaTime)
    {
        // Handle animation updates
        m_AnimationTimer += deltaTime;
        if (m_AnimationTimer >= m_FrameDuration) {
            m_AnimationTimer -= m_FrameDuration;

            if (!m_RightWalkTextures.empty()) {
                m_CurrentFrame = (m_CurrentFrame + 1) % m_RightWalkTextures.size();
                m_Sprite.setTexture(m_RightWalkTextures[m_CurrentFrame]);
            }
            else if (!m_LeftWalkTextures.empty()) {
                m_CurrentFrame = (m_CurrentFrame + 1) % m_LeftWalkTextures.size();
                m_Sprite.setTexture(m_LeftWalkTextures[m_CurrentFrame]);
            }
        }
    }

    void TextureComponent::Render(sf::RenderWindow& window) {
        if (m_Texture) {
            //LOG("Textcomponet Rendering");
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
            LOG("Loaded Texture Successfully");
        }
        else {
            LOG("Failed to load texture: %s", texturePath.c_str());
        }
    }

    std::shared_ptr<sf::Texture> TextureComponent::GetTexture() const {
        return m_Texture;
    }

    sf::Sprite& TextureComponent::GetSprite() {
        return m_Sprite;
    }

    // Load walking textures for right and left animations
    void TextureComponent::LoadWalkingTextures() {
        LOG("ANIMATIONG");

        LoadTextures("PNG/player/walking_sprites/right_walk_", 9, m_RightWalkTextures);
        LoadTextures("PNG/player/walking_sprites/left_walk_", 9, m_LeftWalkTextures);

        // Set the initial texture (starting with right walk animation)
        if (!m_RightWalkTextures.empty()) {
            m_Sprite.setTexture(m_RightWalkTextures[0]);
        }

        if (m_Sprite.getTexture()) {
            m_Sprite.setOrigin(m_Sprite.getTexture()->getSize().x / 2.f, m_Sprite.getTexture()->getSize().y / 2.f);
        }
    }

    // Helper method to load textures into a vector
    void TextureComponent::LoadTextures(const std::string& basePath, int numFrames, std::vector<sf::Texture>& textureVector) {
        for (int i = 1; i <= numFrames; ++i) {
            std::string texturePath = basePath + std::to_string(i) + ".png";
            auto texture = AssetManager::Get().LoadTexture(texturePath);  // Load texture as shared pointer
            if (texture) {
                textureVector.push_back(*texture);  // Dereference shared pointer to store texture in vector
            }
            else {
                LOG("Failed to load texture: %s", texturePath.c_str());
            }
        }
    }


} // namespace fa
