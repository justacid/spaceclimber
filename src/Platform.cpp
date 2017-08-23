#include "Platform.h"
#include <Box2D/Box2D.h>
#include "ResourceManager.h"
#include "Utility/b2Helper.hpp"

Platform::Platform(b2Body* body) :
    mBody(body),
    mLeft(ResourceManager::instance().getTexture("gfx/left_corner.png")),
    mMiddle(ResourceManager::instance().getTexture("gfx/middle.png")),
    mRight(ResourceManager::instance().getTexture("gfx/right_corner.png"))
{
}

void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    b2Vec2 bodyPos = mBody->GetPosition();
    auto lb = mLeft.getGlobalBounds();
    auto mb = mMiddle.getGlobalBounds();
    auto rb = mRight.getGlobalBounds();
    auto dims = b2::m2p(getPolyShapeDimensions(mBody));
    int numMiddlePieces = static_cast<int>((dims.x - (lb.width + rb.width)) / mb.width);

    mLeft.setPosition(b2::m2p(bodyPos.x) - dims.x / 2.f, b2::m2p(bodyPos.y) - dims.y / 2.f);
    mRight.setPosition(b2::m2p(bodyPos.x) + dims.x / 2.f - rb.width, b2::m2p(bodyPos.y) - dims.y / 2.f);

    target.draw(mLeft, states);
    for (int i = 0; i < numMiddlePieces; ++i)
    {
        float x = (b2::m2p(bodyPos.x) - dims.x / 2.f + lb.width) + i * mb.width;
        mMiddle.setPosition({x, b2::m2p(bodyPos.y) - dims.y / 2.f});
        target.draw(mMiddle, states);
    }
    target.draw(mRight, states);
}

b2Body* Platform::getBody()
{
    return mBody;
}

sf::Vector2f Platform::getPolyShapeDimensions(b2Body* body) const
{
    b2PolygonShape* shape = (b2PolygonShape*)body->GetFixtureList()->GetShape();
    return {std::fabs(shape->m_vertices[0].x - shape->m_vertices[1].x),
        std::fabs(shape->m_vertices[0].y - shape->m_vertices[3].y)};
}
