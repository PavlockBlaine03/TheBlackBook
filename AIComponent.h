#pragma once

#include "AIFollow.h"

class AIComponent
{
private:
	Entity& entity;
	Entity& self;

public:
	AIComponent(Entity& self, Entity& entity);
	virtual ~AIComponent();

	void update(const float& dt);
};

