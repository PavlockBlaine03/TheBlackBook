#pragma once


class TextureManager
{
private:
	std::map<std::string, std::string> textures;

	void initTextures();

public:
	TextureManager();
	virtual ~TextureManager();

	// Functions

	const std::map<std::string, std::string>& getTextures() const;
};

