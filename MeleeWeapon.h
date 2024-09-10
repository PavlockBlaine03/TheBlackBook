#pragma once
#include "Weapon.h"

class MeleeWeapon :
    public Weapon
{
private:


protected:
    

public:
    MeleeWeapon(unsigned damage_min, unsigned damage_max, unsigned range, 
        unsigned value, std::string texture_file);
    virtual ~MeleeWeapon();

    virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL) = 0;

    virtual MeleeWeapon* clone() = 0;
};

