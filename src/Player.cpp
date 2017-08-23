#include "Player.h"

#include "ResourceManager.h"

Player::Player(Physics& physics) :
    mPhysics(physics),
    mPlayerState("idle")
{
    mBody = mPhysics.createPlayer({325.f, 742.f, 56.f, 95.f});
    mGravityScale = mBody->GetGravityScale();

    auto& resources = ResourceManager::instance();
    mSpriteIdle.setTexture(resources.getTexture("gfx/climber_idle3.png"));
    mSpriteJumpLeft.setTexture(resources.getTexture("gfx/jump_left3.png"));
    mSpriteJumpRight.setTexture(resources.getTexture("gfx/jump_right3.png"));
    mAnimationRight.setTexture(resources.getTexture("gfx/player_running_right3.png"));
    mAnimationLeft.setTexture(resources.getTexture("gfx/player_running_left3.png"));

    mAnimationRight.addFrame({0, 0, 56, 100}, 0.08f);
    mAnimationRight.addFrame({56, 0, 56, 100}, 0.08f);
    mAnimationRight.addFrame({0, 100, 56, 100}, 0.08f);
    mAnimationRight.addFrame({56, 100, 56, 100}, 0.08f);
    mAnimationRight.addFrame({0, 200, 56, 100}, 0.08f);
    mAnimationRight.addFrame({56, 200, 56, 100}, 0.08f);
    mAnimationRight.addFrame({0, 300, 56, 100}, 0.08f);
    mAnimationRight.addFrame({56, 300, 56, 100}, 0.08f);
    mAnimationRight.addFrame({0, 400, 56, 100}, 0.08f);
    mAnimationRight.addFrame({56, 400, 56, 100}, 0.08f);

    mAnimationLeft.addFrame({0, 0, 56, 100}, 0.08f);
    mAnimationLeft.addFrame({56, 0, 56, 100}, 0.08f);
    mAnimationLeft.addFrame({0, 100, 56, 100}, 0.08f);
    mAnimationLeft.addFrame({56, 100, 56, 100}, 0.08f);
    mAnimationLeft.addFrame({0, 200, 56, 100}, 0.08f);
    mAnimationLeft.addFrame({56, 200, 56, 100}, 0.08f);
    mAnimationLeft.addFrame({0, 300, 56, 100}, 0.08f);
    mAnimationLeft.addFrame({56, 300, 56, 100}, 0.08f);
    mAnimationLeft.addFrame({0, 400, 56, 100}, 0.08f);
    mAnimationLeft.addFrame({56, 400, 56, 100}, 0.08f);

    mAnimationRight.apply(mSpriteRunRight);
    mAnimationRight.setLoop(true);
    mAnimationRight.play();
    mSpriteRunRight.setOrigin(mSpriteRunRight.getGlobalBounds().width / 2.f,
        mSpriteRunRight.getGlobalBounds().height / 2.f);

    mAnimationLeft.apply(mSpriteRunLeft);
    mAnimationLeft.setLoop(true);
    mAnimationLeft.play();
    mSpriteRunLeft.setOrigin(mSpriteRunLeft.getGlobalBounds().width / 2.f,
        mSpriteRunLeft.getGlobalBounds().height / 2.f);

    mSpriteIdle.setOrigin(mSpriteIdle.getGlobalBounds().width / 2.f,
        mSpriteIdle.getGlobalBounds().height / 2.f);
    mSpriteIdle.setScale(0.91f, 0.91f);
    mSpriteJumpLeft.setOrigin(mSpriteJumpLeft.getGlobalBounds().width / 2.f,
        mSpriteJumpLeft.getGlobalBounds().height / 2.f);
    mSpriteJumpRight.setOrigin(mSpriteJumpRight.getGlobalBounds().width / 2.f,
        mSpriteJumpRight.getGlobalBounds().height / 2.f);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mPlayerState == "idle")
        target.draw(mSpriteIdle, states);
    else if (mPlayerState == "running_left")
        target.draw(mSpriteRunLeft, states);
    else if (mPlayerState == "running_right")
        target.draw(mSpriteRunRight, states);
    else if (mPlayerState == "jump_left")
        target.draw(mSpriteJumpLeft, states);
    else if (mPlayerState == "jump_right")
        target.draw(mSpriteJumpRight, states);
}

void Player::applyImpulse(float x, float y)
{
    mBody->ApplyLinearImpulse({x * mBody->GetMass(), -y * mBody->GetMass()},
        mBody->GetWorldCenter(), true);
}

void Player::update()
{
    mSpriteIdle.setPosition(b2::m2p(b2::b2sf(mBody->GetPosition())) +
        sf::Vector2f(0.f, 4.f));
    mSpriteJumpLeft.setPosition(b2::m2p(b2::b2sf(mBody->GetPosition())));
    mSpriteJumpRight.setPosition(b2::m2p(b2::b2sf(mBody->GetPosition())));
    mAnimationRight.update(mAnimationTimer.getElapsedTime().asSeconds());
    mAnimationLeft.update(mAnimationTimer.getElapsedTime().asSeconds());
    mSpriteRunRight.setPosition(b2::m2p(b2::b2sf(mBody->GetPosition())) +
        sf::Vector2f(0.f, 4.f));
    mSpriteRunLeft.setPosition(b2::m2p(b2::b2sf(mBody->GetPosition())) +
        sf::Vector2f(0.f, 4.f));
}

void Player::setState(const std::string& playerState)
{
    mPlayerState = playerState;
}

sf::FloatRect Player::getGlobalBounds()
{
    return mSpriteIdle.getGlobalBounds();
}

sf::Vector2f Player::getPosition() const
{
    return b2::m2p(b2::b2sf(mBody->GetPosition()));
}

sf::Vector2f Player::getVelocity() const
{
    return b2::m2p(b2::b2sf(mBody->GetLinearVelocity()));
}

void Player::setVelocity(const sf::Vector2f& velocity)
{
    mBody->SetLinearVelocity(b2::sf2b(b2::p2m(velocity)));
}

bool Player::isFloating() const
{
    return mBody->GetGravityScale() == 0.f;
}

void Player::setFloating(bool floating)
{
    mBody->SetGravityScale(floating ? 0.f : mGravityScale);
}
