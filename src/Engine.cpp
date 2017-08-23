#include "Engine.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Scenes/Title.h"
#include "Scenes/TitleTransition.h"
#include "Scenes/Game.h"
#include "Scenes/GameOver.h"
#include "Scenes/Options.h"
#include "Scenes/Pause.h"

Engine::Engine(sf::RenderWindow& window) :
    mWindow(window)
{
    window.setVerticalSyncEnabled(false);
    window.setMouseCursorVisible(false);

    auto& sceneManager = SceneManager::instance();
    sceneManager.addScene<Title>(mWindow, "title");
    sceneManager.addScene<TitleTransition>(mWindow, "titleToGame");
    sceneManager.addScene<Game>(mWindow, "game");
    sceneManager.addScene<GameOver>(mWindow, "gameOver");
    sceneManager.addScene<Options>(mWindow, "options");
    sceneManager.addScene<Pause>(mWindow, "pause");
    sceneManager.setActive("title");
}

void Engine::update()
{
    auto& sceneManager = SceneManager::instance();
    sceneManager.pollSceneEvents();
    sceneManager.updateScene();
    sceneManager.drawScene();
}
