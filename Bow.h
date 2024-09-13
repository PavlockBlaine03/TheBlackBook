#pragma once
#include "RangedWeapon.h"

class Item;
class RangedWeapon;
class Bow :
    public RangedWeapon
{
private:


public:
    Bow(const short type, unsigned level, unsigned damage_min, unsigned damage_max, unsigned range,
        unsigned value, std::string texture_file);
    virtual ~Bow();

    virtual Bow* clone();

    virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center);
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL);
};

