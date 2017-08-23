#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

class b2Body;

class Platform : public sf::Drawable
{
public:
    Platform(b2Body* body);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    b2Body* getBody();

private:
    b2Body* mBody;

    mutable sf::Sprite mLeft;
    mutable sf::Sprite mMiddle;
    mutable sf::Sprite mRight;

    sf::Vector2f getPolyShapeDimensions(b2Body* body) const;
};

#endif
