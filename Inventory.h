#pragma once

#include "Item.h"

class Inventory
{
private:
	Item** itemArray;
	unsigned nrOfItems;
	unsigned capacity;

	// Private Functions
	void initialize();
	void nullify(const unsigned from = 0);
	void freeMemory();

public:
	Inventory(unsigned capacity);
	virtual ~Inventory();

	// Modifiers


	// Accessors
	const unsigned& size() const;
	const unsigned& maxSize() const;


	// Functions
	const bool empty() const;
	const bool add(Item* item);
	const bool remove(const unsigned index);
	void clear();

	const bool saveToFile(const std::string file_name);
	const bool loadFromFile(const std::string file_name);

};

