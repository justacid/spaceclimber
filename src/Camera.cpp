#include "Camera.h"
#include "Utility/b2Helper.hpp"

Camera::Camera(sf::RenderWindow& window) :
    mWindow(window),
    mIsPaused(false),
    mInterval(10.f),
    mDistance(-1.f),
    GRACE_PERIOD(5.0f),
    MAX_DISTANCE(-8.f)
{
    mView.reset({0.f, 0.f, (float)b2::WINDOW_WIDTH, (float)b2::WINDOW_HEIGHT});
    window.setView(mView);
}

void Camera::update()
{
    if (mGraceTimer.getElapsedTime().asSeconds() < GRACE_PERIOD)
        return;

    if (mSpeedTimer.getElapsedTime().asSeconds() > mInterval)
    {
        if (mDistance > MAX_DISTANCE)
            mDistance -= 1.f;
        mSpeedTimer.restart();
    }

    if (mMoveTimer.getElapsedTime().asMilliseconds() > 15)
    {
        if (!mIsPaused)
            mView.move(0.f, mDistance);
        mWindow.setView(mView);
        mMoveTimer.restart();
    }
}

void Camera::setActive(bool active)
{
    if (active)
        mWindow.setView(mView);
    else
        mWindow.setView(mWindow.getDefaultView());
}

void Camera::changeSpeedRelative(float newSpeed)
{
    mDistance -= newSpeed;
}

void Camera::pause(bool pause)
{
    mIsPaused = pause;
}

float Camera::getHeight() const
{
    return mView.getCenter().y - mView.getSize().y / 2.f;
}

float Camera::getSpeed() const
{
    return mDistance;
}

int Camera::getRemainingGracePeriod() const
{
    return static_cast<int>(
        GRACE_PERIOD - mGraceTimer.getElapsedTime().asSeconds());
}
