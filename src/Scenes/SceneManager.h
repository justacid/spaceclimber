#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <unordered_map>
#include <memory>
#include "Scene.h"

class SceneManager
{
public:

    static SceneManager& instance()
    {
        static SceneManager instance;
        return instance;
    }

    SceneManager(const SceneManager&) = delete;
    void operator=(const SceneManager&) = delete;

    template <typename T, typename ...Args>
    void addScene(Args&&...args)
    {
        auto newScene = std::make_unique<T>(std::forward<Args>(args)...);
        if (mScenes.find(newScene->getKey()) != mScenes.end())
            return;

        mScenes.insert(std::make_pair(newScene->getKey(), std::move(newScene)));
    }

    template <typename T, typename ...Args>
    void resetScene(Scene* scene, Args&&... args)
    {
        auto id = scene->getKey();
        auto it = mScenes.find(id);

        if (it != mScenes.end())
        {
            mScenes.erase(it);
            mScenes[id] = std::make_unique<T>(std::forward<Args>(args)...);
            setActive(id);
        }
    }

    void setActive(const std::string& id);
    void updateScene();
    void drawScene() const;
    void pollSceneEvents();
    Scene* getScene(const std::string& id);

private:
    SceneManager();

    std::unordered_map<std::string, std::unique_ptr<Scene>> mScenes;
    Scene* mActiveScene;
};

#endif
