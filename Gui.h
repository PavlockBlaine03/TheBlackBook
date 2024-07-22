#pragma once

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui
{
	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_cover, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0);

		virtual ~Button();

		// Functions
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);

		const short unsigned& getID() const;
		const bool isPressed() const;
		const std::string getText() const;

		void setText(std::string text);
		void setID(const short unsigned id);
	};

	class DropDownList
	{
	private:
		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;

		float keytime;
		float keytimeMax;

		bool showList;

	public:
		DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned numOfElements, unsigned default_index = 0);
		virtual ~DropDownList();

		const bool getKeytime();
		const unsigned short& getActiveElementID();

		void updateKeytime(const float& dt);
		void update(const sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget& target);
	};

	class TextureSelector
	{
	private:
		float keytime;
		const float keytimeMax;
		float gridSize;
		bool active;
		bool hidden;

		Button* hideBtn;

		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;

	public:
		TextureSelector(float x, float y, float width, float height, float grid_size, const sf::Texture* texture_sheet, sf::Font& font, std::string text);
		~TextureSelector();

		// Accessors
		const bool getKeytime();
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;

		// Functions
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);

	};
}

