#ifndef SPEED_UP_H
#define SPEED_UP_H

#include "PowerUp.h"
#include <SFML/Audio/Sound.hpp>

class Camera;

class SpeedUp : public PowerUp
{
public:
    SpeedUp(Camera& cam);

    void activate() override;
    bool isPassive() override;
    bool update() override;
    sf::Sprite& getActiveIcon() override;

private:
    Camera& mCamera;
};

#endif
