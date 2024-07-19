#pragma once
#include "State.h"

class SettingsState : public State
{
private:
	GraphicSettings& gfxSettings;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::Text optionsText;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::DropDownList*> dropDownLists;
	std::vector<sf::VideoMode> modes;

	void initBackground();
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initGui();
	void initText();

public:
	SettingsState(sf::RenderWindow* window, GraphicSettings& gfx_settings, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~SettingsState();

	// Accessors

	// Functions
	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

