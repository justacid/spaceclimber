#ifndef JUMP_LISTENER_H
#define JUMP_LISTENER_H

#include <Box2D/Box2D.h>

class JumpContactListener : public b2ContactListener
{
public:
    JumpContactListener();
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    int getFootContacts() const;

private:
    int mFootContacts;
};

#endif
