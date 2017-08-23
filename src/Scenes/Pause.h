#ifndef SCENE_PAUSE_H
#define SCENE_PAUSE_H

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Camera.h"

class Pause : public Scene
{
public:
    Pause(sf::RenderWindow& window, const std::string& id);
    void update() override;
    void draw() override;
    void pollEvents() override;
    void reset() override;

private:
    sf::Sprite mBackground;
    sf::Sprite mBack;
    sf::Sprite mOptions;
    sf::Sprite mExit;
    sf::Sprite mTitle;
    Camera mCamera;
    int mCurrentSelection;
};

#endif
