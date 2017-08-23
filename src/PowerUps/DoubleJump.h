#ifndef DOUBLE_JUMP_H
#define DOUBLE_JUMP_H

#include "PowerUp.h"
#include <SFML/Audio/Sound.hpp>

class Player;

class DoubleJump: public PowerUp
{
public:
    DoubleJump(Player& player);
    void activate() override;
    bool update() override;

private:
    Player& mPlayer;
};

#endif