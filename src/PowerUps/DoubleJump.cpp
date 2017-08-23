#include "DoubleJump.h"
#include "Player.h"
#include "SoundManager.h"

DoubleJump::DoubleJump(Player& player) :
    PowerUp("gfx/airjump_active.png", "gfx/powerup_base.png"),
    mPlayer(player)
{
}

void DoubleJump::activate()
{
    SoundManager::instance().playSound("sound/powerup_sound.wav");
    mPlayer.setVelocity({mPlayer.getVelocity().x, 0.f});
    mPlayer.applyImpulse(0.f, 15.f * 1.5f);
    mIsActivated = true;
}

bool DoubleJump::update()
{
    return !mIsActivated;
}
