#include "stdafx.h"
#include "Inventory.h"

// Private Functions
void Inventory::initialize()
{
	this->nrOfItems = 0;
	this->itemArray = new Item* [this->capacity];

	this->nullify();
}

void Inventory::nullify(const unsigned from)
{
	for (int i = from; i < this->capacity; i++)
	{
		this->itemArray[i] = nullptr;
	}
}

void Inventory::freeMemory()
{
	for (int i = 0; i < this->nrOfItems; i++)
	{
		delete this->itemArray[i];
	}
	delete[] this->itemArray;
}

// Construtor / Destructor
Inventory::Inventory(unsigned capacity)
{
	this->capacity = capacity;
	this->initialize();
}

Inventory::~Inventory()
{
	this->freeMemory();
}

// Modifiers

// Accessors
const unsigned& Inventory::size() const
{
	return nrOfItems;
}

const unsigned& Inventory::maxSize() const
{
	return capacity;
}

// Functions
const bool Inventory::empty() const
{
	return nrOfItems == 0;
}

const bool Inventory::add(Item* item)
{
	if (this->nrOfItems < this->capacity)
	{
		this->itemArray[this->nrOfItems++] = item->clone();

		return true;
	}

	return false;
}

const bool Inventory::remove(const unsigned index)
{
	if (this->nrOfItems > 0)
	{
		if (index < 0 || index >= this->capacity)
			return false;

		delete this->itemArray[index];
		this->itemArray[index] = nullptr;
		--this->nrOfItems;

		return true;
	}

	return false;
}

// Functions
void Inventory::clear()
{
	for (int i = 0; i < nrOfItems; i++)
	{
		delete this->itemArray[i];
	}

	nrOfItems = 0;
	nullify();
}

const bool Inventory::saveToFile(const std::string file_name)
{
	return false;
}

const bool Inventory::loadFromFile(const std::string file_name)
{
	return false;
}
