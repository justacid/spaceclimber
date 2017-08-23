#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include "Scenes/SceneManager.h"

class Engine
{
public:
    Engine(sf::RenderWindow& window);
    void update();

private:
    sf::RenderWindow& mWindow;
};

#endif
