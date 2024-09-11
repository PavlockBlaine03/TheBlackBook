#pragma once

#include "CharacterTab.h"

class PlayerTabs
{
private:

	CharacterTab characterTab;

	sf::VideoMode& vm;
	sf::Font& font;
	Player& player;

public:
	PlayerTabs(sf::VideoMode& vm, sf::Font& font, Player& player);
	virtual ~PlayerTabs();

	const bool tabsOpen();
	void toggleCharacterTab();

	void update();
	void render(sf::RenderTarget& target);
};

