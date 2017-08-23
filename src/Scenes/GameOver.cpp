#include "GameOver.h"

#include "Utility/b2Helper.hpp"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"

GameOver::GameOver(sf::RenderWindow& window, const std::string& id) :
    Scene(window, id),
    mCamera(window)
{
    auto& resources = ResourceManager::instance();
    mBackground.setTexture(resources.getTexture("gfx/background.png"));
    mTitle.setTexture(resources.getTexture("gfx/gameover_title.png"));
    mContinue.setTexture(resources.getTexture("gfx/gameover_continue.png"));
    mCross.setTexture(resources.getTexture("gfx/gameover_cross.png"));

    mTitle.setOrigin(mTitle.getGlobalBounds().width / 2.f,
        mTitle.getGlobalBounds().height / 2.f);
    mContinue.setOrigin(mContinue.getGlobalBounds().width / 2.f,
        mContinue.getGlobalBounds().height / 2.f);

    mTitle.setScale(0.9f, 0.9f);
    mTitle.setPosition(b2::WINDOW_WIDTH / 2.f, 175.f);
    mContinue.setPosition(b2::WINDOW_WIDTH / 2.f, 450.f);
    mCross.setScale(0.9f, 0.9f);
    mCross.setPosition(0.f, b2::WINDOW_HEIGHT / 2.f + 40);

    mScoreText.setFont(resources.getFont("fonts/numbers.ttf"));
    mScoreText.setFillColor(sf::Color(100, 100, 100));
    mScoreText.setCharacterSize(50);
    mScoreText.setString("0");
}

void GameOver::update()
{
}

void GameOver::draw()
{
    mCamera.setActive(true);
    mWindow.clear();
    mWindow.draw(mBackground);
    mWindow.draw(mTitle);
    mWindow.draw(mScoreText);
    mWindow.draw(mContinue);
    mWindow.draw(mCross);
    mWindow.display();
    mCamera.setActive(false);
}

void GameOver::pollEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mWindow.close();

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Escape)
            {
                auto& sceneManager = SceneManager::instance();
                sceneManager.getScene("game")->reset();
                sceneManager.getScene("title")->reset();
                sceneManager.setActive("title");
            }
        }
    }
}

void GameOver::reset()
{
    SceneManager::instance().resetScene<GameOver>(this, mWindow, this->getKey());
}

void GameOver::setScore(int score)
{
    mScoreText.setString(std::to_string(score));
    mScoreText.setOrigin(mScoreText.getGlobalBounds().width / 2.f,
        mScoreText.getGlobalBounds().height / 2.f);
    mScoreText.setPosition(b2::WINDOW_WIDTH / 2.f, 375.f);
}
