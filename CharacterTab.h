#pragma once

#include "Tab.h"

class CharacterTab : public Tab
{
private:
	sf::RectangleShape backTab;
	sf::Text infoText;

	void initText();

public:
	CharacterTab(sf::VideoMode& vm, sf::Font& font, Player& player);
	virtual ~CharacterTab();


	void update();
	void render(sf::RenderTarget& target);
};

