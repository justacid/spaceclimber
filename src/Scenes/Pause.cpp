#include "Pause.h"

#include "Utility/b2Helper.hpp"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Options.h"

Pause::Pause(sf::RenderWindow& window, const std::string& id) :
    Scene(window, id),
    mCamera(window),
    mCurrentSelection(0)
{
    auto& resources = ResourceManager::instance();
    mBackground.setTexture(resources.getTexture("gfx/background.png"));
    mBack.setTexture(resources.getTexture("gfx/back.png"));
    mOptions.setTexture(resources.getTexture("gfx/options.png"));
    mExit.setTexture(resources.getTexture("gfx/exit.png"));
    mTitle.setTexture(resources.getTexture("gfx/pause_title.png"));

    mBack.setOrigin(mBack.getGlobalBounds().width / 2.f,
        mBack.getGlobalBounds().height / 2.f);
    mOptions.setOrigin(mOptions.getGlobalBounds().width / 2.f,
        mOptions.getGlobalBounds().height / 2.f);
    mExit.setOrigin(mExit.getGlobalBounds().width / 2.f,
        mExit.getGlobalBounds().height / 2.f);
    mTitle.setOrigin(mTitle.getGlobalBounds().width / 2.f,
        mTitle.getGlobalBounds().height / 2.f);

    mTitle.setPosition(b2::WINDOW_WIDTH / 2.f, 300.f);
    mBack.setPosition(b2::WINDOW_WIDTH / 2.f, b2::WINDOW_HEIGHT / 2.f  + 100.f);
    mOptions.setPosition(b2::WINDOW_WIDTH / 2.f, b2::WINDOW_HEIGHT / 2.f  + 220.f);
    mExit.setScale(0.9f, 0.8f);
    mExit.setPosition(b2::WINDOW_WIDTH / 2.f, b2::WINDOW_HEIGHT / 2.f + 330.f);
}

void Pause::update()
{
    auto& resources = ResourceManager::instance();
    switch (mCurrentSelection)
    {
    case 0:
        mBack.setTexture(resources.getTexture("gfx/back_selected.png"));
        mOptions.setTexture(resources.getTexture("gfx/options.png"));
        mExit.setTexture(resources.getTexture("gfx/exit.png"));
        break;

    case 1:
        mBack.setTexture(resources.getTexture("gfx/back.png"));
        mOptions.setTexture(resources.getTexture("gfx/options_selected.png"));
        mExit.setTexture(resources.getTexture("gfx/exit.png"));
        break;

    case 2:
        mBack.setTexture(resources.getTexture("gfx/back.png"));
        mOptions.setTexture(resources.getTexture("gfx/options.png"));
        mExit.setTexture(resources.getTexture("gfx/exit_selected.png"));
        break;

    default:
        break;
    }
}

void Pause::draw()
{
    mCamera.setActive(true);
    mWindow.clear();
    mWindow.draw(mBackground);
    mWindow.draw(mTitle);
    mWindow.draw(mBack);
    mWindow.draw(mOptions);
    mWindow.draw(mExit);
    mWindow.display();
    mCamera.setActive(false);
}

void Pause::pollEvents()
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
            {
                auto& sceneManager = SceneManager::instance();
                if (mCurrentSelection == 0)
                    sceneManager.setActive("game");
                else if (mCurrentSelection == 1)
                {
                    sceneManager.getScene("options")->reset();
                    ((Options*)sceneManager.getScene("options"))->setCalledFrom(this->getKey());
                    sceneManager.setActive("options");
                }
                else if (mCurrentSelection == 2)
                    sceneManager.setActive("title");
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

            default:
                break;
            }
        }
    }
}

void Pause::reset()
{
    SceneManager::instance().resetScene<Pause>(this, mWindow, this->getKey());
}
