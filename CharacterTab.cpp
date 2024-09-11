#include "stdafx.h"
#include "CharacterTab.h"

CharacterTab::CharacterTab(sf::VideoMode& vm, sf::Font& font, Player& player)
	: Tab(vm, font, player, false)
{
	// Background
	this->backTab.setFillColor(sf::Color(20, 20, 20, 200));

	this->backTab.setSize(
		sf::Vector2f(
			gui::p2pX(35.f, this->vm),
			static_cast<float>(this->vm.height)
		)
	);

	// Text
	this->infoText.setFont(this->font);
	this->infoText.setCharacterSize(gui::calcCharSize(this->vm, 200));
	this->infoText.setFillColor(sf::Color::White);
	this->infoText.setPosition(
		this->backTab.getPosition().x + gui::p2pX(1.f, this->vm),
		this->backTab.getPosition().y + gui::p2pY(1.f, this->vm)
	);
}

CharacterTab::~CharacterTab()
{

}

void CharacterTab::update()
{
	if (!this->hidden)
	{
		this->infoText.setString("TEST");
	}
}

void CharacterTab::render(sf::RenderTarget& target)
{
	if (!this->hidden)
	{
		target.draw(this->backTab);
		target.draw(infoText);
	}
}
