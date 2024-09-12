#include "stdafx.h"
#include "PlayerGUITabs.h"

void PlayerGUITabs::initTabs()
{
	this->tabs.push_back(new CharacterTab(vm, font, player));
}

PlayerGUITabs::PlayerGUITabs(sf::VideoMode& vm, sf::Font& font, Player& player)
	: vm(vm), font(font), player(player)
{
	this->initTabs();
}

PlayerGUITabs::~PlayerGUITabs()
{

}

const bool PlayerGUITabs::tabsOpen()
{
	// Loop through tabs
	bool open = false;
	for (int i = 0; i < tabs.size() && !open; i++)
	{
		if (this->tabs[i]->getOpen())
			open = true;
	}
	return open;
}

void PlayerGUITabs::toggleTab(const int tab_index)
{
	if (tab_index >= 0 || tab_index < this->tabs.size())
		this->tabs[tab_index]->toggle();
}

void PlayerGUITabs::update()
{
	for (int i = 0; i < tabs.size(); i++)
	{
		if(this->tabs[i]->getOpen())
			this->tabs[i]->update();
	}
}

void PlayerGUITabs::render(sf::RenderTarget& target)
{
	for (int i = 0; i < tabs.size(); i++)
	{
		if (this->tabs[i]->getOpen())
			this->tabs[i]->render(target);
	}
}
