#ifndef B2HELPER_H
#define B2HELPER_H

#include <Box2D/Box2D.h>
#include <string>
#include <cmath>
#include <SFML/System/Vector2.hpp>

namespace b2
{

enum Constants
{
    WINDOW_WIDTH = 650,
    WINDOW_HEIGHT = 900,
};

struct Tag
{
    std::string id;

    Tag(std::string&& id) :
        id(std::move(id)) {}
};

/**
 * Converts pixel units to meters
 */
inline float p2m(float px)
{
    return px / 30.f;
}

inline sf::Vector2f p2m(const sf::Vector2f& other)
{
    return sf::Vector2f(other.x / 30.f, other.y / 30.f);
}

/**
 * Converts meters to pixel units
 * @param m meters
 * @return pixel units
 */
inline float m2p(float m)
{
    return m * 30.f;
}

/**
 * Converts meters to pixel units
 * @param other vector to convert
 * @return vector converted to pixel units
 */
inline sf::Vector2f m2p(const sf::Vector2f& other)
{
    return sf::Vector2f(other.x * 30.f, other.y * 30.f);
}

/**
 * Convert a box2d vector into a SFML vector
 * @param vec
 * @return SFML vector
 */
inline sf::Vector2f b2sf(const b2Vec2& vec)
{
    return sf::Vector2f(vec.x, vec.y);
}

/**
 * Convert a SFML vector into a box2d vector
 * @param vec
 * @return box2d vector
 */
inline b2Vec2 sf2b(const sf::Vector2f& vec)
{
    return b2Vec2(vec.x, vec.y);
}

} // namespace b2

#endif
