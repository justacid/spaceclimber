#include "SpeedUp.h"
#include "Camera.h"
#include "SoundManager.h"

SpeedUp::SpeedUp(Camera& cam) :
    PowerUp("gfx/powerup_bad.png", "gfx/powerup_bad.png"),
    mCamera(cam)
{
}

void SpeedUp::activate()
{
    SoundManager::instance().playSound("sound/powerup_sound.wav");
    mCamera.changeSpeedRelative(2.f);
}

bool SpeedUp::isPassive()
{
    return true;
}

bool SpeedUp::update()
{
    return false;
}

sf::Sprite& SpeedUp::getActiveIcon()
{
    return mGfx;
}
