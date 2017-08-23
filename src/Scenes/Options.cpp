#include "Options.h"

#include <SFML/Audio/Listener.hpp>
#include "Utility/b2Helper.hpp"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "SceneManager.h"

Options::Options(sf::RenderWindow& window, const std::string& id) :
    Scene(window, id),
    mCamera(window),
    mCurrentSelection(0),
    mNextActive("title")
{
    auto& resources = ResourceManager::instance();

    mBackground.setTexture(resources.getTexture("gfx/background.png"));
    mTitle.setTexture(resources.getTexture("gfx/options_title.png"));
    mBack.setTexture(resources.getTexture("gfx/back_selected.png"));
    mVolumeSelection.setTexture(resources.getTexture("gfx/volume_selected.png"));
    mVolume.setTexture(resources.getTexture("gfx/options_volume.png"));

    mTitle.setOrigin(mTitle.getGlobalBounds().width / 2.f,
        mTitle.getGlobalBounds().height / 2.f);
    mBack.setOrigin(mBack.getGlobalBounds().width / 2.f,
        mBack.getGlobalBounds().height / 2.f);
    mVolumeSelection.setOrigin(mVolumeSelection.getGlobalBounds().width / 2.f,
        mVolumeSelection.getGlobalBounds().height / 2.f);
    mVolume.setOrigin(mVolume.getGlobalBounds().width / 2.f,
        mVolume.getGlobalBounds().height / 2.f);

    mTitle.setPosition(b2::WINDOW_WIDTH / 2.f, 150.f);
    mBack.setPosition(b2::WINDOW_WIDTH / 2.f, b2::WINDOW_HEIGHT - 124.f);
    mVolumeSelection.setPosition(b2::WINDOW_WIDTH / 2.f, 500.f);
    mVolume.setPosition(b2::WINDOW_WIDTH / 2.f, 400.f);

    mVolumeText.setFont(resources.getFont("fonts/numbers.ttf"));
    mVolumeText.setFillColor(sf::Color(100, 100, 100));
    mVolumeText.setCharacterSize(50);
    mVolumeText.setString("20");

    mGlobalVolume = sf::Listener::getGlobalVolume();
    mVolumeText.setString("20");
    mVolumeText.setOrigin(mVolumeText.getGlobalBounds().width / 2.f,
        mVolumeText.getGlobalBounds().height / 2.f);
    mVolumeText.setPosition(b2::WINDOW_WIDTH / 2.f, 485.f);
}

void Options::update()
{
    if (mTimer.getElapsedTime().asMilliseconds() > 16)
    {
        mVolumeText.setString(std::to_string(static_cast<int>(mGlobalVolume)));
        mVolumeText.setOrigin(mVolumeText.getGlobalBounds().width / 2.f,
            mVolumeText.getGlobalBounds().height / 2.f);
        mVolumeText.setPosition(b2::WINDOW_WIDTH / 2.f, 485.f);

        auto& resources = ResourceManager::instance();
        if (mCurrentSelection == 0)
            mBack.setTexture(resources.getTexture("gfx/back_selected.png"));
        else if (mCurrentSelection == 1)
            mBack.setTexture(resources.getTexture("gfx/back.png"));
    }
}

void Options::draw()
{
    mCamera.setActive(true);
    mWindow.clear();
    mWindow.draw(mBackground);
    mWindow.draw(mTitle);
    mWindow.draw(mBack);
    mWindow.draw(mVolume);

    if (mCurrentSelection == 1)
        mWindow.draw(mVolumeSelection);

    mWindow.draw(mVolumeText);
    mWindow.display();
    mCamera.setActive(false);
}

void Options::pollEvents()
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
            case sf::Keyboard::Return:
                if (mCurrentSelection == 0)
                    SceneManager::instance().setActive(mNextActive);
                break;

            case sf::Keyboard::W:
            case sf::Keyboard::Up:
                mCurrentSelection--;
                if (mCurrentSelection < 0)
                    mCurrentSelection = 1;
                break;

            case sf::Keyboard::A:
            case sf::Keyboard::Left:
                mGlobalVolume -= 1.f;
                if (mGlobalVolume < 0.f)
                    mGlobalVolume = 0.f;
                sf::Listener::setGlobalVolume(mGlobalVolume);
                break;

            case sf::Keyboard::S:
            case sf::Keyboard::Down:
                mCurrentSelection++;
                if (mCurrentSelection > 1)
                    mCurrentSelection = 0;
                break;

            case sf::Keyboard::D:
            case sf::Keyboard::Right:
                mGlobalVolume += 1.f;
                if (mGlobalVolume > 100.f)
                    mGlobalVolume = 100.f;
                sf::Listener::setGlobalVolume(mGlobalVolume);
                break;

            default:
                break;
            }
        }
    }
}

void Options::setCalledFrom(std::string id)
{
    mNextActive = id;
}

void Options::reset()
{
    SceneManager::instance().resetScene<Options>(this, mWindow, this->getKey());
}
