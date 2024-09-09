#include "stdafx.h"
#include "GameState.h"


void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0,
			0,
			this->stateData->gfxSettings->resolution.width,
			this->stateData->gfxSettings->resolution.height
		)
	);

}

void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			this->stateData->gfxSettings->resolution.width / 2.f,
			this->stateData->gfxSettings->resolution.height / 2.f
		)
	);
}

void GameState::initKeybinds()
{
	std::ifstream ifs("C:/VisualCodeProjects/TheBlackBook/config/gamestate_keybinds.ini");

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

void GameState::initFonts()
{
	if (!this->font.loadFromFile("C:/VisualCodeProjects/TheBlackBook/fonts/Bricks.ttf"))
	{
		std::cerr << "ERROR::GAME_STATE::COULD_NOT_LOAD_FONT";
		exit(EXIT_FAILURE);
	}
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap("C:/VisualCodeProjects/TheBlackBook/test.tbbmp");
}

void GameState::initEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures);
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile(this->textureManager.getTextures().at("PLAYER")))
	{
		std::cerr << "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
		exit(EXIT_FAILURE);
	}
	if (!this->textures["RAT1_SHEET"].loadFromFile(this->textureManager.getTextures().at("RAT1")))
	{
		std::cerr << "ERROR::GAME_STATE::COULD_NOT_LOAD_RAT_TEXTURE";
		exit(EXIT_FAILURE);
	}
}

void GameState::initPauseMenu()
{
	const sf::VideoMode& vm = stateData->gfxSettings->resolution;

	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);
	this->pmenu->addButton("EXIT_STATE", gui::p2pY(66.7f, vm), gui::p2pX(6.f, vm), gui::p2pY(3.5f, vm), gui::calcCharSize(vm), "Quit");
}

void GameState::initShaders()
{
	if (!coreShader.loadFromFile("C:/VisualCodeProjects/TheBlackBook/vertex_shader.vert", "C:/VisualCodeProjects/TheBlackBook/fragment_shader.frag"))
	{
		std::cerr << "ERROR::GAME_STATE::COULD_NOT_LOAD_SHADER";
		exit(EXIT_FAILURE);
	}
}

void GameState::initPlayers()
{
	this->player = new Player(this->textures["PLAYER_SHEET"], &this->textureManager, 400.f, 200.f);
}

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player, stateData->gfxSettings->resolution);
}

GameState::GameState(StateData* state_data, sf::Music* menu_music)
	: State(state_data)
{
	this->menuMusic = menu_music;
	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initEnemySystem();
	this->initPauseMenu();
	this->initPlayers();
	this->initPlayerGUI();
	this->initTileMap();
	this->initShaders();

}

GameState::~GameState()
{
	delete this->player;
	delete this->pmenu;
	delete this->tileMap;
	delete this->playerGUI;

	for (auto it : activeEnemies) {
		delete it;
	}
	delete this->enemySystem;
}

void GameState::restartMenuMusic()
{
	this->menuMusic->setLoop(true);
	this->menuMusic->setVolume(25);
	this->menuMusic->play();
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("PAUSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updateView(const float& dt)
{
	this->view.setCenter(
		std::floor(this->player->getPosition().x + (static_cast<float>(mousePosWindow.x) - static_cast<float>(stateData->gfxSettings->resolution.width / 2.f)) / 10.f),
		std::floor(this->player->getPosition().y + (static_cast<float>(mousePosWindow.y) - static_cast<float>(stateData->gfxSettings->resolution.height / 2.f)) / 10.f)
	);

	if (view.getSize().x <= tileMap->getMaxSizeF().x)
	{
		if (view.getCenter().x - view.getSize().x / 2.f < 0.f)
		{
			view.setCenter(0.f + view.getSize().x / 2.f, view.getCenter().y);
		}
		else if (view.getCenter().x + view.getSize().x / 2.f > tileMap->getMaxSizeF().x)
		{
			view.setCenter(tileMap->getMaxSizeF().x - view.getSize().x / 2.f, view.getCenter().y);
		}
	}

	if (view.getSize().y <= tileMap->getMaxSizeF().y)
	{
		if (view.getCenter().y - view.getSize().y / 2.f < 0.f)
		{
			view.setCenter(view.getCenter().x, 0.f + view.getSize().y / 2.f);
		}
		else if (view.getCenter().y + view.getSize().y / 2.f > tileMap->getMaxSizeF().y)
		{
			view.setCenter(view.getCenter().x, tileMap->getMaxSizeF().y - view.getSize().y / 2.f);
		}
	}

	viewGridPosition.x = static_cast<int>(view.getCenter().x) / static_cast<int>(stateData->gridSize);
	viewGridPosition.y = static_cast<int>(view.getCenter().y) / static_cast<int>(stateData->gridSize);
}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->updateWorldBoundsCollision(this->player, dt);
	this->tileMap->updateTilesCollision(this->player, dt);
	this->tileMap->updateTiles(this->player, dt, *this->enemySystem);
}

void GameState::updatePlayerGUI(const float& dt)
{
	this->playerGUI->update(dt);
}

void GameState::updatePlayer(const float& dt)
{

}

void GameState::updateCombatAndEnemies(const float& dt)
{
	int index = 0;
	for (auto* enemy : activeEnemies) 
	{
		enemy->update(dt, mousePosView);
		this->tileMap->updateWorldBoundsCollision(enemy, dt);
		this->tileMap->updateTilesCollision(enemy, dt);
		this->updateCombat(enemy, index, dt);

		// Dangerous!!! Delete later
		if (enemy->isDead())
		{
			this->player->gainEXP(enemy->getGainExp());

			this->activeEnemies.erase(this->activeEnemies.begin() + index);
			--index;
		}

		++index;
	}
}

void GameState::updateCombat(Enemy* enemy, const int indexs, const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (enemy->getGlobalBounds().contains(this->mousePosView) &&
			enemy->getDistance(*this->player) < this->player->getWeapon()->getRange())
		{
			enemy->loseHP(this->player->getWeapon()->getDamageMin());
			std::cout << enemy->getAttributeComponent()->hp << std::endl;
		}
	}

}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused)	// Unpaused update
	{
		this->updateView(dt);

		this->updatePlayerInput(dt);

		this->updateTileMap(dt);

		this->player->update(dt, mousePosView);

		this->updatePlayerGUI(dt);

		this->updateCombatAndEnemies(dt);

	}
	else    // Paused update
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("EXIT_STATE"))
	{
		this->endState();
		//this->restartMenuMusic();
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	// update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
	{
		this->player->move(-1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player->move(0.f, 1.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
	{
		this->player->move(1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		this->player->move(0.f, -1.f, dt);
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);
	this->tileMap->render(
		this->renderTexture, 
		viewGridPosition, 
		&coreShader, 
		player->getCenter(), 
		false
	);

	for (auto* enemy : activeEnemies) {
		enemy->render(this->renderTexture, &this->coreShader, this->player->getCenter(), false);
	}

	this->player->render(this->renderTexture, &coreShader, this->player->getCenter(), false);

	this->tileMap->renderDeferred(this->renderTexture, &coreShader, player->getCenter());

	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);

	if (this->paused)	// paused menu render
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

	// final render
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
