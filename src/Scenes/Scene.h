#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

class SceneManager;

class Scene
{
public:
    Scene(sf::RenderWindow& window, const std::string& id);
    virtual ~Scene();
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void pollEvents() = 0;
    virtual void setActive();
    virtual void reset() = 0;
    virtual std::string getKey();

protected:
    sf::RenderWindow& mWindow;
    std::string mIdentity;
};

#endif
