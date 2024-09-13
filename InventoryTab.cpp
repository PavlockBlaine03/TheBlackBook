#include "stdafx.h"
#include "InventoryTab.h"

void InventoryTab::initWeaponSprite()
{
	this->weaponTexture.loadFromFile("C:/VisualCodeProjects/TheBlackBook/resources/images/Sprites/Player/sword.png");
	this->weaponSprite.setTexture(weaponTexture);
	this->weaponSprite.setPosition(this->backTab.getPosition().x + gui::p2pX(7, vm), this->backTab.getPosition().y + gui::p2pY(5, vm));
	this->weaponSprite.setScale(sf::Vector2f(2.f, 2.f));
}

InventoryTab::InventoryTab(sf::VideoMode& vm, sf::Font& font, Player& player)
	: Tab(vm, font, player, true)
{

	// Background
	this->backTab.setFillColor(sf::Color(20, 20, 20, 225));

	this->backTab.setSize(
		sf::Vector2f(
			gui::p2pX(35.f, this->vm),
			static_cast<float>(this->vm.height)
		)
	);
	this->backTab.setPosition(this->vm.width - this->backTab.getSize().x, 0);
	this->initWeaponSprite();
}

InventoryTab::~InventoryTab()
{

}

void InventoryTab::update()
{
	
}

void InventoryTab::render(sf::RenderTarget& target)
{
	if (!this->hidden)
	{
		target.draw(this->backTab);
		target.draw(this->weaponSprite);
	}
}
