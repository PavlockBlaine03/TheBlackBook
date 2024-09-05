#include "stdafx.h"
#include "Sword.h"

Sword::Sword()
{
	// Visual Weapon
	if (!weaponTexture.loadFromFile("C:/VisualCodeProjects/TheBlackBook/resources/images/Sprites/Player/sword.png"))
	{
		std::cerr << "ERROR::PLAYER.CPP::COULD_NOT_LOAD_WEAPON_TEXTURE";
		exit(EXIT_FAILURE);
	}
	weaponSprite.setTexture(weaponTexture);

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
}

void Sword::render(sf::RenderTarget& target, sf::Shader* shader)
{
	if (shader)
		target.draw(weaponSprite, shader);
	else
		target.draw(weaponSprite);
}
