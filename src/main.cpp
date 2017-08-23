#include <SFML/Graphics.hpp>
#include "Utility/b2Helper.hpp"
#include <physfs.h>
#include "Engine.h"
#include "ResourceManager.h"

int main(int, char** argv)
{
    PHYSFS_init(argv[0]);

    sf::RenderWindow window({b2::WINDOW_WIDTH, b2::WINDOW_HEIGHT}, "Space Climber");
    auto icon = ResourceManager::instance().getImage("gfx/icon_small.png");
    window.setIcon(32, 32, icon.getPixelsPtr());

    Engine game(window);
    while (window.isOpen())
        game.update();

    PHYSFS_deinit();
    return 0;
}
