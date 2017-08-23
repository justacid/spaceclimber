#include "FpsCounter.h"
#include "ResourceManager.h"

FpsCounter::FpsCounter() :
    mFps(0)
{
    mFpsText.setFont(ResourceManager::instance().getFont("fonts/PTSans.ttf"));
    mFpsText.setString("fps: 0");
    mFpsText.setPosition({5.f, 0.f});
    mFpsText.setCharacterSize(16);
    sf::Color textColor(0, 0, 0, 255);
    mFpsText.setFillColor(textColor);
}

void FpsCounter::update()
{
    ++mFps;
    if (mFpsClock.getElapsedTime().asSeconds() > 1.0f)
    {
        mFpsText.setString("fps: " + std::to_string(mFps));
        mFps = 0;
        mFpsClock.restart();
    }
}

void FpsCounter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mFpsText, states);
}

void FpsCounter::setPosition(const sf::Vector2f& pos)
{
    mFpsText.setPosition(pos);
}
