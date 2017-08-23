#include "SafetyNet.h"
#include "Camera.h"
#include "Player.h"
#include "SoundManager.h"

SafetyNet::SafetyNet(Camera& cam, Player& player) :
    PowerUp("gfx/safetynet_active.png", "gfx/powerup_base.png"),
    mCamera(cam),
    mPlayer(player)
{
}

void SafetyNet::activate()
{
}

bool SafetyNet::update()
{
    if (b2::WINDOW_HEIGHT - mPlayer.getPosition().y < std::fabs(mCamera.getHeight()) - 20.f)
    {
        mPlayer.setVelocity(sf::Vector2f(mPlayer.getVelocity().x, 0.f));
        mPlayer.applyImpulse(0.f, 15.f * 2.5f);
        SoundManager::instance().playSound("sound/powerup_sound.wav");
        return false;
    }

    return true;
}
