#include "framework/Actor.h"
#include "framework/Component.h"
#include "framework/World.h"  // Assuming World class is in the "framework" namespace
#include "framework/AssetManager.h"
#include "framework/Core.h"
#include <SFML/Graphics.hpp>

namespace fa {

    // Constructor
    Actor::Actor(World* owningWorld, const sf::Vector2f& position, const std::string& texturePath) :
        m_owningWorld{ owningWorld },
        m_Position{ position },
        m_TexturePath{ texturePath },
        m_TextureComponent{ std::make_shared<TextureComponent>(texturePath) },  // Initialize texture component
        m_PhysicsComponent{ std::make_shared<PhysicsComponent>(owningWorld->GetB2World(), position) },  // Initialize physics component
        m_Components{}  // Add components to the list
    {
        LOG("Actor Constructor called!");

        m_ActorName = "Actor name";
        InitializeComponents(texturePath);
    }

    // Destructor
    Actor::~Actor() {
        LOG_WARNING("Actor was destroyed!");
    }

    // Initialize the actor's components
    void Actor::InitializeComponents(const std::string& texturePath)
    {

        // Add components to m_Components vector
        m_Components.push_back(std::static_pointer_cast<Component>(m_TextureComponent));  // Cast to Component
        m_Components.push_back(std::static_pointer_cast<Component>(m_PhysicsComponent));

        // Ensure the texture component exists and has a valid texture
        if (m_TextureComponent && m_TextureComponent->GetTexture()) {
            sf::Texture* texture = m_TextureComponent->GetTexture().get();
            m_TextureComponent->GetSprite().setTexture(*texture);
            m_TextureComponent->GetSprite().setOrigin(texture->getSize().x / 2.f, texture->getSize().y / 2.f);
        }
        else {
            LOG_ERROR("Texture component is missing or texture is not set.");
        }

        // No need to add the physics component here; it's already added in the constructor
    }

    // Update the actor's components
    void Actor::Update(float dt) {
        //LOG("Components amount: %zu", m_Components.size());
        for (auto& component : m_Components) {
            component->Update(dt);
        }


    }

    // Render the actor's components
    void Actor::Render(sf::RenderWindow& window) {
        if (m_Components.empty()) {
            LOG_ERROR("Actor has no components to render.");
        }

        for (auto& component : m_Components) {
            if (!component) {
                LOG_ERROR("A component in m_Components is nullptr.");
                continue;
            }

            // Attempt to cast to TextureComponent
            auto textureComponent = dynamic_cast<TextureComponent*>(component.get());

            if (textureComponent) {
                try {
                    textureComponent->Render(window);  // Render the texture component
                }
                catch (const std::exception& e) {
                    LOG("Error rendering texture component: %s", e.what());
                }
            }
            else {
                //LOG_ERROR("Component is not a TextureComponent. Skipping render.");
            }

            // Attempt to cast to PhysicsComponent to render the debug shape
            auto physicsComponent = dynamic_cast<PhysicsComponent*>(component.get());

            if (physicsComponent) {
                try {
                    physicsComponent->Render(window);  // Render the debug shape (Box2D body visualization)
                }
                catch (const std::exception& e) {
                    //LOG("Error rendering physics component: %s", e.what());
                }
            }
        }
    }

    // Add a component to the actor
    void Actor::AddComponent(std::shared_ptr<Component> component) {
        m_Components.push_back(component);  // Add to the components list
    }

    // Get a component of a specific type (returns nullptr if not found)
    template <typename T>
    T* Actor::GetComponent() const {
        for (auto& component : m_Components) {
            T* foundComponent = dynamic_cast<T*>(component.get());
            if (foundComponent) {
                return foundComponent;
            }
        }
        return nullptr;  // Return nullptr if no matching component is found
    }

    // Handle movement by passing velocity externally
    void Actor::HandleMovement(const sf::Vector2f& velocity, float dt) {
        auto physicsComp = GetComponent<PhysicsComponent>();  // Get the PhysicsComponent

        if (physicsComp) {
            // Apply velocity to the PhysicsComponent
            physicsComp->ApplyVelocity(velocity, dt);
        }
    }

}  // namespace fa
