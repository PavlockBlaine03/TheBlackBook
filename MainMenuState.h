#pragma once
#include "GameState.h"
#include "EditorState.h"
#include "Gui.h"
#include "SettingsState.h"

class MainMenuState : public State
{
private:

	GraphicSettings& gfxSettings;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	void initBackground();
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	MainMenuState(sf::RenderWindow* window, GraphicSettings& gfx_settings, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

