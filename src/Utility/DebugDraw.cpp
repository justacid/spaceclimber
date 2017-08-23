#include "DebugDraw.h"
#include <SFML/Graphics.hpp>
#include "Utility/b2Helper.hpp"

DebugDraw::DebugDraw(sf::RenderWindow& window) :
    window(window),
    opacity(1.0f)
{
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::ConvexShape polygon;
    polygon.setPointCount(vertexCount);
    polygon.setOutlineThickness(2.5f);
    polygon.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, opacity * 255));
    polygon.setFillColor(sf::Color(0, 0, 0, 0));

    for (int i = 0; i < vertexCount; ++i)
        polygon.setPoint(i, b2::m2p(sf::Vector2f(vertices[i].x, vertices[i].y)));

    window.draw(polygon);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::ConvexShape polygon;
    polygon.setPointCount(vertexCount);
    polygon.setOutlineThickness(1.0f);
    polygon.setOutlineColor(sf::Color(0.f, 0.f, 0.f, opacity * 255.f));
    polygon.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, opacity * 255));

    for (int i = 0; i < vertexCount; ++i)
        polygon.setPoint(i, b2::m2p(sf::Vector2f(vertices[i].x, vertices[i].y)));

    window.draw(polygon);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    sf::CircleShape circle(b2::m2p(radius));
    circle.setOrigin(b2::m2p(radius), b2::m2p(radius));
    circle.setPosition(b2::m2p(center.x), b2::m2p(center.y));
    circle.setOutlineThickness(1.0f);
    circle.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, opacity * 255));
    circle.setFillColor(sf::Color(0, 0, 0, 0));
    window.draw(circle);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2&, const b2Color& color)
{
    sf::CircleShape circle(b2::m2p(radius));
    circle.setOrigin(b2::m2p(radius), b2::m2p(radius));
    circle.setPosition(b2::m2p(center.x), b2::m2p(center.y));
    circle.setOutlineThickness(1.0f);
    circle.setOutlineColor(sf::Color(0.f, 0.f, 0.f, opacity * 255.f));
    circle.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, opacity * 255));
    window.draw(circle);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    sf::RectangleShape line;
    line.setOrigin(b2::m2p((p2.x - p1.x) / 2.f), b2::m2p((p2.y - p1.y) / 2.f));
    line.setPosition(b2::m2p(p1.x), b2::m2p(p1.y));
    line.setSize(sf::Vector2f(b2::m2p(p2.x), b2::m2p(p2.y)));
    line.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, opacity * 255));
    window.draw(line);
}

void DebugDraw::DrawTransform(const b2Transform&)
{
}

void DebugDraw::SetOpacity(float percent)
{
    opacity = percent;
}
