#include "framework/RayCastCallback.h"

namespace fa {

    // Constructor to initialize start and end points
    RayCastCallback::RayCastCallback(const b2Vec2& start, const b2Vec2& end)
        : m_start(start), m_end(end), m_hit(false), m_hitNormal(0.0f, 0.0f), m_hitPoint(0.0f, 0.0f) {
    }

    // Implement the ReportFixture method
    float RayCastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) {
        m_hit = true;  // A hit occurred
        m_hitPoint = point;  // Store the hit point
        m_hitNormal = normal;  // Store the normal at the hit point
        return 1.0f;  // Continue the raycast, return value can be adjusted based on conditions
    }

    // Getters for the start and end points of the raycast
    const b2Vec2& RayCastCallback::GetStart() const {
        return m_start;
    }

    const b2Vec2& RayCastCallback::GetEnd() const {
        return m_end;
    }

    bool RayCastCallback::HasHit() const {
        return m_hit;
    }

    const b2Vec2& RayCastCallback::GetHitPoint() const {
        return m_hitPoint;
    }

    const b2Vec2& RayCastCallback::GetHitNormal() const {
        return m_hitNormal;
    }

}
