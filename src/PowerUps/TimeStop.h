#ifndef TIME_STOP_H
#define TIME_STOP_H

#include "PowerUp.h"
#include <SFML/Audio/Sound.hpp>

class Camera;
class Player;

class TimeStop : public PowerUp
{
public:
    TimeStop(Camera& cam, Player& player);

    void activate() override;
    bool update() override;

private:
    Camera& mCamera;
    Player& mPlayer;
    sf::Clock mTimer;
    sf::Vector2f mVelocity;
};

#endif
