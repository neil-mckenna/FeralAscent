#pragma once

#include <vector>
#include <memory>
#include "framework/Component.h"
#include "framework/TextureComponent.h"
#include "framework/PhysicsComponent.h"

using namespace std;
using namespace sf;


namespace fa {

    class World;
    class Actor {
    public:
        Actor(World* owningWorld, const sf::Vector2f& position, const std::string& texturePath);
        virtual ~Actor();

        // Update the actor and all of its components
        virtual void Update(float dt);
        virtual void Render(RenderWindow& window);

        // Add components to the actor
        void AddComponent(shared_ptr<Component> component);

        // Access components
        template<typename T>
        T* GetComponent() const;

    protected:
        string m_ActorName; // hold the path string temporary
        shared_ptr<TextureComponent> m_TextureComponent;  // Texture component
        shared_ptr<PhysicsComponent> m_PhysicsComponent;  // Physics component
        vector<shared_ptr<Component>> m_Components;  // Store components
        void InitializeComponents(const std::string& texturePath);  // Initialize components in the actor


    private:
        World* m_owningWorld;  // Pointer to the owning world
        Vector2f m_Position;  // Position of the actor
        string m_TexturePath; // hold the path string temporary

    };

}
