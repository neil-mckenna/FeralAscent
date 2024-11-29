#include "framework/Boundary.h"
#include "framework/Actor.h"
#include "framework/Core.h"

namespace fa {

    // Constructor implementation
    Boundary::Boundary(World* world, const sf::Vector2f& position, const sf::Vector2f& size, const std::string& texturePath) :

        Actor(world, position, texturePath),
        m_Position{ position },
        m_Size{ size },
        m_TextureComponent{ texturePath },
        m_body{}
    {

        LOG("Boundary Created at postion x=%f, y=%f ", position.x, position.y);

        // attempt to load a sprite
        // Ensure the texture component exists and has a valid texture
        if (m_TextureComponent.GetTexture()) {
            sf::Texture* texture = m_TextureComponent.GetTexture().get();
            m_TextureComponent.GetSprite().setTexture(*texture);
            m_TextureComponent.GetSprite().setOrigin(texture->getSize().x / 2.f, texture->getSize().y / 2.f);
        }
        else {
            LOG_ERROR("Boundary Texture component is missing or texture is not set.");
        }
    }

    // Render the boundary
    void Boundary::Render(sf::RenderWindow& window)
    {
        LOG("Boundary Updating");
        Actor::Render(window);




    }

    // Update the boundary (e.g., for animated textures)
    void Boundary::Update(float deltaTime) {
        //m_TextureComponent.Update(deltaTime);

        m_TextureComponent.GetSprite().setPosition(m_Position.x, m_Position.y);
    }

} // namespace fa
