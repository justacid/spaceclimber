#include "Game.h"

#include "SceneManager.h"
#include "SoundManager.h"
#include "GameOver.h"

Game::Game(sf::RenderWindow& window, const std::string& id) :
    Scene(window, id),
    mCamera(window),
    mDebugDraw(window),
    mPlayer(mPhysics),
    mMap(mPhysics, mCamera, mPlayer),
    mShouldDrawDebug(false),
    mDesiredVelocity(0.f),
    mScore(0),
    mHasFastMusicTriggered(false),
    mActivePowerup(nullptr)
{
    auto& resources = ResourceManager::instance();

    mPhysics.getWorld()->SetDebugDraw(&mDebugDraw);
    mDebugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_aabbBit);
    mDebugDraw.SetOpacity(0.4f);
    mBackground.setTexture(resources.getTexture("gfx/background.png"));

    mScoreText.setFont(resources.getFont("fonts/numbers.ttf"));
    mScoreText.setFillColor({85, 85, 85});
    mScoreText.setPosition(15.f, 10.f);
    mScoreText.setCharacterSize(40);
    mScoreText.setString("0");

    mGracePeriodText.setFont(resources.getFont("fonts/numbers.ttf"));
    mGracePeriodText.setFillColor(sf::Color(45, 45, 45));
    mGracePeriodText.setCharacterSize(120);
    mGracePeriodText.setString("5");
    mGracePeriodText.setOrigin(mGracePeriodText.getGlobalBounds().width / 2.f,
        mGracePeriodText.getGlobalBounds().height / 2.f);
    mGracePeriodText.setPosition(b2::WINDOW_WIDTH / 2.f, b2::WINDOW_HEIGHT / 2.f);
}

void Game::update()
{
    using namespace std;

    if (mTicks.getElapsedTime().asSeconds() > 1.f / 120.f)
    {
        mPhysics.step(1 / 60.f);
        mMap.update();
        mCamera.update();
        mPlayer.update();

        auto& powerUps = mMap.getPowerUps();
        powerUps.erase(remove_if(begin(powerUps), end(powerUps), [&](auto& powerUp) {
            if (powerUp->getGlobalBounds().intersects(mPlayer.getGlobalBounds()))
            {
                if (powerUp->isPassive())
                    powerUp->activate();
                else
                    mActivePowerup = std::move(powerUp);

                return true;
            }

            return false;
        }), end(powerUps));

        if (mActivePowerup)
        {
            if (!mActivePowerup->update())
                mActivePowerup = nullptr;
        }

        if (b2::m2p(mPlayer.getPosition().y) > 0)
            mScore = (int)(861.f - std::fabs(mPlayer.getPosition().y));
        else
            mScore = (int)(std::fabs(mPlayer.getPosition().y) + 861.f);
        mScoreText.setString(std::to_string(mScore));

        // check whether player or platforms are out of screen
        for (auto it = mPhysics.getWorld()->GetBodyList(); it; it = it->GetNext())
        {
            if (b2::WINDOW_HEIGHT - b2::m2p(it->GetPosition().y) < std::fabs(mCamera.getHeight() + 50.f))
            {
                if (it->GetUserData() && ((b2::Tag*)it->GetUserData())->id == "PLAYER_BODY")
                {
                    SoundManager::instance().playMusic(MusicType::MUSIC_GAME_OVER);
                    auto& sceneManager = SceneManager::instance();
                    sceneManager.getScene("gameOver")->reset();
                    ((GameOver*)sceneManager.getScene("gameOver"))->setScore(mScore);
                    sceneManager.setActive("gameOver");
                }
                else
                {
                    mPhysics.getWorld()->DestroyBody(it);
                    mMap.removePlatforms();
                }
            }
        }

        if (mCamera.getSpeed() < -6.0f && !mHasFastMusicTriggered)
        {
            SoundManager::instance().playMusic(MusicType::MUSIC_GAME_FAST);
            mHasFastMusicTriggered = true;
        }

        if (mPlayer.isFloating())
            mPlayer.setVelocity({mPlayer.getVelocity().x, 0.f});

        mTicks.restart();
    }
}

void Game::draw()
{
    mFps.update();

    mWindow.clear();

    mCamera.setActive(false);
    mWindow.draw(mBackground);
    mCamera.setActive(true);

    for (auto& platform : mMap.getPlatforms())
        mWindow.draw(platform);

    for (auto& powerup : mMap.getPowerUps())
        mWindow.draw(*powerup.get());

    mCamera.setActive(false);
    mWindow.draw(mScoreText);

    if (mActivePowerup)
        mWindow.draw(mActivePowerup->getActiveIcon());

    mCamera.setActive(true);
    mWindow.draw(mPlayer);

    if (mCamera.getRemainingGracePeriod() > 0)
    {
        mGracePeriodText.setString(std::to_string(mCamera.getRemainingGracePeriod()));
        mWindow.draw(mGracePeriodText);
    }

    if (mShouldDrawDebug)
    {
        mPhysics.getWorld()->DrawDebugData();
        mCamera.setActive(false);
        mWindow.draw(mFps);
        mCamera.setActive(true);
    }

    mWindow.display();
}

void Game::pollEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mWindow.close();

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                if (mHasFastMusicTriggered)
                    SceneManager::instance().getScene("title")->reset();
                SceneManager::instance().setActive("pause");
                break;

            case sf::Keyboard::D:
                mShouldDrawDebug = !mShouldDrawDebug;
                break;

            case sf::Keyboard::Space:
                if (mPhysics.canPlayerJump())
                {
                    SoundManager::instance().playSound("sound/jump_sound.wav");
                    if (!mPlayer.isFloating())
                        mPlayer.applyImpulse(0.f, 15.f * 1.5f);
                }
                break;

            case sf::Keyboard::Left:
                mPlayer.setState(!mPhysics.canPlayerJump() ? "jump_left" : "running_left");
                mPlayer.setVelocity({-300.f, mPlayer.getVelocity().y});
                break;

            case sf::Keyboard::Right:
                mPlayer.setState(!mPhysics.canPlayerJump() ? "jump_right" : "running_right");
                mPlayer.setVelocity({300.f, mPlayer.getVelocity().y});
                break;

            default:
                break;
            }
        }

        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Left:
            case sf::Keyboard::Right:
                mPlayer.setState("idle");
                mPlayer.setVelocity({0.f, mPlayer.getVelocity().y});
                break;

            case sf::Keyboard::LControl:
                if (mActivePowerup != nullptr)
                    mActivePowerup->activate();
                break;

            case sf::Keyboard::M:
                sf::Listener::setGlobalVolume(0.f);
                break;

            default:
                break;
            }
        }

        if (event.type == sf::Event::LostFocus)
        {
            if (mHasFastMusicTriggered)
                SceneManager::instance().getScene("title")->reset();
            SceneManager::instance().setActive("pause");
        }
    }
}

void Game::reset()
{
    SceneManager::instance().resetScene<Game>(this, mWindow, this->getKey());
}
