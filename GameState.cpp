#include "stdafx.h"
#include "GameState.h"


void GameState::initDebugText()
{
	this->debugText.setFont(fonts.at("FOLKER"));
	this->debugText.setFillColor(sf::Color::Green);
	this->debugText.setCharacterSize(15);
	this->debugText.setPosition(20.f, this->window->getSize().y / 2.f);
}

void GameState::initGameMusic()
{
	this->soundManager.setMusicVolume("GAME_MUSIC", 1.f);
	this->soundManager.playMusic("GAME_MUSIC");
}

void GameState::initGameSound()
{
	this->soundManager.setSoundVolume("SWORD_ATTACK", 12.f);
	this->soundManager.setSoundVolume("WALK", 10.f);
	this->soundManager.setSoundVolume("DAMAGED", 12.f);
	this->soundManager.setSoundVolume("ENEMY_DAMAGED", 12.f);
}

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

void GameState::initTextureManager()
{
	this->textureManager = new TextureManager();
}

void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width / 2),
			static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)
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
	if (!this->fonts["BRICKS"].loadFromFile("C:/VisualCodeProjects/TheBlackBook/fonts/Bricks.ttf"))
	{
		std::cerr << "ERROR::GAME_STATE::COULD_NOT_LOAD_FONT";
		exit(EXIT_FAILURE);
	}

	if (!this->fonts["FOLKER"].loadFromFile("C:/VisualCodeProjects/TheBlackBook/fonts/Folker.ttf"))
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
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures, *this->player);
}

void GameState::initTextTagSystem()
{
	this->textTagSystem = new TextTagSystem("C:/VisualCodeProjects/TheBlackBook/fonts/Digital.TTF");
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile(this->textureManager->getTextures().at("PLAYER")))
	{
		std::cerr << "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
		exit(EXIT_FAILURE);
	}
	if (!this->textures["RAT1_SHEET"].loadFromFile(this->textureManager->getTextures().at("RAT1")))
	{
		std::cerr << "ERROR::GAME_STATE::COULD_NOT_LOAD_RAT_TEXTURE";
		exit(EXIT_FAILURE);
	}
	if (!this->textures["BIRD1_SHEET"].loadFromFile(this->textureManager->getTextures().at("BIRD1")))
	{
		std::cerr << "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD_TEXTURE";
		exit(EXIT_FAILURE);
	}
	if (!this->textures["SCORPION1_SHEET"].loadFromFile(this->textureManager->getTextures().at("SCORPION1")))
	{
		std::cerr << "ERROR::GAME_STATE::COULD_NOT_LOAD_SCORPION_TEXTURE";
		exit(EXIT_FAILURE);
	}
	if (!this->textures["BLOB1_SHEET"].loadFromFile(this->textureManager->getTextures().at("BLOB1")))
	{
		std::cerr << "ERROR::GAME_STATE::COULD_NOT_LOAD_BLOB_TEXTURE";
		exit(EXIT_FAILURE);
	}
}

void GameState::initPauseMenu()
{
	const sf::VideoMode& vm = stateData->gfxSettings->resolution;

	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->fonts["BRICKS"]);
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
	this->player = new Player(this->textures["PLAYER_SHEET"], this->textureManager, 400.f, 200.f);
}

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player, stateData->gfxSettings->resolution);
}

GameState::GameState(StateData* state_data, SoundManager* soundManager)
	: State(state_data), soundManager(*soundManager)
{
	this->initGameMusic();
	this->initGameSound();
	this->initDeferredRender();
	this->initTextureManager();
	this->initTextures();
	this->initPlayers();
	this->initTextTagSystem();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initPauseMenu();
	this->initEnemySystem();
	this->initPlayerGUI();
	this->initTileMap();
	this->initShaders();
	this->initDebugText();

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
	delete this->textTagSystem;
	delete this->textureManager;
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("PAUSE"))) && this->getKeytime())
	{
		if (!this->paused)
		{
			this->soundManager.pauseMusic("GAME_MUSIC");
			this->pauseState();
		}
		else
		{
			this->soundManager.playMusic("GAME_MUSIC");
			this->unpauseState();
		}
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_PLAYER_CHARACTER_TAB"))) && this->getKeytime())
	{
		this->playerGUI->toggleCharacterTab();
	}
}

void GameState::updatePlayer(const float& dt)
{
	this->player->update(dt, mousePosView, this->view);

	this->updatePlayerGUI(dt);
}

