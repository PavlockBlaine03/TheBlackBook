#pragma once

#include "Tab.h"

class InventoryTab :
    public Tab
{
private:
    sf::RectangleShape backTab;
    sf::Sprite weaponSprite;
    sf::Texture weaponTexture;

    void initWeaponSprite();

public:
    InventoryTab(sf::VideoMode& vm, sf::Font& font, Player& player);
    virtual ~InventoryTab();

    // Functions
    void update();
    void render(sf::RenderTarget& target);
};

