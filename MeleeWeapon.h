#pragma once
#include "Item.h"

class Item;
class MeleeWeapon :
    public Item
{
private:


protected:
    sf::Texture weaponTexture;
    sf::Sprite weaponSprite;

    int damageMin;
    int damageMax;

public:
    MeleeWeapon(unsigned value);
    virtual ~MeleeWeapon();

    virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL) = 0;

    virtual MeleeWeapon* clone() = 0;
};

