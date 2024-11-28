#pragma once

#include <Box2D/Box2D.h>
#include "framework/Component.h"

namespace fa {

    class PhysicsComponent : public Component {
    public:
        // Constructor: Initializes the component with a Box2D body definition
        PhysicsComponent(b2BodyDef bodyDef);

        // Destructor: cleans up the Box2D body when the component is destroyed
        ~PhysicsComponent();

        // Override Update method for physics updates (empty for now, could be extended)
        void Update(float dt) override;

        // Accessor for the Box2D body
        b2Body* GetBody() const;

        // Set the Box2D body's position
        void SetPosition(const b2Vec2& position);

        // Apply force to the body
        void ApplyForce(const b2Vec2& force);

        // Set the Box2D body to a new definition (e.g., after changing velocity)
        void SetBodyDefinition(b2BodyDef newDef);

    private:
        // Box2D body for the physics component
        b2Body* m_Body;

        // World that holds the body (used for cleanup)
        b2World* m_World;
    };

}
