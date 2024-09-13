#pragma once
#include "Weapon.h"

class RangedWeapon :
    public Weapon
{
private:


protected:


public:
    RangedWeapon(const short type, unsigned level, unsigned damage_min, unsigned damage_max, unsigned range,
        unsigned value, std::string texture_file);
    virtual ~RangedWeapon();


    virtual void generate(const unsigned levelMax, const unsigned levelMin);
    virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL) = 0;

    virtual RangedWeapon* clone() = 0;
};