void GameState::updateCombatAndEnemies(const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->getWeapon()->getAttackTimer())
	{
		this->soundManager.playSound("SWORD_ATTACK");
		this->player->setInitAttack(true);
	}

	unsigned index = 0;
	for (auto* enemy : activeEnemies) 
	{
		enemy->update(dt, mousePosView, this->view);
		this->tileMap->updateWorldBoundsCollision(enemy, dt);
		this->tileMap->updateTilesCollision(enemy, dt);

		this->updateCombat(enemy, index, dt);

		// Dangerous!!! Delete later
		if (enemy->isDead())
		{
			this->player->gainEXP(
				static_cast<int>(enemy->getGainExp())
			);

			this->textTagSystem->addTextTag(
				TagTypes::EXPERIENCE_TAG, 
				this->player->getCenter().x - gui::p2pX(1.f, this->stateData->gfxSettings->resolution), this->player->getCenter().y,
				static_cast<int>(enemy->getGainExp()),
				"+", "exp"
			);

			this->enemySystem->removeEnemy(index);
			continue;
		}
		else if (enemy->getDespawnTimerDone())
		{
			this->enemySystem->removeEnemy(index);
			continue;
		}

		++index;
	}
	this->player->setInitAttack(false);
}

void GameState::updateCombat(Enemy* enemy, const int index, const float& dt)
{
	if (this->player->getInitAttack() 
		&& enemy->getGlobalBounds().intersects(this->player->getWeapon()->getSprite().getGlobalBounds())
		&& enemy->getSpriteDistance(*this->player) < this->player->getWeapon()->getRange()
		&& enemy->getDamageTimer())
	{
		int dmg = static_cast<int>(this->player->getDamage());
		this->textTagSystem->addTextTag(
			TagTypes::DEFAULT_TAG, enemy->getCenter().x,
			enemy->getCenter().y,
			dmg, "", ""
		);
		this->soundManager.playSound("ENEMY_DAMAGED");
		enemy->loseHP(dmg);
	}

	// Check for enemy damage
	if (enemy->getGlobalBounds().intersects(player->getGlobalBounds()) && player->getDamageTimer())
	{
		this->soundManager.playSound("DAMAGED");

		int dmg = enemy->getAttributeComponent()->dmgMax;
		player->loseHP(dmg);
		this->textTagSystem->addTextTag(TagTypes::NEGATIVE_TAG, player->getPosition().x, player->getPosition().y, dmg, "-", "hp");

		// Test Death of character
		/*if (player->getAttributeComponent()->hp <= 0)
		{
			this->soundManager.stopMusic("GAME_MUSIC");
			this->soundManager.playMusic("MENU_MUSIC");
			this->endState();
		}*/
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);
	this->updateDebugText(dt);

	if (!this->paused)	// Unpaused update
	{
		this->updateView(dt);

		this->updatePlayerInput(dt);

		this->updateTileMap(dt);

		this->updatePlayer(dt);

		this->updateCombatAndEnemies(dt);

		this->textTagSystem->update(dt);

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
		this->soundManager.stopMusic("GAME_MUSIC");
		this->soundManager.playMusic("MENU_MUSIC");
		this->endState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	// update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
	{
		if (this->getKeytime())
			this->soundManager.playSound("WALK");

		this->player->move(-1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		if (this->getKeytime())
			this->soundManager.playSound("WALK");
		this->player->move(0.f, 1.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
	{
		if (this->getKeytime())
			this->soundManager.playSound("WALK");
		this->player->move(1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		if (this->getKeytime())
			this->soundManager.playSound("WALK");
		this->player->move(0.f, -1.f, dt);
	}
}

void GameState::updateDebugText(const float& dt)
{
	std::stringstream ss;

	ss << "Mouse Pos View: " << this->mousePosView.x << " X " << this->mousePosView.y << "\n"
		<< "Active Enemies: " << activeEnemies.size() << "\n";

	this->debugText.setString(ss.str());
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
		enemy->render(this->renderTexture, &this->coreShader, this->player->getCenter(), true);
	}

	this->player->render(this->renderTexture, &coreShader, this->player->getCenter(), true);

	this->tileMap->renderDeferred(this->renderTexture, &coreShader, player->getCenter());

	this->textTagSystem->render(this->renderTexture);

	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);

	if (this->paused)	// paused menu render
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

	this->renderTexture.draw(this->debugText);

	// final render
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
