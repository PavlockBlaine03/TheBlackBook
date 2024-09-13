#pragma once

#include "Item.h"

enum WeaponType {WEAPON_SWORD = 1, WEAPON_BOW};

class Weapon :
    public Item
{
private:
    void initVariables();

protected:
    sf::Texture weaponTexture;
    sf::Sprite weaponSprite;

    unsigned damageMin;
    unsigned damageMax;
    unsigned range;

    short weaponType;

    sf::Clock attackTimer;
    sf::Int32 attackTimerMax;

public:
    Weapon(unsigned level, unsigned value, std::string texture_file);

    Weapon(const short type, unsigned level, unsigned damage_min, unsigned damage_max, unsigned range,
        unsigned value, std::string texture_file);

    virtual ~Weapon();

    // Accessors
    const short getWeaponType() const;
    const unsigned& getDamageMin() const;
    const unsigned& getDamageMax() const;
    const unsigned getDamage() const;
    const unsigned& getRange() const;
    const bool getAttackTimer();
    const sf::Sprite& getSprite() const;

    // Function
    virtual Weapon* clone() = 0;

    virtual void generate(const unsigned levelMax, const unsigned levelMin) = 0;
    virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL) = 0;
};

