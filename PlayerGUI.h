#pragma once
#include "Player.h"
#include "Gui.h"

class Player;
class sf::RectangleShape;
class sf::Text;
class sf::Font;

class PlayerGUI
{
private:

	sf::VideoMode& vm;

	sf::Font font;
	Player* player;
	
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

public:
	PlayerGUI(Player* player, sf::VideoMode& vm);
	virtual ~PlayerGUI();

	// Functions

	void updateHpBar();
	void updateExpBar();
	void updateLevelBar();
	void update(const float& dt);

	void renderHpbar(sf::RenderTarget& target);
	void renderExpbar(sf::RenderTarget& target);
	void renderLevelBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

