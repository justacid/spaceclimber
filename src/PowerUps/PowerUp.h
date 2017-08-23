#ifndef POWER_UP_H
#define POWER_UP_H

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class PowerUp : public sf::Drawable
{
public:

    PowerUp(const std::string& icon, const std::string& gfx) {
        mIsActivated = false;
        mIco.setTexture(ResourceManager::instance().getTexture(icon));
        mGfx.setTexture(ResourceManager::instance().getTexture(gfx));
        mIco.setPosition(10.f, 75.f);
    }

    virtual void activate() = 0;
    virtual bool update() = 0;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(mGfx, states);
    }

    virtual bool isPassive() {
        return false;
    }

    virtual sf::FloatRect getGlobalBounds() {
        return mGfx.getGlobalBounds();
    }

    virtual sf::Sprite& getActiveIcon() {
        return mIco;
    }

    virtual void setPosition(float x, float y) {
        mGfx.setPosition(x, y);
    }

protected:
    sf::Sprite mIco;
    sf::Sprite mGfx;
    bool mIsActivated;
};

#endif
