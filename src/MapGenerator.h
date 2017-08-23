#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include <vector>
#include <memory>

#include <SFML/System/Clock.hpp>
#include "PowerUps/PowerUp.h"
#include "Physics.h"
#include "Platform.h"

class Player;
class Camera;

class MapGenerator
{
public:
    MapGenerator(Physics& physics, Camera& cam, Player& player);
    ~MapGenerator();

    void update();
    void removePlatforms();
    std::vector<Platform>& getPlatforms();
    std::vector<std::unique_ptr<PowerUp>>& getPowerUps();

private:
    Physics& mPhysics;
    std::vector<Platform> mPlatforms;
    std::vector<std::unique_ptr<PowerUp>> mPowerUps;
    Camera& mCamera;
    Player& mPlayer;

    sf::Clock mUpdateTime;
    sf::Clock mPowerUpTime;
    float mStartHeight;

    void addFloor(const sf::FloatRect& rect);
    void addRandomizedPlatformAt(float y);
    void addRandomizedPowerUpAt(float y);
};

#endif