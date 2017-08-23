#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/View.hpp>

class Camera
{
public:
    Camera(sf::RenderWindow& window);

    void update();
    void pause(bool pause);
    void setActive(bool active);
    void changeSpeedRelative(float newSpeed);

    float getHeight() const;
    float getSpeed() const;
    int getRemainingGracePeriod() const;

private:
    sf::RenderWindow& mWindow;
    sf::View mView;

    sf::Clock mMoveTimer;
    sf::Clock mSpeedTimer;
    sf::Clock mGraceTimer;

    bool mIsPaused;
    float mInterval;
    float mDistance;

    const float GRACE_PERIOD;
    const float MAX_DISTANCE;
};

#endif
