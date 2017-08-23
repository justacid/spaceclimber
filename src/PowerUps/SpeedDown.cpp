#include "SpeedDown.h"
#include "Camera.h"
#include "SoundManager.h"

SpeedDown::SpeedDown(Camera& cam) :
    PowerUp("gfx/powerup_base.png", "gfx/powerup_base.png"),
    mCamera(cam)
{
}

void SpeedDown::activate()
{
    SoundManager::instance().playSound("sound/powerup_sound.wav");
    mCamera.changeSpeedRelative(-2.f);
}

bool SpeedDown::isPassive()
{
    return true;
}

bool SpeedDown::update()
{
    return false;
}

sf::Sprite& SpeedDown::getActiveIcon()
{
    return mGfx;
}
