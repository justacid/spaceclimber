#include "MapGenerator.h"

#include "Player.h"
#include "Camera.h"
#include "PowerUps/SpeedDown.h"
#include "PowerUps/SpeedUp.h"
#include "PowerUps/TimeStop.h"
#include "PowerUps/DoubleJump.h"
#include "PowerUps/SafetyNet.h"

MapGenerator::MapGenerator(Physics& physics, Camera& cam, Player& player) :
    mPhysics(physics),
    mCamera(cam),
    mPlayer(player),
    mStartHeight(b2::WINDOW_HEIGHT - 300)
{
    srand(static_cast<unsigned int>(time(NULL)));
    addFloor({b2::WINDOW_WIDTH / 2.f, b2::WINDOW_HEIGHT - 100.f,
        b2::WINDOW_WIDTH, 30.f});
}

MapGenerator::~MapGenerator()
{
}

void MapGenerator::update()
{
    if (mUpdateTime.getElapsedTime().asSeconds() > 0.5f)
    {
        if (mPlatforms.size() < 5)
        {
            addRandomizedPlatformAt(mStartHeight);
            mStartHeight -= 275.f;
        }

        mUpdateTime.restart();
    }

    if (mPowerUpTime.getElapsedTime().asSeconds() > 10.f)
    {
        addRandomizedPowerUpAt(mStartHeight - 100.f);
        mPowerUpTime.restart();
    }
}

std::vector<Platform>& MapGenerator::getPlatforms()
{
    return mPlatforms;
}

std::vector<std::unique_ptr<PowerUp>>& MapGenerator::getPowerUps()
{
    return mPowerUps;
}

void MapGenerator::removePlatforms()
{
    using namespace std;

    mPlatforms.erase(remove_if(begin(mPlatforms), end(mPlatforms), [&](Platform& platform)
    {
        auto platformPos = b2::m2p(platform.getBody()->GetPosition().y);
        return b2::WINDOW_HEIGHT - platformPos < std::fabs(mCamera.getHeight()) + 50.f;
    }));
}

void MapGenerator::addFloor(const sf::FloatRect& rect)
{
    b2Body* body = mPhysics.createFloor(rect);
    mPlatforms.push_back(std::move(Platform(body)));
}

void MapGenerator::addRandomizedPlatformAt(float y)
{
    int random_center = std::rand() % (b2::WINDOW_WIDTH - 100) + 100;
    int random_width = std::rand() % (b2::WINDOW_WIDTH / 2 - 100) + 50;
    b2Body* body = mPhysics.createPlatform(sf::FloatRect((float)random_center, y, (float)random_width, 30.f));
    mPlatforms.push_back(std::move(Platform(body)));
}

void MapGenerator::addRandomizedPowerUpAt(float y)
{
    int randomX = std::rand() % (b2::WINDOW_WIDTH - 100) + 50;
    int diceRoll = std::rand() % 100;

    std::unique_ptr<PowerUp> powerUp;
    if (diceRoll >= 0 && diceRoll < 10)
        powerUp = std::make_unique<SpeedUp>(mCamera);
    else if (diceRoll >= 10 && diceRoll < 40)
        powerUp = std::make_unique<DoubleJump>(mPlayer);
    else if (diceRoll >= 40 && diceRoll < 60)
        powerUp = std::make_unique<TimeStop>(mCamera, mPlayer);
    else if (diceRoll >= 60 && diceRoll < 70)
        powerUp = std::make_unique<SafetyNet>(mCamera, mPlayer);
    else if (diceRoll >= 70)
        powerUp = std::make_unique<SpeedDown>(mCamera);

    powerUp->setPosition((float)randomX, y);
    mPowerUps.push_back(std::move(powerUp));
}
