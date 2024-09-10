#include "stdafx.h"
#include "Bow.h"

Bow::Bow(unsigned damage_min, unsigned damage_max, unsigned range, 
    unsigned value, std::string texture_file)
    : RangedWeapon(damage_min, damage_max, range, value, texture_file)
{
	// Visual Weapon
	weaponSprite.setOrigin
	(
		weaponSprite.getGlobalBounds().width / 2.f + 10.f,
		weaponSprite.getGlobalBounds().height / 2.f
	);
}

Bow::~Bow()
{

}

Bow* Bow::clone()
{
    return new Bow(*this);
}

void Bow::update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center)
{
	// update visual weapon
	weaponSprite.setPosition(center);

	float dx = mouse_pos_view.x - weaponSprite.getPosition().x;
	float dy = mouse_pos_view.y - weaponSprite.getPosition().y;

	const float PI = 3.14159265f;
	float deg = atan2(dy, dx) * 180.f / PI;

	weaponSprite.setRotation(deg + 180.f);
}

void Bow::render(sf::RenderTarget& target, sf::Shader* shader)
{
	if (shader)
		target.draw(weaponSprite, shader);
	else
		target.draw(weaponSprite);
}
