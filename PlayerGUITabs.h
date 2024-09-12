#pragma once

#include "CharacterTab.h"

enum Player_Tabs {CHARACTER_TAB = 0, INVENTORY_TAB};

class PlayerGUITabs
{
private:

	std::vector<Tab*> tabs;

	sf::VideoMode& vm;
	sf::Font& font;
	Player& player;

	// Init Functions
	void initTabs();

public:
	PlayerGUITabs(sf::VideoMode& vm, sf::Font& font, Player& player);
	virtual ~PlayerGUITabs();

	const bool tabsOpen();
	void toggleTab(const int tab_index);

	void update();
	void render(sf::RenderTarget& target);
};

