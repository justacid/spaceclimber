#include "Physics.h"

Physics::Physics() :
    mWorld(std::make_unique<b2World>(b2Vec2(0.f, 9.81f * 2.f))),
    mGravity({0.f, 9.81f}),
    mVelocityIterations(8),
    mPositionIterations(3)
{
    mWorld->SetContactListener(&mListener);
}

b2World* Physics::getWorld()
{
    return mWorld.get();
}

void Physics::step(float timeStep)
{
    mWorld->Step(timeStep, mVelocityIterations, mPositionIterations);
}

bool Physics::canPlayerJump()
{
    return mListener.getFootContacts() > 0;
}

b2Body* Physics::createPlayer(const sf::FloatRect& rect)
{
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(b2::p2m(rect.left), b2::p2m(rect.top));
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    userData.emplace_back(std::make_unique<b2::Tag>("PLAYER_BODY"));
    bodyDef.userData = userData.back().get();

    b2PolygonShape shape;
    shape.SetAsBox(b2::p2m(rect.width / 2.f), b2::p2m(rect.height / 2.f));

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.f;
    fixtureDef.shape = &shape;
    fixtureDef.friction = 0.f;
    userData.emplace_back(std::make_unique<b2::Tag>("PLAYER"));
    fixtureDef.userData = userData.back().get();

    b2Body* body = mWorld->CreateBody(&bodyDef);
    body->CreateFixture(&fixtureDef);
    shape.SetAsBox(0.5f, 0.2f, b2Vec2(0.f, 1.75f), 0.f);
    fixtureDef.isSensor = true;
    b2Fixture* footSensor = body->CreateFixture(&fixtureDef);
    userData.emplace_back(std::make_unique<b2::Tag>("FOOT_SENSOR"));
    footSensor->SetUserData(userData.back().get());

    return body;
}

b2Body* Physics::createPlatform(const sf::FloatRect& rect)
{
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(b2::p2m(rect.left), b2::p2m(rect.top));
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;

    b2PolygonShape shape;
    shape.SetAsBox(b2::p2m(rect.width / 2.f), b2::p2m(rect.height / 2.f));

    b2FixtureDef fixtureDef;
    fixtureDef.density = 50000.f;
    fixtureDef.shape = &shape;

    userData.emplace_back(std::make_unique<b2::Tag>("ONEWAY_PLATFORM"));
    fixtureDef.userData = (void*)userData.back().get();

    b2Body* body = mWorld->CreateBody(&bodyDef);
    body->CreateFixture(&fixtureDef);
    body->SetGravityScale(0.f);

    return body;
}

b2Body* Physics::createFloor(const sf::FloatRect& rect)
{
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(b2::p2m(rect.left), b2::p2m(rect.top));
    bodyDef.type = b2_staticBody;
    bodyDef.fixedRotation = true;
    b2Body* body = mWorld->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(b2::p2m(rect.width / 2.f), b2::p2m(rect.height / 2.f));

    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.f;
    fixtureDef.shape = &shape;

    body->CreateFixture(&fixtureDef);

    return body;
}
