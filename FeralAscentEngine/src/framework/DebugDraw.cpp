#include "framework/DebugDraw.h"
#include <iostream>

DebugDraw::DebugDraw(sf::RenderWindow& window)
    : m_window(window) {
    // Set the flags for drawing
    SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit);  // Adjust flags as needed
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    std::cout << "DrawPolygon called with " << vertexCount << " vertices." << std::endl;

    sf::ConvexShape shape;
    shape.setPointCount(vertexCount);

    for (int i = 0; i < vertexCount; ++i) {
        shape.setPoint(i, sf::Vector2f(vertices[i].x * SCALE, vertices[i].y * SCALE));
    }

    shape.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, 100));
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1.0f);
    m_window.draw(shape);
}


void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    sf::ConvexShape shape;
    shape.setPointCount(vertexCount);

    for (int i = 0; i < vertexCount; ++i) {
        shape.setPoint(i, sf::Vector2f(vertices[i].x * SCALE, vertices[i].y * SCALE));
    }

    shape.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, 255)); // Solid color
    m_window.draw(shape);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {
    sf::CircleShape shape(radius * SCALE);
    shape.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, 100)); // Semi-transparent color
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1.0f);
    shape.setPosition(center.x * SCALE - radius * SCALE, center.y * SCALE - radius * SCALE);
    m_window.draw(shape);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {
    sf::CircleShape shape(radius * SCALE);
    shape.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, 255)); // Solid color
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1.0f);
    shape.setPosition(center.x * SCALE - radius * SCALE, center.y * SCALE - radius * SCALE);
    m_window.draw(shape);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(p1.x * SCALE, p1.y * SCALE), sf::Color(color.r * 255, color.g * 255, color.b * 255)),
        sf::Vertex(sf::Vector2f(p2.x * SCALE, p2.y * SCALE), sf::Color(color.r * 255, color.g * 255, color.b * 255))
    };
    m_window.draw(line, 2, sf::Lines);
}

void DebugDraw::DrawTransform(const b2Transform& xf) {
    b2Vec2 p1 = xf.p;
    b2Vec2 p2 = p1 + b2Vec2(1.0f, 0.0f); // X-axis
    b2Vec2 p3 = p1 + b2Vec2(0.0f, 1.0f); // Y-axis
    DrawSegment(p1, p2, b2Color(1.0f, 0.0f, 0.0f)); // Red
    DrawSegment(p1, p3, b2Color(0.0f, 1.0f, 0.0f)); // Green
}

void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color) {
    sf::CircleShape point(size * SCALE);
    point.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255));
    point.setPosition(p.x * SCALE - size * SCALE, p.y * SCALE - size * SCALE);
    m_window.draw(point);
}
