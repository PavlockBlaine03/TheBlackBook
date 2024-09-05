#pragma once
#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "DefaultEditorMode.h"

class EditorMode;
class Gui;
class State;
class StateData;
class PauseMenu;
class TileMap;
class Tile;
class EditorStateData;

enum EditorModes {DEFAULT_MODE = 0, ENEMY_MODE};

class EditorState : public State
{
private:
	EditorStateData editorStateData;

	sf::View view;
	sf::Font font;
	PauseMenu* pmenu;

	std::map<std::string, gui::Button*> buttons;

	TileMap* tileMap;

	std::vector<EditorMode*> modes;
	float cameraSpeed;

	void initView();
	void initVariables();
	void initEditorStateData();
	void initFonts();
	void initKeybinds();
	void initPauseMenu();
	void initButtons();
	void initGui();
	void initTileMap();

	void initModes();

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

