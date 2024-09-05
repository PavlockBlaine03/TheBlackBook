#include "stdafx.h"
#include "EditorState.h"

void EditorState::initView()
{
	this->view.setSize(sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width), 
		static_cast<float>(this->stateData->gfxSettings->resolution.height))
	);
	this->view.setCenter(sf::Vector2f(
		this->stateData->gfxSettings->resolution.width / 2.f, 
		this->stateData->gfxSettings->resolution.height / 2.f)
	);

}

void EditorState::initVariables()
{
	this->cameraSpeed = 350.f;
}

void EditorState::initEditorStateData()
{
	this->editorStateData.view = &this->view;
	this->editorStateData.keytime = &this->keytime;
	this->editorStateData.keytimeMax = &this->keytimeMax;
	this->editorStateData.keybinds = &this->keybinds;
	this->editorStateData.mousePosGrid = &this->mousePosGrid;
	this->editorStateData.mousePosScreen = &this->mousePosScreen;
	this->editorStateData.mousePosView = &this->mousePosView;
	this->editorStateData.mousePosWindow = &this->mousePosWindow;
	this->editorStateData.font = &this->font;
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("C:/VisualCodeProjects/TheBlackBook/fonts/Folker.ttf"))
	{
		std::cerr << "ERROR::EDITOR_STATE::COULD_NOT_LOAD_FONT";
		exit(EXIT_FAILURE);
	}
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("C:/VisualCodeProjects/TheBlackBook/config/editorstate_keybinds.ini");

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

void EditorState::initButtons()
{
	
}

void EditorState::initGui()
{

}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, 
		"C:/VisualCodeProjects/TheBlackBook/resources/images/tiles/tilesheet4.png");
}

void EditorState::initModes()
{
	this->modes.push_back(new DefaultEditorMode(this->stateData, this->tileMap, &this->editorStateData));
}

void EditorState::initPauseMenu()
{
	const sf::VideoMode& vm = stateData->gfxSettings->resolution;

	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);
	this->pmenu->addButton("QUIT", gui::p2pY(66.7f, vm), gui::p2pX(6.f, vm), gui::p2pY(3.5f, vm), gui::calcCharSize(vm), "Quit");
	this->pmenu->addButton("SAVE", gui::p2pY(56.3f, vm), gui::p2pX(6.f, vm), gui::p2pY(3.5f, vm), gui::calcCharSize(vm), "Save");
	this->pmenu->addButton("LOAD", gui::p2pY(45.8f, vm), gui::p2pX(6.f, vm), gui::p2pY(3.5f, vm), gui::calcCharSize(vm), "Load");
}

EditorState::EditorState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initEditorStateData();
	this->initView();
	this->initFonts();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();
	this->initModes();
}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	auto end = this->buttons.end();
	for (it; it != end; ++it)
	{
		delete it->second;
	}
	delete this->pmenu;
	delete this->tileMap;

	for (auto it : modes)
	{
		delete it;
	}
}

void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("PAUSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void EditorState::updateEditorInput(const float& dt)
{
	// move view
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		this->view.move(this->cameraSpeed * dt, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		this->view.move(-this->cameraSpeed * dt, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		this->view.move(0.f, this->cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
	{
		this->view.move(0.f, -this->cameraSpeed * dt);
	}

	
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();

	if (this->pmenu->isButtonPressed("SAVE"))
		this->tileMap->saveToFile("test.tbbmp");

	if (this->pmenu->isButtonPressed("LOAD"))
		this->tileMap->loadFromFile("C:/VisualCodeProjects/TheBlackBook/test.tbbmp");

}

void EditorState::updateModes(const float& dt)
{
	this->modes[EditorModes::DEFAULT_MODE]->update(dt);
}

void EditorState::updateButtons()
{
	// Updates all buttons
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

}

void EditorState::updateGui(const float& dt)
{
	
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused)	// Unpaused update
	{
		this->updateButtons();
		this->updateGui(dt);
		this->updateEditorInput(dt);
		this->updateModes(dt);
	}
	else    // Paused update
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}

}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::renderGui(sf::RenderTarget& target)
{
	
}

void EditorState::renderModes(sf::RenderTarget& target)
{
	this->modes[EditorModes::DEFAULT_MODE]->render(target);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->setView(this->view);
	this->tileMap->render(*target, this->mousePosGrid, NULL, sf::Vector2f(), true);
	this->tileMap->renderDeferred(*target);

	target->setView(this->window->getDefaultView());
	this->renderButtons(*target);

	this->renderGui(*target);

	this->renderModes(*target);

	if (this->paused)	// paused menu render
	{
		target->setView(this->window->getDefaultView());
		this->pmenu->render(*target);
	}
}

