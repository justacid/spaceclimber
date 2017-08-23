#include "TimeStop.h"
#include "Camera.h"
#include "Player.h"
#include "SoundManager.h"

TimeStop::TimeStop(Camera& cam, Player& player) :
    PowerUp("gfx/timestop_active.png", "gfx/powerup_base.png"),
    mCamera(cam),
    mPlayer(player)
{
}

void TimeStop::activate()
{
    SoundManager::instance().playSound("sound/powerup_sound.wav");
    mVelocity = mPlayer.getVelocity();
    mPlayer.setFloating(true);
    mPlayer.setVelocity({0.f, 0.f});
    mTimer.restart();
    mCamera.pause(true);
    mIsActivated = true;
}

bool TimeStop::update()
{
    if (mIsActivated)
    {
        if (mTimer.getElapsedTime().asSeconds() < 3.0f)
            return true;

        mPlayer.setFloating(false);
        mPlayer.setVelocity(mVelocity);
        mCamera.pause(false);
        return false;
    }

    return true;
}
