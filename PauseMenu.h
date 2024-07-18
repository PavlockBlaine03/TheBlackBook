#pragma once

#include "Gui.h"

class PauseMenu
{
private:
	sf::RectangleShape background;
	sf::RectangleShape container;

	sf::Text menuText;
	sf::Font& font;

	std::map<std::string, gui::Button*> buttons;

	// Private Functions
	

public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	// Accessor
	std::map<std::string, gui::Button*>& getButtons();


	// Functions
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, const std::string text);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};

