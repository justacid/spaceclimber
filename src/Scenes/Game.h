#ifndef SCENE_GAME_H
#define SCENE_GAME_H

#include "Scene.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Physics.h"
#include "Utility/DebugDraw.h"
#include "Camera.h"
#include "FpsCounter.h"
#include "Player.h"
#include "MapGenerator.h"
#include "PowerUps/PowerUp.h"

class Game : public Scene
{
public:
    Game(sf::RenderWindow& window, const std::string& id);

    void update() override;
    void draw() override;
    void pollEvents() override;
    void reset() override;

private:
    Physics mPhysics;

    Camera mCamera;
    DebugDraw mDebugDraw;
    FpsCounter mFps;
    Player mPlayer;
    MapGenerator mMap;

    bool mShouldDrawDebug;
    float mDesiredVelocity;
    int mScore;
    bool mHasFastMusicTriggered;

    sf::Sprite mBackground;
    sf::Clock mTicks;
    sf::Text mScoreText;
    sf::Text mGracePeriodText;

    std::unique_ptr<PowerUp> mActivePowerup;
};

#endif
