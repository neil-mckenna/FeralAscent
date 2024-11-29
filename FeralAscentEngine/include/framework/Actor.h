#pragma once

#include "framework/Component.h"
#include "framework/TextureComponent.h"
#include "framework/PhysicsComponent.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace fa {

    class World;  // Forward declaration of World class

    class Actor {
    public:
        // Constructor
        Actor(World* owningWorld, const sf::Vector2f& position, const std::string& texturePath);

        // Destructor
        ~Actor();

        // Update the actor's components
        void Update(float dt);

        // Render the actor's components
        void Render(sf::RenderWindow& window);

        // Add a component to the actor
        void AddComponent(std::shared_ptr<Component> component);

        // Get a component of a specific type
        template <typename T>
        T* GetComponent() const;

        // Handle movement by passing velocity externally
        void HandleMovement(const sf::Vector2f& velocity, float dt);

    protected:
        // Components of the actor
        std::shared_ptr<TextureComponent> m_TextureComponent;
        std::shared_ptr<PhysicsComponent> m_PhysicsComponent;

        // Actor's position in world space
        sf::Vector2f m_Position;

        // Actor's name (for debugging)
        std::string m_ActorName;

    private:
        // Initialize the actor's components
        void InitializeComponents(const std::string& texturePath);

        // The world this actor belongs to
        World* m_owningWorld;


        // Path to the texture used for the actor
        std::string m_TexturePath;


        // Vector of all components (renderable, physics, etc.)
        std::vector<std::shared_ptr<Component>> m_Components;

    };

}  // namespace fa
