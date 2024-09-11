#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initVariables()
{

}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("C:/VisualCodeProjects/TheBlackBook/fonts/Bricks.ttf"))
	{
		std::cerr << "ERROR::MAIN_STATE::COULD_NOT_LOAD_FONT";
		exit(EXIT_FAILURE);
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("C:/VisualCodeProjects/TheBlackBook/config/mainmenu_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";
		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void MainMenuState::initGui()
{
	const sf::VideoMode& vm = stateData->gfxSettings->resolution;

	this->background.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));

	if (!this->backgroundTexture.loadFromFile("C:/VisualCodeProjects/TheBlackBook/resources/images/backgrounds/bg1.png"))
	{
		std::cerr << "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_BACKGROUND_IMAGE_FILE";
		exit(EXIT_FAILURE);
	}

	this->background.setTexture(&this->backgroundTexture);

	this->buttons["GAME_STATE"] = new gui::Button(gui::p2pX(70.3f, vm), gui::p2pY(48.6f, vm), gui::p2pX(6.f, vm), gui::p2pY(3.5f, vm), &this->font, "New Game", gui::calcCharSize(vm),
		sf::Color(125, 125, 125, 200), sf::Color(255, 255, 255, 255), sf::Color(70, 70, 70, 200),				// Text colors
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));		// Button Colors

	this->buttons["SETTINGS_STATE"] = new gui::Button(gui::p2pX(70.3f, vm), gui::p2pY(55.5f, vm), gui::p2pX(6.f, vm), gui::p2pY(3.5f, vm), &this->font, "Settings", gui::calcCharSize(vm),
		sf::Color(125, 125, 125, 200), sf::Color(255, 255, 255, 255), sf::Color(70, 70, 70, 200),				// Text Colors
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));		// Button Colors

	this->buttons["EDITOR_STATE"] = new gui::Button(gui::p2pX(70.3f, vm), gui::p2pY(62.5f, vm), gui::p2pX(6.f, vm), gui::p2pY(3.5f, vm), &this->font, "Editor", gui::calcCharSize(vm),
		sf::Color(125, 125, 125, 200), sf::Color(255, 255, 255, 255), sf::Color(70, 70, 70, 200),				// Text Colors
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));		// Button Colors

	this->buttons["EXIT_STATE"] = new gui::Button(gui::p2pX(70.3f, vm), gui::p2pY(69.4, vm), gui::p2pX(6.f, vm), gui::p2pY(3.5f, vm), &this->font, "Quit", gui::calcCharSize(vm),
		sf::Color(125, 125, 125, 200), sf::Color(255, 255, 255, 255), sf::Color(70, 70, 70, 200),				// Text Colors
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));		// Button Colors
}

void MainMenuState::resetGui()
{
	/*
	* 
	* Clears the gui and re-initilizes the GUI
	* 
	* @return void
	* 
	*/

	auto it = this->buttons.begin();
	auto end = this->buttons.end();
	for (it; it != end; ++it)
	{
		delete it->second;
	}

	this->buttons.clear();

	this->initGui();
}

void MainMenuState::initMenuMusic()
{
	this->soundManager.loadMusic("MENU_MUSIC", "C:/VisualCodeProjects/TheBlackBook/resources/sound/menu/MenuMusic.wav");
}

MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initMenuMusic();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->resetGui();

}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	auto end = this->buttons.end();
	for (it; it != end; ++it)
	{
		delete it->second;
	}
}

void MainMenuState::updateInput(const float& dt)
{
	// update player input
}

void MainMenuState::updateButtons()
{
	// Updates all buttons
	for(auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	// New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->soundManager.stopMusic("MENU_MUSIC");
		this->states->push(new GameState(this->stateData));
	}

	// Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->soundManager.stopMusic("MENU_MUSIC");
		this->states->push(new SettingsState(this->stateData));
	}

	// Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->soundManager.stopMusic("MENU_MUSIC");
		this->states->push(new EditorState(this->stateData));
	}

	// Quit game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->soundManager.stopMusic("MENU_MUSIC");
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->soundManager.playMusic("MENU_MUSIC");
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	this->renderButtons(*target);

}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}
