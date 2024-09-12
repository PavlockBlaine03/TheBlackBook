#include "stdafx.h"
#include "CharacterTab.h"

void CharacterTab::initText()
{
	// Text
	this->infoText.setFont(this->font);
	this->infoText.setCharacterSize(gui::calcCharSize(this->vm, 150));
	this->infoText.setFillColor(sf::Color(200, 200, 200, 255));
	this->infoText.setPosition(
		this->backTab.getPosition().x + gui::p2pX(1.f, this->vm),
		this->backTab.getPosition().y + gui::p2pY(1.f, this->vm)
	);

	this->infoText.setString(this->player.toStringCharacterTab());
}

CharacterTab::CharacterTab(sf::VideoMode& vm, sf::Font& font, Player& player)
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

	initText();
}

CharacterTab::~CharacterTab()
{

}

void CharacterTab::update()
{
	if (!this->hidden)
	{
		this->infoText.setString(this->player.toStringCharacterTab());
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
