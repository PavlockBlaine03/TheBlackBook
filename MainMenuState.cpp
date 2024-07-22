#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	
	if (!this->backgroundTexture.loadFromFile("C:/VisualCodeProjects/TheBlackBook/resources/images/backgrounds/bg1.png"))
	{
		std::cerr << "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_BACKGROUND_IMAGE_FILE";
		exit(EXIT_FAILURE);
	}

	this->background.setTexture(&this->backgroundTexture);
}

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

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new gui::Button(1800.f, 700.f, 150.f, 50.f, &this->font, "New Game", 32,
		sf::Color(125, 125, 125, 200), sf::Color(255, 255, 255, 255), sf::Color(70, 70, 70, 200),				// Text colors
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));		// Button Colors

	this->buttons["SETTINGS_STATE"] = new gui::Button(1800.f, 800.f, 150.f, 50.f, &this->font, "Settings", 32,
		sf::Color(125, 125, 125, 200), sf::Color(255, 255, 255, 255), sf::Color(70, 70, 70, 200),				// Text Colors
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));		// Button Colors

	this->buttons["EDITOR_STATE"] = new gui::Button(1800.f, 900.f, 150.f, 50.f, &this->font, "Editor", 32,
		sf::Color(125, 125, 125, 200), sf::Color(255, 255, 255, 255), sf::Color(70, 70, 70, 200),				// Text Colors
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));		// Button Colors

	this->buttons["EXIT_STATE"] = new gui::Button(1800.f, 1000.f, 150.f, 50.f, &this->font, "Quit", 32,
		sf::Color(125, 125, 125, 200), sf::Color(255, 255, 255, 255), sf::Color(70, 70, 70, 200),				// Text Colors
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));		// Button Colors
}
void MainMenuState::initAudio()
{
	if (!this->menuBuffer.loadFromFile("C:/VisualCodeProjects/TheBlackBook/resources/sound/menu/MenuMusic.wav"))
	{
		std::cerr << "ERROR::MAIN_MENU_STATE::INIT_AUDIO::COULD_NOT_LOAD_AUDIO_FILE" << std::endl;
	}
	this->menuSound.setBuffer(this->menuBuffer);

	if (!this->menuMusic.openFromFile("C:/VisualCodeProjects/TheBlackBook/resources/sound/menu/MenuMusic.wav"))
	{
		std::cerr << "ERROR::MAIN_MENU_STATE::INIT_AUDIO::COULD_NOT_LOAD_MUSIC_FILE" << std::endl;
	}

	this->menuMusic.setLoop(true);
	this->menuMusic.setVolume(25);
	this->menuMusic.play();
}

MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initAudio();

}

MainMenuState::~MainMenuState()
{
	this->stopMusic();
	auto it = this->buttons.begin();
	auto end = this->buttons.end();
	for (it; it != end; ++it)
	{
		delete it->second;
	}
}

void MainMenuState::stopMusic()
{
	this->menuMusic.stop();
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
		it.second->update(this->mousePosView);
	}

	// New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->stopMusic();
		this->states->push(new GameState(this->stateData));
	}

	// Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingsState(this->stateData));
	}

	// Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}

	// Quit game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
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
