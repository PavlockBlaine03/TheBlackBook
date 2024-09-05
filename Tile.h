#pragma once

#include "Gui.h"

class Gui;

enum TileTypes {DEFAULT = 0, DAMAGING, RENDERTOP, ENEMYSPAWNER};
class Tile
{
private:


protected:
	sf::Sprite shape;
	bool collision;
	short type;

public:
	Tile();
	Tile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& tile_texture_sheet, const sf::IntRect& tex_rect,
		bool collision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();

	// Functions
	const sf::Vector2f& getPosition() const;
	const bool& getCollision() const;
	const sf::FloatRect getGlobalBounds() const;
	const bool intersects(const sf::FloatRect bounds) const;
	const std::string getAsString() const;
	const short& getType() const;

	virtual void update();
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f player_position = sf::Vector2f());
};

