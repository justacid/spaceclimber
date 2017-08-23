#include "SceneManager.h"

SceneManager::SceneManager() :
    mActiveScene(nullptr)
{
}

void SceneManager::setActive(const std::string& id)
{
    auto it = mScenes.find(id);
    if (it != mScenes.end())
        mActiveScene = it->second.get();
}

void SceneManager::updateScene()
{
    mActiveScene->update();
}

void SceneManager::drawScene() const
{
    mActiveScene->draw();
}

void SceneManager::pollSceneEvents()
{
    mActiveScene->pollEvents();
}

Scene* SceneManager::getScene(const std::string& id)
{
    auto it = mScenes.find(id);
    return it != mScenes.end() ? it->second.get() : nullptr;
}
