#include "JumpContactListener.h"
#include "Utility/b2Helper.hpp"

JumpContactListener::JumpContactListener() :
    mFootContacts(0)
{
}

void JumpContactListener::PreSolve(b2Contact* contact, const b2Manifold*)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    b2::Tag* fixAID = (b2::Tag*)fixtureA->GetUserData();
    b2::Tag* fixBID = (b2::Tag*)fixtureB->GetUserData();

    if (!fixAID || !fixBID)
        return;

    float playerY = 0;
    float platformY = 0;

    if ((fixAID->id.compare("ONEWAY_PLATFORM") && fixBID->id.compare("PLAYER"))
        || (fixAID->id.compare("PLAYER") && fixBID->id.compare("ONEWAY_PLATFORM")))
    {
        if (fixAID->id.compare("PLAYER"))
        {
            playerY = fixtureA->GetBody()->GetPosition().y;
            platformY = fixtureB->GetBody()->GetPosition().y;
        }
        else if (fixAID->id.compare("ONEWAY_PLATFORM"))
        {
            playerY = fixtureB->GetBody()->GetPosition().y;
            platformY = fixtureA->GetBody()->GetPosition().y;
        }

        if (playerY < platformY + b2::p2m(55.5f) + 3.f * b2_linearSlop)
            contact->SetEnabled(false);
    }
}

void JumpContactListener::BeginContact(b2Contact* contact)
{
    b2::Tag* fixtureA = (b2::Tag*)contact->GetFixtureA()->GetUserData();
    if (fixtureA != 0 && fixtureA->id.compare("FOOT_SENSOR"))
        ++mFootContacts;

    b2::Tag* fixtureB = (b2::Tag*)contact->GetFixtureB()->GetUserData();
    if (fixtureB != 0 && fixtureB->id.compare("FOOT_SENSOR"))
        ++mFootContacts;
}

void JumpContactListener::EndContact(b2Contact* contact)
{
    b2::Tag* fixtureA = (b2::Tag*)contact->GetFixtureA()->GetUserData();
    if (fixtureA != 0 && fixtureA->id.compare("FOOT_SENSOR"))
        --mFootContacts;

    b2::Tag* fixtureB = (b2::Tag*)contact->GetFixtureB()->GetUserData();
    if (fixtureB != 0 && fixtureB->id.compare("FOOT_SENSOR"))
        --mFootContacts;
}

int JumpContactListener::getFootContacts() const
{
    return mFootContacts;
}