#ifndef RAYCASTCALLBACK_HPP
#define RAYCASTCALLBACK_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

namespace fa {

    class RayCastCallback : public b2RayCastCallback {
    public:
        RayCastCallback(const b2Vec2& start, const b2Vec2& end);

        // Declare the ReportFixture method
        float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override;

        const b2Vec2& GetStart() const;
        const b2Vec2& GetEnd() const;
        const b2Vec2& GetHitPoint() const;
        const b2Vec2& GetHitNormal() const;
        bool HasHit() const;

    private:
        b2Vec2 m_start, m_end;
        bool m_hit;
        b2Vec2 m_hitPoint, m_hitNormal;
    };

}

#endif // RAYCASTCALLBACK_HPP
