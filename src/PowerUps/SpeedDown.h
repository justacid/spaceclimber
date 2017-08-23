#ifndef SPEED_DOWN_H
#define SPEED_DOWN_H

#include "PowerUp.h"
#include <SFML/Audio/Sound.hpp>

class Camera;

class SpeedDown : public PowerUp
{
public:
    SpeedDown(Camera& cam);

    void activate() override;
    bool isPassive() override;
    bool update() override;
    sf::Sprite& getActiveIcon() override;

private:
    Camera& mCamera;
};

#endif
