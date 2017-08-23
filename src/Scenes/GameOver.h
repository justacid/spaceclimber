#ifndef SCENE_GAME_OVER_H
#define SCENE_GAME_OVER_H

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Camera.h"

class GameOver : public Scene
{
public:
    GameOver(sf::RenderWindow& window, const std::string& id);
    void update() override;
    void draw() override;
    void pollEvents() override;
    void reset() override;
    void setScore(int score);

private:
    Camera mCamera;
    sf::Sprite mBackground;
    sf::Sprite mTitle;
    sf::Sprite mContinue;
    sf::Sprite mCross;
    sf::Text mScoreText;
};

#endif
