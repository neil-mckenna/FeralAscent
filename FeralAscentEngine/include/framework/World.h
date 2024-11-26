#pragma once

#include <vector>
#include <memory>
#include "framework/Actor.h"
#include "framework/Application.h"
#include "framework/Core.h"
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

namespace fa {

    class World {
    public:
        // Constructor and Destructor
        World(Application* owningApp, const b2Vec2& gravity);
        ~World();

        // Update and Render methods
        void UpdateInternal(float dt);  // Internal updates, e.g., actor updates
        void Render(sf::RenderWindow& window);  // Render all actors

        // BeginPlay methods
        void BeginPlay();  // Called when the world starts
        void BeginPlayInternal();  // Internal method to handle logic on start

        // Custom update and clean cycle
        void Update(float dt);  // Custom updates
        void CleanCycle();  // Handle any pending destruction of actors

        // Getter for Box2D world
        b2World& GetB2World();

        // Window size for boundaries and calculations
        sf::Vector2u GetWindowSize() const;

        // Set gravity for the world
        void SetGravity(const b2Vec2& gravity);

        // Methods to manage actors
        void AddActor(std::shared_ptr<Actor> actor);  // Add actor to active list
        void AddActor(Actor* actor);
        void RemoveActor(std::shared_ptr<Actor> actor);  // Remove actor from active list
        void AddPendingActor(std::shared_ptr<Actor> actor);  // Add actor to pending list
        void RemovePendingActor(std::shared_ptr<Actor> actor);  // Remove actor from pending list
        void CleanPendingActors();  // Transfer pending actors to active list



    private:

        Application* m_owningApp;  // Pointer to the owning application
        bool m_BeginPlay;  // Flag to track if the world has started
        b2World b2WorldInstance;  // Box2D world instance for physics simulations

        std::vector<std::shared_ptr<Actor>> m_Actors;  // List of actors in the world
        std::vector<std::shared_ptr<Actor>> m_pendingActors;  // List of pending actors to add




    };
}
