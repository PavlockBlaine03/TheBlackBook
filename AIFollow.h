#pragma once

#include "AIOption.h"

class AIFollow :
    public AIOption
{
private:


public:
    AIFollow(Entity& self, Entity& entity);
    virtual ~AIFollow();

    virtual void update(const float& dt);

};

