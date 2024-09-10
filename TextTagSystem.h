#pragma once

enum TagTypes { DEFAULT_TAG = 0, NEGATIVE_TAG, POSITIVE_TAG, EXPERIENCE_TAG, ENVIORMENTAL_TAG };

class TextTagSystem
{
private:
	class TextTag
	{
	private:
		float dirX;
		float dirY;
		float lifeTime;
		float speed;
		sf::Text text;


	public:
		TextTag(sf::Font& font, std::string text, float pos_x, float pos_y, float dir_x, float dir_y,
			sf::Color color, unsigned char_size, float life_time, float speed)
		{
			this->text.setFont(font);
			this->text.setPosition(pos_x, pos_y);
			this->text.setString(text);
			this->text.setFillColor(color);
			this->text.setCharacterSize(char_size);
			this->dirX = dir_x;
			this->dirY = dir_y;
			this->lifeTime = life_time;
			this->speed = speed;
		}

		TextTag(TextTag* tag, float pos_x, float pos_y, std::string str)
		{
			this->text = tag->text;
			this->text.setString(str);
			this->text.setPosition(pos_x, pos_y);
			this->dirX = tag->dirX;
			this->dirY = tag->dirY;
			this->lifeTime = tag->lifeTime;
			this->speed = tag->speed;
		}

		~TextTag()
		{

		}

		// Accessors
		inline const bool isExpired() const { return this->lifeTime <= 0.f; }

		void update(const float& dt)
		{
			if (this->lifeTime > 0.f)
			{
				this->lifeTime -= 100.f * dt;
				this->text.move
				(
					this->dirX * this->speed * dt,
					this->dirY * this->speed * dt
				);
			}
		}
		void render(sf::RenderTarget& target)
		{
			target.draw(this->text);
		}
	};

	sf::Font font;
	std::vector<TextTag*> tags;
	std::map<unsigned, TextTag*> tagTemplates;

	void initVariables();
	void initFonts(std::string font_file);
	void initTagTemplates();

public:
	TextTagSystem(std::string font_file);
	virtual ~TextTagSystem();

	// Functions
	void addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const std::string str,
		const std::string pre_fix = "", const std::string post_fix = "");
	void addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const int i,
		const std::string pre_fix = "", const std::string post_fix = "");
	void addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const float f,
		const std::string pre_fix = "", const std::string post_fix = "");

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

