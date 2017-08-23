#ifndef SAFETY_NET_H
#define SAFETY_NET_H

#include "PowerUp.h"
#include <SFML/Audio/Sound.hpp>

class Camera;
class Player;

class SafetyNet: public PowerUp
{
public:
    SafetyNet(Camera& cam, Player& player);
    void activate();
    bool update();

private:
    Camera& mCamera;
    Player& mPlayer;
};

#endif
