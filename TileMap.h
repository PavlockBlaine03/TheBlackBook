#pragma once
#include "Tile.h"

class Tile;
class TileMap
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;
	sf::Vector2u maxSize;
	std::vector<std::vector<std::vector<Tile*>>> map;
	std::string textureFile;
	sf::Texture tileSheet;

	void clear();

public:
	TileMap(float grid_size, unsigned width, unsigned height, std::string texture_file);
	virtual ~TileMap();

	// Accessors
	const sf::Texture* getTileSheet() const;

	// Functions
	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& tex_rect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void update();
	void render(sf::RenderTarget& target);
};

