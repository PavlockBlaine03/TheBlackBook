#include "stdafx.h"
#include "TextureManager.h"

void TextureManager::initTextures()
{
	this->textures["PLAYER"] = "C:/VisualCodeProjects/TheBlackBook/resources/images/Sprites/Player/PLAYER_SHEET2.png";
	this->textures["RAT1"] = "C:/VisualCodeProjects/TheBlackBook/resources/images/Sprites/Enemy/rat1_60x64.png";
	this->textures["SWORD"] = "C:/VisualCodeProjects/TheBlackBook/resources/images/Sprites/Player/sword.png";
}

TextureManager::TextureManager()
{
	this->initTextures();
}

TextureManager::~TextureManager()
{
}

const std::map<std::string, std::string>& TextureManager::getTextures() const
{
	return this->textures;
}
