#pragma once

#include "Item.h"


class Weapon :
    public Item
{
private:
    void initVariables();
    void initCoolDown();

protected:
    sf::Texture weaponTexture;
    sf::Sprite weaponSprite;

    unsigned damageMin;
    unsigned damageMax;
    unsigned range;

    float cooldown;
    float cooldownMax;
    float cooldownIteration;

public:
    Weapon(unsigned value, std::string texture_file);
    virtual ~Weapon();

    // Accessors
    const unsigned& getDamageMin() const;
    const unsigned& getDamageMax() const;
    const unsigned& getRange() const;

    // Function


    virtual Weapon* clone() = 0;
    virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL) = 0;
};

