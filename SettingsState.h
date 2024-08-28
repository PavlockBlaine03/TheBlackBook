#pragma once
#include "State.h"

class State;
class SettingsState : public State
{
private:
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::Text optionsText;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::DropDownList*> dropDownLists;
	std::vector<sf::VideoMode> modes;

	void initVariables();
	void initFonts();
	void initKeybinds();
	void initGui();
	void resetGui();

public:
	SettingsState(StateData* state_data);
	virtual ~SettingsState();

	// Accessors

	// Functions
	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

