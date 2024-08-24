#include "stdafx.h"
#include "State.h"

State::State(StateData* state_data)
{
	this->stateData = state_data;
	this->window = state_data->window;
	this->states = state_data->states;
	this->supportedKeys = state_data->supportedKeys;
	this->gridSize = state_data->gridSize;
	this->quit = false;
	this->paused = false;
	this->keytime = 0.f;
	this->keytimeMax = 3.f;
}

State::~State()
{

}

const bool& State::getQuit() const
{
	return this->quit;
}

const bool State::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

const float State::p2pX(const float perc) const
{
	/*
	* Converts a percentage value to pixels relative to current resolution in the x-axis.
	* 
	* @param	float perc		The percentage value.
	* 
	* @return	float			The calculated x-axis pixel value.
	* 
	*/

	return std::floor(static_cast<float>(stateData->gfxSettings->resolution.width* (perc / 100.f)));
}

const float State::p2pY(const float perc) const 
{
	/*
	* Converts a percentage value to pixels relative to current resolution in the y-axis.
	*
	* @param	float perc		The percentage value.
	*
	* @return	float			The calculated y-axis pixel value.
	*
	*/

	return std::floor(static_cast<float>(stateData->gfxSettings->resolution.height * (perc / 100.f)));
}

const unsigned State::calcCharSize() const
{
	/*
	* Calculates character size for text by using current resolution and a constant.
	*
	* @return	unsigned		The calculated character size value.
	*
	*/

	return static_cast<unsigned>((stateData->gfxSettings->resolution.width + stateData->gfxSettings->resolution.height) / 125);
}

void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

void State::updateMousePositions(sf::View* view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	if(view)
		this->window->setView(*view);

	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = 
		sf::Vector2i(
			static_cast<int>(this->mousePosView.x) / static_cast<int>(this->gridSize),
			static_cast<int>(this->mousePosView.y) / static_cast<int>(this->gridSize)
		);
	this->window->setView(this->window->getDefaultView());
}

void State::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
	{
		this->keytime += 10.f * dt;
	}
}
