#ifndef PHYSICS_H
#define PHYSICS_H

#include <memory>
#include <vector>
#include <Box2D/Box2D.h>
#include <SFML/Graphics/Rect.hpp>
#include "JumpContactListener.h"
#include "Utility/b2Helper.hpp"

class Physics
{
public:
    Physics();

    void step(float timeStep);
    b2World* getWorld();
    b2Body* createPlayer(const sf::FloatRect& rect);
    b2Body* createPlatform(const sf::FloatRect& rect);
    b2Body* createFloor(const sf::FloatRect& rect);
    bool canPlayerJump();

private:
    std::unique_ptr<b2World> mWorld;
    b2Vec2 mGravity;
    JumpContactListener mListener;

    int mVelocityIterations;
    int mPositionIterations;

    std::vector<std::unique_ptr<b2::Tag>> userData;
};

#endif
