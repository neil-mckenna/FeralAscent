#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include <SFML/Graphics.hpp>
#include <algorithm>  // For std::find

namespace fa {

    World::World(Application* owningApp, const b2Vec2& gravity)
        : m_owningApp(owningApp),
        m_BeginPlay(false),
        b2WorldInstance(gravity)  // Initialize Box2D with the given gravity
    {
    }

    World::~World() {
        CleanCycle();  // Ensure any pending actors are cleaned up
    }




    void World::BeginPlay() {
        // World initialization logic, e.g., spawning actors or setting up environments
    }

    void World::BeginPlayInternal() {
        if (!m_BeginPlay) {
            m_BeginPlay = true;
            BeginPlay();
        }
    }

    void World::Update(float dt) {
        //LOG("World Updating");
        UpdateInternal(dt);  // Call the internal update method for actors and physics
    }

    void World::UpdateInternal(float dt) {
        // Update all actors and Box2D world
        LOG("Amount of Actors: %zu", m_Actors.size());

        for (auto& actor : m_Actors) {
            actor->Update(dt);  // Update each actor
        }

        b2WorldInstance.Step(dt, 8, 3);  // Default velocity and position iterations for Box2D

        CleanCycle();  // Clean up any pending actors
    }

    void World::Render(sf::RenderWindow& window) {
        for (auto& actor : m_Actors) {
            actor->Render(window);  // Render each actor to the window
        }
    }

    void World::CleanCycle() {
        // Remove all pending actors that need to be deleted from the world
        for (auto& actor : m_pendingActors) {
            auto it = std::find(m_Actors.begin(), m_Actors.end(), actor);
            if (it != m_Actors.end()) {
                m_Actors.erase(it);  // Erase the actor from the active list
            }
        }
        m_pendingActors.clear();  // Clear the pending actors list
    }

    b2World* World::GetB2World() {
        return &b2WorldInstance;  // Return a pointer to the Box2D world instance
    }

    sf::Vector2u World::GetWindowSize() const {
        return m_owningApp->GetWindowSize();  // Get the window size from the owning application
    }

    void World::SetGravity(const b2Vec2& gravity) {
        b2WorldInstance.SetGravity(gravity);  // Set the gravity in the Box2D world
    }

    void World::AddActor(std::shared_ptr<Actor> actor) {
        LOG("Added new actor");
        m_Actors.push_back(actor);  // Add actor to the active list
    }

    void World::AddActor(Actor* actor) {
        m_Actors.push_back(std::shared_ptr<Actor>(actor));  // Wrap raw pointer in shared_ptr and add it
    }

    // Method to remove an actor from the world
    void World::RemoveActor(std::shared_ptr<Actor> actor) {

        if (actor) {
            // Remove the actor from the pending actors list (if it exists)
            auto removeFromPending = std::remove(m_pendingActors.begin(), m_pendingActors.end(), actor);
            if (removeFromPending != m_pendingActors.end()) {
                m_pendingActors.erase(removeFromPending, m_pendingActors.end());
            }

            // Remove the actor from the active actors list (if it exists)
            auto removeFromActive = std::remove(m_Actors.begin(), m_Actors.end(), actor);
            if (removeFromActive != m_Actors.end()) {
                m_Actors.erase(removeFromActive, m_Actors.end());
            }
        }
    }

    void World::LogActors() {
        LOG("Logging all actors in m_World:");

        // Iterate through the vector and log each actor
        for (const auto& actor : m_Actors) {
            LOG("Actor pointer: %p", actor.get());

        }
    }

    void World::ClearAllActors()
    {
        // Loop through each actor in the vector and delete it
        for (auto actor : m_Actors) {
            actor->~Actor();  // Call the destructor for each actor
        }
        // Clear the vector (removes all pointers, leaving it empty)
        m_Actors.clear();

    }

}
