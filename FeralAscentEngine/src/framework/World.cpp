#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include <SFML/Graphics.hpp>

namespace fa {

    // Constructor now takes a gravity vector
    World::World(Application* owningApp, const b2Vec2& gravity)
        :
        m_owningApp(owningApp),
        m_BeginPlay(false),
        b2WorldInstance(gravity)  // Initialize Box2D with the given gravity
    {
    }

    World::~World() {
        CleanCycle();
    }

    void World::UpdateInternal(float dt) {
        // Update all actors and Box2D world
        LOG("Amount of Actors: %u", m_Actors.size());

        for (auto& actor : m_Actors) {
            actor->Update(dt);
        }

        b2WorldInstance.Step(dt, 8, 3);  // Default velocity and position iterations

        CleanCycle();
    }

    void World::Render(sf::RenderWindow& window) {
        for (auto& actor : m_Actors) {
            actor->Render(window);
        }
    }

    void World::BeginPlay() {
        // World initialization logic
    }

    void World::BeginPlayInternal() {
        if (!m_BeginPlay) {
            m_BeginPlay = true;
            BeginPlay();
        }
    }

    void World::Update(float dt) {
        UpdateInternal(dt);  // Call internal update method
    }

    void World::CleanCycle() {
        // Remove all pending actors that need to be deleted
        for (auto& actor : m_pendingActors) {
            auto it = std::find(m_Actors.begin(), m_Actors.end(), actor);
            if (it != m_Actors.end()) {
                m_Actors.erase(it);
            }
        }
        m_pendingActors.clear();
    }

    b2World& World::GetB2World() {
        return b2WorldInstance;
    }

    sf::Vector2u World::GetWindowSize() const {
        return m_owningApp->GetWindowSize();
    }

    void World::SetGravity(const b2Vec2& gravity) {
        b2WorldInstance.SetGravity(gravity);
    }

    void World::AddActor(std::shared_ptr<Actor> actor) {
        m_Actors.push_back(actor);
    }

    void World::AddActor(Actor* actor) {
        m_Actors.push_back(std::shared_ptr<Actor>(actor));  // Wrap raw pointer in shared_ptr
    }

    // Method to remove an actor from the world
    void World::RemoveActor(std::shared_ptr<Actor> actor) {
        if (actor) {
            // Check both m_Actors and m_pendingActors
            auto itPending = std::find(m_pendingActors.begin(), m_pendingActors.end(), actor);
            if (itPending != m_pendingActors.end()) {
                m_pendingActors.erase(itPending);
            }

            auto itActor = std::find(m_Actors.begin(), m_Actors.end(), actor);
            if (itActor != m_Actors.end()) {
                m_Actors.erase(itActor);
            }
        }
    }



}
