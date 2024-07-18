#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Gui.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

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

