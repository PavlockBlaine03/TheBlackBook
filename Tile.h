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
	Tile(short type, int grid_x, int grid_y, float gridSizeF, const sf::Texture& tile_texture_sheet, const sf::IntRect& tex_rect, const bool collision= false);
	virtual ~Tile();

	// Functions
	virtual const bool& getCollision() const;
	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const bool intersects(const sf::FloatRect bounds) const;
	virtual const std::string getAsString() const = 0;

	const short& getType() const;

	virtual void update() = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f player_position = sf::Vector2f()) = 0;
};

