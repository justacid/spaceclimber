#ifndef FPS_H
#define FPS_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

class FpsCounter : public sf::Drawable
{
public:
    FpsCounter();
    void update();
    void setPosition(const sf::Vector2f& pos);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Clock mFpsClock;
    sf::Text mFpsText;
    unsigned int mFps;
};

#endif
