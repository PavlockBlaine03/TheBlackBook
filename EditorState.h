#pragma once
#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"

class Gui;
class State;
class PauseMenu;
class TileMap;

class EditorState : public State
{
private:
	sf::View view;
	sf::Font font;
	sf::Text cursorText;
	PauseMenu* pmenu;

	std::map<std::string, gui::Button*> buttons;

	TileMap* tileMap;

	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;
	sf::RectangleShape sideBar;
	gui::TextureSelector* texureSelector;

	float cameraSpeed;
	int layer;
	bool collision;
	bool tileAddLock;
	short type;

	void initBackground();
	void initView();
	void initVariables();
	void initFonts();
	void initText();
	void initKeybinds();
	void initPauseMenu();
	void initButtons();
	void initGui();
	void initTileMap();

public:
	EditorState(StateData* state_data);
	virtual ~EditorState();

	void updateInput(const float& dt);
	void updateEditorInput(const float& dt);
	void updatePauseMenuButtons();
	void updateButtons();
	void updateGui(const float& dt);
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

