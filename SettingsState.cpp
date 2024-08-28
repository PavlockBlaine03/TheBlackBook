#include "stdafx.h"
#include "SettingsState.h"

// Init functions
void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("C:/VisualCodeProjects/TheBlackBook/fonts/Folker.ttf"))
	{
		std::cerr << "ERROR::MAIN_STATE::COULD_NOT_LOAD_FONT";
		exit(EXIT_FAILURE);
	}
}

void SettingsState::initKeybinds()
{
	std::ifstream ifs("C:/VisualCodeProjects/TheBlackBook/config/settings_keybinds.ini");

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

void SettingsState::initGui()
{
	const sf::VideoMode& vm = stateData->gfxSettings->resolution;

	this->background.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));

	if (!this->backgroundTexture.loadFromFile("C:/VisualCodeProjects/TheBlackBook/resources/images/backgrounds/bg1.png"))
	{
		std::cerr << "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_BACKGROUND_IMAGE_FILE";
		exit(EXIT_FAILURE);
	}

	this->background.setTexture(&this->backgroundTexture);

	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(90.f, vm), gui::p2pY(90.2f, vm), gui::p2pX(6.f, vm), gui::p2pY(3.5f, vm),
		&this->font, "Back", gui::calcCharSize(vm),
		sf::Color(125, 125, 125, 200), sf::Color(255, 255, 255, 255), sf::Color(70, 70, 70, 200),	
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0
		)
	);

	this->buttons["APPLY"] = new gui::Button(
		gui::p2pX(82.f, vm), gui::p2pY(90.2f, vm), gui::p2pX(6.f, vm), gui::p2pY(3.5f, vm),
		&this->font, "Apply", gui::calcCharSize(vm),
		sf::Color(125, 125, 125, 200), sf::Color(255, 255, 255, 255), sf::Color(70, 70, 70, 200),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0
		)
	);

	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}
	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(gui::p2pX(75.3f, vm), gui::p2pY(27.8f, vm), gui::p2pX(7.8f, vm), gui::p2pY(3.5f, vm), font, vm, modes_str.data(), static_cast<unsigned>(modes_str.size()));
	
	// Text
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(gui::p2pX(62.5f, vm), gui::p2pY(29.5f, vm)));
	this->optionsText.setCharacterSize(gui::calcCharSize(vm));
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));


	this->optionsText.setString("Resolution \n\n\nFullscreen \n\n\nVsync \n\n\nAntialiasing \n\n\n");

}

void SettingsState::resetGui()
{
	/*
	* 
	* Clears the gui elements and re-initializes the GUI
	* 
	* @return void
	* 
	*/

	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
	this->buttons.clear();

	for (auto it = this->dropDownLists.begin(); it != this->dropDownLists.end(); ++it) {
		delete it->second;
	}
	this->dropDownLists.clear();

	this->initGui();
}

SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initGui();
	this->initKeybinds();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	auto end = this->buttons.end();
	for (it; it != end; ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownLists.begin();
	auto end2 = this->dropDownLists.end();
	for (it2; it2 != end2; ++it2)
	{
		delete it2->second;
	}
}
// Accessors

// Functions
void SettingsState::updateInput(const float& dt)
{
	// update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void SettingsState::updateGui(const float& dt)
{
	// Updates all buttons
	// Buttons
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	// Quit game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}

	// Apply settings
	if (this->buttons["APPLY"]->isPressed())
	{	
		// Test remove later
		this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementID()];
		this->window->close();

		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);

		this->resetGui();
	}

	// Update Dropdownlists
	for (auto& it : this->dropDownLists)
	{
		it.second->update(this->mousePosWindow, dt);
	}
}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateGui(dt);
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	this->renderGui(*target);

	target->draw(this->optionsText);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
	for (auto& it : this->dropDownLists)
	{
		it.second->render(target);
	}
}
