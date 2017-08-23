#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "Scene.h"
#include "Camera.h"

#include <SFML/Graphics.hpp>

class Title : public Scene
{
public:
    Title(sf::RenderWindow& window, const std::string& id);
    void update() override;
    void draw() override;
    void pollEvents() override;
    void reset() override;

private:
    sf::Sprite mBackground;
    sf::Sprite mStart;
    sf::Sprite mOptions;
    sf::Sprite mExit;
    sf::Sprite mTitle;
    sf::Clock mTimer;
    int mCurrentSelection;
    Camera mCamera;
};

#endif
