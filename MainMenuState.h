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

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	sf::SoundBuffer menuBuffer;
	sf::Sound menuSound;
	sf::Music menuMusic;

	void initVariables();
	void initFonts();
	void initKeybinds();
	void initGui();
	void initAudio();
	void resetGui();

public:
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();


	void stopMusic();
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

