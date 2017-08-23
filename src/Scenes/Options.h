#ifndef SCENE_OPTIONS_H
#define SCENE_OPTIONS_H

#include "Scene.h"
#include "Camera.h"

#include <SFML/Graphics.hpp>

class Options : public Scene
{
public:
    Options(sf::RenderWindow& window, const std::string& id);
    void update() override;
    void draw() override;
    void pollEvents() override;
    void reset() override;
    void setCalledFrom(std::string id);

private:
    sf::Sprite mBackground;
    sf::Sprite mTitle;
    sf::Sprite mVolumeSelection;
    sf::Sprite mBack;
    sf::Sprite mVolume;
    sf::Text mVolumeText;
    sf::Clock mTimer;
    Camera mCamera;
    float mGlobalVolume;
    int mCurrentSelection;
    std::string mNextActive;
};

#endif
