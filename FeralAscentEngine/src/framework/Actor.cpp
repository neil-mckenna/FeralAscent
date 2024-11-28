#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/Component.h"
#include "framework/TextureComponent.h"
#include "framework/PhysicsComponent.h"
#include <SFML/Graphics.hpp>

namespace fa {

    Actor::Actor(World* owningWorld, const sf::Vector2f& position, const std::string& texturePath) :
        m_owningWorld{ owningWorld },
        m_Position{ position },
        m_TexturePath{ texturePath},
        m_TextureComponent{ new TextureComponent(texturePath)}

    {
        m_ActorName = "Actor name";


        InitializeComponents(texturePath);


    }

    void Actor::InitializeComponents(const std::string& texturePath)
    {
        // Initialize the texture component
        auto textureComponent = std::make_shared<TextureComponent>(texturePath);
        AddComponent(textureComponent);

        // Initialize PhysicsComponent
        //m_PhysicsComponent = std::make_shared<PhysicsComponent>(m_owningWorld->GetB2World(), position);
        //AddComponent(m_PhysicsComponent);  // Add physics component to actor

        // Ensure the texture component exists and has a valid texture
        if (m_TextureComponent && m_TextureComponent->GetTexture()) {
            // Get the texture from the component
            sf::Texture* texture = m_TextureComponent->GetTexture();

            // Set the texture to the sprite inside the component
            m_TextureComponent->GetSprite().setTexture(*texture);

            // Set the origin of the sprite to the center of the texture
            m_TextureComponent->GetSprite().setOrigin(texture->getSize().x / 2.f, texture->getSize().y / 2.f);
        }
        else {
            LOG_ERROR("Texture component is missing or texture is not set.");
        }


    }

    Actor::~Actor() {
        // Destructor logic for cleanup (if needed)
        LOG_WARNING("Actor was destroyed! Check if this is the approtiate methid call");
    }

    // Update all components of the actor
    void Actor::Update(float dt) {
        for (auto& component : m_Components) {
            component->Update(dt);
        }
    }

    // Render all components that need to be rendered (e.g., TextureComponent)
    void Actor::Render(sf::RenderWindow& window) {
        if (m_Components.empty()) {
            LOG_ERROR("Actor has no components to render.");
        }

        for (auto& component : m_Components) {
            if (!component) {
                LOG_ERROR("A component in m_Components is nullptr.");
                continue;  // Skip to the next component
            }

            // Attempt to cast to TextureComponent
            auto textureComponent = dynamic_cast<TextureComponent*>(component.get());

            if (textureComponent) {
                try {
                    textureComponent->Render(window);  // Render the texture component if it exists
                }
                catch (const std::exception& e) {
                    LOG("Error rendering texture component: %s", string(e.what()));
                }
            }
            else {
                LOG_ERROR("Component is not a TextureComponent. Skipping render.");
            }
        }
    }

    // Add a component to the actor
    void Actor::AddComponent(std::shared_ptr<Component> component) {
        m_Components.push_back(component);
    }



    // Retrieve a component of a specific type (returns nullptr if not found)
    template<typename T>
    T* Actor::GetComponent() const {
        for (auto& component : m_Components) {
            T* foundComponent = dynamic_cast<T*>(component.get());
            if (foundComponent) {
                return foundComponent;
            }
        }
        return nullptr;  // Return nullptr if no matching component is found
    }

}
