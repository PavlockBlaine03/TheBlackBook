#include "stdafx.h"
#include "RegularTile.h"

RegularTile::RegularTile(short type, int grid_x, int grid_y, float gridSizeF,
	const sf::Texture& tile_texture_sheet, const sf::IntRect& tex_rect, bool collision)
	: Tile(type, grid_x, grid_y, gridSizeF, tile_texture_sheet, tex_rect, collision)
{

}

RegularTile::~RegularTile()
{

}

const std::string RegularTile::getAsString() const
{
	std::stringstream ss;

	ss << this->type <<
		" " << this->shape.getTextureRect().left <<
		" " << this->shape.getTextureRect().top <<
		" " << this->collision;

	return ss.str();
}

void RegularTile::update()
{

}

void RegularTile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_position)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", player_position);

		target.draw(this->shape, shader);
	}
	else
		target.draw(this->shape);
}
