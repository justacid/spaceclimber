#include "Scene.h"
#include "SceneManager.h"

Scene::Scene(sf::RenderWindow& window, const std::string& id) :
    mWindow(window),
    mIdentity(id)
{
}

Scene::~Scene()
{
}

void Scene::setActive()
{
    SceneManager::instance().setActive(mIdentity);
}

std::string Scene::getKey()
{
    return mIdentity;
}
