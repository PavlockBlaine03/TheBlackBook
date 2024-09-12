#pragma once

#include "Entity.h"

class AIOption
{
protected:
	Entity& self;
	Entity& entity;

public:
	AIOption(Entity& self, Entity& entity);
	virtual ~AIOption();

	virtual void update(const float& dt) = 0;
};

