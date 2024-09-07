#pragma once

#include "Tile.h"

class Tile;

class RegularTile :
    public Tile
{
private:


protected:


public:
    RegularTile(short type, int grid_x, int grid_y, float gridSizeF, const sf::Texture& tile_texture_sheet, const sf::IntRect& tex_rect,
        bool collision = false);
    virtual ~RegularTile();

	// Functions
	virtual const std::string getAsString() const;

	virtual void update();
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f player_position = sf::Vector2f());
};

