#include "stdafx.h"
#include "TextTagSystem.h"

void TextTagSystem::initVariables()
{

}

void TextTagSystem::initFonts(std::string font_file)
{
	if (!this->font.loadFromFile(font_file))
	{
		std::cerr << "ERROR::TEXT_TAG_SYSTEM::COULD_NOT_LOAD_FONT " << font_file << "\n";
		exit(EXIT_FAILURE);
	}
}

void TextTagSystem::initTagTemplates()
{
	this->tagTemplates[TagTypes::DEFAULT_TAG] = new TextTag(this->font, "", 400.f, 400.f, 0.f, -1.f, 
		sf::Color::White, 20, 100.f, 125.f, 500.f, 2);

	this->tagTemplates[TagTypes::EXPERIENCE_TAG] = new TextTag(this->font, "", 400.f, 400.f, -0.5f, -1.f, 
		sf::Color::Cyan, 40, 125.f, 160.f, 400.f, 2);

	this->tagTemplates[TagTypes::NEGATIVE_TAG] = new TextTag(this->font, "", 400.f, 400.f, 0.f, 1.f, 
		sf::Color(255, 20, 20), 25, 90.f, 120.f, 500.f, 2);
}

TextTagSystem::TextTagSystem(std::string font_file)
{
	this->initFonts(font_file);
	this->initVariables();
	this->initTagTemplates();
}

TextTagSystem::~TextTagSystem()
{
	// Clean Up Tags
	for (auto* tag : this->tags)
	{
		delete tag;
	}

	// Clean Up Tag Templates
	for (auto& tag : this->tagTemplates)
	{
		delete tag.second;
	}
}

void TextTagSystem::addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const std::string str, 
	const std::string pre_fix, const std::string post_fix)
{
	std::stringstream ss;
	ss << pre_fix << " " << str << " " << post_fix;

	this->tags.push_back(new TextTag(this->tagTemplates[tag_type], pos_x, pos_y, ss.str()));
}

void TextTagSystem::addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const int i, 
	const std::string pre_fix, const std::string post_fix)
{
	std::stringstream ss;
	ss << pre_fix << " " << i << " " << post_fix;

	this->tags.push_back(new TextTag(this->tagTemplates[tag_type], pos_x, pos_y, ss.str()));
}

void TextTagSystem::addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const float f, 
	const std::string pre_fix, const std::string post_fix)
{
	std::stringstream ss;
	ss << pre_fix << " " << f << " " << post_fix;

	this->tags.push_back(new TextTag(this->tagTemplates[tag_type], pos_x, pos_y, ss.str()));
}

void TextTagSystem::update(const float& dt)
{
	for (int i = 0; i < this->tags.size(); ++i)
	{
		this->tags[i]->update(dt);

		if (this->tags[i]->isExpired())
		{
			delete this->tags[i];
			this->tags.erase(this->tags.begin() + i);
		}
	}
}

void TextTagSystem::render(sf::RenderTarget& target)
{
	for (auto& tag : this->tags)
	{
		tag->render(target);
	}
}
