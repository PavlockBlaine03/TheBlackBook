#include "stdafx.h"
#include "Gui.h"

const float gui::p2pX(const float perc, const sf::VideoMode& vm)
{
	/*
	* Converts a percentage value to pixels relative to current resolution in the x-axis.
	*
	* @param	float perc				The percentage value.
	* @param	sf::VideoMode& vm		The current video mode.
	*
	* @return	float					The calculated x-axis pixel value.
	*
	*/

	return std::floor(static_cast<float>(vm.width * (perc / 100.f)));
}

const float gui::p2pY(const float perc, const sf::VideoMode& vm)
{
	/*
	* Converts a percentage value to pixels relative to current resolution in the y-axis.
	*
	* @param	float perc				The percentage value.
	* @param	sf::VideoMode& vm		The current video mode.
	*
	* @return	float					The calculated y-axis pixel value.
	*
	*/

	return std::floor(static_cast<float>(vm.height * (perc / 100.f)));
}

const unsigned gui::calcCharSize(const sf::VideoMode& vm, const unsigned modifier)
{
	/*
	* Calculates character size for text by using current resolution and a constant.
	* 
	* @param	sf::VideoMode& vm			The current video mode.
	* @param	const unsigned modifier		Modifies the character size.
	* 
	* @return	unsigned				The calculated character size value.
	*
	*/

	return static_cast<unsigned>((vm.width + vm.height) / modifier);
}

gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size, 
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, 
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color, 
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
	short unsigned id)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;

	this->id = id;
}

gui::Button::~Button()
{

}

void gui::Button::update(const sf::Vector2i& mousePosWindow)
{
	/*Update the booleans for hover and pressed*/

	// Idle
	this->buttonState = BTN_IDLE;

	// Hover
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->buttonState = BTN_HOVER;

		// Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}
	
	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		this->text.setFillColor(this->textIdleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		this->text.setFillColor(this->textActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->shape.setOutlineColor(sf::Color::Green);
		this->text.setFillColor(sf::Color::White);
		break;
	}

}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

const short unsigned& gui::Button::getID() const
{
	return this->id;
}

// Accessors
const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
	{
		return true;
	}
	else
		return false;
}

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

// Modifiers
void gui::Button::setText(std::string text)
{
	this->text.setString(text);
}

void gui::Button::setID(const short unsigned id)
{
	this->id = id;
}

/*******************************
* ******************************
* *****DROPDOWNBOX CLASS********
* ******************************
********************************/

gui::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& font, sf::VideoMode vm, std::string list[], unsigned numOfElements, unsigned default_index)
	: font(font), showList(false), keytimeMax(1.f), keytime(0.f)
{
	this->activeElement = new gui::Button(
		x, y, width, height, &this->font, list[default_index], gui::calcCharSize(vm, 160),
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(70, 70, 70, 200),
		sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 100), sf::Color(20, 20, 20, 100), 
		sf::Color(255, 255, 255, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 50)
	);

	for (unsigned i = 0; i < numOfElements; i++)
	{
		this->list.push_back(
			new gui::Button(
				x, y + ((i + 1) * height), width, height, &this->font, list[i], 16,
				sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(70, 70, 70, 200),
				sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 100), sf::Color(20, 20, 20, 100), 
				sf::Color(255, 255, 255, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), 
				i
			)
		);
	}


}
gui::DropDownList::~DropDownList()
{
	delete this->activeElement;
	for (size_t i = 0; i < this->list.size(); i++)
	{
		delete this->list[i];
	}
}

// Functions
const bool gui::DropDownList::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	else
		return false;
}

const unsigned short& gui::DropDownList::getActiveElementID()
{
	return this->activeElement->getID();
}

void gui::DropDownList::updateKeytime(const float& dt)
{
	if(this->keytime < this->keytimeMax)
		this->keytime += 10.f * dt;
}

void gui::DropDownList::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
	this->updateKeytime(dt);
	this->activeElement->update(mousePosWindow);

	if (this->activeElement->isPressed() && this->getKeytime())
	{
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->update(mousePosWindow);

			if (i->isPressed() && this->getKeytime())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setID(i->getID());
			}
		}
	}
}

void gui::DropDownList::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->render(target);
		}
	}
}
/*******************************
* ******************************
* *****TEXTURESELECTOR CLASS****
* ******************************
********************************/

gui::TextureSelector::TextureSelector(float x, float y, float width, float height, float grid_size, const sf::Texture* texture_sheet,
	sf::Font& font, std::string text)
	: keytimeMax(2.f), keytime(0.f)
{
	this->hidden = false;
	this->active = false;
	this->gridSize = grid_size;

	float yOffset = grid_size;

	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x, y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->sheet.getGlobalBounds().height)));
	}
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->sheet.getGlobalBounds().width), static_cast<int>(this->bounds.getGlobalBounds().height)));
	}

	this->selector.setPosition(x, y);
	this->selector.setSize(sf::Vector2f(this->gridSize, grid_size));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Red);

	this->textureRect.width = static_cast<int>(this->gridSize);
	this->textureRect.height = static_cast<int>(this->gridSize);

	this->hideBtn = new gui::Button(
		x, y - yOffset, 125.f, 50.f, &font, text, 32,
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(90, 90, 90, 200),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 250), sf::Color(70, 70, 70, 50));
}

gui::TextureSelector::~TextureSelector()
{
	delete this->hideBtn;
}

// Accessors
const bool& gui::TextureSelector::getActive() const
{
	return this->active;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	return this->textureRect;
}

const bool gui::TextureSelector::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	else
		return false;
}

// Functions
void gui::TextureSelector::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.f * dt;
}

void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
	this->updateKeytime(dt);
	this->hideBtn->update(mousePosWindow);

	if (this->hideBtn->isPressed() && this->getKeytime())
	{
		if (this->hidden)
			this->hidden = false;
		else
			this->hidden = true;
	}

	if (!this->hidden)
	{
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
			this->active = true;
		else
			this->active = false;

		if (this->active)
		{
			this->mousePosGrid.x = ((mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize));
			this->mousePosGrid.y = ((mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize));

			this->selector.setPosition(
				this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
				this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize
			);

			// Update texture rectangle
			this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
			this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
		}
	}
}

void gui::TextureSelector::render(sf::RenderTarget& target)
{

	if (!this->hidden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);

		if (this->active)
			target.draw(this->selector);
	}

	this->hideBtn->render(target);
}
