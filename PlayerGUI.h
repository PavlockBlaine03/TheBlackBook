 #pragma once

#include "PlayerTabs.h"

class PlayerGUI
{
private:

	sf::VideoMode& vm;

	sf::Font font;
	Player* player;
	std::unique_ptr<PlayerTabs> playerTabs;
	
	// Level Bar
	std::string lvlBarString;
	sf::Text lvlBarText;
	sf::RectangleShape lvlBarBack;

	// EXP bar
	gui::ProgressBar* expBar;

	// Health Bar
	gui::ProgressBar* hpBar;

	void initFont();
	void initLevelBar();
	void initHpBar();
	void initExpBar();
	void initPlayerTabs(sf::VideoMode& vm, sf::Font& font, Player& player);

public:
	PlayerGUI(Player* player, sf::VideoMode& vm);
	virtual ~PlayerGUI();

	// Functions
	const bool getTabsOpen() const;
	void toggleCharacterTab();

	void updatePlayerTabs();
	void updateHpBar();
	void updateExpBar();
	void updateLevelBar();
	void update(const float& dt);

	void renderPlayerTabs(sf::RenderTarget& target);
	void renderHpbar(sf::RenderTarget& target);
	void renderExpbar(sf::RenderTarget& target);
	void renderLevelBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

