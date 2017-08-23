#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include "Physics.h"
#include "Animation.h"

class b2Body;

class Player : public sf::Drawable
{
public:
    Player(Physics& physics);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void applyImpulse(float x, float y);
    void update();
    void setState(const std::string& playerState);

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    void setVelocity(const sf::Vector2f& velocity);
    bool isFloating() const;
    void setFloating(bool floating);

    sf::FloatRect getGlobalBounds();

private:
    Physics& mPhysics;
    b2Body* mBody;
    float mGravityScale;

    std::string mPlayerState;
    sf::Sprite mSpriteRunRight;
    sf::Sprite mSpriteRunLeft;
    sf::Sprite mSpriteIdle;
    sf::Sprite mSpriteJumpLeft;
    sf::Sprite mSpriteJumpRight;

    sf::Clock mAnimationTimer;
    Animation mAnimationRight;
    Animation mAnimationLeft;

};

#endif
