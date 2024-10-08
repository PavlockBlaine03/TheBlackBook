#pragma once
#include "GameState.h"
#include "EditorState.h"
#include "Gui.h"
#include "SettingsState.h"

class GameState;
class EditorState;
class Gui;
class SettingsState;

class MainMenuState : public State
{
private:
	SoundManager& soundManager;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;


	void initVariables();
	void initFonts();
	void initKeybinds();
	void initGui();
	void resetGui();
	void initMenuMusic();

public:
	MainMenuState(StateData* state_data, SoundManager* soundManager);
	virtual ~MainMenuState();


	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

