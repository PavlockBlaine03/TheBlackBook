#include "stdafx.h"
#include "PlayerTabs.h"

PlayerTabs::PlayerTabs(sf::VideoMode& vm, sf::Font& font, Player& player)
	: vm(vm), font(font), player(player), characterTab(vm, font, player)
{
}

PlayerTabs::~PlayerTabs()
{

}

const bool PlayerTabs::tabsOpen()
{
	return characterTab.getOpen();
}

void PlayerTabs::toggleCharacterTab()
{
	if (this->characterTab.getHidden())
		this->characterTab.show();
	else
		this->characterTab.hide();
}

void PlayerTabs::update()
{
	
}

void PlayerTabs::render(sf::RenderTarget& target)
{
	this->characterTab.render(target);
}
