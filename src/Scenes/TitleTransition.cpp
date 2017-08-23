#include "TitleTransition.h"

#include "Utility/b2Helper.hpp"
#include "SceneManager.h"
#include "ResourceManager.h"

TitleTransition::TitleTransition(sf::RenderWindow& window, const std::string& id) :
    Scene(window, id),
    mOpacityFadeIn(0),
    mOpacityFadeOut(255),
    mFadeOutAmount(5),
    mFadeInAmount(4)
{
    auto& resources = ResourceManager::instance();
    mBackground.setTexture(resources.getTexture("gfx/background.png"));
    mStart.setTexture(resources.getTexture("gfx/start_selected.png"));
    mOptions.setTexture(resources.getTexture("gfx/options.png"));
    mExit.setTexture(resources.getTexture("gfx/exit.png"));
    mTitle.setTexture(resources.getTexture("gfx/title_picture.png"));
    mPlayer.setTexture(resources.getTexture("gfx/climber_idle3.png"));

    mStart.setOrigin(mStart.getGlobalBounds().width / 2.f,
        mStart.getGlobalBounds().height / 2.f);
    mOptions.setOrigin(mOptions.getGlobalBounds().width / 2.f,
        mOptions.getGlobalBounds().height / 2.f);
    mExit.setOrigin(mExit.getGlobalBounds().width / 2.f,
        mExit.getGlobalBounds().height / 2.f);
    mTitle.setOrigin(mTitle.getGlobalBounds().width / 2.f,
        mTitle.getGlobalBounds().height / 2.f);
    mPlayer.setOrigin(mPlayer.getGlobalBounds().width / 2.f,
        mPlayer.getGlobalBounds().height / 2.f);

    mStart.setPosition(b2::WINDOW_WIDTH / 2.f, b2::WINDOW_HEIGHT / 2.f  + 100.f);
    mOptions.setPosition(b2::WINDOW_WIDTH / 2.f, b2::WINDOW_HEIGHT / 2.f  + 220.f);
    mExit.setScale(0.9f, 0.8f);
    mExit.setPosition(b2::WINDOW_WIDTH / 2.f, b2::WINDOW_HEIGHT / 2.f + 330.f);
    mTitle.setPosition(b2::WINDOW_WIDTH / 2.f, 250.f);
    mPlayer.setScale(0.91f, 0.91f);
    mPlayer.setPosition(325.f, 742.f - 1.f);
}

void TitleTransition::update()
{
    if (mFadeTime.getElapsedTime().asSeconds() < 1.0f)
        fadeOut();

    if (mFadeTime.getElapsedTime().asSeconds() >= 1.0f)
        fadeIn();

    if (mFadeTime.getElapsedTime().asSeconds() > 2.0f)
        SceneManager::instance().getScene("game")->reset();
}

void TitleTransition::draw()
{	
    mStart.setColor({255, 255, 255, mOpacityFadeOut});
    mOptions.setColor({255, 255, 255, mOpacityFadeOut});
    mExit.setColor({255, 255, 255, mOpacityFadeOut});
    mTitle.setColor({255, 255, 255, mOpacityFadeOut});
    mPlayer.setColor({255, 255, 255, mOpacityFadeIn});

    mWindow.clear();
    mWindow.draw(mBackground);
    mWindow.draw(mTitle);
    mWindow.draw(mStart);
    mWindow.draw(mOptions);
    mWindow.draw(mExit);
    mWindow.draw(mPlayer);
    mWindow.display();
}

void TitleTransition::pollEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
            SceneManager::instance().getScene("game")->reset();
    }
}

void TitleTransition::reset()
{
    SceneManager::instance().resetScene<TitleTransition>(this, mWindow, this->getKey());
}

void TitleTransition::fadeOut()
{	
    if (mFrameTime.getElapsedTime().asSeconds() > 1.f / 51.f)
    {
        if (mOpacityFadeOut < mOpacityFadeOut - mFadeOutAmount)
            return;

        mOpacityFadeOut -= mFadeOutAmount;
        mFrameTime.restart();
    }
}

void TitleTransition::fadeIn()
{	
    if (mFrameTime.getElapsedTime().asSeconds() > 1.f / 60.f)
    {
        if (mOpacityFadeOut > mOpacityFadeOut + mFadeOutAmount)
            return;

        mOpacityFadeIn += mFadeInAmount;
        mFrameTime.restart();
    }
}
