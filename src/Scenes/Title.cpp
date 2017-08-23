#include "Title.h"

#include <SFML/Audio/Listener.hpp>
#include "Utility/b2Helper.hpp"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "Options.h"

Title::Title(sf::RenderWindow& window, const std::string& id) :
    Scene(window, id),
    mCurrentSelection(0),
    mCamera(window)
{
    auto& resources = ResourceManager::instance();
    mBackground.setTexture(resources.getTexture("gfx/background.png"));
    mStart.setTexture(resources.getTexture("gfx/start_selected.png"));
    mOptions.setTexture(resources.getTexture("gfx/options.png"));
    mExit.setTexture(resources.getTexture("gfx/exit.png"));
    mTitle.setTexture(resources.getTexture("gfx/title_picture.png"));

    mStart.setOrigin(mStart.getGlobalBounds().width / 2.f,
        mStart.getGlobalBounds().height / 2.f);
    mOptions.setOrigin(mOptions.getGlobalBounds().width / 2.f,
        mOptions.getGlobalBounds().height / 2.f);
    mExit.setOrigin(mExit.getGlobalBounds().width / 2.f,
        mExit.getGlobalBounds().height / 2.f);
    mTitle.setOrigin(mTitle.getGlobalBounds().width / 2.f,
        mTitle.getGlobalBounds().height / 2.f);

    mStart.setPosition(b2::WINDOW_WIDTH / 2.f, b2::WINDOW_HEIGHT / 2.f  + 100.f);
    mOptions.setPosition(b2::WINDOW_WIDTH / 2.f, b2::WINDOW_HEIGHT / 2.f  + 220.f);
    mExit.setScale(0.9f, 0.8f);
    mExit.setPosition(b2::WINDOW_WIDTH / 2.f, b2::WINDOW_HEIGHT / 2.f + 330.f);
    mTitle.setPosition(b2::WINDOW_WIDTH / 2.f, 250.f);

    SoundManager::instance().playMusic(MusicType::MUSIC_TITLE);
}

void Title::update()
{
    if (mTimer.getElapsedTime().asSeconds() > 1.f / 30.f)
    {
        auto& resources = ResourceManager::instance();
        switch (mCurrentSelection)
        {
        case 0:
            mStart.setTexture(resources.getTexture("gfx/start_selected.png"));
            mOptions.setTexture(resources.getTexture("gfx/options.png"));
            mExit.setTexture(resources.getTexture("gfx/exit.png"));
            break;

        case 1:
            mStart.setTexture(resources.getTexture("gfx/start.png"));
            mOptions.setTexture(resources.getTexture("gfx/options_selected.png"));
            mExit.setTexture(resources.getTexture("gfx/exit.png"));
            break;

        case 2:
            mStart.setTexture(resources.getTexture("gfx/start.png"));
            mOptions.setTexture(resources.getTexture("gfx/options.png"));
            mExit.setTexture(resources.getTexture("gfx/exit_selected.png"));
            break;

        default:
            break;
        }

        mTimer.restart();
    }
}

void Title::draw()
{
    mCamera.setActive(true);
    mWindow.clear();
    mWindow.draw(mBackground);
    mWindow.draw(mTitle);
    mWindow.draw(mStart);
    mWindow.draw(mOptions);
    mWindow.draw(mExit);
    mWindow.display();
    mCamera.setActive(false);
}

void Title::pollEvents()
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
                    mWindow.close();
                    break;

                case sf::Keyboard::Space:
                case sf::Keyboard::Return:
                {
                    auto& sceneManager = SceneManager::instance();
                    if (mCurrentSelection == 0)
                        sceneManager.getScene("titleToGame")->reset();
                    else if (mCurrentSelection == 1)
                    {
                        sceneManager.getScene("options")->reset();
                        ((Options*)sceneManager.getScene("options"))->setCalledFrom(this->getKey());
                    }
                    else if (mCurrentSelection == 2)
                        mWindow.close();
                    break;
                }

                case sf::Keyboard::W:
                case sf::Keyboard::Up:
                    mCurrentSelection--;
                    if (mCurrentSelection < 0)
                        mCurrentSelection = 2;
                    break;

                case sf::Keyboard::S:
                case sf::Keyboard::Down:
                    mCurrentSelection++;
                    if (mCurrentSelection > 2)
                        mCurrentSelection = 0;
                    break;

                case sf::Keyboard::M:
                    sf::Listener::setGlobalVolume(0.f);
                    break;

                default:
                    break;
            }
        }
    }
}

void Title::reset()
{
    SceneManager::instance().resetScene<Title>(this, mWindow, this->getKey());
}
