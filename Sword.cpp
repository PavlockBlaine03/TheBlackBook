#include "stdafx.h"
#include "Sword.h"

Sword::Sword(unsigned level, unsigned damage_min, unsigned damage_max, unsigned range,
	unsigned value, std::string texture_file)
	: MeleeWeapon(level, damage_min, damage_max, range, value, texture_file)
{
	// Visual Weapon
	weaponSprite.setOrigin
	(
		weaponSprite.getGlobalBounds().width / 2.f,
		weaponSprite.getGlobalBounds().height
	);
}

Sword::~Sword()
{

}

void Sword::update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center)
{
	// update visual weapon
	weaponSprite.setPosition(center);

	float dx = mouse_pos_view.x - weaponSprite.getPosition().x;
	float dy = mouse_pos_view.y - weaponSprite.getPosition().y;

	const float PI = 3.14159265f;
	float deg = atan2(dy, dx) * 180.f / PI;

	weaponSprite.setRotation(deg + 90.f);

	if (this->attackTimer.getElapsedTime().asMilliseconds() < this->attackTimerMax)
	{
		this->weaponSprite.rotate(45.f);
	}
}

void Sword::render(sf::RenderTarget& target, sf::Shader* shader)
{
	if (shader)
		target.draw(weaponSprite, shader);
	else
		target.draw(weaponSprite);
}

Sword* Sword::clone()
{
	return new Sword(*this);
}
