#ifndef SCENE_FADEIN_H
#define SCENE_FADEIN_H

#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <cstdint>

class TitleTransition : public Scene
{
public:
    TitleTransition(sf::RenderWindow& window, const std::string& id);
    void update() override;
    void draw() override;
    void pollEvents() override;
    void reset() override;

private:
    sf::Clock mFadeTime;
    sf::Clock mFrameTime;
    sf::Sprite mBackground;
    sf::Sprite mStart;
    sf::Sprite mOptions;
    sf::Sprite mExit;
    sf::Sprite mTitle;
    sf::Sprite mPlayer;

    uint8_t mOpacityFadeIn;
    uint8_t mOpacityFadeOut;
    uint8_t mFadeOutAmount;
    uint8_t mFadeInAmount;

    void fadeOut();
    void fadeIn();
};

#endif
